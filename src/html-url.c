/* Collect URLs from HTML source.
   Copyright (C) 1998, 2000 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include "wget.h"
#include "html-parse.h"
#include "url.h"
#include "utils.h"

#ifndef errno
extern int errno;
#endif

enum tag_category { TC_LINK, TC_SPEC };

/* Here we try to categorize the known tags.  Each tag has its ID and
   cetegory.  Category TC_LINK means that one or more of its
   attributes contain links that should be retrieved.  TC_SPEC means
   that the tag is specific in some way, and has to be handled
   specially. */
static struct {
  const char *name;
  enum tag_category category;
} known_tags[] = {
#define TAG_A		0
  { "a",	TC_LINK },
#define TAG_APPLET	1
  { "applet",	TC_LINK },
#define TAG_AREA	2
  { "area",	TC_LINK },
#define TAG_BASE	3
  { "base",	TC_SPEC },
#define TAG_BGSOUND	4
  { "bgsound",	TC_LINK },
#define TAG_BODY	5
  { "body",	TC_LINK },
#define TAG_EMBED	6
  { "embed",	TC_LINK },
#define TAG_FIG		7
  { "fig",	TC_LINK },
#define TAG_FRAME	8
  { "frame",	TC_LINK },
#define TAG_IFRAME	9
  { "iframe",	TC_LINK },
#define TAG_IMG		10
  { "img",	TC_LINK },
#define TAG_INPUT	11
  { "input",	TC_LINK },
#define TAG_LAYER	12
  { "layer",	TC_LINK },
#define TAG_LINK	13
  { "link",	TC_SPEC },
#define TAG_META	14
  { "meta",	TC_SPEC },
#define TAG_OVERLAY	15
  { "overlay",	TC_LINK },
#define TAG_SCRIPT	16
  { "script",	TC_LINK },
#define TAG_TABLE	17
  { "table",	TC_LINK },
#define TAG_TD		18
  { "td",	TC_LINK },
#define TAG_TH		19
  { "th",	TC_LINK }
};

/* Flags for specific url-attr pairs handled through TC_LINK: */
#define AF_EXTERNAL 1

/* For tags handled by TC_LINK: attributes that contain URLs to
   download. */
static struct {
  int tagid;
  const char *attr_name;
  int flags;
} url_tag_attr_map[] = {
  { TAG_A,		"href",		AF_EXTERNAL },
  { TAG_APPLET,		"code",		0 },
  { TAG_AREA,		"href",		AF_EXTERNAL },
  { TAG_BGSOUND,	"src",		0 },
  { TAG_BODY,		"background",	0 },
  { TAG_EMBED,		"src",		0 },
  { TAG_FIG,		"src",		0 },
  { TAG_FRAME,		"src",		0 },
  { TAG_IFRAME,		"src",		0 },
  { TAG_IMG,		"href",		0 },
  { TAG_IMG,		"lowsrc",	0 },
  { TAG_IMG,		"src",		0 },
  { TAG_INPUT,		"src",		0 },
  { TAG_LAYER,		"src",		0 },
  { TAG_OVERLAY,	"src",		0 },
  { TAG_SCRIPT,		"src",		0 },
  { TAG_TABLE,		"background",	0 },
  { TAG_TD,		"background",	0 },
  { TAG_TH,		"background",	0 }
};

/* The lists of interesting tags and attributes are built dynamically,
   from the information above.  However, some places in the code refer
   to the attributes not mentioned here.  We add them manually.  */
static const char *additional_attributes[] = {
  "rel",			/* for TAG_LINK */
  "http-equiv",			/* for TAG_META */
  "name",			/* for TAG_META */
  "content"			/* for TAG_META */
};

static const char **interesting_tags;
static const char **interesting_attributes;

