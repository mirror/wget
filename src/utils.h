/* Declarations for utils.c.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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

#ifndef UTILS_H
#define UTILS_H

/* Flags for slist.  */
enum {
   NOSORT     = 1
};

enum accd {
   ALLABS = 1
};

/* A linked list of strings.  The list is ordered alphabetically.  */
typedef struct _slist
{
  char *string;
  struct _slist *next;
} slist;

char *time_str PARAMS ((time_t *));
const char *uerrmsg PARAMS ((uerr_t));

char *strdupdelim PARAMS ((const char *, const char *));
char **sepstring PARAMS ((const char *));
int frontcmp PARAMS ((const char *, const char *));
char *pwd_cuserid PARAMS ((char *));
void fork_to_background PARAMS ((void));
void path_simplify PARAMS ((char *));

void touch PARAMS ((const char *, time_t));
int remove_link PARAMS ((const char *));
int file_exists_p PARAMS ((const char *));
int file_non_directory_p PARAMS ((const char *));
int make_directory PARAMS ((const char *));
char *unique_name PARAMS ((const char *));

int acceptable PARAMS ((const char *));
int accdir PARAMS ((const char *s, enum accd));
char *suffix PARAMS ((const char *s));

char *read_whole_line PARAMS ((FILE *));
void load_file PARAMS ((FILE *, char **, long *));

void free_vec PARAMS ((char **));
char **merge_vecs PARAMS ((char **, char **));
slist *add_slist PARAMS ((slist *, const char *, int));
int in_slist PARAMS ((slist *, const char *));
void free_slist PARAMS ((slist *));

char *legible PARAMS ((long));
int numdigit PARAMS ((long));
void long_to_string PARAMS ((char *, long));

#endif /* UTILS_H */
