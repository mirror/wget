/* Declarations for host.c
   Copyright (C) 1995, 1996, 1997, 2001 Free Software Foundation, Inc.

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
struct address_list;

/* Function declarations */
struct address_list *lookup_host PARAMS ((const char *, int));
char *herrmsg PARAMS ((int));

void address_list_get_bounds PARAMS ((struct address_list *, int *, int *));
void address_list_copy_one PARAMS ((struct address_list *, int,
				    unsigned char *));
int address_list_match_all PARAMS ((struct address_list *,
				    struct address_list *));
void address_list_set_faulty PARAMS ((struct address_list *, int));
void address_list_release PARAMS ((struct address_list *));

/* This was originally going to be a macro, but then every caller
   would have to #include the netinet stuff.  */
char *pretty_print_address PARAMS ((const unsigned char *));

int accept_domain PARAMS ((struct url *));
int sufmatch PARAMS ((const char **, const char *));

void host_cleanup PARAMS ((void));

#endif /* HOST_H */
