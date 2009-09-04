/* Declarations for html-url.c.
   Copyright (C) 1995, 1996, 1997, 2009 Free Software Foundation, Inc.

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

#ifndef HTML_URL_H
#define HTML_URL_H

struct map_context {
  char *text;			/* HTML text. */
  char *base;			/* Base URI of the document, possibly
				   changed through <base href=...>. */
  const char *parent_base;	/* Base of the current document. */
  const char *document_file;	/* File name of this document. */
  bool nofollow;		/* whether NOFOLLOW was specified in a
                                   <meta name=robots> tag. */

  struct urlpos *head, *tail;	/* List of URLs that is being
				   built. */
};

struct urlpos *get_urls_file (const char *);
struct urlpos *get_urls_html (const char *, const char *, bool *, struct iri *);
struct urlpos *append_url (const char *, int, int, struct map_context *);
void free_urlpos (struct urlpos *);

#endif /* HTML_URL_H */
