/* Various functions of utilitarian nature.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001
   Free Software Foundation, Inc.

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
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_MMAP
# include <sys/mman.h>
#endif
#ifdef HAVE_PWD_H
# include <pwd.h>
#endif
#include <limits.h>
#ifdef HAVE_UTIME_H
# include <utime.h>
#endif
#ifdef HAVE_SYS_UTIME_H
# include <sys/utime.h>
#endif
#include <errno.h>
#ifdef NeXT
# include <libc.h>		/* for access() */
#endif
#include <fcntl.h>
#include <assert.h>

/* For TIOCGWINSZ and friends: */
#ifdef HAVE_SYS_IOCTL_H
# include <sys/ioctl.h>
#endif
#ifdef HAVE_TERMIOS_H
# include <termios.h>
#endif

/* Needed for run_with_timeout. */
#undef USE_SIGNAL_TIMEOUT
#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif
#ifdef HAVE_SETJMP_H
# include <setjmp.h>
#endif
/* If sigsetjmp is a macro, configure won't pick it up. */
#ifdef sigsetjmp
# define HAVE_SIGSETJMP
#endif
#ifdef HAVE_SIGNAL
# ifdef HAVE_SIGSETJMP
#  define USE_SIGNAL_TIMEOUT
# endif
# ifdef HAVE_SIGBLOCK
#  define USE_SIGNAL_TIMEOUT
# endif
#endif

#include "wget.h"
#include "utils.h"
#include "hash.h"

#ifndef errno
extern int errno;
#endif

/* This section implements several wrappers around the basic
   allocation routines.  This is done for two reasons: first, so that
   the callers of these functions need not consistently check for
   errors.  If there is not enough virtual memory for running Wget,
   something is seriously wrong, and Wget exits with an appropriate
   error message.

   The second reason why these are useful is that, if DEBUG_MALLOC is
   defined, they also provide a handy (if crude) malloc debugging
   interface that checks memory leaks.  */

/* Croak the fatal memory error and bail out with non-zero exit
   status.  */
static void
memfatal (const char *what)
{
  /* Make sure we don't try to store part of the log line, and thus
     call malloc.  */
  log_set_save_context (0);
  logprintf (LOG_ALWAYS, _("%s: %s: Not enough memory.\n"), exec_name, what);
  exit (1);
}

/* These functions end with _real because they need to be
   distinguished from the debugging functions, and from the macros.
   Explanation follows:

   If memory debugging is not turned on, wget.h defines these:

     #define xmalloc xmalloc_real
     #define xrealloc xrealloc_real
     #define xstrdup xstrdup_real
     #define xfree free

   In case of memory debugging, the definitions are a bit more
   complex, because we want to provide more information, *and* we want
   to call the debugging code.  (The former is the reason why xmalloc
   and friends need to be macros in the first place.)  Then it looks
   like this:

     #define xmalloc(a) xmalloc_debug (a, __FILE__, __LINE__)
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
    memfatal ("malloc");
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
    memfatal ("realloc");
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
    memfatal ("strdup");
  memcpy (copy, s, l + 1);
#else  /* HAVE_STRDUP */
  copy = strdup (s);
  if (!copy)
    memfatal ("strdup");
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

