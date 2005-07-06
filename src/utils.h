/* Declarations for utils.c.
   Copyright (C) 1996-2005 Free Software Foundation, Inc.

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
along with Wget; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

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

struct hash_table;

struct file_memory {
  char *content;
  long length;
  int mmap_p;
};

#define HYPHENP(x) (*(x) == '-' && !*((x) + 1))

char *time_str (time_t *);
char *datetime_str (time_t *);

#ifdef DEBUG_MALLOC
void print_malloc_debug_stats ();
#endif

char *xstrdup_lower (const char *);

char *strdupdelim (const char *, const char *);
char **sepstring (const char *);
bool frontcmp (const char *, const char *);
void fork_to_background (void);

char *aprintf (const char *, ...) GCC_FORMAT_ATTR (1, 2);
char *concat_strings (const char *, ...);

void touch (const char *, time_t);
int remove_link (const char *);
bool file_exists_p (const char *);
bool file_non_directory_p (const char *);
wgint file_size (const char *);
int make_directory (const char *);
char *unique_name (const char *, bool);
FILE *unique_create (const char *, bool, char **);
FILE *fopen_excl (const char *, bool);
char *file_merge (const char *, const char *);

int fnmatch_nocase (const char *, const char *, int);
bool acceptable (const char *);
bool accdir (const char *s);
char *suffix (const char *s);
bool match_tail (const char *, const char *, bool);
bool has_wildcards_p (const char *);

bool has_html_suffix_p (const char *);

char *read_whole_line (FILE *);
struct file_memory *read_file (const char *);
void read_file_free (struct file_memory *);

void free_vec (char **);
char **merge_vecs (char **, char **);
char **vec_append (char **, const char *);

void string_set_add (struct hash_table *, const char *);
int string_set_contains (struct hash_table *, const char *);
void string_set_to_array (struct hash_table *, char **);
void string_set_free (struct hash_table *);
void free_keys_and_values (struct hash_table *);

const char *with_thousand_seps (wgint);

/* human_readable must be able to accept wgint and SUM_SIZE_INT
   arguments.  On machines where wgint is 32-bit, declare it to accept
   double.  */
#if SIZEOF_WGINT >= 8
# define HR_NUMTYPE wgint
#else
# define HR_NUMTYPE double
#endif
char *human_readable (HR_NUMTYPE);


int numdigit (wgint);
char *number_to_string (char *, wgint);
char *number_to_static_string (wgint);

int determine_screen_width (void);
int random_number (int);
double random_float (void);

bool run_with_timeout (double, void (*) (void *), void *);
void xsleep (double);

/* How many bytes it will take to store LEN bytes in base64.  */
#define BASE64_LENGTH(len) (4 * (((len) + 2) / 3))

int base64_encode (const char *, int, char *);
int base64_decode (const char *, char *);

void stable_sort (void *, size_t, size_t, int (*) (const void *, const void *));

const char *print_decimal (double);

#endif /* UTILS_H */
