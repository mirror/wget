/* URL handling.
   Copyright (C) 1995, 1996, 1997, 2000, 2001, 2003, 2003
   Free Software Foundation, Inc.

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
#include "hash.h"

#ifndef errno
extern int errno;
#endif

/* Is X "."?  */
#define DOTP(x) ((*(x) == '.') && (!*(x + 1)))
/* Is X ".."?  */
#define DDOTP(x) ((*(x) == '.') && (*(x + 1) == '.') && (!*(x + 2)))

static const int NS_INADDRSZ  = 4;
static const int NS_IN6ADDRSZ = 16;
static const int NS_INT16SZ = 2;


struct scheme_data
{
  char *leading_string;
  int default_port;
  int enabled;
};

/* Supported schemes: */
static struct scheme_data supported_schemes[] =
{
  { "http://",  DEFAULT_HTTP_PORT,  1 },
#ifdef HAVE_SSL
  { "https://", DEFAULT_HTTPS_PORT, 1 },
#endif
  { "ftp://",   DEFAULT_FTP_PORT,   1 },

  /* SCHEME_INVALID */
  { NULL,       -1,                 0 }
};

/* Forward declarations: */

static char *construct_relative PARAMS ((const char *, const char *));
static int path_simplify PARAMS ((char *));



/* Support for encoding and decoding of URL strings.  We determine
   whether a character is unsafe through static table lookup.  This
   code assumes ASCII character set and 8-bit chars.  */

enum {
  /* rfc1738 reserved chars, preserved from encoding.  */
  urlchr_reserved = 1,

  /* rfc1738 unsafe chars, plus some more.  */
  urlchr_unsafe   = 2
};

#define urlchr_test(c, mask) (urlchr_table[(unsigned char)(c)] & (mask))
#define URL_RESERVED_CHAR(c) urlchr_test(c, urlchr_reserved)
#define URL_UNSAFE_CHAR(c) urlchr_test(c, urlchr_unsafe)

/* Shorthands for the table: */
#define R  urlchr_reserved
#define U  urlchr_unsafe
#define RU R|U

const static unsigned char urlchr_table[256] =
{
  U,  U,  U,  U,   U,  U,  U,  U,   /* NUL SOH STX ETX  EOT ENQ ACK BEL */
  U,  U,  U,  U,   U,  U,  U,  U,   /* BS  HT  LF  VT   FF  CR  SO  SI  */
  U,  U,  U,  U,   U,  U,  U,  U,   /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
  U,  U,  U,  U,   U,  U,  U,  U,   /* CAN EM  SUB ESC  FS  GS  RS  US  */
  U,  0,  U, RU,   0,  U,  R,  0,   /* SP  !   "   #    $   %   &   '   */
  0,  0,  0,  R,   0,  0,  0,  R,   /* (   )   *   +    ,   -   .   /   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* 0   1   2   3    4   5   6   7   */
  0,  0, RU,  R,   U,  R,  U,  R,   /* 8   9   :   ;    <   =   >   ?   */
 RU,  0,  0,  0,   0,  0,  0,  0,   /* @   A   B   C    D   E   F   G   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* H   I   J   K    L   M   N   O   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* P   Q   R   S    T   U   V   W   */
  0,  0,  0, RU,   U, RU,  U,  0,   /* X   Y   Z   [    \   ]   ^   _   */
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
#undef R
#undef U
#undef RU

/* URL-unescape the string S.

   This is done by transforming the sequences "%HH" to the character
   represented by the hexadecimal digits HH.  If % is not followed by
   two hexadecimal digits, it is inserted literally.

   The transformation is done in place.  If you need the original
   string intact, make a copy before calling this function.  */

static void
url_unescape (char *s)
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
	  if (!h[1] || !h[2] || !(ISXDIGIT (h[1]) && ISXDIGIT (h[2])))
	    goto copychar;
	  *t = X2DIGITS_TO_NUM (h[1], h[2]);
	  h += 2;
	}
    }
  *t = '\0';
}

/* The core of url_escape_* functions.  Escapes the characters that
   match the provided mask in urlchr_table.

   If ALLOW_PASSTHROUGH is non-zero, a string with no unsafe chars
   will be returned unchanged.  If ALLOW_PASSTHROUGH is zero, a
   freshly allocated string will be returned in all cases.  */

static char *
url_escape_1 (const char *s, unsigned char mask, int allow_passthrough)
{
  const char *p1;
  char *p2, *newstr;
  int newlen;
  int addition = 0;

  for (p1 = s; *p1; p1++)
    if (urlchr_test (*p1, mask))
      addition += 2;		/* Two more characters (hex digits) */

  if (!addition)
    return allow_passthrough ? (char *)s : xstrdup (s);

  newlen = (p1 - s) + addition;
  newstr = (char *)xmalloc (newlen + 1);

  p1 = s;
  p2 = newstr;
  while (*p1)
    {
      /* Quote the characters that match the test mask. */
      if (urlchr_test (*p1, mask))
	{
	  unsigned char c = *p1++;
	  *p2++ = '%';
	  *p2++ = XNUM_TO_digit (c >> 4);
	  *p2++ = XNUM_TO_digit (c & 0xf);
	}
      else
	*p2++ = *p1++;
    }
  assert (p2 - newstr == newlen);
  *p2 = '\0';

  return newstr;
}

/* URL-escape the unsafe characters (see urlchr_table) in a given
   string, returning a freshly allocated string.  */

char *
url_escape (const char *s)
{
  return url_escape_1 (s, urlchr_unsafe, 0);
}

/* URL-escape the unsafe characters (see urlchr_table) in a given
   string.  If no characters are unsafe, S is returned.  */

static char *
url_escape_allow_passthrough (const char *s)
{
  return url_escape_1 (s, urlchr_unsafe, 1);
}

enum copy_method { CM_DECODE, CM_ENCODE, CM_PASSTHROUGH };

/* Decide whether to encode, decode, or pass through the char at P.
   This used to be a macro, but it got a little too convoluted.  */
static inline enum copy_method
decide_copy_method (const char *p)
{
  if (*p == '%')
    {
      if (ISXDIGIT (*(p + 1)) && ISXDIGIT (*(p + 2)))
	{
	  /* %xx sequence: decode it, unless it would decode to an
	     unsafe or a reserved char; in that case, leave it as
	     is. */
	  char preempt = X2DIGITS_TO_NUM (*(p + 1), *(p + 2));
	  if (URL_UNSAFE_CHAR (preempt) || URL_RESERVED_CHAR (preempt))
	    return CM_PASSTHROUGH;
	  else
	    return CM_DECODE;
	}
      else
	/* Garbled %.. sequence: encode `%'. */
	return CM_ENCODE;
    }
  else if (URL_UNSAFE_CHAR (*p) && !URL_RESERVED_CHAR (*p))
    return CM_ENCODE;
  else
    return CM_PASSTHROUGH;
}

