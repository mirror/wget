/* Messages logging.
   Copyright (C) 1998, 2000 Free Software Foundation, Inc.

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
#ifdef HAVE_STDARG_H
# define WGET_USE_STDARG
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

/* The file descriptor used for logging. */

static FILE *logfp;

/* Whether logging is saved at all.  */
int save_log_p;

/* In the event of a hang-up, and if its output was on a TTY, Wget
   redirects its output to `wget-log'.

   For the convenience of reading this newly-created log, we store the
   last several lines ("screenful", hence the choice of 24) of Wget
   output, and dump them as context when the time comes.  */
#define SAVED_LOG_LINES 24

/* log_lines is a circular buffer that stores SAVED_LOG_LINES lines of
   output.  log_line_current always points to the position in the
   buffer that will be written to next.  When log_line_current reaches
   SAVED_LOG_LINES, it is reset to zero.

   The problem here is that we'd have to either (re)allocate and free
   strings all the time, or limit the lines to an arbitrary number of
   characters.  Instead of settling for either of these, we do both:
   if the line is smaller than a certain "usual" line length (80 chars
   by default), a preallocated memory is used.  The rare lines that
   are longer than 80 characters are malloc'ed and freed separately.
   This gives good performance with minimum memory consumption and
   fragmentation.  */

#define STATIC_LENGTH 80

static struct log_ln {
  char static_line[STATIC_LENGTH + 1]; /* statically allocated
                                          line. */
  char *malloced_line;		/* malloc'ed line, for lines of output
                                   larger than 80 characters. */
  char *content;		/* this points either to malloced_line
                                   or to the appropriate static_line.
                                   If this is NULL, it means the line
                                   has not yet been used. */
} log_lines[SAVED_LOG_LINES];

/* The current position in the ring. */
static int log_line_current = -1;

/* Whether the most recently written line was "trailing", i.e. did not
   finish with \n.  This is an important piece of information because
   the code is always careful to append data to trailing lines, rather
   than create new ones.  */
static int trailing_line;


#define ROT_ADVANCE(num) do {			\
  if (++num >= SAVED_LOG_LINES)			\
    num = 0;					\
} while (0)

/* Free the log line index with NUM.  This calls free on
   ln->malloced_line if it's non-NULL, and it also resets
   ln->malloced_line and ln->content to NULL.  */

static void
free_log_line (int num)
{
  struct log_ln *ln = log_lines + num;
  if (ln->malloced_line)
    {
      free (ln->malloced_line);
      ln->malloced_line = NULL;
    }
  ln->content = NULL;
}

/* Append bytes in the range [start, end) to one line in the log.  The
   region is not supposed to contain newlines, except for the last
   character (at end[-1]).  */

static void
saved_append_1 (const char *start, const char *end)
{
  int len = end - start;
  if (!len)
    return;

  /* First, check whether we need to append to an existing line or to
     create a new one.  */
  if (!trailing_line)
    {
      /* Create a new line. */
      struct log_ln *ln;

      if (log_line_current == -1)
	log_line_current = 0;
      else
	free_log_line (log_line_current);
      ln = log_lines + log_line_current;
      if (len > STATIC_LENGTH)
	{
	  ln->malloced_line = strdupdelim (start, end);
	  ln->content = ln->malloced_line;
	}
      else
	{
	  memcpy (ln->static_line, start, len);
	  ln->static_line[len] = '\0';
	  ln->content = ln->static_line;
	}
    }
  else
    {
      /* Append to the last line.  If the line is malloc'ed, we just
         call realloc and append the new string.  If the line is
         static, we have to check whether appending the new string
         would make it exceed STATIC_LENGTH characters, and if so,
         convert it to malloc(). */
      struct log_ln *ln = log_lines + log_line_current;
      if (ln->malloced_line)
	{
	  /* Resize malloc'ed line and append. */
	  int old_len = strlen (ln->malloced_line);
	  ln->malloced_line = xrealloc (ln->malloced_line, old_len + len + 1);
	  memcpy (ln->malloced_line + old_len, start, len);
	  ln->malloced_line[old_len + len] = '\0';
	  /* might have changed due to realloc */
	  ln->content = ln->malloced_line;
	}
      else
	{
	  int old_len = strlen (ln->static_line);
	  if (old_len + len > STATIC_LENGTH)
	    {
	      /* Allocate memory and concatenate the old and the new
                 contents. */
	      ln->malloced_line = xmalloc (old_len + len + 1);
	      memcpy (ln->malloced_line, ln->static_line,
		      old_len);
	      memcpy (ln->malloced_line + old_len, start, len);
	      ln->malloced_line[old_len + len] = '\0';
	      ln->content = ln->malloced_line;
	    }
	  else
	    {
	      /* Just append to the old, statically allocated
                 contents.  */
	      memcpy (ln->static_line + old_len, start, len);
	      ln->static_line[old_len + len] = '\0';
	      ln->content = ln->static_line;
	    }
	}
    }
  trailing_line = !(end[-1] == '\n');
  if (!trailing_line)
    ROT_ADVANCE (log_line_current);
}

/* Log the contents of S, as explained above.  If S consists of
   multiple lines, they are logged separately.  If S does not end with
   a newline, it will form a "trailing" line, to which things will get
   appended the next time this function is called.  */

static void
saved_append (const char *s)
{
  while (*s)
    {
      const char *end = strchr (s, '\n');
      if (!end)
	end = s + strlen (s);
      else
	++end;
      saved_append_1 (s, end);
      s = end;
    }
}

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
    /* This might happen if somebody calls a */	\
    /* log* function before log_init(). */	\
    logfp = stderr;				\
} while (0)


