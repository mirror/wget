/* Miscellaneous declarations.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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
/* locale independent replacement for ctype.h */
#include "safe-ctype.h"

#define DO_NOTHING do {} while (0)

/* Print X if debugging is enabled; a no-op otherwise.  */
#ifdef DEBUG
# define DEBUGP(x) do { if (opt.debug) { debug_logprintf x; } } while (0)
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

#ifdef HAVE_STDARG_H
void logprintf PARAMS ((enum log_options, const char *, ...))
     GCC_FORMAT_ATTR (2, 3);
void debug_logprintf PARAMS ((const char *, ...)) GCC_FORMAT_ATTR (1, 2);
#else  /* not HAVE_STDARG_H */
void logprintf ();
void debug_logprintf ();
#endif /* not HAVE_STDARG_H */
void logputs PARAMS ((enum log_options, const char *));

/* Defined in `utils.c', but used literally everywhere.  */
#ifndef DEBUG_MALLOC

#define xmalloc  xmalloc_real
#define xrealloc xrealloc_real
#define xstrdup  xstrdup_real
#define xfree    free

void *xmalloc_real PARAMS ((size_t));
void *xrealloc_real PARAMS ((void *, size_t));
char *xstrdup_real PARAMS ((const char *));

#else  /* DEBUG_MALLOC */

#define xmalloc(s)     xmalloc_debug (s, __FILE__, __LINE__)
#define xfree(p)       xfree_debug (p, __FILE__, __LINE__)
#define xrealloc(p, s) xrealloc_debug (p, s, __FILE__, __LINE__)
#define xstrdup(p)     xstrdup_debug (p, __FILE__, __LINE__)

void *xmalloc_debug PARAMS ((size_t, const char *, int));
void xfree_debug PARAMS ((void *, const char *, int));
void *xrealloc_debug PARAMS ((void *, size_t, const char *, int));
char *xstrdup_debug PARAMS ((const char *, const char *, int));

#endif /* DEBUG_MALLOC */

/* #### Find a better place for this.  */
/* The log file to which Wget writes to after HUP.  */
#define DEFAULT_LOGFILE "wget-log"

#define MD5_HASHLEN 16

/* Useful macros used across the code: */

/* Is the string a hpyhen-only?  */
#define HYPHENP(x) (*(x) == '-' && !*((x) + 1))

/* The smaller value of the two.  */
#define MINVAL(x, y) ((x) < (y) ? (x) : (y))

/* Convert the ASCII character X to a hex-digit.  X should be between
   '0' and '9', or between 'A' and 'F', or between 'a' and 'f'.  The
   result is a number between 0 and 15.  If X is not a hexadecimal
   digit character, the result is undefined.  */
#define XCHAR_TO_XDIGIT(x)			\
  (((x) >= '0' && (x) <= '9') ?			\
   ((x) - '0') : (TOUPPER(x) - 'A' + 10))

/* The reverse of the above: convert a HEX digit in the [0, 15] range
   to an ASCII character representing it.  The A-F characters are
   always in upper case.  */
#define XDIGIT_TO_XCHAR(x) (((x) < 10) ? ((x) + '0') : ((x) - 10 + 'A'))

/* Like XDIGIT_TO_XCHAR, but produce a lower-case char. */
#define XDIGIT_TO_xchar(x) (((x) < 10) ? ((x) + '0') : ((x) - 10 + 'a'))

#define ARRAY_SIZE(array) (sizeof (array) / sizeof (*(array)))

/* Copy the data delimited with BEG and END to alloca-allocated
   storage, and zero-terminate it.  BEG and END are evaluated only
   once, in that order.  */
#define BOUNDED_TO_ALLOCA(beg, end, place) do {	\
  const char *DTA_beg = (beg);			\
  int DTA_len = (end) - DTA_beg;		\
  place = alloca (DTA_len + 1);			\
  memcpy (place, DTA_beg, DTA_len);		\
  place[DTA_len] = '\0';			\
} while (0)

/* Return non-zero if string bounded between BEG and END is equal to
   STRING_LITERAL.  The comparison is case-sensitive.  */
#define BOUNDED_EQUAL(beg, end, string_literal)	\
  ((end) - (beg) == sizeof (string_literal) - 1	\
   && !memcmp ((beg), (string_literal),		\
	       sizeof (string_literal) - 1))

/* The same as above, except the comparison is case-insensitive. */
#define BOUNDED_EQUAL_NO_CASE(beg, end, string_literal)	\
  ((end) - (beg) == sizeof (string_literal) - 1		\
   && !strncasecmp ((beg), (string_literal),		\
	            sizeof (string_literal) - 1))

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

