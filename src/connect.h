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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef CONNECT_H
#define CONNECT_H

struct address_list;

/* Function declarations */

int connect_to_one PARAMS ((const unsigned char *, unsigned short, int));
int connect_to_many PARAMS ((struct address_list *, unsigned short, int));
void set_connection_host_name PARAMS ((const char *));

int test_socket_open PARAMS ((int));
int select_fd PARAMS ((int, int, int));
uerr_t bindport PARAMS ((unsigned short *));
uerr_t acceptport PARAMS ((int *));
void closeport PARAMS ((int));
unsigned char *conaddr PARAMS ((int));

int iread PARAMS ((int, char *, int));
int iwrite PARAMS ((int, char *, int));

#endif /* CONNECT_H */
