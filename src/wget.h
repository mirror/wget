/* Miscellaneous declarations.
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

/* This file contains some declarations that don't fit anywhere else.
   It also contains some useful includes, like the obnoxious TIME_H
   inclusion.  */

#ifndef WGET_H
#define WGET_H

#ifndef DEBUG
# define NDEBUG /* To kill off assertions */
#endif /* not DEBUG */

#ifndef PARAMS
# if PROTOTYPES
#  define PARAMS(args) args
# else
#  define PARAMS(args) ()
# endif
#endif

/* `gettext (FOO)' is long to write, so we use `_(FOO)'.  If NLS is
   unavailable, _(STRING) simply returns STRING.  */
#ifdef HAVE_NLS
# define _(string) gettext (string)
# ifdef HAVE_LIBINTL_H
#  include <libintl.h>
# endif /* HAVE_LIBINTL_H */
#else  /* not HAVE_NLS */
# define _(string) string
#endif /* not HAVE_NLS */

/* I18N NOTE: You will notice that none of the DEBUG messages are
   marked as translatable.  This is intentional, for a few reasons:

   1) The debug messages are not meant for the users to look at, but
   for the developers; as such, they should be considered more like
   source comments than real program output.

   2) The messages are numerous, and yet they are random and frivolous
   ("double yuck!" and such).  There would be a lot of work with no
   gain.

   3) Finally, the debug messages are meant to be a clue for me to
   debug problems with Wget.  If I get them in a language I don't
   understand, debugging will become a new challenge of its own!  :-) */


/* Include these, so random files need not include them.  */
#include "sysdep.h"
#include "options.h"

#define DO_NOTHING do {} while (0)

/* Print X if debugging is enabled; a no-op otherwise.  */
#ifdef DEBUG
# define DEBUGP(x) do { debug_logprintf x; } while (0)
#else  /* not DEBUG */
# define DEBUGP(x) DO_NOTHING
#endif /* not DEBUG */

/* Make gcc check for the format of logmsg() and debug_logmsg().  */
#ifdef __GNUC__
# define GCC_FORMAT_ATTR(a, b) __attribute__ ((format (printf, a, b)))
#else  /* not __GNUC__ */
# define GCC_FORMAT_ATTR(a, b)
#endif /* not __GNUC__ */

/* These are from log.c, but they are used everywhere, so we declare
   them here.  */
enum log_options { LOG_VERBOSE, LOG_NOTQUIET, LOG_NONVERBOSE, LOG_ALWAYS };

void logprintf PARAMS ((enum log_options, const char *, ...))
     GCC_FORMAT_ATTR (2, 3);
void debug_logprintf PARAMS ((const char *, ...)) GCC_FORMAT_ATTR (1, 2);
void logputs PARAMS ((enum log_options, const char *));

/* Defined in `utils.c', but used literally everywhere.  */
void *xmalloc PARAMS ((size_t));
void *xrealloc PARAMS ((void *, size_t));
char *xstrdup PARAMS ((const char *));

/* #### Find a better place for this.  */
/* The log file to which Wget writes to after HUP.  */
#define DEFAULT_LOGFILE "wget-log"

#define MD5_HASHLEN 16

/* Useful macros used across the code: */

/* Is the string a hpyhen-only?  */
#define HYPHENP(x) (*(x) == '-' && !*((x) + 1))

/* The smaller value of the two.  */
#define MINVAL(x, y) ((x) < (y) ? (x) : (y))

/* ASCII char -> HEX digit */
#define ASC2HEXD(x) (((x) >= '0' && (x) <= '9') ?               \
		     ((x) - '0') : (toupper(x) - 'A' + 10))

/* HEX digit -> ASCII char */
#define HEXD2ASC(x) (((x) < 10) ? ((x) + '0') : ((x) - 10 + 'A'))

#define ARRAY_SIZE(array) (sizeof (array) / sizeof (*(array)))

