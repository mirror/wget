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


/* Structure containing info on a URL.  */
struct urlinfo
{
  char *url;			/* Unchanged URL */
  uerr_t proto;			/* URL protocol */
  char *host;			/* Extracted hostname */
  unsigned short port;
  char ftp_type;
  char *path, *dir, *file, *qstring;	
                                /* Path, dir, file, and query string
				   (properly decoded) */
  char *user, *passwd;		/* Username and password */
  struct urlinfo *proxy;	/* The exact string to pass to proxy
				   server */
  char *referer;		/* The source from which the request
				   URI was obtained */
  char *local;			/* The local filename of the URL
				   document */
};

enum convert_options {
  CO_NOCONVERT = 0,		/* don't convert this URL */
  CO_CONVERT_TO_RELATIVE,	/* convert to relative, e.g. to
                                   "../../otherdir/foo.gif" */
  CO_CONVERT_TO_COMPLETE	/* convert to absolute, e.g. to
				   "http://orighost/somedir/bar.jpg". */
};

/* A structure that defines the whereabouts of a URL, i.e. its
   position in an HTML document, etc.  */

typedef struct _urlpos
{
  char *url;			/* linked URL, after it has been
				   merged with the base */
  char *local_name;		/* Local file to which it was saved */

  /* Information about the original link: */
  int link_relative_p;		/* was the link relative? */
  int link_complete_p;		/* was the link complete (with the
                                   host name, etc.) */

  /* Conversion requirements: */
  enum convert_options convert;	/* is conversion required? */

  /* URL's position in the buffer. */
  int pos, size;

  struct _urlpos *next;		/* Next struct in list */
} urlpos;

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

struct urlinfo *newurl PARAMS ((void));
void freeurl PARAMS ((struct urlinfo *, int));
uerr_t urlproto PARAMS ((const char *));
int skip_proto PARAMS ((const char *));
int has_proto PARAMS ((const char *));
int skip_uname PARAMS ((const char *));

uerr_t parseurl PARAMS ((const char *, struct urlinfo *, int));
char *str_url PARAMS ((const struct urlinfo *, int));
int url_equal PARAMS ((const char *, const char *));

urlpos *get_urls_file PARAMS ((const char *));
urlpos *get_urls_html PARAMS ((const char *, const char *, int, int *));
void free_urlpos PARAMS ((urlpos *));

char *uri_merge PARAMS ((const char *, const char *));

void rotate_backups PARAMS ((const char *));
int mkalldirs PARAMS ((const char *));
char *url_filename PARAMS ((const struct urlinfo *));
void opt_url PARAMS ((struct urlinfo *));

char *getproxy PARAMS ((uerr_t));
int no_proxy_match PARAMS ((const char *, const char **));

void convert_links PARAMS ((const char *, urlpos *));
urlpos *add_url PARAMS ((urlpos *, const char *, const char *));

downloaded_file_t downloaded_file PARAMS ((downloaded_file_t, const char *));

#endif /* URL_H */
