/* URL handling.
   Copyright (C) 1995, 1996, 1997, 2000 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <ctype.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <errno.h>
#include <assert.h>

#include "wget.h"
#include "utils.h"
#include "url.h"
#include "host.h"
#include "html.h"

#ifndef errno
extern int errno;
#endif

/* Default port definitions */
#define DEFAULT_HTTP_PORT 80
#define DEFAULT_FTP_PORT 21

/* URL separator (for findurl) */
#define URL_SEPARATOR "!\"#'(),>`{}|<>"

/* A list of unsafe characters for encoding, as per RFC1738.  '@' and
   ':' (not listed in RFC) were added because of user/password
   encoding.  */

#ifndef WINDOWS
# define URL_UNSAFE_CHARS "<>\"#%{}|\\^~[]`@:"
#else  /* WINDOWS */
# define URL_UNSAFE_CHARS "<>\"%{}|\\^[]`"
#endif /* WINDOWS */

#define UNSAFE_CHAR(c) (   ((unsigned char)(c) <= ' ')  /* ASCII 32  */  \
   			|| ((unsigned char)(c) >  '~')  /* ASCII 127 */  \
			|| strchr (URL_UNSAFE_CHARS, c))

/* If S contains unsafe characters, free it and replace it with a
   version that doesn't.  */
#define URL_CLEANSE(s) do			\
{						\
  if (contains_unsafe (s))			\
    {						\
      char *uc_tmp = encode_string (s);		\
      free (s);					\
      (s) = uc_tmp;				\
    }						\
} while (0)

/* Is a directory "."?  */
#define DOTP(x) ((*(x) == '.') && (!*(x + 1)))
/* Is a directory ".."?  */
#define DDOTP(x) ((*(x) == '.') && (*(x + 1) == '.') && (!*(x + 2)))

#if 0
static void path_simplify_with_kludge PARAMS ((char *));
#endif
static int urlpath_length PARAMS ((const char *));

/* NULL-terminated list of strings to be recognized as prototypes (URL
   schemes).  Note that recognized doesn't mean supported -- only HTTP
   and FTP are currently supported.

   However, a string that does not match anything in the list will be
   considered a relative URL.  Thus it's important that this list has
   anything anyone could think of being legal.

   There are wild things here.  :-) Take a look at
   <URL:http://www.w3.org/pub/WWW/Addressing/schemes.html> for more
   fun.  */
static char *protostrings[] =
{
  "cid:",
  "clsid:",
  "file:",
  "finger:",
  "ftp:",
  "gopher:",
  "hdl:",
  "http:",
  "https:",
  "ilu:",
  "ior:",
  "irc:",
  "java:",
  "javascript:",
  "lifn:",
  "mailto:",
  "mid:",
  "news:",
  "nntp:",
  "path:",
  "prospero:",
  "rlogin:",
  "service:",
  "shttp:",
  "snews:",
  "stanf:",
  "telnet:",
  "tn3270:",
  "wais:",
  "whois++:",
  NULL
};

struct proto
{
  char *name;
  uerr_t ind;
  unsigned short port;
};

/* Similar to former, but for supported protocols: */
static struct proto sup_protos[] =
{
  { "http://", URLHTTP, DEFAULT_HTTP_PORT },
  { "ftp://", URLFTP, DEFAULT_FTP_PORT },
  /*{ "file://", URLFILE, DEFAULT_FTP_PORT },*/
};

static void parse_dir PARAMS ((const char *, char **, char **));
static uerr_t parse_uname PARAMS ((const char *, char **, char **));
static char *construct PARAMS ((const char *, const char *, int , int));
static char *construct_relative PARAMS ((const char *, const char *));
static char process_ftp_type PARAMS ((char *));


/* Returns the number of characters to be skipped if the first thing
   in a URL is URL: (which is 0 or 4+).  The optional spaces after
   URL: are also skipped.  */
int
skip_url (const char *url)
{
  int i;

  if (TOUPPER (url[0]) == 'U'
      && TOUPPER (url[1]) == 'R'
      && TOUPPER (url[2]) == 'L'
      && url[3] == ':')
    {
      /* Skip blanks.  */
      for (i = 4; url[i] && ISSPACE (url[i]); i++);
      return i;
    }
  else
    return 0;
}

/* Returns 1 if the string contains unsafe characters, 0 otherwise.  */
int
contains_unsafe (const char *s)
{
  for (; *s; s++)
    if (UNSAFE_CHAR (*s))
      return 1;
  return 0;
}

/* Decodes the forms %xy in a URL to the character the hexadecimal
   code of which is xy.  xy are hexadecimal digits from
   [0123456789ABCDEF] (case-insensitive).  If x or y are not
   hex-digits or `%' precedes `\0', the sequence is inserted
   literally.  */

static void
decode_string (char *s)
{
  char *p = s;

  for (; *s; s++, p++)
    {
      if (*s != '%')
	*p = *s;
      else
	{
	  /* Do nothing if at the end of the string, or if the chars
	     are not hex-digits.  */
	  if (!*(s + 1) || !*(s + 2)
	      || !(ISXDIGIT (*(s + 1)) && ISXDIGIT (*(s + 2))))
	    {
	      *p = *s;
	      continue;
	    }
	  *p = (ASC2HEXD (*(s + 1)) << 4) + ASC2HEXD (*(s + 2));
	  s += 2;
	}
    }
  *p = '\0';
}

/* Encode the unsafe characters (as determined by URL_UNSAFE) in a
   given string, returning a malloc-ed %XX encoded string.  */
char *
encode_string (const char *s)
{
  const char *b;
  char *p, *res;
  int i;

  b = s;
  for (i = 0; *s; s++, i++)
    if (UNSAFE_CHAR (*s))
      i += 2; /* Two more characters (hex digits) */
  res = (char *)xmalloc (i + 1);
  s = b;
  for (p = res; *s; s++)
    if (UNSAFE_CHAR (*s))
      {
	const unsigned char c = *s;
	*p++ = '%';
	*p++ = HEXD2ASC (c >> 4);
	*p++ = HEXD2ASC (c & 0xf);
      }
    else
      *p++ = *s;
  *p = '\0';
  return res;
}

/* Returns the proto-type if URL's protocol is supported, or
   URLUNKNOWN if not.  */
uerr_t
urlproto (const char *url)
{
  int i;

  url += skip_url (url);
  for (i = 0; i < ARRAY_SIZE (sup_protos); i++)
    if (!strncasecmp (url, sup_protos[i].name, strlen (sup_protos[i].name)))
      return sup_protos[i].ind;
  for (i = 0; url[i] && url[i] != ':' && url[i] != '/'; i++);
  if (url[i] == ':')
    {
      for (++i; url[i] && url[i] != '/'; i++)
	if (!ISDIGIT (url[i]))
	  return URLBADPORT;
      if (url[i - 1] == ':')
	return URLFTP;
      else
	return URLHTTP;
    }
  else
    return URLHTTP;
}

