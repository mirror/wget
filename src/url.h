/* Declarations for url.c.
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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

#ifndef URL_H
#define URL_H

/* Default port definitions */
#define DEFAULT_HTTP_PORT 80
#define DEFAULT_FTP_PORT 21
#define DEFAULT_HTTPS_PORT 443

/* Note: the ordering here is related to the order of elements in
   `supported_schemes' in url.c.  */

enum url_scheme {
  SCHEME_HTTP,
#ifdef HAVE_SSL
  SCHEME_HTTPS,
#endif
  SCHEME_FTP,
  SCHEME_INVALID
};

/* Structure containing info on a URL.  */
struct url
{
  char *url;			/* Original URL */
  enum url_scheme scheme;	/* URL scheme */

  char *host;			/* Extracted hostname */
  int port;			/* Port number */

  /* URL components (URL-quoted). */
  char *path;
  char *params;
  char *query;
  char *fragment;

  /* Extracted path info (unquoted). */
  char *dir;
  char *file;

  /* Username and password (unquoted). */
  char *user;
  char *passwd;
};

enum convert_options {
  CO_NOCONVERT = 0,		/* don't convert this URL */
  CO_CONVERT_TO_RELATIVE,	/* convert to relative, e.g. to
                                   "../../otherdir/foo.gif" */
  CO_CONVERT_TO_COMPLETE,	/* convert to absolute, e.g. to
				   "http://orighost/somedir/bar.jpg". */
  CO_NULLIFY_BASE		/* change to empty string. */
};

/* A structure that defines the whereabouts of a URL, i.e. its
   position in an HTML document, etc.  */

struct urlpos {
  struct url *url;		/* the URL of the link, after it has
				   been merged with the base */
  char *local_name;		/* local file to which it was saved
				   (used by convert_links) */

  /* reserved for special links such as <base href="..."> which are
     used when converting links, but ignored when downloading.  */
  unsigned int ignore_when_downloading	:1;

  /* Information about the original link: */

  unsigned int link_relative_p	:1; /* was the link relative? */
  unsigned int link_complete_p	:1; /* was the link complete (with the
				       host name, etc.) */
  unsigned int link_base_p	:1; /* was the link <base href=...> */
  unsigned int link_inline_p	:1; /* needed to render the page. */

  unsigned int link_refresh_p	:1; /* link was received from
				       <meta http-equiv=refresh content=...> */
  int refresh_timeout;		/* for reconstructing the refresh. */

  /* Conversion requirements: */
  enum convert_options convert;	/* is conversion required? */

  /* URL's position in the buffer. */
  int pos, size;

  struct urlpos *next;		/* next list element */
};

/* downloaded_file() takes a parameter of this type and returns this type. */
typedef enum
{
  /* Return enumerators: */
  FILE_NOT_ALREADY_DOWNLOADED = 0,

  /* Return / parameter enumerators: */
  FILE_DOWNLOADED_NORMALLY,
  FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED,

  /* Parameter enumerators: */
  CHECK_FOR_FILE
} downloaded_file_t;

/* Function declarations */

char *encode_string PARAMS ((const char *));

struct url *url_parse PARAMS ((const char *, int *));
const char *url_error PARAMS ((int));
char *url_full_path PARAMS ((const struct url *));
void url_set_dir PARAMS ((struct url *, const char *));
void url_set_file PARAMS ((struct url *, const char *));
void url_free PARAMS ((struct url *));

enum url_scheme url_scheme PARAMS ((const char *));
int url_skip_scheme PARAMS ((const char *));
int url_has_scheme PARAMS ((const char *));
int scheme_default_port PARAMS ((enum url_scheme));
void scheme_disable PARAMS ((enum url_scheme));

int url_skip_uname PARAMS ((const char *));

char *url_string PARAMS ((const struct url *, int));

struct urlpos *get_urls_file PARAMS ((const char *));
struct urlpos *get_urls_html PARAMS ((const char *, const char *, int *));
void free_urlpos PARAMS ((struct urlpos *));

char *uri_merge PARAMS ((const char *, const char *));

void rotate_backups PARAMS ((const char *));
int mkalldirs PARAMS ((const char *));
char *url_filename PARAMS ((const struct url *));

char *getproxy PARAMS ((enum url_scheme));
int no_proxy_match PARAMS ((const char *, const char **));

void convert_links PARAMS ((const char *, struct urlpos *));

downloaded_file_t downloaded_file PARAMS ((downloaded_file_t, const char *));

char *rewrite_shorthand_url PARAMS ((const char *));

#endif /* URL_H */
