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
#ifndef S_ISLNK
# define S_ISLNK(m) 0
#endif
#ifndef lstat
# define lstat stat
#endif
#endif /* __EMX__ */

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

#ifdef __BEOS__
# undef READ
# undef WRITE
# define READ(fd, buf, cnt) recv((fd), (buf), (cnt), 0)
# define WRITE(fd, buf, cnt) send((fd), (buf), (cnt), 0)
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

/* Define a large ("very long") type useful for storing large
   non-negative quantities that exceed sizes of normal download, such
   as the *total* number of bytes downloaded.  To fit today's needs,
   this needs to be an integral type at least 64 bits wide.  On the
   machines where `long' is 64-bit, we use long.  Otherwise, we check
   whether `long long' is available and if yes, use that.  If long
   long is unavailable, we give up and just use `long'.

   This check could be smarter and moved to configure, which could
   check for a bunch of non-standard types such as uint64_t.  But I
   don't see the need for it -- the current test will work on all
   modern architectures, and if it fails, nothing bad happens, we just
   end up with long.

   Note: you cannot use VERY_LONG_TYPE along with printf().  When you
   need to print it, use very_long_to_string().  */

#if (SIZEOF_LONG >= 8) || !defined(HAVE_LONG_LONG)
/* either long is "big enough", or long long is unavailable which
   leaves long as the only choice. */ 
# define VERY_LONG_TYPE   unsigned long
#else  /* use long long */
/* long is smaller than 8 bytes, but long long is available. */
# define VERY_LONG_TYPE   unsigned long long
#endif /* use long long */

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
#ifndef HAVE_VSNPRINTF
int vsnprintf ();
#endif
#ifndef HAVE_USLEEP
int usleep ();
#endif
#ifndef HAVE_MEMMOVE
void *memmove ();
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

/* Some systems (Linux libc5, "NCR MP-RAS 3.0", and others) don't
   provide MAP_FAILED, a symbolic constant for the value returned by
   mmap() when it doesn't work.  Usually, this constant should be -1.
   This only makes sense for files that use mmap() and include
   sys/mman.h *before* sysdep.h, but doesn't hurt others.  */

#ifndef MAP_FAILED
# define MAP_FAILED ((void *) -1)
#endif

#endif /* SYSDEP_H */