/* Translate a %-escaped (but possibly non-conformant) input string S
   into a %-escaped (and conformant) output string.  If no characters
   are encoded or decoded, return the same string S; otherwise, return
   a freshly allocated string with the new contents.

   After a URL has been run through this function, the protocols that
   use `%' as the quote character can use the resulting string as-is,
   while those that don't call url_unescape() to get to the intended
   data.  This function is also stable: after an input string is
   transformed the first time, all further transformations of the
   result yield the same result string.

   Let's discuss why this function is needed.

   Imagine Wget is to retrieve `http://abc.xyz/abc def'.  Since a raw
   space character would mess up the HTTP request, it needs to be
   quoted, like this:

       GET /abc%20def HTTP/1.0

   It appears that the unsafe chars need to be quoted, for example
   with url_escape.  But what if we're requested to download
   `abc%20def'?  url_escape transforms "%" to "%25", which would leave
   us with `abc%2520def'.  This is incorrect -- since %-escapes are
   part of URL syntax, "%20" is the correct way to denote a literal
   space on the Wget command line.  This leaves us in the conclusion
   that in that case Wget should not call url_escape, but leave the
   `%20' as is.

   And what if the requested URI is `abc%20 def'?  If we call
   url_escape, we end up with `/abc%2520%20def', which is almost
   certainly not intended.  If we don't call url_escape, we are left
   with the embedded space and cannot complete the request.  What the
   user meant was for Wget to request `/abc%20%20def', and this is
   where reencode_escapes kicks in.

   Wget used to solve this by first decoding %-quotes, and then
   encoding all the "unsafe" characters found in the resulting string.
   This was wrong because it didn't preserve certain URL special
   (reserved) characters.  For instance, URI containing "a%2B+b" (0x2b
   == '+') would get translated to "a%2B%2Bb" or "a++b" depending on
   whether we considered `+' reserved (it is).  One of these results
   is inevitable because by the second step we would lose information
   on whether the `+' was originally encoded or not.  Both results
   were wrong because in CGI parameters + means space, while %2B means
   literal plus.  reencode_escapes correctly translates the above to
   "a%2B+b", i.e. returns the original string.

   This function uses an algorithm proposed by Anon Sricharoenchai:

   1. Encode all URL_UNSAFE and the "%" that are not followed by 2
      hexdigits.

   2. Decode all "%XX" except URL_UNSAFE, URL_RESERVED (";/?:@=&") and
      "+".

   ...except that this code conflates the two steps, and decides
   whether to encode, decode, or pass through each character in turn.
   The function still uses two passes, but their logic is the same --
   the first pass exists merely for the sake of allocation.  Another
   small difference is that we include `+' to URL_RESERVED.

   Anon's test case:

   "http://abc.xyz/%20%3F%%36%31%25aa% a?a=%61+a%2Ba&b=b%26c%3Dc"
   ->
   "http://abc.xyz/%20%3F%2561%25aa%25%20a?a=a+a%2Ba&b=b%26c%3Dc"

   Simpler test cases:

   "foo bar"         -> "foo%20bar"
   "foo%20bar"       -> "foo%20bar"
   "foo %20bar"      -> "foo%20%20bar"
   "foo%%20bar"      -> "foo%25%20bar"       (0x25 == '%')
   "foo%25%20bar"    -> "foo%25%20bar"
   "foo%2%20bar"     -> "foo%252%20bar"
   "foo+bar"         -> "foo+bar"            (plus is reserved!)
   "foo%2b+bar"      -> "foo%2b+bar"  */

static char *
reencode_escapes (const char *s)
{
  const char *p1;
  char *newstr, *p2;
  int oldlen, newlen;

  int encode_count = 0;
  int decode_count = 0;

  /* First, pass through the string to see if there's anything to do,
     and to calculate the new length.  */
  for (p1 = s; *p1; p1++)
    {
      switch (decide_copy_method (p1))
	{
	case CM_ENCODE:
	  ++encode_count;
	  break;
	case CM_DECODE:
	  ++decode_count;
	  break;
	case CM_PASSTHROUGH:
	  break;
	}
    }

  if (!encode_count && !decode_count)
    /* The string is good as it is. */
    return (char *)s;		/* C const model sucks. */

  oldlen = p1 - s;
  /* Each encoding adds two characters (hex digits), while each
     decoding removes two characters.  */
  newlen = oldlen + 2 * (encode_count - decode_count);
  newstr = xmalloc (newlen + 1);

  p1 = s;
  p2 = newstr;

  while (*p1)
    {
      switch (decide_copy_method (p1))
	{
	case CM_ENCODE:
	  {
	    unsigned char c = *p1++;
	    *p2++ = '%';
	    *p2++ = XNUM_TO_DIGIT (c >> 4);
	    *p2++ = XNUM_TO_DIGIT (c & 0xf);
	  }
	  break;
	case CM_DECODE:
	  *p2++ = X2DIGITS_TO_NUM (p1[1], p1[2]);
	  p1 += 3;		/* skip %xx */
	  break;
	case CM_PASSTHROUGH:
	  *p2++ = *p1++;
	}
    }
  *p2 = '\0';
  assert (p2 - newstr == newlen);
  return newstr;
}

/* Returns the scheme type if the scheme is supported, or
   SCHEME_INVALID if not.  */
enum url_scheme
url_scheme (const char *url)
{
  int i;

  for (i = 0; supported_schemes[i].leading_string; i++)
    if (0 == strncasecmp (url, supported_schemes[i].leading_string,
			  strlen (supported_schemes[i].leading_string)))
      {
	if (supported_schemes[i].enabled)
	  return (enum url_scheme) i;
	else
	  return SCHEME_INVALID;
      }

  return SCHEME_INVALID;
}

/* Return the number of characters needed to skip the scheme part of
   the URL, e.g. `http://'.  If no scheme is found, returns 0.  */
int
url_skip_scheme (const char *url)
{
  const char *p = url;

  /* Skip the scheme name.  We allow `-' and `+' because of `whois++',
     etc. */
  while (ISALNUM (*p) || *p == '-' || *p == '+')
    ++p;
  if (*p != ':')
    return 0;
  /* Skip ':'. */
  ++p;

  /* Skip "//" if found. */
  if (*p == '/' && *(p + 1) == '/')
    p += 2;

  return p - url;
}

/* Returns 1 if the URL begins with a scheme (supported or
   unsupported), 0 otherwise.  */
int
url_has_scheme (const char *url)
{
  const char *p = url;
  while (ISALNUM (*p) || *p == '-' || *p == '+')
    ++p;
  return *p == ':';
}

int
scheme_default_port (enum url_scheme scheme)
{
  return supported_schemes[scheme].default_port;
}

void
scheme_disable (enum url_scheme scheme)
{
  supported_schemes[scheme].enabled = 0;
}

/* Skip the username and password, if present here.  The function
   should be called *not* with the complete URL, but with the part
   right after the scheme.

   If no username and password are found, return 0.  */
int
url_skip_uname (const char *url)
{
  const char *p;

  /* Look for '@' that comes before '/' or '?'. */
  p = (const char *)strpbrk (url, "/?@");
  if (!p || *p != '@')
    return 0;

  return p - url + 1;
}

static int
parse_uname (const char *str, int len, char **user, char **passwd)
{
  char *colon;

  if (len == 0)
    /* Empty user name not allowed. */
    return 0;

  colon = memchr (str, ':', len);
  if (colon == str)
    /* Empty user name again. */
    return 0;

  if (colon)
    {
      int pwlen = len - (colon + 1 - str);
      *passwd = xmalloc (pwlen + 1);
      memcpy (*passwd, colon + 1, pwlen);
      (*passwd)[pwlen] = '\0';
      len -= pwlen + 1;
    }
  else
    *passwd = NULL;

  *user = xmalloc (len + 1);
  memcpy (*user, str, len);
  (*user)[len] = '\0';

  if (*user)
    url_unescape (*user);
  if (*passwd)
    url_unescape (*passwd);

  return 1;
}

/* Used by main.c: detect URLs written using the "shorthand" URL forms
   popularized by Netscape and NcFTP.  HTTP shorthands look like this:

   www.foo.com[:port]/dir/file   -> http://www.foo.com[:port]/dir/file
   www.foo.com[:port]            -> http://www.foo.com[:port]

   FTP shorthands look like this:

   foo.bar.com:dir/file          -> ftp://foo.bar.com/dir/file
   foo.bar.com:/absdir/file      -> ftp://foo.bar.com//absdir/file

   If the URL needs not or cannot be rewritten, return NULL.  */
char *
rewrite_shorthand_url (const char *url)
{
  const char *p;

  if (url_has_scheme (url))
    return NULL;

  /* Look for a ':' or '/'.  The former signifies NcFTP syntax, the
     latter Netscape.  */
  for (p = url; *p && *p != ':' && *p != '/'; p++)
    ;

  if (p == url)
    return NULL;

  if (*p == ':')
    {
      const char *pp;
      char *res;
      /* If the characters after the colon and before the next slash
	 or end of string are all digits, it's HTTP.  */
      int digits = 0;
      for (pp = p + 1; ISDIGIT (*pp); pp++)
	++digits;
      if (digits > 0 && (*pp == '/' || *pp == '\0'))
	goto http;

      /* Prepend "ftp://" to the entire URL... */
      res = xmalloc (6 + strlen (url) + 1);
      sprintf (res, "ftp://%s", url);
      /* ...and replace ':' with '/'. */
      res[6 + (p - url)] = '/';
      return res;
    }
  else
    {
      char *res;
    http:
      /* Just prepend "http://" to what we have. */
      res = xmalloc (7 + strlen (url) + 1);
      sprintf (res, "http://%s", url);
      return res;
    }
}

static void parse_path PARAMS ((const char *, char **, char **));

/* Like strpbrk, with the exception that it returns the pointer to the
   terminating zero (end-of-string aka "eos") if no matching character
   is found.

   Although I normally balk at Gcc-specific optimizations, it probably
   makes sense here: glibc has optimizations that detect strpbrk being
   called with literal string as ACCEPT and inline the search.  That
   optimization is defeated if strpbrk is hidden within the call to
   another function.  (And no, making strpbrk_or_eos inline doesn't
   help because the check for literal accept is in the
   preprocessor.)  */

