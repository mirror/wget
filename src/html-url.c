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

struct map_context;

typedef void (*tag_handler_t) PARAMS ((int, struct taginfo *,
				       struct map_context *));

#define DECLARE_TAG_HANDLER(fun)					\
  static void fun PARAMS ((int, struct taginfo *, struct map_context *))

DECLARE_TAG_HANDLER (tag_find_urls);
DECLARE_TAG_HANDLER (tag_handle_base);
DECLARE_TAG_HANDLER (tag_handle_link);
DECLARE_TAG_HANDLER (tag_handle_meta);

/* The list of known tags and functions used for handling them.  Most
   tags are simply harvested for URLs. */
static struct {
  const char *name;
  tag_handler_t handler;
} known_tags[] = {
#define TAG_A		0
  { "a",	tag_find_urls },
#define TAG_APPLET	1
  { "applet",	tag_find_urls },
#define TAG_AREA	2
  { "area",	tag_find_urls },
#define TAG_BASE	3
  { "base",	tag_handle_base },
#define TAG_BGSOUND	4
  { "bgsound",	tag_find_urls },
#define TAG_BODY	5
  { "body",	tag_find_urls },
#define TAG_EMBED	6
  { "embed",	tag_find_urls },
#define TAG_FIG		7
  { "fig",	tag_find_urls },
#define TAG_FRAME	8
  { "frame",	tag_find_urls },
#define TAG_IFRAME	9
  { "iframe",	tag_find_urls },
#define TAG_IMG		10
  { "img",	tag_find_urls },
#define TAG_INPUT	11
  { "input",	tag_find_urls },
#define TAG_LAYER	12
  { "layer",	tag_find_urls },
#define TAG_LINK	13
  { "link",	tag_handle_link },
#define TAG_META	14
  { "meta",	tag_handle_meta },
#define TAG_OVERLAY	15
  { "overlay",	tag_find_urls },
#define TAG_SCRIPT	16
  { "script",	tag_find_urls },
#define TAG_TABLE	17
  { "table",	tag_find_urls },
#define TAG_TD		18
  { "td",	tag_find_urls },
#define TAG_TH		19
  { "th",	tag_find_urls }
};

/* tag_url_attributes documents which attributes of which tags contain
   URLs to harvest.  It is used by tag_find_urls.  */

/* Defines for the FLAGS field; currently only one flag is defined. */

/* This tag points to an external document not necessary for rendering this 
   document (i.e. it's not an inlined image, stylesheet, etc.). */
#define TUA_EXTERNAL 1

/* For tags handled by tag_find_urls: attributes that contain URLs to
   download. */
