/* This stores global variables that are initialized with 
   preprocessor declarations for output with the --version flag.

   Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003,
   2004, 2005, 2006, 2007, 2008 Free Software Foundation, Inc.

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

const char* (compiled_features[]) =
{

#ifdef ENABLE_DIGEST
  "+digest",
#else
  "-digest",
#endif

#ifdef ENABLE_IPV6
  "+ipv6",
#else
  "-ipv6",
#endif

#ifdef ENABLE_NLS
  "+nls",
#else
  "-nls",
#endif

#ifdef ENABLE_NTLM
  "+ntlm",
#else
  "-ntlm",
#endif

#ifdef ENABLE_OPIE
  "+opie",
#else
  "-opie",
#endif

#ifdef HAVE_MD5
#ifdef HAVE_BUILTIN_MD5
  "+md5/builtin", 
#elif HAVE_OPENSSL_MD5
  "+md5/openssl",
#elif HAVE_SOLARIS_MD5
  "+md5/solaris",
#else
#error "md5 set, but no library found!",
#endif
#else
  "-md5",
#endif

#ifdef HAVE_SSL
  "+https",
#else
  "-https",
#endif

#ifdef HAVE_LIBGNUTLS
  "+gnutls",
#else
  "-gnutls",
#endif

#ifdef HAVE_LIBSSL
  "+openssl",
#else
  "-openssl",
#endif

#ifdef HAVE_GETTEXT
  "+gettext",
#else
  "-gettext",
#endif

#ifdef ENABLE_IRI
  "+iri",
#else
  "-iri",
#endif

  /* sentinel value */
  NULL
};


