/* Declarations for host.c
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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

#ifndef HOST_H
#define HOST_H

struct url;

/* Function declarations */

struct hostent *ngethostbyname PARAMS ((const char *));
int store_hostaddress PARAMS ((unsigned char *, const char *));

void host_cleanup PARAMS ((void));

int accept_domain PARAMS ((struct url *));
int sufmatch PARAMS ((const char **, const char *));

char *herrmsg PARAMS ((int));

#endif /* HOST_H */