/* Note that this much more elegant definition cannot be used:

   #define STRDUP_ALLOCA(str) (strcpy ((char *)alloca (strlen (str) + 1), str))

   This is because some compilers don't handle alloca() as argument to
   function correctly.  Gcc under Intel has been reported to offend in
   this case.  */

#define STRDUP_ALLOCA(ptr, str) do {		\
  (ptr) = (char *)alloca (strlen (str) + 1);	\
  strcpy (ptr, str);				\
} while (0)

#define ALLOCA_ARRAY(type, len) ((type *) alloca ((len) * sizeof (type)))

#define XREALLOC_ARRAY(ptr, type, len)					\
     ((void) (ptr = (type *) xrealloc (ptr, (len) * sizeof (type))))

/* Generally useful if you want to avoid arbitrary size limits but
   don't need a full dynamic array.  Assumes that BASEVAR points to a
   malloced array of TYPE objects (or possibly a NULL pointer, if
   SIZEVAR is 0), with the total size stored in SIZEVAR.  This macro
   will realloc BASEVAR as necessary so that it can hold at least
   NEEDED_SIZE objects.  The reallocing is done by doubling, which
   ensures constant amortized time per element.  */
#define DO_REALLOC(basevar, sizevar, needed_size, type)	do	\
{								\
  /* Avoid side-effectualness.  */				\
  long do_realloc_needed_size = (needed_size);			\
  long do_realloc_newsize = 0;					\
  while ((sizevar) < (do_realloc_needed_size)) {		\
    do_realloc_newsize = 2*(sizevar);				\
    if (do_realloc_newsize < 32)				\
      do_realloc_newsize = 32;					\
    (sizevar) = do_realloc_newsize;				\
  }								\
  if (do_realloc_newsize)					\
    XREALLOC_ARRAY (basevar, type, do_realloc_newsize);		\
} while (0)

/* Free FOO if it is non-NULL.  */
#define FREE_MAYBE(foo) do { if (foo) free (foo); } while (0)

/* #### Hack: OPTIONS_DEFINED_HERE is defined in main.c.  */
#ifndef OPTIONS_DEFINED_HERE
extern const char *exec_name;
#endif


/* Document-type flags */
enum
{
  TEXTHTML      = 0x0001,	/* document is of type text/html */
  RETROKF       = 0x0002,	/* retrieval was OK */
  HEAD_ONLY     = 0x0004,	/* only send the HEAD request */
  SEND_NOCACHE  = 0x0008,	/* send Pragma: no-cache directive */
  ACCEPTRANGES  = 0x0010	/* Accept-ranges header was found */
};

/* Universal error type -- used almost everywhere.
   This is, of course, utter crock.  */
typedef enum
{
  NOCONERROR, HOSTERR, CONSOCKERR, CONERROR,
  CONREFUSED, NEWLOCATION, NOTENOUGHMEM, CONPORTERR,
  BINDERR, BINDOK, LISTENERR, ACCEPTERR, ACCEPTOK,
  CONCLOSED, FTPOK, FTPLOGINC, FTPLOGREFUSED, FTPPORTERR,
  FTPNSFOD, FTPRETROK, FTPUNKNOWNTYPE, FTPRERR,
  FTPREXC, FTPSRVERR, FTPRETRINT, FTPRESTFAIL,
  URLOK, URLHTTP, URLFTP, URLFILE, URLUNKNOWN, URLBADPORT,
  URLBADHOST, FOPENERR, FWRITEERR, HOK, HLEXC, HEOF,
  HERR, RETROK, RECLEVELEXC, FTPACCDENIED, WRONGCODE,
  FTPINVPASV, FTPNOPASV,
  RETRFINISHED, READERR, TRYLIMEXC, URLBADPATTERN,
  FILEBADFILE, RANGEERR, RETRBADPATTERN, RETNOTSUP,
  ROBOTSOK, NOROBOTS, PROXERR, AUTHFAILED, QUOTEXC, WRITEFAILED
} uerr_t;

#endif /* WGET_H */
