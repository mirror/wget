/* Messages logging.
   Copyright (C) 1998 Free Software Foundation, Inc.

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
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <stdlib.h>
#if defined(__STDC__) && defined(HAVE_STDARG_H)
/* If we have __STDC__ and stdarg.h, we'll assume it's an ANSI system.  */
# define USE_STDARG
# include <stdarg.h>
#else
# include <varargs.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <assert.h>
#include <errno.h>

#include "wget.h"
#include "utils.h"

#ifndef errno
extern int errno;
#endif

/* We expect no message passed to logprintf() to be bigger than this.
   Before a message is printed, we make sure that at least this much
   room is left for printing it.  */
#define SAVED_LOG_MAXMSG 32768

/* Maximum allowed growing size.  */
#define SAVED_LOG_MAXSIZE (10 * 1L << 20)

static char *saved_log;
/* Size of the current log.  */
static long saved_log_size;
/* Offset into the log where we are about to print (size of the
   used-up part of SAVED_LOG).  */
static long saved_log_offset;
/* Whether logging is saved at all.  */
int save_log_p;

static FILE *logfp;

/* Check X against opt.verbose and opt.quiet.  The semantics is as
   follows:

   * LOG_ALWAYS - print the message unconditionally;

   * LOG_NOTQUIET - print the message if opt.quiet is non-zero;

   * LOG_NONVERBOSE - print the message if opt.verbose is zero;

   * LOG_VERBOSE - print the message if opt.verbose is non-zero.  */
#define CHECK_VERBOSE(x)			\
  switch (x)					\
    {						\
    case LOG_ALWAYS:				\
      break;					\
    case LOG_NOTQUIET:				\
      if (opt.quiet)				\
	return;					\
      break;					\
    case LOG_NONVERBOSE:			\
      if (opt.verbose || opt.quiet)		\
	return;					\
      break;					\
    case LOG_VERBOSE:				\
      if (!opt.verbose)				\
	return;					\
    }

#define CANONICALIZE_LOGFP_OR_RETURN do {	\
  if (logfp == stdin)				\
    return;					\
  else if (!logfp)				\
    /* #### Should this ever happen?  */	\
    logfp = stderr;				\
} while (0)


void
logputs (enum log_options o, const char *s)
{
  CHECK_VERBOSE (o);
  CANONICALIZE_LOGFP_OR_RETURN;

  fputs (s, logfp);
  if (!opt.no_flush)
    fflush (logfp);

  if (save_log_p && saved_log_size < SAVED_LOG_MAXSIZE)
    {
      int len = strlen (s);

      /* Increase size of SAVED_LOG exponentially.  */
      DO_REALLOC (saved_log, saved_log_size,
		  saved_log_offset + len + 1, char);
      memcpy (saved_log + saved_log_offset, s, len + 1);
      saved_log_offset += len;
    }
}

/* Print a message to the log file logfp.  If logfp is NULL, print to
   stderr.  If logfp is stdin, don't print at all.  A copy of message
   will be saved to saved_log, for later reusal by dump_log().  */
static void
logvprintf (enum log_options o, const char *fmt, va_list args)
{
  CHECK_VERBOSE (o);
  CANONICALIZE_LOGFP_OR_RETURN;

  /* Originally, we first used vfprintf(), and then checked whether
     the message needs to be stored with vsprintf().  However, Watcom
     C didn't like ARGS being used twice, so now we first vsprintf()
     the message, and then fwrite() it to LOGFP.  */
  if (save_log_p && saved_log_size < SAVED_LOG_MAXSIZE)
    {
      int len;
      /* Increase size of `saved_log' exponentially.  */
      DO_REALLOC (saved_log, saved_log_size,
		  saved_log_offset + SAVED_LOG_MAXMSG, char);
      /* Print the message to the log saver...  */
#ifdef HAVE_VSNPRINTF
      vsnprintf (saved_log + saved_log_offset, SAVED_LOG_MAXMSG, fmt, args);
#else  /* not HAVE_VSNPRINTF */
      vsprintf (saved_log + saved_log_offset, fmt, args);
#endif /* not HAVE_VSNPRINTF */
      /* ...and then dump it to LOGFP.  */
      len = strlen (saved_log + saved_log_offset);
      fwrite (saved_log + saved_log_offset, len, 1, logfp);
      saved_log_offset += len;
      /* If we ran off the limits and corrupted something, bail out
	 immediately.  */
      assert (saved_log_size >= saved_log_offset);
    }
  else
    vfprintf (logfp, fmt, args);

  if (!opt.no_flush)
    fflush (logfp);
}

