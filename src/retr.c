/* File retrieval.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.

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

#ifdef HAVE_SSL
# include "gen_sslfunc.h"	/* for ssl_iread */
#endif

#ifndef errno
extern int errno;
#endif

/* See the comment in gethttp() why this is needed. */
int global_download_count;


static struct {
  long bytes;
  long dltime;
} limit_data;

static void
limit_bandwidth_reset (void)
{
  limit_data.bytes  = 0;
  limit_data.dltime = 0;
}

/* Limit the bandwidth by pausing the download for an amount of time.
   BYTES is the number of bytes received from the network, DELTA is
   how long it took to receive them, DLTIME the current download time,
   TIMER the timer, and ADJUSTMENT the previous.  */

static void
limit_bandwidth (long bytes, long delta)
{
  long expected;

  limit_data.bytes += bytes;
  limit_data.dltime += delta;

  expected = (long)(1000.0 * limit_data.bytes / opt.limit_rate);

  if (expected > limit_data.dltime)
    {
      long slp = expected - limit_data.dltime;
      if (slp < 200)
	{
	  DEBUGP (("deferring a %ld ms sleep (%ld/%ld) until later.\n",
		   slp, limit_data.bytes, limit_data.dltime));
	  return;
	}
      DEBUGP (("sleeping %ld ms\n", slp));
      usleep (1000 * slp);
    }

  limit_data.bytes = 0;
  limit_data.dltime = 0;
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
	      struct rbuf *rbuf, int use_expected, long *elapsed)
{
  int res = 0;
  static char c[8192];
  void *progress = NULL;
  struct wget_timer *timer = wtimer_allocate ();
  long dltime = 0, last_dltime = 0;

  *len = restval;

  if (opt.verbose)
    progress = progress_create (restval, expected);

