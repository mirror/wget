/* File retrieval.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

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
#include <assert.h>

#include "wget.h"
#include "utils.h"
#include "retr.h"
#include "progress.h"
#include "url.h"
#include "recur.h"
#include "ftp.h"
#include "host.h"
#include "connect.h"
#include "hash.h"
#include "convert.h"

#ifdef HAVE_SSL
# include "gen_sslfunc.h"	/* for ssl_iread */
#endif

#ifndef errno
extern int errno;
#endif

/* See the comment in gethttp() why this is needed. */
int global_download_count;

/* Total size of downloaded files.  Used to enforce quota.  */
LARGE_INT total_downloaded_bytes;


static struct {
  long chunk_bytes;
  double chunk_start;
  double sleep_adjust;
} limit_data;

static void
limit_bandwidth_reset (void)
{
  limit_data.chunk_bytes = 0;
  limit_data.chunk_start = 0;
}

/* Limit the bandwidth by pausing the download for an amount of time.
   BYTES is the number of bytes received from the network, and DELTA
   is the number of milliseconds it took to receive them.  */

static void
limit_bandwidth (long bytes, double *dltime, struct wget_timer *timer)
{
  double delta_t = *dltime - limit_data.chunk_start;
  double expected;

  limit_data.chunk_bytes += bytes;

  /* Calculate the amount of time we expect downloading the chunk
     should take.  If in reality it took less time, sleep to
     compensate for the difference.  */
  expected = 1000.0 * limit_data.chunk_bytes / opt.limit_rate;

  if (expected > delta_t)
    {
      double slp = expected - delta_t + limit_data.sleep_adjust;
      double t0, t1;
      if (slp < 200)
	{
	  DEBUGP (("deferring a %.2f ms sleep (%ld/%.2f).\n",
		   slp, limit_data.chunk_bytes, delta_t));
	  return;
	}
      DEBUGP (("\nsleeping %.2f ms for %ld bytes, adjust %.2f ms\n",
	       slp, limit_data.chunk_bytes, limit_data.sleep_adjust));

      t0 = *dltime;
      usleep ((unsigned long) (1000 * slp));
      t1 = wtimer_elapsed (timer);

      /* Due to scheduling, we probably slept slightly longer (or
	 shorter) than desired.  Calculate the difference between the
	 desired and the actual sleep, and adjust the next sleep by
	 that amount.  */
      limit_data.sleep_adjust = slp - (t1 - t0);

      /* Since we've called wtimer_elapsed, we might as well update
	 the caller's dltime. */
      *dltime = t1;
    }

  limit_data.chunk_bytes = 0;
  limit_data.chunk_start = *dltime;
}

#define MIN(i, j) ((i) <= (j) ? (i) : (j))

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
	      struct rbuf *rbuf, int use_expected, double *elapsed)
{
  int res = 0;

  static char dlbuf[16384];
  int dlbufsize = sizeof (dlbuf);

  void *progress = NULL;
  struct wget_timer *timer = wtimer_allocate ();
  double dltime = 0;

  *len = restval;

  if (opt.verbose)
    progress = progress_create (restval, expected);

  if (rbuf && RBUF_FD (rbuf) == fd)
    {
      int sz = 0;
      while ((res = rbuf_flush (rbuf, dlbuf, sizeof (dlbuf))) != 0)
	{
	  fwrite (dlbuf, 1, res, fp);
	  *len += res;
	  sz += res;
	}
      if (sz)
	fflush (fp);
      if (ferror (fp))
	{
	  res = -2;
	  goto out;
	}
      if (progress)
	progress_update (progress, sz, 0);
    }

  if (opt.limit_rate)
    limit_bandwidth_reset ();
  wtimer_reset (timer);

  /* Use a smaller buffer for low requested bandwidths.  For example,
     with --limit-rate=2k, it doesn't make sense to slurp in 16K of
     data and then sleep for 8s.  With buffer size equal to the limit,
     we never have to sleep for more than one second.  */
  if (opt.limit_rate && opt.limit_rate < dlbufsize)
    dlbufsize = opt.limit_rate;

