/* Internationalization related declarations.
   Copyright (C) 2008 Free Software Foundation, Inc.

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

#ifndef IRI_H
#define IRI_H

#ifdef ENABLE_IRI

char *parse_charset (char *str);
char *find_locale (void);
bool check_encoding_name (char *encoding);
const char *locale_to_utf8 (const char *str);
char *idn_encode (char *host, bool utf8_encoded);
char *idn_decode (char *host);
char *get_remote_charset (void);
char *get_current_charset (void);
void set_current_charset (char *charset);
void set_current_as_locale (void);
void set_current_charset (char *charset);
void set_remote_charset (char *charset);
void set_remote_as_current (void);
bool remote_to_utf8 (const char *str, const char **new);
void reset_utf8_encode (void);
void set_utf8_encode (bool encode);
bool get_utf8_encode (void);

/* ugly ugly ugly */
void set_ugly_no_encode (bool ugly);

#else /* ENABLE_IRI */

#define parse_charset(str)          NULL
#define find_locale()               NULL
#define check_encoding_name(str)    false
#define locale_to_utf8(str)         (str)
#define idn_encode(str,encoded)     NULL
#define idn_decode(str)             NULL
#define get_remote_charset()        NULL
#define get_current_charset()       NULL
#define set_current_charset(str)
#define set_current_as_locale()
#define set_current_charset(str)
#define set_remote_charset(str)
#define set_remote_as_current()
#define remote_to_utf8(a,b)         false
#define reset_utf8_encode()
#define set_utf8_encode(a)
#define get_utf8_encode()           false

#endif /* ENABLE_IRI */
#endif /* IRI_H */