void
xfree_debug (void *ptr, const char *source_file, int source_line)
{
  assert (ptr != NULL);
  ++free_count;
  unregister_ptr (ptr);
  free (ptr);
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

#endif /* DEBUG_MALLOC */

/* Utility function: like xstrdup(), but also lowercases S.  */

char *
xstrdup_lower (const char *s)
{
  char *copy = xstrdup (s);
  char *p = copy;
  for (; *p; p++)
    *p = TOLOWER (*p);
  return copy;
}

/* Return a count of how many times CHR occurs in STRING. */

int
count_char (const char *string, char chr)
{
  const char *p;
  int count = 0;
  for (p = string; *p; p++)
    if (*p == chr)
      ++count;
  return count;
}

/* Copy the string formed by two pointers (one on the beginning, other
   on the char after the last char) to a new, malloc-ed location.
   0-terminate it.  */
char *
strdupdelim (const char *beg, const char *end)
{
  char *res = (char *)xmalloc (end - beg + 1);
  memcpy (res, beg, end - beg);
  res[end - beg] = '\0';
  return res;
}

/* Parse a string containing comma-separated elements, and return a
   vector of char pointers with the elements.  Spaces following the
   commas are ignored.  */
char **
sepstring (const char *s)
{
  char **res;
  const char *p;
  int i = 0;

  if (!s || !*s)
    return NULL;
  res = NULL;
  p = s;
  while (*s)
    {
      if (*s == ',')
	{
	  res = (char **)xrealloc (res, (i + 2) * sizeof (char *));
	  res[i] = strdupdelim (p, s);
	  res[++i] = NULL;
	  ++s;
	  /* Skip the blanks following the ','.  */
	  while (ISSPACE (*s))
	    ++s;
	  p = s;
	}
      else
	++s;
    }
  res = (char **)xrealloc (res, (i + 2) * sizeof (char *));
  res[i] = strdupdelim (p, s);
  res[i + 1] = NULL;
  return res;
}

/* Return pointer to a static char[] buffer in which zero-terminated
   string-representation of TM (in form hh:mm:ss) is printed.

   If TM is non-NULL, the current time-in-seconds will be stored
   there.

   (#### This is misleading: one would expect TM would be used instead
   of the current time in that case.  This design was probably
   influenced by the design time(2), and should be changed at some
   points.  No callers use non-NULL TM anyway.)  */

char *
time_str (time_t *tm)
{
  static char output[15];
  struct tm *ptm;
  time_t secs = time (tm);

  if (secs == -1)
    {
      /* In case of error, return the empty string.  Maybe we should
	 just abort if this happens?  */
      *output = '\0';
      return output;
    }
  ptm = localtime (&secs);
  sprintf (output, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
  return output;
}

/* Like the above, but include the date: YYYY-MM-DD hh:mm:ss.  */

char *
datetime_str (time_t *tm)
{
  static char output[20];	/* "YYYY-MM-DD hh:mm:ss" + \0 */
  struct tm *ptm;
  time_t secs = time (tm);

  if (secs == -1)
    {
      /* In case of error, return the empty string.  Maybe we should
	 just abort if this happens?  */
      *output = '\0';
      return output;
    }
  ptm = localtime (&secs);
  sprintf (output, "%04d-%02d-%02d %02d:%02d:%02d",
	   ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
	   ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
  return output;
}

/* The Windows versions of the following two functions are defined in
   mswindows.c.  */

#ifndef WINDOWS
void
fork_to_background (void)
{
  pid_t pid;
  /* Whether we arrange our own version of opt.lfilename here.  */
  int changedp = 0;

  if (!opt.lfilename)
    {
      opt.lfilename = unique_name (DEFAULT_LOGFILE, 0);
      changedp = 1;
    }
  pid = fork ();
  if (pid < 0)
    {
      /* parent, error */
      perror ("fork");
      exit (1);
    }
  else if (pid != 0)
    {
      /* parent, no error */
      printf (_("Continuing in background, pid %d.\n"), (int)pid);
      if (changedp)
	printf (_("Output will be written to `%s'.\n"), opt.lfilename);
      exit (0);			/* #### should we use _exit()? */
    }

  /* child: give up the privileges and keep running. */
  setsid ();
  freopen ("/dev/null", "r", stdin);
  freopen ("/dev/null", "w", stdout);
  freopen ("/dev/null", "w", stderr);
}
#endif /* not WINDOWS */

/* "Touch" FILE, i.e. make its atime and mtime equal to the time
   specified with TM.  */
void
touch (const char *file, time_t tm)
{
#ifdef HAVE_STRUCT_UTIMBUF
  struct utimbuf times;
  times.actime = times.modtime = tm;
#else
  time_t times[2];
  times[0] = times[1] = tm;
#endif

  if (utime (file, &times) == -1)
    logprintf (LOG_NOTQUIET, "utime(%s): %s\n", file, strerror (errno));
}

/* Checks if FILE is a symbolic link, and removes it if it is.  Does
   nothing under MS-Windows.  */
int
remove_link (const char *file)
{
  int err = 0;
  struct stat st;

  if (lstat (file, &st) == 0 && S_ISLNK (st.st_mode))
    {
      DEBUGP (("Unlinking %s (symlink).\n", file));
      err = unlink (file);
      if (err != 0)
	logprintf (LOG_VERBOSE, _("Failed to unlink symlink `%s': %s\n"),
		   file, strerror (errno));
    }
  return err;
}

/* Does FILENAME exist?  This is quite a lousy implementation, since
   it supplies no error codes -- only a yes-or-no answer.  Thus it
   will return that a file does not exist if, e.g., the directory is
   unreadable.  I don't mind it too much currently, though.  The
   proper way should, of course, be to have a third, error state,
   other than true/false, but that would introduce uncalled-for
   additional complexity to the callers.  */
int
file_exists_p (const char *filename)
{
#ifdef HAVE_ACCESS
  return access (filename, F_OK) >= 0;
#else
  struct stat buf;
  return stat (filename, &buf) >= 0;
#endif
}

/* Returns 0 if PATH is a directory, 1 otherwise (any kind of file).
   Returns 0 on error.  */
int
file_non_directory_p (const char *path)
{
  struct stat buf;
  /* Use lstat() rather than stat() so that symbolic links pointing to
     directories can be identified correctly.  */
  if (lstat (path, &buf) != 0)
    return 0;
  return S_ISDIR (buf.st_mode) ? 0 : 1;
}

/* Return the size of file named by FILENAME, or -1 if it cannot be
   opened or seeked into. */
long
file_size (const char *filename)
{
  long size;
  /* We use fseek rather than stat to determine the file size because
     that way we can also verify whether the file is readable.
     Inspired by the POST patch by Arnaud Wylie.  */
  FILE *fp = fopen (filename, "rb");
  if (!fp)
    return -1;
  fseek (fp, 0, SEEK_END);
  size = ftell (fp);
  fclose (fp);
  return size;
}

/* stat file names named PREFIX.1, PREFIX.2, etc., until one that
   doesn't exist is found.  Return a freshly allocated copy of the
   unused file name.  */

static char *
unique_name_1 (const char *prefix)
{
  int count = 1;
  int plen = strlen (prefix);
  char *template = (char *)alloca (plen + 1 + 24);
  char *template_tail = template + plen;

  memcpy (template, prefix, plen);
  *template_tail++ = '.';

  do
    number_to_string (template_tail, count++);
  while (file_exists_p (template));

  return xstrdup (template);
}

/* Return a unique file name, based on FILE.

   More precisely, if FILE doesn't exist, it is returned unmodified.
   If not, FILE.1 is tried, then FILE.2, etc.  The first FILE.<number>
   file name that doesn't exist is returned.

   The resulting file is not created, only verified that it didn't
   exist at the point in time when the function was called.
   Therefore, where security matters, don't rely that the file created
   by this function exists until you open it with O_EXCL or
   something.

   If ALLOW_PASSTHROUGH is 0, it always returns a freshly allocated
   string.  Otherwise, it may return FILE if the file doesn't exist
   (and therefore doesn't need changing).  */

char *
unique_name (const char *file, int allow_passthrough)
{
  /* If the FILE itself doesn't exist, return it without
     modification. */
  if (!file_exists_p (file))
    return allow_passthrough ? (char *)file : xstrdup (file);

  /* Otherwise, find a numeric suffix that results in unused file name
     and return it.  */
  return unique_name_1 (file);
}

/* Create DIRECTORY.  If some of the pathname components of DIRECTORY
   are missing, create them first.  In case any mkdir() call fails,
   return its error status.  Returns 0 on successful completion.

   The behaviour of this function should be identical to the behaviour
   of `mkdir -p' on systems where mkdir supports the `-p' option.  */
int
make_directory (const char *directory)
{
  int quit = 0;
  int i;
  int ret = 0;
  char *dir;

  /* Make a copy of dir, to be able to write to it.  Otherwise, the
     function is unsafe if called with a read-only char *argument.  */
  STRDUP_ALLOCA (dir, directory);

  /* If the first character of dir is '/', skip it (and thus enable
     creation of absolute-pathname directories.  */
  for (i = (*dir == '/'); 1; ++i)
    {
      for (; dir[i] && dir[i] != '/'; i++)
	;
      if (!dir[i])
	quit = 1;
      dir[i] = '\0';
      /* Check whether the directory already exists.  Allow creation of
	 of intermediate directories to fail, as the initial path components
	 are not necessarily directories!  */
      if (!file_exists_p (dir))
	ret = mkdir (dir, 0777);
      else
	ret = 0;
      if (quit)
	break;
      else
	dir[i] = '/';
    }
  return ret;
}

/* Merge BASE with FILE.  BASE can be a directory or a file name, FILE
   should be a file name.

   file_merge("/foo/bar", "baz")  => "/foo/baz"
   file_merge("/foo/bar/", "baz") => "/foo/bar/baz"
   file_merge("foo", "bar")       => "bar"

   In other words, it's a simpler and gentler version of uri_merge_1.  */

char *
file_merge (const char *base, const char *file)
{
  char *result;
  const char *cut = (const char *)strrchr (base, '/');

  if (!cut)
    return xstrdup (file);

  result = (char *)xmalloc (cut - base + 1 + strlen (file) + 1);
  memcpy (result, base, cut - base);
  result[cut - base] = '/';
  strcpy (result + (cut - base) + 1, file);

  return result;
}

static int in_acclist PARAMS ((const char *const *, const char *, int));

/* Determine whether a file is acceptable to be followed, according to
   lists of patterns to accept/reject.  */
int
acceptable (const char *s)
{
  int l = strlen (s);

  while (l && s[l] != '/')
    --l;
  if (s[l] == '/')
    s += (l + 1);
  if (opt.accepts)
    {
      if (opt.rejects)
	return (in_acclist ((const char *const *)opt.accepts, s, 1)
		&& !in_acclist ((const char *const *)opt.rejects, s, 1));
      else
	return in_acclist ((const char *const *)opt.accepts, s, 1);
    }
  else if (opt.rejects)
    return !in_acclist ((const char *const *)opt.rejects, s, 1);
  return 1;
}

/* Compare S1 and S2 frontally; S2 must begin with S1.  E.g. if S1 is
   `/something', frontcmp() will return 1 only if S2 begins with
   `/something'.  Otherwise, 0 is returned.  */
int
frontcmp (const char *s1, const char *s2)
{
  for (; *s1 && *s2 && (*s1 == *s2); ++s1, ++s2);
  return !*s1;
}

/* Iterate through STRLIST, and return the first element that matches
   S, through wildcards or front comparison (as appropriate).  */
static char *
proclist (char **strlist, const char *s, enum accd flags)
{
  char **x;

  for (x = strlist; *x; x++)
    if (has_wildcards_p (*x))
      {
	if (fnmatch (*x, s, FNM_PATHNAME) == 0)
	  break;
      }
    else
      {
	char *p = *x + ((flags & ALLABS) && (**x == '/')); /* Remove '/' */
	if (frontcmp (p, s))
	  break;
      }
  return *x;
}

/* Returns whether DIRECTORY is acceptable for download, wrt the
   include/exclude lists.

   If FLAGS is ALLABS, the leading `/' is ignored in paths; relative
   and absolute paths may be freely intermixed.  */
int
accdir (const char *directory, enum accd flags)
{
  /* Remove starting '/'.  */
  if (flags & ALLABS && *directory == '/')
    ++directory;
  if (opt.includes)
    {
      if (!proclist (opt.includes, directory, flags))
	return 0;
    }
  if (opt.excludes)
    {
      if (proclist (opt.excludes, directory, flags))
	return 0;
    }
  return 1;
}

/* Return non-zero if STRING ends with TAIL.  For instance:

   match_tail ("abc", "bc", 0)  -> 1
   match_tail ("abc", "ab", 0)  -> 0
   match_tail ("abc", "abc", 0) -> 1

   If FOLD_CASE_P is non-zero, the comparison will be
   case-insensitive.  */

int
match_tail (const char *string, const char *tail, int fold_case_p)
{
  int i, j;

  /* We want this to be fast, so we code two loops, one with
     case-folding, one without. */

  if (!fold_case_p)
    {
      for (i = strlen (string), j = strlen (tail); i >= 0 && j >= 0; i--, j--)
	if (string[i] != tail[j])
	  break;
    }
  else
    {
      for (i = strlen (string), j = strlen (tail); i >= 0 && j >= 0; i--, j--)
	if (TOLOWER (string[i]) != TOLOWER (tail[j]))
	  break;
    }

  /* If the tail was exhausted, the match was succesful.  */
  if (j == -1)
    return 1;
  else
    return 0;
}

/* Checks whether string S matches each element of ACCEPTS.  A list
   element are matched either with fnmatch() or match_tail(),
   according to whether the element contains wildcards or not.

   If the BACKWARD is 0, don't do backward comparison -- just compare
   them normally.  */
static int
in_acclist (const char *const *accepts, const char *s, int backward)
{
  for (; *accepts; accepts++)
    {
      if (has_wildcards_p (*accepts))
	{
	  /* fnmatch returns 0 if the pattern *does* match the
	     string.  */
	  if (fnmatch (*accepts, s, 0) == 0)
	    return 1;
	}
      else
	{
	  if (backward)
	    {
	      if (match_tail (s, *accepts, 0))
		return 1;
	    }
	  else
	    {
	      if (!strcmp (s, *accepts))
		return 1;
	    }
	}
    }
  return 0;
}

/* Return the location of STR's suffix (file extension).  Examples:
   suffix ("foo.bar")       -> "bar"
   suffix ("foo.bar.baz")   -> "baz"
   suffix ("/foo/bar")      -> NULL
   suffix ("/foo.bar/baz")  -> NULL  */
char *
suffix (const char *str)
{
  int i;

  for (i = strlen (str); i && str[i] != '/' && str[i] != '.'; i--)
    ;

  if (str[i++] == '.')
    return (char *)str + i;
  else
    return NULL;
}

/* Return non-zero if S contains globbing wildcards (`*', `?', `[' or
   `]').  */

int
has_wildcards_p (const char *s)
{
  for (; *s; s++)
    if (*s == '*' || *s == '?' || *s == '[' || *s == ']')
      return 1;
  return 0;
}

/* Return non-zero if FNAME ends with a typical HTML suffix.  The
   following (case-insensitive) suffixes are presumed to be HTML files:
   
     html
     htm
     ?html (`?' matches one character)

   #### CAVEAT.  This is not necessarily a good indication that FNAME
   refers to a file that contains HTML!  */
int
has_html_suffix_p (const char *fname)
{
  char *suf;

  if ((suf = suffix (fname)) == NULL)
    return 0;
  if (!strcasecmp (suf, "html"))
    return 1;
  if (!strcasecmp (suf, "htm"))
    return 1;
  if (suf[0] && !strcasecmp (suf + 1, "html"))
    return 1;
  return 0;
}

/* Read a line from FP and return the pointer to freshly allocated
   storage.  The storage space is obtained through malloc() and should
   be freed with free() when it is no longer needed.

   The length of the line is not limited, except by available memory.
   The newline character at the end of line is retained.  The line is
   terminated with a zero character.

   After end-of-file is encountered without anything being read, NULL
   is returned.  NULL is also returned on error.  To distinguish
   between these two cases, use the stdio function ferror().  */

char *
read_whole_line (FILE *fp)
{
  int length = 0;
  int bufsize = 82;
  char *line = (char *)xmalloc (bufsize);

  while (fgets (line + length, bufsize - length, fp))
    {
      length += strlen (line + length);
      if (length == 0)
	/* Possible for example when reading from a binary file where
	   a line begins with \0.  */
	continue;

      if (line[length - 1] == '\n')
	break;

      /* fgets() guarantees to read the whole line, or to use up the
         space we've given it.  We can double the buffer
         unconditionally.  */
      bufsize <<= 1;
      line = xrealloc (line, bufsize);
    }
  if (length == 0 || ferror (fp))
    {
      xfree (line);
      return NULL;
    }
  if (length + 1 < bufsize)
    /* Relieve the memory from our exponential greediness.  We say
       `length + 1' because the terminating \0 is not included in
       LENGTH.  We don't need to zero-terminate the string ourselves,
       though, because fgets() does that.  */
    line = xrealloc (line, length + 1);
  return line;
}

/* Read FILE into memory.  A pointer to `struct file_memory' are
   returned; use struct element `content' to access file contents, and
   the element `length' to know the file length.  `content' is *not*
   zero-terminated, and you should *not* read or write beyond the [0,
   length) range of characters.

   After you are done with the file contents, call read_file_free to
   release the memory.

   Depending on the operating system and the type of file that is
   being read, read_file() either mmap's the file into memory, or
   reads the file into the core using read().

   If file is named "-", fileno(stdin) is used for reading instead.
   If you want to read from a real file named "-", use "./-" instead.  */

struct file_memory *
read_file (const char *file)
{
  int fd;
  struct file_memory *fm;
  long size;
  int inhibit_close = 0;

  /* Some magic in the finest tradition of Perl and its kin: if FILE
     is "-", just use stdin.  */
  if (HYPHENP (file))
    {
      fd = fileno (stdin);
      inhibit_close = 1;
      /* Note that we don't inhibit mmap() in this case.  If stdin is
         redirected from a regular file, mmap() will still work.  */
    }
  else
    fd = open (file, O_RDONLY);
  if (fd < 0)
    return NULL;
  fm = xmalloc (sizeof (struct file_memory));

#ifdef HAVE_MMAP
  {
    struct stat buf;
    if (fstat (fd, &buf) < 0)
      goto mmap_lose;
    fm->length = buf.st_size;
    /* NOTE: As far as I know, the callers of this function never
       modify the file text.  Relying on this would enable us to
       specify PROT_READ and MAP_SHARED for a marginal gain in
       efficiency, but at some cost to generality.  */
    fm->content = mmap (NULL, fm->length, PROT_READ | PROT_WRITE,
			MAP_PRIVATE, fd, 0);
    if (fm->content == (char *)MAP_FAILED)
      goto mmap_lose;
    if (!inhibit_close)
      close (fd);

    fm->mmap_p = 1;
    return fm;
  }

 mmap_lose:
  /* The most common reason why mmap() fails is that FD does not point
     to a plain file.  However, it's also possible that mmap() doesn't
     work for a particular type of file.  Therefore, whenever mmap()
     fails, we just fall back to the regular method.  */
#endif /* HAVE_MMAP */

  fm->length = 0;
  size = 512;			/* number of bytes fm->contents can
                                   hold at any given time. */
  fm->content = xmalloc (size);
  while (1)
    {
      long nread;
      if (fm->length > size / 2)
	{
	  /* #### I'm not sure whether the whole exponential-growth
             thing makes sense with kernel read.  On Linux at least,
             read() refuses to read more than 4K from a file at a
             single chunk anyway.  But other Unixes might optimize it
             better, and it doesn't *hurt* anything, so I'm leaving
             it.  */

	  /* Normally, we grow SIZE exponentially to make the number
             of calls to read() and realloc() logarithmic in relation
             to file size.  However, read() can read an amount of data
             smaller than requested, and it would be unreasonable to
             double SIZE every time *something* was read.  Therefore,
             we double SIZE only when the length exceeds half of the
             entire allocated size.  */
	  size <<= 1;
	  fm->content = xrealloc (fm->content, size);
	}
      nread = read (fd, fm->content + fm->length, size - fm->length);
      if (nread > 0)
	/* Successful read. */
	fm->length += nread;
      else if (nread < 0)
	/* Error. */
	goto lose;
      else
	/* EOF */
	break;
    }
  if (!inhibit_close)
    close (fd);
  if (size > fm->length && fm->length != 0)
    /* Due to exponential growth of fm->content, the allocated region
       might be much larger than what is actually needed.  */
    fm->content = xrealloc (fm->content, fm->length);
  fm->mmap_p = 0;
  return fm;

 lose:
  if (!inhibit_close)
    close (fd);
  xfree (fm->content);
  xfree (fm);
  return NULL;
}

/* Release the resources held by FM.  Specifically, this calls
   munmap() or xfree() on fm->content, depending whether mmap or
   malloc/read were used to read in the file.  It also frees the
   memory needed to hold the FM structure itself.  */

void
read_file_free (struct file_memory *fm)
{
#ifdef HAVE_MMAP
  if (fm->mmap_p)
    {
      munmap (fm->content, fm->length);
    }
  else
#endif
    {
      xfree (fm->content);
    }
  xfree (fm);
}

/* Free the pointers in a NULL-terminated vector of pointers, then
   free the pointer itself.  */
void
free_vec (char **vec)
{
  if (vec)
    {
      char **p = vec;
      while (*p)
	xfree (*p++);
      xfree (vec);
    }
}

/* Append vector V2 to vector V1.  The function frees V2 and
   reallocates V1 (thus you may not use the contents of neither
   pointer after the call).  If V1 is NULL, V2 is returned.  */
char **
merge_vecs (char **v1, char **v2)
{
  int i, j;

  if (!v1)
    return v2;
  if (!v2)
    return v1;
  if (!*v2)
    {
      /* To avoid j == 0 */
      xfree (v2);
      return v1;
    }
  /* Count v1.  */
  for (i = 0; v1[i]; i++);
  /* Count v2.  */
  for (j = 0; v2[j]; j++);
  /* Reallocate v1.  */
  v1 = (char **)xrealloc (v1, (i + j + 1) * sizeof (char **));
  memcpy (v1 + i, v2, (j + 1) * sizeof (char *));
  xfree (v2);
  return v1;
}

/* A set of simple-minded routines to store strings in a linked list.
   This used to also be used for searching, but now we have hash
   tables for that.  */

/* It's a shame that these simple things like linked lists and hash
   tables (see hash.c) need to be implemented over and over again.  It
   would be nice to be able to use the routines from glib -- see
   www.gtk.org for details.  However, that would make Wget depend on
   glib, and I want to avoid dependencies to external libraries for
   reasons of convenience and portability (I suspect Wget is more
   portable than anything ever written for Gnome).  */

/* Append an element to the list.  If the list has a huge number of
   elements, this can get slow because it has to find the list's
   ending.  If you think you have to call slist_append in a loop,
   think about calling slist_prepend() followed by slist_nreverse().  */

slist *
slist_append (slist *l, const char *s)
{
  slist *newel = (slist *)xmalloc (sizeof (slist));
  slist *beg = l;

  newel->string = xstrdup (s);
  newel->next = NULL;

  if (!l)
    return newel;
  /* Find the last element.  */
  while (l->next)
    l = l->next;
  l->next = newel;
  return beg;
}

/* Prepend S to the list.  Unlike slist_append(), this is O(1).  */

slist *
slist_prepend (slist *l, const char *s)
{
  slist *newel = (slist *)xmalloc (sizeof (slist));
  newel->string = xstrdup (s);
  newel->next = l;
  return newel;
}

/* Destructively reverse L. */

slist *
slist_nreverse (slist *l)
{
  slist *prev = NULL;
  while (l)
    {
      slist *next = l->next;
      l->next = prev;
      prev = l;
      l = next;
    }
  return prev;
}

/* Is there a specific entry in the list?  */
int
slist_contains (slist *l, const char *s)
{
  for (; l; l = l->next)
    if (!strcmp (l->string, s))
      return 1;
  return 0;
}

/* Free the whole slist.  */
void
slist_free (slist *l)
{
  while (l)
    {
      slist *n = l->next;
      xfree (l->string);
      xfree (l);
      l = n;
    }
}

/* Sometimes it's useful to create "sets" of strings, i.e. special
   hash tables where you want to store strings as keys and merely
   query for their existence.  Here is a set of utility routines that
   makes that transparent.  */

void
string_set_add (struct hash_table *ht, const char *s)
{
  /* First check whether the set element already exists.  If it does,
     do nothing so that we don't have to free() the old element and
     then strdup() a new one.  */
  if (hash_table_contains (ht, s))
    return;

  /* We use "1" as value.  It provides us a useful and clear arbitrary
     value, and it consumes no memory -- the pointers to the same
     string "1" will be shared by all the key-value pairs in all `set'
     hash tables.  */
  hash_table_put (ht, xstrdup (s), "1");
}

/* Synonym for hash_table_contains... */

int
string_set_contains (struct hash_table *ht, const char *s)
{
  return hash_table_contains (ht, s);
}

static int
string_set_free_mapper (void *key, void *value_ignored, void *arg_ignored)
{
  xfree (key);
  return 0;
}

void
string_set_free (struct hash_table *ht)
{
  hash_table_map (ht, string_set_free_mapper, NULL);
  hash_table_destroy (ht);
}

static int
free_keys_and_values_mapper (void *key, void *value, void *arg_ignored)
{
  xfree (key);
  xfree (value);
  return 0;
}

/* Another utility function: call free() on all keys and values of HT.  */

void
free_keys_and_values (struct hash_table *ht)
{
  hash_table_map (ht, free_keys_and_values_mapper, NULL);
}


/* Engine for legible and legible_large_int; add thousand separators
   to numbers printed in strings.  */

static char *
legible_1 (const char *repr)
{
  static char outbuf[48];
  int i, i1, mod;
  char *outptr;
  const char *inptr;

  /* Reset the pointers.  */
  outptr = outbuf;
  inptr = repr;

  /* Ignore the sign for the purpose of adding thousand
     separators.  */
  if (*inptr == '-')
    {
      *outptr++ = '-';
      ++inptr;
    }
  /* How many digits before the first separator?  */
  mod = strlen (inptr) % 3;
  /* Insert them.  */
  for (i = 0; i < mod; i++)
    *outptr++ = inptr[i];
  /* Now insert the rest of them, putting separator before every
     third digit.  */
  for (i1 = i, i = 0; inptr[i1]; i++, i1++)
    {
      if (i % 3 == 0 && i1 != 0)
	*outptr++ = ',';
      *outptr++ = inptr[i1];
    }
  /* Zero-terminate the string.  */
  *outptr = '\0';
  return outbuf;
}

/* Legible -- return a static pointer to the legibly printed long.  */

char *
legible (long l)
{
  char inbuf[24];
  /* Print the number into the buffer.  */
  number_to_string (inbuf, l);
  return legible_1 (inbuf);
}

/* Write a string representation of LARGE_INT NUMBER into the provided
   buffer.  The buffer should be able to accept 24 characters,
   including the terminating zero.

   It would be dangerous to use sprintf, because the code wouldn't
   work on a machine with gcc-provided long long support, but without
   libc support for "%lld".  However, such platforms will typically
   not have snprintf and will use our version, which does support
   "%lld" where long longs are available.  */

static void
large_int_to_string (char *buffer, LARGE_INT number)
{
  snprintf (buffer, 24, LARGE_INT_FMT, number);
}

/* The same as legible(), but works on LARGE_INT.  */

char *
legible_large_int (LARGE_INT l)
{
  char inbuf[48];
  large_int_to_string (inbuf, l);
  return legible_1 (inbuf);
}

/* Count the digits in a (long) integer.  */
int
numdigit (long number)
{
  int cnt = 1;
  if (number < 0)
    {
      number = -number;
      ++cnt;
    }
  while ((number /= 10) > 0)
    ++cnt;
  return cnt;
}

/* A half-assed implementation of INT_MAX on machines that don't
   bother to define one. */
#ifndef INT_MAX
# define INT_MAX ((int) ~((unsigned)1 << 8 * sizeof (int) - 1))
#endif

#define ONE_DIGIT(figure) *p++ = n / (figure) + '0'
#define ONE_DIGIT_ADVANCE(figure) (ONE_DIGIT (figure), n %= (figure))

#define DIGITS_1(figure) ONE_DIGIT (figure)
#define DIGITS_2(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_1 ((figure) / 10)
#define DIGITS_3(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_2 ((figure) / 10)
#define DIGITS_4(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_3 ((figure) / 10)
#define DIGITS_5(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_4 ((figure) / 10)
#define DIGITS_6(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_5 ((figure) / 10)
#define DIGITS_7(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_6 ((figure) / 10)
#define DIGITS_8(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_7 ((figure) / 10)
#define DIGITS_9(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_8 ((figure) / 10)
#define DIGITS_10(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_9 ((figure) / 10)

/* DIGITS_<11-20> are only used on machines with 64-bit longs. */

#define DIGITS_11(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_10 ((figure) / 10)
#define DIGITS_12(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_11 ((figure) / 10)
#define DIGITS_13(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_12 ((figure) / 10)
#define DIGITS_14(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_13 ((figure) / 10)
#define DIGITS_15(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_14 ((figure) / 10)
#define DIGITS_16(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_15 ((figure) / 10)
#define DIGITS_17(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_16 ((figure) / 10)
#define DIGITS_18(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_17 ((figure) / 10)
#define DIGITS_19(figure) ONE_DIGIT_ADVANCE (figure); DIGITS_18 ((figure) / 10)

/* Print NUMBER to BUFFER in base 10.  This should be completely
   equivalent to `sprintf(buffer, "%ld", number)', only much faster.

   The speedup may make a difference in programs that frequently
   convert numbers to strings.  Some implementations of sprintf,
   particularly the one in GNU libc, have been known to be extremely
   slow compared to this function.

   Return the pointer to the location where the terminating zero was
   printed.  (Equivalent to calling buffer+strlen(buffer) after the
   function is done.)

   BUFFER should be big enough to accept as many bytes as you expect
   the number to take up.  On machines with 64-bit longs the maximum
   needed size is 24 bytes.  That includes the digits needed for the
   largest 64-bit number, the `-' sign in case it's negative, and the
   terminating '\0'.  */

char *
number_to_string (char *buffer, long number)
{
  char *p = buffer;
  long n = number;

#if (SIZEOF_LONG != 4) && (SIZEOF_LONG != 8)
  /* We are running in a strange or misconfigured environment.  Let
     sprintf cope with it.  */
  sprintf (buffer, "%ld", n);
  p += strlen (buffer);
#else  /* (SIZEOF_LONG == 4) || (SIZEOF_LONG == 8) */

  if (n < 0)
    {
      if (n < -INT_MAX)
	{
	  /* We cannot print a '-' and assign -n to n because -n would
	     overflow.  Let sprintf deal with this border case.  */
	  sprintf (buffer, "%ld", n);
	  p += strlen (buffer);
	  return p;
	}

      *p++ = '-';
      n = -n;
    }

  if      (n < 10)                   { DIGITS_1 (1); }
  else if (n < 100)                  { DIGITS_2 (10); }
  else if (n < 1000)                 { DIGITS_3 (100); }
  else if (n < 10000)                { DIGITS_4 (1000); }
  else if (n < 100000)               { DIGITS_5 (10000); }
  else if (n < 1000000)              { DIGITS_6 (100000); }
  else if (n < 10000000)             { DIGITS_7 (1000000); }
  else if (n < 100000000)            { DIGITS_8 (10000000); }
  else if (n < 1000000000)           { DIGITS_9 (100000000); }
#if SIZEOF_LONG == 4
  /* ``if (1)'' serves only to preserve editor indentation. */
  else if (1)                        { DIGITS_10 (1000000000); }
#else  /* SIZEOF_LONG != 4 */
  else if (n < 10000000000L)         { DIGITS_10 (1000000000L); }
  else if (n < 100000000000L)        { DIGITS_11 (10000000000L); }
  else if (n < 1000000000000L)       { DIGITS_12 (100000000000L); }
  else if (n < 10000000000000L)      { DIGITS_13 (1000000000000L); }
  else if (n < 100000000000000L)     { DIGITS_14 (10000000000000L); }
  else if (n < 1000000000000000L)    { DIGITS_15 (100000000000000L); }
  else if (n < 10000000000000000L)   { DIGITS_16 (1000000000000000L); }
  else if (n < 100000000000000000L)  { DIGITS_17 (10000000000000000L); }
  else if (n < 1000000000000000000L) { DIGITS_18 (100000000000000000L); }
  else                               { DIGITS_19 (1000000000000000000L); }
#endif /* SIZEOF_LONG != 4 */

  *p = '\0';
#endif /* (SIZEOF_LONG == 4) || (SIZEOF_LONG == 8) */

  return p;
}

#undef ONE_DIGIT
#undef ONE_DIGIT_ADVANCE

#undef DIGITS_1
#undef DIGITS_2
#undef DIGITS_3
#undef DIGITS_4
#undef DIGITS_5
#undef DIGITS_6
#undef DIGITS_7
#undef DIGITS_8
#undef DIGITS_9
#undef DIGITS_10
#undef DIGITS_11
#undef DIGITS_12
#undef DIGITS_13
#undef DIGITS_14
#undef DIGITS_15
#undef DIGITS_16
#undef DIGITS_17
#undef DIGITS_18
#undef DIGITS_19

/* Support for timers. */

#undef TIMER_WINDOWS
#undef TIMER_GETTIMEOFDAY
#undef TIMER_TIME

/* Depending on the OS and availability of gettimeofday(), one and
   only one of the above constants will be defined.  Virtually all
   modern Unix systems will define TIMER_GETTIMEOFDAY; Windows will
   use TIMER_WINDOWS.  TIMER_TIME is a catch-all method for
   non-Windows systems without gettimeofday.

   #### Perhaps we should also support ftime(), which exists on old
   BSD 4.2-influenced systems?  (It also existed under MS DOS Borland
   C, if memory serves me.)  */

#ifdef WINDOWS
# define TIMER_WINDOWS
#else  /* not WINDOWS */
# ifdef HAVE_GETTIMEOFDAY
#  define TIMER_GETTIMEOFDAY
# else
#  define TIMER_TIME
# endif
#endif /* not WINDOWS */

#ifdef TIMER_GETTIMEOFDAY
typedef struct timeval wget_sys_time;
#endif

#ifdef TIMER_TIME
typedef time_t wget_sys_time;
#endif

#ifdef TIMER_WINDOWS
typedef ULARGE_INTEGER wget_sys_time;
#endif

struct wget_timer {
  /* The starting point in time which, subtracted from the current
     time, yields elapsed time. */
  wget_sys_time start;

  /* The most recent elapsed time, calculated by wtimer_elapsed().
     Measured in milliseconds.  */
  double elapsed_last;

  /* Approximately, the time elapsed between the true start of the
     measurement and the time represented by START.  */
  double elapsed_pre_start;
};

/* Allocate a timer.  It is not legal to do anything with a freshly
   allocated timer, except call wtimer_reset() or wtimer_delete().  */

struct wget_timer *
wtimer_allocate (void)
{
  struct wget_timer *wt =
    (struct wget_timer *)xmalloc (sizeof (struct wget_timer));
  return wt;
}

/* Allocate a new timer and reset it.  Return the new timer. */

struct wget_timer *
wtimer_new (void)
{
  struct wget_timer *wt = wtimer_allocate ();
  wtimer_reset (wt);
  return wt;
}

/* Free the resources associated with the timer.  Its further use is
   prohibited.  */

void
wtimer_delete (struct wget_timer *wt)
{
  xfree (wt);
}

/* Store system time to WST.  */

static void
wtimer_sys_set (wget_sys_time *wst)
{
#ifdef TIMER_GETTIMEOFDAY
  gettimeofday (wst, NULL);
#endif

#ifdef TIMER_TIME
  time (wst);
#endif

#ifdef TIMER_WINDOWS
  /* We use GetSystemTime to get the elapsed time.  MSDN warns that
     system clock adjustments can skew the output of GetSystemTime
     when used as a timer and gives preference to GetTickCount and
     high-resolution timers.  But GetTickCount can overflow, and hires
     timers are typically used for profiling, not for regular time
     measurement.  Since we handle clock skew anyway, we just use
     GetSystemTime.  */
  FILETIME ft;
  SYSTEMTIME st;
  GetSystemTime (&st);

  /* As recommended by MSDN, we convert SYSTEMTIME to FILETIME, copy
     FILETIME to ULARGE_INTEGER, and use regular 64-bit integer
     arithmetic on that.  */
  SystemTimeToFileTime (&st, &ft);
  wst->HighPart = ft.dwHighDateTime;
  wst->LowPart  = ft.dwLowDateTime;
#endif
}

/* Reset timer WT.  This establishes the starting point from which
   wtimer_elapsed() will return the number of elapsed
   milliseconds.  It is allowed to reset a previously used timer.  */

void
wtimer_reset (struct wget_timer *wt)
{
  /* Set the start time to the current time. */
  wtimer_sys_set (&wt->start);
  wt->elapsed_last = 0;
  wt->elapsed_pre_start = 0;
}

static double
wtimer_sys_diff (wget_sys_time *wst1, wget_sys_time *wst2)
{
#ifdef TIMER_GETTIMEOFDAY
  return ((double)(wst1->tv_sec - wst2->tv_sec) * 1000
	  + (double)(wst1->tv_usec - wst2->tv_usec) / 1000);
#endif

#ifdef TIMER_TIME
  return 1000 * (*wst1 - *wst2);
#endif

#ifdef WINDOWS
  /* VC++ 6 doesn't support direct cast of uint64 to double.  To work
     around this, we subtract, then convert to signed, then finally to
     double.  */
  return (double)(signed __int64)(wst1->QuadPart - wst2->QuadPart) / 10000;
#endif
}

/* Return the number of milliseconds elapsed since the timer was last
   reset.  It is allowed to call this function more than once to get
   increasingly higher elapsed values.  These timers handle clock
   skew.  */

double
wtimer_elapsed (struct wget_timer *wt)
{
  wget_sys_time now;
  double elapsed;

  wtimer_sys_set (&now);
  elapsed = wt->elapsed_pre_start + wtimer_sys_diff (&now, &wt->start);

  /* Ideally we'd just return the difference between NOW and
     wt->start.  However, the system timer can be set back, and we
     could return a value smaller than when we were last called, even
     a negative value.  Both of these would confuse the callers, which
     expect us to return monotonically nondecreasing values.

     Therefore: if ELAPSED is smaller than its previous known value,
     we reset wt->start to the current time and effectively start
     measuring from this point.  But since we don't want the elapsed
     value to start from zero, we set elapsed_pre_start to the last
     elapsed time and increment all future calculations by that
     amount.  */

  if (elapsed < wt->elapsed_last)
    {
      wt->start = now;
      wt->elapsed_pre_start = wt->elapsed_last;
      elapsed = wt->elapsed_last;
    }

  wt->elapsed_last = elapsed;
  return elapsed;
}

/* Return the assessed granularity of the timer implementation, in
   milliseconds.  This is used by code that tries to substitute a
   better value for timers that have returned zero.  */

double
wtimer_granularity (void)
{
#ifdef TIMER_GETTIMEOFDAY
  /* Granularity of gettimeofday varies wildly between architectures.
     However, it appears that on modern machines it tends to be better
     than 1ms.  Assume 100 usecs.  (Perhaps the configure process
     could actually measure this?)  */
  return 0.1;
#endif

#ifdef TIMER_TIME
  return 1000;
#endif

#ifdef TIMER_WINDOWS
  /* According to MSDN, GetSystemTime returns a broken-down time
     structure the smallest member of which are milliseconds.  */
  return 1;
#endif
}

/* This should probably be at a better place, but it doesn't really
   fit into html-parse.c.  */

/* The function returns the pointer to the malloc-ed quoted version of
   string s.  It will recognize and quote numeric and special graphic
   entities, as per RFC1866:

   `&' -> `&amp;'
   `<' -> `&lt;'
   `>' -> `&gt;'
   `"' -> `&quot;'
   SP  -> `&#32;'

   No other entities are recognized or replaced.  */
char *
html_quote_string (const char *s)
{
  const char *b = s;
  char *p, *res;
  int i;

  /* Pass through the string, and count the new size.  */
  for (i = 0; *s; s++, i++)
    {
      if (*s == '&')
	i += 4;			/* `amp;' */
      else if (*s == '<' || *s == '>')
	i += 3;			/* `lt;' and `gt;' */
      else if (*s == '\"')
	i += 5;			/* `quot;' */
      else if (*s == ' ')
	i += 4;			/* #32; */
    }
  res = (char *)xmalloc (i + 1);
  s = b;
  for (p = res; *s; s++)
    {
      switch (*s)
	{
	case '&':
	  *p++ = '&';
	  *p++ = 'a';
	  *p++ = 'm';
	  *p++ = 'p';
	  *p++ = ';';
	  break;
	case '<': case '>':
	  *p++ = '&';
	  *p++ = (*s == '<' ? 'l' : 'g');
	  *p++ = 't';
	  *p++ = ';';
	  break;
	case '\"':
	  *p++ = '&';
	  *p++ = 'q';
	  *p++ = 'u';
	  *p++ = 'o';
	  *p++ = 't';
	  *p++ = ';';
	  break;
	case ' ':
	  *p++ = '&';
	  *p++ = '#';
	  *p++ = '3';
	  *p++ = '2';
	  *p++ = ';';
	  break;
	default:
	  *p++ = *s;
	}
    }
  *p = '\0';
  return res;
}

/* Determine the width of the terminal we're running on.  If that's
   not possible, return 0.  */

int
determine_screen_width (void)
{
  /* If there's a way to get the terminal size using POSIX
     tcgetattr(), somebody please tell me.  */
#ifndef TIOCGWINSZ
  return 0;
#else  /* TIOCGWINSZ */
  int fd;
  struct winsize wsz;

  if (opt.lfilename != NULL)
    return 0;

  fd = fileno (stderr);
  if (ioctl (fd, TIOCGWINSZ, &wsz) < 0)
    return 0;			/* most likely ENOTTY */

  return wsz.ws_col;
#endif /* TIOCGWINSZ */
}

/* Return a random number between 0 and MAX-1, inclusive.

   If MAX is greater than the value of RAND_MAX+1 on the system, the
   returned value will be in the range [0, RAND_MAX].  This may be
   fixed in a future release.

   The random number generator is seeded automatically the first time
   it is called.

   This uses rand() for portability.  It has been suggested that
   random() offers better randomness, but this is not required for
   Wget, so I chose to go for simplicity and use rand
   unconditionally.

   DO NOT use this for cryptographic purposes.  It is only meant to be
   used in situations where quality of the random numbers returned
   doesn't really matter.  */

int
random_number (int max)
{
  static int seeded;
  double bounded;
  int rnd;

  if (!seeded)
    {
      srand (time (NULL));
      seeded = 1;
    }
  rnd = rand ();

  /* On systems that don't define RAND_MAX, assume it to be 2**15 - 1,
     and enforce that assumption by masking other bits.  */
#ifndef RAND_MAX
# define RAND_MAX 32767
  rnd &= RAND_MAX;
#endif

  /* This is equivalent to rand() % max, but uses the high-order bits
     for better randomness on architecture where rand() is implemented
     using a simple congruential generator.  */

  bounded = (double)max * rnd / (RAND_MAX + 1.0);
  return (int)bounded;
}

/* Return a random uniformly distributed floating point number in the
   [0, 1) range.  The precision of returned numbers is 9 digits.

   Modify this to use erand48() where available!  */

double
random_float (void)
{
  /* We can't rely on any specific value of RAND_MAX, but I'm pretty
     sure it's greater than 1000.  */
  int rnd1 = random_number (1000);
  int rnd2 = random_number (1000);
  int rnd3 = random_number (1000);
  return rnd1 / 1000.0 + rnd2 / 1000000.0 + rnd3 / 1000000000.0;
}

#if 0
/* A debugging function for checking whether an MD5 library works. */

#include "gen-md5.h"

char *
debug_test_md5 (char *buf)
{
  unsigned char raw[16];
  static char res[33];
  unsigned char *p1;
  char *p2;
  int cnt;
  ALLOCA_MD5_CONTEXT (ctx);

  gen_md5_init (ctx);
  gen_md5_update ((unsigned char *)buf, strlen (buf), ctx);
  gen_md5_finish (ctx, raw);

  p1 = raw;
  p2 = res;
  cnt = 16;
  while (cnt--)
    {
      *p2++ = XNUM_TO_digit (*p1 >> 4);
      *p2++ = XNUM_TO_digit (*p1 & 0xf);
      ++p1;
    }
  *p2 = '\0';

  return res;
}
#endif

/* Implementation of run_with_timeout, a generic timeout-forcing
   routine for systems with Unix-like signal handling.  */

#ifdef USE_SIGNAL_TIMEOUT
# ifdef HAVE_SIGSETJMP
#  define SETJMP(env) sigsetjmp (env, 1)

static sigjmp_buf run_with_timeout_env;

static RETSIGTYPE
abort_run_with_timeout (int sig)
{
  assert (sig == SIGALRM);
  siglongjmp (run_with_timeout_env, -1);
}
# else /* not HAVE_SIGSETJMP */
#  define SETJMP(env) setjmp (env)

static jmp_buf run_with_timeout_env;

static RETSIGTYPE
abort_run_with_timeout (int sig)
{
  assert (sig == SIGALRM);
  /* We don't have siglongjmp to preserve the set of blocked signals;
     if we longjumped out of the handler at this point, SIGALRM would
     remain blocked.  We must unblock it manually. */
  int mask = siggetmask ();
  mask &= ~sigmask (SIGALRM);
  sigsetmask (mask);

  /* Now it's safe to longjump. */
  longjmp (run_with_timeout_env, -1);
}
# endif /* not HAVE_SIGSETJMP */

/* Arrange for SIGALRM to be delivered in TIMEOUT seconds.  This uses
   setitimer where available, alarm otherwise.

   TIMEOUT should be non-zero.  If the timeout value is so small that
   it would be rounded to zero, it is rounded to the least legal value
   instead (1us for setitimer, 1s for alarm).  That ensures that
   SIGALRM will be delivered in all cases.  */

static void
alarm_set (double timeout)
{
#ifdef ITIMER_REAL
  /* Use the modern itimer interface. */
  struct itimerval itv;
  memset (&itv, 0, sizeof (itv));
  itv.it_value.tv_sec = (long) timeout;
  itv.it_value.tv_usec = 1000000L * (timeout - (long)timeout);
  if (itv.it_value.tv_sec == 0 && itv.it_value.tv_usec == 0)
    /* Ensure that we wait for at least the minimum interval.
       Specifying zero would mean "wait forever".  */
    itv.it_value.tv_usec = 1;
  setitimer (ITIMER_REAL, &itv, NULL);
#else  /* not ITIMER_REAL */
  /* Use the old alarm() interface. */
  int secs = (int) timeout;
  if (secs == 0)
    /* Round TIMEOUTs smaller than 1 to 1, not to zero.  This is
       because alarm(0) means "never deliver the alarm", i.e. "wait
       forever", which is not what someone who specifies a 0.5s
       timeout would expect.  */
    secs = 1;
  alarm (secs);
#endif /* not ITIMER_REAL */
}

/* Cancel the alarm set with alarm_set. */

static void
alarm_cancel (void)
{
#ifdef ITIMER_REAL
  struct itimerval disable;
  memset (&disable, 0, sizeof (disable));
  setitimer (ITIMER_REAL, &disable, NULL);
#else  /* not ITIMER_REAL */
  alarm (0);
#endif /* not ITIMER_REAL */
}

/* Call FUN(ARG), but don't allow it to run for more than TIMEOUT
   seconds.  Returns non-zero if the function was interrupted with a
   timeout, zero otherwise.

   This works by setting up SIGALRM to be delivered in TIMEOUT seconds
   using setitimer() or alarm().  The timeout is enforced by
   longjumping out of the SIGALRM handler.  This has several
   advantages compared to the traditional approach of relying on
   signals causing system calls to exit with EINTR:

     * The callback function is *forcibly* interrupted after the
       timeout expires, (almost) regardless of what it was doing and
       whether it was in a syscall.  For example, a calculation that
       takes a long time is interrupted as reliably as an IO
       operation.

     * It works with both SYSV and BSD signals because it doesn't
       depend on the default setting of SA_RESTART.

     * It doesn't special handler setup beyond a simple call to
       signal().  (It does use sigsetjmp/siglongjmp, but they're
       optional.)

   The only downside is that, if FUN allocates internal resources that
   are normally freed prior to exit from the functions, they will be
   lost in case of timeout.  */

int
run_with_timeout (double timeout, void (*fun) (void *), void *arg)
{
  int saved_errno;

  if (timeout == 0)
    {
      fun (arg);
      return 0;
    }

  signal (SIGALRM, abort_run_with_timeout);
  if (SETJMP (run_with_timeout_env) != 0)
    {
      /* Longjumped out of FUN with a timeout. */
      signal (SIGALRM, SIG_DFL);
      return 1;
    }
  alarm_set (timeout);
  fun (arg);

  /* Preserve errno in case alarm() or signal() modifies it. */
  saved_errno = errno;
  alarm_cancel ();
  signal (SIGALRM, SIG_DFL);
  errno = saved_errno;

  return 0;
}

#else  /* not USE_SIGNAL_TIMEOUT */

#ifndef WINDOWS
/* A stub version of run_with_timeout that just calls FUN(ARG).  Don't
   define it under Windows, because Windows has its own version of
   run_with_timeout that uses threads.  */

int
run_with_timeout (double timeout, void (*fun) (void *), void *arg)
{
  fun (arg);
  return 0;
}
#endif /* not WINDOWS */
#endif /* not USE_SIGNAL_TIMEOUT */
