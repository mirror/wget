/* Download progress.
   Copyright (C) 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
\(at your option) any later version.

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
#include <assert.h>

#include "wget.h"
#include "progress.h"
#include "utils.h"
#include "retr.h"

struct progress_implementation {
  char *name;
  void *(*create) (long, long);
  void (*update) (void *, long);
  void (*finish) (void *);
  void (*set_params) (const char *);
};

/* Necessary forward declarations. */

static void *dp_create PARAMS ((long, long));
static void dp_update PARAMS ((void *, long));
static void dp_finish PARAMS ((void *));
static void dp_set_params PARAMS ((const char *));

static void *bar_create PARAMS ((long, long));
static void bar_update PARAMS ((void *, long));
static void bar_finish PARAMS ((void *));
static void bar_set_params PARAMS ((const char *));

static struct progress_implementation implementations[] = {
  { "dot", dp_create, dp_update, dp_finish, dp_set_params },
  { "bar", bar_create, bar_update, bar_finish, bar_set_params }
};
static struct progress_implementation *current_impl;

/* Return non-zero if NAME names a valid progress bar implementation.
   The characters after the first : will be ignored.  */

int
valid_progress_implementation_p (const char *name)
{
  int i = 0;
  struct progress_implementation *pi = implementations;
  char *colon = strchr (name, ':');
  int namelen = colon ? colon - name : strlen (name);

  for (i = 0; i < ARRAY_SIZE (implementations); i++, pi++)
    if (!strncmp (pi->name, name, namelen))
      return 1;
  return 0;
}

/* Set the progress implementation to NAME.  */

void
set_progress_implementation (const char *name)
{
  int i = 0;
  struct progress_implementation *pi = implementations;
  char *colon = strchr (name, ':');
  int namelen = colon ? colon - name : strlen (name);

  for (i = 0; i < ARRAY_SIZE (implementations); i++, pi++)
    if (!strncmp (pi->name, name, namelen))
      {
	current_impl = pi;

	if (colon)
	  /* We call pi->set_params even if colon is NULL because we
	     want to give the implementation a chance to set up some
	     things it needs to run.  */
	  ++colon;

	if (pi->set_params)
	  pi->set_params (colon);
	return;
      }
  abort ();
}

/* Create a progress gauge.  INITIAL is the number of bytes the
   download starts from (zero if the download starts from scratch).
   TOTAL is the expected total number of bytes in this download.  If
   TOTAL is zero, it means that the download size is not known in
   advance.  */

void *
progress_create (long initial, long total)
{
  return current_impl->create (initial, total);
}

/* Inform the progress gauge of newly received bytes. */

void
progress_update (void *progress, long howmuch)
{
  current_impl->update (progress, howmuch);
}

/* Tell the progress gauge to clean up.  Calling this will free the
   PROGRESS object, the further use of which is not allowed.  */

void
progress_finish (void *progress)
{
  current_impl->finish (progress);
}

/* Dot-printing. */

struct dot_progress {
  long initial_length;		/* how many bytes have been downloaded
				   previously. */
  long total_length;		/* expected total byte count when the
				   download finishes */

  int accumulated;

  int rows;			/* number of rows printed so far */
  int dots;			/* number of dots printed in this row */

  struct wget_timer *timer;	/* timer used to measure per-row
				   download rates. */
  long last_timer_value;
};

/* Dot-progress backend for progress_create. */

