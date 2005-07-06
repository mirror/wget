/* Support for various Windows compilation environments.
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
along with Wget; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */


/* This file contains specifics of various compilers supported on the
   Windows platform.  In this case "compiler" can refer either to the
   specific compiler feature (such as how to construct a 64-bit
   constant) or to a feature of the compilation environment shipped
   with the compiler.

   The file is divided into sections for each compiler.  Most of the
   explanatory comments are in the first (MinGW) section to avoid
   repetition.

   Things that apply to *all* compilers, as well as things that are
   specific to Wget, belong in src/mswindows.h.  */

/* -------------------- */
/* MinGW (GCC) section. */
/* -------------------- */
#if defined __GNUC__

#define OS_TYPE "Windows-MinGW"

#define LL(n) n##LL

/* Transparently support statting large files, like POSIX's LFS API
   does.  All Windows compilers we support use _stati64 (but have
   different names for 2nd argument type, see below), so we use
   that.  */
#define stat(fname, buf) _stati64 (fname, buf)

/* On Windows the 64-bit stat requires an explicitly different type
   for the 2nd argument, so we define a struct_stat macro that expands
   to the appropriate type on Windows, and to the regular struct stat
   on Unix.

   Note that Borland C 5.5 has 64-bit stat (_stati64), but not a
   64-bit fstat!  Because of that we also need a struct_fstat that
   points to struct_stat on Unix and on Windows, except under Borland,
   where it points to the 32-bit struct stat.  */

#define struct_stat struct _stati64
#define struct_fstat struct _stati64

/* MinGW 3.7 (or older) prototypes gai_strerror(), but is missing
   from all import libraries. */
#ifdef ENABLE_IPV6
# undef gai_strerror
#  define gai_strerror windows_strerror
# endif
#endif

/* -------------------- */
/* MS Visual C section. */
/* -------------------- */
#elif defined _MSC_VER

#define OS_TYPE "Windows-MSVC"

#define LL(n) n##I64

#define stat(fname, buf) _stati64 (fname, buf)
#define struct_stat struct _stati64
#define struct_fstat struct _stati64

#define isatty _isatty

/* ------------------ */
/* Borland C section. */
/* ------------------ */
#elif defined __BORLANDC__

#define OS_TYPE "Windows-Borland"

#define LL(n) n##I64
#define stat(fname, buf) _stati64 (fname, buf)
#define struct_stat struct stati64
#define struct_fstat struct stat

/* ------------------------------ */
/* Digital Mars Compiler section. */
/* ------------------------------ */
#elif defined __DMC__

#define OS_TYPE "Windows-DMC"

#define LL(n) n##LL
#undef stat
#undef struct_stat
#undef struct_fstat

/* DMC's runtime supports some POSIX and C99 features we use.  */
#define HAVE_USLEEP 1
#define HAVE_STDBOOL_H 1
#define HAVE__BOOL 1

#else
# error Your compiler is not supported.
#endif