/* Log a literal string S.  The string is logged as-is, without a
   newline appended.  */

void
logputs (enum log_options o, const char *s)
{
  CHECK_VERBOSE (o);
  CANONICALIZE_LOGFP_OR_RETURN;

  fputs (s, logfp);
  if (!opt.no_flush)
    fflush (logfp);
  if (save_log_p)
    saved_append (s);
}

/* Print a message to the log.  A copy of message will be saved to
   saved_log, for later reusal by log_dump().  */

static void
logvprintf (enum log_options o, const char *fmt, va_list args)
{
  CHECK_VERBOSE (o);
  CANONICALIZE_LOGFP_OR_RETURN;

  /* Originally, we first used vfprintf(), and then checked whether
     the message needs to be stored with vsprintf().  However, Watcom
     C didn't like ARGS being used twice, so now we first vsprintf()
     the message, and then fwrite() it to LOGFP.  */

  if (!save_log_p)
    {
      /* In the simple case just call vfprintf(), to avoid needless
         allocation and games with vsnprintf(). */
      vfprintf (logfp, fmt, args);
    }
  else
    {
      char smallmsg[128];
      char *bigmsg = NULL;
      int available_size = sizeof (smallmsg);
      char *write_ptr = smallmsg;

      while (1)
	{
	  /* The GNU coding standards advise not to rely on the return
             value of sprintf().  However, vsnprintf() is a relatively
             new function missing from legacy systems.  Therefore it's
             safe to assume that its return value is meaningful.  On
             the systems where vsnprintf() is not available, we use
             the implementation from snprintf.c which does return the
             correct value.  */
	  int numwritten = vsnprintf (write_ptr, available_size, fmt, args);

	  /* vsnprintf() will not step over the limit given by
             available_size.  If it fails, it will return either -1
             (POSIX?) or the number of characters that *would have*
             been written, if there had been enough room.  In the
             former case, we double the available_size and malloc() to
             get a larger buffer, and try again.  In the latter case,
             we use the returned information to build a buffer of the
             correct size.  */

	  if (numwritten == -1)
	    {
	      /* Writing failed, and we don't know the needed size.
		 Try again with doubled size. */
	      available_size <<= 1;
	      bigmsg = xrealloc (bigmsg, available_size);
	      write_ptr = bigmsg;
	    }
	  else if (numwritten >= available_size)
	    {
	      /* Writing failed, but we know exactly how much space we
		 need. */
	      available_size = numwritten + 1;
	      bigmsg = xrealloc (bigmsg, available_size);
	      write_ptr = bigmsg;
	    }
	  else
	    {
	      /* Writing succeeded. */
	      break;
	    }
	}
      saved_append (write_ptr);
      fputs (write_ptr, logfp);
      if (bigmsg)
	free (bigmsg);
    }
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

/* Portability with pre-ANSI compilers makes these two functions look
   like @#%#@$@#$.  */

#ifdef WGET_USE_STDARG
void
logprintf (enum log_options o, const char *fmt, ...)
#else  /* not WGET_USE_STDARG */
void
logprintf (va_alist)
     va_dcl
#endif /* not WGET_USE_STDARG */
{
  va_list args;
#ifndef WGET_USE_STDARG
  enum log_options o;
  const char *fmt;
#endif

#ifdef WGET_USE_STDARG
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
#ifdef WGET_USE_STDARG
void
debug_logprintf (const char *fmt, ...)
#else  /* not WGET_USE_STDARG */
void
debug_logprintf (va_alist)
     va_dcl
#endif /* not WGET_USE_STDARG */
{
  if (opt.debug)
    {
      va_list args;
#ifndef WGET_USE_STDARG
      const char *fmt;
#endif

#ifdef WGET_USE_STDARG
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
      /* The log goes to stderr to avoid collisions with the output if
         the user specifies `-O -'.  #### Francois Pinard suggests
         that it's a better idea to print to stdout by default, and to
         stderr only if the user actually specifies `-O -'.  He says
         this inconsistency is harder to document, but is overall
         easier on the user.  */
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
  int i;

  if (logfp != stdin)
    fclose (logfp);
  save_log_p = 0;
  for (i = 0; i < SAVED_LOG_LINES; i++)
    free_log_line (i);
  log_line_current = -1;
  trailing_line = 0;
}

/* Dump saved lines to logfp. */
static void
log_dump (void)
{
  int num = log_line_current;
  FILE *fp = logfp;

  if (num == -1)
    return;
  if (trailing_line)
    ROT_ADVANCE (num);
  do
    {
      struct log_ln *ln = log_lines + num;
      if (ln->content)
	fputs (ln->content, fp);
      ROT_ADVANCE (num);
    }
  while (num != log_line_current);
  if (trailing_line)
    if (log_lines[log_line_current].content)
      fputs (log_lines[log_line_current].content, fp);
  fflush (fp);
}

/* Redirect output to `wget-log'.  MESSIJ is printed on stdout, and
   should contain *exactly one* `%s', which will be replaced by the
   log file name.

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
      /* Eek!  Opening the alternate log file has failed.  Nothing we
         can do but disable printing completely. */
      fprintf (stderr, "%s: %s: %s\n", exec_name, logfile, strerror (errno));
      /* `stdin' is magic to not print anything, ever.  */
      logfp = stdin;
    }
  fprintf (stderr, messij, logfile);
  free (logfile);
  /* Dump the previous screenful of output to LOGFILE.  */
  log_dump ();
  save_log_p = 0;
}
