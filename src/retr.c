/* File retrieval.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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
#include <stdlib.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <errno.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif /* HAVE_STRING_H */
#include <ctype.h>
#include <assert.h>

#include "wget.h"
#include "utils.h"
#include "retr.h"
#include "url.h"
#include "recur.h"
#include "ftp.h"
#include "host.h"
#include "connect.h"

/* Internal variables used by the timer.  */
static long internal_secs, internal_msecs;

void logflush PARAMS ((void));

/* From http.c.  */
uerr_t http_loop PARAMS ((struct urlinfo *, char **, int *));

/* Flags for show_progress().  */
enum spflags { SP_NONE, SP_INIT, SP_FINISH };

static int show_progress PARAMS ((long, long, enum spflags));

/* Reads the contents of file descriptor FD, until it is closed, or a
   read error occurs.  The data is read in 8K chunks, and stored to
   stream fp, which should have been open for writing.  If BUF is
   non-NULL and its file descriptor is equal to FD, flush RBUF first.
   This function will *not* use the rbuf_* functions!

   The EXPECTED argument is passed to show_progress() unchanged, but
   otherwise ignored.

   If opt.verbose is set, the progress is also shown.  RESTVAL
   represents a value from which to start downloading (which will be
   shown accordingly).  If RESTVAL is non-zero, the stream should have
   been open for appending.

   The function exits and returns codes of 0, -1 and -2 if the
   connection was closed, there was a read error, or if it could not
   write to the output stream, respectively.

   IMPORTANT: The function flushes the contents of the buffer in
   rbuf_flush() before actually reading from fd.  If you wish to read
   from fd immediately, flush or discard the buffer.  */
int
get_contents (int fd, FILE *fp, long *len, long restval, long expected,
	      struct rbuf *rbuf)
{
  int res;
  static char c[8192];

  *len = restval;
  if (opt.verbose)
    show_progress (restval, expected, SP_INIT);
  if (rbuf && RBUF_FD (rbuf) == fd)
    {
      while ((res = rbuf_flush (rbuf, c, sizeof (c))) != 0)
	{
	  if (fwrite (c, sizeof (char), res, fp) < res)
	    return -2;
	  if (opt.verbose)
	    {
	      if (show_progress (res, expected, SP_NONE))
		fflush (fp);
	    }
	  *len += res;
	}
    }
  /* Read from fd while there is available data.  */
  do
    {
      res = iread (fd, c, sizeof (c));
      if (res > 0)
	{
	  if (fwrite (c, sizeof (char), res, fp) < res)
	    return -2;
	  if (opt.verbose)
	    {
	      if (show_progress (res, expected, SP_NONE))
		fflush (fp);
	    }
	  *len += res;
	}
    } while (res > 0);
  if (res < -1)
    res = -1;
  if (opt.verbose)
    show_progress (0, expected, SP_FINISH);
  return res;
}

static void
print_percentage (long bytes, long expected)
{
  int percentage = (int)(100.0 * bytes / expected);
  logprintf (LOG_VERBOSE, " [%3d%%]", percentage);
}

/* Show the dotted progress report of file loading.  Called with
   length and a flag to tell it whether to reset or not.  It keeps the
   offset information in static local variables.

   Return value: 1 or 0, designating whether any dots have been drawn.

   If the init argument is set, the routine will initialize.

   If the res is non-zero, res/line_bytes lines are skipped
   (meaning the appropriate number ok kilobytes), and the number of
   "dots" fitting on the first line are drawn as ','.  */
