/* Declarations for metalink.c.
   Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
   2005, 2006, 2007, 2008, 2009, 2010, 2011 Free Software Foundation,
   Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget.  If not, see <http://www.gnu.org/licenses/>.

Additional permission under GNU GPL version 3 section 7

If you modify this program, or any covered work, by linking or
combining it with the OpenSSL project's OpenSSL library (or a
modified version of that library), containing parts covered by the
terms of the OpenSSL or SSLeay licenses, the Free Software Foundation
grants you additional permission to convey the resulting work.
Corresponding Source for a non-source form of such a combination
shall include the source code for the parts of OpenSSL used as well
as that of the covered work.  */

#ifndef MLINK_H
#define MLINK_H

typedef struct metalink_piece_hash
{
  struct metalink_piece_hash *next;

  int piece;
  char *hash;
} mlink_piece_hash;

typedef struct metalink_checksum
{
  struct metalink_checksum *next;

  char *type;
  char *hash;
} mlink_checksum;

typedef struct metalink_resource
{
  struct metalink_resource *next;

  char *url;
  char *type;
  char *location;
  int preference;
  int maxconnections;
} mlink_resource;

typedef struct
{
  char *type;
  int length;
  mlink_piece_hash *piece_hashes;
} mlink_chunk_checksum;

typedef struct metalink_file
{
  struct metalink_file *next;

  char *name;
  long long int size;
  char *version;
  char *language;
  char *os;
  int maxconnections;
  mlink_resource *resources;
  int num_of_res;
  mlink_checksum *checksums;
  int num_of_checksums;
  mlink_chunk_checksum *chunk_checksum;
} mlink_file;

typedef struct
{
  char *identity;
  char *tags;
  mlink_file *files;
  int num_of_files;
} mlink;

mlink *parse_metalink (char *);

void elect_resources (mlink *);

void elect_checksums (mlink *);

void delete_mlink (mlink *);

metalink_t *metalink_context (const char *);

int verify_file_hash (const char *, mlink_checksum *);

#endif /* MLINK_H */
