/* Handling of recursive HTTP retrieving.
   Copyright (C) 1995, 1996, 1997, 2000 Free Software Foundation, Inc.

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

#ifndef errno
extern int errno;
#endif

extern char *version_string;

#define ROBOTS_FILENAME "robots.txt"

static struct hash_table *dl_file_url_map;
static struct hash_table *dl_url_file_map;

/* List of HTML files downloaded in this Wget run.  Used for link
   conversion after Wget is done.  */
static slist *downloaded_html_files;

/* List of undesirable-to-load URLs.  */
static struct hash_table *undesirable_urls;

/* List of forbidden locations.  */
static char **forbidden = NULL;

/* Current recursion depth.  */
static int depth;

/* Base directory we're recursing from (used by no_parent).  */
static char *base_dir;

/* The host name for which we last checked robots.  */
static char *robots_host;

static int first_time = 1;

/* Construct the robots URL.  */
static struct urlinfo *robots_url PARAMS ((const char *, const char *));
static uerr_t retrieve_robots PARAMS ((const char *, const char *));
static char **parse_robots PARAMS ((const char *));
static int robots_match PARAMS ((struct urlinfo *, char **));


/* Cleanup the data structures associated with recursive retrieving
   (the variables above).  */
void
recursive_cleanup (void)
{
  if (undesirable_urls)
    {
      string_set_free (undesirable_urls);
      undesirable_urls = NULL;
    }
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
  undesirable_urls = NULL;
  free_vec (forbidden);
  forbidden = NULL;
  slist_free (downloaded_html_files);
  downloaded_html_files = NULL;
  FREE_MAYBE (base_dir);
  FREE_MAYBE (robots_host);
  first_time = 1;
}

/* Reset FIRST_TIME to 1, so that some action can be taken in
   recursive_retrieve().  */
void
recursive_reset (void)
{
  first_time = 1;
}

/* The core of recursive retrieving.  Endless recursion is avoided by
   having all URLs stored to a linked list of URLs, which is checked
   before loading any URL.  That way no URL can get loaded twice.

   The function also supports specification of maximum recursion depth
   and a number of other goodies.  */
