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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

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

#include "wget.h"
#include "utils.h"
#include "fnmatch.h"
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
  /* HACK: expose save_log_p from log.c, so we can turn it off in
     order to prevent saving the log.  Saving the log is dangerous
     because logprintf() and logputs() can call malloc(), so this
     could infloop.  When logging is turned off, infloop can no longer
     happen.

     #### This is no longer really necessary because the new routines
     in log.c cons only if the line exceeds eighty characters.  But
     this can come at the end of a line, so it's OK to be careful.

     On a more serious note, it would be good to have a
     log_forced_shutdown() routine that exposes this cleanly.  */
  extern int save_log_p;

  save_log_p = 0;
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
  for (i = 0; i < ARRAY_SIZE (malloc_debug); i++)
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
  for (i = 0; i < ARRAY_SIZE (malloc_debug); i++)
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
  for (i = 0; i < ARRAY_SIZE (malloc_debug); i++)
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

/* Returns an error message for ERRNUM.  #### This requires more work.
   This function, as well as the whole error system, is very
   ill-conceived.  */
const char *
uerrmsg (uerr_t errnum)
{
  switch (errnum)
    {
    case URLUNKNOWN:
      return _("Unknown/unsupported protocol");
      break;
    case URLBADPORT:
      return _("Invalid port specification");
      break;
    case URLBADHOST:
      return _("Invalid host name");
      break;
    default:
      abort ();
      /* $@#@#$ compiler.  */
      return NULL;
    }
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
      opt.lfilename = unique_name (DEFAULT_LOGFILE);
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
      printf (_("Continuing in background.\n"));
      if (changedp)
	printf (_("Output will be written to `%s'.\n"), opt.lfilename);
      exit (0);
    }
  /* child: keep running */
}
#endif /* not WINDOWS */

/* Canonicalize PATH, and return a new path.  The new path differs from PATH
   in that:
	Multple `/'s are collapsed to a single `/'.
	Leading `./'s and trailing `/.'s are removed.
	Trailing `/'s are removed.
	Non-leading `../'s and trailing `..'s are handled by removing
	portions of the path.

   E.g. "a/b/c/./../d/.." will yield "a/b".  This function originates
   from GNU Bash.

   Changes for Wget:
	Always use '/' as stub_char.
	Don't check for local things using canon_stat.
	Change the original string instead of strdup-ing.
	React correctly when beginning with `./' and `../'.  */
void
path_simplify (char *path)
{
  register int i, start, ddot;
  char stub_char;

  if (!*path)
    return;

  /*stub_char = (*path == '/') ? '/' : '.';*/
  stub_char = '/';

  /* Addition: Remove all `./'-s preceding the string.  If `../'-s
     precede, put `/' in front and remove them too.  */
  i = 0;
  ddot = 0;
  while (1)
    {
      if (path[i] == '.' && path[i + 1] == '/')
	i += 2;
      else if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
	{
	  i += 3;
	  ddot = 1;
	}
      else
	break;
    }
  if (i)
    strcpy (path, path + i - ddot);

  /* Replace single `.' or `..' with `/'.  */
  if ((path[0] == '.' && path[1] == '\0')
      || (path[0] == '.' && path[1] == '.' && path[2] == '\0'))
    {
      path[0] = stub_char;
      path[1] = '\0';
      return;
    }
  /* Walk along PATH looking for things to compact.  */
  i = 0;
  while (1)
    {
      if (!path[i])
	break;

      while (path[i] && path[i] != '/')
	i++;

      start = i++;

      /* If we didn't find any slashes, then there is nothing left to do.  */
      if (!path[start])
	break;

      /* Handle multiple `/'s in a row.  */
      while (path[i] == '/')
	i++;

      if ((start + 1) != i)
	{
	  strcpy (path + start + 1, path + i);
	  i = start + 1;
	}

      /* Check for trailing `/'.  */
      if (start && !path[i])
	{
	zero_last:
	  path[--i] = '\0';
	  break;
	}

      /* Check for `../', `./' or trailing `.' by itself.  */
      if (path[i] == '.')
	{
	  /* Handle trailing `.' by itself.  */
	  if (!path[i + 1])
	    goto zero_last;

	  /* Handle `./'.  */
	  if (path[i + 1] == '/')
	    {
	      strcpy (path + i, path + i + 1);
	      i = (start < 0) ? 0 : start;
	      continue;
	    }

	  /* Handle `../' or trailing `..' by itself.  */
	  if (path[i + 1] == '.' &&
	      (path[i + 2] == '/' || !path[i + 2]))
	    {
	      while (--start > -1 && path[start] != '/');
	      strcpy (path + start + 1, path + i + 2);
	      i = (start < 0) ? 0 : start;
	      continue;
	    }
	}	/* path == '.' */
    } /* while */

  if (!*path)
    {
      *path = stub_char;
      path[1] = '\0';
    }
}

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

