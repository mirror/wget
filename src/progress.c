/* Download progress.
   Copyright (C) 2001 Free Software Foundation, Inc.

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
#include <assert.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif

#include "wget.h"
#include "progress.h"
#include "utils.h"
#include "retr.h"

struct progress_implementation {
  char *name;
  void *(*create) (long, long);
  void (*update) (void *, long, long);
  void (*finish) (void *, long);
  void (*set_params) (const char *);
};

/* Necessary forward declarations. */

static void *dot_create PARAMS ((long, long));
static void dot_update PARAMS ((void *, long, long));
static void dot_finish PARAMS ((void *, long));
static void dot_set_params PARAMS ((const char *));

static void *bar_create PARAMS ((long, long));
static void bar_update PARAMS ((void *, long, long));
static void bar_finish PARAMS ((void *, long));
static void bar_set_params PARAMS ((const char *));

static struct progress_implementation implementations[] = {
  { "dot", dot_create, dot_update, dot_finish, dot_set_params },
  { "bar", bar_create, bar_update, bar_finish, bar_set_params }
};
static struct progress_implementation *current_impl;
static int current_impl_locked;

/* Progress implementation used by default.  Can be overriden in
   wgetrc or by the fallback one.  */

#define DEFAULT_PROGRESS_IMPLEMENTATION "bar"

/* Fallnback progress implementation should be something that works
   under all display types.  If you put something other than "dot"
   here, remember that bar_set_params tries to switch to this if we're
   not running on a TTY.  So changing this to "bar" could cause
   infloop.  */

#define FALLBACK_PROGRESS_IMPLEMENTATION "dot"

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
  int i, namelen;
  struct progress_implementation *pi = implementations;
  char *colon;

  if (!name)
    name = DEFAULT_PROGRESS_IMPLEMENTATION;

  colon = strchr (name, ':');
  namelen = colon ? colon - name : strlen (name);

  for (i = 0; i < ARRAY_SIZE (implementations); i++, pi++)
    if (!strncmp (pi->name, name, namelen))
      {
	current_impl = pi;
	current_impl_locked = 0;

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

static int output_redirected;

void
progress_schedule_redirect (void)
{
  output_redirected = 1;
}

/* Create a progress gauge.  INITIAL is the number of bytes the
   download starts from (zero if the download starts from scratch).
   TOTAL is the expected total number of bytes in this download.  If
   TOTAL is zero, it means that the download size is not known in
   advance.  */

void *
progress_create (long initial, long total)
{
  /* Check if the log status has changed under our feet. */
  if (output_redirected)
    {
      if (!current_impl_locked)
	set_progress_implementation (FALLBACK_PROGRESS_IMPLEMENTATION);
      output_redirected = 0;
    }

  return current_impl->create (initial, total);
}

/* Inform the progress gauge of newly received bytes.  DLTIME is the
   time in milliseconds since the beginning of the download.  */

void
progress_update (void *progress, long howmuch, long dltime)
{
  current_impl->update (progress, howmuch, dltime);
}

/* Tell the progress gauge to clean up.  Calling this will free the
   PROGRESS object, the further use of which is not allowed.  */

void
progress_finish (void *progress, long dltime)
{
  current_impl->finish (progress, dltime);
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
  long last_timer_value;
};

/* Dot-progress backend for progress_create. */

static void *
dot_create (long initial, long total)
{
  struct dot_progress *dp = xmalloc (sizeof (struct dot_progress));

  memset (dp, 0, sizeof (*dp));

  dp->initial_length = initial;
  dp->total_length   = total;

  if (dp->initial_length)
    {
      int dot_bytes = opt.dot_bytes;
      long row_bytes = opt.dot_bytes * opt.dots_in_line;

      int remainder = (int) (dp->initial_length % row_bytes);
      long skipped = dp->initial_length - remainder;

      if (skipped)
	{
	  int skipped_k = (int) (skipped / 1024); /* skipped amount in K */
	  int skipped_k_len = numdigit (skipped_k);
	  if (skipped_k_len < 5)
	    skipped_k_len = 5;

	  /* Align the [ skipping ... ] line with the dots.  To do
	     that, insert the number of spaces equal to the number of
	     digits in the skipped amount in K.  */
	  logprintf (LOG_VERBOSE, _("\n%*s[ skipping %dK ]"),
		     2 + skipped_k_len, "", skipped_k);
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
print_download_speed (struct dot_progress *dp, long bytes, long dltime)
{
  logprintf (LOG_VERBOSE, " %s",
	     retr_rate (bytes, dltime - dp->last_timer_value, 1));
  dp->last_timer_value = dltime;
}

/* Dot-progress backend for progress_update. */

static void
dot_update (void *progress, long howmuch, long dltime)
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
	  long row_qty = row_bytes;
	  if (dp->rows == dp->initial_length / row_bytes)
	    row_qty -= dp->initial_length % row_bytes;

	  ++dp->rows;
	  dp->dots = 0;

	  if (dp->total_length)
	    print_percentage (dp->rows * row_bytes, dp->total_length);
	  print_download_speed (dp, row_qty, dltime);
	}
    }

  log_set_flush (1);
}

/* Dot-progress backend for progress_finish. */

static void
dot_finish (void *progress, long dltime)
{
  struct dot_progress *dp = progress;
  int dot_bytes = opt.dot_bytes;
  long row_bytes = opt.dot_bytes * opt.dots_in_line;
  int i;

  log_set_flush (0);

  if (dp->dots == 0)
    logprintf (LOG_VERBOSE, "\n%5ldK", dp->rows * row_bytes / 1024);
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

  {
    long row_qty = dp->dots * dot_bytes + dp->accumulated;
    if (dp->rows == dp->initial_length / row_bytes)
      row_qty -= dp->initial_length % row_bytes;
    print_download_speed (dp, row_qty, dltime);
  }

  logputs (LOG_VERBOSE, "\n\n");
  log_set_flush (0);

  xfree (dp);
}

/* This function interprets the progress "parameters".  For example,
   if Wget is invoked with --progress=dot:mega, it will set the
   "dot-style" to "mega".  Valid styles are default, binary, mega, and
   giga.  */

static void
dot_set_params (const char *params)
{
  if (!params || !*params)
    params = opt.dot_style;

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

  long last_update;		/* time of the last screen update. */

  int width;			/* screen width we're using at the
				   time the progress gauge was
				   created.  this is different from
				   the screen_width global variable in
				   that the latter can be changed by a
				   signal. */
  char *buffer;			/* buffer where the bar "image" is
				   stored. */
  int tick;
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

  /* - 1 because we don't want to use the last screen column. */
  bp->width = screen_width - 1;
  /* + 1 for the terminating zero. */
  bp->buffer = xmalloc (bp->width + 1);

  logputs (LOG_VERBOSE, "\n");

  create_image (bp, 0);
  display_image (bp->buffer);

  return bp;
}

static void
bar_update (void *progress, long howmuch, long dltime)
{
  struct bar_progress *bp = progress;
  int force_update = 0;

  bp->count += howmuch;
  if (bp->total_length > 0
      && bp->count + bp->initial_length > bp->total_length)
    /* We could be downloading more than total_length, e.g. when the
       server sends an incorrect Content-Length header.  In that case,
       adjust bp->total_length to the new reality, so that the code in
       create_image() that depends on total size being smaller or
       equal to the expected size doesn't abort.  */
    bp->total_length = bp->count + bp->initial_length;

  if (screen_width - 1 != bp->width)
    {
      bp->width = screen_width - 1;
      bp->buffer = xrealloc (bp->buffer, bp->width + 1);
      force_update = 1;
    }

  if (dltime - bp->last_update < 200 && !force_update)
    /* Don't update more often than five times per second. */
    return;

  bp->last_update = dltime;

  create_image (bp, dltime);
  display_image (bp->buffer);
}

static void
bar_finish (void *progress, long dltime)
{
  struct bar_progress *bp = progress;

  if (dltime == 0)
    /* If the download was faster than the granularity of the timer,
       fake some output so that we don't get the ugly "----.--" rate
       at the download finish.  */
    dltime = 1;

  create_image (bp, dltime);
  display_image (bp->buffer);

  logputs (LOG_VERBOSE, "\n\n");

  xfree (bp->buffer);
  xfree (bp);
}

#define APPEND_LITERAL(s) do {			\
  memcpy (p, s, sizeof (s) - 1);		\
  p += sizeof (s) - 1;				\
} while (0)

