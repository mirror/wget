/* URL handling.
   Copyright (C) 1995, 1996, 1997, 2000, 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
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

#ifndef errno
extern int errno;
#endif

/* Is X "."?  */
#define DOTP(x) ((*(x) == '.') && (!*(x + 1)))
/* Is X ".."?  */
#define DDOTP(x) ((*(x) == '.') && (*(x + 1) == '.') && (!*(x + 2)))

static int urlpath_length PARAMS ((const char *));

/* A NULL-terminated list of strings to be recognized as protocol
   types (URL schemes).  Note that recognized doesn't mean supported
   -- only HTTP, HTTPS and FTP are currently supported.

   However, a string that does not match anything in the list will be
   considered a relative URL.  Thus it's important that this list has
   anything anyone could think of being legal.

   #### This is probably broken.  Wget should use other means to
   distinguish between absolute and relative URIs in HTML links.

   Take a look at <http://www.w3.org/pub/WWW/Addressing/schemes.html>
   for more.  */
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
#ifdef HAVE_SSL
  { "https://",URLHTTPS, DEFAULT_HTTPS_PORT},
#endif
  { "ftp://", URLFTP, DEFAULT_FTP_PORT }
};

static void parse_dir PARAMS ((const char *, char **, char **));
static uerr_t parse_uname PARAMS ((const char *, char **, char **));
static char *construct_relative PARAMS ((const char *, const char *));
static char process_ftp_type PARAMS ((char *));


/* Support for encoding and decoding of URL strings.  We determine
   whether a character is unsafe through static table lookup.  This
   code assumes ASCII character set and 8-bit chars.  */

enum {
  urlchr_reserved = 1,
  urlchr_unsafe   = 2
};

#define R  urlchr_reserved
#define U  urlchr_unsafe
#define RU R|U

#define urlchr_test(c, mask) (urlchr_table[(unsigned char)(c)] & (mask))

/* rfc1738 reserved chars.  We don't use this yet; preservation of
   reserved chars will be implemented when I integrate the new
   `reencode_string' function.  */

#define RESERVED_CHAR(c) urlchr_test(c, urlchr_reserved)

/* Unsafe chars:
   - anything <= 32;
   - stuff from rfc1738 ("<>\"#%{}|\\^~[]`");
   - '@' and ':'; needed for encoding URL username and password.
   - anything >= 127. */

#define UNSAFE_CHAR(c) urlchr_test(c, urlchr_unsafe)

const static unsigned char urlchr_table[256] =
{
  U,  U,  U,  U,   U,  U,  U,  U,   /* NUL SOH STX ETX  EOT ENQ ACK BEL */
  U,  U,  U,  U,   U,  U,  U,  U,   /* BS  HT  LF  VT   FF  CR  SO  SI  */
  U,  U,  U,  U,   U,  U,  U,  U,   /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
  U,  U,  U,  U,   U,  U,  U,  U,   /* CAN EM  SUB ESC  FS  GS  RS  US  */
  U,  0,  U,  U,   0,  U,  R,  0,   /* SP  !   "   #    $   %   &   '   */
  0,  0,  0,  R,   0,  0,  0,  R,   /* (   )   *   +    ,   -   .   /   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* 0   1   2   3    4   5   6   7   */
  0,  0,  U,  R,   U,  R,  U,  R,   /* 8   9   :   ;    <   =   >   ?   */
 RU,  0,  0,  0,   0,  0,  0,  0,   /* @   A   B   C    D   E   F   G   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* H   I   J   K    L   M   N   O   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* P   Q   R   S    T   U   V   W   */
  0,  0,  0,  U,   U,  U,  U,  0,   /* X   Y   Z   [    \   ]   ^   _   */
  U,  0,  0,  0,   0,  0,  0,  0,   /* `   a   b   c    d   e   f   g   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* h   i   j   k    l   m   n   o   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* p   q   r   s    t   u   v   w   */
  0,  0,  0,  U,   U,  U,  U,  U,   /* x   y   z   {    |   }   ~   DEL */

  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,

  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
  U, U, U, U,  U, U, U, U,  U, U, U, U,  U, U, U, U,
};

/* Decodes the forms %xy in a URL to the character the hexadecimal
   code of which is xy.  xy are hexadecimal digits from
   [0123456789ABCDEF] (case-insensitive).  If x or y are not
   hex-digits or `%' precedes `\0', the sequence is inserted
   literally.  */

