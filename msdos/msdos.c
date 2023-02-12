/* MSDOS utility functions.
   Copyright (C) 2009-2011, 2015, 2023 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget.  If not, see <http://www.gnu.org/licenses/>.

Additional permission under GNU GPL version 3 section 7

If you modify this program, or any covered work, by linking or
combining it with the OpenSSL project's OpenSSL library (or a
modified version of that library), containing parts covered by the
terms of the OpenSSL or SSLeay licenses, the Free Software Foundation
grants you additional permission to convey the resulting work.
Corresponding Source for a non-source form of such a combination
shall include the source code for the parts of OpenSSL used as well
as that of the covered work.  */

#include "wget.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/* This variable (i.e. MB_CUR_MAX) is set here so that we force a unibyte
   locale in ../lib/quotearg.c. */
#ifdef __DJGPP__
int __dj_mb_cur_max = 1;
#endif

#ifndef __WATCOMC__
/* These is just a dummy function to make Wget link. These are never called
   because 'unibyte_locale == 1' in ../lib/quotearg.c. */
int mbsinit (void)
{
  return 0;
}

int mbrtowc (void)
{
  return 0;
}

int iswprint (void)
{
  return 0;
}
#endif   /* __WATCOMC__ */


#define PASS_MAX 512

/* Get a user string with echo off. Handy for entering passwords. The prompt
   optional. */
char *
getpass (const char *prompt)
{
  char getpassbuf[PASS_MAX + 1];
  size_t i = 0;
  int c;

  if (prompt)
    {
      fputs (prompt, stderr);
      fflush (stderr);
    }

  for (;;)
    {
      c = getch ();
      if (c == '\r')
	{
	  getpassbuf[i] = '\0';
	  break;
	}
      else if (i < PASS_MAX)
	{
	  getpassbuf[i++] = c;
	}

      if (i >= PASS_MAX)
	{
	  getpassbuf[i] = '\0';
	  break;
	}
    }

  if (prompt)
    {
      fputs ("\r\n", stderr);
      fflush (stderr);
    }

  return strdup (getpassbuf);
}