#ifdef __GNUC__

#define strpbrk_or_eos(s, accept) ({		\
  char *SOE_p = strpbrk (s, accept);		\
  if (!SOE_p)					\
    SOE_p = (char *)s + strlen (s);		\
  SOE_p;					\
})

#else  /* not __GNUC__ */

static char *
strpbrk_or_eos (const char *s, const char *accept)
{
  char *p = strpbrk (s, accept);
  if (!p)
    p = (char *)s + strlen (s);
  return p;
}
#endif

/* Turn STR into lowercase; return non-zero if a character was
   actually changed. */

static int
lowercase_str (char *str)
{
  int change = 0;
  for (; *str; str++)
    if (ISUPPER (*str))
      {
	change = 1;
	*str = TOLOWER (*str);
      }
  return change;
}

static char *parse_errors[] = {
#define PE_NO_ERROR			0
  "No error",
#define PE_UNSUPPORTED_SCHEME		1
  "Unsupported scheme",
#define PE_EMPTY_HOST			2
  "Empty host",
#define PE_BAD_PORT_NUMBER		3
  "Bad port number",
#define PE_INVALID_USER_NAME		4
  "Invalid user name",
#define PE_UNTERMINATED_IPV6_ADDRESS	5
  "Unterminated IPv6 numeric address",
#define PE_IPV6_NOT_SUPPORTED		6
  "IPv6 addresses not supported",
#define PE_INVALID_IPV6_ADDRESS		7
  "Invalid IPv6 numeric address"
};

#define SETERR(p, v) do {			\
  if (p)					\
    *(p) = (v);					\
} while (0)

#ifdef ENABLE_IPV6
/* The following two functions were adapted from glibc. */

static int
is_valid_ipv4_address (const char *str, const char *end)
{
  int saw_digit, octets;
  int val;

  saw_digit = 0;
  octets = 0;
  val = 0;

  while (str < end) {
    int ch = *str++;

    if (ch >= '0' && ch <= '9') {
      val = val * 10 + (ch - '0');

      if (val > 255)
        return 0;
      if (saw_digit == 0) {
        if (++octets > 4)
          return 0;
        saw_digit = 1;
      }
    } else if (ch == '.' && saw_digit == 1) {
      if (octets == 4)
        return 0;
      val = 0;
      saw_digit = 0;
    } else
      return 0;
  }
  if (octets < 4)
    return 0;
  
  return 1;
}

static int
is_valid_ipv6_address (const char *str, const char *end)
{
  static const char xdigits[] = "0123456789abcdef";
  const char *curtok;
  int tp;
  const char *colonp;
  int saw_xdigit;
  unsigned int val;

  tp = 0;
  colonp = NULL;

  if (str == end)
    return 0;
  
  /* Leading :: requires some special handling. */
  if (*str == ':')
    {
      ++str;
      if (str == end || *str != ':')
	return 0;
    }

  curtok = str;
  saw_xdigit = 0;
  val = 0;

  while (str < end) {
    int ch = *str++;
    const char *pch;

    /* if ch is a number, add it to val. */
    pch = strchr(xdigits, ch);
    if (pch != NULL) {
      val <<= 4;
      val |= (pch - xdigits);
      if (val > 0xffff)
	return 0;
      saw_xdigit = 1;
      continue;
    }

    /* if ch is a colon ... */
    if (ch == ':') {
      curtok = str;
      if (saw_xdigit == 0) {
	if (colonp != NULL)
	  return 0;
	colonp = str + tp;
	continue;
      } else if (str == end) {
	return 0;
      }
      if (tp > NS_IN6ADDRSZ - NS_INT16SZ)
	return 0;
      tp += NS_INT16SZ;
      saw_xdigit = 0;
      val = 0;
      continue;
    }

    /* if ch is a dot ... */
    if (ch == '.' && (tp <= NS_IN6ADDRSZ - NS_INADDRSZ) &&
	is_valid_ipv4_address(curtok, end) == 1) {
      tp += NS_INADDRSZ;
      saw_xdigit = 0;
      break;
    }
    
    return 0;
  }

  if (saw_xdigit == 1) {
    if (tp > NS_IN6ADDRSZ - NS_INT16SZ) 
      return 0;
    tp += NS_INT16SZ;
  }

  if (colonp != NULL) {
    if (tp == NS_IN6ADDRSZ) 
      return 0;
    tp = NS_IN6ADDRSZ;
  }

  if (tp != NS_IN6ADDRSZ)
    return 0;

  return 1;
}
#endif

/* Parse a URL.

   Return a new struct url if successful, NULL on error.  In case of
   error, and if ERROR is not NULL, also set *ERROR to the appropriate
   error code. */
struct url *
url_parse (const char *url, int *error)
{
  struct url *u;
  const char *p;
  int path_modified, host_modified;

  enum url_scheme scheme;

  const char *uname_b,     *uname_e;
  const char *host_b,      *host_e;
  const char *path_b,      *path_e;
  const char *params_b,    *params_e;
  const char *query_b,     *query_e;
  const char *fragment_b,  *fragment_e;

  int port;
  char *user = NULL, *passwd = NULL;

  char *url_encoded;

  scheme = url_scheme (url);
  if (scheme == SCHEME_INVALID)
    {
      SETERR (error, PE_UNSUPPORTED_SCHEME);
      return NULL;
    }

  url_encoded = reencode_escapes (url);
  p = url_encoded;

  p += strlen (supported_schemes[scheme].leading_string);
  uname_b = p;
  p += url_skip_uname (p);
  uname_e = p;

  /* scheme://user:pass@host[:port]... */
  /*                    ^              */

  /* We attempt to break down the URL into the components path,
     params, query, and fragment.  They are ordered like this:

       scheme://host[:port][/path][;params][?query][#fragment]  */

  params_b   = params_e   = NULL;
  query_b    = query_e    = NULL;
  fragment_b = fragment_e = NULL;

  host_b = p;

  if (*p == '[')
    {
      /* Handle IPv6 address inside square brackets.  Ideally we'd
	 just look for the terminating ']', but rfc2732 mandates
	 rejecting invalid IPv6 addresses.  */

      /* The address begins after '['. */
      host_b = p + 1;
      host_e = strchr (host_b, ']');

      if (!host_e)
	{
	  SETERR (error, PE_UNTERMINATED_IPV6_ADDRESS);
	  return NULL;
	}

#ifdef ENABLE_IPV6
      /* Check if the IPv6 address is valid. */
      if (!is_valid_ipv6_address(host_b, host_e))
	{
	  SETERR (error, PE_INVALID_IPV6_ADDRESS);
	  return NULL;
	}

      /* Continue parsing after the closing ']'. */
      p = host_e + 1;
#else
      SETERR (error, PE_IPV6_NOT_SUPPORTED);
      return NULL;
#endif
    }
  else
    {
      p = strpbrk_or_eos (p, ":/;?#");
      host_e = p;
    }

  if (host_b == host_e)
    {
      SETERR (error, PE_EMPTY_HOST);
      return NULL;
    }

  port = scheme_default_port (scheme);
  if (*p == ':')
    {
      const char *port_b, *port_e, *pp;

      /* scheme://host:port/tralala */
      /*              ^             */
      ++p;
      port_b = p;
      p = strpbrk_or_eos (p, "/;?#");
      port_e = p;

      if (port_b == port_e)
	{
	  /* http://host:/whatever */
	  /*             ^         */
	  SETERR (error, PE_BAD_PORT_NUMBER);
	  return NULL;
	}

      for (port = 0, pp = port_b; pp < port_e; pp++)
	{
	  if (!ISDIGIT (*pp))
	    {
	      /* http://host:12randomgarbage/blah */
	      /*               ^                  */
	      SETERR (error, PE_BAD_PORT_NUMBER);
	      return NULL;
	    }
	  
	  port = 10 * port + (*pp - '0');
	}
    }

  if (*p == '/')
    {
      ++p;
      path_b = p;
      p = strpbrk_or_eos (p, ";?#");
      path_e = p;
    }
  else
    {
      /* Path is not allowed not to exist. */
      path_b = path_e = p;
    }

  if (*p == ';')
    {
      ++p;
      params_b = p;
      p = strpbrk_or_eos (p, "?#");
      params_e = p;
    }
  if (*p == '?')
    {
      ++p;
      query_b = p;
      p = strpbrk_or_eos (p, "#");
      query_e = p;

      /* Hack that allows users to use '?' (a wildcard character) in
	 FTP URLs without it being interpreted as a query string
	 delimiter.  */
      if (scheme == SCHEME_FTP)
	{
	  query_b = query_e = NULL;
	  path_e = p;
	}
    }
  if (*p == '#')
    {
      ++p;
      fragment_b = p;
      p += strlen (p);
      fragment_e = p;
    }
  assert (*p == 0);

  if (uname_b != uname_e)
    {
      /* http://user:pass@host */
      /*        ^         ^    */
      /*     uname_b   uname_e */
      if (!parse_uname (uname_b, uname_e - uname_b - 1, &user, &passwd))
	{
	  SETERR (error, PE_INVALID_USER_NAME);
	  return NULL;
	}
    }

  u = (struct url *)xmalloc (sizeof (struct url));
  memset (u, 0, sizeof (*u));

  u->scheme = scheme;
  u->host   = strdupdelim (host_b, host_e);
  u->port   = port;
  u->user   = user;
  u->passwd = passwd;

  u->path = strdupdelim (path_b, path_e);
  path_modified = path_simplify (u->path);
  parse_path (u->path, &u->dir, &u->file);

  host_modified = lowercase_str (u->host);

  if (params_b)
    u->params = strdupdelim (params_b, params_e);
  if (query_b)
    u->query = strdupdelim (query_b, query_e);
  if (fragment_b)
    u->fragment = strdupdelim (fragment_b, fragment_e);

  if (path_modified || u->fragment || host_modified || path_b == path_e)
    {
      /* If we suspect that a transformation has rendered what
	 url_string might return different from URL_ENCODED, rebuild
	 u->url using url_string.  */
      u->url = url_string (u, 0);

      if (url_encoded != url)
	xfree ((char *) url_encoded);
    }
  else
    {
      if (url_encoded == url)
	u->url = xstrdup (url);
      else
	u->url = url_encoded;
    }
  url_encoded = NULL;

  return u;
}

