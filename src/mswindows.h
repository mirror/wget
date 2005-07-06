/* Declarations for windows
   Copyright (C) 1996-2005 Free Software Foundation, Inc.

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

#ifndef MSWINDOWS_H
#define MSWINDOWS_H

#ifndef WGET_H
# error This file should not be included directly.
#endif

/* Prevent inclusion of <winsock*.h> in <windows.h>.  */
#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

/* We need winsock2.h for IPv6 and ws2tcpip.h for getaddrinfo, so
  include both in ENABLE_IPV6 case.  (ws2tcpip.h includes winsock2.h
  only on MinGW.) */
#ifdef ENABLE_IPV6
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <winsock.h>
#endif

#ifndef EAI_SYSTEM
# define EAI_SYSTEM -1   /* value doesn't matter */
#endif

/* Declares file access functions, such as open, creat, access, and
   chmod.  Unix declares these in unistd.h and fcntl.h.  */
#include <io.h>

#ifndef S_ISDIR
# define S_ISDIR(m) (((m) & (_S_IFMT)) == (_S_IFDIR))
#endif
#ifndef S_ISLNK
# define S_ISLNK(a) 0
#endif

/* We have strcasecmp and strncasecmp, just under different names.  */
#ifndef HAVE_STRCASECMP
# define strcasecmp stricmp
#endif
#ifndef HAVE_STRNCASECMP
# define strncasecmp strnicmp
#endif

/* The same for snprintf() and vsnprintf().  */
#define snprintf _snprintf
#define vsnprintf _vsnprintf

/* Define a wgint type under Windows. */
typedef __int64 wgint;
#define SIZEOF_WGINT 8
#define WGINT_MAX LL (9223372036854775807)

/* str_to_wgint is a function with the semantics of strtol, but which
   works on wgint.  */
#if defined HAVE_STRTOLL
# define str_to_wgint strtoll
#elif defined HAVE__STRTOI64
# define str_to_wgint _strtoi64
#else
__int64 str_to_int64 (const char *, char **, int);
# define str_to_wgint str_to_int64
#endif

/* Windows has no symlink, therefore no lstat.  Without symlinks lstat
   is equivalent to stat anyway.  */
#define lstat stat

#define PATH_SEPARATOR '\\'

/* Win32 doesn't support the MODE argument to mkdir.  */
#include <direct.h>
#define mkdir(a, b) (mkdir) (a)

/* Additional declarations needed for IPv6: */
#ifdef ENABLE_IPV6
const char *inet_ntop (int, const void *, char *, socklen_t);
#endif

#ifndef INHIBIT_WRAP

/* Winsock functions don't set errno, so we provide wrappers that do. */

#define socket wrapped_socket
#define bind wrapped_bind
#define connect wrapped_connect
#define listen wrapped_listen
#define accept wrapped_accept
#define recv wrapped_recv
#define send wrapped_send
#define select wrapped_select
#define getsockname wrapped_getsockname
#define getpeername wrapped_getpeername
#define setsockopt wrapped_setsockopt
#define closesocket wrapped_closesocket

#endif /* not INHIBIT_WRAP */

int wrapped_socket (int, int, int);
int wrapped_bind (int, struct sockaddr *, int);
int wrapped_connect (int, const struct sockaddr *, int);
int wrapped_listen (int s, int backlog);
int wrapped_accept (int s, struct sockaddr *a, int *alen);
int wrapped_recv (int, void *, int, int);
int wrapped_send (int, const void *, int, int);
int wrapped_select (int, fd_set *, fd_set *, fd_set *, const struct timeval *);
int wrapped_getsockname (int, struct sockaddr *, int *);
int wrapped_getpeername (int, struct sockaddr *, int *);
int wrapped_setsockopt (int, int, int, const void *, int);
int wrapped_closesocket (int);

/* Finally, provide a private version of strerror that does the
   right thing with Winsock errors. */
#ifndef INHIBIT_WRAP
# define strerror windows_strerror
#endif
const char *windows_strerror (int);

/* Declarations of various socket errors:  */

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

void ws_startup (void);
void ws_changetitle (const char *);
void ws_percenttitle (double);
char *ws_mypath (void);
void windows_main (int *, char **, char **);

#endif /* MSWINDOWS_H */