static void *
dp_create (long initial, long total)
{
  struct dot_progress *dp = xmalloc (sizeof (struct dot_progress));

  memset (dp, 0, sizeof (*dp));

  dp->initial_length = initial;
  dp->total_length   = total;
  dp->timer = wtimer_new ();

  if (dp->initial_length)
    {
      int dot_bytes = opt.dot_bytes;
      long row_bytes = opt.dot_bytes * opt.dots_in_line;

      int remainder = (int) (dp->initial_length % row_bytes);
      long skipped = dp->initial_length - remainder;

      if (skipped)
	{
	  logputs (LOG_VERBOSE, "\n      "); /* leave spacing untranslated */
	  logprintf (LOG_VERBOSE, _("[ skipping %dK ]"),
		     (int) (skipped / 1024));
	}

      logprintf (LOG_VERBOSE, "\n%5ldK", skipped / 1024);
      for (; remainder >= dot_bytes; remainder -= dot_bytes)
	{
	  if (dp->dots % opt.dot_spacing == 0)
	    logputs (LOG_VERBOSE, " ");
	  logputs (LOG_VERBOSE, ",");
	  ++dp->dots;
	}
      assert (dp->dots < opt.dots_in_line);

      dp->accumulated = remainder;
      dp->rows = skipped / row_bytes;
    }

  return dp;
}

static void
print_percentage (long bytes, long expected)
{
  int percentage = (int)(100.0 * bytes / expected);
  logprintf (LOG_VERBOSE, "%3d%%", percentage);
}

static void
print_elapsed (struct dot_progress *dp, long bytes)
{
  long timer_value = wtimer_elapsed (dp->timer);
  logprintf (LOG_VERBOSE, " @ %s",
	     rate (bytes, timer_value - dp->last_timer_value, 1));
  dp->last_timer_value = timer_value;
}

/* Dot-progress backend for progress_update. */

static void
dp_update (void *progress, long howmuch)
{
  struct dot_progress *dp = progress;
  int dot_bytes = opt.dot_bytes;
  long row_bytes = opt.dot_bytes * opt.dots_in_line;

  log_set_flush (0);

  dp->accumulated += howmuch;
  for (; dp->accumulated >= dot_bytes; dp->accumulated -= dot_bytes)
    {
      if (dp->dots == 0)
	logprintf (LOG_VERBOSE, "\n%5ldK", dp->rows * row_bytes / 1024);

      if (dp->dots % opt.dot_spacing == 0)
	logputs (LOG_VERBOSE, " ");
      logputs (LOG_VERBOSE, ".");

      ++dp->dots;
      if (dp->dots >= opt.dots_in_line)
	{
	  ++dp->rows;
	  dp->dots = 0;

	  if (dp->total_length)
	    print_percentage (dp->rows * row_bytes, dp->total_length);

	  print_elapsed (dp, row_bytes - (dp->initial_length % row_bytes));
	}
    }

  log_set_flush (1);
}

/* Dot-progress backend for progress_finish. */

static void
dp_finish (void *progress)
{
  struct dot_progress *dp = progress;
  int dot_bytes = opt.dot_bytes;
  long row_bytes = opt.dot_bytes * opt.dots_in_line;
  int i;

  log_set_flush (0);

  for (i = dp->dots; i < opt.dots_in_line; i++)
    {
      if (i % opt.dot_spacing == 0)
	logputs (LOG_VERBOSE, " ");
      logputs (LOG_VERBOSE, " ");
    }
  if (dp->total_length)
    {
      print_percentage (dp->rows * row_bytes
			+ dp->dots * dot_bytes
			+ dp->accumulated,
			dp->total_length);
    }

  print_elapsed (dp, dp->dots * dot_bytes
		 + dp->accumulated
		 - dp->initial_length % row_bytes);
  logputs (LOG_VERBOSE, "\n\n");

  log_set_flush (0);

  wtimer_delete (dp->timer);
  xfree (dp);
}

/* This function interprets the progress "parameters".  For example,
   if Wget is invoked with --progress=bar:mega, it will set the
   "dot-style" to "mega".  Valid styles are default, binary, mega, and
   giga.  */