const char *
url_error (int error_code)
{
  assert (error_code >= 0 && error_code < countof (parse_errors));
  return parse_errors[error_code];
}

/* Parse PATH into dir and file.  PATH is extracted from the URL and
   is URL-escaped.  The function returns unescaped DIR and FILE.  */

static void
parse_path (const char *path, char **dir, char **file)
{
  char *last_slash;

  last_slash = strrchr (path, '/');
  if (!last_slash)
    {
      *dir = xstrdup ("");
      *file = xstrdup (path);
    }
  else
    {
      *dir = strdupdelim (path, last_slash);
      *file = xstrdup (last_slash + 1);
    }
  url_unescape (*dir);
  url_unescape (*file);
}

/* Note: URL's "full path" is the path with the query string and
   params appended.  The "fragment" (#foo) is intentionally ignored,
   but that might be changed.  For example, if the original URL was
   "http://host:port/foo/bar/baz;bullshit?querystring#uselessfragment",
   the full path will be "/foo/bar/baz;bullshit?querystring".  */

/* Return the length of the full path, without the terminating
   zero.  */

static int
full_path_length (const struct url *url)
{
  int len = 0;

#define FROB(el) if (url->el) len += 1 + strlen (url->el)

  FROB (path);
  FROB (params);
  FROB (query);

#undef FROB

  return len;
}

/* Write out the full path. */

static void
full_path_write (const struct url *url, char *where)
{
#define FROB(el, chr) do {			\
  char *f_el = url->el;				\
  if (f_el) {					\
    int l = strlen (f_el);			\
    *where++ = chr;				\
    memcpy (where, f_el, l);			\
    where += l;					\
  }						\
} while (0)

  FROB (path, '/');
  FROB (params, ';');
  FROB (query, '?');

#undef FROB
}

/* Public function for getting the "full path".  E.g. if u->path is
   "foo/bar" and u->query is "param=value", full_path will be
   "/foo/bar?param=value". */

char *
url_full_path (const struct url *url)
{
  int length = full_path_length (url);
  char *full_path = (char *)xmalloc(length + 1);

  full_path_write (url, full_path);
  full_path[length] = '\0';

  return full_path;
}

/* Escape unsafe and reserved characters, except for the slash
   characters.  */

static char *
url_escape_dir (const char *dir)
{
  char *newdir = url_escape_1 (dir, urlchr_unsafe | urlchr_reserved, 1);
  char *h, *t;
  if (newdir == dir)
    return (char *)dir;

  /* Unescape slashes in NEWDIR. */

  h = newdir;			/* hare */
  t = newdir;			/* tortoise */

  for (; *h; h++, t++)
    {
      if (*h == '%' && h[1] == '2' && h[2] == 'F')
	{
	  *t = '/';
	  h += 2;
	}
      else
	*t = *h;
    }
  *t = '\0';

  return newdir;
}

/* Sync u->path and u->url with u->dir and u->file.  Called after
   u->file or u->dir have been changed, typically by the FTP code.  */

static void
sync_path (struct url *u)
{
  char *newpath, *efile, *edir;

  xfree (u->path);

  /* u->dir and u->file are not escaped.  URL-escape them before
     reassembling them into u->path.  That way, if they contain
     separators like '?' or even if u->file contains slashes, the
     path will be correctly assembled.  (u->file can contain slashes
     if the URL specifies it with %2f, or if an FTP server returns
     it.)  */
  edir = url_escape_dir (u->dir);
  efile = url_escape_1 (u->file, urlchr_unsafe | urlchr_reserved, 1);

  if (!*edir)
    newpath = xstrdup (efile);
  else
    {
      int dirlen = strlen (edir);
      int filelen = strlen (efile);

      /* Copy "DIR/FILE" to newpath. */
      char *p = newpath = xmalloc (dirlen + 1 + filelen + 1);
      memcpy (p, edir, dirlen);
      p += dirlen;
      *p++ = '/';
      memcpy (p, efile, filelen);
      p += filelen;
      *p++ = '\0';
    }

  u->path = newpath;

  if (edir != u->dir)
    xfree (edir);
  if (efile != u->file)
    xfree (efile);

  /* Regenerate u->url as well.  */
  xfree (u->url);
  u->url = url_string (u, 0);
}

/* Mutators.  Code in ftp.c insists on changing u->dir and u->file.
   This way we can sync u->path and u->url when they get changed.  */

void
url_set_dir (struct url *url, const char *newdir)
{
  xfree (url->dir);
  url->dir = xstrdup (newdir);
  sync_path (url);
}

void
url_set_file (struct url *url, const char *newfile)
{
  xfree (url->file);
  url->file = xstrdup (newfile);
  sync_path (url);
}

void
url_free (struct url *url)
{
  xfree (url->host);
  xfree (url->path);
  xfree (url->url);

  FREE_MAYBE (url->params);
  FREE_MAYBE (url->query);
  FREE_MAYBE (url->fragment);
  FREE_MAYBE (url->user);
  FREE_MAYBE (url->passwd);

  xfree (url->dir);
  xfree (url->file);

  xfree (url);
}

