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

#ifdef DEBUG_MALLOC
void print_malloc_debug_stats ();
#endif

char *xstrdup_lower PARAMS ((const char *));
int count_char PARAMS ((const char *, char));

char *strdupdelim PARAMS ((const char *, const char *));
char **sepstring PARAMS ((const char *));
int frontcmp PARAMS ((const char *, const char *));
char *pwd_cuserid PARAMS ((char *));
void fork_to_background PARAMS ((void));

void touch PARAMS ((const char *, time_t));
int remove_link PARAMS ((const char *));
int file_exists_p PARAMS ((const char *));
int file_non_directory_p PARAMS ((const char *));
long file_size PARAMS ((const char *));
int make_directory PARAMS ((const char *));
char *unique_name PARAMS ((const char *, int));
char *file_merge PARAMS ((const char *, const char *));

int acceptable PARAMS ((const char *));
int accdir PARAMS ((const char *s, enum accd));
char *suffix PARAMS ((const char *s));
int match_tail PARAMS ((const char *, const char *, int));
int has_wildcards_p PARAMS ((const char *));

int has_html_suffix_p PARAMS ((const char *));

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
char *legible_large_int PARAMS ((LARGE_INT));
int numdigit PARAMS ((long));
char *number_to_string PARAMS ((char *, long));

struct wget_timer *wtimer_allocate PARAMS ((void));
struct wget_timer *wtimer_new PARAMS ((void));
void wtimer_delete PARAMS ((struct wget_timer *));
void wtimer_reset PARAMS ((struct wget_timer *));
double wtimer_elapsed PARAMS ((struct wget_timer *));
double wtimer_granularity PARAMS ((void));

char *html_quote_string PARAMS ((const char *));

int determine_screen_width PARAMS ((void));
int random_number PARAMS ((int));
double random_float PARAMS ((void));

int run_with_timeout PARAMS ((double, void (*) (void *), void *));

#endif /* UTILS_H */
