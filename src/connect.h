/* Declarations for connect.
   Copyright (C) 1995, 1996, 1997, 2000 Free Software Foundation, Inc.

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

#ifndef CONNECT_H
#define CONNECT_H

#include "host.h"		/* for definition of ip_address */

#ifndef ENABLE_IPV6
# ifndef HAVE_SOCKADDR_STORAGE
#  define sockaddr_storage sockaddr_in
# endif
#endif /* ENABLE_IPV6 */

/* Function declarations */

/* Returned by connect_to_host when host name cannot be resolved.  */
enum {
  E_HOST = -100
};
int connect_to_host PARAMS ((const char *, int));
int connect_to_ip PARAMS ((const ip_address *, int, const char *));

uerr_t bindport PARAMS ((const ip_address *, int *, int *));
uerr_t acceptport PARAMS ((int, int *));

enum {
  ENDPOINT_LOCAL,
  ENDPOINT_PEER
};
int socket_ip_address PARAMS ((int, ip_address *, int));

/* Flags for select_fd's WAIT_FOR argument. */
enum {
  WAIT_FOR_READ = 1,
  WAIT_FOR_WRITE = 2
};
int select_fd PARAMS ((int, double, int));
int test_socket_open PARAMS ((int));

typedef int (*xreader_t) PARAMS ((int, char *, int, void *));
typedef int (*xwriter_t) PARAMS ((int, char *, int, void *));
typedef int (*xpoller_t) PARAMS ((int, double, int, void *));
typedef void (*xcloser_t) PARAMS ((int, void *));
void register_extended PARAMS ((int,
				xreader_t, xwriter_t, xpoller_t, xcloser_t,
				void *));

int xread PARAMS ((int, char *, int, double));
int xwrite PARAMS ((int, char *, int, double));
void xclose PARAMS ((int));
#endif /* CONNECT_H */
