/* Declarations for host.c
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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

#ifndef HOST_H
#define HOST_H

struct urlinfo;

/* Function declarations */

struct hostent *ngethostbyname PARAMS ((const char *));
int store_hostaddress PARAMS ((unsigned char *, const char *));

void clean_hosts PARAMS ((void));

char *realhost PARAMS ((const char *));
int same_host PARAMS ((const char *, const char *));
int accept_domain PARAMS ((struct urlinfo *));
int sufmatch PARAMS ((const char **, const char *));

char *ftp_getaddress PARAMS ((void));

char *herrmsg PARAMS ((int));

#endif /* HOST_H */