uerr_t
recursive_retrieve (const char *file, const char *this_url)
{
  char *constr, *filename, *newloc;
  char *canon_this_url = NULL;
  int dt, inl, dash_p_leaf_HTML = FALSE;
  int meta_disallow_follow;
  int this_url_ftp;            /* See below the explanation */
  uerr_t err;
  struct urlinfo *rurl;
  urlpos *url_list, *cur_url;
  char *rfile; /* For robots */
  struct urlinfo *u;

  assert (this_url != NULL);
  assert (file != NULL);
  /* If quota was exceeded earlier, bail out.  */
  if (downloaded_exceeds_quota ())
    return QUOTEXC;
  /* Cache the current URL in the list.  */
  if (first_time)
    {
      /* These three operations need to be done only once per Wget
         run.  They should probably be at a different location.  */
      if (!undesirable_urls)
	undesirable_urls = make_string_hash_table (0);

      hash_table_clear (undesirable_urls);
      string_set_add (undesirable_urls, this_url);
      /* Enter this_url to the hash table, in original and "enhanced" form.  */
      u = newurl ();
      err = parseurl (this_url, u, 0);
      if (err == URLOK)
	{
	  string_set_add (undesirable_urls, u->url);
	  if (opt.no_parent)
	    base_dir = xstrdup (u->dir); /* Set the base dir.  */
	  /* Set the canonical this_url to be sent as referer.  This
	     problem exists only when running the first time.  */
	  canon_this_url = xstrdup (u->url);
	}
      else
	{
	  DEBUGP (("Double yuck!  The *base* URL is broken.\n"));
	  base_dir = NULL;
	}
      freeurl (u, 1);
      depth = 1;
      robots_host = NULL;
      forbidden = NULL;
      first_time = 0;
    }
  else
    ++depth;

  if (opt.reclevel != INFINITE_RECURSION && depth > opt.reclevel)
    /* We've exceeded the maximum recursion depth specified by the user. */
    {
      if (opt.page_requisites && depth <= opt.reclevel + 1)
	/* When -p is specified, we can do one more partial recursion from the
	   "leaf nodes" on the HTML document tree.  The recursion is partial in
	   that we won't traverse any <A> or <AREA> tags, nor any <LINK> tags
	   except for <LINK REL="stylesheet">. */
	dash_p_leaf_HTML = TRUE;
      else
	/* Either -p wasn't specified or it was and we've already gone the one
	   extra (pseudo-)level that it affords us, so we need to bail out. */
	{
	  DEBUGP (("Recursion depth %d exceeded max. depth %d.\n",
		   depth, opt.reclevel));
	  --depth;
	  return RECLEVELEXC;
	}
    }

  /* Determine whether this_url is an FTP URL.  If it is, it means
     that the retrieval is done through proxy.  In that case, FTP
     links will be followed by default and recursion will not be
     turned off when following them.  */
  this_url_ftp = (urlproto (this_url) == URLFTP);

  /* Get the URL-s from an HTML file: */
  url_list = get_urls_html (file, canon_this_url ? canon_this_url : this_url,
			    dash_p_leaf_HTML, &meta_disallow_follow);

  if (opt.use_robots && meta_disallow_follow)
    {
      /* The META tag says we are not to follow this file.  Respect
         that.  */
      free_urlpos (url_list);
      url_list = NULL;
    }

  /* Decide what to do with each of the URLs.  A URL will be loaded if
     it meets several requirements, discussed later.  */
  for (cur_url = url_list; cur_url; cur_url = cur_url->next)
    {
      /* If quota was exceeded earlier, bail out.  */
      if (downloaded_exceeds_quota ())
	break;
      /* Parse the URL for convenient use in other functions, as well
	 as to get the optimized form.  It also checks URL integrity.  */
      u = newurl ();
      if (parseurl (cur_url->url, u, 0) != URLOK)
	{
	  DEBUGP (("Yuck!  A bad URL.\n"));
	  freeurl (u, 1);
	  continue;
	}
      if (u->proto == URLFILE)
	{
	  DEBUGP (("Nothing to do with file:// around here.\n"));
	  freeurl (u, 1);
	  continue;
	}
      assert (u->url != NULL);
      constr = xstrdup (u->url);

      /* Several checkings whether a file is acceptable to load:
	 1. check if URL is ftp, and we don't load it
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

	 Note that .html and (yuck) .htm will get loaded regardless of
	 suffix rules (but that is remedied later with unlink) unless
	 the depth equals the maximum depth.

	 More time- and memory- consuming tests should be put later on
	 the list.  */

      /* inl is set if the URL we are working on (constr) is stored in
	 undesirable_urls.  Using it is crucial to avoid unnecessary
	 repeated continuous hits to the hash table.  */
      inl = string_set_contains (undesirable_urls, constr);

      /* If it is FTP, and FTP is not followed, chuck it out.  */
      if (!inl)
	if (u->proto == URLFTP && !opt.follow_ftp && !this_url_ftp)
	  {
	    DEBUGP (("Uh, it is FTP but i'm not in the mood to follow FTP.\n"));
	    string_set_add (undesirable_urls, constr);
	    inl = 1;
	  }
      /* If it is absolute link and they are not followed, chuck it
	 out.  */
      if (!inl && u->proto != URLFTP)
	if (opt.relative_only && !cur_url->link_relative_p)
	  {
	    DEBUGP (("It doesn't really look like a relative link.\n"));
	    string_set_add (undesirable_urls, constr);
	    inl = 1;
	  }
      /* If its domain is not to be accepted/looked-up, chuck it out.  */
      if (!inl)
	if (!accept_domain (u))
	  {
	    DEBUGP (("I don't like the smell of that domain.\n"));
	    string_set_add (undesirable_urls, constr);
	    inl = 1;
	  }
      /* Check for parent directory.  */
      if (!inl && opt.no_parent
	  /* If the new URL is FTP and the old was not, ignore
             opt.no_parent.  */
	  && !(!this_url_ftp && u->proto == URLFTP))
	{
	  /* Check for base_dir first.  */
	  if (!(base_dir && frontcmp (base_dir, u->dir)))
	    {
	      /* Failing that, check for parent dir.  */
	      struct urlinfo *ut = newurl ();
	      if (parseurl (this_url, ut, 0) != URLOK)
		DEBUGP (("Double yuck!  The *base* URL is broken.\n"));
	      else if (!frontcmp (ut->dir, u->dir))
		{
		  /* Failing that too, kill the URL.  */
		  DEBUGP (("Trying to escape parental guidance with no_parent on.\n"));
		  string_set_add (undesirable_urls, constr);
		  inl = 1;
		}
	      freeurl (ut, 1);
	    }
	}
      /* If the file does not match the acceptance list, or is on the
	 rejection list, chuck it out.  The same goes for the
	 directory exclude- and include- lists.  */
      if (!inl && (opt.includes || opt.excludes))
	{
	  if (!accdir (u->dir, ALLABS))
	    {
	      DEBUGP (("%s (%s) is excluded/not-included.\n", constr, u->dir));
	      string_set_add (undesirable_urls, constr);
	      inl = 1;
	    }
	}
      if (!inl)
	{
	  char *suf = NULL;
	  /* We check for acceptance/rejection rules only for non-HTML
	     documents.  Since we don't know whether they really are
	     HTML, it will be deduced from (an OR-ed list):

	     1) u->file is "" (meaning it is a directory)
	     2) suffix exists, AND:
	     a) it is "html", OR
	     b) it is "htm"

	     If the file *is* supposed to be HTML, it will *not* be
            subject to acc/rej rules, unless a finite maximum depth has
            been specified and the current depth is the maximum depth. */
	  if (!
	      (!*u->file
	       || (((suf = suffix (constr)) != NULL)
                  && ((!strcmp (suf, "html") || !strcmp (suf, "htm"))
                      && ((opt.reclevel != INFINITE_RECURSION) &&
			  (depth != opt.reclevel))))))
	    {
	      if (!acceptable (u->file))
		{
		  DEBUGP (("%s (%s) does not match acc/rej rules.\n",
			  constr, u->file));
		  string_set_add (undesirable_urls, constr);
		  inl = 1;
		}
	    }
	  FREE_MAYBE (suf);
	}
      /* Optimize the URL (which includes possible DNS lookup) only
	 after all other possibilities have been exhausted.  */
      if (!inl)
	{
	  if (!opt.simple_check)
	    opt_url (u);
	  else
	    {
	      char *p;
	      /* Just lowercase the hostname.  */
	      for (p = u->host; *p; p++)
		*p = TOLOWER (*p);
	      xfree (u->url);
	      u->url = str_url (u, 0);
	    }
	  xfree (constr);
	  constr = xstrdup (u->url);
	  string_set_add (undesirable_urls, constr);
	  if (!inl && !((u->proto == URLFTP) && !this_url_ftp))
	    if (!opt.spanhost && this_url && !same_host (this_url, constr))
	      {
		DEBUGP (("This is not the same hostname as the parent's.\n"));
		string_set_add (undesirable_urls, constr);
		inl = 1;
	      }
	}
      /* What about robots.txt?  */
      if (!inl && opt.use_robots && u->proto == URLHTTP)
	{
	  /* Since Wget knows about only one set of robot rules at a
	     time, /robots.txt must be reloaded whenever a new host is
	     accessed.

	     robots_host holds the host the current `forbid' variable
	     is assigned to.  */
	  if (!robots_host || !same_host (robots_host, u->host))
	    {
	      FREE_MAYBE (robots_host);
	      /* Now make robots_host the new host, no matter what the
		 result will be.  So if there is no /robots.txt on the
		 site, Wget will not retry getting robots all the
		 time.  */
	      robots_host = xstrdup (u->host);
	      free_vec (forbidden);
	      forbidden = NULL;
	      err = retrieve_robots (constr, ROBOTS_FILENAME);
	      if (err == ROBOTSOK)
		{
		  rurl = robots_url (constr, ROBOTS_FILENAME);
		  rfile = url_filename (rurl);
		  forbidden = parse_robots (rfile);
		  freeurl (rurl, 1);
		  xfree (rfile);
		}
	    }

	  /* Now that we have (or don't have) robots, we can check for
	     them.  */
	  if (!robots_match (u, forbidden))
	    {
	      DEBUGP (("Stuffing %s because %s forbids it.\n", this_url,
		       ROBOTS_FILENAME));
	      string_set_add (undesirable_urls, constr);
	      inl = 1;
	    }
	}

      filename = NULL;
      /* If it wasn't chucked out, do something with it.  */
      if (!inl)
	{
	  DEBUGP (("I've decided to load it -> "));
	  /* Add it to the list of already-loaded URL-s.  */
	  string_set_add (undesirable_urls, constr);
	  /* Automatically followed FTPs will *not* be downloaded
	     recursively.  */
	  if (u->proto == URLFTP)
	    {
	      /* Don't you adore side-effects?  */
	      opt.recursive = 0;
	    }
	  /* Reset its type.  */
	  dt = 0;
	  /* Retrieve it.  */
	  retrieve_url (constr, &filename, &newloc,
		       canon_this_url ? canon_this_url : this_url, &dt);
	  if (u->proto == URLFTP)
	    {
	      /* Restore...  */
	      opt.recursive = 1;
	    }
	  if (newloc)
	    {
	      xfree (constr);
	      constr = newloc;
	    }
	  /* If there was no error, and the type is text/html, parse
	     it recursively.  */
	  if (dt & TEXTHTML)
	    {
	      if (dt & RETROKF)
		recursive_retrieve (filename, constr);
	    }
	  else
	    DEBUGP (("%s is not text/html so we don't chase.\n",
		     filename ? filename: "(null)"));

	  if (opt.delete_after || (filename && !acceptable (filename)))
	    /* Either --delete-after was specified, or we loaded this otherwise
	       rejected (e.g. by -R) HTML file just so we could harvest its
	       hyperlinks -- in either case, delete the local file. */
	    {
	      DEBUGP (("Removing file due to %s in recursive_retrieve():\n",
		       opt.delete_after ? "--delete-after" :
		       "recursive rejection criteria"));
	      logprintf (LOG_VERBOSE,
			 (opt.delete_after ? _("Removing %s.\n")
			  : _("Removing %s since it should be rejected.\n")),
			 filename);
	      if (unlink (filename))
		logprintf (LOG_NOTQUIET, "unlink: %s\n", strerror (errno));
	      dt &= ~RETROKF;
	    }

	  /* If everything was OK, and links are to be converted, let's
	     store the local filename.  */
	  if (opt.convert_links && (dt & RETROKF) && (filename != NULL))
	    {
	      cur_url->convert = CO_CONVERT_TO_RELATIVE;
	      cur_url->local_name = xstrdup (filename);
	    }
	}
      else
	DEBUGP (("%s already in list, so we don't load.\n", constr));
      /* Free filename and constr.  */
      FREE_MAYBE (filename);
      FREE_MAYBE (constr);
      freeurl (u, 1);
      /* Increment the pbuf for the appropriate size.  */
    }
  if (opt.convert_links && !opt.delete_after)
    /* This is merely the first pass: the links that have been
       successfully downloaded are converted.  In the second pass,
       convert_all_links() will also convert those links that have NOT
       been downloaded to their canonical form.  */
    convert_links (file, url_list);
  /* Free the linked list of URL-s.  */
  free_urlpos (url_list);
  /* Free the canonical this_url.  */
  FREE_MAYBE (canon_this_url);
  /* Decrement the recursion depth.  */
  --depth;
  if (downloaded_exceeds_quota ())
    return QUOTEXC;
  else
    return RETROK;
}

