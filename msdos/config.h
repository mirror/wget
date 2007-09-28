/* Configuration header file for MS-DOS/Watt-32

   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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


#ifndef CONFIG_DOS_H
#define CONFIG_DOS_H

#include <stdlib.h>
#include <limits.h>
#include <tcp.h>
#include <malloc.h>

#ifdef __DJGPP__
#include <sys/config.h>
#endif

#include <sys/errno.h>

#if defined(__WATCOMC__) && (__WATCOMC__ >= 1250)  /* OW 1.5+ */
  #define OPENWATCOM_15
#endif

#if defined(__HIGHC__)
  #define inline
  #define HAVE_UNISTD_H 1
  #define HAVE_UTIME_H 1
#endif

#if defined(__WATCOMC__) || defined(__BORLANDC__)
  #define inline
#endif

#ifdef HAVE_SSL
  #define OPENSSL_NO_KRB5
#endif

#define STDC_HEADERS 1
#define RETSIGTYPE void

#define USE_OPIE 1
#define USE_DIGEST 1
#define DEBUG

#ifdef __DJGPP__
  #define HAVE_STRUCT_UTIMBUF 1
  #define HAVE_UNAME 1
  #define HAVE_UTIME_H 1
  #define HAVE_STRCASECMP 1
  #define HAVE_STRNCASECMP 1
  #define HAVE_SYS_SELECT_H 1
  #define HAVE_USLEEP 1
  #define HAVE_SIGNAL 1
  #define HAVE_BASENAME 1
  #define HAVE_SIGSETJMP 1
  #define HAVE_SIGBLOCK 1
  #define HAVE__BOOL 1

  #if (DJGPP_MINOR >= 4)
    #include <stdbool.h>
    #define HAVE_SNPRINTF 1
    #define HAVE_VSNPRINTF 1
    #define HAVE_UINT32_T 1
  #endif
#endif

#ifdef __HIGHC__
  #define HAVE_STRUCT_UTIMBUF 1
  #define HAVE_UTIME_H 1
#endif

#ifdef OPENWATCOM_15
  #define HAVE_STRCASECMP
  #define HAVE_STRNCASECMP
#endif

#define HAVE_GETHOSTBYNAME 1
#define HAVE_GETHOSTNAME 1
#define HAVE_SELECT 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRSTR 1
#define HAVE_MKTIME 1
#define HAVE_STDARG_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_SIGNAL_H 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_MD5 1
#define HAVE_BUILTIN_MD5 1
#define HAVE_ISATTY 1
#define HAVE_MEMMOVE 1

#define OS_TYPE "DOS"
#define CTRLBREAK_BACKGND 1
#define PROTOTYPES 1

#define WGET_USE_STDARG

#define lookup_host  wget_lookuphost
#define select       select_s
#define socklen_t    int

#define sock_read    wget_sock_read
#define sock_write   wget_sock_write
#define sock_close   wget_sock_close

#if defined(__DJGPP__)
  #define MKDIR(p,a) mkdir(p,a)
#else
  #define strcasecmp stricmp
  #define MKDIR(p,a) mkdir(p)
#endif

#if !defined(MSDOS)
#define MSDOS
#endif

#endif  /* CONFIG_DOS_H */
