/* Declarations for `headers.c'.
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

#ifndef HEADERS_H
#define HEADERS_H

enum {
  HG_OK, HG_ERROR, HG_EOF
};

enum header_get_flags { HG_NONE = 0,
			HG_NO_CONTINUATIONS = 0x2 };

int header_get PARAMS ((struct rbuf *, char **, enum header_get_flags));
int header_process PARAMS ((const char *, const char *,
			    int (*) (const char *, void *),
			    void *));

int header_extract_number PARAMS ((const char *, void *));
int header_strdup PARAMS ((const char *, void *));
int header_exists PARAMS ((const char *, void *));

int skip_lws PARAMS ((const char *));

#endif /* HEADERS_H */