static struct {
  int tagid;
  const char *attr_name;
  int flags;
} tag_url_attributes[] = {
  { TAG_A,		"href",		TUA_EXTERNAL },
  { TAG_APPLET,		"code",		0 },
  { TAG_AREA,		"href",		TUA_EXTERNAL },
  { TAG_BGSOUND,	"src",		0 },
  { TAG_BODY,		"background",	0 },
  { TAG_EMBED,		"href",		0 },
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
     and --follow-tags.

     This function is as large as this only because of the glorious
     expressivity of the C programming language.  */

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

  /* The same for attributes, except we loop through tag_url_attributes.
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
    for (i = 0; i < ARRAY_SIZE (tag_url_attributes); i++)
      {
	int j, seen = 0;
	const char *look_for = tag_url_attributes[i].attr_name;
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
   attribute is not present, return NULL.  If ATTRIND is non-NULL, the
   index of the attribute in TAG will be stored there.  */
static char *
find_attr (struct taginfo *tag, const char *name, int *attrind)
{
  int i;
  for (i = 0; i < tag->nattrs; i++)
    if (!strcasecmp (tag->attrs[i].name, name))
      {
	if (attrind)
	  *attrind = i;
	return tag->attrs[i].value;
      }
  return NULL;
}

struct map_context {
  char *text;			/* HTML text. */
  char *base;			/* Base URI of the document, possibly
				   changed through <base href=...>. */
  const char *parent_base;	/* Base of the current document. */
  const char *document_file;	/* File name of this document. */
  int nofollow;			/* whether NOFOLLOW was specified in a
                                   <meta name=robots> tag. */

  struct urlpos *head, *tail;	/* List of URLs that is being
				   built. */
};

/* Append LINK_URI to the urlpos structure that is being built.

   LINK_URI will be merged with the current document base.  TAG and
   ATTRIND are the necessary context to store the position and
   size.  */

static struct urlpos *
append_one_url (const char *link_uri, int inlinep,
		struct taginfo *tag, int attrind, struct map_context *ctx)
{
  int link_has_scheme = url_has_scheme (link_uri);
  struct urlpos *newel;
  const char *base = ctx->base ? ctx->base : ctx->parent_base;
  struct url *url;

  if (!base)
    {
      DEBUGP (("%s: no base, merge will use \"%s\".\n",
	       ctx->document_file, link_uri));

      if (!link_has_scheme)
	{
	  /* Base URL is unavailable, and the link does not have a
	     location attached to it -- we have to give up.  Since
	     this can only happen when using `--force-html -i', print
	     a warning.  */
	  logprintf (LOG_NOTQUIET,
		     _("%s: Cannot resolve relative link %s.\n"),
		     ctx->document_file, link_uri);
	  return NULL;
	}

      url = url_parse (link_uri, NULL);
      if (!url)
	{
	  DEBUGP (("%s: link \"%s\" doesn't parse.\n",
		   ctx->document_file, link_uri));
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
	       ctx->document_file, base, link_uri, complete_uri));

      url = url_parse (complete_uri, NULL);
      if (!url)
	{
	  DEBUGP (("%s: merged link \"%s\" doesn't parse.\n",
		   ctx->document_file, complete_uri));
	  xfree (complete_uri);
	  return NULL;
	}
      xfree (complete_uri);
    }

  DEBUGP (("appending \"%s\" to urlpos.\n", url->url));

  newel = (struct urlpos *)xmalloc (sizeof (struct urlpos));
  memset (newel, 0, sizeof (*newel));

  newel->next = NULL;
  newel->url = url;
  newel->pos = tag->attrs[attrind].value_raw_beginning - ctx->text;
  newel->size = tag->attrs[attrind].value_raw_size;
  newel->link_inline_p = inlinep;

  /* A URL is relative if the host is not named, and the name does not
     start with `/'.  */
  if (!link_has_scheme && *link_uri != '/')
    newel->link_relative_p = 1;
  else if (link_has_scheme)
    newel->link_complete_p = 1;

  if (ctx->tail)
    {
      ctx->tail->next = newel;
      ctx->tail = newel;
    }
  else
    ctx->tail = ctx->head = newel;

  return newel;
}

/* All the tag_* functions are called from collect_tags_mapper, as
   specified by KNOWN_TAGS.  */

/* Default tag handler: collect URLs from attributes specified for
   this tag by tag_url_attributes.  */

static void
tag_find_urls (int tagid, struct taginfo *tag, struct map_context *ctx)
{
  int i, attrind, first = -1;
  int size = ARRAY_SIZE (tag_url_attributes);

  for (i = 0; i < size; i++)
    if (tag_url_attributes[i].tagid == tagid)
      {
	/* We've found the index of tag_url_attributes where the
	   attributes of our tag begin.  */
	first = i;
	break;
      }
  assert (first != -1);

  /* Loop over the "interesting" attributes of this tag.  In this
     example, it will loop over "src" and "lowsrc".

       <img src="foo.png" lowsrc="bar.png">

     This has to be done in the outer loop so that the attributes are
     processed in the same order in which they appear in the page.
     This is required when converting links.  */

  for (attrind = 0; attrind < tag->nattrs; attrind++)
    {
      /* Find whether TAG/ATTRIND is a combination that contains a
	 URL. */
      char *link = tag->attrs[attrind].value;

      /* If you're cringing at the inefficiency of the nested loops,
	 remember that they both iterate over a laughably small
	 quantity of items.  The worst-case inner loop is for the IMG
	 tag, which has three attributes.  */
      for (i = first; i < size && tag_url_attributes[i].tagid == tagid; i++)
	{
	  if (0 == strcasecmp (tag->attrs[attrind].name,
			       tag_url_attributes[i].attr_name))
	    {
	      int flags = tag_url_attributes[i].flags;
	      append_one_url (link, !(flags & TUA_EXTERNAL), tag, attrind, ctx);
	    }
	}
    }
}

/* Handle the BASE tag, for <base href=...>. */

static void
tag_handle_base (int tagid, struct taginfo *tag, struct map_context *ctx)
{
  struct urlpos *base_urlpos;
  int attrind;
  char *newbase = find_attr (tag, "href", &attrind);
  if (!newbase)
    return;

  base_urlpos = append_one_url (newbase, 0, tag, attrind, ctx);
  if (!base_urlpos)
    return;
  base_urlpos->ignore_when_downloading = 1;
  base_urlpos->link_base_p = 1;

  if (ctx->base)
    xfree (ctx->base);
  if (ctx->parent_base)
    ctx->base = uri_merge (ctx->parent_base, newbase);
  else
    ctx->base = xstrdup (newbase);
}