void
register_download (const char *url, const char *file)
{
  if (!opt.convert_links)
    return;
  if (!dl_file_url_map)
    dl_file_url_map = make_string_hash_table (0);
  hash_table_put (dl_file_url_map, xstrdup (file), xstrdup (url));
  if (!dl_url_file_map)
    dl_url_file_map = make_string_hash_table (0);
  hash_table_put (dl_url_file_map, xstrdup (url), xstrdup (file));
}

void
register_html (const char *url, const char *file)
{
  if (!opt.convert_links)
    return;
  downloaded_html_files = slist_prepend (downloaded_html_files, file);
}

/* convert_links() is called from recursive_retrieve() after we're
   done with an HTML file.  This call to convert_links is not complete
   because it converts only the downloaded files, and Wget cannot know
   which files will be downloaded afterwards.  So, if we have file
   fileone.html with:

   <a href="/c/something.gif">

   and /c/something.gif was not downloaded because it exceeded the
   recursion depth, the reference will *not* be changed.

   However, later we can encounter /c/something.gif from an "upper"
   level HTML (let's call it filetwo.html), and it gets downloaded.

   But now we have a problem because /c/something.gif will be
   correctly transformed in filetwo.html, but not in fileone.html,
   since Wget could not have known that /c/something.gif will be
   downloaded in the future.

   This is why Wget must, after the whole retrieval, call
   convert_all_links to go once more through the entire list of
   retrieved HTMLs, and re-convert them.

   All the downloaded HTMLs are kept in downloaded_html_files, and downloaded URLs
   in urls_downloaded.  From these two lists information is
   extracted.  */