  /* Read from fd while there is available data.

     Normally, if expected is 0, it means that it is not known how
     much data is expected.  However, if use_expected is specified,
     then expected being zero means exactly that.  */
  while (!use_expected || (*len < expected))
    {
      int amount_to_read = (use_expected
			    ? MIN (expected - *len, dlbufsize) : dlbufsize);
#ifdef HAVE_SSL
      if (rbuf->ssl!=NULL)
	res = ssl_iread (rbuf->ssl, dlbuf, amount_to_read);
      else
#endif /* HAVE_SSL */
	res = iread (fd, dlbuf, amount_to_read);

      if (res <= 0)
	break;

      fwrite (dlbuf, 1, res, fp);
      /* Always flush the contents of the network packet.  This should
	 not hinder performance: fast downloads will be received in
	 16K chunks (which stdio would write out anyway), and slow
	 downloads won't be limited with disk performance.  */
      fflush (fp);
      if (ferror (fp))
	{
	  res = -2;
	  goto out;
	}

      dltime = wtimer_elapsed (timer);
      if (opt.limit_rate)
	limit_bandwidth (res, &dltime, timer);

      *len += res;
      if (progress)
	progress_update (progress, res, dltime);
#ifdef WINDOWS
      if (use_expected && expected > 0)
	ws_percenttitle (100.0 * (double)(*len) / (double)expected);
#endif
    }
  if (res < -1)
    res = -1;

 out:
  if (progress)
    progress_finish (progress, dltime);
  if (elapsed)
    *elapsed = dltime;
  wtimer_delete (timer);

  return res;
}

/* Return a printed representation of the download rate, as
   appropriate for the speed.  If PAD is non-zero, strings will be
   padded to the width of 7 characters (xxxx.xx).  */
char *
retr_rate (long bytes, double msecs, int pad)
{
  static char res[20];
  static char *rate_names[] = {"B/s", "KB/s", "MB/s", "GB/s" };
  int units = 0;

  double dlrate = calc_rate (bytes, msecs, &units);
  sprintf (res, pad ? "%7.2f %s" : "%.2f %s", dlrate, rate_names[units]);

  return res;
}

/* Calculate the download rate and trim it as appropriate for the
   speed.  Appropriate means that if rate is greater than 1K/s,
   kilobytes are used, and if rate is greater than 1MB/s, megabytes
   are used.

   UNITS is zero for B/s, one for KB/s, two for MB/s, and three for
   GB/s.  */
double
calc_rate (long bytes, double msecs, int *units)
{
  double dlrate;

  assert (msecs >= 0);
  assert (bytes >= 0);

  if (msecs == 0)
    /* If elapsed time is exactly zero, it means we're under the
       granularity of the timer.  This often happens on systems that
       use time() for the timer.  */
    msecs = wtimer_granularity ();

  dlrate = (double)1000 * bytes / msecs;
  if (dlrate < 1024.0)
    *units = 0;
  else if (dlrate < 1024.0 * 1024.0)
    *units = 1, dlrate /= 1024.0;
  else if (dlrate < 1024.0 * 1024.0 * 1024.0)
    *units = 2, dlrate /= (1024.0 * 1024.0);
  else
    /* Maybe someone will need this, one day. */
    *units = 3, dlrate /= (1024.0 * 1024.0 * 1024.0);

  return dlrate;
}

/* Maximum number of allowed redirections.  20 was chosen as a
   "reasonable" value, which is low enough to not cause havoc, yet
   high enough to guarantee that normal retrievals will not be hurt by
   the check.  */

#define MAX_REDIRECTIONS 20

#define SUSPEND_POST_DATA do {			\
  post_data_suspended = 1;			\
  saved_post_data = opt.post_data;		\
  saved_post_file_name = opt.post_file_name;	\
  opt.post_data = NULL;				\
  opt.post_file_name = NULL;			\
} while (0)

