/* Handling of recursive HTTP retrieving.
   Copyright (C) 1995, 1996, 1997, 2000, 2001 Free Software Foundation, Inc.

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
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <errno.h>
#include <assert.h>
#include <sys/types.h>

#include "wget.h"
#include "url.h"
#include "recur.h"
#include "utils.h"
#include "retr.h"
#include "ftp.h"
#include "fnmatch.h"
#include "host.h"
#include "hash.h"
#include "res.h"

#ifndef errno
extern int errno;
#endif

extern char *version_string;

static struct hash_table *dl_file_url_map;
static struct hash_table *dl_url_file_map;

/* List of HTML files downloaded in this Wget run.  Used for link
   conversion after Wget is done.  This list should only be traversed
   in order.  If you need to check whether a file has been downloaded,
   use a hash table, e.g. dl_file_url_map.  */
static slist *downloaded_html_files;

static void register_delete_file PARAMS ((const char *));

/* Functions for maintaining the URL queue.  */

struct queue_element {
  const char *url;
  const char *referer;
  int depth;
  struct queue_element *next;
};

struct url_queue {
  struct queue_element *head;
  struct queue_element *tail;
  int count, maxcount;
};

/* Create a URL queue. */

static struct url_queue *
url_queue_new (void)
{
  struct url_queue *queue = xmalloc (sizeof (*queue));
  memset (queue, '\0', sizeof (*queue));
  return queue;
}

/* Delete a URL queue. */

static void
url_queue_delete (struct url_queue *queue)
{
  xfree (queue);
}

/* Enqueue a URL in the queue.  The queue is FIFO: the items will be
   retrieved ("dequeued") from the queue in the order they were placed
   into it.  */

static void
url_enqueue (struct url_queue *queue,
	     const char *url, const char *referer, int depth)
{
  struct queue_element *qel = xmalloc (sizeof (*qel));
  qel->url = url;
  qel->referer = referer;
  qel->depth = depth;
  qel->next = NULL;

  ++queue->count;
  if (queue->count > queue->maxcount)
    queue->maxcount = queue->count;

  DEBUGP (("Enqueuing %s at depth %d\n", url, depth));
  DEBUGP (("Queue count %d, maxcount %d.\n", queue->count, queue->maxcount));

  if (queue->tail)
    queue->tail->next = qel;
  queue->tail = qel;

  if (!queue->head)
    queue->head = queue->tail;
}

/* Take a URL out of the queue.  Return 1 if this operation succeeded,
   or 0 if the queue is empty.  */

static int
url_dequeue (struct url_queue *queue,
	     const char **url, const char **referer, int *depth)
{
  struct queue_element *qel = queue->head;

  if (!qel)
    return 0;

  queue->head = queue->head->next;
  if (!queue->head)
    queue->tail = NULL;

  *url = qel->url;
  *referer = qel->referer;
  *depth = qel->depth;

  --queue->count;

  DEBUGP (("Dequeuing %s at depth %d\n", qel->url, qel->depth));
  DEBUGP (("Queue count %d, maxcount %d.\n", queue->count, queue->maxcount));

  xfree (qel);
  return 1;
}

static int download_child_p PARAMS ((const struct urlpos *, struct url *, int,
				     struct url *, struct hash_table *));
static int descend_redirect_p PARAMS ((const char *, const char *, int,
				       struct url *, struct hash_table *));


/* Retrieve a part of the web beginning with START_URL.  This used to
   be called "recursive retrieval", because the old function was
   recursive and implemented depth-first search.  retrieve_tree on the
   other hand implements breadth-search traversal of the tree, which
   results in much nicer ordering of downloads.

   The algorithm this function uses is simple:

   1. put START_URL in the queue.
   2. while there are URLs in the queue:

     3. get next URL from the queue.
     4. download it.
     5. if the URL is HTML and its depth does not exceed maximum depth,
        get the list of URLs embedded therein.
     6. for each of those URLs do the following:

       7. if the URL is not one of those downloaded before, and if it
          satisfies the criteria specified by the various command-line
	  options, add it to the queue. */

