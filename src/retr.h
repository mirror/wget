/* Declarations for retr.c.
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

#ifndef RETR_H
#define RETR_H

#include "rbuf.h"

int get_contents PARAMS ((int, FILE *, long *, long, long, struct rbuf *,
			  int, long *));

uerr_t retrieve_url PARAMS ((const char *, char **, char **,
			     const char *, int *));
uerr_t retrieve_from_file PARAMS ((const char *, int, int *));

char *retr_rate PARAMS ((long, long, int));
double calc_rate PARAMS ((long, long, int *));
void printwhat PARAMS ((int, int));

void downloaded_increase PARAMS ((unsigned long));
int downloaded_exceeds_quota PARAMS ((void));

void sleep_between_retrievals PARAMS ((int));

/* Because there's no http.h. */

struct url;

uerr_t http_loop PARAMS ((struct url *, char **, char **, const char *,
			  int *, struct url *));


#endif /* RETR_H */
