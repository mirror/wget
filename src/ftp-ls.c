/* Parsing FTP `ls' output.
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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
#else
# include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>

#include "wget.h"
#include "utils.h"
#include "ftp.h"

/* Converts symbolic permissions to number-style ones, e.g. string
   rwxr-xr-x to 755.  For now, it knows nothing of
   setuid/setgid/sticky.  ACLs are ignored.  */
static int
symperms (const char *s)
{
  int perms = 0, i;

  if (strlen (s) < 9)
    return 0;
  for (i = 0; i < 3; i++, s += 3)
    {
      perms <<= 3;
      perms += (((s[0] == 'r') << 2) + ((s[1] == 'w') << 1) +
		(s[2] == 'x' || s[2] == 's'));
    }
  return perms;
}


/* Convert the Un*x-ish style directory listing stored in FILE to a
   linked list of fileinfo (system-independent) entries.  The contents
   of FILE are considered to be produced by the standard Unix `ls -la'
   output (whatever that might be).  BSD (no group) and SYSV (with
   group) listings are handled.

   The time stamps are stored in a separate variable, time_t
   compatible (I hope).  The timezones are ignored.  */
static struct fileinfo *
ftp_parse_unix_ls (const char *file)
{
  FILE *fp;
  static const char *months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  int next, len, i, error, ignore;
  int year, month, day;		/* for time analysis */
  int hour, min, sec;
  struct tm timestruct, *tnow;
  time_t timenow;

  char *line, *tok;		/* tokenizer */
  struct fileinfo *dir, *l, cur; /* list creation */

  fp = fopen (file, "rb");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
      return NULL;
    }
  dir = l = NULL;

  /* Line loop to end of file: */
  while ((line = read_whole_line (fp)))
    {
      DEBUGP (("%s\n", line));
      len = strlen (line);
      /* Destroy <CR> if there is one.  */
      if (len && line[len - 1] == '\r')
	line[--len] = '\0';

      /* Skip if total...  */
      if (!strncasecmp (line, "total", 5))
	{
	  free (line);
	  continue;
	}
      /* Get the first token (permissions).  */
      tok = strtok (line, " ");
      if (!tok)
	{
	  free (line);
	  continue;
	}

      cur.name = NULL;
      cur.linkto = NULL;

      /* Decide whether we deal with a file or a directory.  */
      switch (*tok)
	{
	case '-':
	  cur.type = FT_PLAINFILE;
	  DEBUGP (("PLAINFILE; "));
	  break;
	case 'd':
	  cur.type = FT_DIRECTORY;
	  DEBUGP (("DIRECTORY; "));
	  break;
	case 'l':
	  cur.type = FT_SYMLINK;
	  DEBUGP (("SYMLINK; "));
	  break;
	default:
	  cur.type = FT_UNKNOWN;
	  DEBUGP (("UNKOWN; "));
	  break;
	}

      cur.perms = symperms (tok + 1);
      DEBUGP (("perms %0o; ", cur.perms));

      error = ignore = 0;       /* Errnoeous and ignoring entries are
				   treated equally for now.  */
      year = hour = min = sec = 0; /* Silence the compiler.  */
      month = day = 0;
      next = -1;
      /* While there are tokens on the line, parse them.  Next is the
	 number of tokens left until the filename.

	 Use the month-name token as the "anchor" (the place where the
	 position wrt the file name is "known").  When a month name is
	 encountered, `next' is set to 5.  Also, the preceding
	 characters are parsed to get the file size.

	 This tactic is quite dubious when it comes to
	 internationalization issues (non-English month names), but it
	 works for now.  */
      while ((tok = strtok (NULL, " ")))
	{
	  --next;
	  if (next < 0)		/* a month name was not encountered */
	    {
	      for (i = 0; i < 12; i++)
		if (!strcmp (tok, months[i]))
		  break;
	      /* If we got a month, it means the token before it is the
		 size, and the filename is three tokens away.  */
	      if (i != 12)
		{
		  char *t = tok - 2;
		  long mul = 1;

		  for (cur.size = 0; t > line && ISDIGIT (*t); mul *= 10, t--)
		    cur.size += mul * (*t - '0');
		  if (t == line)
		    {
		      /* Something is seriously wrong.  */
		      error = 1;
		      break;
		    }
		  month = i;
		  next = 5;
		  DEBUGP (("month: %s; ", months[month]));
		}
	    }
	  else if (next == 4)	/* days */
	    {
	      if (tok[1])	/* two-digit... */
		day = 10 * (*tok - '0') + tok[1] - '0';
	      else		/* ...or one-digit */
		day = *tok - '0';
	      DEBUGP (("day: %d; ", day));
	    }
	  else if (next == 3)
	    {
	      /* This ought to be either the time, or the year.  Let's
		 be flexible!

		 If we have a number x, it's a year.  If we have x:y,
		 it's hours and minutes.  If we have x:y:z, z are
		 seconds.  */
	      year = 0;
	      min = hour = sec = 0;
	      /* We must deal with digits.  */
	      if (ISDIGIT (*tok))
		{
		  /* Suppose it's year.  */
		  for (; ISDIGIT (*tok); tok++)
		    year = (*tok - '0') + 10 * year;
		  if (*tok == ':')
		    {
		      /* This means these were hours!  */
		      hour = year;
		      year = 0;
		      ++tok;
		      /* Get the minutes...  */
		      for (; ISDIGIT (*tok); tok++)
			min = (*tok - '0') + 10 * min;
		      if (*tok == ':')
			{
			  /* ...and the seconds.  */
			  ++tok;
			  for (; ISDIGIT (*tok); tok++)
			    sec = (*tok - '0') + 10 * sec;
			}
		    }
		}
	      if (year)
		DEBUGP (("year: %d (no tm); ", year));
	      else
		DEBUGP (("time: %02d:%02d:%02d (no yr); ", hour, min, sec));
	    }
	  else if (next == 2)    /* The file name */
	    {
	      int fnlen;
	      char *p;

	      /* Since the file name may contain a SPC, it is possible
		 for strtok to handle it wrong.  */
	      fnlen = strlen (tok);
	      if (fnlen < len - (tok - line))
		{
		  /* So we have a SPC in the file name.  Restore the
		     original.  */
		  tok[fnlen] = ' ';
		  /* If the file is a symbolic link, it should have a
		     ` -> ' somewhere.  */
		  if (cur.type == FT_SYMLINK)
		    {
		      p = strstr (tok, " -> ");
		      if (!p)
			{
			  error = 1;
			  break;
			}
		      cur.linkto = xstrdup (p + 4);
		      DEBUGP (("link to: %s\n", cur.linkto));
		      /* And separate it from the file name.  */
		      *p = '\0';
		    }
		}
	      /* If we have the filename, add it to the list of files or
		 directories.  */
	      /* "." and ".." are an exception!  */
	      if (!strcmp (tok, ".") || !strcmp (tok, ".."))
		{
		  DEBUGP (("\nIgnoring `.' and `..'; "));
		  ignore = 1;
		  break;
		}
	      /* Some FTP sites choose to have ls -F as their default
		 LIST output, which marks the symlinks with a trailing
		 `@', directory names with a trailing `/' and
		 executables with a trailing `*'.  This is no problem
		 unless encountering a symbolic link ending with `@',
		 or an executable ending with `*' on a server without
		 default -F output.  I believe these cases are very
		 rare.  */
	      fnlen = strlen (tok); /* re-calculate `fnlen' */
	      cur.name = (char *)xmalloc (fnlen + 1);
	      memcpy (cur.name, tok, fnlen + 1);
	      if (fnlen)
		{
		  if (cur.type == FT_DIRECTORY && cur.name[fnlen - 1] == '/')
		    {
		      cur.name[fnlen - 1] = '\0';
		      DEBUGP (("trailing `/' on dir.\n"));
		    }
		  else if (cur.type == FT_SYMLINK && cur.name[fnlen - 1] == '@')
		    {
		      cur.name[fnlen - 1] = '\0';
		      DEBUGP (("trailing `@' on link.\n"));
		    }
		  else if (cur.type == FT_PLAINFILE
			   && (cur.perms & 0111)
			   && cur.name[fnlen - 1] == '*')
		    {
		      cur.name[fnlen - 1] = '\0';
		      DEBUGP (("trailing `*' on exec.\n"));
		    }
		} /* if (fnlen) */
	      else
		error = 1;
	      break;
	    }
	  else
	    abort ();
	} /* while */

      if (!cur.name || (cur.type == FT_SYMLINK && !cur.linkto))
	error = 1;

      DEBUGP (("\n"));

      if (error || ignore)
	{
	  DEBUGP (("Skipping.\n"));
	  FREE_MAYBE (cur.name);
	  FREE_MAYBE (cur.linkto);
	  free (line);
	  continue;
	}

      if (!dir)
	{
	  l = dir = (struct fileinfo *)xmalloc (sizeof (struct fileinfo));
	  memcpy (l, &cur, sizeof (cur));
	  l->prev = l->next = NULL;
	}
      else
	{
	  cur.prev = l;
	  l->next = (struct fileinfo *)xmalloc (sizeof (struct fileinfo));
	  l = l->next;
	  memcpy (l, &cur, sizeof (cur));
	  l->next = NULL;
	}
      /* Get the current time.  */
      timenow = time (NULL);
      tnow = localtime (&timenow);
      /* Build the time-stamp (the idea by zaga@fly.cc.fer.hr).  */
      timestruct.tm_sec   = sec;
      timestruct.tm_min   = min;
      timestruct.tm_hour  = hour;
      timestruct.tm_mday  = day;
      timestruct.tm_mon   = month;
      if (year == 0)
	{
	  /* Some listings will not specify the year if it is "obvious"
	     that the file was from the previous year.  E.g. if today
	     is 97-01-12, and you see a file of Dec 15th, its year is
	     1996, not 1997.  Thanks to Vladimir Volovich for
	     mentioning this!  */
	  if (month > tnow->tm_mon)
	    timestruct.tm_year = tnow->tm_year - 1;
	  else
	    timestruct.tm_year = tnow->tm_year;
	}
      else
	timestruct.tm_year = year;
      if (timestruct.tm_year >= 1900)
	timestruct.tm_year -= 1900;
      timestruct.tm_wday  = 0;
      timestruct.tm_yday  = 0;
      timestruct.tm_isdst = -1;
      l->tstamp = mktime (&timestruct); /* store the time-stamp */

      free (line);
    }

  fclose (fp);
  return dir;
}

/* This function is just a stub.  It should actually accept some kind
   of information what system it is running on -- e.g. FPL_UNIX,
   FPL_DOS, FPL_NT, FPL_VMS, etc. and a "guess-me" value, like
   FPL_GUESS.  Then it would call the appropriate parsers to fill up
   fileinfos.

   Since we currently support only the Unix FTP servers, this function
   simply returns the result of ftp_parse_unix_ls().  */
struct fileinfo *
ftp_parse_ls (const char *file)
{
  return ftp_parse_unix_ls (file);
}