/* Handle the LINK tag.  It requires special handling because how its
   links will be followed in -p mode depends on the REL attribute.  */

static void
tag_handle_link (int tagid, struct taginfo *tag, struct map_context *ctx)
{
  int attrind;
  char *href = find_attr (tag, "href", &attrind);

  /* All <link href="..."> link references are external,
     except for <link rel="stylesheet" href="...">.  */
  if (href)
    {
      char *rel  = find_attr (tag, "rel", NULL);
      int inlinep = (rel && 0 == strcasecmp (rel, "stylesheet"));
      append_one_url (href, inlinep, tag, attrind, ctx);
    }
}

/* Handle the META tag.  This requires special handling because of the
   refresh feature and because of robot exclusion.  */

static void
tag_handle_meta (int tagid, struct taginfo *tag, struct map_context *ctx)
{
  char *name = find_attr (tag, "name", NULL);
  char *http_equiv = find_attr (tag, "http-equiv", NULL);

  if (http_equiv && 0 == strcasecmp (http_equiv, "refresh"))
    {
      /* Some pages use a META tag to specify that the page be
	 refreshed by a new page after a given number of seconds.  The
	 general format for this is:

	   <meta http-equiv=Refresh content="NUMBER; URL=index2.html">

	 So we just need to skip past the "NUMBER; URL=" garbage to
	 get to the URL.  */

      struct urlpos *entry;

      int attrind;
      char *p, *refresh = find_attr (tag, "content", &attrind);
      int timeout = 0;

      for (p = refresh; ISDIGIT (*p); p++)
	timeout = 10 * timeout + *p - '0';
      if (*p++ != ';')
	return;

      while (ISSPACE (*p))
	++p;
      if (!(   TOUPPER (*p)       == 'U'
	    && TOUPPER (*(p + 1)) == 'R'
	    && TOUPPER (*(p + 2)) == 'L'
	    &&          *(p + 3)  == '='))
	return;
      p += 4;
      while (ISSPACE (*p))
	++p;

      entry = append_one_url (p, 0, tag, attrind, ctx);
      if (entry)
	{
	  entry->link_refresh_p = 1;
	  entry->refresh_timeout = timeout;
	}
    }
  else if (name && 0 == strcasecmp (name, "robots"))
    {
      /* Handle stuff like:
	 <meta name="robots" content="index,nofollow"> */
      char *content = find_attr (tag, "content", NULL);
      if (!content)
	return;
      if (!strcasecmp (content, "none"))
	ctx->nofollow = 1;
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
		ctx->nofollow = 1;
	      content = end;
	    }
	}
    }
}

/* Examine name and attributes of TAG and take appropriate action
   according to the tag.  */

static void
collect_tags_mapper (struct taginfo *tag, void *arg)
{
  struct map_context *ctx = (struct map_context *)arg;
  int tagid;
  tag_handler_t handler;

  tagid = find_tag (tag->name);
  assert (tagid != -1);
  handler = known_tags[tagid].handler;

  handler (tagid, tag, ctx);
}

/* Analyze HTML tags FILE and construct a list of URLs referenced from
   it.  It merges relative links in FILE with URL.  It is aware of
   <base href=...> and does the right thing.  */
struct urlpos *
get_urls_html (const char *file, const char *url, int *meta_disallow_follow)
{
  struct file_memory *fm;
  struct map_context ctx;

  /* Load the file. */
  fm = read_file (file);
  if (!fm)
    {
      logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
      return NULL;
    }
  DEBUGP (("Loaded %s (size %ld).\n", file, fm->length));

  ctx.text = fm->content;
  ctx.head = ctx.tail = NULL;
  ctx.base = NULL;
  ctx.parent_base = url ? url : opt.base_href;
  ctx.document_file = file;
  ctx.nofollow = 0;

  if (!interesting_tags)
    init_interesting ();

  map_html_tags (fm->content, fm->length, interesting_tags,
		 interesting_attributes, collect_tags_mapper, &ctx);

  DEBUGP (("no-follow in %s: %d\n", file, ctx.nofollow));
  if (meta_disallow_follow)
    *meta_disallow_follow = ctx.nofollow;

  FREE_MAYBE (ctx.base);
  read_file_free (fm);
  return ctx.head;
}

void
cleanup_html_url (void)
{
  FREE_MAYBE (interesting_tags);
  FREE_MAYBE (interesting_attributes);
}