/* Skip the protocol part of the URL, e.g. `http://'.  If no protocol
   part is found, returns 0.  */
int
skip_proto (const char *url)
{
  char **s;
  int l;

  for (s = protostrings; *s; s++)
    if (!strncasecmp (*s, url, strlen (*s)))
      break;
  if (!*s)
    return 0;
  l = strlen (*s);
  /* HTTP and FTP protocols are expected to yield exact host names
     (i.e. the `//' part must be skipped, too).  */
  if (!strcmp (*s, "http:") || !strcmp (*s, "ftp:"))
    l += 2;
  return l;
}

/* Returns 1 if the URL begins with a protocol (supported or
   unsupported), 0 otherwise.  */
static int
has_proto (const char *url)
{
  char **s;

  url += skip_url (url);
  for (s = protostrings; *s; s++)
    if (strncasecmp (url, *s, strlen (*s)) == 0)
      return 1;
  return 0;
}

/* Skip the username and password, if present here.  The function
   should be called *not* with the complete URL, but with the part
   right after the protocol.

   If no username and password are found, return 0.  */
int
skip_uname (const char *url)
{
  const char *p;
  for (p = url; *p && *p != '/'; p++)
    if (*p == '@')
      break;
  /* If a `@' was found before the first occurrence of `/', skip
     it.  */
  if (*p == '@')
    return p - url + 1;
  else
    return 0;
}

/* Allocate a new urlinfo structure, fill it with default values and
   return a pointer to it.  */
struct urlinfo *
newurl (void)
{
  struct urlinfo *u;

  u = (struct urlinfo *)xmalloc (sizeof (struct urlinfo));
  memset (u, 0, sizeof (*u));
  u->proto = URLUNKNOWN;
  return u;
}

/* Perform a "deep" free of the urlinfo structure.  The structure
   should have been created with newurl, but need not have been used.
   If free_pointer is non-0, free the pointer itself.  */
void
freeurl (struct urlinfo *u, int complete)
{
  assert (u != NULL);
  FREE_MAYBE (u->url);
  FREE_MAYBE (u->host);
  FREE_MAYBE (u->path);
  FREE_MAYBE (u->file);
  FREE_MAYBE (u->dir);
  FREE_MAYBE (u->user);
  FREE_MAYBE (u->passwd);
  FREE_MAYBE (u->local);
  FREE_MAYBE (u->referer);
  if (u->proxy)
    freeurl (u->proxy, 1);
  if (complete)
    free (u);
  return;
}

/* Extract the given URL of the form
   (http:|ftp:)// (user (:password)?@)?hostname (:port)? (/path)?
   1. hostname (terminated with `/' or `:')
   2. port number (terminated with `/'), or chosen for the protocol
   3. dirname (everything after hostname)
   Most errors are handled.  No allocation is done, you must supply
   pointers to allocated memory.
   ...and a host of other stuff :-)

   - Recognizes hostname:dir/file for FTP and
     hostname (:portnum)?/dir/file for HTTP.
   - Parses the path to yield directory and file
   - Parses the URL to yield the username and passwd (if present)
   - Decodes the strings, in case they contain "forbidden" characters
   - Writes the result to struct urlinfo

   If the argument STRICT is set, it recognizes only the canonical
   form.  */
uerr_t
parseurl (const char *url, struct urlinfo *u, int strict)
{
  int i, l, abs_ftp;
  int recognizable;            /* Recognizable URL is the one where
				  the protocol name was explicitly
				  named, i.e. it wasn't deduced from
				  the URL format.  */
  uerr_t type;

  DEBUGP (("parseurl (\"%s\") -> ", url));
  url += skip_url (url);
  recognizable = has_proto (url);
  if (strict && !recognizable)
    return URLUNKNOWN;
  for (i = 0, l = 0; i < ARRAY_SIZE (sup_protos); i++)
    {
      l = strlen (sup_protos[i].name);
      if (!strncasecmp (sup_protos[i].name, url, l))
	break;
    }
  /* If protocol is recognizable, but unsupported, bail out, else
     suppose unknown.  */
  if (recognizable && i == ARRAY_SIZE (sup_protos))
    return URLUNKNOWN;
  else if (i == ARRAY_SIZE (sup_protos))
    type = URLUNKNOWN;
  else
    u->proto = type = sup_protos[i].ind;

  if (type == URLUNKNOWN)
    l = 0;
  /* Allow a username and password to be specified (i.e. just skip
     them for now).  */
  if (recognizable)
    l += skip_uname (url + l);
  for (i = l; url[i] && url[i] != ':' && url[i] != '/'; i++);
  if (i == l)
    return URLBADHOST;
  /* Get the hostname.  */
  u->host = strdupdelim (url + l, url + i);
  DEBUGP (("host %s -> ", u->host));

  /* Assume no port has been given.  */
  u->port = 0;
  if (url[i] == ':')
    {
      /* We have a colon delimiting the hostname.  It could mean that
	 a port number is following it, or a directory.  */
      if (ISDIGIT (url[++i]))    /* A port number */
	{
	  if (type == URLUNKNOWN)
	    u->proto = type = URLHTTP;
	  for (; url[i] && url[i] != '/'; i++)
	    if (ISDIGIT (url[i]))
	      u->port = 10 * u->port + (url[i] - '0');
	    else
	      return URLBADPORT;
	  if (!u->port)
	    return URLBADPORT;
	  DEBUGP (("port %hu -> ", u->port));
	}
      else if (type == URLUNKNOWN) /* or a directory */
	u->proto = type = URLFTP;
      else                      /* or just a misformed port number */
	return URLBADPORT;
    }
  else if (type == URLUNKNOWN)
    u->proto = type = URLHTTP;
  if (!u->port)
    {
      int i;
      for (i = 0; i < ARRAY_SIZE (sup_protos); i++)
	if (sup_protos[i].ind == type)
	  break;
      if (i == ARRAY_SIZE (sup_protos))
	return URLUNKNOWN;
      u->port = sup_protos[i].port;
    }
  /* Some delimiter troubles...  */
  if (url[i] == '/' && url[i - 1] != ':')
    ++i;
  if (type == URLHTTP)
    while (url[i] && url[i] == '/')
      ++i;
  u->path = (char *)xmalloc (strlen (url + i) + 8);
  strcpy (u->path, url + i);
  if (type == URLFTP)
    {
      u->ftp_type = process_ftp_type (u->path);
      /* #### We don't handle type `d' correctly yet.  */
      if (!u->ftp_type || TOUPPER (u->ftp_type) == 'D')
	u->ftp_type = 'I';
    }
  DEBUGP (("opath %s -> ", u->path));
  /* Parse the username and password (if existing).  */
  parse_uname (url, &u->user, &u->passwd);
  /* Decode the strings, as per RFC 1738.  */
  decode_string (u->host);
  decode_string (u->path);
  if (u->user)
    decode_string (u->user);
  if (u->passwd)
    decode_string (u->passwd);
  /* Parse the directory.  */
  parse_dir (u->path, &u->dir, &u->file);
  DEBUGP (("dir %s -> file %s -> ", u->dir, u->file));
  /* Simplify the directory.  */
  path_simplify (u->dir);
  /* Remove the leading `/' in HTTP.  */
  if (type == URLHTTP && *u->dir == '/')
    strcpy (u->dir, u->dir + 1);
  DEBUGP (("ndir %s\n", u->dir));
  /* Strip trailing `/'.  */
  l = strlen (u->dir);
  if (l && u->dir[l - 1] == '/')
    u->dir[l - 1] = '\0';
  /* Re-create the path: */
  abs_ftp = (u->proto == URLFTP && *u->dir == '/');
  /*  sprintf (u->path, "%s%s%s%s", abs_ftp ? "%2F": "/",
      abs_ftp ? (u->dir + 1) : u->dir, *u->dir ? "/" : "", u->file); */
  strcpy (u->path, abs_ftp ? "%2F" : "/");
  strcat (u->path, abs_ftp ? (u->dir + 1) : u->dir);
  strcat (u->path, *u->dir ? "/" : "");
  strcat (u->path, u->file);
  URL_CLEANSE (u->path);
  DEBUGP (("newpath: %s\n", u->path));
  /* Create the clean URL.  */
  u->url = str_url (u, 0);
  return URLOK;
}

