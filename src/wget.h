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

/* This file contains some declarations that don't fit anywhere else.
   It also contains some useful includes, like the obnoxious TIME_H
   inclusion.  */

#ifndef WGET_H
#define WGET_H

/* Disable assertions when debug support is not compiled in. */
#ifndef ENABLE_DEBUG
# define NDEBUG
#endif

/* Define this if you want primitive but extensive malloc debugging.
   It will make Wget extremely slow, so only do it in development
   builds.  */
#undef DEBUG_MALLOC

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

/* No-op version of gettext, used for constant strings. */
#define N_(string) (string)

/* I18N NOTE: You will notice that none of the DEBUGP messages are
   marked as translatable.  This is intentional, for a few reasons:

   1) The debug messages are not meant for the users to look at, but
   for the developers; as such, they should be considered more like
   source comments than real program output.

   2) The messages are numerous, and yet they are random and frivolous
   ("double yuck!" and such).  There would be a lot of work with no
   gain.

   3) Finally, the debug messages are meant to be a clue for me to
   debug problems with Wget.  If I get them in a language I don't
   understand, debugging will become a new challenge of its own!  */


/* Include these, so random files need not include them.  */
#include "sysdep.h"
#include "options.h"
/* locale independent replacement for ctype.h */
#include "safe-ctype.h"

#define DO_NOTHING do {} while (0)

/* Print X if debugging is enabled; a no-op otherwise.  */
#ifdef ENABLE_DEBUG
# define DEBUGP(x) do { if (opt.debug) { debug_logprintf x; } } while (0)
#else  /* not ENABLE_DEBUG */
# define DEBUGP(x) DO_NOTHING
#endif /* not ENABLE_DEBUG */

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
void logflush PARAMS ((void));
void log_set_flush PARAMS ((int));
int log_set_save_context PARAMS ((int));

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

/* Convert an ASCII hex digit to the corresponding number between 0
   and 15.  X should be a hexadecimal digit that satisfies isxdigit;
   otherwise, the result is undefined.  */
#define XDIGIT_TO_NUM(x) ((x) < 'A' ? (x) - '0' : TOUPPER (x) - 'A' + 10)

/* Convert a sequence of ASCII hex digits X and Y to a number betewen
   0 and 255.  Uses XDIGIT_TO_NUM for conversion of individual
   digits.  */
#define X2DIGITS_TO_NUM(h1, h2) ((XDIGIT_TO_NUM (h1) << 4) + XDIGIT_TO_NUM (h2))

/* The reverse of the above: convert a number in the [0, 16) range to
   its ASCII representation in hex.  The A-F characters are in upper
   case.  */
#define XNUM_TO_DIGIT(x) ("0123456789ABCDEF"[x])

/* Like XNUM_TO_DIGIT, but generates lower-case characters. */
#define XNUM_TO_digit(x) ("0123456789abcdef"[x])

/* Returns the number of elements in an array with fixed
   initialization.  For example:

   static char a[] = "foo";     -- countof(a) == 4 (for terminating \0)

   int a[5] = {1, 2};           -- countof(a) == 5

   char *a[] = {                -- countof(a) == 3
     "foo", "bar", "baz"
   }; */
#define countof(array) (sizeof (array) / sizeof (*(array)))

#define alloca_array(type, size) ((type *) alloca ((size) * sizeof (type)))

/* Copy the data delimited with BEG and END to alloca-allocated
   storage, and zero-terminate it.  Arguments are evaluated only once,
   in the order BEG, END, PLACE.  */
#define BOUNDED_TO_ALLOCA(beg, end, place) do {	\
  const char *BTA_beg = (beg);			\
  int BTA_len = (end) - BTA_beg;		\
  char **BTA_dest = &(place);			\
  *BTA_dest = alloca (BTA_len + 1);		\
  memcpy (*BTA_dest, BTA_beg, BTA_len);		\
  (*BTA_dest)[BTA_len] = '\0';			\
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
  strcpy ((ptr), (str));			\
} while (0)

/* Generally useful if you want to avoid arbitrary size limits but
   don't need a full dynamic array.  Assumes that BASEVAR points to a
   malloced array of TYPE objects (or possibly a NULL pointer, if
   SIZEVAR is 0), with the total size stored in SIZEVAR.  This macro
   will realloc BASEVAR as necessary so that it can hold at least
   NEEDED_SIZE objects.  The reallocing is done by doubling, which
   ensures constant amortized time per element.  */
#define DO_REALLOC(basevar, sizevar, needed_size, type)	do			\
{										\
  /* Avoid side-effectualness.  */						\
  long do_realloc_needed_size = (needed_size);					\
  long do_realloc_newsize = 0;							\
  while ((sizevar) < (do_realloc_needed_size)) {				\
    do_realloc_newsize = 2*(sizevar);						\
    if (do_realloc_newsize < 32)						\
      do_realloc_newsize = 32;							\
    (sizevar) = do_realloc_newsize;						\
  }										\
  if (do_realloc_newsize)							\
    basevar = (type *)xrealloc (basevar, do_realloc_newsize * sizeof (type));	\
} while (0)

/* Free FOO if it is non-NULL.  */
#define FREE_MAYBE(foo) do { if (foo) xfree (foo); } while (0)

extern const char *exec_name;

/* Document type ("dt") flags */
enum
{
  TEXTHTML             = 0x0001,	/* document is of type text/html
                                           or application/xhtml+xml */
  RETROKF              = 0x0002,	/* retrieval was OK */
  HEAD_ONLY            = 0x0004,	/* only send the HEAD request */
  SEND_NOCACHE         = 0x0008,	/* send Pragma: no-cache directive */
  ACCEPTRANGES         = 0x0010,	/* Accept-ranges header was found */
  ADDED_HTML_EXTENSION = 0x0020         /* added ".html" extension due to -E */
};

/* Universal error type -- used almost everywhere.  Error reporting of
   this detail is not generally used or needed and should be
   simplified.  */
typedef enum
{
  NOCONERROR, HOSTERR, CONSOCKERR, CONERROR, CONSSLERR,
  CONREFUSED, NEWLOCATION, NOTENOUGHMEM, CONPORTERR,
  BINDERR, BINDOK, LISTENERR, ACCEPTERR, ACCEPTOK,
  CONCLOSED, FTPOK, FTPLOGINC, FTPLOGREFUSED, FTPPORTERR,
  FTPNSFOD, FTPRETROK, FTPUNKNOWNTYPE, FTPRERR,
  FTPREXC, FTPSRVERR, FTPRETRINT, FTPRESTFAIL, URLERROR,
  FOPENERR, FWRITEERR, HOK, HLEXC, HEOF,
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

#define CONNECT_ERROR(x) ((x) == ECONNREFUSED && !opt.retry_connrefused	\
			  ? CONREFUSED : CONERROR)

#endif /* WGET_H */