static int
show_progress (long res, long expected, enum spflags flags)
{
  static long line_bytes;
  static long offs;
  static int ndot, nrow;
  int any_output = 0;

  if (flags == SP_FINISH)
    {
      if (expected)
	{
	  int dot = ndot;
	  char *tmpstr = (char *)alloca (2 * opt.dots_in_line + 1);
	  char *tmpp = tmpstr;
	  for (; dot < opt.dots_in_line; dot++)
	    {
	      if (!(dot % opt.dot_spacing))
		*tmpp++ = ' ';
	      *tmpp++ = ' ';
	    }
	  *tmpp = '\0';
	  logputs (LOG_VERBOSE, tmpstr);
	  print_percentage (nrow * line_bytes + ndot * opt.dot_bytes + offs,
			    expected);
	}
      logputs (LOG_VERBOSE, "\n\n");
      return 0;
    }

  /* Temporarily disable flushing.  */
  opt.no_flush = 1;
  /* init set means initialization.  If res is set, it also means that
     the retrieval is *not* done from the beginning.  The part that
     was already retrieved is not shown again.  */
  if (flags == SP_INIT)
    {
      /* Generic initialization of static variables.  */
      offs = 0L;
      ndot = nrow = 0;
      line_bytes = (long)opt.dots_in_line * opt.dot_bytes;
      if (res)
	{
	  if (res >= line_bytes)
	    {
	      nrow = res / line_bytes;
	      res %= line_bytes;
	      logprintf (LOG_VERBOSE,
			 _("\n          [ skipping %dK ]"),
			 (int) ((nrow * line_bytes) / 1024));
	      ndot = 0;
	    }
	}
      logprintf (LOG_VERBOSE, "\n%5ldK ->", nrow * line_bytes / 1024);
    }
  /* Offset gets incremented by current value.  */
  offs += res;
  /* While offset is >= opt.dot_bytes, print dots, taking care to
     precede every 50th dot with a status message.  */
  for (; offs >= opt.dot_bytes; offs -= opt.dot_bytes)
    {
      if (!(ndot % opt.dot_spacing))
	logputs (LOG_VERBOSE, " ");
      any_output = 1;
      logputs (LOG_VERBOSE, flags == SP_INIT ? "," : ".");
      ++ndot;
      if (ndot == opt.dots_in_line)
	{
	  ndot = 0;
	  ++nrow;
	  if (expected)
	    print_percentage (nrow * line_bytes, expected);
	  logprintf (LOG_VERBOSE, "\n%5ldK ->", nrow * line_bytes / 1024);
	}
    }
  /* Reenable flushing.  */
  opt.no_flush = 0;
  if (any_output)
    /* Force flush.  #### Oh, what a kludge!  */
    logflush ();
  return any_output;
}

/* Reset the internal timer.  */
void
reset_timer (void)
{
#ifdef HAVE_GETTIMEOFDAY
  struct timeval t;
  gettimeofday (&t, NULL);
  internal_secs = t.tv_sec;
  internal_msecs = t.tv_usec / 1000;
#else
  internal_secs = time (NULL);
  internal_msecs = 0;
#endif
}

/* Return the time elapsed from the last call to reset_timer(), in
   milliseconds.  */
long
elapsed_time (void)
{
#ifdef HAVE_GETTIMEOFDAY
  struct timeval t;
  gettimeofday (&t, NULL);
  return ((t.tv_sec - internal_secs) * 1000
	  + (t.tv_usec / 1000 - internal_msecs));
#else
  return 1000 * ((long)time (NULL) - internal_secs);
#endif
}

/* Print out the appropriate download rate.  Appropriate means that if
   rate is > 1024 bytes per second, kilobytes are used, and if rate >
   1024 * 1024 bps, megabytes are used.  */
char *
rate (long bytes, long msecs)
{
  static char res[15];
  double dlrate;

  if (!msecs)
    ++msecs;
  dlrate = (double)1000 * bytes / msecs;
  /* #### Should these strings be translatable?  */
  if (dlrate < 1024.0)
    sprintf (res, "%.2f B/s", dlrate);
  else if (dlrate < 1024.0 * 1024.0)
    sprintf (res, "%.2f KB/s", dlrate / 1024.0);
  else
    sprintf (res, "%.2f MB/s", dlrate / (1024.0 * 1024.0));
  return res;
}

#define USE_PROXY_P(u) (opt.use_proxy && getproxy((u)->proto)		\
			&& no_proxy_match((u)->host,			\
					  (const char **)opt.no_proxy))

/* Retrieve the given URL.  Decides which loop to call -- HTTP, FTP,
   or simply copy it with file:// (#### the latter not yet
   implemented!).  */