uerr_t
retrieve_tree (const char *start_url)
{
  uerr_t status = RETROK;

  /* The queue of URLs we need to load. */
  struct url_queue *queue = url_queue_new ();

  /* The URLs we do not wish to enqueue, because they are already in
     the queue, but haven't been downloaded yet.  */
  struct hash_table *blacklist = make_string_hash_table (0);

  /* We'll need various components of this, so better get it over with
     now. */
  struct url *start_url_parsed = url_parse (start_url, NULL);

  url_enqueue (queue, xstrdup (start_url), NULL, 0);
  string_set_add (blacklist, start_url);

  while (1)
    {
      int descend = 0;
      char *url, *referer, *file = NULL;
      int depth;
      boolean dash_p_leaf_HTML = FALSE;

      if (downloaded_exceeds_quota ())
	break;
      if (status == FWRITEERR)
	break;

      /* Get the next URL from the queue... */

      if (!url_dequeue (queue,
			(const char **)&url, (const char **)&referer,
			&depth))
	break;

      /* ...and download it.  Note that this download is in most cases
	 unconditional, as download_child_p already makes sure a file
	 doesn't get enqueued twice -- and yet this check is here, and
	 not in download_child_p.  This is so that if you run `wget -r
	 URL1 URL2', and a random URL is encountered once under URL1
	 and again under URL2, but at a different (possibly smaller)
	 depth, we want the URL's children to be taken into account
	 the second time.  */
      if (dl_url_file_map && hash_table_contains (dl_url_file_map, url))
	{
	  DEBUGP (("Already downloaded \"%s\", reusing it from \"%s\".\n",
		   url, (char *)hash_table_get (dl_url_file_map, url)));
	}
      else
	{
	  int dt = 0;
	  char *redirected = NULL;
	  int oldrec = opt.recursive;

	  opt.recursive = 0;
	  status = retrieve_url (url, &file, &redirected, NULL, &dt);
	  opt.recursive = oldrec;

	  if (file && status == RETROK
	      && (dt & RETROKF) && (dt & TEXTHTML))
	    descend = 1;

	  if (redirected)
	    {
	      /* We have been redirected, possibly to another host, or
		 different path, or wherever.  Check whether we really
		 want to follow it.  */
	      if (descend)
		{
		  if (!descend_redirect_p (redirected, url, depth,
					   start_url_parsed, blacklist))
		    descend = 0;
		  else
		    /* Make sure that the old pre-redirect form gets
		       blacklisted. */
		    string_set_add (blacklist, url);
		}

	      xfree (url);
	      url = redirected;
	    }
	}

      if (descend
	  && depth >= opt.reclevel && opt.reclevel != INFINITE_RECURSION)
	{
	  if (opt.page_requisites
	      && (depth == opt.reclevel || depth == opt.reclevel + 1))
	    {
	      /* When -p is specified, we are allowed to exceed the
		 maximum depth, but only for the "inline" links,
		 i.e. those that are needed to display the page.
		 Originally this could exceed the depth at most by
		 one, but we allow one more level so that the leaf
		 pages that contain frames can be loaded
		 correctly.  */
	      dash_p_leaf_HTML = TRUE;
	    }
	  else
	    {
	      /* Either -p wasn't specified or it was and we've
		 already spent the two extra (pseudo-)levels that it
		 affords us, so we need to bail out. */
	      DEBUGP (("Not descending further; at depth %d, max. %d.\n",
		       depth, opt.reclevel));
	      descend = 0;
	    }
	}

      /* If the downloaded document was HTML, parse it and enqueue the
	 links it contains. */

      if (descend)
	{
	  int meta_disallow_follow = 0;
	  struct urlpos *children
	    = get_urls_html (file, url, &meta_disallow_follow);

	  if (opt.use_robots && meta_disallow_follow)
	    {
	      free_urlpos (children);
	      children = NULL;
	    }

	  if (children)
	    {
	      struct urlpos *child = children;
	      struct url *url_parsed = url_parsed = url_parse (url, NULL);
	      assert (url_parsed != NULL);

	      for (; child; child = child->next)
		{
		  if (child->ignore_when_downloading)
		    continue;
		  if (dash_p_leaf_HTML && !child->link_inline_p)
		    continue;
		  if (download_child_p (child, url_parsed, depth, start_url_parsed,
					blacklist))
		    {
		      url_enqueue (queue, xstrdup (child->url->url),
				   xstrdup (url), depth + 1);
		      /* We blacklist the URL we have enqueued, because we
			 don't want to enqueue (and hence download) the
			 same URL twice.  */
		      string_set_add (blacklist, child->url->url);
		    }
		}

	      url_free (url_parsed);
	      free_urlpos (children);
	    }
	}

      if (opt.delete_after || (file && !acceptable (file)))
	{
	  /* Either --delete-after was specified, or we loaded this
	     otherwise rejected (e.g. by -R) HTML file just so we
	     could harvest its hyperlinks -- in either case, delete
	     the local file. */
	  DEBUGP (("Removing file due to %s in recursive_retrieve():\n",
		   opt.delete_after ? "--delete-after" :
		   "recursive rejection criteria"));
	  logprintf (LOG_VERBOSE,
		     (opt.delete_after
		      ? _("Removing %s.\n")
		      : _("Removing %s since it should be rejected.\n")),
		     file);
	  if (unlink (file))
	    logprintf (LOG_NOTQUIET, "unlink: %s\n", strerror (errno));
	  register_delete_file (file);
	}

      xfree (url);
      FREE_MAYBE (referer);
      FREE_MAYBE (file);
    }

  /* If anything is left of the queue due to a premature exit, free it
     now.  */
  {
    char *d1, *d2;
    int d3;
    while (url_dequeue (queue, (const char **)&d1, (const char **)&d2, &d3))
      {
	xfree (d1);
	FREE_MAYBE (d2);
      }
  }
  url_queue_delete (queue);

  if (start_url_parsed)
    url_free (start_url_parsed);
  string_set_free (blacklist);

  if (downloaded_exceeds_quota ())
    return QUOTEXC;
  else if (status == FWRITEERR)
    return FWRITEERR;
  else
    return RETROK;
}

