/* Various functions of utilitarian nature.
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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else  /* not HAVE_STRING_H */
# include <strings.h>
#endif /* not HAVE_STRING_H */
#include <ctype.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
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

#include "wget.h"
#include "utils.h"
#include "fnmatch.h"

#ifndef errno
extern int errno;
#endif


/* Croak the fatal memory error and bail out with non-zero exit
   status.  */
static void
memfatal (const char *s)
{
  /* HACK: expose save_log_p from log.c, so we can turn it off in
     order to prevent saving the log.  Saving the log is dangerous
     because logprintf() and logputs() can call malloc(), so this
     could infloop.  When logging is turned off, infloop can no longer
     happen.  */
  extern int save_log_p;

  save_log_p = 0;
  logprintf (LOG_ALWAYS, _("%s: %s: Not enough memory.\n"), exec_name, s);
  exit (1);
}

/* xmalloc, xrealloc and xstrdup exit the program if there is not
   enough memory.  xstrdup also implements strdup on systems that do
   not have it.  */
void *
xmalloc (size_t size)
{
  void *res;

  res = malloc (size);
  if (!res)
    memfatal ("malloc");
  return res;
}

void *
xrealloc (void *obj, size_t size)
{
  void *res;

  /* Not all Un*xes have the feature of realloc() that calling it with
     a NULL-pointer is the same as malloc(), but it is easy to
     simulate.  */
  if (obj)
    res = realloc (obj, size);
  else
    res = malloc (size);
  if (!res)
    memfatal ("realloc");
  return res;
}

