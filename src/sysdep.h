/* Dirty system-dependent hacks.
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

/* This file is included by wget.h.  Random .c files need not include
   it.  */

#ifndef SYSDEP_H
#define SYSDEP_H

/* We need these to be playing with various stuff.  */
#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else /* not TIME_WITH_SYS_TIME_H */
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#else /* not HAVE_SYS_TIME_H */
# include <time.h>
#endif /* HAVE_SYS_TIME_H */
#endif /* TIME_WITH_SYS_TIME_H */

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WINDOWS
/* Windows doesn't have some functions.  Include mswindows.h so we get
   their declarations, as well as some additional declarations and
   macros.  This must come first, so it can set things up.  */
#include <mswindows.h>
#endif /* WINDOWS */

/* Allegedly needed for compilation under OS/2: */
#ifdef EMXOS2
#ifndef S_ISLNK
# define S_ISLNK(m) 0
#endif
#ifndef lstat
# define lstat stat
#endif
#endif /* EMXOS2 */

/* Reportedly, stat() macros are broken on some old systems.  Those
   systems will have to fend for themselves, as I will not introduce
   new code to handle it.

   However, I will add code for *missing* macros, and the following
   are missing from many systems.  */
#ifndef S_ISLNK
# define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#ifndef S_ISDIR
# define S_ISDIR(m) (((m) & (_S_IFMT)) == (_S_IFDIR))
#endif
#ifndef S_ISREG
# define S_ISREG(m) (((m) & _S_IFMT) == _S_IFREG)
#endif

/* Bletch!  SPARC compiler doesn't define sparc (needed by
   arpa/nameser.h) when in -Xc mode.  Luckily, it always defines
   __sparc.  */
#ifdef __sparc
#ifndef sparc
#define sparc
#endif
#endif

/* mswindows.h defines these.  */
#ifndef READ
# define READ(fd, buf, cnt) read ((fd), (buf), (cnt))
#endif
#ifndef WRITE
# define WRITE(fd, buf, cnt) write ((fd), (buf), (cnt))
#endif
#ifndef REALCLOSE
# define REALCLOSE(x) close (x)
#endif

#define CLOSE(x)				\
do {						\
  REALCLOSE (x);				\
  DEBUGP (("Closing fd %d\n", x));		\
} while (0)

/* OK, now define a decent interface to ctype macros.  The regular
   ones misfire when you feed them chars >= 127, as they understand
   them as "negative", which results in out-of-bound access at
   table-lookup, yielding random results.  This is, of course, totally
   bogus.  One way to "solve" this is to use `unsigned char'
   everywhere, but it is nearly impossible to do that cleanly, because
   all of the library functions and system calls accept `char'.

   Thus we define our wrapper macros which simply cast the argument to
   unsigned char before passing it to the <ctype.h> macro.  These
   versions are used consistently across the code.  */
#define ISASCII(x)  isascii ((unsigned char)(x))
#define ISALPHA(x)  isalpha ((unsigned char)(x))
#define ISSPACE(x)  isspace ((unsigned char)(x))
#define ISDIGIT(x)  isdigit ((unsigned char)(x))
#define ISXDIGIT(x) isxdigit ((unsigned char)(x))

/* Defined in cmpt.c: */
#ifndef HAVE_STRERROR
char *strerror ();
#endif
#ifndef HAVE_STRCASECMP
int strcasecmp ();
#endif
#ifndef HAVE_STRNCASECMP
int strncasecmp ();
#endif
#ifndef HAVE_STRSTR
char *strstr ();
#endif
#ifndef HAVE_STRPTIME
char *strptime ();
#endif

/* SunOS brain damage -- for some reason, SunOS header files fail to
   declare the functions below, which causes all kinds of problems
   (compiling errors) with pointer arithmetic and similar.

   This used to be only within `#ifdef STDC_HEADERS', but it got
   tripped on other systems (AIX), thus causing havoc.  Fortunately,
   SunOS appears to be the only system braindamaged that badly, so I
   added an extra `#ifdef sun' guard.  */
#ifndef STDC_HEADERS
#ifdef sun
#ifndef __cplusplus
char *strstr ();
char *strchr ();
char *strrchr ();
char *strtok ();
char *strdup ();
void *memcpy ();
#endif /* not __cplusplus */
#endif /* sun */
#endif /* STDC_HEADERS */

#endif /* SYSDEP_H */