/* Special versions of DOTP and DDOTP for parse_dir(). */

#define PD_DOTP(x)  ((*(x) == '.') && (!*((x) + 1) || *((x) + 1) == '?'))
#define PD_DDOTP(x) ((*(x) == '.') && (*(x) == '.')		\
		     && (!*((x) + 2) || *((x) + 2) == '?'))

/* Build the directory and filename components of the path.  Both
   components are *separately* malloc-ed strings!  It does not change
   the contents of path.

   If the path ends with "." or "..", they are (correctly) counted as
   directories.  */
static void
parse_dir (const char *path, char **dir, char **file)
{
  int i, l;

  l = urlpath_length (path);
  for (i = l; i && path[i] != '/'; i--);

  if (!i && *path != '/')   /* Just filename */
    {
      if (PD_DOTP (path) || PD_DDOTP (path))
	{
	  *dir = strdupdelim (path, path + l);
	  *file = xstrdup (path + l); /* normally empty, but could
                                         contain ?... */
	}
      else
	{
	  *dir = xstrdup ("");     /* This is required because of FTP */
	  *file = xstrdup (path);
	}
    }
  else if (!i)                 /* /filename */
    {
      if (PD_DOTP (path + 1) || PD_DDOTP (path + 1))
	{
	  *dir = strdupdelim (path, path + l);
	  *file = xstrdup (path + l); /* normally empty, but could
                                         contain ?... */
	}
      else
	{
	  *dir = xstrdup ("/");
	  *file = xstrdup (path + 1);
	}
    }
  else /* Nonempty directory with or without a filename */
    {
      if (PD_DOTP (path + i + 1) || PD_DDOTP (path + i + 1))
	{
	  *dir = strdupdelim (path, path + l);
	  *file = xstrdup (path + l); /* normally empty, but could
                                         contain ?... */
	}
      else
	{
	  *dir = strdupdelim (path, path + i);
	  *file = xstrdup (path + i + 1);
	}
    }
}

/* Find the optional username and password within the URL, as per
   RFC1738.  The returned user and passwd char pointers are
   malloc-ed.  */
static uerr_t
parse_uname (const char *url, char **user, char **passwd)
{
  int l;
  const char *p, *col;
  char **where;

  *user = NULL;
  *passwd = NULL;
  url += skip_url (url);
  /* Look for end of protocol string.  */
  l = skip_proto (url);
  if (!l)
    return URLUNKNOWN;
  /* Add protocol offset.  */
  url += l;
  /* Is there an `@' character?  */
  for (p = url; *p && *p != '/'; p++)
    if (*p == '@')
      break;
  /* If not, return.  */
  if (*p != '@')
    return URLOK;
  /* Else find the username and password.  */
  for (p = col = url; *p != '@'; p++)
    {
      if (*p == ':' && !*user)
	{
	  *user = (char *)xmalloc (p - url + 1);
	  memcpy (*user, url, p - url);
	  (*user)[p - url] = '\0';
	  col = p + 1;
	}
    }
  /* Decide whether you have only the username or both.  */
  where = *user ? passwd : user;
  *where = (char *)xmalloc (p - col + 1);
  memcpy (*where, col, p - col);
  (*where)[p - col] = '\0';
  return URLOK;
}

/* If PATH ends with `;type=X', return the character X.  */
static char
process_ftp_type (char *path)
{
  int len = strlen (path);

  if (len >= 7
      && !memcmp (path + len - 7, ";type=", 6))
    {
      path[len - 7] = '\0';
      return path[len - 1];
    }
  else
    return '\0';
}

/* Return the URL as fine-formed string, with a proper protocol,
   optional port number, directory and optional user/password.  If
   HIDE is non-zero, password will be hidden.  The forbidden
   characters in the URL will be cleansed.  */
char *
str_url (const struct urlinfo *u, int hide)
{
  char *res, *host, *user, *passwd, *proto_name, *dir, *file;
  int i, l, ln, lu, lh, lp, lf, ld;
  unsigned short proto_default_port;

  /* Look for the protocol name.  */
  for (i = 0; i < ARRAY_SIZE (sup_protos); i++)
    if (sup_protos[i].ind == u->proto)
      break;
  if (i == ARRAY_SIZE (sup_protos))
    return NULL;
  proto_name = sup_protos[i].name;
  proto_default_port = sup_protos[i].port;
  host = CLEANDUP (u->host);
  dir = CLEANDUP (u->dir);
  file = CLEANDUP (u->file);
  user = passwd = NULL;
  if (u->user)
    user = CLEANDUP (u->user);
  if (u->passwd)
    {
      int i;
      passwd = CLEANDUP (u->passwd);
      if (hide)
	for (i = 0; passwd[i]; i++)
	  passwd[i] = 'x';
    }
  if (u->proto == URLFTP && *dir == '/')
    {
      char *tmp = (char *)xmalloc (strlen (dir) + 3);
      /*sprintf (tmp, "%%2F%s", dir + 1);*/
      tmp[0] = '%';
      tmp[1] = '2';
      tmp[2] = 'F';
      strcpy (tmp + 3, dir + 1);
      free (dir);
      dir = tmp;
    }

  ln = strlen (proto_name);
  lu = user ? strlen (user) : 0;
  lp = passwd ? strlen (passwd) : 0;
  lh = strlen (host);
  ld = strlen (dir);
  lf = strlen (file);
  res = (char *)xmalloc (ln + lu + lp + lh + ld + lf + 20); /* safe sex */
  /* sprintf (res, "%s%s%s%s%s%s:%d/%s%s%s", proto_name,
     (user ? user : ""), (passwd ? ":" : ""),
     (passwd ? passwd : ""), (user ? "@" : ""),
     host, u->port, dir, *dir ? "/" : "", file); */
  l = 0;
  memcpy (res, proto_name, ln);
  l += ln;
  if (user)
    {
      memcpy (res + l, user, lu);
      l += lu;
      if (passwd)
	{
	  res[l++] = ':';
	  memcpy (res + l, passwd, lp);
	  l += lp;
	}
      res[l++] = '@';
    }
  memcpy (res + l, host, lh);
  l += lh;
  if (u->port != proto_default_port)
    {
      res[l++] = ':';
      long_to_string (res + l, (long)u->port);
      l += numdigit (u->port);
    }
  res[l++] = '/';
  memcpy (res + l, dir, ld);
  l += ld;
  if (*dir)
    res[l++] = '/';
  strcpy (res + l, file);
  free (host);
  free (dir);
  free (file);
  FREE_MAYBE (user);
  FREE_MAYBE (passwd);
  return res;
}