void
convert_all_links (void)
{
  slist *html;

  /* Destructively reverse downloaded_html_files to get it in the right order.
     recursive_retrieve() used slist_prepend() consistently.  */
  downloaded_html_files = slist_nreverse (downloaded_html_files);

  for (html = downloaded_html_files; html; html = html->next)
    {
      urlpos *urls, *cur_url;
      char *url;

      DEBUGP (("Rescanning %s\n", html->string));
      /* Determine the URL of the HTML file.  get_urls_html will need
	 it.  */
      url = hash_table_get (dl_file_url_map, html->string);
      if (url)
	DEBUGP (("It should correspond to %s.\n", url));
      else
	DEBUGP (("I cannot find the corresponding URL.\n"));
      /* Parse the HTML file...  */
      urls = get_urls_html (html->string, url, FALSE, NULL);
      /* We don't respect meta_disallow_follow here because, even if
         the file is not followed, we might still want to convert the
         links that have been followed from other files.  */
      for (cur_url = urls; cur_url; cur_url = cur_url->next)
	{
	  char *local_name;

	  /* The URL must be in canonical form to be compared.  */
	  struct urlinfo *u = newurl ();
	  uerr_t res = parseurl (cur_url->url, u, 0);
	  if (res != URLOK)
	    {
	      freeurl (u, 1);
	      continue;
	    }
	  /* We decide the direction of conversion according to whether
	     a URL was downloaded.  Downloaded URLs will be converted
	     ABS2REL, whereas non-downloaded will be converted REL2ABS.  */
	  local_name = hash_table_get (dl_url_file_map, u->url);
	  if (local_name)
	    DEBUGP (("%s marked for conversion, local %s\n",
		     u->url, local_name));
	  /* Decide on the conversion direction.  */
	  if (local_name)
	    {
	      /* We've downloaded this URL.  Convert it to relative
                 form.  We do this even if the URL already is in
                 relative form, because our directory structure may
                 not be identical to that on the server (think `-nd',
                 `--cut-dirs', etc.)  */
	      cur_url->convert = CO_CONVERT_TO_RELATIVE;
	      cur_url->local_name = xstrdup (local_name);
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
	    }
	  freeurl (u, 1);
	}
      /* Convert the links in the file.  */
      convert_links (html->string, urls);
      /* Free the data.  */
      free_urlpos (urls);
    }
}

