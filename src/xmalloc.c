/* Wrappers around malloc and memory debugging support.
   Copyright (C) 2003 Free Software Foundation, Inc.

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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else  /* not HAVE_STRING_H */
# include <strings.h>
#endif /* not HAVE_STRING_H */
#include <sys/types.h>
#include <errno.h>
#include <assert.h>

#include "wget.h"
#include "xmalloc.h"

#ifndef errno
extern int errno;
#endif

/* This file implements several wrappers around the basic allocation
   routines.  This is done for two reasons: first, so that the callers
   of these functions need not check for errors, which is easy to
   forget.  If there is not enough virtual memory for running Wget,
   something is seriously wrong, and Wget exits with an appropriate
   error message.

   The second reason why these are useful is that, if DEBUG_MALLOC is
   defined, they also provide a handy (if crude) malloc debugging
   interface that checks memory leaks.  */

/* Croak the fatal memory error and bail out with non-zero exit
   status.  */

static void
memfatal (const char *context, long size)
{
  /* Make sure we don't try to store part of the log line, and thus
     call malloc.  */
  log_set_save_context (0);
  logprintf (LOG_ALWAYS, _("%s: %s: Cannot allocate %ld bytes.\n"),
	     exec_name, context, size);
  exit (1);
}

/* These functions end with _real because they need to be
   distinguished from the debugging functions, and from the macros.
   Explanation follows:

   If memory debugging is not turned on, wget.h defines these:

     #define xmalloc xmalloc_real
     #define xmalloc0 xmalloc0_real
     #define xrealloc xrealloc_real
     #define xstrdup xstrdup_real
     #define xfree free

   In case of memory debugging, the definitions are a bit more
   complex, because we want to provide more information, *and* we want
   to call the debugging code.  (The former is the reason why xmalloc
   and friends need to be macros in the first place.)  Then it looks
   like this:

     #define xmalloc(a) xmalloc_debug (a, __FILE__, __LINE__)
     #define xmalloc0(a) xmalloc0_debug (a, __FILE__, __LINE__)
     #define xfree(a)   xfree_debug (a, __FILE__, __LINE__)
     #define xrealloc(a, b) xrealloc_debug (a, b, __FILE__, __LINE__)
     #define xstrdup(a) xstrdup_debug (a, __FILE__, __LINE__)

   Each of the *_debug function does its magic and calls the real one.  */

#ifdef DEBUG_MALLOC
# define STATIC_IF_DEBUG static
#else
# define STATIC_IF_DEBUG
#endif

STATIC_IF_DEBUG void *
xmalloc_real (size_t size)
{
  void *ptr = malloc (size);
  if (!ptr)
    memfatal ("malloc", size);
  return ptr;
}

STATIC_IF_DEBUG void *
xmalloc0_real (size_t size)
{
  /* Using calloc can be faster than malloc+memset because some calloc
     implementations know when they're dealing with zeroed-out memory
     from the system and can avoid unnecessary memset.  */
  void *ptr = calloc (1, size);
  if (!ptr)
    memfatal ("calloc", size);
  return ptr;
}

STATIC_IF_DEBUG void *
xrealloc_real (void *ptr, size_t newsize)
{
  void *newptr;

  /* Not all Un*xes have the feature of realloc() that calling it with
     a NULL-pointer is the same as malloc(), but it is easy to
     simulate.  */
  if (ptr)
    newptr = realloc (ptr, newsize);
  else
    newptr = malloc (newsize);
  if (!newptr)
    memfatal ("realloc", newsize);
  return newptr;
}

STATIC_IF_DEBUG char *
xstrdup_real (const char *s)
{
  char *copy;

#ifndef HAVE_STRDUP
  int l = strlen (s);
  copy = malloc (l + 1);
  if (!copy)
    memfatal ("strdup", l + 1);
  memcpy (copy, s, l + 1);
#else  /* HAVE_STRDUP */
  copy = strdup (s);
  if (!copy)
    memfatal ("strdup", 1 + strlen (s));
#endif /* HAVE_STRDUP */

  return copy;
}

