/* Declarations for url.c.
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

#ifndef URL_H
#define URL_H

/* If the string contains unsafe characters, duplicate it with
   encode_string, otherwise just copy it with strdup.  */
#define CLEANDUP(x) (contains_unsafe (x) ? encode_string (x) : xstrdup (x))

/* Structure containing info on a URL.  */
struct urlinfo
{
  char *url;			/* Unchanged URL */
  uerr_t proto;			/* URL protocol */
  char *host;			/* Extracted hostname */
  unsigned short port;
  char ftp_type;
  char *path, *dir, *file;	/* Path, as well as dir and file
				   (properly decoded) */
  char *user, *passwd;		/* Username and password */
  struct urlinfo *proxy;	/* The exact string to pass to proxy
				   server */
  char *referer;		/* The source from which the request
				   URI was obtained */
  char *local;			/* The local filename of the URL
				   document */
};

enum uflags
{
  URELATIVE     = 0x0001,      /* Is URL relative? */
  UNOPROTO      = 0x0002,      /* Is URL without a protocol? */
  UABS2REL      = 0x0004,      /* Convert absolute to relative? */
  UREL2ABS      = 0x0008       /* Convert relative to absolute? */
};

/* A structure that defines the whereabouts of a URL, i.e. its
   position in an HTML document, etc.  */
typedef struct _urlpos
{
  char *url;                   /* URL */
  char *local_name;            /* Local file to which it was saved */
  enum uflags flags;           /* Various flags */
  int pos, size;               /* Rekative position in the buffer */
  struct _urlpos *next;        /* Next struct in list */
} urlpos;


/* Function declarations */

int skip_url PARAMS ((const char *));

int contains_unsafe PARAMS ((const char *));
char *encode_string PARAMS ((const char *));

struct urlinfo *newurl PARAMS ((void));
void freeurl PARAMS ((struct urlinfo *, int));
uerr_t urlproto PARAMS ((const char *));
int skip_proto PARAMS ((const char *));
int skip_uname PARAMS ((const char *));

uerr_t parseurl PARAMS ((const char *, struct urlinfo *, int));
char *str_url PARAMS ((const struct urlinfo *, int));
int url_equal PARAMS ((const char *, const char *));

urlpos *get_urls_file PARAMS ((const char *));
urlpos *get_urls_html PARAMS ((const char *, const char *, int));
void free_urlpos PARAMS ((urlpos *));

void rotate_backups PARAMS ((const char *));
int mkalldirs PARAMS ((const char *));
char *url_filename PARAMS ((const struct urlinfo *));
void opt_url PARAMS ((struct urlinfo *));

char *getproxy PARAMS ((uerr_t));
int no_proxy_match PARAMS ((const char *, const char **));

void convert_links PARAMS ((const char *, urlpos *));
urlpos *add_url PARAMS ((urlpos *, const char *, const char *));

#endif /* URL_H */