/* Robots support.  */

/* Construct the robots URL.  */
static struct urlinfo *
robots_url (const char *url, const char *robots_filename)
{
  struct urlinfo *u = newurl ();
  uerr_t err;

  err = parseurl (url, u, 0);
  assert (err == URLOK && u->proto == URLHTTP);
  xfree (u->file);
  xfree (u->dir);
  xfree (u->url);
  u->dir = xstrdup ("");
  u->file = xstrdup (robots_filename);
  u->url = str_url (u, 0);
  return u;
}

/* Retrieves the robots_filename from the root server directory, if
   possible.  Returns ROBOTSOK if robots were retrieved OK, and
   NOROBOTS if robots could not be retrieved for any reason.  */
static uerr_t
retrieve_robots (const char *url, const char *robots_filename)
{
  int dt;
  uerr_t err;
  struct urlinfo *u;

  u = robots_url (url, robots_filename);
  logputs (LOG_VERBOSE, _("Loading robots.txt; please ignore errors.\n"));
  err = retrieve_url (u->url, NULL, NULL, NULL, &dt);
  freeurl (u, 1);
  if (err == RETROK)
    return ROBOTSOK;
  else
    return NOROBOTS;
}

/* Parse the robots_filename and return the disallowed path components
   in a malloc-ed vector of character pointers.

   It should be fully compliant with the syntax as described in the
   file norobots.txt, adopted by the robots mailing list
   (robots@webcrawler.com).  */