#define RESTORE_POST_DATA do {				\
  if (post_data_suspended)				\
    {							\
      opt.post_data = saved_post_data;			\
      opt.post_file_name = saved_post_file_name;	\
      post_data_suspended = 0;				\
    }							\
} while (0)

static char *getproxy PARAMS ((struct url *));

/* Retrieve the given URL.  Decides which loop to call -- HTTP, FTP,
   FTP, proxy, etc.  */

/* #### This function should be rewritten so it doesn't return from
   multiple points. */

uerr_t
retrieve_url (const char *origurl, char **file, char **newloc,
	      const char *refurl, int *dt)
{
  uerr_t result;
  char *url;
  int location_changed, dummy;
  char *mynewloc, *proxy;
  struct url *u, *proxy_url;
  int up_error_code;		/* url parse error code */
  char *local_file;
  int redirection_count = 0;

  int post_data_suspended = 0;
  char *saved_post_data = NULL;
  char *saved_post_file_name = NULL;

  /* If dt is NULL, use local storage.  */
  if (!dt)
    {
      dt = &dummy;
      dummy = 0;
    }
  url = xstrdup (origurl);
  if (newloc)
    *newloc = NULL;
  if (file)
    *file = NULL;

  u = url_parse (url, &up_error_code);
  if (!u)
    {
      logprintf (LOG_NOTQUIET, "%s: %s.\n", url, url_error (up_error_code));
      xfree (url);
      return URLERROR;
    }

  if (!refurl)
    refurl = opt.referer;

 redirected:

  result = NOCONERROR;
  mynewloc = NULL;
  local_file = NULL;
  proxy_url = NULL;

  proxy = getproxy (u);
  if (proxy)
    {
      /* Parse the proxy URL.  */
      proxy_url = url_parse (proxy, &up_error_code);
      if (!proxy_url)
	{
	  logprintf (LOG_NOTQUIET, _("Error parsing proxy URL %s: %s.\n"),
		     proxy, url_error (up_error_code));
	  xfree (url);
	  RESTORE_POST_DATA;
	  return PROXERR;
	}
      if (proxy_url->scheme != SCHEME_HTTP && proxy_url->scheme != u->scheme)
	{
	  logprintf (LOG_NOTQUIET, _("Error in proxy URL %s: Must be HTTP.\n"), proxy);
	  url_free (proxy_url);
	  xfree (url);
	  RESTORE_POST_DATA;
	  return PROXERR;
	}
    }

  if (u->scheme == SCHEME_HTTP
#ifdef HAVE_SSL
      || u->scheme == SCHEME_HTTPS
#endif
      || (proxy_url && proxy_url->scheme == SCHEME_HTTP))
    {
      result = http_loop (u, &mynewloc, &local_file, refurl, dt, proxy_url);
    }
  else if (u->scheme == SCHEME_FTP)
    {
      /* If this is a redirection, we must not allow recursive FTP
	 retrieval, so we save recursion to oldrec, and restore it
	 later.  */
      int oldrec = opt.recursive;
      if (redirection_count)
	opt.recursive = 0;
      result = ftp_loop (u, dt, proxy_url);
      opt.recursive = oldrec;

      /* There is a possibility of having HTTP being redirected to
	 FTP.  In these cases we must decide whether the text is HTML
	 according to the suffix.  The HTML suffixes are `.html',
	 `.htm' and a few others, case-insensitive.  */
      if (redirection_count && local_file && u->scheme == SCHEME_FTP)
	{
	  if (has_html_suffix_p (local_file))
	    *dt |= TEXTHTML;
	}
    }

  if (proxy_url)
    {
      url_free (proxy_url);
      proxy_url = NULL;
    }

  location_changed = (result == NEWLOCATION);
  if (location_changed)
    {
      char *construced_newloc;
      struct url *newloc_parsed;

      assert (mynewloc != NULL);

      if (local_file)
	xfree (local_file);

      /* The HTTP specs only allow absolute URLs to appear in
	 redirects, but a ton of boneheaded webservers and CGIs out
	 there break the rules and use relative URLs, and popular
	 browsers are lenient about this, so wget should be too. */
      construced_newloc = uri_merge (url, mynewloc);
      xfree (mynewloc);
      mynewloc = construced_newloc;

      /* Now, see if this new location makes sense. */
      newloc_parsed = url_parse (mynewloc, &up_error_code);
      if (!newloc_parsed)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s.\n", mynewloc,
		     url_error (up_error_code));
	  url_free (u);
	  xfree (url);
	  xfree (mynewloc);
	  RESTORE_POST_DATA;
	  return result;
	}

      /* Now mynewloc will become newloc_parsed->url, because if the
         Location contained relative paths like .././something, we
         don't want that propagating as url.  */
      xfree (mynewloc);
      mynewloc = xstrdup (newloc_parsed->url);

      /* Check for max. number of redirections.  */
      if (++redirection_count > MAX_REDIRECTIONS)
	{
	  logprintf (LOG_NOTQUIET, _("%d redirections exceeded.\n"),
		     MAX_REDIRECTIONS);
	  url_free (newloc_parsed);
	  url_free (u);
	  xfree (url);
	  xfree (mynewloc);
	  RESTORE_POST_DATA;
	  return WRONGCODE;
	}

      xfree (url);
      url = mynewloc;
      url_free (u);
      u = newloc_parsed;

      /* If we're being redirected from POST, we don't want to POST
	 again.  Many requests answer POST with a redirection to an
	 index page; that redirection is clearly a GET.  We "suspend"
	 POST data for the duration of the redirections, and restore
	 it when we're done. */
      if (!post_data_suspended)
	SUSPEND_POST_DATA;

      goto redirected;
    }

  if (local_file)
    {
      if (*dt & RETROKF)
	{
	  register_download (u->url, local_file);
	  if (redirection_count && 0 != strcmp (origurl, u->url))
	    register_redirection (origurl, u->url);
	  if (*dt & TEXTHTML)
	    register_html (u->url, local_file);
	}
    }

  if (file)
    *file = local_file ? local_file : NULL;
  else
    FREE_MAYBE (local_file);

  url_free (u);

  if (redirection_count)
    {
      if (newloc)
	*newloc = url;
      else
	xfree (url);
    }
  else
    {
      if (newloc)
	*newloc = NULL;
      xfree (url);
    }

  ++global_download_count;
  RESTORE_POST_DATA;

  return result;
}