/* Check whether two URL-s are equivalent, i.e. pointing to the same
   location.  Uses parseurl to parse them, and compares the canonical
   forms.

   Returns 1 if the URL1 is equivalent to URL2, 0 otherwise.  Also
   return 0 on error.  */
int
url_equal (const char *url1, const char *url2)
{
  struct urlinfo *u1, *u2;
  uerr_t err;
  int res;

  u1 = newurl ();
  err = parseurl (url1, u1, 0);
  if (err != URLOK)
    {
      freeurl (u1, 1);
      return 0;
    }
  u2 = newurl ();
  err = parseurl (url2, u2, 0);
  if (err != URLOK)
    {
      freeurl (u2, 1);
      return 0;
    }
  res = !strcmp (u1->url, u2->url);
  freeurl (u1, 1);
  freeurl (u2, 1);
  return res;
}

/* Find URL of format scheme:hostname[:port]/dir in a buffer.  The
   buffer may contain pretty much anything; no errors are signaled.  */
static const char *
findurl (const char *buf, int howmuch, int *count)
{
  char **prot;
  const char *s1, *s2;

  for (s1 = buf; howmuch; s1++, howmuch--)
    for (prot = protostrings; *prot; prot++)
      if (howmuch <= strlen (*prot))
	continue;
      else if (!strncasecmp (*prot, s1, strlen (*prot)))
	{
	  for (s2 = s1, *count = 0;
	       howmuch && *s2 && *s2 >= 32 && *s2 < 127 && !ISSPACE (*s2) &&
		 !strchr (URL_SEPARATOR, *s2);
	       s2++, (*count)++, howmuch--);
	  return s1;
	}
  return NULL;
}

/* Scans the file for signs of URL-s.  Returns a vector of pointers,
   each pointer representing a URL string.  The file is *not* assumed
   to be HTML.  */
urlpos *
get_urls_file (const char *file)
{
  long nread;
  FILE *fp;
  char *buf;
  const char *pbuf;
  int size;
  urlpos *first, *current, *old;

  if (file && !HYPHENP (file))
    {
      fp = fopen (file, "rb");
      if (!fp)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
	  return NULL;
	}
    }
  else
    fp = stdin;
  /* Load the file.  */
  load_file (fp, &buf, &nread);
  if (file && !HYPHENP (file))
    fclose (fp);
  DEBUGP (("Loaded %s (size %ld).\n", file, nread));
  first = current = NULL;
  /* Fill the linked list with URLs.  */
  for (pbuf = buf; (pbuf = findurl (pbuf, nread - (pbuf - buf), &size));
       pbuf += size)
    {
      /* Allocate the space.  */
      old = current;
      current = (urlpos *)xmalloc (sizeof (urlpos));
      if (old)
	old->next = current;
      memset (current, 0, sizeof (*current));
      current->next = NULL;
      current->url = (char *)xmalloc (size + 1);
      memcpy (current->url, pbuf, size);
      current->url[size] = '\0';
      if (!first)
	first = current;
    }
  /* Free the buffer.  */
  free (buf);

  return first;
}

/* Similar to get_urls_file, but for HTML files.  FILE is scanned as
   an HTML document using htmlfindurl(), which see.  get_urls_html()
   constructs the HTML-s from the relative href-s.

   If SILENT is non-zero, do not barf on baseless relative links.  */