/* Based on the context provided by retrieve_tree, decide whether a
   URL is to be descended to.  This is only ever called from
   retrieve_tree, but is in a separate function for clarity.

   The most expensive checks (such as those for robots) are memoized
   by storing these URLs to BLACKLIST.  This may or may not help.  It
   will help if those URLs are encountered many times.  */

static int
download_child_p (const struct urlpos *upos, struct url *parent, int depth,
		  struct url *start_url_parsed, struct hash_table *blacklist)
{
  struct url *u = upos->url;
  const char *url = u->url;

  DEBUGP (("Deciding whether to enqueue \"%s\".\n", url));

  if (string_set_contains (blacklist, url))
    {
      DEBUGP (("Already on the black list.\n"));
      goto out;
    }

  /* Several things to check for:
     1. if scheme is not http, and we don't load it
     2. check for relative links (if relative_only is set)
     3. check for domain
     4. check for no-parent
     5. check for excludes && includes
     6. check for suffix
     7. check for same host (if spanhost is unset), with possible
     gethostbyname baggage
     8. check for robots.txt

     Addendum: If the URL is FTP, and it is to be loaded, only the
     domain and suffix settings are "stronger".

     Note that .html files will get loaded regardless of suffix rules
     (but that is remedied later with unlink) unless the depth equals
     the maximum depth.

     More time- and memory- consuming tests should be put later on
     the list.  */