#ifndef MAX
# define MAX(a, b) ((a) >= (b) ? (a) : (b))
#endif

static void
create_image (struct bar_progress *bp, long dltime)
{
  char *p = bp->buffer;
  long size = bp->initial_length + bp->count;

  char *size_legible = legible (size);
  int size_legible_len = strlen (size_legible);

  /* The progress bar should look like this:
     xx% [=======>             ] nn,nnn 12.34K/s ETA 00:00

     Calculate the geometry.  The idea is to assign as much room as
     possible to the progress bar.  The other idea is to never let
     things "jitter", i.e. pad elements that vary in size so that
     their variance does not affect the placement of other elements.
     It would be especially bad for the progress bar to be resized
     randomly.

     "xx% " or "100%"  - percentage               - 4 chars
     "[]"              - progress bar decorations - 2 chars
     " nnn,nnn,nnn"    - downloaded bytes         - 12 chars or very rarely more
     " 1012.56K/s"     - dl rate                  - 11 chars
     " ETA xx:xx:xx"   - ETA                      - 13 chars

     "=====>..."       - progress bar             - the rest
  */
  int dlbytes_size = 1 + MAX (size_legible_len, 11);
  int progress_size = bp->width - (4 + 2 + dlbytes_size + 11 + 13);

  if (progress_size < 5)
    progress_size = 0;

  /* "xx% " */
  if (bp->total_length > 0)
    {
      int percentage = (int)(100.0 * size / bp->total_length);

      assert (percentage <= 100);

      if (percentage < 100)
	sprintf (p, "%2d%% ", percentage);
      else
	strcpy (p, "100%");
      p += 4;
    }
  else
    APPEND_LITERAL ("    ");

  /* The progress bar: "[====>      ]" */
  if (progress_size && bp->total_length > 0)
    {
      double fraction = (double)size / bp->total_length;
      int dlsz = (int)(fraction * progress_size);
      char *begin;

      assert (dlsz <= progress_size);

      *p++ = '[';
      begin = p;

      if (dlsz > 0)
	{
	  /* Draw dlsz-1 '=' chars and one arrow char.  */
	  while (dlsz-- > 1)
	    *p++ = '=';
	  *p++ = '>';
	}

      while (p - begin < progress_size)
	*p++ = ' ';

      *p++ = ']';
    }
  else if (progress_size)
    {
      /* If we can't draw a real progress bar, then at least show
	 *something* to the user.  */
      int ind = bp->tick % (progress_size * 2 - 6);
      int i, pos;

      /* Make the star move in two directions. */
      if (ind < progress_size - 2)
	pos = ind + 1;
      else
	pos = progress_size - (ind - progress_size + 5);

      *p++ = '[';
      for (i = 0; i < progress_size; i++)
	{
	  if      (i == pos - 1) *p++ = '<';
	  else if (i == pos    ) *p++ = '=';
	  else if (i == pos + 1) *p++ = '>';
	  else
	    *p++ = ' ';
	}
      *p++ = ']';

      ++bp->tick;
    }

  /* " 234,567,890" */
  sprintf (p, " %-11s", legible (size));
  p += strlen (p);

  /* " 1012.45K/s" */
  if (dltime && bp->count)
    {
      static char *short_units[] = { "B/s", "K/s", "M/s", "G/s" };
      int units = 0;
      double dlrate = calc_rate (bp->count, dltime, &units);
      sprintf (p, " %7.2f%s", dlrate, short_units[units]);
      p += strlen (p);
    }
  else
    APPEND_LITERAL ("   --.--K/s");

  /* " ETA xx:xx:xx" */
  if (bp->total_length > 0 && bp->count > 0)
    {
      int eta, eta_hrs, eta_min, eta_sec;
      double tm_sofar = (double)dltime / 1000;
      long bytes_remaining = bp->total_length - size;

      eta = (int) (tm_sofar * bytes_remaining / bp->count);

      eta_hrs = eta / 3600, eta %= 3600;
      eta_min = eta / 60,   eta %= 60;
      eta_sec = eta;

      /* Pad until the end of screen.  The padding is dependent on the
	 hour value.  */
      if (eta_hrs == 0 || eta_hrs > 99)
	/* Hours not printed: pad with three spaces (two digits and
	   colon). */
	APPEND_LITERAL ("   ");
      else if (eta_hrs >= 10)
	/* Hours printed with one digit: pad with one space. */
	*p++ = ' ';
      else
	/* Hours printed with two digits: we're using maximum width,
	   don't pad. */
	;

      APPEND_LITERAL (" ETA ");

      if (eta_hrs > 99)
	/* Bogus value, probably due to a calculation overflow.  Print
	   something safe to avoid overstepping the buffer bounds. */
	sprintf (p, "--:--");
      else if (eta_hrs > 0)
	sprintf (p, "%d:%02d:%02d", eta_hrs, eta_min, eta_sec);
      else
	sprintf (p, "%02d:%02d", eta_min, eta_sec);
      p += strlen (p);
    }
  else if (bp->total_length > 0)
    APPEND_LITERAL ("    ETA --:--");

  assert (p - bp->buffer <= bp->width);

  while (p < bp->buffer + bp->width)
    *p++ = ' ';
  *p = '\0';
}