static void
dp_set_params (const char *params)
{
  if (!params)
    return;

  /* We use this to set the retrieval style.  */
  if (!strcasecmp (params, "default"))
    {
      /* Default style: 1K dots, 10 dots in a cluster, 50 dots in a
	 line.  */
      opt.dot_bytes = 1024;
      opt.dot_spacing = 10;
      opt.dots_in_line = 50;
    }
  else if (!strcasecmp (params, "binary"))
    {
      /* "Binary" retrieval: 8K dots, 16 dots in a cluster, 48 dots
	 (384K) in a line.  */
      opt.dot_bytes = 8192;
      opt.dot_spacing = 16;
      opt.dots_in_line = 48;
    }
  else if (!strcasecmp (params, "mega"))
    {
      /* "Mega" retrieval, for retrieving very long files; each dot is
	 64K, 8 dots in a cluster, 6 clusters (3M) in a line.  */
      opt.dot_bytes = 65536L;
      opt.dot_spacing = 8;
      opt.dots_in_line = 48;
    }
  else if (!strcasecmp (params, "giga"))
    {
      /* "Giga" retrieval, for retrieving very very *very* long files;
	 each dot is 1M, 8 dots in a cluster, 4 clusters (32M) in a
	 line.  */
      opt.dot_bytes = (1L << 20);
      opt.dot_spacing = 8;
      opt.dots_in_line = 32;
    }
  else
    fprintf (stderr,
	     _("Invalid dot style specification `%s'; leaving unchanged.\n"),
	     params);
}

/* "Thermometer" (bar) progress. */

/* Assumed screen width if we can't find the real value.  */
#define DEFAULT_SCREEN_WIDTH 80

/* Minimum screen width we'll try to work with.  If this is too small,
   create_image will overflow the buffer.  */
#define MINIMUM_SCREEN_WIDTH 45

static int screen_width = DEFAULT_SCREEN_WIDTH;

struct bar_progress {
  long initial_length;		/* how many bytes have been downloaded
				   previously. */
  long total_length;		/* expected total byte count when the
				   download finishes */
  long count;			/* bytes downloaded so far */

  struct wget_timer *timer;	/* timer used to measure the download
				   rates. */
  long last_update;		/* time of the last screen update. */

  int width;			/* screen width at the time the
				   progress gauge was created. */
  char *buffer;			/* buffer where the bar "image" is
				   stored. */
};

static void create_image PARAMS ((struct bar_progress *, long));
static void display_image PARAMS ((char *));

static void *
bar_create (long initial, long total)
{
  struct bar_progress *bp = xmalloc (sizeof (struct bar_progress));

  memset (bp, 0, sizeof (*bp));

  bp->initial_length = initial;
  bp->total_length   = total;
  bp->timer = wtimer_new ();
  bp->width = screen_width;
  bp->buffer = xmalloc (bp->width + 1);

  logputs (LOG_VERBOSE, "\n");

  create_image (bp, 0);
  display_image (bp->buffer);

  return bp;
}

static void
bar_update (void *progress, long howmuch)
{
  struct bar_progress *bp = progress;
  int force_update = 0;
  long dltime = wtimer_elapsed (bp->timer);

  bp->count += howmuch;

  if (screen_width != bp->width)
    {
      bp->width = screen_width;
      bp->buffer = xrealloc (bp->buffer, bp->width + 1);
    }

  if (dltime - bp->last_update < 200 && !force_update)
    /* Don't update more often than every half a second. */
    return;

  bp->last_update = dltime;

  create_image (bp, dltime);
  display_image (bp->buffer);
}

static void
bar_finish (void *progress)
{
  struct bar_progress *bp = progress;

  create_image (bp, wtimer_elapsed (bp->timer));
  display_image (bp->buffer);

  logputs (LOG_VERBOSE, "\n\n");

  xfree (bp->buffer);
  wtimer_delete (bp->timer);
  xfree (bp);
}