  /* 1. Schemes other than HTTP are normally not recursed into. */
  if (u->scheme != SCHEME_HTTP
      && !(u->scheme == SCHEME_FTP && opt.follow_ftp))
    {
      DEBUGP (("Not following non-HTTP schemes.\n"));
      goto out;
    }

  /* 2. If it is an absolute link and they are not followed, throw it
     out.  */
  if (u->scheme == SCHEME_HTTP)
    if (opt.relative_only && !upos->link_relative_p)
      {
	DEBUGP (("It doesn't really look like a relative link.\n"));
	goto out;
      }

  /* 3. If its domain is not to be accepted/looked-up, chuck it
     out.  */
  if (!accept_domain (u))
    {
      DEBUGP (("The domain was not accepted.\n"));
      goto out;
    }

  /* 4. Check for parent directory.

     If we descended to a different host or changed the scheme, ignore
     opt.no_parent.  Also ignore it for documents needed to display
     the parent page when in -p mode.  */
  if (opt.no_parent
      && u->scheme == start_url_parsed->scheme
      && 0 == strcasecmp (u->host, start_url_parsed->host)
      && u->port == start_url_parsed->port
      && !(opt.page_requisites && upos->link_inline_p))
    {
      if (!frontcmp (start_url_parsed->dir, u->dir))
	{
	  DEBUGP (("Going to \"%s\" would escape \"%s\" with no_parent on.\n",
		   u->dir, start_url_parsed->dir));
	  goto out;
	}
    }

  /* 5. If the file does not match the acceptance list, or is on the
     rejection list, chuck it out.  The same goes for the directory
     exclusion and inclusion lists.  */
  if (opt.includes || opt.excludes)
    {
      if (!accdir (u->dir, ALLABS))
	{
	  DEBUGP (("%s (%s) is excluded/not-included.\n", url, u->dir));
	  goto out;
	}
    }

  /* 6. */
  {
    char *suf;
    /* Check for acceptance/rejection rules.  We ignore these rules
       for HTML documents because they might lead to other files which
       need to be downloaded.  Of course, we don't know which
       documents are HTML before downloading them, so we guess.

       A file is subject to acceptance/rejection rules if:

       * u->file is not "" (i.e. it is not a directory)
       and either:
         + there is no file suffix,
	 + or there is a suffix, but is not "html" or "htm",
	 + both:
	   - recursion is not infinite,
	   - and we are at its very end. */

    if (u->file[0] != '\0'
	&& ((suf = suffix (url)) == NULL
	    || (0 != strcmp (suf, "html") && 0 != strcmp (suf, "htm"))
	    || (opt.reclevel != INFINITE_RECURSION && depth >= opt.reclevel)))
      {
	if (!acceptable (u->file))
	  {
	    DEBUGP (("%s (%s) does not match acc/rej rules.\n",
		     url, u->file));
	    goto out;
	  }
      }
  }

  /* 7. */
  if (u->scheme == parent->scheme)
    if (!opt.spanhost && 0 != strcasecmp (parent->host, u->host))
      {
	DEBUGP (("This is not the same hostname as the parent's (%s and %s).\n",
		 u->host, parent->host));
	goto out;
      }

  /* 8. */
  if (opt.use_robots && u->scheme == SCHEME_HTTP)
    {
      struct robot_specs *specs = res_get_specs (u->host, u->port);
      if (!specs)
	{
	  char *rfile;
	  if (res_retrieve_file (url, &rfile))
	    {
	      specs = res_parse_from_file (rfile);
	      xfree (rfile);
	    }
	  else
	    {
	      /* If we cannot get real specs, at least produce
		 dummy ones so that we can register them and stop
		 trying to retrieve them.  */
	      specs = res_parse ("", 0);
	    }
	  res_register_specs (u->host, u->port, specs);
	}

      /* Now that we have (or don't have) robots.txt specs, we can
	 check what they say.  */
      if (!res_match_path (specs, u->path))
	{
	  DEBUGP (("Not following %s because robots.txt forbids it.\n", url));
	  string_set_add (blacklist, url);
	  goto out;
	}
    }

