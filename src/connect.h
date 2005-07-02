/* Declarations for connect.
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

#ifndef CONNECT_H
#define CONNECT_H

#include "host.h"		/* for definition of ip_address */

/* Function declarations */

/* Returned by connect_to_host when host name cannot be resolved.  */
enum {
  E_HOST = -100
};
int connect_to_host (const char *, int);
int connect_to_ip (const ip_address *, int, const char *);

int bind_local (const ip_address *, int *);
int accept_connection (int);

enum {
  ENDPOINT_LOCAL,
  ENDPOINT_PEER
};
bool socket_ip_address (int, ip_address *, int);

bool retryable_socket_connect_error (int);

/* Flags for select_fd's WAIT_FOR argument. */
enum {
  WAIT_FOR_READ = 1,
  WAIT_FOR_WRITE = 2
};
int select_fd (int, double, int);
bool test_socket_open (int);

typedef int (*fd_reader_t) (int, char *, int, void *);
typedef int (*fd_writer_t) (int, char *, int, void *);
typedef int (*fd_poller_t) (int, double, int, void *);
typedef int (*fd_peeker_t) (int, char *, int, void *);
typedef void (*fd_closer_t) (int, void *);
void fd_register_transport (int, fd_reader_t, fd_writer_t,
			    fd_poller_t, fd_peeker_t, fd_closer_t, void *);
void *fd_transport_context (int);

int fd_read (int, char *, int, double);
int fd_write (int, char *, int, double);
int fd_peek (int, char *, int, double);
void fd_close (int);
#endif /* CONNECT_H */