urlpos *
get_urls_html (const char *file, const char *this_url, int silent,
	       int dash_p_leaf_HTML)
{
  long nread;
  FILE *fp;
  char *orig_buf;
  const char *buf;
  int step, first_time;
  urlpos *first, *current, *old;

  if (file && !HYPHENP (file))
    {
      fp = fopen (file, "rb");
      if (!fp)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
	  return NULL;
	}
    }
  else
    fp = stdin;
  /* Load the file.  */
  load_file (fp, &orig_buf, &nread);
  if (file && !HYPHENP (file))
    fclose (fp);
  DEBUGP (("Loaded HTML file %s (size %ld).\n", file, nread));
  first = current = NULL;
  first_time = 1;
  /* Iterate over the URLs in BUF, picked by htmlfindurl().  */
  for (buf = orig_buf;
       (buf = htmlfindurl (buf, nread - (buf - orig_buf), &step, first_time,
			   dash_p_leaf_HTML));
       buf += step)
    {
      int i, no_proto;
      int size = step;
      const char *pbuf = buf;
      char *constr, *base;
      const char *cbase;
      char *needs_freeing, *url_data;

      first_time = 0;

      /* A frequent phenomenon that needs to be handled are pages
         generated by brain-damaged HTML generators, which refer to to
         URI-s as <a href="<spaces>URI<spaces>">.  We simply ignore
         any spaces at the beginning or at the end of the string.
         This is probably not strictly correct, but that's what the
         browsers do, so we may follow.  May the authors of "WYSIWYG"
         HTML tools burn in hell for the damage they've inflicted!  */
      while ((pbuf < buf + step) && ISSPACE (*pbuf))
        {
          ++pbuf;
          --size;
        }
      while (size && ISSPACE (pbuf[size - 1]))
	--size;
      if (!size)
	break;

      /* It would be nice if we could avoid allocating memory in this
         loop, but I don't see an easy way.  To process the entities,
         we need to either copy the data, or change it destructively.
         I choose the former.

	 We have two pointers: needs_freeing and url_data, because the
	 code below does thing like url_data += <something>, and we
	 want to pass the original string to free(). */
      needs_freeing = url_data = html_decode_entities (pbuf, pbuf + size);
      size = strlen (url_data);

      for (i = 0; protostrings[i]; i++)
	{
	  if (!strncasecmp (protostrings[i], url_data,
			    MINVAL (strlen (protostrings[i]), size)))
	    break;
	}
      /* Check for http:RELATIVE_URI.  See below for details.  */
      if (protostrings[i]
	  && !(strncasecmp (url_data, "http:", 5) == 0
	       && strncasecmp (url_data, "http://", 7) != 0))
	{
	  no_proto = 0;
	}
      else
	{
	  no_proto = 1;
	  /* This is for extremely brain-damaged pages that refer to
	     relative URI-s as <a href="http:URL">.  Just strip off the
	     silly leading "http:" (as well as any leading blanks
	     before it).  */
	  if ((size > 5) && !strncasecmp ("http:", url_data, 5))
	    url_data += 5, size -= 5;
	}
      if (!no_proto)
	{
	  for (i = 0; i < ARRAY_SIZE (sup_protos); i++)
	    {
	      if (!strncasecmp (sup_protos[i].name, url_data,
			       MINVAL (strlen (sup_protos[i].name), size)))
		break;
	    }
	  /* Do *not* accept a non-supported protocol.  */
	  if (i == ARRAY_SIZE (sup_protos))
	    {
	      free (needs_freeing);
	      continue;
	    }
	}
      if (no_proto)
	{
	  /* First, construct the base, which can be relative itself.

	     Criteria for creating the base are:
	     1) html_base created by <base href="...">
	     2) current URL
	     3) base provided from the command line */
	  cbase = html_base ();
	  if (!cbase)
	    cbase = this_url;
	  if (!cbase)
	    cbase = opt.base_href;
	  if (!cbase)             /* Error condition -- a baseless
				     relative link.  */
	    {
	      if (!opt.quiet && !silent)
		{
		  /* Use malloc, not alloca because this is called in
                     a loop. */
		  char *temp = (char *)malloc (size + 1);
		  strncpy (temp, url_data, size);
		  temp[size] = '\0';
		  logprintf (LOG_NOTQUIET,
			     _("Error (%s): Link %s without a base provided.\n"),
			     file, temp);
		  free (temp);
		}
	      free (needs_freeing);
	      continue;
	    }
	  if (this_url)
	    base = construct (this_url, cbase, strlen (cbase),
			      !has_proto (cbase));
	  else
	    {
	      /* Base must now be absolute, with host name and
		 protocol.  */
	      if (!has_proto (cbase))
		{
		  logprintf (LOG_NOTQUIET, _("\
Error (%s): Base %s relative, without referer URL.\n"),
			     file, cbase);
		  free (needs_freeing);
		  continue;
		}
	      base = xstrdup (cbase);
	    }
	  constr = construct (base, url_data, size, no_proto);
	  free (base);
	}
      else /* has proto */
	{
	  constr = (char *)xmalloc (size + 1);
	  strncpy (constr, url_data, size);
	  constr[size] = '\0';
	}
#ifdef DEBUG
      if (opt.debug)
	{
	  char *tmp;
	  const char *tmp2;

	  tmp2 = html_base ();
	  /* Use malloc, not alloca because this is called in a loop. */
	  tmp = (char *)xmalloc (size + 1);
	  strncpy (tmp, url_data, size);
	  tmp[size] = '\0';
	  logprintf (LOG_ALWAYS,
		     "file %s; this_url %s; base %s\nlink: %s; constr: %s\n",
		     file, this_url ? this_url : "(null)",
		     tmp2 ? tmp2 : "(null)", tmp, constr);
	  free (tmp);
	}
#endif

      /* Allocate the space.  */
      old = current;
      current = (urlpos *)xmalloc (sizeof (urlpos));
      if (old)
	old->next = current;
      if (!first)
	first = current;
      /* Fill the values.  */
      memset (current, 0, sizeof (*current));
      current->next = NULL;
      current->url = constr;
      current->size = step;
      current->pos = buf - orig_buf;
      /* A URL is relative if the host and protocol are not named,
	 and the name does not start with `/'.  */
      if (no_proto && *url_data != '/')
	current->flags |= (URELATIVE | UNOPROTO);
      else if (no_proto)
	current->flags |= UNOPROTO;
      free (needs_freeing);
    }
  free (orig_buf);

  return first;
}

/* Free the linked list of urlpos.  */
void
free_urlpos (urlpos *l)
{
  while (l)
    {
      urlpos *next = l->next;
      free (l->url);
      FREE_MAYBE (l->local_name);
      free (l);
      l = next;
    }
}

/* Rotate FNAME opt.backups times */
void
rotate_backups(const char *fname)
{
  int maxlen = strlen (fname) + 1 + numdigit (opt.backups) + 1;
  char *from = (char *)alloca (maxlen);
  char *to = (char *)alloca (maxlen);
  struct stat sb;
  int i;

  if (stat (fname, &sb) == 0)
    if (S_ISREG (sb.st_mode) == 0)
      return;

  for (i = opt.backups; i > 1; i--)
    {
      sprintf (from, "%s.%d", fname, i - 1);
      sprintf (to, "%s.%d", fname, i);
      /* #### This will fail on machines without the rename() system
         call.  */
      rename (from, to);
    }

  sprintf (to, "%s.%d", fname, 1);
  rename(fname, to);
}

/* Create all the necessary directories for PATH (a file).  Calls
   mkdirhier() internally.  */
int
mkalldirs (const char *path)
{
  const char *p;
  char *t;
  struct stat st;
  int res;

  p = path + strlen (path);
  for (; *p != '/' && p != path; p--);
  /* Don't create if it's just a file.  */
  if ((p == path) && (*p != '/'))
    return 0;
  t = strdupdelim (path, p);
  /* Check whether the directory exists.  */
  if ((stat (t, &st) == 0))
    {
      if (S_ISDIR (st.st_mode))
	{
	  free (t);
	  return 0;
	}
      else
	{
	  /* If the dir exists as a file name, remove it first.  This
	     is *only* for Wget to work with buggy old CERN http
	     servers.  Here is the scenario: When Wget tries to
	     retrieve a directory without a slash, e.g.
	     http://foo/bar (bar being a directory), CERN server will
	     not redirect it too http://foo/bar/ -- it will generate a
	     directory listing containing links to bar/file1,
	     bar/file2, etc.  Wget will lose because it saves this
	     HTML listing to a file `bar', so it cannot create the
	     directory.  To work around this, if the file of the same
	     name exists, we just remove it and create the directory
	     anyway.  */
	  DEBUGP (("Removing %s because of directory danger!\n", t));
	  unlink (t);
	}
    }
  res = make_directory (t);
  if (res != 0)
    logprintf (LOG_NOTQUIET, "%s: %s", t, strerror (errno));
  free (t);
  return res;
}

static int
count_slashes (const char *s)
{
  int i = 0;
  while (*s)
    if (*s++ == '/')
      ++i;
  return i;
}