uerr_t
retrieve_url (const char *origurl, char **file, char **newloc,
	      const char *refurl, int *dt)
{
  uerr_t result;
  char *url;
  int location_changed, already_redirected, dummy;
  int local_use_proxy;
  char *mynewloc, *proxy;
  struct urlinfo *u;


  /* If dt is NULL, just ignore it.  */
  if (!dt)
    dt = &dummy;
  url = xstrdup (origurl);
  if (newloc)
    *newloc = NULL;
  if (file)
    *file = NULL;
  already_redirected = 0;

 again:
  u = newurl ();
  /* Parse the URL.  RFC2068 requires `Location' to contain an
     absoluteURI, but many sites break this requirement.  #### We
     should be liberal and accept a relative location, too.  */
  result = parseurl (url, u, already_redirected);
  if (result != URLOK)
    {
      freeurl (u, 1);
      logprintf (LOG_NOTQUIET, "%s: %s.\n", url, uerrmsg (result));
      return result;
    }

  /* Set the referer.  */
  if (refurl)
    u->referer = xstrdup (refurl);
  else
    u->referer = NULL;

  local_use_proxy = USE_PROXY_P (u);
  if (local_use_proxy)
    {
      struct urlinfo *pu = newurl ();

      /* Copy the original URL to new location.  */
      memcpy (pu, u, sizeof (*u));
      pu->proxy = NULL; /* A minor correction :) */
      /* Initialize u to nil.  */
      memset (u, 0, sizeof (*u));
      u->proxy = pu;
      /* Get the appropriate proxy server, appropriate for the
	 current protocol.  */
      proxy = getproxy (pu->proto);
      if (!proxy)
	{
	  logputs (LOG_NOTQUIET, _("Could not find proxy host.\n"));
	  freeurl (u, 1);
	  return PROXERR;
	}
      /* Parse the proxy URL.  */
      result = parseurl (proxy, u, 0);
      if (result != URLOK || u->proto != URLHTTP)
	{
	  if (u->proto == URLHTTP)
	    logprintf (LOG_NOTQUIET, "Proxy %s: %s.\n", proxy, uerrmsg (result));
	  else
	    logprintf (LOG_NOTQUIET, _("Proxy %s: Must be HTTP.\n"), proxy);
	  freeurl (u, 1);
	  return PROXERR;
	}
      u->proto = URLHTTP;
    }

  assert (u->proto != URLFILE);	/* #### Implement me!  */
  mynewloc = NULL;

  if (u->proto == URLHTTP)
    result = http_loop (u, &mynewloc, dt);
  else if (u->proto == URLFTP)
    {
      /* If this is a redirection, we must not allow recursive FTP
	 retrieval, so we save recursion to oldrec, and restore it
	 later.  */
      int oldrec = opt.recursive;
      if (already_redirected)
	opt.recursive = 0;
      result = ftp_loop (u, dt);
      opt.recursive = oldrec;
      /* There is a possibility of having HTTP being redirected to
	 FTP.  In these cases we must decide whether the text is HTML
	 according to the suffix.  The HTML suffixes are `.html' and
	 `.htm', case-insensitive.

	 #### All of this is, of course, crap.  These types should be
	 determined through mailcap.  */
      if (already_redirected && u->local && (u->proto == URLFTP ))
	{
	  char *suf = suffix (u->local);
	  if (suf && (!strcasecmp (suf, "html") || !strcasecmp (suf, "htm")))
	    *dt |= TEXTHTML;
	  FREE_MAYBE (suf);
	}
    }
  location_changed = (result == NEWLOCATION);
  if (location_changed)
    {
      /* Check for redirection to oneself.  */
      if (url_equal (url, mynewloc))
	{
	  logprintf (LOG_NOTQUIET, _("%s: Redirection to itself.\n"),
		     mynewloc);
	  return WRONGCODE;
	}
      if (mynewloc)
	{
	  free (url);
	  url = mynewloc;
	}
      freeurl (u, 1);
      already_redirected = 1;
      goto again;
    }
  if (file)
    {
      if (u->local)
	*file = xstrdup (u->local);
      else
	*file = NULL;
    }
  freeurl (u, 1);

  if (newloc)
    *newloc = url;
  else
    free (url);

  return result;
}

/* Find the URL-s in the file and call retrieve_url() for each of
   them.  If HTML is non-zero, treat the file as HTML, and construct
   the URL-s accordingly.

   If opt.recursive is set, call recursive_retrieve() for each file.  */
uerr_t
retrieve_from_file (const char *file, int html, int *count)
{
  uerr_t status;
  urlpos *url_list, *cur_url;

  /* If spider-mode is on, we do not want get_urls_html barfing
     errors on baseless links.  */
  url_list = (html ? get_urls_html (file, NULL, opt.spider)
	      : get_urls_file (file));
  status = RETROK;             /* Suppose everything is OK.  */
  *count = 0;                  /* Reset the URL count.  */
  recursive_reset ();
  for (cur_url = url_list; cur_url; cur_url = cur_url->next, ++*count)
    {
      char *filename, *new_file;
      int dt;

      if (opt.quota && opt.downloaded > opt.quota)
	{
	  status = QUOTEXC;
	  break;
	}
      status = retrieve_url (cur_url->url, &filename, &new_file, NULL, &dt);
      if (opt.recursive && status == RETROK && (dt & TEXTHTML))
	status = recursive_retrieve (filename, new_file ? new_file : cur_url->url);

      if (filename && opt.delete_after && file_exists_p (filename))
	{
	  logprintf (LOG_VERBOSE, _("Removing %s.\n"), filename);
	  if (unlink (filename))
	    logprintf (LOG_NOTQUIET, "unlink: %s\n", strerror (errno));
	  dt &= ~RETROKF;
	}

      FREE_MAYBE (new_file);
      FREE_MAYBE (filename);
    }

  /* Free the linked list of URL-s.  */
  free_urlpos (url_list);

  return status;
}

/* Print `giving up', or `retrying', depending on the impending
   action.  N1 and N2 are the attempt number and the attempt limit.  */
void
printwhat (int n1, int n2)
{
  logputs (LOG_VERBOSE, (n1 == n2) ? _("Giving up.\n\n") : _("Retrying.\n\n"));
}
