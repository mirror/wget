/* Portable timers.
   Copyright (C) 2005 Free Software Foundation, Inc.

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

/* This file implements "portable timers" (ptimers), objects that
   measure elapsed time using the primitives most appropriate for the
   underlying operating system.  The entry points are:

     ptimer_new     -- creates a timer.
     ptimer_reset   -- resets the timer's elapsed time to zero.
     ptimer_measure -- measure and return the time elapsed since
		       creation or last reset.
     ptimer_read    -- reads the last measured elapsed value.
     ptimer_destroy -- destroy the timer.
     ptimer_granularity -- returns the approximate granularity of the timers.

   Timers operate in milliseconds, but return floating point values
   that can be more precise.  For example, to measure the time it
   takes to run a loop, you can use something like:

     ptimer *tmr = ptimer_new ();
     while (...)
       ... loop ...
     double msecs = ptimer_measure ();
     printf ("The loop took %.2f ms\n", msecs);  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else  /* not HAVE_STRING_H */
# include <strings.h>
#endif /* not HAVE_STRING_H */
#include <sys/types.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <assert.h>

#include "wget.h"
#include "ptimer.h"

#ifndef errno
extern int errno;
#endif

/* Depending on the OS and availability of gettimeofday(), one and
   only one of PTIMER_WINDOWS, PTIMER_GETTIMEOFDAY, or PTIMER_TIME will
   be defined.

   Virtually all modern Unix systems will define PTIMER_GETTIMEOFDAY;
   Windows will use PTIMER_WINDOWS.  PTIMER_TIME is a catch-all method
   for non-Windows systems without gettimeofday, such as DOS or really
   old Unix-like systems.  */

#undef PTIMER_POSIX
#undef PTIMER_GETTIMEOFDAY
#undef PTIMER_TIME
#undef PTIMER_WINDOWS

#ifdef WINDOWS
# define PTIMER_WINDOWS		/* use Windows timers */
#else
# if _POSIX_TIMERS > 0
#  define PTIMER_POSIX		/* use POSIX timers (clock_gettime) */
# else
#  ifdef HAVE_GETTIMEOFDAY
#   define PTIMER_GETTIMEOFDAY	/* use gettimeofday */
#  else
#   define PTIMER_TIME
#  endif
# endif
#endif

/* The type ptimer_system_time holds system time. */

#ifdef PTIMER_POSIX
typedef struct timespec ptimer_system_time;
#endif

#ifdef PTIMER_GETTIMEOFDAY
typedef struct timeval ptimer_system_time;
#endif

#ifdef PTIMER_TIME
typedef time_t ptimer_system_time;
#endif

#ifdef PTIMER_WINDOWS
typedef union {
  DWORD lores;          /* In case GetTickCount is used */
  LARGE_INTEGER hires;  /* In case high-resolution timer is used */
} ptimer_system_time;
#endif

struct ptimer {
  /* Whether the start time has been set. */
  int initialized;

  /* The starting point in time which, subtracted from the current
     time, yields elapsed time. */
  ptimer_system_time start;

  /* The most recent elapsed time, calculated by ptimer_measure().
     Measured in milliseconds.  */
  double elapsed_last;

  /* Approximately, the time elapsed between the true start of the
     measurement and the time represented by START.  */
  double elapsed_pre_start;
};

#ifdef PTIMER_WINDOWS
/* Whether high-resolution timers are used.  Set by ptimer_initialize_once
   the first time ptimer_allocate is called. */
static int windows_hires_timers;

/* Frequency of high-resolution timers -- number of updates per
   millisecond.  Calculated the first time ptimer_allocate is called
   provided that high-resolution timers are available. */
static double windows_hires_msfreq;

/* The first time a timer is created, determine whether to use
   high-resolution timers. */

static void
ptimer_init (void)
{
  LARGE_INTEGER freq;
  freq.QuadPart = 0;
  QueryPerformanceFrequency (&freq);
  if (freq.QuadPart != 0)
    {
      windows_hires_timers = 1;
      windows_hires_msfreq = (double) freq.QuadPart / 1000.0;
    }
}
#define PTIMER_INIT_DEFINED
#endif /* PTIMER_WINDOWS */

#ifdef PTIMER_POSIX

/* clock_id to use for POSIX clocks.  This tries to use
   CLOCK_MONOTONIC where available, CLOCK_REALTIME otherwise.  */
static int posix_clock_id;

/* Resolution of the clock, in milliseconds. */
static double posix_resolution;

/* Check whether the monotonic clock is available, and retrieve POSIX
   timer resolution.  */

static void
ptimer_init (void)
{
  struct timespec res;

#if _POSIX_MONOTONIC_CLOCK > 0
  if (sysconf (_SC_MONOTONIC_CLOCK) > 0)
    posix_clock_id = CLOCK_MONOTONIC;
  else
#endif
    posix_clock_id = CLOCK_REALTIME;

  if (clock_getres (posix_clock_id, &res) < 0)
    {
      logprintf (LOG_NOTQUIET, _("Cannot read clock resolution: %s\n"),
		 strerror (errno));
      /* Assume 1 ms resolution */
      res.tv_sec = 0;
      res.tv_nsec = 1000000;
    }

  posix_resolution = res.tv_sec * 1000.0 + res.tv_nsec / 1000000.0;
  /* Guard against clock_getres reporting 0 resolution; after all, it
     can be used for division.  */
  if (posix_resolution == 0)
    posix_resolution = 1;
}
#define PTIMER_INIT_DEFINED
#endif

