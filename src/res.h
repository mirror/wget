/* Declarations for res.c.
   Copyright (C) 2001 Free Software Foundation, Inc.

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

#ifndef RES_H
#define RES_H

struct robot_specs;

struct robot_specs *res_parse PARAMS ((const char *, int));
struct robot_specs *res_parse_from_file PARAMS ((const char *));

int res_match_path PARAMS ((const struct robot_specs *, const char *));

void res_register_specs PARAMS ((const char *, int, struct robot_specs *));
struct robot_specs *res_get_specs PARAMS ((const char *, int));

int res_retrieve_file PARAMS ((const char *, char **));

void res_cleanup PARAMS ((void));

#endif /* RES_H */