/* Use this for small stack-allocated memory chunks that might grow.
   The initial array is created using alloca(), and this macro
   requests it to grow.  If the needed size is larger than the array,
   this macro will use malloc to allocate it to new size, and copy the
   old contents.  After that, successive invocations behave just like
   DO_REALLOC.  */
#define DO_REALLOC_FROM_ALLOCA(basevar, sizevar, needed_size, allocap, type) do	\
{										\
  /* Avoid side-effectualness.  */						\
  long do_realloc_needed_size = (needed_size);					\
  long do_realloc_newsize = 0;							\
  while ((sizevar) < (do_realloc_needed_size)) {				\
    do_realloc_newsize = 2*(sizevar);						\
    if (do_realloc_newsize < 16)						\
      do_realloc_newsize = 16;							\
    (sizevar) = do_realloc_newsize;						\
  }										\
  if (do_realloc_newsize)							\
    {										\
      if (!allocap)								\
	XREALLOC_ARRAY (basevar, type, do_realloc_newsize);			\
      else									\
	{									\
	  void *drfa_new_basevar = xmalloc (do_realloc_newsize);		\
	  memcpy (drfa_new_basevar, basevar, sizevar);				\
	  (basevar) = drfa_new_basevar;						\
	  allocap = 0;								\
	}									\
    }										\
} while (0)

/* Free FOO if it is non-NULL.  */
#define FREE_MAYBE(foo) do { if (foo) xfree (foo); } while (0)

/* #### Hack: OPTIONS_DEFINED_HERE is defined in main.c.  */
/* [Is this weird hack really necessary on any compilers?  No ANSI C compiler
    should complain about "extern const char *exec_name;" followed by
    "const char *exec_name;".  Are we doing this for K&R compilers, or...??
    -- Dan Harkless <wget@harkless.org>] */
#ifndef OPTIONS_DEFINED_HERE
extern const char *exec_name;
#endif


/* Document type ("dt") flags */
enum
{
  TEXTHTML             = 0x0001,	/* document is of type text/html */
  RETROKF              = 0x0002,	/* retrieval was OK */
  HEAD_ONLY            = 0x0004,	/* only send the HEAD request */
  SEND_NOCACHE         = 0x0008,	/* send Pragma: no-cache directive */
  ACCEPTRANGES         = 0x0010,	/* Accept-ranges header was found */
  ADDED_HTML_EXTENSION = 0x0020         /* added ".html" extension due to -E */
};

/* Universal error type -- used almost everywhere.
   This is, of course, utter crock.  */
typedef enum
{
  NOCONERROR, HOSTERR, CONSOCKERR, CONERROR, CONSSLERR,
  CONREFUSED, NEWLOCATION, NOTENOUGHMEM, CONPORTERR,
  BINDERR, BINDOK, LISTENERR, ACCEPTERR, ACCEPTOK,
  CONCLOSED, FTPOK, FTPLOGINC, FTPLOGREFUSED, FTPPORTERR,
  FTPNSFOD, FTPRETROK, FTPUNKNOWNTYPE, FTPRERR,
  FTPREXC, FTPSRVERR, FTPRETRINT, FTPRESTFAIL, URLHTTPS,
  URLOK, URLHTTP, URLFTP, URLFILE, URLUNKNOWN, URLBADPORT,
  URLBADHOST, FOPENERR, FWRITEERR, HOK, HLEXC, HEOF,
  HERR, RETROK, RECLEVELEXC, FTPACCDENIED, WRONGCODE,
  FTPINVPASV, FTPNOPASV,
  CONTNOTSUPPORTED, RETRUNNEEDED, RETRFINISHED, READERR, TRYLIMEXC,
  URLBADPATTERN, FILEBADFILE, RANGEERR, RETRBADPATTERN,
  RETNOTSUP, ROBOTSOK, NOROBOTS, PROXERR, AUTHFAILED,
  QUOTEXC, WRITEFAILED,
  SSLERRCERTFILE,SSLERRCERTKEY,SSLERRCTXCREATE
} uerr_t;

typedef unsigned char  boolean;
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif

/* So we can say strcmp(a, b) == EQ rather than strcmp(a, b) == 0 or
   the really awful !strcmp(a, b). */
#define EQ 0

/* For most options, 0 means no limits, but with -p in the picture, that causes
   a problem on the maximum recursion depth variable.  To retain backwards
   compatibility we allow users to consider "0" to be synonymous with "inf" for
   -l, but internally infinite recursion is specified by -1 and 0 means to only
   retrieve the requisites of a single document. */
#define INFINITE_RECURSION -1

#endif /* WGET_H */