/* Return a unique filename, given a prefix and count */
static char *
unique_name_1 (const char *fileprefix, int count)
{
  char *filename;

  if (count)
    {
      filename = (char *)xmalloc (strlen (fileprefix) + numdigit (count) + 2);
      sprintf (filename, "%s.%d", fileprefix, count);
    }
  else
    filename = xstrdup (fileprefix);

  if (!file_exists_p (filename))
    return filename;
  else
    {
      xfree (filename);
      return NULL;
    }
}

/* Return a unique file name, based on PREFIX.  */
char *
unique_name (const char *prefix)
{
  char *file = NULL;
  int count = 0;

  while (!file)
    file = unique_name_1 (prefix, count++);
  return file;
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
      /* Check whether the directory already exists.  */
      if (!file_exists_p (dir))
	{
	  if (mkdir (dir, 0777) < 0)
	    return -1;
	}
      if (quit)
	break;
      else
	dir[i] = '/';
    }
  return 0;
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

/* Match the end of STRING against PATTERN.  For instance:

   match_backwards ("abc", "bc") -> 1
   match_backwards ("abc", "ab") -> 0
   match_backwards ("abc", "abc") -> 1 */
static int
match_backwards (const char *string, const char *pattern)
{
  int i, j;

  for (i = strlen (string), j = strlen (pattern); i >= 0 && j >= 0; i--, j--)
    if (string[i] != pattern[j])
      break;
  /* If the pattern was exhausted, the match was succesful.  */
  if (j == -1)
    return 1;
  else
    return 0;
}

/* Checks whether string S matches each element of ACCEPTS.  A list
   element are matched either with fnmatch() or match_backwards(),
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
	      if (match_backwards (s, *accepts))
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

/* Return the malloc-ed suffix of STR.  For instance:
   suffix ("foo.bar")       -> "bar"
   suffix ("foo.bar.baz")   -> "baz"
   suffix ("/foo/bar")      -> NULL
   suffix ("/foo.bar/baz")  -> NULL  */
char *
suffix (const char *str)
{
  int i;

  for (i = strlen (str); i && str[i] != '/' && str[i] != '.'; i--);
  if (str[i++] == '.')
    return xstrdup (str + i);
  else
    return NULL;
}

/* Read a line from FP.  The function reallocs the storage as needed
   to accomodate for any length of the line.  Reallocs are done
   storage exponentially, doubling the storage after each overflow to
   minimize the number of calls to realloc() and fgets().  The newline
   character at the end of line is retained.

   After end-of-file is encountered without anything being read, NULL
   is returned.  NULL is also returned on error.  To distinguish
   between these two cases, use the stdio function ferror().  */

