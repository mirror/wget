/* Pattern matching (globbing).
   Copyright (C) 1991, 1996, 1997 Free Software Foundation, Inc.

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

/* NOTE: Some Un*xes have their own fnmatch() -- yet, they are
   reportedly unreliable and buggy.  Thus I chose never to use it;
   this version (from GNU Bash) is used unconditionally.  */

#include <config.h>

#include <errno.h>
#include "wget.h"
#include "fnmatch.h"

/* Match STRING against the filename pattern PATTERN, returning zero
   if it matches, FNM_NOMATCH if not.  */
int
fnmatch (const char *pattern, const char *string, int flags)
{
  register const char *p = pattern, *n = string;
  register char c;

  if ((flags & ~__FNM_FLAGS) != 0)
    {
      errno = EINVAL;
      return (-1);
    }

  while ((c = *p++) != '\0')
    {
      switch (c)
	{
	case '?':
	  if (*n == '\0')
	    return (FNM_NOMATCH);
	  else if ((flags & FNM_PATHNAME) && *n == '/')
	    return (FNM_NOMATCH);
	  else if ((flags & FNM_PERIOD) && *n == '.' &&
		   (n == string || ((flags & FNM_PATHNAME) && n[-1] == '/')))
	    return (FNM_NOMATCH);
	  break;

	case '\\':
	  if (!(flags & FNM_NOESCAPE))
	    c = *p++;
	  if (*n != c)
	    return (FNM_NOMATCH);
	  break;

	case '*':
	  if ((flags & FNM_PERIOD) && *n == '.' &&
	      (n == string || ((flags & FNM_PATHNAME) && n[-1] == '/')))
	    return (FNM_NOMATCH);

	  for (c = *p++; c == '?' || c == '*'; c = *p++, ++n)
	    if (((flags & FNM_PATHNAME) && *n == '/') ||
		(c == '?' && *n == '\0'))
	      return (FNM_NOMATCH);

	  if (c == '\0')
	    return (0);

	  {
	    char c1 = (!(flags & FNM_NOESCAPE) && c == '\\') ? *p : c;
	    for (--p; *n != '\0'; ++n)
	      if ((c == '[' || *n == c1) &&
		  fnmatch (p, n, flags & ~FNM_PERIOD) == 0)
		return (0);
	    return (FNM_NOMATCH);
	  }

	case '[':
	  {
	    /* Nonzero if the sense of the character class is
	       inverted.  */
	    register int not;

	    if (*n == '\0')
	      return (FNM_NOMATCH);

	    if ((flags & FNM_PERIOD) && *n == '.' &&
		(n == string || ((flags & FNM_PATHNAME) && n[-1] == '/')))
	      return (FNM_NOMATCH);

	    /* Make sure there is a closing `]'.  If there isn't,
	       the `[' is just a character to be matched.  */
	    {
	      register const char *np;

	      for (np = p; np && *np && *np != ']'; np++);

	      if (np && !*np)
		{
		  if (*n != '[')
		    return (FNM_NOMATCH);
		  goto next_char;
		}
	    }

	    not = (*p == '!' || *p == '^');
	    if (not)
	      ++p;

	    c = *p++;
	    while (1)
	      {
		register char cstart = c, cend = c;

		if (!(flags & FNM_NOESCAPE) && c == '\\')
		  cstart = cend = *p++;

		if (c == '\0')
		  /* [ (unterminated) loses.  */
		  return (FNM_NOMATCH);

		c = *p++;

		if ((flags & FNM_PATHNAME) && c == '/')
		  /* [/] can never match.  */
		  return (FNM_NOMATCH);

		if (c == '-' && *p != ']')
		  {
		    cend = *p++;
		    if (!(flags & FNM_NOESCAPE) && cend == '\\')
		      cend = *p++;
		    if (cend == '\0')
		      return (FNM_NOMATCH);
		    c = *p++;
		  }

		if (*n >= cstart && *n <= cend)
		  goto matched;

		if (c == ']')
		  break;
	      }
	    if (!not)
	      return (FNM_NOMATCH);

	  next_char:
	    break;

	  matched:
	    /* Skip the rest of the [...] that already matched.  */
	    while (c != ']')
	      {
		if (c == '\0')
		  /* [... (unterminated) loses.  */
		  return (FNM_NOMATCH);

		c = *p++;
		if (!(flags & FNM_NOESCAPE) && c == '\\')
		  /* 1003.2d11 is unclear if this is right.  %%% */
		  ++p;
	      }
	    if (not)
	      return (FNM_NOMATCH);
	  }
	  break;

	default:
	  if (c != *n)
	    return (FNM_NOMATCH);
	}

      ++n;
    }

  if (*n == '\0')
    return (0);

  return (FNM_NOMATCH);
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