  if (rbuf && RBUF_FD (rbuf) == fd)
    {
      int sz = 0;
      while ((res = rbuf_flush (rbuf, c, sizeof (c))) != 0)
	{
	  fwrite (c, sizeof (char), res, fp);
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
      if (opt.verbose)
	progress_update (progress, sz, 0);
    }

  if (opt.limit_rate)
    limit_bandwidth_reset ();
  wtimer_reset (timer);

  /* Read from fd while there is available data.

     Normally, if expected is 0, it means that it is not known how
     much data is expected.  However, if use_expected is specified,
     then expected being zero means exactly that.  */
  while (!use_expected || (*len < expected))
    {
      int amount_to_read = (use_expected
			    ? MIN (expected - *len, sizeof (c))
			    : sizeof (c));
#ifdef HAVE_SSL
      if (rbuf->ssl!=NULL)
	res = ssl_iread (rbuf->ssl, c, amount_to_read);
      else
#endif /* HAVE_SSL */
	res = iread (fd, c, amount_to_read);

      if (res > 0)
	{
	  fwrite (c, sizeof (char), res, fp);
	  /* Always flush the contents of the network packet.  This
	     should not be adverse to performance, as the network
	     packets typically won't be too tiny anyway.  */
	  fflush (fp);
	  if (ferror (fp))
	    {
	      res = -2;
	      goto out;
	    }

	  /* If bandwidth is not limited, one call to wtimer_elapsed
	     is sufficient.  */
	  dltime = wtimer_elapsed (timer);
	  if (opt.limit_rate)
	    {
	      limit_bandwidth (res, dltime - last_dltime);
	      dltime = wtimer_elapsed (timer);
	      last_dltime = dltime;
	    }

	  if (opt.verbose)
	    progress_update (progress, res, dltime);
	  *len += res;
	}
      else
	break;
    }
  if (res < -1)
    res = -1;

 out:
  if (opt.verbose)
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
retr_rate (long bytes, long msecs, int pad)
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
calc_rate (long bytes, long msecs, int *units)
{
  double dlrate;

  assert (msecs >= 0);
  assert (bytes >= 0);

  if (msecs == 0)
    /* If elapsed time is 0, it means we're under the granularity of
       the timer.  This often happens on systems that use time() for
       the timer.  */
    msecs = wtimer_granularity ();

  dlrate = (double)1000 * bytes / msecs;
  if (dlrate < 1024.0)
    *units = 0;
  else if (dlrate < 1024.0 * 1024.0)
    *units = 1, dlrate /= 1024.0;
  else if (dlrate < 1024.0 * 1024.0 * 1024.0)
    *units = 2, dlrate /= (1024.0 * 1024.0);
  else
    /* Maybe someone will need this one day.  More realistically, it
       will get tickled by buggy timers. */
    *units = 3, dlrate /= (1024.0 * 1024.0 * 1024.0);

  return dlrate;
}

static int
register_redirections_mapper (void *key, void *value, void *arg)
{
  const char *redirected_from = (const char *)key;
  const char *redirected_to   = (const char *)arg;
  if (0 != strcmp (redirected_from, redirected_to))
    register_redirection (redirected_from, redirected_to);
  return 0;
}

/* Register the redirections that lead to the successful download of
   this URL.  This is necessary so that the link converter can convert
   redirected URLs to the local file.  */

static void
register_all_redirections (struct hash_table *redirections, const char *final)
{
  hash_table_map (redirections, register_redirections_mapper, (void *)final);
}

#define USE_PROXY_P(u) (opt.use_proxy && getproxy((u)->scheme)		\
			&& no_proxy_match((u)->host,			\
					  (const char **)opt.no_proxy))

/* Maximum number of allowed redirections.  20 was chosen as a
   "reasonable" value, which is low enough to not cause havoc, yet
   high enough to guarantee that normal retrievals will not be hurt by
   the check.  */

#define MAX_REDIRECTIONS 20

/* Retrieve the given URL.  Decides which loop to call -- HTTP, FTP,
   FTP, proxy, etc.  */

uerr_t
retrieve_url (const char *origurl, char **file, char **newloc,
	      const char *refurl, int *dt)
{
  uerr_t result;
  char *url;
  int location_changed, dummy;
  int use_proxy;
  char *mynewloc, *proxy;
  struct url *u;
  int up_error_code;		/* url parse error code */
  char *local_file;
  struct hash_table *redirections = NULL;
  int redirection_count = 0;

  /* If dt is NULL, just ignore it.  */
  if (!dt)
    dt = &dummy;
  url = xstrdup (origurl);
  if (newloc)
    *newloc = NULL;
  if (file)
    *file = NULL;

  u = url_parse (url, &up_error_code);
  if (!u)
    {
      logprintf (LOG_NOTQUIET, "%s: %s.\n", url, url_error (up_error_code));
      if (redirections)
	string_set_free (redirections);
      xfree (url);
      return URLERROR;
    }

  if (!refurl)
    refurl = opt.referer;

 redirected:

  result = NOCONERROR;
  mynewloc = NULL;
  local_file = NULL;

  use_proxy = USE_PROXY_P (u);
  if (use_proxy)
    {
      struct url *proxy_url;

      /* Get the proxy server for the current scheme.  */
      proxy = getproxy (u->scheme);
      if (!proxy)
	{
	  logputs (LOG_NOTQUIET, _("Could not find proxy host.\n"));
	  url_free (u);
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  return PROXERR;
	}

      /* Parse the proxy URL.  */
      proxy_url = url_parse (proxy, &up_error_code);
      if (!proxy_url)
	{
	  logprintf (LOG_NOTQUIET, _("Error parsing proxy URL %s: %s.\n"),
		     proxy, url_error (up_error_code));
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  return PROXERR;
	}
      if (proxy_url->scheme != SCHEME_HTTP)
	{
	  logprintf (LOG_NOTQUIET, _("Error in proxy URL %s: Must be HTTP.\n"), proxy);
	  url_free (proxy_url);
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  return PROXERR;
	}

      result = http_loop (u, &mynewloc, &local_file, refurl, dt, proxy_url);
      url_free (proxy_url);
    }
  else if (u->scheme == SCHEME_HTTP
#ifdef HAVE_SSL
      || u->scheme == SCHEME_HTTPS
#endif
      )
    {
      result = http_loop (u, &mynewloc, &local_file, refurl, dt, NULL);
    }
  else if (u->scheme == SCHEME_FTP)
    {
      /* If this is a redirection, we must not allow recursive FTP
	 retrieval, so we save recursion to oldrec, and restore it
	 later.  */
      int oldrec = opt.recursive;
      if (redirections)
	opt.recursive = 0;
      result = ftp_loop (u, dt);
      opt.recursive = oldrec;

      /* There is a possibility of having HTTP being redirected to
	 FTP.  In these cases we must decide whether the text is HTML
	 according to the suffix.  The HTML suffixes are `.html' and
	 `.htm', case-insensitive.  */
      if (redirections && local_file && u->scheme == SCHEME_FTP)
	{
	  char *suf = suffix (local_file);
	  if (suf && (!strcasecmp (suf, "html") || !strcasecmp (suf, "htm")))
	    *dt |= TEXTHTML;
	}
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
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  xfree (mynewloc);
	  return result;
	}

      /* Now mynewloc will become newloc_parsed->url, because if the
         Location contained relative paths like .././something, we
         don't want that propagating as url.  */
      xfree (mynewloc);
      mynewloc = xstrdup (newloc_parsed->url);

      if (!redirections)
	{
	  redirections = make_string_hash_table (0);
	  /* Add current URL immediately so we can detect it as soon
             as possible in case of a cycle. */
	  string_set_add (redirections, u->url);
	}

      /* The new location is OK.  Check for max. number of
	 redirections.  */
      if (++redirection_count > MAX_REDIRECTIONS)
	{
	  logprintf (LOG_NOTQUIET, _("%d redirections exceeded.\n"),
		     MAX_REDIRECTIONS);
	  url_free (newloc_parsed);
	  url_free (u);
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  xfree (mynewloc);
	  return WRONGCODE;
	}

      /*Check for redirection cycle by
         peeking through the history of redirections. */
      if (string_set_contains (redirections, newloc_parsed->url))
	{
	  logprintf (LOG_NOTQUIET, _("%s: Redirection cycle detected.\n"),
		     mynewloc);
	  url_free (newloc_parsed);
	  url_free (u);
	  if (redirections)
	    string_set_free (redirections);
	  xfree (url);
	  xfree (mynewloc);
	  return WRONGCODE;
	}
      string_set_add (redirections, newloc_parsed->url);

      xfree (url);
      url = mynewloc;
      url_free (u);
      u = newloc_parsed;
      goto redirected;
    }

