/* Collect URLs from HTML source.
   Copyright (C) 1998, 2000, 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <stdlib.h>
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

/* This tag points to an external document not necessary for rendering this 
   document (i.e. it's not an inlined image, stylesheet, etc.). */
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

static void
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
	   --follow-tags, so the code gets a bit hairier.  */

	if (opt.ignore_tags)
	  {
	    /* --ignore-tags was specified.  Do not match these
	       specific tags.  --ignore-tags takes precedence over
	       --follow-tags, so we process --ignore first and fall
	       through if there's no match. */
	    int j, lose = 0;
	    for (j = 0; opt.ignore_tags[j] != NULL; j++)
	      /* Loop through all the tags this user doesn't care about. */
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
	    /* --follow-tags was specified.  Only match these specific tags, so
	       continue back to top of for if we don't match one of them. */
	    int j, win = 0;
	    for (j = 0; opt.follow_tags[j] != NULL; j++)
	      /* Loop through all the tags this user cares about. */
	      if (strcasecmp(opt.follow_tags[j], name) == EQ)
		{
		  win = 1;
		  break;
		}
	    if (!win)
	      continue;  /* wasn't one of the explicitly desired tags */
	  }

	/* If we get to here, --follow-tags isn't being used or the
	   tag is among the ones that are followed, and --ignore-tags,
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
  struct urlpos *head, *tail;	/* List of URLs */
  const char *parent_base;	/* Base of the current document. */
  const char *document_file;	/* File name of this document. */
  int nofollow;			/* whether NOFOLLOW was specified in a
                                   <meta name=robots> tag. */
};

/* Resolve LINK_URI and append it to closure->tail.  TAG and ATTRID
   are the necessary context to store the position and size.  */

static struct urlpos *
handle_link (struct collect_urls_closure *closure, const char *link_uri,
	     struct taginfo *tag, int attrid)
{
  int link_has_scheme = url_has_scheme (link_uri);
  struct urlpos *newel;
  const char *base = closure->base ? closure->base : closure->parent_base;
  struct url *url;

  if (!base)
    {
      DEBUGP (("%s: no base, merge will use \"%s\".\n",
	       closure->document_file, link_uri));

      if (!link_has_scheme)
	{
	  /* We have no base, and the link does not have a host
	     attached to it.  Nothing we can do.  */
	  /* #### Should we print a warning here?  Wget 1.5.x used to.  */
	  return NULL;
	}

      url = url_parse (link_uri, NULL);
      if (!url)
	{
	  DEBUGP (("%s: link \"%s\" doesn't parse.\n",
		   closure->document_file, link_uri));
	  return NULL;
	}
    }
  else
    {
      /* Merge BASE with LINK_URI, but also make sure the result is
	 canonicalized, i.e. that "../" have been resolved.
	 (parse_url will do that for us.) */

      char *complete_uri = uri_merge (base, link_uri);

      DEBUGP (("%s: merge(\"%s\", \"%s\") -> %s\n",
	       closure->document_file, base, link_uri, complete_uri));

      url = url_parse (complete_uri, NULL);
      if (!url)
	{
	  DEBUGP (("%s: merged link \"%s\" doesn't parse.\n",
		   closure->document_file, complete_uri));
	  xfree (complete_uri);
	  return NULL;
	}
      xfree (complete_uri);
    }

  newel = (struct urlpos *)xmalloc (sizeof (struct urlpos));

  memset (newel, 0, sizeof (*newel));
  newel->next = NULL;
  newel->url = url;
  newel->pos = tag->attrs[attrid].value_raw_beginning - closure->text;
  newel->size = tag->attrs[attrid].value_raw_size;

  /* A URL is relative if the host is not named, and the name does not
     start with `/'.  */
  if (!link_has_scheme && *link_uri != '/')
    newel->link_relative_p = 1;
  else if (link_has_scheme)
    newel->link_complete_p = 1;

  if (closure->tail)
    {
      closure->tail->next = newel;
      closure->tail = newel;
    }
  else
    closure->tail = closure->head = newel;

