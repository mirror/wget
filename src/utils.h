/* Declarations for utils.c.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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

#ifndef UTILS_H
#define UTILS_H

enum accd {
   ALLABS = 1
};

/* A linked list of strings.  The list is ordered alphabetically.  */
typedef struct _slist
{
  char *string;
  struct _slist *next;
} slist;

struct hash_table;

struct file_memory {
  char *content;
  long length;
  int mmap_p;
};

struct wget_timer;

char *time_str PARAMS ((time_t *));
char *datetime_str PARAMS ((time_t *));

const char *uerrmsg PARAMS ((uerr_t));

#ifdef DEBUG_MALLOC
void print_malloc_debug_stats ();
#endif

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
struct file_memory *read_file PARAMS ((const char *));
void read_file_free PARAMS ((struct file_memory *));

void free_vec PARAMS ((char **));
char **merge_vecs PARAMS ((char **, char **));
slist *slist_append PARAMS ((slist *, const char *));
slist *slist_prepend PARAMS ((slist *, const char *));
slist *slist_nreverse PARAMS ((slist *));
int slist_contains PARAMS ((slist *, const char *));
void slist_free PARAMS ((slist *));

void string_set_add PARAMS ((struct hash_table *, const char *));
int string_set_contains PARAMS ((struct hash_table *, const char *));
void string_set_free PARAMS ((struct hash_table *));
void free_keys_and_values PARAMS ((struct hash_table *));

char *legible PARAMS ((long));
char *legible_very_long PARAMS ((VERY_LONG_TYPE));
int numdigit PARAMS ((long));
void long_to_string PARAMS ((char *, long));

struct wget_timer *wtimer_allocate PARAMS ((void));
struct wget_timer *wtimer_new PARAMS ((void));
void wtimer_delete PARAMS ((struct wget_timer *));
void wtimer_reset PARAMS ((struct wget_timer *));
long wtimer_elapsed PARAMS ((struct wget_timer *));
long wtimer_granularity PARAMS ((void));

char *html_quote_string PARAMS ((const char *));

#endif /* UTILS_H */