/* Flush LOGFP.  */
void
logflush (void)
{
  CANONICALIZE_LOGFP_OR_RETURN;
  fflush (logfp);
}

/* Portability makes these two functions look like @#%#@$@#$.  */

#ifdef USE_STDARG
void
logprintf (enum log_options o, const char *fmt, ...)
#else  /* not USE_STDARG */
void
logprintf (va_alist)
     va_dcl
#endif /* not USE_STDARG */
{
  va_list args;
#ifndef USE_STDARG
  enum log_options o;
  const char *fmt;
#endif

#ifdef USE_STDARG
  va_start (args, fmt);
#else
  va_start (args);
  o = va_arg (args, enum log_options);
  fmt = va_arg (args, char *);
#endif
  logvprintf (o, fmt, args);
  va_end (args);
}

#ifdef DEBUG
/* The same as logprintf(), but does anything only if opt.debug is
   non-zero.  */
#ifdef USE_STDARG
void
debug_logprintf (const char *fmt, ...)
#else  /* not USE_STDARG */
void
debug_logprintf (va_alist)
     va_dcl
#endif /* not USE_STDARG */
{
  if (opt.debug)
    {
      va_list args;
#ifndef USE_STDARG
      const char *fmt;
#endif

#ifdef USE_STDARG
      va_start (args, fmt);
#else
      va_start (args);
      fmt = va_arg (args, char *);
#endif
      logvprintf (LOG_ALWAYS, fmt, args);
      va_end (args);
    }
}
#endif /* DEBUG */

/* Open FILE and set up a logging stream.  If FILE cannot be opened,
   exit with status of 1.  */
void
log_init (const char *file, int appendp)
{
  if (file)
    {
      logfp = fopen (file, appendp ? "a" : "w");
      if (!logfp)
	{
	  perror (opt.lfilename);
	  exit (1);
	}
    }
  else
    {
      logfp = stderr;
      /* If the output is a TTY, enable logging, which will make Wget
         remember all the printed messages, to be able to dump them to
         a log file in case SIGHUP or SIGUSR1 is received (or
         Ctrl+Break is pressed under Windows).  */
      if (1
#ifdef HAVE_ISATTY
	  && isatty (fileno (logfp))
#endif
	  )
	{
	  save_log_p = 1;
	}
    }
}

/* Close LOGFP, inhibit further logging and free the memory associated
   with it.  */
void
log_close (void)
{
  fclose (logfp);
  save_log_p = 0;
  FREE_MAYBE (saved_log);
  saved_log = NULL;
  saved_log_size = saved_log_offset = 0;
}

/* Dump SAVED_LOG using logprintf(), but quit further logging to memory.
   Also, free the memory occupied by saved_log.  */
static void
log_dump (void)
{
  save_log_p = 0;
  if (!saved_log)
    return;
  logputs (LOG_ALWAYS, saved_log);
  free (saved_log);
  saved_log = NULL;
  saved_log_size = saved_log_offset = 0;
}

/* Redirect output to `wget-log' if opt.lfile is stdout.  MESSIJ is
   printed on stdout, and should contain *exactly one* `%s', which
   will be replaced by the log file name.

   If logging was not enabled, MESSIJ will not be printed.  */
void
redirect_output (const char *messij)
{
  char *logfile;

  if (!save_log_p)
    return;

  logfile = unique_name (DEFAULT_LOGFILE);
  logfp = fopen (logfile, "w");
  if (!logfp)
    {
      printf ("%s: %s: %s\n", exec_name, logfile, strerror (errno));
      /* `stdin' is magic to not print anything.  */
      logfp = stdin;
    }
  printf (messij, logfile);
  free (logfile);
  /* Dump all the previous messages to LOGFILE.  */
  log_dump ();
}