void
init_interesting (void)
{
  /* Init the variables interesting_tags and interesting_attributes
     that are used by the HTML parser to know which tags and
     attributes we're interested in.  We initialize this only once,
     for performance reasons.

     Here we also make sure that what we put in interesting_tags
     matches the user's preferences as specified through --ignore-tags
     and --follow-tags.  */

  {
    int i, ind = 0;
    int size = ARRAY_SIZE (known_tags);
    interesting_tags = (const char **)xmalloc ((size + 1) * sizeof (char *));

    for (i = 0; i < size; i++)
      {
	const char *name = known_tags[i].name;

	/* Normally here we could say:
	   interesting_tags[i] = name;
	   But we need to respect the settings of --ignore-tags and
	   --follow-tags, so the code gets a bit harier.  */

	if (opt.ignore_tags)
	  {
	    /* --ignore-tags was specified.  Do not match these
	       specific tags.  --ignore-tags takes precedence over
	       --follow-tags, so we process --ignore first and fall
	       through if there's no match. */
	    int j, lose = 0;
	    for (j = 0; opt.ignore_tags[j] != NULL; j++)
	      /* Loop through all the tags this user doesn't care
                 about. */
	      if (strcasecmp(opt.ignore_tags[j], name) == EQ)
		{
		  lose = 1;
		  break;
		}
	    if (lose)
	      continue;
	  }

	if (opt.follow_tags)
	  {
	    /* --follow-tags was specified.  Only match these specific
	       tags, so return FALSE if we don't match one of them. */
	    int j, win = 0;
	    for (j = 0; opt.follow_tags[j] != NULL; j++)
	      /* Loop through all the tags this user cares about. */
	      if (strcasecmp(opt.follow_tags[j], name) == EQ)
		{
		  win = 1;
		  break;
		}
	    if (!win)
	      continue;		/* wasn't one of the explicitly
                                   desired tags */
	  }

	/* If we get to here, --follow-tags isn't being used or the
	   tag is among the ones that are follwed, and --ignore-tags,
	   if specified, didn't include this tag, so it's an
	   "interesting" one. */
	interesting_tags[ind++] = name;
      }
    interesting_tags[ind] = NULL;
  }

  /* The same for attributes, except we loop through url_tag_attr_map.
     Here we also need to make sure that the list of attributes is
     unique, and to include the attributes from additional_attributes.  */
  {
    int i, ind;
    const char **att = xmalloc ((ARRAY_SIZE (additional_attributes) + 1)
				* sizeof (char *));
    /* First copy the "additional" attributes. */
    for (i = 0; i < ARRAY_SIZE (additional_attributes); i++)
      att[i] = additional_attributes[i];
    ind = i;
    att[ind] = NULL;
    for (i = 0; i < ARRAY_SIZE (url_tag_attr_map); i++)
      {
	int j, seen = 0;
	const char *look_for = url_tag_attr_map[i].attr_name;
	for (j = 0; j < ind - 1; j++)
	  if (!strcmp (att[j], look_for))
	    {
	      seen = 1;
	      break;
	    }
	if (!seen)
	  {
	    att = xrealloc (att, (ind + 2) * sizeof (*att));
	    att[ind++] = look_for;
	    att[ind] = NULL;
	  }
      }
    interesting_attributes = att;
  }
}

static int
find_tag (const char *tag_name)
{
  int i;

  /* This is linear search; if the number of tags grow, we can switch
     to binary search.  */

  for (i = 0; i < ARRAY_SIZE (known_tags); i++)
    {
      int cmp = strcasecmp (known_tags[i].name, tag_name);
      /* known_tags are sorted alphabetically, so we can
         micro-optimize.  */
      if (cmp > 0)
	break;
      else if (cmp == 0)
	return i;
    }
  return -1;
}

/* Find the value of attribute named NAME in the taginfo TAG.  If the
   attribute is not present, return NULL.  If ATTRID is non-NULL, the
   exact identity of the attribute will be returned.  */
static char *
find_attr (struct taginfo *tag, const char *name, int *attrid)
{
  int i;
  for (i = 0; i < tag->nattrs; i++)
    if (!strcasecmp (tag->attrs[i].name, name))
      {
	if (attrid)
	  *attrid = i;
	return tag->attrs[i].value;
      }
  return NULL;
}

struct collect_urls_closure {
  char *text;			/* HTML text. */
  char *base;			/* Base URI of the document, possibly
				   changed through <base href=...>. */
  urlpos *head, *tail;		/* List of URLs */
  const char *parent_base;	/* Base of the current document. */
  const char *document_file;	/* File name of this document. */
  int dash_p_leaf_HTML;		/* Whether -p is specified, and this
                                   document is the "leaf" node of the
                                   HTML tree. */
  int nofollow;			/* whether NOFOLLOW was specified in a
                                   <meta name=robots> tag. */
};