static void
decode_string (char *s)
{
  char *t = s;			/* t - tortoise */
  char *h = s;			/* h - hare     */

  for (; *h; h++, t++)
    {
      if (*h != '%')
	{
	copychar:
	  *t = *h;
	}
      else
	{
	  /* Do nothing if '%' is not followed by two hex digits. */
	  if (!*(h + 1) || !*(h + 2)
	      || !(ISXDIGIT (*(h + 1)) && ISXDIGIT (*(h + 2))))
	    goto copychar;
	  *t = (XCHAR_TO_XDIGIT (*(h + 1)) << 4) + XCHAR_TO_XDIGIT (*(h + 2));
	  h += 2;
	}
    }
  *t = '\0';
}

/* Like encode_string, but return S if there are no unsafe chars.  */

static char *
encode_string_maybe (const char *s)
{
  const char *p1;
  char *p2, *newstr;
  int newlen;
  int addition = 0;

  for (p1 = s; *p1; p1++)
    if (UNSAFE_CHAR (*p1))
      addition += 2;		/* Two more characters (hex digits) */

  if (!addition)
    return (char *)s;

  newlen = (p1 - s) + addition;
  newstr = (char *)xmalloc (newlen + 1);

  p1 = s;
  p2 = newstr;
  while (*p1)
    {
      if (UNSAFE_CHAR (*p1))
	{
	  const unsigned char c = *p1++;
	  *p2++ = '%';
	  *p2++ = XDIGIT_TO_XCHAR (c >> 4);
	  *p2++ = XDIGIT_TO_XCHAR (c & 0xf);
	}
      else
	*p2++ = *p1++;
    }
  *p2 = '\0';
  assert (p2 - newstr == newlen);

  return newstr;
}

/* Encode the unsafe characters (as determined by UNSAFE_CHAR) in a
   given string, returning a malloc-ed %XX encoded string.  */
  
char *
encode_string (const char *s)
{
  char *encoded = encode_string_maybe (s);
  if (encoded != s)
    return encoded;
  else
    return xstrdup (s);
}

/* Encode unsafe characters in PTR to %xx.  If such encoding is done,
   the old value of PTR is freed and PTR is made to point to the newly
   allocated storage.  */

#define ENCODE(ptr) do {			\
  char *e_new = encode_string_maybe (ptr);	\
  if (e_new != ptr)				\
    {						\
      xfree (ptr);				\
      ptr = e_new;				\
    }						\
} while (0)

/* Returns the protocol type if URL's protocol is supported, or
   URLUNKNOWN if not.  */