  /* The URL has passed all the tests.  It can be placed in the
     download queue. */
  DEBUGP (("Decided to load it.\n"));

  return 1;

 out:
  DEBUGP (("Decided NOT to load it.\n"));

  return 0;
}

/* This function determines whether we will consider downloading the
   children of a URL whose download resulted in a redirection,
   possibly to another host, etc.  It is needed very rarely, and thus
   it is merely a simple-minded wrapper around download_child_p.  */

static int
descend_redirect_p (const char *redirected, const char *original, int depth,
		    struct url *start_url_parsed, struct hash_table *blacklist)
{
  struct url *orig_parsed, *new_parsed;
  struct urlpos *upos;
  int success;

  orig_parsed = url_parse (original, NULL);
  assert (orig_parsed != NULL);

  new_parsed = url_parse (redirected, NULL);
  assert (new_parsed != NULL);

  upos = xmalloc (sizeof (struct urlpos));
  memset (upos, 0, sizeof (*upos));
  upos->url = new_parsed;

  success = download_child_p (upos, orig_parsed, depth,
			      start_url_parsed, blacklist);

  url_free (orig_parsed);
  url_free (new_parsed);
  xfree (upos);

  if (!success)
    DEBUGP (("Redirection \"%s\" failed the test.\n", redirected));

  return success;
}


#define ENSURE_TABLES_EXIST do {			\
  if (!dl_file_url_map)					\
    dl_file_url_map = make_string_hash_table (0);	\
  if (!dl_url_file_map)					\
    dl_url_file_map = make_string_hash_table (0);	\
} while (0)

/* Return 1 if S1 and S2 are the same, except for "/index.html".  The
   three cases in which it returns one are (substitute any substring
   for "foo"):

   m("foo/index.html", "foo/")  ==> 1
   m("foo/", "foo/index.html")  ==> 1
   m("foo", "foo/index.html")   ==> 1
   m("foo", "foo/"              ==> 1
   m("foo", "foo")              ==> 1  */

static int
match_except_index (const char *s1, const char *s2)
{
  int i;
  const char *lng;

  /* Skip common substring. */
  for (i = 0; *s1 && *s2 && *s1 == *s2; s1++, s2++, i++)
    ;
  if (i == 0)
    /* Strings differ at the very beginning -- bail out.  We need to
       check this explicitly to avoid `lng - 1' reading outside the
       array.  */
    return 0;

  if (!*s1 && !*s2)
    /* Both strings hit EOF -- strings are equal. */
    return 1;
  else if (*s1 && *s2)
    /* Strings are randomly different, e.g. "/foo/bar" and "/foo/qux". */
    return 0;
  else if (*s1)
    /* S1 is the longer one. */
    lng = s1;
  else
    /* S2 is the longer one. */
    lng = s2;

  /* foo            */            /* foo/           */
  /* foo/index.html */  /* or */  /* foo/index.html */
  /*    ^           */            /*     ^          */

  if (*lng != '/')
    /* The right-hand case. */
    --lng;

  if (*lng == '/' && *(lng + 1) == '\0')
    /* foo  */
    /* foo/ */
    return 1;

  return 0 == strcmp (lng, "/index.html");
}

static int
dissociate_urls_from_file_mapper (void *key, void *value, void *arg)
{
  char *mapping_url = (char *)key;
  char *mapping_file = (char *)value;
  char *file = (char *)arg;

  if (0 == strcmp (mapping_file, file))
    {
      hash_table_remove (dl_url_file_map, mapping_url);
      xfree (mapping_url);
      xfree (mapping_file);
    }

  /* Continue mapping. */
  return 0;
}

/* Remove all associations from various URLs to FILE from dl_url_file_map. */

static void
dissociate_urls_from_file (const char *file)
{
  hash_table_map (dl_url_file_map, dissociate_urls_from_file_mapper,
		  (char *)file);
}