/* Print the contents of the buffer as a one-line ASCII "image" so
   that it can be overwritten next time.  */

static void
display_image (char *buf)
{
  logputs (LOG_VERBOSE, "\r");
  logputs (LOG_VERBOSE, buf);
}

static void
bar_set_params (const char *params)
{
  int sw;

  if (params
      && 0 == strcmp (params, "force"))
    current_impl_locked = 1;

  if ((opt.lfilename
#ifdef HAVE_ISATTY
       || !isatty (fileno (stderr))
#else
       1
#endif
       )
      && !current_impl_locked)
    {
      /* We're not printing to a TTY, so revert to the fallback
	 display.  #### We're recursively calling
	 set_progress_implementation here, which is slightly kludgy.
	 It would be nicer if we provided that function a return value
	 indicating a failure of some sort.  */
      set_progress_implementation (FALLBACK_PROGRESS_IMPLEMENTATION);
      return;
    }

  sw = determine_screen_width ();
  if (sw && sw >= MINIMUM_SCREEN_WIDTH)
    screen_width = sw;
}

#ifdef SIGWINCH
RETSIGTYPE
progress_handle_sigwinch (int sig)
{
  int sw = determine_screen_width ();
  if (sw && sw >= MINIMUM_SCREEN_WIDTH)
    screen_width = sw;
  signal (SIGWINCH, progress_handle_sigwinch);
}
#endif