  return newel;
}

/* Examine name and attributes of TAG and take appropriate action.
   What will be done depends on TAG's category and attribute values.
   Tags of TC_LINK category have attributes that contain links to
   follow; tags of TC_SPEC category need to be handled specially.

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
	int i, id, first;
	int size = ARRAY_SIZE (url_tag_attr_map);
	for (i = 0; i < size; i++)
	  if (url_tag_attr_map[i].tagid == tagid)
	    break;
	/* We've found the index of url_tag_attr_map where the
           attributes of our tags begin.  Now, look for every one of
           them, and handle it.  */
	/* Need to process the attributes in the order they appear in
	   the tag, as this is required if we convert links.  */
	first = i;
	for (id = 0; id < tag->nattrs; id++)
	  {
	    /* This nested loop may seem inefficient (O(n^2)), but it's
	       not, since the number of attributes (n) we loop over is
	       extremely small.  In the worst case of IMG with all its
	       possible attributes, n^2 will be only 9.  */
	    for (i = first; (i < size && url_tag_attr_map[i].tagid == tagid);
		 i++)
	      {
		if (0 == strcasecmp (tag->attrs[id].name,
				     url_tag_attr_map[i].attr_name))
		  {
		    char *attr_value = tag->attrs[id].value;
		    if (attr_value)
		      {
			struct urlpos *entry;
			entry = handle_link (closure, attr_value, tag, id);
			if (entry != NULL
			    && !(url_tag_attr_map[i].flags & AF_EXTERNAL))
			  entry->link_inline_p = 1;
		      }
		  }
	      }
	  }
      }
      break;
    case TC_SPEC:
      switch (tagid)
	{
	case TAG_BASE:
	  {
	    struct urlpos *base_urlpos;
	    int id;
	    char *newbase = find_attr (tag, "href", &id);
	    if (!newbase)
	      break;

	    base_urlpos = handle_link (closure, newbase, tag, id);
	    if (!base_urlpos)
	      break;
	    base_urlpos->ignore_when_downloading = 1;
	    base_urlpos->link_base_p = 1;

	    if (closure->base)
	      xfree (closure->base);
	    if (closure->parent_base)
	      closure->base = uri_merge (closure->parent_base, newbase);
	    else
	      closure->base = xstrdup (newbase);
	  }
	  break;
	case TAG_LINK:
	  {
	    int id;
	    char *href = find_attr (tag, "href", &id);

	    /* All <link href="..."> link references are external,
	       except for <link rel="stylesheet" href="...">.  */
	    if (href)
	      {
		struct urlpos *entry;
		entry = handle_link (closure, href, tag, id);
		if (entry != NULL)
		  {
		    char *rel  = find_attr (tag, "rel", NULL);
		    if (rel && 0 == strcasecmp (rel, "stylesheet"))
		      entry->link_inline_p = 1;
		  }
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
	    char *name = find_attr (tag, "name", NULL);
	    char *http_equiv = find_attr (tag, "http-equiv", NULL);
	    if (http_equiv && !strcasecmp (http_equiv, "refresh"))
	      {
		struct urlpos *entry;

		int id;
		char *p, *refresh = find_attr (tag, "content", &id);
		int timeout = 0;

		for (p = refresh; ISDIGIT (*p); p++)
		  timeout = 10 * timeout + *p - '0';
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

		entry = handle_link (closure, p, tag, id);
		if (entry)
		  {
		    entry->link_refresh_p = 1;
		    entry->refresh_timeout = timeout;
		  }
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

/* Analyze HTML tags FILE and construct a list of URLs referenced from
   it.  It merges relative links in FILE with URL.  It is aware of
   <base href=...> and does the right thing.  */
struct urlpos *
get_urls_html (const char *file, const char *url, int *meta_disallow_follow)
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
  closure.parent_base = url ? url : opt.base_href;
  closure.document_file = file;
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

void
cleanup_html_url (void)
{
  FREE_MAYBE (interesting_tags);
  FREE_MAYBE (interesting_attributes);
}