  if (local_file)
    {
      if (*dt & RETROKF)
	{
	  register_download (u->url, local_file);
	  if (redirections)
	    register_all_redirections (redirections, u->url);
	  if (*dt & TEXTHTML)
	    register_html (u->url, local_file);
	}
    }

  if (file)
    *file = local_file ? local_file : NULL;
  else
    FREE_MAYBE (local_file);

  url_free (u);

  if (redirections)
    {
      string_set_free (redirections);
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

      if (downloaded_exceeds_quota ())
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

/* Increment opt.downloaded by BY_HOW_MUCH.  If an overflow occurs,
   set opt.downloaded_overflow to 1. */
void
downloaded_increase (unsigned long by_how_much)
{
  VERY_LONG_TYPE old;
  if (opt.downloaded_overflow)
    return;
  old = opt.downloaded;
  opt.downloaded += by_how_much;
  if (opt.downloaded < old)	/* carry flag, where are you when I
                                   need you? */
    {
      /* Overflow. */
      opt.downloaded_overflow = 1;
      opt.downloaded = ~((VERY_LONG_TYPE)0);
    }
}

/* Return non-zero if the downloaded amount of bytes exceeds the
   desired quota.  If quota is not set or if the amount overflowed, 0
   is returned. */
int
downloaded_exceeds_quota (void)
{
  if (!opt.quota)
    return 0;
  if (opt.downloaded_overflow)
    /* We don't really know.  (Wildly) assume not. */
    return 0;

  return opt.downloaded > opt.quota;
}

/* If opt.wait or opt.waitretry are specified, and if certain
   conditions are met, sleep the appropriate number of seconds.  See
   the documentation of --wait and --waitretry for more information.

   COUNT is the count of current retrieval, beginning with 1. */

void
sleep_between_retrievals (int count)
{
  static int first_retrieval = 1;

  if (first_retrieval && opt.random_wait)
    /* --random-wait uses the RNG, so seed it. */
    srand (time (NULL));

  if (!first_retrieval && (opt.wait || opt.waitretry))
    {
      if (opt.waitretry && count > 1)
	{
	  /* If opt.waitretry is specified and this is a retry, wait
	     for COUNT-1 number of seconds, or for opt.waitretry
	     seconds.  */
	  if (count <= opt.waitretry)
	    sleep (count - 1);
	  else
	    sleep (opt.waitretry);
	}
      else if (opt.wait)
	{
	  /* Otherwise, check if opt.wait is specified.  If so, sleep.  */
	  if (count > 1 || !opt.random_wait)
	    sleep (opt.wait);
	  else
	    {
	      int waitmax = 2 * opt.wait;
	      /* This is equivalent to rand() % waitmax, but uses the
		 high-order bits for better randomness.  */
	      int waitsecs = (double)waitmax * rand () / (RAND_MAX + 1.0);

	      DEBUGP (("sleep_between_retrievals: norm=%ld,fuzz=%ld,sleep=%d\n",
		       opt.wait, waitsecs - opt.wait, waitsecs));

	      if (waitsecs)
		sleep (waitsecs);
	    }
	}
    }
  if (first_retrieval)
    first_retrieval = 0;
}
