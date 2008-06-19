/* IRI related functions.
   Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,
   2008 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at
your option) any later version.

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
#include <assert.h>
#include <string.h>

#include "utils.h"
#include "iri.h"


/* Given a string containing "charset=XXX", return the encoding if found,
   or NULL otherwise */
char *
parse_charset (char *str)
{
  char *charset;

  if (!str || !*str)
    return NULL;

  str = strcasestr (str, "charset=");
  if (!str)
    return NULL;

  str += 8;
  charset = str;

  /* sXXXav: which chars should be banned ??? */
  while (*charset && !c_isspace (*charset))
    charset++;

  /* sXXXav: could strdupdelim return NULL ? */
  charset = strdupdelim (str, charset);
  logprintf (LOG_VERBOSE, "parse_charset: %s\n", quote (charset));

  return charset;
}