/* Find the URLs in the file and call retrieve_url() for each of
   them.  If HTML is non-zero, treat the file as HTML, and construct
   the URLs accordingly.

   If opt.recursive is set, call recursive_retrieve() for each file.  */
uerr_t
retrieve_from_file (const char *file, int html, int *count)
{
  uerr_t status;
  struct urlpos *url_list, *cur_url;

  url_list = (html ? get_urls_html (file, NULL, NULL)
	      : get_urls_file (file));
  status = RETROK;             /* Suppose everything is OK.  */
  *count = 0;                  /* Reset the URL count.  */

  for (cur_url = url_list; cur_url; cur_url = cur_url->next, ++*count)
    {
      char *filename = NULL, *new_file = NULL;
      int dt;

      if (cur_url->ignore_when_downloading)
	continue;

      if (opt.quota && total_downloaded_bytes > opt.quota)
	{
	  status = QUOTEXC;
	  break;
	}
      if (opt.recursive && cur_url->url->scheme != SCHEME_FTP)
	status = retrieve_tree (cur_url->url->url);
      else
	status = retrieve_url (cur_url->url->url, &filename, &new_file, NULL, &dt);

      if (filename && opt.delete_after && file_exists_p (filename))
	{
	  DEBUGP (("Removing file due to --delete-after in"
		   " retrieve_from_file():\n"));
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

/* If opt.wait or opt.waitretry are specified, and if certain
   conditions are met, sleep the appropriate number of seconds.  See
   the documentation of --wait and --waitretry for more information.

   COUNT is the count of current retrieval, beginning with 1. */

void
sleep_between_retrievals (int count)
{
  static int first_retrieval = 1;

  if (first_retrieval)
    {
      /* Don't sleep before the very first retrieval. */
      first_retrieval = 0;
      return;
    }

  if (opt.waitretry && count > 1)
    {
      /* If opt.waitretry is specified and this is a retry, wait for
	 COUNT-1 number of seconds, or for opt.waitretry seconds.  */
      if (count <= opt.waitretry)
	sleep (count - 1);
      else
	usleep (1000000L * opt.waitretry);
    }
  else if (opt.wait)
    {
      if (!opt.random_wait || count > 1)
	/* If random-wait is not specified, or if we are sleeping
	   between retries of the same download, sleep the fixed
	   interval.  */
	usleep (1000000L * opt.wait);
      else
	{
	  /* Sleep a random amount of time averaging in opt.wait
	     seconds.  The sleeping amount ranges from 0 to
	     opt.wait*2, inclusive.  */
	  double waitsecs = 2 * opt.wait * random_float ();
	  DEBUGP (("sleep_between_retrievals: avg=%f,sleep=%f\n",
		   opt.wait, waitsecs));
	  usleep (1000000L * waitsecs);
	}
    }
}

/* Free the linked list of urlpos.  */
void
free_urlpos (struct urlpos *l)
{
  while (l)
    {
      struct urlpos *next = l->next;
      if (l->url)
	url_free (l->url);
      FREE_MAYBE (l->local_name);
      xfree (l);
      l = next;
    }
}

/* Rotate FNAME opt.backups times */
void
rotate_backups(const char *fname)
{
  int maxlen = strlen (fname) + 1 + numdigit (opt.backups) + 1;
  char *from = (char *)alloca (maxlen);
  char *to = (char *)alloca (maxlen);
  struct stat sb;
  int i;

  if (stat (fname, &sb) == 0)
    if (S_ISREG (sb.st_mode) == 0)
      return;

  for (i = opt.backups; i > 1; i--)
    {
      sprintf (from, "%s.%d", fname, i - 1);
      sprintf (to, "%s.%d", fname, i);
      rename (from, to);
    }

  sprintf (to, "%s.%d", fname, 1);
  rename(fname, to);
}

static int no_proxy_match PARAMS ((const char *, const char **));

/* Return the URL of the proxy appropriate for url U.  */

static char *
getproxy (struct url *u)
{
  char *proxy = NULL;
  char *rewritten_url;
  static char rewritten_storage[1024];

  if (!opt.use_proxy)
    return NULL;
  if (!no_proxy_match (u->host, (const char **)opt.no_proxy))
    return NULL;

  switch (u->scheme)
    {
    case SCHEME_HTTP:
      proxy = opt.http_proxy ? opt.http_proxy : getenv ("http_proxy");
      break;
#ifdef HAVE_SSL
    case SCHEME_HTTPS:
      proxy = opt.https_proxy ? opt.https_proxy : getenv ("https_proxy");
      break;
#endif
    case SCHEME_FTP:
      proxy = opt.ftp_proxy ? opt.ftp_proxy : getenv ("ftp_proxy");
      break;
    case SCHEME_INVALID:
      break;
    }
  if (!proxy || !*proxy)
    return NULL;

  /* Handle shorthands.  `rewritten_storage' is a kludge to allow
     getproxy() to return static storage. */
  rewritten_url = rewrite_shorthand_url (proxy);
  if (rewritten_url)
    {
      strncpy (rewritten_storage, rewritten_url, sizeof(rewritten_storage));
      rewritten_storage[sizeof (rewritten_storage) - 1] = '\0';
      proxy = rewritten_storage;
    }

  return proxy;
}

/* Should a host be accessed through proxy, concerning no_proxy?  */
int
no_proxy_match (const char *host, const char **no_proxy)
{
  if (!no_proxy)
    return 1;
  else
    return !sufmatch (no_proxy, host);
}