/* Register that URL has been successfully downloaded to FILE.  This
   is used by the link conversion code to convert references to URLs
   to references to local files.  It is also being used to check if a
   URL has already been downloaded.  */

void
register_download (const char *url, const char *file)
{
  char *old_file, *old_url;

  ENSURE_TABLES_EXIST;

  /* With some forms of retrieval, it is possible, although not likely
     or particularly desirable.  If both are downloaded, the second
     download will override the first one.  When that happens,
     dissociate the old file name from the URL.  */

  if (hash_table_get_pair (dl_file_url_map, file, &old_file, &old_url))
    {
      if (0 == strcmp (url, old_url))
	/* We have somehow managed to download the same URL twice.
	   Nothing to do.  */
	return;

      if (match_except_index (url, old_url)
	  && !hash_table_contains (dl_url_file_map, url))
	/* The two URLs differ only in the "index.html" ending.  For
	   example, one is "http://www.server.com/", and the other is
	   "http://www.server.com/index.html".  Don't remove the old
	   one, just add the new one as a non-canonical entry.  */
	goto url_only;

      hash_table_remove (dl_file_url_map, file);
      xfree (old_file);
      xfree (old_url);

      /* Remove all the URLs that point to this file.  Yes, there can
	 be more than one such URL, because we store redirections as
	 multiple entries in dl_url_file_map.  For example, if URL1
	 redirects to URL2 which gets downloaded to FILE, we map both
	 URL1 and URL2 to FILE in dl_url_file_map.  (dl_file_url_map
	 only points to URL2.)  When another URL gets loaded to FILE,
	 we want both URL1 and URL2 dissociated from it.

         This is a relatively expensive operation because it performs
         a linear search of the whole hash table, but it should be
         called very rarely, only when two URLs resolve to the same
         file name, *and* the "<file>.1" extensions are turned off.
         In other words, almost never.  */
      dissociate_urls_from_file (file);
    }

  /* A URL->FILE mapping is not possible without a FILE->URL mapping.
     If the latter were present, it should have been removed by the
     above `if'.  */
  assert (!hash_table_contains (dl_url_file_map, url));

  hash_table_put (dl_file_url_map, xstrdup (file), xstrdup (url));
 url_only:
  hash_table_put (dl_url_file_map, xstrdup (url), xstrdup (file));
}

/* Register that FROM has been redirected to TO.  This assumes that TO
   is successfully downloaded and already registered using
   register_download() above.  */

void
register_redirection (const char *from, const char *to)
{
  char *file;

  ENSURE_TABLES_EXIST;

  file = hash_table_get (dl_url_file_map, to);
  assert (file != NULL);
  if (!hash_table_contains (dl_url_file_map, from))
    hash_table_put (dl_url_file_map, xstrdup (from), xstrdup (file));
}

/* Register that the file has been deleted. */

static void
register_delete_file (const char *file)
{
  char *old_url, *old_file;

  ENSURE_TABLES_EXIST;

  if (!hash_table_get_pair (dl_file_url_map, file, &old_file, &old_url))
    return;

  hash_table_remove (dl_file_url_map, file);
  xfree (old_file);
  xfree (old_url);
  dissociate_urls_from_file (file);
}

/* Register that FILE is an HTML file that has been downloaded. */

void
register_html (const char *url, const char *file)
{
  if (!opt.convert_links)
    return;
  downloaded_html_files = slist_prepend (downloaded_html_files, file);
}

/* This function is called when the retrieval is done to convert the
   links that have been downloaded.  It has to be called at the end of
   the retrieval, because only then does Wget know conclusively which
   URLs have been downloaded, and which not, so it can tell which
   direction to convert to.

   The "direction" means that the URLs to the files that have been
   downloaded get converted to the relative URL which will point to
   that file.  And the other URLs get converted to the remote URL on
   the server.

   All the downloaded HTMLs are kept in downloaded_html_files, and
   downloaded URLs in urls_downloaded.  All the information is
   extracted from these two lists.  */