static char **
parse_robots (const char *robots_filename)
{
  FILE *fp;
  char **entries;
  char *line, *cmd, *str, *p;
  char *base_version, *version;
  int num, i;
  int wget_matched;		/* is the part meant for Wget?  */

  entries = NULL;

  num = 0;
  fp = fopen (robots_filename, "rb");
  if (!fp)
    return NULL;

  /* Kill version number.  */
  if (opt.useragent)
    {
      STRDUP_ALLOCA (base_version, opt.useragent);
      STRDUP_ALLOCA (version, opt.useragent);
    }
  else
    {
      int len = 10 + strlen (version_string);
      base_version = (char *)alloca (len);
      sprintf (base_version, "Wget/%s", version_string);
      version = (char *)alloca (len);
      sprintf (version, "Wget/%s", version_string);
    }
  for (p = version; *p; p++)
    *p = TOLOWER (*p);
  for (p = base_version; *p && *p != '/'; p++)
    *p = TOLOWER (*p);
  *p = '\0';

  /* Setting this to 1 means that Wget considers itself under
     restrictions by default, even if the User-Agent field is not
     present.  However, if it finds the user-agent set to anything
     other than Wget, the rest will be ignored (up to the following
     User-Agent field).  Thus you may have something like:

     Disallow: 1
     Disallow: 2
     User-Agent: stupid-robot
     Disallow: 3
     Disallow: 4
     User-Agent: Wget*
     Disallow: 5
     Disallow: 6
     User-Agent: *
     Disallow: 7

     In this case the 1, 2, 5, 6 and 7 disallow lines will be
     stored.  */
  wget_matched = 1;
  while ((line = read_whole_line (fp)))
    {
      int len = strlen (line);
      /* Destroy <CR><LF> if present.  */
      if (len && line[len - 1] == '\n')
	line[--len] = '\0';
      if (len && line[len - 1] == '\r')
	line[--len] = '\0';
      /* According to specifications, optional space may be at the
	 end...  */
      DEBUGP (("Line: %s\n", line));
      /* Skip spaces.  */
      for (cmd = line; *cmd && ISSPACE (*cmd); cmd++);
      if (!*cmd)
	{
	  xfree (line);
	  DEBUGP (("(chucked out)\n"));
	  continue;
	}
      /* Look for ':'.  */
      for (str = cmd; *str && *str != ':'; str++);
      if (!*str)
	{
	  xfree (line);
	  DEBUGP (("(chucked out)\n"));
	  continue;
	}
      /* Zero-terminate the command.  */
      *str++ = '\0';
      /* Look for the string beginning...  */
      for (; *str && ISSPACE (*str); str++);
      /* Look for comments or trailing spaces and kill them off.  */
      for (p = str; *p; p++)
	if (*p && ISSPACE (*p) && ((*(p + 1) == '#') || (*(p + 1) == '\0')))
	  {
	    /* We have found either a shell-style comment `<sp>+#' or some
               trailing spaces.  Now rewind to the beginning of the spaces
               and place '\0' there.  */
	    while (p > str && ISSPACE (*p))
	      --p;
	    if (p == str)
	      *p = '\0';
	    else
	      *(p + 1) = '\0';
	    break;
	  }
      if (!strcasecmp (cmd, "User-agent"))
	{
	  int match = 0;
	  /* Lowercase the agent string.  */
	  for (p = str; *p; p++)
	    *p = TOLOWER (*p);
	  /* If the string is `*', it matches.  */
	  if (*str == '*' && !*(str + 1))
	    match = 1;
	  else
	    {
	      /* If the string contains wildcards, we'll run it through
		 fnmatch().  */
	      if (has_wildcards_p (str))
		{
		  /* If the string contains '/', compare with the full
		     version.  Else, compare it to base_version.  */
		  if (strchr (str, '/'))
		    match = !fnmatch (str, version, 0);
		  else
		    match = !fnmatch (str, base_version, 0);
		}
	      else                /* Substring search */
		{
		  if (strstr (version, str))
		    match = 1;
		  else
		    match = 0;
		}
	    }
	  /* If Wget is not matched, skip all the entries up to the
	     next User-agent field.  */
	  wget_matched = match;
	}
      else if (!wget_matched)
	{
	  xfree (line);
	  DEBUGP (("(chucking out since it is not applicable for Wget)\n"));
	  continue;
	}
      else if (!strcasecmp (cmd, "Disallow"))
	{
	  /* If "Disallow" is empty, the robot is welcome.  */
	  if (!*str)
	    {
	      free_vec (entries);
	      entries = (char **)xmalloc (sizeof (char *));
	      *entries = NULL;
	      num = 0;
	    }
	  else
	    {
	      entries = (char **)xrealloc (entries, (num + 2)* sizeof (char *));
	      entries[num] = xstrdup (str);
	      entries[++num] = NULL;
	      /* Strip trailing spaces, according to specifications.  */
	      for (i = strlen (str); i >= 0 && ISSPACE (str[i]); i--)
		if (ISSPACE (str[i]))
		  str[i] = '\0';
	    }
	}
      else
	{
	  /* unknown command */
	  DEBUGP (("(chucked out)\n"));
	}
      xfree (line);
    }
  fclose (fp);
  return entries;
}

/* May the URL url be loaded according to disallowing rules stored in
   forbidden?  */
static int
robots_match (struct urlinfo *u, char **fb)
{
  int l;

  if (!fb)
    return 1;
  DEBUGP (("Matching %s against: ", u->path));
  for (; *fb; fb++)
    {
      DEBUGP (("%s ", *fb));
      l = strlen (*fb);
      /* If dir is fb, we may not load the file.  */
      if (strncmp (u->path, *fb, l) == 0)
	{
	  DEBUGP (("matched.\n"));
	  return 0; /* Matches, i.e. does not load...  */
	}
    }
  DEBUGP (("not matched.\n"));
  return 1;
}