uerr_t
urlproto (const char *url)
{
  int i;

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
int
has_proto (const char *url)
{
  char **s;

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
  const char *q = NULL;
  for (p = url ; *p && *p != '/'; p++)
    if (*p == '@') q = p;
  /* If a `@' was found before the first occurrence of `/', skip
     it.  */
  if (q != NULL)
    return q - url + 1;
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
    xfree (u);
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
      int ind;
      for (ind = 0; ind < ARRAY_SIZE (sup_protos); ind++)
	if (sup_protos[ind].ind == type)
	  break;
      if (ind == ARRAY_SIZE (sup_protos))
	return URLUNKNOWN;
      u->port = sup_protos[ind].port;
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
      DEBUGP (("ftp_type %c -> ", u->ftp_type));
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
  if (l > 1 && u->dir[l - 1] == '/')
    u->dir[l - 1] = '\0';
  /* Re-create the path: */
  abs_ftp = (u->proto == URLFTP && *u->dir == '/');
  /*  sprintf (u->path, "%s%s%s%s", abs_ftp ? "%2F": "/",
      abs_ftp ? (u->dir + 1) : u->dir, *u->dir ? "/" : "", u->file); */
  strcpy (u->path, abs_ftp ? "%2F" : "/");
  strcat (u->path, abs_ftp ? (u->dir + 1) : u->dir);
  strcat (u->path, *u->dir ? "/" : "");
  strcat (u->path, u->file);
  ENCODE (u->path);
  DEBUGP (("newpath: %s\n", u->path));
  /* Create the clean URL.  */
  u->url = str_url (u, 0);
  return URLOK;
}

/* Special versions of DOTP and DDOTP for parse_dir().  They work like
   DOTP and DDOTP, but they also recognize `?' as end-of-string
   delimiter.  This is needed for correct handling of query
   strings.  */

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
  const char *p, *q, *col;
  char **where;

  *user = NULL;
  *passwd = NULL;

  /* Look for the end of the protocol string.  */
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
  for (p = q = col = url; *p && *p != '/'; p++)
    {
      if (*p == ':' && !*user)
	{
	  *user = (char *)xmalloc (p - url + 1);
	  memcpy (*user, url, p - url);
	  (*user)[p - url] = '\0';
	  col = p + 1;
	}
      if (*p == '@') q = p;
    }
  /* Decide whether you have only the username or both.  */
  where = *user ? passwd : user;
  *where = (char *)xmalloc (q - col + 1);
  memcpy (*where, col, q - col);
  (*where)[q - col] = '\0';
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

/* Return the URL as fine-formed string, with a proper protocol, optional port
   number, directory and optional user/password.  If `hide' is non-zero (as it
   is when we're calling this on a URL we plan to print, but not when calling it
   to canonicalize a URL for use within the program), password will be hidden.
   The forbidden characters in the URL will be cleansed.  */
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
  host = encode_string (u->host);
  dir = encode_string (u->dir);
  file = encode_string (u->file);
  user = passwd = NULL;
  if (u->user)
    user = encode_string (u->user);
  if (u->passwd)
    {
      if (hide)
	/* Don't output the password, or someone might see it over the user's
	   shoulder (or in saved wget output).  Don't give away the number of
	   characters in the password, either, as we did in past versions of
	   this code, when we replaced the password characters with 'x's. */
	passwd = xstrdup("<password>");
      else
	passwd = encode_string (u->passwd);
    }
  if (u->proto == URLFTP && *dir == '/')
    {
      char *tmp = (char *)xmalloc (strlen (dir) + 3);
      /*sprintf (tmp, "%%2F%s", dir + 1);*/
      tmp[0] = '%';
      tmp[1] = '2';
      tmp[2] = 'F';
      strcpy (tmp + 3, dir + 1);
      xfree (dir);
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
  xfree (host);
  xfree (dir);
  xfree (file);
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

urlpos *
get_urls_file (const char *file)
{
  struct file_memory *fm;
  urlpos *head, *tail;
  const char *text, *text_end;

  /* Load the file.  */
  fm = read_file (file);
  if (!fm)
    {
      logprintf (LOG_NOTQUIET, "%s: %s\n", file, strerror (errno));
      return NULL;
    }
  DEBUGP (("Loaded %s (size %ld).\n", file, fm->length));
  head = tail = NULL;
  text = fm->content;
  text_end = fm->content + fm->length;
  while (text < text_end)
    {
      const char *line_beg = text;
      const char *line_end = memchr (text, '\n', text_end - text);
      if (!line_end)
	line_end = text_end;
      else
	++line_end;
      text = line_end;
      while (line_beg < line_end
	     && ISSPACE (*line_beg))
	++line_beg;
      while (line_end > line_beg + 1
	     && ISSPACE (*(line_end - 1)))
	--line_end;
      if (line_end > line_beg)
	{
	  urlpos *entry = (urlpos *)xmalloc (sizeof (urlpos));
	  memset (entry, 0, sizeof (*entry));
	  entry->next = NULL;
	  entry->url = strdupdelim (line_beg, line_end);
	  if (!head)
	    head = entry;
	  else
	    tail->next = entry;
	  tail = entry;
	}
    }
  read_file_free (fm);
  return head;
}

/* Free the linked list of urlpos.  */
void
free_urlpos (urlpos *l)
{
  while (l)
    {
      urlpos *next = l->next;
      xfree (l->url);
      FREE_MAYBE (l->local_name);
      xfree (l);
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
	  xfree (t);
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
  xfree (t);
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
      xfree (host);
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
  xfree (host);

  /* If there is a prefix, prepend it.  */
  if (*dirpref)
    {
      char *newdir = (char *)alloca (strlen (dirpref) + 1 + strlen (dir) + 2);
      sprintf (newdir, "%s%s%s", dirpref, *dir == '/' ? "" : "/", dir);
      dir = newdir;
    }
  dir = encode_string (dir);
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
  xfree (dir);
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
	  xfree (file);
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
  xfree (file);
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

/* Resolve the result of "linking" a base URI (BASE) to a
   link-specified URI (LINK).

   Either of the URIs may be absolute or relative, complete with the
   host name, or path only.  This tries to behave "reasonably" in all
   foreseeable cases.  It employs little specific knowledge about
   protocols or URL-specific stuff -- it just works on strings.

   The parameters LINKLENGTH is useful if LINK is not zero-terminated.
   See uri_merge for a gentler interface to this functionality.

   #### This function should handle `./' and `../' so that the evil
   path_simplify can go.  */
static char *
uri_merge_1 (const char *base, const char *link, int linklength, int no_proto)
{
  char *constr;

  if (no_proto)
    {
      const char *end = base + urlpath_length (base);

      if (*link != '/')
	{
	  /* LINK is a relative URL: we need to replace everything
	     after last slash (possibly empty) with LINK.

	     So, if BASE is "whatever/foo/bar", and LINK is "qux/xyzzy",
	     our result should be "whatever/foo/qux/xyzzy".  */
	  int need_explicit_slash = 0;
	  int span;
	  const char *start_insert;
	  const char *last_slash = find_last_char (base, end, '/');
	  if (!last_slash)
	    {
	      /* No slash found at all.  Append LINK to what we have,
		 but we'll need a slash as a separator.

		 Example: if base == "foo" and link == "qux/xyzzy", then
		 we cannot just append link to base, because we'd get
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
	  else if (last_slash && last_slash != base && *(last_slash - 1) == '/')
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

	  span = start_insert - base;
	  constr = (char *)xmalloc (span + linklength + 1);
	  if (span)
	    memcpy (constr, base, span);
	  if (need_explicit_slash)
	    constr[span - 1] = '/';
	  if (linklength)
	    memcpy (constr + span, link, linklength);
	  constr[span + linklength] = '\0';
	}
      else /* *link == `/' */
	{
	  /* LINK is an absolute path: we need to replace everything
             after (and including) the FIRST slash with LINK.

	     So, if BASE is "http://host/whatever/foo/bar", and LINK is
	     "/qux/xyzzy", our result should be
	     "http://host/qux/xyzzy".  */
	  int span;
	  const char *slash;
	  const char *start_insert = NULL; /* for gcc to shut up. */
	  const char *pos = base;
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
	     pointer to the location where LINK will be inserted.  When
	     examining the last two examples, keep in mind that LINK
	     begins with '/'. */

	  if (!slash && !seen_slash_slash)
	    /* example: "foo" */
	    /*           ^    */
	    start_insert = base;
	  else if (!slash && seen_slash_slash)
	    /* example: "http://foo" */
	    /*                     ^ */
	    start_insert = end;
	  else if (slash && !seen_slash_slash)
	    /* example: "foo/bar" */
	    /*           ^        */
	    start_insert = base;
	  else if (slash && seen_slash_slash)
	    /* example: "http://something/" */
	    /*                           ^  */
	    start_insert = slash;

	  span = start_insert - base;
	  constr = (char *)xmalloc (span + linklength + 1);
	  if (span)
	    memcpy (constr, base, span);
	  if (linklength)
	    memcpy (constr + span, link, linklength);
	  constr[span + linklength] = '\0';
	}
    }
  else /* !no_proto */
    {
      constr = strdupdelim (link, link + linklength);
    }
  return constr;
}

/* Merge BASE with LINK and return the resulting URI.  This is an
   interface to uri_merge_1 that assumes that LINK is a
   zero-terminated string.  */
char *
uri_merge (const char *base, const char *link)
{
  return uri_merge_1 (base, link, strlen (link), !has_proto (link));
}

/* Optimize URL by host, destructively replacing u->host with realhost
   (u->host).  Do this regardless of opt.simple_check.  */
void
opt_url (struct urlinfo *u)
{
  /* Find the "true" host.  */
  char *host = realhost (u->host);
  xfree (u->host);
  u->host = host;
  assert (u->dir != NULL);      /* the URL must have been parsed */
  /* Refresh the printed representation.  */
  xfree (u->url);
  u->url = str_url (u, 0);
}

/* Returns proxy host address, in accordance with PROTO.  */
char *
getproxy (uerr_t proto)
{
  char *proxy;

  if (proto == URLHTTP)
    proxy = opt.http_proxy ? opt.http_proxy : getenv ("http_proxy");
  else if (proto == URLFTP)
    proxy = opt.ftp_proxy ? opt.ftp_proxy : getenv ("ftp_proxy");
#ifdef HAVE_SSL
  else if (proto == URLHTTPS)
    proxy = opt.https_proxy ? opt.https_proxy : getenv ("https_proxy");
#endif /* HAVE_SSL */
  else
    proxy = NULL;
  if (!proxy || !*proxy)
    return NULL;
  return proxy;
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

static void write_backup_file PARAMS ((const char *, downloaded_file_t));
static void replace_attr PARAMS ((const char **, int, FILE *, const char *));

/* Change the links in an HTML document.  Accepts a structure that
   defines the positions of all the links.  */
void
convert_links (const char *file, urlpos *l)
{
  struct file_memory *fm;
  FILE               *fp;
  const char         *p;
  downloaded_file_t  downloaded_file_return;

  logprintf (LOG_VERBOSE, _("Converting %s... "), file);

  {
    /* First we do a "dry run": go through the list L and see whether
       any URL needs to be converted in the first place.  If not, just
       leave the file alone.  */
    int count = 0;
    urlpos *dry = l;
    for (dry = l; dry; dry = dry->next)
      if (dry->convert != CO_NOCONVERT)
	++count;
    if (!count)
      {
	logputs (LOG_VERBOSE, _("nothing to do.\n"));
	return;
      }
  }

  fm = read_file (file);
  if (!fm)
    {
      logprintf (LOG_NOTQUIET, _("Cannot convert links in %s: %s\n"),
		 file, strerror (errno));
      return;
    }

  downloaded_file_return = downloaded_file (CHECK_FOR_FILE, file);
  if (opt.backup_converted && downloaded_file_return)
    write_backup_file (file, downloaded_file_return);

  /* Before opening the file for writing, unlink the file.  This is
     important if the data in FM is mmaped.  In such case, nulling the
     file, which is what fopen() below does, would make us read all
     zeroes from the mmaped region.  */
  if (unlink (file) < 0 && errno != ENOENT)
    {
      logprintf (LOG_NOTQUIET, _("Unable to delete `%s': %s\n"),
		 file, strerror (errno));
      read_file_free (fm);
      return;
    }
  /* Now open the file for writing.  */
  fp = fopen (file, "wb");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, _("Cannot convert links in %s: %s\n"),
		 file, strerror (errno));
      read_file_free (fm);
      return;
    }
  /* Here we loop through all the URLs in file, replacing those of
     them that are downloaded with relative references.  */
  p = fm->content;
  for (; l; l = l->next)
    {
      char *url_start = fm->content + l->pos;

      if (l->pos >= fm->length)
	{
	  DEBUGP (("Something strange is going on.  Please investigate."));
	  break;
	}
      /* If the URL is not to be converted, skip it.  */
      if (l->convert == CO_NOCONVERT)
	{
	  DEBUGP (("Skipping %s at position %d.\n", l->url, l->pos));
	  continue;
	}

      /* Echo the file contents, up to the offending URL's opening
         quote, to the outfile.  */
      fwrite (p, 1, url_start - p, fp);
      p = url_start;
      if (l->convert == CO_CONVERT_TO_RELATIVE)
	{
	  /* Convert absolute URL to relative. */
	  char *newname = construct_relative (file, l->local_name);
	  char *quoted_newname = html_quote_string (newname);
	  replace_attr (&p, l->size, fp, quoted_newname);
	  DEBUGP (("TO_RELATIVE: %s to %s at position %d in %s.\n",
		   l->url, newname, l->pos, file));
	  xfree (newname);
	  xfree (quoted_newname);
	}
      else if (l->convert == CO_CONVERT_TO_COMPLETE)
	{
	  /* Convert the link to absolute URL. */
	  char *newlink = l->url;
	  char *quoted_newlink = html_quote_string (newlink);
	  replace_attr (&p, l->size, fp, quoted_newlink);
	  DEBUGP (("TO_COMPLETE: <something> to %s at position %d in %s.\n",
		   newlink, l->pos, file));
	  xfree (quoted_newlink);
	}
    }
  /* Output the rest of the file. */
  if (p - fm->content < fm->length)
    fwrite (p, 1, fm->length - (p - fm->content), fp);
  fclose (fp);
  read_file_free (fm);
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

static void
write_backup_file (const char *file, downloaded_file_t downloaded_file_return)
{
  /* Rather than just writing over the original .html file with the
     converted version, save the former to *.orig.  Note we only do
     this for files we've _successfully_ downloaded, so we don't
     clobber .orig files sitting around from previous invocations. */

  /* Construct the backup filename as the original name plus ".orig". */
  size_t         filename_len = strlen(file);
  char*          filename_plus_orig_suffix;
  boolean        already_wrote_backup_file = FALSE;
  slist*         converted_file_ptr;
  static slist*  converted_files = NULL;

  if (downloaded_file_return == FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED)
    {
      /* Just write "orig" over "html".  We need to do it this way
	 because when we're checking to see if we've downloaded the
	 file before (to see if we can skip downloading it), we don't
	 know if it's a text/html file.  Therefore we don't know yet
	 at that stage that -E is going to cause us to tack on
	 ".html", so we need to compare vs. the original URL plus
	 ".orig", not the original URL plus ".html.orig". */
      filename_plus_orig_suffix = alloca (filename_len + 1);
      strcpy(filename_plus_orig_suffix, file);
      strcpy((filename_plus_orig_suffix + filename_len) - 4, "orig");
    }
  else /* downloaded_file_return == FILE_DOWNLOADED_NORMALLY */
    {
      /* Append ".orig" to the name. */
      filename_plus_orig_suffix = alloca (filename_len + sizeof(".orig"));
      strcpy(filename_plus_orig_suffix, file);
      strcpy(filename_plus_orig_suffix + filename_len, ".orig");
    }

  /* We can get called twice on the same URL thanks to the
     convert_all_links() call in main().  If we write the .orig file
     each time in such a case, it'll end up containing the first-pass
     conversion, not the original file.  So, see if we've already been
     called on this file. */
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
	 so I had to make this separate list.
	 -- Dan Harkless <wget@harkless.org>

         This [adding a field to the urlpos structure] didn't work
         because convert_file() is called twice: once after all its
         sublinks have been retrieved in recursive_retrieve(), and
         once at the end of the day in convert_all_links().  The
         original linked list collected in recursive_retrieve() is
         lost after the first invocation of convert_links(), and
         convert_all_links() makes a new one (it calls get_urls_html()
         for each file it covers.)  That's why your first approach didn't
         work.  The way to make it work is perhaps to make this flag a
         field in the `urls_html' list.
	 -- Hrvoje Niksic <hniksic@arsdigita.com>
      */
      converted_file_ptr = xmalloc(sizeof(*converted_file_ptr));
      converted_file_ptr->string = xstrdup(file);  /* die on out-of-mem. */
      converted_file_ptr->next = converted_files;
      converted_files = converted_file_ptr;
    }
}

static int find_fragment PARAMS ((const char *, int, const char **,
				  const char **));

static void
replace_attr (const char **pp, int raw_size, FILE *fp, const char *new_str)
{
  const char *p = *pp;
  int quote_flag = 0;
  int size = raw_size;
  char quote_char = '\"';
  const char *frag_beg, *frag_end;

  /* Structure of our string is:
       "...old-contents..."
       <---  l->size   --->  (with quotes)
     OR:
       ...old-contents...
       <---  l->size  -->    (no quotes)   */

  if (*p == '\"' || *p == '\'')
    {
      quote_char = *p;
      quote_flag = 1;
      ++p;
      size -= 2;		/* disregard opening and closing quote */
    }
  putc (quote_char, fp);
  fputs (new_str, fp);

  /* Look for fragment identifier, if any. */
  if (find_fragment (p, size, &frag_beg, &frag_end))
    fwrite (frag_beg, 1, frag_end - frag_beg, fp);
  p += size;
  if (quote_flag)
    ++p;
  putc (quote_char, fp);
  *pp = p;
}

/* Find the first occurrence of '#' in [BEG, BEG+SIZE) that is not
   preceded by '&'.  If the character is not found, return zero.  If
   the character is found, return 1 and set BP and EP to point to the
   beginning and end of the region.

   This is used for finding the fragment indentifiers in URLs.  */

static int
find_fragment (const char *beg, int size, const char **bp, const char **ep)
{
  const char *end = beg + size;
  int saw_amp = 0;
  for (; beg < end; beg++)
    {
      switch (*beg)
	{
	case '&':
	  saw_amp = 1;
	  break;
	case '#':
	  if (!saw_amp)
	    {
	      *bp = beg;
	      *ep = end;
	      return 1;
	    }
	  /* fallthrough */
	default:
	  saw_amp = 0;
	}
    }
  return 0;
}

typedef struct _downloaded_file_list {
  char*                          file;
  downloaded_file_t              download_type;
  struct _downloaded_file_list*  next;
} downloaded_file_list;

static downloaded_file_list *downloaded_files;

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
  boolean                       found_file = FALSE;
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

void
downloaded_files_free (void)
{
  downloaded_file_list*         rover = downloaded_files;
  while (rover)
    {
      downloaded_file_list *next = rover->next;
      xfree (rover->file);
      xfree (rover);
      rover = next;
    }
}
