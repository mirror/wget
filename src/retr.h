/* Declarations for retr.c.
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

#ifndef RETR_H
#define RETR_H

#include "rbuf.h"

int get_contents PARAMS ((int, FILE *, long *, long, long, struct rbuf *));

uerr_t retrieve_url PARAMS ((const char *, char **, char **,
			     const char *, int *));
uerr_t retrieve_from_file PARAMS ((const char *, int, int *));

void reset_timer PARAMS ((void));
long elapsed_time PARAMS ((void));
char *rate PARAMS ((long, long));

void printwhat PARAMS ((int, int));

#endif /* RETR_H */
