/* Support for cookies.
   Copyright (C) 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* struct cookie is not exported; this file only exports functions for
   manipulating cookie contents.  */

int set_cookie_header_cb PARAMS ((const char *, void *));

char *build_cookies_request PARAMS ((const char *, int, const char *, int));

void load_cookies PARAMS ((const char *));
void save_cookies PARAMS ((const char *));

void cookies_cleanup PARAMS ((void));