#ifdef DEBUG_MALLOC

/* Crude home-grown routines for debugging some malloc-related
   problems.  Featured:

   * Counting the number of malloc and free invocations, and reporting
     the "balance", i.e. how many times more malloc was called than it
     was the case with free.

   * Making malloc store its entry into a simple array and free remove
     stuff from that array.  At the end, print the pointers which have
     not been freed, along with the source file and the line number.
     This also has the side-effect of detecting freeing memory that
     was never allocated.

   Note that this kind of memory leak checking strongly depends on
   every malloc() being followed by a free(), even if the program is
   about to finish.  Wget is careful to free the data structure it
   allocated in init.c.  */

static int malloc_count, free_count;

static struct {
  char *ptr;
  const char *file;
  int line;
} malloc_debug[100000];

/* Both register_ptr and unregister_ptr take O(n) operations to run,
   which can be a real problem.  It would be nice to use a hash table
   for malloc_debug, but the functions in hash.c are not suitable
   because they can call malloc() themselves.  Maybe it would work if
   the hash table were preallocated to a huge size, and if we set the
   rehash threshold to 1.0.  */

/* Register PTR in malloc_debug.  Abort if this is not possible
   (presumably due to the number of current allocations exceeding the
   size of malloc_debug.)  */

static void
register_ptr (void *ptr, const char *file, int line)
{
  int i;
  for (i = 0; i < countof (malloc_debug); i++)
    if (malloc_debug[i].ptr == NULL)
      {
	malloc_debug[i].ptr = ptr;
	malloc_debug[i].file = file;
	malloc_debug[i].line = line;
	return;
      }
  abort ();
}

/* Unregister PTR from malloc_debug.  Abort if PTR is not present in
   malloc_debug.  (This catches calling free() with a bogus pointer.)  */

static void
unregister_ptr (void *ptr)
{
  int i;
  for (i = 0; i < countof (malloc_debug); i++)
    if (malloc_debug[i].ptr == ptr)
      {
	malloc_debug[i].ptr = NULL;
	return;
      }
  abort ();
}

/* Print the malloc debug stats that can be gathered from the above
   information.  Currently this is the count of mallocs, frees, the
   difference between the two, and the dump of the contents of
   malloc_debug.  The last part are the memory leaks.  */

void
print_malloc_debug_stats (void)
{
  int i;
  printf ("\nMalloc:  %d\nFree:    %d\nBalance: %d\n\n",
	  malloc_count, free_count, malloc_count - free_count);
  for (i = 0; i < countof (malloc_debug); i++)
    if (malloc_debug[i].ptr != NULL)
      printf ("0x%08ld: %s:%d\n", (long)malloc_debug[i].ptr,
	      malloc_debug[i].file, malloc_debug[i].line);
}

void *
xmalloc_debug (size_t size, const char *source_file, int source_line)
{
  void *ptr = xmalloc_real (size);
  ++malloc_count;
  register_ptr (ptr, source_file, source_line);
  return ptr;
}

void *
xmalloc0_debug (size_t size, const char *source_file, int source_line)
{
  void *ptr = xmalloc0_real (size);
  ++malloc_count;
  register_ptr (ptr, source_file, source_line);
  return ptr;
}

void *
xrealloc_debug (void *ptr, size_t newsize, const char *source_file, int source_line)
{
  void *newptr = xrealloc_real (ptr, newsize);
  if (!ptr)
    {
      ++malloc_count;
      register_ptr (newptr, source_file, source_line);
    }
  else if (newptr != ptr)
    {
      unregister_ptr (ptr);
      register_ptr (newptr, source_file, source_line);
    }
  return newptr;
}

char *
xstrdup_debug (const char *s, const char *source_file, int source_line)
{
  char *copy = xstrdup_real (s);
  ++malloc_count;
  register_ptr (copy, source_file, source_line);
  return copy;
}

void
xfree_debug (void *ptr, const char *source_file, int source_line)
{
  assert (ptr != NULL);
  ++free_count;
  unregister_ptr (ptr);
  free (ptr);
}

#endif /* DEBUG_MALLOC */