/* Allocate a timer.  Calling ptimer_read on the timer will return
   zero.  It is not legal to call ptimer_measure with a freshly
   allocated timer -- use ptimer_reset first.  */

struct ptimer *
ptimer_allocate (void)
{
  struct ptimer *wt;

#ifdef PTIMER_INIT_DEFINED
  static int init_done;
  if (!init_done)
    {
      init_done = 1;
      ptimer_init ();
    }
#endif

  wt = xnew0 (struct ptimer);
  return wt;
}

/* Allocate a new timer and reset it.  Return the new timer. */

struct ptimer *
ptimer_new (void)
{
  struct ptimer *wt = ptimer_allocate ();
  ptimer_reset (wt);
  return wt;
}

/* Free the resources associated with the timer.  Its further use is
   prohibited.  */

void
ptimer_destroy (struct ptimer *wt)
{
  xfree (wt);
}

/* Store system time to PST.  */

static void
ptimer_sys_set (ptimer_system_time *pst)
{
#ifdef PTIMER_POSIX
  clock_gettime (posix_clock_id, pst);
#endif

#ifdef PTIMER_GETTIMEOFDAY
  gettimeofday (pst, NULL);
#endif

#ifdef PTIMER_TIME
  time (pst);
#endif

#ifdef PTIMER_WINDOWS
  if (windows_hires_timers)
    {
      QueryPerformanceCounter (&pst->hires);
    }
  else
    {
      /* Where hires counters are not available, use GetTickCount rather
         GetSystemTime, because it is unaffected by clock skew and simpler
         to use.  Note that overflows don't affect us because we never use
         absolute values of the ticker, only the differences.  */
      pst->lores = GetTickCount ();
    }
#endif
}

/* Reset timer WT.  This establishes the starting point from which
   ptimer_read() will return the number of elapsed milliseconds.
   It is allowed to reset a previously used timer.  */

void
ptimer_reset (struct ptimer *wt)
{
  /* Set the start time to the current time. */
  ptimer_sys_set (&wt->start);
  wt->elapsed_last = 0;
  wt->elapsed_pre_start = 0;
  wt->initialized = 1;
}

static double
ptimer_diff (ptimer_system_time *pst1, ptimer_system_time *pst2)
{
#ifdef PTIMER_POSIX
  return ((pst1->tv_sec - pst2->tv_sec) * 1000.0
	  + (pst1->tv_nsec - pst2->tv_nsec) / 1000000.0);
#endif

#ifdef PTIMER_GETTIMEOFDAY
  return ((pst1->tv_sec - pst2->tv_sec) * 1000.0
	  + (pst1->tv_usec - pst2->tv_usec) / 1000.0);
#endif

#ifdef PTIMER_TIME
  return 1000 * (*pst1 - *pst2);
#endif

#ifdef WINDOWS
  if (using_hires_timers)
    return (pst1->hires.QuadPart - pst2->hires.QuadPart) / windows_hires_msfreq;
  else
    return pst1->lores - pst2->lores;
#endif
}

/* Measure the elapsed time since timer creation/reset and return it
   to the caller.  The value remains stored for further reads by
   ptimer_read.

   This function causes the timer to call gettimeofday (or time(),
   etc.) to update its idea of current time.  To get the elapsed
   interval in milliseconds, use ptimer_read.

   This function handles clock skew, i.e. time that moves backwards is
   ignored.  */

double
ptimer_measure (struct ptimer *wt)
{
  ptimer_system_time now;
  double elapsed;

  assert (wt->initialized != 0);

  ptimer_sys_set (&now);
  elapsed = wt->elapsed_pre_start + ptimer_diff (&now, &wt->start);

  /* Ideally we'd just return the difference between NOW and
     wt->start.  However, the system timer can be set back, and we
     could return a value smaller than when we were last called, even
     a negative value.  Both of these would confuse the callers, which
     expect us to return monotonically nondecreasing values.

     Therefore: if ELAPSED is smaller than its previous known value,
     we reset wt->start to the current time and effectively start
     measuring from this point.  But since we don't want the elapsed
     value to start from zero, we set elapsed_pre_start to the last
     elapsed time and increment all future calculations by that
     amount.

     This cannot happen with Windows and CLOCK_MONOTONIC timers, but
     the check is not expensive.  */

  if (elapsed < wt->elapsed_last)
    {
      wt->start = now;
      wt->elapsed_pre_start = wt->elapsed_last;
      elapsed = wt->elapsed_last;
    }

  wt->elapsed_last = elapsed;
  return elapsed;
}

/* Return the elapsed time in milliseconds between the last call to
   ptimer_reset and the last call to ptimer_update.  */

double
ptimer_read (const struct ptimer *wt)
{
  return wt->elapsed_last;
}

/* Return the assessed granularity of the timer implementation, in
   milliseconds.  This is used by code that tries to substitute a
   better value for timers that have returned zero.  */

double
ptimer_granularity (void)
{
#ifdef PTIMER_POSIX
  /* POSIX timers give us a way to measure granularity. */
  assert (posix_resolution != 0);
  return posix_resolution;
#endif

#ifdef PTIMER_GETTIMEOFDAY
  /* Granularity of gettimeofday varies wildly between architectures.
     However, it appears that on modern machines it tends to be better
     than 1ms.  Assume 100 usecs.  */
  return 0.1;
#endif

#ifdef PTIMER_TIME
  return 1000;
#endif

#ifdef PTIMER_WINDOWS
  if (windows_hires_timers)
    return 1.0 / windows_hires_msfreq;
  else
    return 10;  /* according to MSDN */
#endif
}