/* Return the path name of the URL-equivalent file name, with a
   remote-like structure of directories.  */
static char *
mkstruct (const struct urlinfo *u)
{
  char *host, *dir, *file, *res, *dirpref;
  int l;

  assert (u->dir != NULL);
  assert (u->host != NULL);

  if (opt.cut_dirs)
    {
      char *ptr = u->dir + (*u->dir == '/');
      int slash_count = 1 + count_slashes (ptr);
      int cut = MINVAL (opt.cut_dirs, slash_count);
      for (; cut && *ptr; ptr++)
	if (*ptr == '/')
	  --cut;
      STRDUP_ALLOCA (dir, ptr);
    }
  else
    dir = u->dir + (*u->dir == '/');

  host = xstrdup (u->host);
  /* Check for the true name (or at least a consistent name for saving
     to directory) of HOST, reusing the hlist if possible.  */
  if (opt.add_hostdir && !opt.simple_check)
    {
      char *nhost = realhost (host);
      free (host);
      host = nhost;
    }
  /* Add dir_prefix and hostname (if required) to the beginning of
     dir.  */
  if (opt.add_hostdir)
    {
      if (!DOTP (opt.dir_prefix))
	{
	  dirpref = (char *)alloca (strlen (opt.dir_prefix) + 1
				    + strlen (host) + 1);
	  sprintf (dirpref, "%s/%s", opt.dir_prefix, host);
	}
      else
	STRDUP_ALLOCA (dirpref, host);
    }
  else                         /* not add_hostdir */
    {
      if (!DOTP (opt.dir_prefix))
	dirpref = opt.dir_prefix;
      else
	dirpref = "";
    }
  free (host);

  /* If there is a prefix, prepend it.  */
  if (*dirpref)
    {
      char *newdir = (char *)alloca (strlen (dirpref) + 1 + strlen (dir) + 2);
      sprintf (newdir, "%s%s%s", dirpref, *dir == '/' ? "" : "/", dir);
      dir = newdir;
    }
  dir = xstrdup (dir);
  URL_CLEANSE (dir);
  l = strlen (dir);
  if (l && dir[l - 1] == '/')
    dir[l - 1] = '\0';

  if (!*u->file)
    file = "index.html";
  else
    file = u->file;

  /* Finally, construct the full name.  */
  res = (char *)xmalloc (strlen (dir) + 1 + strlen (file) + 1);
  sprintf (res, "%s%s%s", dir, *dir ? "/" : "", file);
  free (dir);
  return res;
}

/* Create a unique filename, corresponding to a given URL.  Calls
   mkstruct if necessary.  Does *not* actually create any directories.  */
char *
url_filename (const struct urlinfo *u)
{
  char *file, *name;
  int have_prefix = 0;		/* whether we must prepend opt.dir_prefix */

  if (opt.dirstruct)
    {
      file = mkstruct (u);
      have_prefix = 1;
    }
  else
    {
      if (!*u->file)
	file = xstrdup ("index.html");
      else
	file = xstrdup (u->file);
    }

  if (!have_prefix)
    {
      /* Check whether the prefix directory is something other than "."
	 before prepending it.  */
      if (!DOTP (opt.dir_prefix))
	{
	  char *nfile = (char *)xmalloc (strlen (opt.dir_prefix)
					 + 1 + strlen (file) + 1);
	  sprintf (nfile, "%s/%s", opt.dir_prefix, file);
	  free (file);
	  file = nfile;
	}
    }
  /* DOS-ish file systems don't like `%' signs in them; we change it
     to `@'.  */
#ifdef WINDOWS
  {
    char *p = file;
    for (p = file; *p; p++)
      if (*p == '%')
	*p = '@';
  }
#endif /* WINDOWS */

  /* Check the cases in which the unique extensions are not used:
     1) Clobbering is turned off (-nc).
     2) Retrieval with regetting.
     3) Timestamping is used.
     4) Hierarchy is built.

     The exception is the case when file does exist and is a
     directory (actually support for bad httpd-s).  */
  if ((opt.noclobber || opt.always_rest || opt.timestamping || opt.dirstruct)
      && !(file_exists_p (file) && !file_non_directory_p (file)))
    return file;

  /* Find a unique name.  */
  name = unique_name (file);
  free (file);
  return name;
}

/* Like strlen(), but allow the URL to be ended with '?'.  */
static int
urlpath_length (const char *url)
{
  const char *q = strchr (url, '?');
  if (q)
    return q - url;
  return strlen (url);
}

/* Find the last occurrence of character C in the range [b, e), or
   NULL, if none are present.  This is almost completely equivalent to
   { *e = '\0'; return strrchr(b); }, except that it doesn't change
   the contents of the string.  */
static const char *
find_last_char (const char *b, const char *e, char c)
{
  for (; e > b; e--)
    if (*e == c)
      return e;
  return NULL;
}

/* Construct a URL by concatenating an absolute URL and a path, which
   may or may not be absolute.  This tries to behave "reasonably" in
   all foreseeable cases.  It employs little specific knowledge about
   protocols or URL-specific stuff -- it just works on strings.  */
