/* Declarations for res.c.
   Copyright (C) 2001 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget.  If not, see <http://www.gnu.org/licenses/>.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#ifndef RES_H
#define RES_H

struct robot_specs;

struct robot_specs *res_parse (const char *, int);
struct robot_specs *res_parse_from_file (const char *);

bool res_match_path (const struct robot_specs *, const char *);

void res_register_specs (const char *, int, struct robot_specs *);
struct robot_specs *res_get_specs (const char *, int);

bool res_retrieve_file (const char *, char **);

bool is_robots_txt_url (const char *);

void res_cleanup (void);

#endif /* RES_H */