/* Resolve LINK_URI and append it to closure->tail.  TAG and ATTRID
   are the necessary context to store the position and size.  */

static void
handle_link (struct collect_urls_closure *closure, const char *link_uri,
	     struct taginfo *tag, int attrid)
{
  int no_proto = !has_proto (link_uri);
  urlpos *newel;

  const char *base = closure->base ? closure->base : closure->parent_base;
  char *complete_uri;

  char *fragment = strrchr (link_uri, '#');

  if (fragment)
    {
      /* Nullify the fragment identifier, i.e. everything after the
         last occurrence of `#', inclusive.  This copying is
         relatively inefficient, but it doesn't matter because
         fragment identifiers don't come up all that often.  */
      int hashlen = fragment - link_uri;
      char *p = alloca (hashlen + 1);
      memcpy (p, link_uri, hashlen);
      p[hashlen] = '\0';
      link_uri = p;
    }

  if (!base)
    {
      if (no_proto)
	{
	  /* We have no base, and the link does not have a protocol or
             a host attached to it.  Nothing we can do.  */
	  /* #### Should we print a warning here?  Wget 1.5.x used to.  */
	  return;
	}
      else
	complete_uri = xstrdup (link_uri);
    }
  else
    complete_uri = url_concat (base, link_uri);

  DEBUGP (("%s: merge(\"%s\", \"%s\") -> %s\n",
	   closure->document_file, base ? base : "(null)",
	   link_uri, complete_uri));

  newel = (urlpos *)xmalloc (sizeof (urlpos));

  memset (newel, 0, sizeof (*newel));
  newel->next = NULL;
  newel->url = complete_uri;
  newel->pos = tag->attrs[attrid].value_raw_beginning - closure->text;
  newel->size = tag->attrs[attrid].value_raw_size;

  /* A URL is relative if the host and protocol are not named, and the
     name does not start with `/'.
     #### This logic might need some rethinking.  */
  if (no_proto && *link_uri != '/')
    newel->flags |= (URELATIVE | UNOPROTO);
  else if (no_proto)
    newel->flags |= UNOPROTO;

  if (closure->tail)
    {
      closure->tail->next = newel;
      closure->tail = newel;
    }
  else
    closure->tail = closure->head = newel;
}

/* #### Document what this does.
   #### It would be nice to split this into several functions.  */

