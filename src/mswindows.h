/* Declarations for windows
   Copyright (C) 1995, 1997, 1997, 1998 Free Software Foundation, Inc.

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

#ifndef MSWINDOWS_H
#define MSWINDOWS_H

#ifndef S_ISDIR
# define S_ISDIR(m) (((m) & (_S_IFMT)) == (_S_IFDIR))
#endif
#ifndef S_ISLNK
# define S_ISLNK(a) 0
#endif

/* We have strcasecmp and strncasecmp, just under a different name. */
#define strcasecmp stricmp
#define strncasecmp strnicmp

/* No stat on Windows.  */
#define lstat stat

#define PATH_SEPARATOR '\\'

/* Microsoft says stat is _stat, Borland doesn't */
#ifdef _MSC_VER
# define stat _stat
#endif

#define REALCLOSE(x) closesocket (x)

/* read & write don't work with sockets on Windows 95.  */
#define READ(fd, buf, cnt) recv ((fd), (buf), (cnt), 0)
#define WRITE(fd, buf, cnt) send ((fd), (buf), (cnt), 0)

/* #### Do we need this?  */
#include <direct.h>

/* Windows compilers accept only one arg to mkdir. */
#ifndef __BORLANDC__
# define mkdir(a, b) _mkdir(a)
#else  /* __BORLANDC__ */
# define mkdir(a, b) mkdir(a)
#endif /* __BORLANDC__ */

#include <windows.h>

/* Declarations of various socket errors: */

#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

/* Public functions.  */

unsigned int sleep (unsigned);
void ws_startup (void);
void ws_changetitle (char*, int);
char *ws_mypath (void);
void ws_help (const char *);
void windows_main_junk (int *, char **, char **);

#endif /* MSWINDOWS_H */
