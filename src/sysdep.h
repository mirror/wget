/* Dirty system-dependent hacks.
   Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.

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

/* This file is included by wget.h.  Random .c files need not include
   it.  */

#ifndef SYSDEP_H
#define SYSDEP_H

/* Must include these, so we can test for the missing stat macros and
   define them as necessary.  */
#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif

#ifdef WINDOWS
/* Windows doesn't have some functions.  Include mswindows.h so we get
   their declarations, as well as some additional declarations and
   macros.  This must come first, so it can set things up.  */
#include <mswindows.h>
#endif /* WINDOWS */

/* Watcom-specific stuff.  In practice this is probably specific to
   Windows, although Watcom exists under other OS's too.  For that
   reason, we keep this here.  */

#ifdef __WATCOMC__
/* Watcom has its own alloca() defined in malloc.h malloc.h needs to
   be included in the sources to prevent 'undefined external' errors
   at the link phase. */
# include <malloc.h>
/* io.h defines unlink() and chmod().  We put this here because it's
   way too obscure to require all the .c files to observe.  */
# include <io.h>
#endif /* __WATCOMC__ */

/* Needed for compilation under OS/2: */
#ifdef __EMX__
# ifndef S_ISLNK
#  define S_ISLNK(m) 0
# endif
# ifndef lstat
#  define lstat stat
# endif
#endif /* __EMX__ */

/* Reportedly, stat() macros are broken on some old systems.  Those
   systems will have to fend for themselves, as I will not introduce
   new code to handle it.

   However, I will add code for *missing* macros, and the following
   are reportedly missing from many systems.  */
#ifndef S_ISLNK
# define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#ifndef S_ISDIR
# define S_ISDIR(m) (((m) & (_S_IFMT)) == (_S_IFDIR))
#endif
#ifndef S_ISREG
# define S_ISREG(m) (((m) & _S_IFMT) == _S_IFREG)
#endif

/* Define a large integral type useful for storing large sizes that
   exceed sizes of one download, such as when printing the sum of all
   downloads.  Note that this has nothing to do with large file
   support, which determines the wgint type.  This should be as large
   as possible even on systems where when wgint is 32-bit; also,
   unlike wgint, this can be a floating point type.

   We use a 64-bit integral type where available, `double' otherwise.
   It's hard to print LARGE_INT's portably, but fortunately it's
   rarely needed.  */

#if SIZEOF_LONG >= 8
/* Long is large enough: use it.  */
typedef long LARGE_INT;
# define LARGE_INT_FMT "%ld"
#elif SIZEOF_LONG_LONG >= 8
/* Long long is large enough: use it.  */
typedef long long LARGE_INT;
# define LARGE_INT_FMT "%lld"
#elif _MSC_VER
/* Use __int64 under Windows. */
typedef __int64 LARGE_INT;
# define LARGE_INT_FMT "%I64"
#else
/* Large integer type unavailable; fake it with `double'.  */
typedef double LARGE_INT;
# define LARGE_INT_FMT "%.0f"
#endif

/* Under Windows we #define struct_stat to struct _stati64. */
#ifndef struct_stat
# define struct_stat struct stat
#endif

/* For CHAR_BIT, LONG_MAX, etc. */
#include <limits.h>

#ifndef CHAR_BIT
# define CHAR_BIT 8
#endif

/* Used by wget.h to define SIZEOF_WGINT. */
#ifndef LONG_MAX
# define LONG_MAX ((long) ~((unsigned long)1 << (CHAR_BIT * sizeof (long) - 1)))
#endif
#ifndef LLONG_MAX
# define LLONG_MAX ((long long) ~((unsigned long long)1 << (CHAR_BIT * sizeof (long long) - 1)))
#endif

/* These are defined in cmpt.c if missing, so we must declare
   them.  */
#ifndef HAVE_STRCASECMP
int strcasecmp ();
#endif
#ifndef HAVE_STRNCASECMP
int strncasecmp ();
#endif
#ifndef HAVE_STRPTIME
char *strptime ();
#endif

/* These are defined in snprintf.c.  It would be nice to have an
   snprintf.h, though.  */
#ifndef HAVE_SNPRINTF
int snprintf ();
#endif
#ifndef HAVE_VSNPRINTF
int vsnprintf ();
#endif

/* Some systems (Linux libc5, "NCR MP-RAS 3.0", and others) don't
   provide MAP_FAILED, a symbolic constant for the value returned by
   mmap() when it doesn't work.  Usually, this constant should be -1.
   This only makes sense for files that use mmap() and include
   sys/mman.h *before* sysdep.h, but doesn't hurt others.  */

#ifndef MAP_FAILED
# define MAP_FAILED ((void *) -1)
#endif

/* Enable system fnmatch only on systems where fnmatch.h is usable and
   which are known to have a non-broken fnmatch implementation.
   Currently those include glibc-based systems and Solaris.  One could
   add more, but fnmatch is not that large, so it might be better to
   play it safe.  */
#ifdef HAVE_WORKING_FNMATCH_H
# if defined __GLIBC__ && __GLIBC__ >= 2
#  define SYSTEM_FNMATCH
# endif
# ifdef solaris
#  define SYSTEM_FNMATCH
# endif
#endif /* HAVE_WORKING_FNMATCH_H */

#ifdef SYSTEM_FNMATCH
# include <fnmatch.h>
#else  /* not SYSTEM_FNMATCH */
/* Define fnmatch flags.  Undef them first to avoid warnings in case
   an evil library include chose to include system fnmatch.h.  */
# undef FNM_PATHNAME
# undef FNM_NOESCAPE
# undef FNM_PERIOD
# undef FNM_NOMATCH

# define FNM_PATHNAME	(1 << 0) /* No wildcard can ever match `/'.  */
# define FNM_NOESCAPE	(1 << 1) /* Backslashes don't quote special chars.  */
# define FNM_PERIOD	(1 << 2) /* Leading `.' is matched only explicitly.  */
# define FNM_NOMATCH	1

/* Declare the function minimally. */
int fnmatch ();
#endif

/* Provide sig_atomic_t if the system doesn't.  */
#ifndef HAVE_SIG_ATOMIC_T
typedef int sig_atomic_t;
#endif

/* Provide uint32_t on the platforms that don't define it.  Although
   most code should be agnostic about integer sizes, some code really
   does need a 32-bit integral type.  Such code should use uint32_t.
   (The exception is gnu-md5.[ch], which uses its own detection for
   portability across platforms.)  */

#ifndef HAVE_UINT32_T
# if SIZEOF_INT == 4
typedef unsigned int uint32_t;
# else
#  if SIZEOF_LONG == 4
typedef unsigned long uint32_t;
#  else
#   if SIZEOF_SHORT == 4
typedef unsigned short uint32_t;
#   else
 #error "Cannot determine a 32-bit unsigned integer type"
#   endif
#  endif
# endif
#endif

#endif /* SYSDEP_H */