static void
collect_tags_mapper (struct taginfo *tag, void *arg)
{
  struct collect_urls_closure *closure = (struct collect_urls_closure *)arg;
  int tagid = find_tag (tag->name);
  assert (tagid != -1);

  switch (known_tags[tagid].category)
    {
    case TC_LINK:
      {
	int i;
	int size = ARRAY_SIZE (url_tag_attr_map);
	for (i = 0; i < size; i++)
	  if (url_tag_attr_map[i].tagid == tagid)
	    break;
	/* We've found the index of url_tag_attr_map where the
           attributes of our tags begin.  Now, look for every one of
           them, and handle it.  */
	for (; (i < size && url_tag_attr_map[i].tagid == tagid); i++)
	  {
	    char *attr_value;
	    int id;
	    if (closure->dash_p_leaf_HTML
		&& (url_tag_attr_map[i].flags & AF_EXTERNAL))
	      /* If we're at a -p leaf node, we don't want to retrieve
                 links to references we know are external, such as <a
                 href=...>.  */
	      continue;

	    /* This find_attr() buried in a loop may seem inefficient
               (O(n^2)), but it's not, since the number of attributes
               (n) we loop over is extremely small.  In the worst case
               of IMG with all its possible attributes, n^2 will be
               only 9.  */
	    attr_value = find_attr (tag, url_tag_attr_map[i].attr_name, &id);
	    if (attr_value)
	      handle_link (closure, attr_value, tag, id);
	  }
      }
      break;
    case TC_SPEC:
      switch (tagid)
	{
	case TAG_BASE:
	  {
	    char *newbase = find_attr (tag, "href", NULL);
	    if (!newbase)
	      break;
	    if (closure->base)
	      free (closure->base);
	    if (closure->parent_base)
	      closure->base = url_concat (closure->parent_base, newbase);
	    else
	      closure->base = xstrdup (newbase);
	  }
	  break;
	case TAG_LINK:
	  {
	    int id;
	    char *rel  = find_attr (tag, "rel", NULL);
	    char *href = find_attr (tag, "href", &id);
	    if (href)
	      {
		/* In the normal case, all <link href=...> tags are
		   fair game.

		   In the special case of when -p is active, however,
		   and we're at a leaf node (relative to the -l
		   max. depth) in the HTML document tree, the only
		   <LINK> tag we'll follow is a <LINK REL=
		   "stylesheet">, as it's necessary for displaying
		   this document properly.  We won't follow other
		   <LINK> tags, like <LINK REL="home">, for instance,
		   as they refer to external documents.  */
		if (!closure->dash_p_leaf_HTML
		    || (rel && !strcasecmp (rel, "stylesheet")))
		  handle_link (closure, href, tag, id);
	      }
	  }
	  break;
	case TAG_META:
	  /* Some pages use a META tag to specify that the page be
	     refreshed by a new page after a given number of seconds.
	     The general format for this is:

	     <meta http-equiv=Refresh content="NUMBER; URL=index2.html">

	     So we just need to skip past the "NUMBER; URL=" garbage
	     to get to the URL.  */
	  {
	    int id;
	    char *name = find_attr (tag, "name", NULL);
	    char *http_equiv = find_attr (tag, "http-equiv", &id);
	    if (http_equiv && !strcasecmp (http_equiv, "refresh"))
	      {
		char *refresh = find_attr (tag, "content", NULL);
		char *p = refresh;
		int offset;
		while (ISDIGIT (*p))
		  ++p;
		if (*p++ != ';')
		  return;
		while (ISSPACE (*p))
		  ++p;
		if (!(TOUPPER (*p) == 'U'
		      && TOUPPER (*(p + 1)) == 'R'
		      && TOUPPER (*(p + 2)) == 'L'
		      && *(p + 3) == '='))
		  return;
		p += 4;
		while (ISSPACE (*p))
		  ++p;
		offset = p - refresh;
		tag->attrs[id].value_raw_beginning += offset;
		tag->attrs[id].value_raw_size -= offset;
		handle_link (closure, p, tag, id);
	      }
	    else if (name && !strcasecmp (name, "robots"))
	      {
		/* Handle stuff like:
		   <meta name="robots" content="index,nofollow"> */
		char *content = find_attr (tag, "content", NULL);
		if (!content)
		  return;
		if (!strcasecmp (content, "none"))
		  closure->nofollow = 1;
		else
		  {
		    while (*content)
		      {
			/* Find the next occurrence of ',' or the end of
			   the string.  */
			char *end = strchr (content, ',');
			if (end)
			  ++end;
			else
			  end = content + strlen (content);
			if (!strncasecmp (content, "nofollow", end - content))
			  closure->nofollow = 1;
			content = end;
		      }
		  }
	      }
	  }
	  break;
	default:
	  /* Category is TC_SPEC, but tag name is unhandled.  This
             must not be.  */
	  abort ();
	}
      break;
    }
}

/* Scan FILE, retrieving links to HTML documents from it.  Each link is 

  Similar to get_urls_file, but for HTML files.  FILE is scanned as
   an HTML document.  get_urls_html() constructs the URLs from the
   relative href-s.

   If SILENT is non-zero, do not barf on baseless relative links.  */
urlpos *
get_urls_html (const char *file, const char *this_url, int dash_p_leaf_HTML,
	       int *meta_disallow_follow)
{
  struct file_memory *fm;
  struct collect_urls_closure closure;

  /* Load the file. */
  fm = read_file (file);
  if (!fm)
    {
      logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
      return NULL;
    }
  DEBUGP (("Loaded %s (size %ld).\n", file, fm->length));

  closure.text = fm->content;
  closure.head = closure.tail = NULL;
  closure.base = NULL;
  closure.parent_base = this_url ? this_url : opt.base_href;
  closure.document_file = file;
  closure.dash_p_leaf_HTML = dash_p_leaf_HTML;
  closure.nofollow = 0;

  if (!interesting_tags)
    init_interesting ();

  map_html_tags (fm->content, fm->length, interesting_tags,
		 interesting_attributes, collect_tags_mapper, &closure);

  DEBUGP (("no-follow in %s: %d\n", file, closure.nofollow));
  if (meta_disallow_follow)
    *meta_disallow_follow = closure.nofollow;

  FREE_MAYBE (closure.base);
  read_file_free (fm);
  return closure.head;
}