char *
xstrdup (const char *s)
{
#ifndef HAVE_STRDUP
  int l = strlen (s);
  char *s1 = malloc (l + 1);
  if (!s1)
    memfatal ("strdup");
  memcpy (s1, s, l + 1);
  return s1;
#else  /* HAVE_STRDUP */
  char *s1 = strdup (s);
  if (!s1)
    memfatal ("strdup");
  return s1;
#endif /* HAVE_STRDUP */
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
   string-representation of TM (in form hh:mm:ss) is printed.  It is
   shamelessly non-reentrant, but it doesn't matter, really.

   If TM is non-NULL, the time_t of the current time will be stored
   there.  */
char *
time_str (time_t *tm)
{
  static char tms[15];
  struct tm *ptm;
  time_t tim;

  *tms = '\0';
  tim = time (tm);
  if (tim == -1)
    return tms;
  ptm = localtime (&tim);
  sprintf (tms, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
  return tms;
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

/* A cuserid() immitation using getpwuid(), to avoid hassling with
   utmp.  Besides, not all systems have cuesrid().  Under Windows, it
   is defined in mswindows.c.

   If WHERE is non-NULL, the username will be stored there.
   Otherwise, it will be returned as a static buffer (as returned by
   getpwuid()).  In the latter case, the buffer should be copied
   before calling getpwuid() or pwd_cuserid() again.  */
#ifndef WINDOWS
char *
pwd_cuserid (char *where)
{
  struct passwd *pwd;

  if (!(pwd = getpwuid (getuid ())) || !pwd->pw_name)
    return NULL;
  if (where)
    {
      strcpy (where, pwd->pw_name);
      return where;
    }
  else
    return pwd->pw_name;
}

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
    logprintf (LOG_NOTQUIET, "utime: %s\n", strerror (errno));
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
      free (filename);
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
   minimize the number of calls to realloc().

   It is not an exemplary of correctness, since it kills off the
   newline (and no, there is no way to know if there was a newline at
   EOF).  */
char *
read_whole_line (FILE *fp)
{
  char *line;
  int i, bufsize, c;

  i = 0;
  bufsize = 40;
  line = (char *)xmalloc (bufsize);
  /* Construct the line.  */
  while ((c = getc (fp)) != EOF && c != '\n')
    {
      if (i > bufsize - 1)
	line = (char *)xrealloc (line, (bufsize <<= 1));
      line[i++] = c;
    }
  if (c == EOF && !i)
    {
      free (line);
      return NULL;
    }
  /* Check for overflow at zero-termination (no need to double the
     buffer in this case.  */
  if (i == bufsize)
    line = (char *)xrealloc (line, i + 1);
  line[i] = '\0';
  return line;
}

/* Load file pointed to by FP to memory and return the malloc-ed
   buffer with the contents.  *NREAD will contain the number of read
   bytes.  The file is loaded in chunks, allocated exponentially,
   starting with FILE_BUFFER_SIZE bytes.  */
void
load_file (FILE *fp, char **buf, long *nread)
{
  long bufsize;

  bufsize = 512;
  *nread = 0;
  *buf = NULL;
  while (!feof (fp) && !ferror (fp))
    {
      *buf = (char *)xrealloc (*buf, bufsize + *nread);
      *nread += fread (*buf + *nread, sizeof (char), bufsize, fp);
      bufsize <<= 1;
    }
  /* #### No indication of encountered error??  */
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
	free (*p++);
      free (vec);
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
      free (v2);
      return v1;
    }
  /* Count v1.  */
  for (i = 0; v1[i]; i++);
  /* Count v2.  */
  for (j = 0; v2[j]; j++);
  /* Reallocate v1.  */
  v1 = (char **)xrealloc (v1, (i + j + 1) * sizeof (char **));
  memcpy (v1 + i, v2, (j + 1) * sizeof (char *));
  free (v2);
  return v1;
}

/* A set of simple-minded routines to store and search for strings in
   a linked list.  You may add a string to the slist, and peek whether
   it's still in there at any time later.  */

/* Add an element to the list.  If flags is NOSORT, the list will not
   be sorted.  */
slist *
add_slist (slist *l, const char *s, int flags)
{
  slist *t, *old, *beg;
  int cmp;

  if (flags & NOSORT)
    {
      if (!l)
	{
	  t = (slist *)xmalloc (sizeof (slist));
	  t->string = xstrdup (s);
	  t->next = NULL;
	  return t;
	}
      beg = l;
      /* Find the last element.  */
      while (l->next)
	l = l->next;
      t = (slist *)xmalloc (sizeof (slist));
      l->next = t;
      t->string = xstrdup (s);
      t->next = NULL;
      return beg;
    }
  /* Empty list or changing the first element.  */
  if (!l || (cmp = strcmp (l->string, s)) > 0)
    {
      t = (slist *)xmalloc (sizeof (slist));
      t->string = xstrdup (s);
      t->next = l;
      return t;
    }

  beg = l;
  if (cmp == 0)
    return beg;

  /* Second two one-before-the-last element.  */
  while (l->next)
    {
      old = l;
      l = l->next;
      cmp = strcmp (s, l->string);
      if (cmp == 0)             /* no repeating in the list */
	return beg;
      else if (cmp > 0)
	continue;
      /* If the next list element is greater than s, put s between the
	 current and the next list element.  */
      t = (slist *)xmalloc (sizeof (slist));
      old->next = t;
      t->next = l;
      t->string = xstrdup (s);
      return beg;
    }
  t = (slist *)xmalloc (sizeof (slist));
  t->string = xstrdup (s);
  /* Insert the new element after the last element.  */
  l->next = t;
  t->next = NULL;
  return beg;
}

/* Is there a specific entry in the list?  */
int
in_slist (slist *l, const char *s)
{
  int cmp;

  while (l)
    {
      cmp = strcmp (l->string, s);
      if (cmp == 0)
	return 1;
      else if (cmp > 0)         /* the list is ordered!  */
	return 0;
      l = l->next;
    }
  return 0;
}

/* Free the whole slist.  */
void
free_slist (slist *l)
{
  slist *n;

  while (l)
    {
      n = l->next;
      free (l->string);
      free (l);
      l = n;
    }
}

/* Legible -- return a static pointer to the legibly printed long.  */
char *
legible (long l)
{
  static char outbuf[20];
  char inbuf[20];
  int i, i1, mod;
  char *outptr, *inptr;

  /* Print the number into the buffer.  */
  long_to_string (inbuf, l);
  /* Reset the pointers.  */
  outptr = outbuf;
  inptr = inbuf;
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

/* Count the digits in a (long) integer.  */
int
numdigit (long a)
{
  int res = 1;
  while ((a /= 10) != 0)
    ++res;
  return res;
}

/* Print NUMBER to BUFFER.  The digits are first written in reverse
   order (the least significant digit first), and are then reversed.  */
void
long_to_string (char *buffer, long number)
{
  char *p;
  int i, l;

  if (number < 0)
    {
      *buffer++ = '-';
      number = -number;
    }
  p = buffer;
  /* Print the digits to the string.  */
  do
    {
      *p++ = number % 10 + '0';
      number /= 10;
    }
  while (number);
  /* And reverse them.  */
  l = p - buffer - 1;
  for (i = l/2; i >= 0; i--)
    {
      char c = buffer[i];
      buffer[i] = buffer[l - i];
      buffer[l - i] = c;
    }
  buffer[l + 1] = '\0';
}