struct urlpos *
get_urls_file (const char *file)
{
  struct file_memory *fm;
  struct urlpos *head, *tail;
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

      /* Strip whitespace from the beginning and end of line. */
      while (line_beg < line_end && ISSPACE (*line_beg))
	++line_beg;
      while (line_end > line_beg && ISSPACE (*(line_end - 1)))
	--line_end;

      if (line_end > line_beg)
	{
	  /* URL is in the [line_beg, line_end) region. */

	  int up_error_code;
	  char *url_text;
	  struct urlpos *entry;
	  struct url *url;

	  /* We must copy the URL to a zero-terminated string, and we
	     can't use alloca because we're in a loop.  *sigh*.  */
	  url_text = strdupdelim (line_beg, line_end);

	  if (opt.base_href)
	    {
	      /* Merge opt.base_href with URL. */
	      char *merged = uri_merge (opt.base_href, url_text);
	      xfree (url_text);
	      url_text = merged;
	    }

	  url = url_parse (url_text, &up_error_code);
	  if (!url)
	    {
	      logprintf (LOG_NOTQUIET, "%s: Invalid URL %s: %s\n",
			 file, url_text, url_error (up_error_code));
	      xfree (url_text);
	      continue;
	    }
	  xfree (url_text);

	  entry = (struct urlpos *)xmalloc (sizeof (struct urlpos));
	  memset (entry, 0, sizeof (*entry));
	  entry->next = NULL;
	  entry->url = url;

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
free_urlpos (struct urlpos *l)
{
  while (l)
    {
      struct urlpos *next = l->next;
      if (l->url)
	url_free (l->url);
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
  for (; *p != '/' && p != path; p--)
    ;

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

/* Functions for constructing the file name out of URL components.  */

/* A growable string structure, used by url_file_name and friends.
   This should perhaps be moved to utils.c.

   The idea is to have a convenient and efficient way to construct a
   string by having various functions append data to it.  Instead of
   passing the obligatory BASEVAR, SIZEVAR and TAILPOS to all the
   functions in questions, we pass the pointer to this struct.  */

struct growable {
  char *base;
  int size;
  int tail;
};

/* Ensure that the string can accept APPEND_COUNT more characters past
   the current TAIL position.  If necessary, this will grow the string
   and update its allocated size.  If the string is already large
   enough to take TAIL+APPEND_COUNT characters, this does nothing.  */
#define GROW(g, append_size) do {					\
  struct growable *G_ = g;						\
  DO_REALLOC (G_->base, G_->size, G_->tail + append_size, char);	\
} while (0)

/* Return the tail position of the string. */
#define TAIL(r) ((r)->base + (r)->tail)

/* Move the tail position by APPEND_COUNT characters. */
#define TAIL_INCR(r, append_count) ((r)->tail += append_count)

/* Append the string STR to DEST.  NOTICE: the string in DEST is not
   terminated.  */

static void
append_string (const char *str, struct growable *dest)
{
  int l = strlen (str);
  GROW (dest, l);
  memcpy (TAIL (dest), str, l);
  TAIL_INCR (dest, l);
}

/* Append CH to DEST.  For example, append_char (0, DEST)
   zero-terminates DEST.  */

static void
append_char (char ch, struct growable *dest)
{
  GROW (dest, 1);
  *TAIL (dest) = ch;
  TAIL_INCR (dest, 1);
}

enum {
  filechr_not_unix    = 1,	/* unusable on Unix, / and \0 */
  filechr_not_windows = 2,	/* unusable on Windows, one of \|/<>?:*" */
  filechr_control     = 4,	/* a control character, e.g. 0-31 */
};

#define FILE_CHAR_TEST(c, mask) (filechr_table[(unsigned char)(c)] & (mask))

/* Shorthands for the table: */
#define U filechr_not_unix
#define W filechr_not_windows
#define C filechr_control

#define UW U|W
#define UWC U|W|C

/* Table of characters unsafe under various conditions (see above).

   Arguably we could also claim `%' to be unsafe, since we use it as
   the escape character.  If we ever want to be able to reliably
   translate file name back to URL, this would become important
   crucial.  Right now, it's better to be minimal in escaping.  */

const static unsigned char filechr_table[256] =
{
UWC,  C,  C,  C,   C,  C,  C,  C,   /* NUL SOH STX ETX  EOT ENQ ACK BEL */
  C,  C,  C,  C,   C,  C,  C,  C,   /* BS  HT  LF  VT   FF  CR  SO  SI  */
  C,  C,  C,  C,   C,  C,  C,  C,   /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
  C,  C,  C,  C,   C,  C,  C,  C,   /* CAN EM  SUB ESC  FS  GS  RS  US  */
  0,  0,  W,  0,   0,  0,  0,  0,   /* SP  !   "   #    $   %   &   '   */
  0,  0,  W,  0,   0,  0,  0, UW,   /* (   )   *   +    ,   -   .   /   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* 0   1   2   3    4   5   6   7   */
  0,  0,  W,  0,   W,  0,  W,  W,   /* 8   9   :   ;    <   =   >   ?   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* @   A   B   C    D   E   F   G   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* H   I   J   K    L   M   N   O   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* P   Q   R   S    T   U   V   W   */
  0,  0,  0,  0,   W,  0,  0,  0,   /* X   Y   Z   [    \   ]   ^   _   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* `   a   b   c    d   e   f   g   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* h   i   j   k    l   m   n   o   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* p   q   r   s    t   u   v   w   */
  0,  0,  0,  0,   0,  0,  0,  0,   /* x   y   z   {    |   }   ~   DEL */

  C, C, C, C,  C, C, C, C,  C, C, C, C,  C, C, C, C, /* 128-143 */
  C, C, C, C,  C, C, C, C,  C, C, C, C,  C, C, C, C, /* 144-159 */
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,

  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
};
#undef U
#undef W
#undef C
#undef UW
#undef UWC

/* FN_PORT_SEP is the separator between host and port in file names
   for non-standard port numbers.  On Unix this is normally ':', as in
   "www.xemacs.org:4001/index.html".  Under Windows, we set it to +
   because Windows can't handle ':' in file names.  */
#define FN_PORT_SEP  (opt.restrict_files_os != restrict_windows ? ':' : '+')

/* FN_QUERY_SEP is the separator between the file name and the URL
   query, normally '?'.  Since Windows cannot handle '?' as part of
   file name, we use '@' instead there.  */
#define FN_QUERY_SEP (opt.restrict_files_os != restrict_windows ? '?' : '@')

/* Quote path element, characters in [b, e), as file name, and append
   the quoted string to DEST.  Each character is quoted as per
   file_unsafe_char and the corresponding table.  */

static void
append_uri_pathel (const char *b, const char *e, struct growable *dest)
{
  char *pathel;
  int pathlen;

  const char *p;
  int quoted, outlen;

  int mask;
  if (opt.restrict_files_os == restrict_unix)
    mask = filechr_not_unix;
  else
    mask = filechr_not_windows;
  if (opt.restrict_files_ctrl)
    mask |= filechr_control;

  /* Copy [b, e) to PATHEL and URL-unescape it. */
  BOUNDED_TO_ALLOCA (b, e, pathel);
  url_unescape (pathel);
  pathlen = strlen (pathel);

  /* Go through PATHEL and check how many characters we'll need to
     add for file quoting. */
  quoted = 0;
  for (p = pathel; *p; p++)
    if (FILE_CHAR_TEST (*p, mask))
      ++quoted;

  /* p - pathel is the string length.  Each quoted char means two
     additional characters in the string, hence 2*quoted.  */
  outlen = (p - pathel) + (2 * quoted);
  GROW (dest, outlen);

  if (!quoted)
    {
      /* If there's nothing to quote, we don't need to go through the
	 string the second time.  */
      memcpy (TAIL (dest), pathel, outlen);
    }
  else
    {
      char *q = TAIL (dest);
      for (p = pathel; *p; p++)
	{
	  if (!FILE_CHAR_TEST (*p, mask))
	    *q++ = *p;
	  else
	    {
	      unsigned char ch = *p;
	      *q++ = '%';
	      *q++ = XNUM_TO_DIGIT (ch >> 4);
	      *q++ = XNUM_TO_DIGIT (ch & 0xf);
	    }
	}
      assert (q - TAIL (dest) == outlen);
    }
  TAIL_INCR (dest, outlen);
}

/* Append to DEST the directory structure that corresponds the
   directory part of URL's path.  For example, if the URL is
   http://server/dir1/dir2/file, this appends "/dir1/dir2".

   Each path element ("dir1" and "dir2" in the above example) is
   examined, url-unescaped, and re-escaped as file name element.

   Additionally, it cuts as many directories from the path as
   specified by opt.cut_dirs.  For example, if opt.cut_dirs is 1, it
   will produce "bar" for the above example.  For 2 or more, it will
   produce "".

   Each component of the path is quoted for use as file name.  */

static void
append_dir_structure (const struct url *u, struct growable *dest)
{
  char *pathel, *next;
  int cut = opt.cut_dirs;

  /* Go through the path components, de-URL-quote them, and quote them
     (if necessary) as file names.  */

  pathel = u->path;
  for (; (next = strchr (pathel, '/')) != NULL; pathel = next + 1)
    {
      if (cut-- > 0)
	continue;
      if (pathel == next)
	/* Ignore empty pathels.  path_simplify should remove
	   occurrences of "//" from the path, but it has special cases
	   for starting / which generates an empty pathel here.  */
	continue;

      if (dest->tail)
	append_char ('/', dest);
      append_uri_pathel (pathel, next, dest);
    }
}

/* Return a unique file name that matches the given URL as good as
   possible.  Does not create directories on the file system.  */

char *
url_file_name (const struct url *u)
{
  struct growable fnres;

  char *u_file, *u_query;
  char *fname, *unique;

  fnres.base = NULL;
  fnres.size = 0;
  fnres.tail = 0;

  /* Start with the directory prefix, if specified. */
  if (!DOTP (opt.dir_prefix))
    append_string (opt.dir_prefix, &fnres);

  /* If "dirstruct" is turned on (typically the case with -r), add
     the host and port (unless those have been turned off) and
     directory structure.  */
  if (opt.dirstruct)
    {
      if (opt.add_hostdir)
	{
	  if (fnres.tail)
	    append_char ('/', &fnres);
	  append_string (u->host, &fnres);
	  if (u->port != scheme_default_port (u->scheme))
	    {
	      char portstr[24];
	      number_to_string (portstr, u->port);
	      append_char (FN_PORT_SEP, &fnres);
	      append_string (portstr, &fnres);
	    }
	}

      append_dir_structure (u, &fnres);
    }

  /* Add the file name. */
  if (fnres.tail)
    append_char ('/', &fnres);
  u_file = *u->file ? u->file : "index.html";
  append_uri_pathel (u_file, u_file + strlen (u_file), &fnres);

  /* Append "?query" to the file name. */
  u_query = u->query && *u->query ? u->query : NULL;
  if (u_query)
    {
      append_char (FN_QUERY_SEP, &fnres);
      append_uri_pathel (u_query, u_query + strlen (u_query), &fnres);
    }

  /* Zero-terminate the file name. */
  append_char ('\0', &fnres);

  fname = fnres.base;

  /* Check the cases in which the unique extensions are not used:
     1) Clobbering is turned off (-nc).
     2) Retrieval with regetting.
     3) Timestamping is used.
     4) Hierarchy is built.

     The exception is the case when file does exist and is a
     directory (see `mkalldirs' for explanation).  */

  if ((opt.noclobber || opt.always_rest || opt.timestamping || opt.dirstruct)
      && !(file_exists_p (fname) && !file_non_directory_p (fname)))
    return fname;

  unique = unique_name (fname, 1);
  if (unique != fname)
    xfree (fname);
  return unique;
}

/* Return the length of URL's path.  Path is considered to be
   terminated by one of '?', ';', '#', or by the end of the
   string.  */
static int
path_length (const char *url)
{
  const char *q = strpbrk_or_eos (url, "?;#");
  return q - url;
}

/* Find the last occurrence of character C in the range [b, e), or
   NULL, if none are present.  This is equivalent to strrchr(b, c),
   except that it accepts an END argument instead of requiring the
   string to be zero-terminated.  Why is there no memrchr()?  */
static const char *
find_last_char (const char *b, const char *e, char c)
{
  for (; e > b; e--)
    if (*e == c)
      return e;
  return NULL;
}

/* Resolve "." and ".." elements of PATH by destructively modifying
   PATH.  "." is resolved by removing that path element, and ".." is
   resolved by removing the preceding path element.  Leading and
   trailing slashes are preserved.

   Return non-zero if any changes have been made.

   For example, "a/b/c/./../d/.." will yield "a/b/".  More exhaustive
   test examples are provided below.  If you change anything in this
   function, run test_path_simplify to make sure you haven't broken a
   test case.

   A previous version of this function was based on path_simplify()
   from GNU Bash, but it has been rewritten for Wget 1.8.1.  */

static int
path_simplify (char *path)
{
  int change = 0;
  char *p, *end;

  if (path[0] == '/')
    ++path;			/* preserve the leading '/'. */

  p = path;
  end = p + strlen (p) + 1;	/* position past the terminating zero. */

  while (1)
    {
    again:
      /* P should point to the beginning of a path element. */

      if (*p == '.' && (*(p + 1) == '/' || *(p + 1) == '\0'))
	{
	  /* Handle "./foo" by moving "foo" two characters to the
	     left. */
	  if (*(p + 1) == '/')
	    {
	      change = 1;
	      memmove (p, p + 2, end - p);
	      end -= 2;
	      goto again;
	    }
	  else
	    {
	      change = 1;
	      *p = '\0';
	      break;
	    }
	}
      else if (*p == '.' && *(p + 1) == '.'
	       && (*(p + 2) == '/' || *(p + 2) == '\0'))
	{
	  /* Handle "../foo" by moving "foo" one path element to the
	     left.  */
	  char *b = p;		/* not p-1 because P can equal PATH */

	  /* Backtrack by one path element, but not past the beginning
	     of PATH. */

	  /* foo/bar/../baz */
	  /*         ^ p    */
	  /*     ^ b        */

	  if (b > path)
	    {
	      /* Move backwards until B hits the beginning of the
		 previous path element or the beginning of path. */
	      for (--b; b > path && *(b - 1) != '/'; b--)
		;
	    }

	  change = 1;
	  if (*(p + 2) == '/')
	    {
	      memmove (b, p + 3, end - (p + 3));
	      end -= (p + 3) - b;
	      p = b;
	    }
	  else
	    {
	      *b = '\0';
	      break;
	    }

	  goto again;
	}
      else if (*p == '/')
	{
	  /* Remove empty path elements.  Not mandated by rfc1808 et
	     al, but it seems like a good idea to get rid of them.
	     Supporting them properly is hard (in which directory do
	     you save http://x.com///y.html?) and they don't seem to
	     bring much gain.  */
	  char *q = p;
	  while (*q == '/')
	    ++q;
	  change = 1;
	  if (*q == '\0')
	    {
	      *p = '\0';
	      break;
	    }
	  memmove (p, q, end - q);
	  end -= q - p;
	  goto again;
	}

      /* Skip to the next path element. */
      while (*p && *p != '/')
	++p;
      if (*p == '\0')
	break;

      /* Make sure P points to the beginning of the next path element,
	 which is location after the slash. */
      ++p;
    }

  return change;
}

/* Resolve the result of "linking" a base URI (BASE) to a
   link-specified URI (LINK).

   Either of the URIs may be absolute or relative, complete with the
   host name, or path only.  This tries to behave "reasonably" in all
   foreseeable cases.  It employs little specific knowledge about
   schemes or URL-specific stuff -- it just works on strings.

   The parameters LINKLENGTH is useful if LINK is not zero-terminated.
   See uri_merge for a gentler interface to this functionality.

   Perhaps this function should call path_simplify so that the callers
   don't have to call url_parse unconditionally.  */
static char *
uri_merge_1 (const char *base, const char *link, int linklength, int no_scheme)
{
  char *constr;

  if (no_scheme)
    {
      const char *end = base + path_length (base);

      if (!*link)
	{
	  /* Empty LINK points back to BASE, query string and all. */
	  constr = xstrdup (base);
	}
      else if (*link == '?')
	{
	  /* LINK points to the same location, but changes the query
	     string.  Examples: */
	  /* uri_merge("path",         "?new") -> "path?new"     */
	  /* uri_merge("path?foo",     "?new") -> "path?new"     */
	  /* uri_merge("path?foo#bar", "?new") -> "path?new"     */
	  /* uri_merge("path#foo",     "?new") -> "path?new"     */
	  int baselength = end - base;
	  constr = xmalloc (baselength + linklength + 1);
	  memcpy (constr, base, baselength);
	  memcpy (constr + baselength, link, linklength);
	  constr[baselength + linklength] = '\0';
	}
      else if (*link == '#')
	{
	  /* uri_merge("path",         "#new") -> "path#new"     */
	  /* uri_merge("path#foo",     "#new") -> "path#new"     */
	  /* uri_merge("path?foo",     "#new") -> "path?foo#new" */
	  /* uri_merge("path?foo#bar", "#new") -> "path?foo#new" */
	  int baselength;
	  const char *end1 = strchr (base, '#');
	  if (!end1)
	    end1 = base + strlen (base);
	  baselength = end1 - base;
	  constr = xmalloc (baselength + linklength + 1);
	  memcpy (constr, base, baselength);
	  memcpy (constr + baselength, link, linklength);
	  constr[baselength + linklength] = '\0';
	}
      else if (linklength > 1 && *link == '/' && *(link + 1) == '/')
	{
	  /* LINK begins with "//" and so is a net path: we need to
	     replace everything after (and including) the double slash
	     with LINK. */

	  /* uri_merge("foo", "//new/bar")            -> "//new/bar"      */
	  /* uri_merge("//old/foo", "//new/bar")      -> "//new/bar"      */
	  /* uri_merge("http://old/foo", "//new/bar") -> "http://new/bar" */

	  int span;
	  const char *slash;
	  const char *start_insert;

	  /* Look for first slash. */
	  slash = memchr (base, '/', end - base);
	  /* If found slash and it is a double slash, then replace
	     from this point, else default to replacing from the
	     beginning.  */
	  if (slash && *(slash + 1) == '/')
	    start_insert = slash;
	  else
	    start_insert = base;

	  span = start_insert - base;
	  constr = (char *)xmalloc (span + linklength + 1);
	  if (span)
	    memcpy (constr, base, span);
	  memcpy (constr + span, link, linklength);
	  constr[span + linklength] = '\0';
	}
      else if (*link == '/')
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
      else
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
    }
  else /* !no_scheme */
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
  return uri_merge_1 (base, link, strlen (link), !url_has_scheme (link));
}

#define APPEND(p, s) do {			\
  int len = strlen (s);				\
  memcpy (p, s, len);				\
  p += len;					\
} while (0)

/* Use this instead of password when the actual password is supposed
   to be hidden.  We intentionally use a generic string without giving
   away the number of characters in the password, like previous
   versions did.  */
#define HIDDEN_PASSWORD "*password*"

/* Recreate the URL string from the data in URL.

   If HIDE is non-zero (as it is when we're calling this on a URL we
   plan to print, but not when calling it to canonicalize a URL for
   use within the program), password will be hidden.  Unsafe
   characters in the URL will be quoted.  */

char *
url_string (const struct url *url, int hide_password)
{
  int size;
  char *result, *p;
  char *quoted_user = NULL, *quoted_passwd = NULL;

  int scheme_port  = supported_schemes[url->scheme].default_port;
  char *scheme_str = supported_schemes[url->scheme].leading_string;
  int fplen = full_path_length (url);

  int brackets_around_host = 0;

  assert (scheme_str != NULL);

  /* Make sure the user name and password are quoted. */
  if (url->user)
    {
      quoted_user = url_escape_allow_passthrough (url->user);
      if (url->passwd)
	{
	  if (hide_password)
	    quoted_passwd = HIDDEN_PASSWORD;
	  else
	    quoted_passwd = url_escape_allow_passthrough (url->passwd);
	}
    }

  if (strchr (url->host, ':'))
    brackets_around_host = 1;

  size = (strlen (scheme_str)
	  + strlen (url->host)
	  + (brackets_around_host ? 2 : 0)
	  + fplen
	  + 1);
  if (url->port != scheme_port)
    size += 1 + numdigit (url->port);
  if (quoted_user)
    {
      size += 1 + strlen (quoted_user);
      if (quoted_passwd)
	size += 1 + strlen (quoted_passwd);
    }

  p = result = xmalloc (size);

  APPEND (p, scheme_str);
  if (quoted_user)
    {
      APPEND (p, quoted_user);
      if (quoted_passwd)
	{
	  *p++ = ':';
	  APPEND (p, quoted_passwd);
	}
      *p++ = '@';
    }

  if (brackets_around_host)
    *p++ = '[';
  APPEND (p, url->host);
  if (brackets_around_host)
    *p++ = ']';
  if (url->port != scheme_port)
    {
      *p++ = ':';
      p = number_to_string (p, url->port);
    }

  full_path_write (url, p);
  p += fplen;
  *p++ = '\0';

  assert (p - result == size);

  if (quoted_user && quoted_user != url->user)
    xfree (quoted_user);
  if (quoted_passwd && !hide_password
      && quoted_passwd != url->passwd)
    xfree (quoted_passwd);

  return result;
}

/* Return the URL of the proxy appropriate for url U.  */
char *
getproxy (struct url *u)
{
  char *proxy = NULL;
  char *rewritten_url;
  static char rewritten_storage[1024];

  if (!opt.use_proxy)
    return NULL;
  if (!no_proxy_match (u->host, (const char **)opt.no_proxy))
    return NULL;

  switch (u->scheme)
    {
    case SCHEME_HTTP:
      proxy = opt.http_proxy ? opt.http_proxy : getenv ("http_proxy");
      break;
#ifdef HAVE_SSL
    case SCHEME_HTTPS:
      proxy = opt.https_proxy ? opt.https_proxy : getenv ("https_proxy");
      break;
#endif
    case SCHEME_FTP:
      proxy = opt.ftp_proxy ? opt.ftp_proxy : getenv ("ftp_proxy");
      break;
    case SCHEME_INVALID:
      break;
    }
  if (!proxy || !*proxy)
    return NULL;

  /* Handle shorthands.  `rewritten_storage' is a kludge to allow
     getproxy() to return static storage. */
  rewritten_url = rewrite_shorthand_url (proxy);
  if (rewritten_url)
    {
      strncpy (rewritten_storage, rewritten_url, sizeof(rewritten_storage));
      rewritten_storage[sizeof (rewritten_storage) - 1] = '\0';
      proxy = rewritten_storage;
    }

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

/* Support for converting links for local viewing in downloaded HTML
   files.  This should be moved to another file, because it has
   nothing to do with processing URLs.  */

static void write_backup_file PARAMS ((const char *, downloaded_file_t));
static const char *replace_attr PARAMS ((const char *, int, FILE *,
					 const char *));
static const char *replace_attr_refresh_hack PARAMS ((const char *, int, FILE *,
						      const char *, int));
static char *local_quote_string PARAMS ((const char *));

/* Change the links in one HTML file.  LINKS is a list of links in the
   document, along with their positions and the desired direction of
   the conversion.  */
void
convert_links (const char *file, struct urlpos *links)
{
  struct file_memory *fm;
  FILE *fp;
  const char *p;
  downloaded_file_t downloaded_file_return;

  struct urlpos *link;
  int to_url_count = 0, to_file_count = 0;

  logprintf (LOG_VERBOSE, _("Converting %s... "), file);

  {
    /* First we do a "dry run": go through the list L and see whether
       any URL needs to be converted in the first place.  If not, just
       leave the file alone.  */
    int dry_count = 0;
    struct urlpos *dry = links;
    for (dry = links; dry; dry = dry->next)
      if (dry->convert != CO_NOCONVERT)
	++dry_count;
    if (!dry_count)
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
  for (link = links; link; link = link->next)
    {
      char *url_start = fm->content + link->pos;

      if (link->pos >= fm->length)
	{
	  DEBUGP (("Something strange is going on.  Please investigate."));
	  break;
	}
      /* If the URL is not to be converted, skip it.  */
      if (link->convert == CO_NOCONVERT)
	{
	  DEBUGP (("Skipping %s at position %d.\n", link->url->url, link->pos));
	  continue;
	}

      /* Echo the file contents, up to the offending URL's opening
         quote, to the outfile.  */
      fwrite (p, 1, url_start - p, fp);
      p = url_start;

      switch (link->convert)
	{
	case CO_CONVERT_TO_RELATIVE:
	  /* Convert absolute URL to relative. */
	  {
	    char *newname = construct_relative (file, link->local_name);
	    char *quoted_newname = local_quote_string (newname);

	    if (!link->link_refresh_p)
	      p = replace_attr (p, link->size, fp, quoted_newname);
	    else
	      p = replace_attr_refresh_hack (p, link->size, fp, quoted_newname,
					     link->refresh_timeout);

	    DEBUGP (("TO_RELATIVE: %s to %s at position %d in %s.\n",
		     link->url->url, newname, link->pos, file));
	    xfree (newname);
	    xfree (quoted_newname);
	    ++to_file_count;
	    break;
	  }
	case CO_CONVERT_TO_COMPLETE:
	  /* Convert the link to absolute URL. */
	  {
	    char *newlink = link->url->url;
	    char *quoted_newlink = html_quote_string (newlink);

	    if (!link->link_refresh_p)
	      p = replace_attr (p, link->size, fp, quoted_newlink);
	    else
	      p = replace_attr_refresh_hack (p, link->size, fp, quoted_newlink,
					     link->refresh_timeout);

	    DEBUGP (("TO_COMPLETE: <something> to %s at position %d in %s.\n",
		     newlink, link->pos, file));
	    xfree (quoted_newlink);
	    ++to_url_count;
	    break;
	  }
	case CO_NULLIFY_BASE:
	  /* Change the base href to "". */
	  p = replace_attr (p, link->size, fp, "");
	  break;
	case CO_NOCONVERT:
	  abort ();
	  break;
	}
    }

  /* Output the rest of the file. */
  if (p - fm->content < fm->length)
    fwrite (p, 1, fm->length - (p - fm->content), fp);
  fclose (fp);
  read_file_free (fm);

  logprintf (LOG_VERBOSE, "%d-%d\n", to_file_count, to_url_count);
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
         because convert_file() is called from convert_all_links at
         the end of the retrieval with a freshly built new urlpos
         list.
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

/* Replace an attribute's original text with NEW_TEXT. */

static const char *
replace_attr (const char *p, int size, FILE *fp, const char *new_text)
{
  int quote_flag = 0;
  char quote_char = '\"';	/* use "..." for quoting, unless the
				   original value is quoted, in which
				   case reuse its quoting char. */
  const char *frag_beg, *frag_end;

  /* Structure of our string is:
       "...old-contents..."
       <---    size    --->  (with quotes)
     OR:
       ...old-contents...
       <---    size   -->    (no quotes)   */

  if (*p == '\"' || *p == '\'')
    {
      quote_char = *p;
      quote_flag = 1;
      ++p;
      size -= 2;		/* disregard opening and closing quote */
    }
  putc (quote_char, fp);
  fputs (new_text, fp);

  /* Look for fragment identifier, if any. */
  if (find_fragment (p, size, &frag_beg, &frag_end))
    fwrite (frag_beg, 1, frag_end - frag_beg, fp);
  p += size;
  if (quote_flag)
    ++p;
  putc (quote_char, fp);

  return p;
}

/* The same as REPLACE_ATTR, but used when replacing
   <meta http-equiv=refresh content="new_text"> because we need to
   append "timeout_value; URL=" before the next_text.  */

static const char *
replace_attr_refresh_hack (const char *p, int size, FILE *fp,
			   const char *new_text, int timeout)
{
  /* "0; URL=..." */
  char *new_with_timeout = (char *)alloca (numdigit (timeout)
					   + 6 /* "; URL=" */
					   + strlen (new_text)
					   + 1);
  sprintf (new_with_timeout, "%d; URL=%s", timeout, new_text);

  return replace_attr (p, size, fp, new_with_timeout);
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

/* Quote FILE for use as local reference to an HTML file.

   We quote ? as %3F to avoid passing part of the file name as the
   parameter when browsing the converted file through HTTP.  However,
   it is safe to do this only when `--html-extension' is turned on.
   This is because converting "index.html?foo=bar" to
   "index.html%3Ffoo=bar" would break local browsing, as the latter
   isn't even recognized as an HTML file!  However, converting
   "index.html?foo=bar.html" to "index.html%3Ffoo=bar.html" should be
   safe for both local and HTTP-served browsing.  */

static char *
local_quote_string (const char *file)
{
  const char *file_sans_qmark;
  int qm;

  if (!opt.html_extension)
    return html_quote_string (file);

  qm = count_char (file, '?');

  if (qm)
    {
      const char *from = file;
      char *to, *newname;

      /* qm * 2 because we replace each question mark with "%3F",
	 i.e. replace one char with three, hence two more.  */
      int fsqlen = strlen (file) + qm * 2;

      to = newname = (char *)alloca (fsqlen + 1);
      for (; *from; from++)
	{
	  if (*from != '?')
	    *to++ = *from;
	  else
	    {
	      *to++ = '%';
	      *to++ = '3';
	      *to++ = 'F';
	    }
	}
      assert (to - newname == fsqlen);
      *to = '\0';

      file_sans_qmark = newname;
    }
  else
    file_sans_qmark = file;

  return html_quote_string (file_sans_qmark);
}

/* We're storing "modes" of type downloaded_file_t in the hash table.
   However, our hash tables only accept pointers for keys and values.
   So when we need a pointer, we use the address of a
   downloaded_file_t variable of static storage.  */
   
static downloaded_file_t *
downloaded_mode_to_ptr (downloaded_file_t mode)
{
  static downloaded_file_t
    v1 = FILE_NOT_ALREADY_DOWNLOADED,
    v2 = FILE_DOWNLOADED_NORMALLY,
    v3 = FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED,
    v4 = CHECK_FOR_FILE;

  switch (mode)
    {
    case FILE_NOT_ALREADY_DOWNLOADED:
      return &v1;
    case FILE_DOWNLOADED_NORMALLY:
      return &v2;
    case FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED:
      return &v3;
    case CHECK_FOR_FILE:
      return &v4;
    }
  return NULL;
}

/* This should really be merged with dl_file_url_map and
   downloaded_html_files in recur.c.  This was originally a list, but
   I changed it to a hash table beause it was actually taking a lot of
   time to find things in it.  */

static struct hash_table *downloaded_files_hash;

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
downloaded_file (downloaded_file_t mode, const char *file)
{
  downloaded_file_t *ptr;

  if (mode == CHECK_FOR_FILE)
    {
      if (!downloaded_files_hash)
	return FILE_NOT_ALREADY_DOWNLOADED;
      ptr = hash_table_get (downloaded_files_hash, file);
      if (!ptr)
	return FILE_NOT_ALREADY_DOWNLOADED;
      return *ptr;
    }

  if (!downloaded_files_hash)
    downloaded_files_hash = make_string_hash_table (0);

  ptr = hash_table_get (downloaded_files_hash, file);
  if (ptr)
    return *ptr;

  ptr = downloaded_mode_to_ptr (mode);
  hash_table_put (downloaded_files_hash, xstrdup (file), &ptr);

  return FILE_NOT_ALREADY_DOWNLOADED;
}

static int
df_free_mapper (void *key, void *value, void *ignored)
{
  xfree (key);
  return 0;
}

void
downloaded_files_free (void)
{
  if (downloaded_files_hash)
    {
      hash_table_map (downloaded_files_hash, df_free_mapper, NULL);
      hash_table_destroy (downloaded_files_hash);
      downloaded_files_hash = NULL;
    }
}

/* Return non-zero if scheme a is similar to scheme b.
 
   Schemes are similar if they are equal.  If SSL is supported, schemes
   are also similar if one is http (SCHEME_HTTP) and the other is https
   (SCHEME_HTTPS).  */
int
schemes_are_similar_p (enum url_scheme a, enum url_scheme b)
{
  if (a == b)
    return 1;
#ifdef HAVE_SSL
  if ((a == SCHEME_HTTP && b == SCHEME_HTTPS)
      || (a == SCHEME_HTTPS && b == SCHEME_HTTP))
    return 1;
#endif
  return 0;
}

#if 0
/* Debugging and testing support for path_simplify. */

/* Debug: run path_simplify on PATH and return the result in a new
   string.  Useful for calling from the debugger.  */
static char *
ps (char *path)
{
  char *copy = xstrdup (path);
  path_simplify (copy);
  return copy;
}

static void
run_test (char *test, char *expected_result, int expected_change)
{
  char *test_copy = xstrdup (test);
  int modified = path_simplify (test_copy);

  if (0 != strcmp (test_copy, expected_result))
    {
      printf ("Failed path_simplify(\"%s\"): expected \"%s\", got \"%s\".\n",
	      test, expected_result, test_copy);
    }
  if (modified != expected_change)
    {
      if (expected_change == 1)
	printf ("Expected no modification with path_simplify(\"%s\").\n",
		test);
      else
	printf ("Expected modification with path_simplify(\"%s\").\n",
		test);
    }
  xfree (test_copy);
}

static void
test_path_simplify (void)
{
  static struct {
    char *test, *result;
    int should_modify;
  } tests[] = {
    { "",		"",		0 },
    { ".",		"",		1 },
    { "..",		"",		1 },
    { "foo",		"foo",		0 },
    { "foo/bar",	"foo/bar",	0 },
    { "foo///bar",	"foo/bar",	1 },
    { "foo/.",		"foo/",		1 },
    { "foo/./",		"foo/",		1 },
    { "foo./",		"foo./",	0 },
    { "foo/../bar",	"bar",		1 },
    { "foo/../bar/",	"bar/",		1 },
    { "foo/bar/..",	"foo/",		1 },
    { "foo/bar/../x",	"foo/x",	1 },
    { "foo/bar/../x/",	"foo/x/",	1 },
    { "foo/..",		"",		1 },
    { "foo/../..",	"",		1 },
    { "a/b/../../c",	"c",		1 },
    { "./a/../b",	"b",		1 }
  };
  int i;

  for (i = 0; i < countof (tests); i++)
    {
      char *test = tests[i].test;
      char *expected_result = tests[i].result;
      int   expected_change = tests[i].should_modify;
      run_test (test, expected_result, expected_change);
    }

  /* Now run all the tests with a leading slash before the test case,
     to prove that the slash is being preserved.  */
  for (i = 0; i < countof (tests); i++)
    {
      char *test, *expected_result;
      int expected_change = tests[i].should_modify;

      test = xmalloc (1 + strlen (tests[i].test) + 1);
      sprintf (test, "/%s", tests[i].test);

      expected_result = xmalloc (1 + strlen (tests[i].result) + 1);
      sprintf (expected_result, "/%s", tests[i].result);

      run_test (test, expected_result, expected_change);

      xfree (test);
      xfree (expected_result);
    }
}
#endif