char *
read_whole_line (FILE *fp)
{
  int length = 0;
  int bufsize = 81;
  char *line = (char *)xmalloc (bufsize);

  while (fgets (line + length, bufsize - length, fp))
    {
      length += strlen (line + length);
      assert (length > 0);
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
             smaller than requested, and it would be unreasonably to
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


/* Engine for legible and legible_very_long; this function works on
   strings.  */

static char *
legible_1 (const char *repr)
{
  static char outbuf[128];
  int i, i1, mod;
  char *outptr;
  const char *inptr;

  /* Reset the pointers.  */
  outptr = outbuf;
  inptr = repr;
  /* If the number is negative, shift the pointers.  */
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
  long_to_string (inbuf, l);
  return legible_1 (inbuf);
}

/* Write a string representation of NUMBER into the provided buffer.
   We cannot use sprintf() because we cannot be sure whether the
   platform supports printing of what we chose for VERY_LONG_TYPE.

   Example: Gcc supports `long long' under many platforms, but on many
   of those the native libc knows nothing of it and therefore cannot
   print it.

   How long BUFFER needs to be depends on the platform and the content
   of NUMBER.  For 64-bit VERY_LONG_TYPE (the most common case), 24
   bytes are sufficient.  Using more might be a good idea.

   This function does not go through the hoops that long_to_string
   goes to because it doesn't aspire to be fast.  (It's called perhaps
   once in a Wget run.)  */

static void
very_long_to_string (char *buffer, VERY_LONG_TYPE number)
{
  int i = 0;
  int j;

  /* Print the number backwards... */
  do
    {
      buffer[i++] = '0' + number % 10;
      number /= 10;
    }
  while (number);

  /* ...and reverse the order of the digits. */
  for (j = 0; j < i / 2; j++)
    {
      char c = buffer[j];
      buffer[j] = buffer[i - 1 - j];
      buffer[i - 1 - j] = c;
    }
  buffer[i] = '\0';
}

/* The same as legible(), but works on VERY_LONG_TYPE.  See sysdep.h.  */
char *
legible_very_long (VERY_LONG_TYPE l)
{
  char inbuf[128];
  /* Print the number into the buffer.  */
  very_long_to_string (inbuf, l);
  return legible_1 (inbuf);
}

/* Count the digits in a (long) integer.  */
int
numdigit (long a)
{
  int res = 1;
  if (a < 0)
    {
      a = -a;
      ++res;
    }
  while ((a /= 10) != 0)
    ++res;
  return res;
}

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

/* Print NUMBER to BUFFER in base 10.  This is completely equivalent
   to `sprintf(buffer, "%ld", number)', only much faster.

   The speedup may make a difference in programs that frequently
   convert numbers to strings.  Some implementations of sprintf,
   particularly the one in GNU libc, have been known to be extremely
   slow compared to this function.

   BUFFER should accept as many bytes as you expect the number to take
   up.  On machines with 64-bit longs the maximum needed size is 24
   bytes.  That includes the worst-case digits, the optional `-' sign,
   and the trailing \0.  */

void
long_to_string (char *buffer, long number)
{
  char *p = buffer;
  long n = number;

#if (SIZEOF_LONG != 4) && (SIZEOF_LONG != 8)
  /* We are running in a strange or misconfigured environment.  Let
     sprintf cope with it.  */
  sprintf (buffer, "%ld", n);
#else  /* (SIZEOF_LONG == 4) || (SIZEOF_LONG == 8) */

  if (n < 0)
    {
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

struct wget_timer {
#ifdef TIMER_GETTIMEOFDAY
  long secs;
  long usecs;
#endif

#ifdef TIMER_TIME
  time_t secs;
#endif

#ifdef TIMER_WINDOWS
  ULARGE_INTEGER wintime;
#endif
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

/* Reset timer WT.  This establishes the starting point from which
   wtimer_elapsed() will return the number of elapsed
   milliseconds.  It is allowed to reset a previously used timer.  */

void
wtimer_reset (struct wget_timer *wt)
{
#ifdef TIMER_GETTIMEOFDAY
  struct timeval t;
  gettimeofday (&t, NULL);
  wt->secs  = t.tv_sec;
  wt->usecs = t.tv_usec;
#endif

#ifdef TIMER_TIME
  wt->secs = time (NULL);
#endif

#ifdef TIMER_WINDOWS
  FILETIME ft;
  SYSTEMTIME st;
  GetSystemTime (&st);
  SystemTimeToFileTime (&st, &ft);
  wt->wintime.HighPart = ft.dwHighDateTime;
  wt->wintime.LowPart  = ft.dwLowDateTime;
#endif
}

/* Return the number of milliseconds elapsed since the timer was last
   reset.  It is allowed to call this function more than once to get
   increasingly higher elapsed values.  */

long
wtimer_elapsed (struct wget_timer *wt)
{
#ifdef TIMER_GETTIMEOFDAY
  struct timeval t;
  gettimeofday (&t, NULL);
  return (t.tv_sec - wt->secs) * 1000 + (t.tv_usec - wt->usecs) / 1000;
#endif

#ifdef TIMER_TIME
  time_t now = time (NULL);
  return 1000 * (now - wt->secs);
#endif

#ifdef WINDOWS
  FILETIME ft;
  SYSTEMTIME st;
  ULARGE_INTEGER uli;
  GetSystemTime (&st);
  SystemTimeToFileTime (&st, &ft);
  uli.HighPart = ft.dwHighDateTime;
  uli.LowPart = ft.dwLowDateTime;
  return (long)((uli.QuadPart - wt->wintime.QuadPart) / 10000);
#endif
}

/* Return the assessed granularity of the timer implementation.  This
   is important for certain code that tries to deal with "zero" time
   intervals.  */

long
wtimer_granularity (void)
{
#ifdef TIMER_GETTIMEOFDAY
  /* Granularity of gettimeofday is hugely architecture-dependent.
     However, it appears that on modern machines it is better than
     1ms.  */
  return 1;
#endif

#ifdef TIMER_TIME
  /* This is clear. */
  return 1000;
#endif

#ifdef TIMER_WINDOWS
  /* ? */
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