static void
create_image (struct bar_progress *bp, long dltime)
{
  char *p = bp->buffer;
  long size = bp->initial_length + bp->count;

  /* The progress bar should look like this:
     xxx% |=======>             | xx KB/s nnnnn ETA: 00:00

     Calculate its geometry:

     "xxx% "         - percentage                - 5 chars
     "| ... | "      - progress bar decorations  - 3 chars
     "1234.56 K/s "  - dl rate                   - 12 chars
     "nnnn "         - downloaded bytes          - 11 chars
     "ETA: xx:xx:xx" - ETA                       - 13 chars

     "=====>..."     - progress bar content      - the rest
  */
  int progress_len = screen_width - (5 + 3 + 12 + 11 + 13);

  if (progress_len < 7)
    progress_len = 0;

  /* "xxx% " */
  if (bp->total_length > 0)
    {
      int percentage = (int)(100.0 * size / bp->total_length);

      assert (percentage <= 100);

      sprintf (p, "%3d%% ", percentage);
      p += 5;
    }

  /* The progress bar: "|====>      | " */
  if (progress_len && bp->total_length > 0)
    {
      double fraction = (double)size / bp->total_length;
      int dlsz = (int)(fraction * progress_len);
      char *begin;

      assert (dlsz <= progress_len);

      *p++ = '|';
      begin = p;

      if (dlsz > 0)
	{
	  /* Draw dlsz-1 '=' chars and one arrow char.  */
	  while (dlsz-- > 1)
	    *p++ = '=';
	  *p++ = '>';
	}

      while (p - begin < progress_len)
	*p++ = ' ';

      *p++ = '|';
      *p++ = ' ';
    }

  /* "2.3 KB/s " */
  if (dltime && bp->count)
    {
      char *rt = rate (bp->count, dltime, 1);
      strcpy (p, rt);
      p += strlen (p);
      *p++ = ' ';
    }
  else
    {
      strcpy (p, "----.-- KB/s ");
      p += 13;
    }

  /* "12376 " */
  sprintf (p, _("%ld "), size);
  p += strlen (p);

  /* "ETA: xx:xx:xx" */
  if (bp->total_length > 0 && bp->count > 0)
    {
      int eta, eta_hrs, eta_min, eta_sec;
      double tm_sofar = (double)dltime / 1000;
      long bytes_remaining = bp->total_length - size;

      eta = (int) (tm_sofar * bytes_remaining / bp->count);

      eta_hrs = eta / 3600, eta %= 3600;
      eta_min = eta / 60,   eta %= 60;
      eta_sec = eta;

      /*printf ("\neta: %d, %d %d %d\n", eta, eta_hrs, eta_min, eta_sec);*/
      /*printf ("\n%ld %f %ld %ld\n", dltime, tm_sofar, bytes_remaining, bp->count);*/

      *p++ = 'E';
      *p++ = 'T';
      *p++ = 'A';
      *p++ = ':';
      *p++ = ' ';

      if (eta_hrs > 99)
	/* Bogus value, for whatever reason.  We must avoid overflow. */
	sprintf (p, "--:--");
      else if (eta_hrs > 0)
	sprintf (p, "%d:%02d:%02d", eta_hrs, eta_min, eta_sec);
      else
	sprintf (p, "%02d:%02d", eta_min, eta_sec);
      p += strlen (p);
    }
  else if (bp->total_length > 0)
    {
      strcpy (p, "ETA: --:--");
      p += 10;
    }

  assert (p - bp->buffer <= screen_width);

  while (p < bp->buffer + screen_width)
    *p++ = ' ';
  *p = '\0';
}

static void
display_image (char *buf)
{
  int len = strlen (buf);
  char *del_buf = alloca (len + 1);

  logputs (LOG_VERBOSE, buf);

  memset (del_buf, '\b', len);
  del_buf[len] = '\0';

  logputs (LOG_VERBOSE, del_buf);
}

static void
bar_set_params (const char *ignored)
{
  int sw = determine_screen_width ();
  if (sw && sw >= MINIMUM_SCREEN_WIDTH)
    screen_width = sw;
}

RETSIGTYPE
progress_handle_sigwinch (int sig)
{
  int sw = determine_screen_width ();
  if (sw && sw >= MINIMUM_SCREEN_WIDTH)
    screen_width = sw;
}
