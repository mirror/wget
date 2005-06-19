/* Hash table declarations.
   Copyright (C) 2000 Free Software Foundation, Inc.

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

#ifndef HASH_H
#define HASH_H

struct hash_table;

struct hash_table *hash_table_new (int, unsigned long (*) (const void *),
				   int (*) (const void *, const void *));
void hash_table_destroy (struct hash_table *);

void *hash_table_get (const struct hash_table *, const void *);
int hash_table_get_pair (const struct hash_table *, const void *,
                         void *, void *);
int hash_table_contains (const struct hash_table *, const void *);

void hash_table_put (struct hash_table *, const void *, void *);
int hash_table_remove (struct hash_table *, const void *);
void hash_table_clear (struct hash_table *);

void hash_table_map (struct hash_table *,
		     int (*) (void *, void *, void *), void *);
int hash_table_count (const struct hash_table *);

struct hash_table *make_string_hash_table (int);
struct hash_table *make_nocase_string_hash_table (int);

unsigned long hash_pointer (const void *);

#endif /* HASH_H */
