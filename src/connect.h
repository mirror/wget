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

#include "host.h"

/* Function declarations */

int connect_to_one PARAMS ((ip_address *, unsigned short, int));
int connect_to_many PARAMS ((struct address_list *, unsigned short, int));
void set_connection_host_name PARAMS ((const char *));

int test_socket_open PARAMS ((int));
int select_fd PARAMS ((int, double, int));
uerr_t bindport PARAMS ((unsigned short *, int));
uerr_t acceptport PARAMS ((int *));
void closeport PARAMS ((int));
int conaddr PARAMS ((int, ip_address *));

int iread PARAMS ((int, char *, int));
int iwrite PARAMS ((int, char *, int));

#endif /* CONNECT_H */