static char *
construct (const char *url, const char *sub, int subsize, int no_proto)
{
  char *constr;

  if (no_proto)
    {
      const char *end = url + urlpath_length (url);

      if (*sub != '/')
	{
	  /* SUB is a relative URL: we need to replace everything
	     after last slash (possibly empty) with SUB.

	     So, if URL is "whatever/foo/bar", and SUB is "qux/xyzzy",
	     our result should be "whatever/foo/qux/xyzzy".  */
	  int need_explicit_slash = 0;
	  int span;
	  const char *start_insert;
	  const char *last_slash = find_last_char (url, end, '/'); /* the last slash. */
	  if (!last_slash)
	    {
	      /* No slash found at all.  Append SUB to what we have,
		 but we'll need a slash as a separator.

		 Example: if url == "foo" and sub == "qux/xyzzy", then
		 we cannot just append sub to url, because we'd get
		 "fooqux/xyzzy", whereas what we want is
		 "foo/qux/xyzzy".

		 To make sure the / gets inserted, we set
		 need_explicit_slash to 1.  We also set start_insert
		 to end + 1, so that the length calculations work out
		 correctly for one more (slash) character.  Accessing
		 that character is fine, since it will be the
		 delimiter, '\0' or '?'.  */
	      /* example: "foo?..." */
	      /*               ^    ('?' gets changed to '/') */
	      start_insert = end + 1;
	      need_explicit_slash = 1;
	    }
	  else if (last_slash && last_slash != url && last_slash[-1] == '/')
	    {
	      /* example: http://host"  */
	      /*                      ^ */
	      start_insert = end + 1;
	      need_explicit_slash = 1;
	    }
	  else
	    {
	      /* example: "whatever/foo/bar" */
	      /*                        ^    */
	      start_insert = last_slash + 1;
	    }

	  span = start_insert - url;
	  constr = (char *)xmalloc (span + subsize + 1);
	  if (span)
	    memcpy (constr, url, span);
	  if (need_explicit_slash)
	    constr[span - 1] = '/';
	  if (subsize)
	    memcpy (constr + span, sub, subsize);
	  constr[span + subsize] = '\0';
	}
      else /* *sub == `/' */
	{
	  /* SUB is an absolute path: we need to replace everything
             after (and including) the FIRST slash with SUB.

	     So, if URL is "http://host/whatever/foo/bar", and SUB is
	     "/qux/xyzzy", our result should be
	     "http://host/qux/xyzzy".  */
	  int span;
	  const char *slash;
	  const char *start_insert = NULL; /* for gcc to shut up. */
	  const char *pos = url;
	  int seen_slash_slash = 0;
	  /* We're looking for the first slash, but want to ignore
             double slash. */
	again:
	  slash = memchr (pos, '/', end - pos);
	  if (slash && !seen_slash_slash)
	    if (*(slash + 1) == '/')
	      {
		pos = slash + 2;
		seen_slash_slash = 1;
		goto again;
	      }

	  /* At this point, SLASH is the location of the first / after
	     "//", or the first slash altogether.  START_INSERT is the
	     pointer to the location where SUB will be inserted.  When
	     examining the last two examples, keep in mind that SUB
	     begins with '/'. */

	  if (!slash && !seen_slash_slash)
	    /* example: "foo" */
	    /*           ^    */
	    start_insert = url;
	  else if (!slash && seen_slash_slash)
	    /* example: "http://foo" */
	    /*                     ^ */
	    start_insert = end;
	  else if (slash && !seen_slash_slash)
	    /* example: "foo/bar" */
	    /*           ^        */
	    start_insert = url;
	  else if (slash && seen_slash_slash)
	    /* example: "http://something/" */
	    /*                           ^  */
	    start_insert = slash;

	  span = start_insert - url;
	  constr = (char *)xmalloc (span + subsize + 1);
	  if (span)
	    memcpy (constr, url, span);
	  if (subsize)
	    memcpy (constr + span, sub, subsize);
	  constr[span + subsize] = '\0';
	}
    }
  else /* !no_proto */
    {
      constr = strdupdelim (sub, sub + subsize);
    }
  return constr;
}

/* Like the function above, but with a saner caller interface. */
char *
url_concat (const char *base_url, const char *new_url)
{
  return construct (base_url, new_url, strlen (new_url), !has_proto (new_url));
}

/* Optimize URL by host, destructively replacing u->host with realhost
   (u->host).  Do this regardless of opt.simple_check.  */
void
opt_url (struct urlinfo *u)
{
  /* Find the "true" host.  */
  char *host = realhost (u->host);
  free (u->host);
  u->host = host;
  assert (u->dir != NULL);      /* the URL must have been parsed */
  /* Refresh the printed representation.  */
  free (u->url);
  u->url = str_url (u, 0);
}

/* This beautiful kludge is fortunately not needed, as I've made
   parse_dir do the (almost) right thing, so that a query can never
   become a part of directory.  */
#if 0
/* Call path_simplify, but make sure that the part after the
   question-mark, if any, is not destroyed by path_simplify's
   "optimizations".  */
void
path_simplify_with_kludge (char *path)
{
  char *query = strchr (path, '?');
  if (query)
    /* path_simplify also works destructively, so we also have the
       license to write. */
    *query = '\0';
  path_simplify (path);
  if (query)
    {
      char *newend = path + strlen (path);
      *query = '?';
      if (newend != query)
	memmove (newend, query, strlen (query) + 1);
    }
}
#endif

/* Returns proxy host address, in accordance with PROTO.  */
char *
getproxy (uerr_t proto)
{
  if (proto == URLHTTP)
    return opt.http_proxy ? opt.http_proxy : getenv ("http_proxy");
  else if (proto == URLFTP)
    return opt.ftp_proxy ? opt.ftp_proxy : getenv ("ftp_proxy");
  else
    return NULL;
}

/* Should a host be accessed through proxy, concerning no_proxy?  */
int
no_proxy_match (const char *host, const char **no_proxy)
{
  if (!no_proxy)
    return 1;
  else
    return !sufmatch (no_proxy, host);
}

/* Change the links in an HTML document.  Accepts a structure that
   defines the positions of all the links.  */