void
convert_all_links (void)
{
  slist *html;
  long msecs;
  int file_count = 0;

  struct wget_timer *timer = wtimer_new ();
  struct hash_table *seen = make_string_hash_table (0);

  /* Destructively reverse downloaded_html_files to get it in the right order.
     recursive_retrieve() used slist_prepend() consistently.  */
  downloaded_html_files = slist_nreverse (downloaded_html_files);

  for (html = downloaded_html_files; html; html = html->next)
    {
      struct urlpos *urls, *cur_url;
      char *url;
      char *file = html->string;

      /* Guard against duplicates. */
      if (string_set_contains (seen, file))
	continue;
      string_set_add (seen, file);

      /* Determine the URL of the HTML file.  get_urls_html will need
	 it.  */
      url = hash_table_get (dl_file_url_map, file);
      if (!url)
	{
	  DEBUGP (("Apparently %s has been removed.\n", file));
	  continue;
	}

      DEBUGP (("Scanning %s (from %s)\n", file, url));

      /* Parse the HTML file...  */
      urls = get_urls_html (file, url, NULL);

      /* We don't respect meta_disallow_follow here because, even if
         the file is not followed, we might still want to convert the
         links that have been followed from other files.  */

      for (cur_url = urls; cur_url; cur_url = cur_url->next)
	{
	  char *local_name;
	  struct url *u = cur_url->url;

	  if (cur_url->link_base_p)
	    {
	      /* Base references have been resolved by our parser, so
		 we turn the base URL into an empty string.  (Perhaps
		 we should remove the tag entirely?)  */
	      cur_url->convert = CO_NULLIFY_BASE;
	      continue;
	    }

	  /* We decide the direction of conversion according to whether
	     a URL was downloaded.  Downloaded URLs will be converted
	     ABS2REL, whereas non-downloaded will be converted REL2ABS.  */
	  local_name = hash_table_get (dl_url_file_map, u->url);

	  /* Decide on the conversion type.  */
	  if (local_name)
	    {
	      /* We've downloaded this URL.  Convert it to relative
                 form.  We do this even if the URL already is in
                 relative form, because our directory structure may
                 not be identical to that on the server (think `-nd',
                 `--cut-dirs', etc.)  */
	      cur_url->convert = CO_CONVERT_TO_RELATIVE;
	      cur_url->local_name = xstrdup (local_name);
	      DEBUGP (("will convert url %s to local %s\n", u->url, local_name));
	    }
	  else
	    {
	      /* We haven't downloaded this URL.  If it's not already
                 complete (including a full host name), convert it to
                 that form, so it can be reached while browsing this
                 HTML locally.  */
	      if (!cur_url->link_complete_p)
		cur_url->convert = CO_CONVERT_TO_COMPLETE;
	      cur_url->local_name = NULL;
	      DEBUGP (("will convert url %s to complete\n", u->url));
	    }
	}

      /* Convert the links in the file.  */
      convert_links (file, urls);
      ++file_count;

      /* Free the data.  */
      free_urlpos (urls);
    }

  msecs = wtimer_elapsed (timer);
  wtimer_delete (timer);
  logprintf (LOG_VERBOSE, _("Converted %d files in %.2f seconds.\n"),
	     file_count, (double)msecs / 1000);

  string_set_free (seen);
}

/* Cleanup the data structures associated with recursive retrieving
   (the variables above).  */
void
recursive_cleanup (void)
{
  if (dl_file_url_map)
    {
      free_keys_and_values (dl_file_url_map);
      hash_table_destroy (dl_file_url_map);
      dl_file_url_map = NULL;
    }
  if (dl_url_file_map)
    {
      free_keys_and_values (dl_url_file_map);
      hash_table_destroy (dl_url_file_map);
      dl_url_file_map = NULL;
    }
  slist_free (downloaded_html_files);
  downloaded_html_files = NULL;
}