void
convert_links (const char *file, urlpos *l)
{
  FILE               *fp;
  char               *buf, *p, *p2;
  downloaded_file_t  downloaded_file_return;
  long               size;

  logprintf (LOG_VERBOSE, _("Converting %s... "), file);
  /* Read from the file....  */
  fp = fopen (file, "rb");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, _("Cannot convert links in %s: %s\n"),
		 file, strerror (errno));
      return;
    }
  /* ...to a buffer.  */
  load_file (fp, &buf, &size);
  fclose (fp);

  downloaded_file_return = downloaded_file(CHECK_FOR_FILE, file);

  if (opt.backup_converted && downloaded_file_return)
    /* Rather than just writing over the original .html file with the converted
       version, save the former to *.orig.  Note we only do this for files we've
       _successfully_ downloaded, so we don't clobber .orig files sitting around
       from previous invocations. */
    {
      /* Construct the backup filename as the original name plus ".orig". */
      size_t         filename_len = strlen(file);
      char*          filename_plus_orig_suffix;
      boolean        already_wrote_backup_file = FALSE;
      slist*         converted_file_ptr;
      static slist*  converted_files = NULL;

      if (downloaded_file_return == FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED)
	{
	  /* Just write "orig" over "html".  We need to do it this way because
	     when we're checking to see if we've downloaded the file before (to
	     see if we can skip downloading it), we don't know if it's a
	     text/html file.  Therefore we don't know yet at that stage that -E
	     is going to cause us to tack on ".html", so we need to compare
	     vs. the original URL plus ".orig", not the original URL plus
	     ".html.orig". */
	  filename_plus_orig_suffix = xmalloc(filename_len + 1);
	  strcpy(filename_plus_orig_suffix, file);
	  strcpy((filename_plus_orig_suffix + filename_len) - 4, "orig");
	}
      else /* downloaded_file_return == FILE_DOWNLOADED_NORMALLY */
	{
	  /* Append ".orig" to the name. */
	  filename_plus_orig_suffix = xmalloc(filename_len + sizeof(".orig"));
	  strcpy(filename_plus_orig_suffix, file);
	  strcpy(filename_plus_orig_suffix + filename_len, ".orig");
	}

      /* We can get called twice on the same URL thanks to the
	 convert_all_links() call in main().  If we write the .orig file each
	 time in such a case, it'll end up containing the first-pass conversion,
	 not the original file.  So, see if we've already been called on this
	 file. */
      converted_file_ptr = converted_files;
      while (converted_file_ptr != NULL)
	if (strcmp(converted_file_ptr->string, file) == 0)
	  {
	    already_wrote_backup_file = TRUE;
	    break;
	  }
	else
	  converted_file_ptr = converted_file_ptr->next;

      if (!already_wrote_backup_file)
	{
	  /* Rename <file> to <file>.orig before former gets written over. */
	  if (rename(file, filename_plus_orig_suffix) != 0)
	    logprintf (LOG_NOTQUIET, _("Cannot back up %s as %s: %s\n"),
		       file, filename_plus_orig_suffix, strerror (errno));

	  /* Remember that we've already written a .orig backup for this file.
	     Note that we never free this memory since we need it till the
	     convert_all_links() call, which is one of the last things the
	     program does before terminating.  BTW, I'm not sure if it would be
	     safe to just set 'converted_file_ptr->string' to 'file' below,
	     rather than making a copy of the string...  Another note is that I
	     thought I could just add a field to the urlpos structure saying
	     that we'd written a .orig file for this URL, but that didn't work,
	     so I had to make this separate list. */
	  converted_file_ptr = xmalloc(sizeof(*converted_file_ptr));
	  converted_file_ptr->string = xstrdup(file);  /* die on out-of-mem. */
	  converted_file_ptr->next = converted_files;
	  converted_files = converted_file_ptr;
	}

      free(filename_plus_orig_suffix);
    }
  /* Now open the file for writing.  */
  fp = fopen (file, "wb");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, _("Cannot convert links in %s: %s\n"),
		 file, strerror (errno));
      free (buf);
      return;
    }
  /* Presumably we have to loop through multiple URLs here (even though we're
     only talking about a single local file) because of the -O option. */
  for (p = buf; l; l = l->next)
    {
      if (l->pos >= size)
	{
	  DEBUGP (("Something strange is going on.  Please investigate."));
	  break;
	}
      /* If the URL already is relative or it is not to be converted
	 for some other reason (e.g. because of not having been
	 downloaded in the first place), skip it.  */
      if ((l->flags & URELATIVE) || !(l->flags & UABS2REL))
	{
	  DEBUGP (("Skipping %s at position %d (flags %d).\n", l->url,
		   l->pos, l->flags));
	  continue;
	}
      /* Else, reach the position of the offending URL, echoing
	 everything up to it to the outfile.  */
      for (p2 = buf + l->pos; p < p2; p++)
	putc (*p, fp);
      if (l->flags & UABS2REL)
	/* Convert absolute URL to relative. */
	{
	  char *newname = construct_relative (file, l->local_name);
	  fprintf (fp, "%s", newname);
	  DEBUGP (("ABS2REL: %s to %s at position %d in %s.\n",
		   l->url, newname, l->pos, file));
	  free (newname);
	}
      p += l->size;
    }
  /* Output the rest of the file. */
  if (p - buf < size)
    {
      for (p2 = buf + size; p < p2; p++)
	putc (*p, fp);
    }
  fclose (fp);
  free (buf);
  logputs (LOG_VERBOSE, _("done.\n"));
}

/* Construct and return a malloced copy of the relative link from two
   pieces of information: local name S1 of the referring file and
   local name S2 of the referred file.

   So, if S1 is "jagor.srce.hr/index.html" and S2 is
   "jagor.srce.hr/images/news.gif", the function will return
   "images/news.gif".

   Alternately, if S1 is "fly.cc.fer.hr/ioccc/index.html", and S2 is
   "fly.cc.fer.hr/images/fly.gif", the function will return
   "../images/fly.gif".

   Caveats: S1 should not begin with `/', unless S2 also begins with
   '/'.  S1 should not contain things like ".." and such --
   construct_relative ("fly/ioccc/../index.html",
   "fly/images/fly.gif") will fail.  (A workaround is to call
   something like path_simplify() on S1).  */
static char *
construct_relative (const char *s1, const char *s2)
{
  int i, cnt, sepdirs1;
  char *res;

  if (*s2 == '/')
    return xstrdup (s2);
  /* S1 should *not* be absolute, if S2 wasn't.  */
  assert (*s1 != '/');
  i = cnt = 0;
  /* Skip the directories common to both strings.  */
  while (1)
    {
      while (s1[i] && s2[i]
	     && (s1[i] == s2[i])
	     && (s1[i] != '/')
	     && (s2[i] != '/'))
	++i;
      if (s1[i] == '/' && s2[i] == '/')
	cnt = ++i;
      else
	break;
    }
  for (sepdirs1 = 0; s1[i]; i++)
    if (s1[i] == '/')
      ++sepdirs1;
  /* Now, construct the file as of:
     - ../ repeated sepdirs1 time
     - all the non-mutual directories of S2.  */
  res = (char *)xmalloc (3 * sepdirs1 + strlen (s2 + cnt) + 1);
  for (i = 0; i < sepdirs1; i++)
    memcpy (res + 3 * i, "../", 3);
  strcpy (res + 3 * i, s2 + cnt);
  return res;
}

/* Add URL to the head of the list L.  */
urlpos *
add_url (urlpos *l, const char *url, const char *file)
{
  urlpos *t;

  t = (urlpos *)xmalloc (sizeof (urlpos));
  memset (t, 0, sizeof (*t));
  t->url = xstrdup (url);
  t->local_name = xstrdup (file);
  t->next = l;
  return t;
}


/* Remembers which files have been downloaded.  In the standard case, should be
   called with mode == FILE_DOWNLOADED_NORMALLY for each file we actually
   download successfully (i.e. not for ones we have failures on or that we skip
   due to -N).

   When we've downloaded a file and tacked on a ".html" extension due to -E,
   call this function with FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED rather than
   FILE_DOWNLOADED_NORMALLY.

   If you just want to check if a file has been previously added without adding
   it, call with mode == CHECK_FOR_FILE.  Please be sure to call this function
   with local filenames, not remote URLs. */
downloaded_file_t
downloaded_file (downloaded_file_t  mode, const char*  file)
{
  typedef struct _downloaded_file_list
  {
    char*                          file;
    downloaded_file_t              download_type;
    struct _downloaded_file_list*  next;
  } downloaded_file_list;
  
  boolean                       found_file = FALSE;
  static downloaded_file_list*  downloaded_files = NULL;
  downloaded_file_list*         rover = downloaded_files;

  while (rover != NULL)
    if (strcmp(rover->file, file) == 0)
      {
	found_file = TRUE;
	break;
      }
    else
      rover = rover->next;

  if (found_file)
    return rover->download_type;  /* file had already been downloaded */
  else
    {
      if (mode != CHECK_FOR_FILE)
	{
	  rover = xmalloc(sizeof(*rover));
	  rover->file = xstrdup(file); /* use xstrdup() so die on out-of-mem. */
	  rover->download_type = mode;
	  rover->next = downloaded_files;
	  downloaded_files = rover;
	}

      return FILE_NOT_ALREADY_DOWNLOADED;
    }
}
