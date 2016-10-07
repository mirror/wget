/* IRI related functions.
   Copyright (C) 2008, 2009, 2010, 2011, 2015 Free Software Foundation,
   Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at
your option) any later version.

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
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_ICONV
# include <iconv.h>
#endif
#include <stringprep.h>
#include <idna.h>
#include <idn-free.h>
#include <errno.h>

#include "utils.h"
#include "url.h"
#include "c-strcase.h"
#include "c-strcasestr.h"
#include "xstrndup.h"

/* RFC3987 section 3.1 mandates STD3 ASCII RULES */
#define IDNA_FLAGS  IDNA_USE_STD3_ASCII_RULES

/* Note: locale encoding is kept in options struct (opt.locale) */

/* Given a string containing "charset=XXX", return the encoding if found,
   or NULL otherwise */
char *
parse_charset (const char *str)
{
  const char *end;
  char *charset;

  if (!str || !*str)
    return NULL;

  str = c_strcasestr (str, "charset=");
  if (!str)
    return NULL;

  str += 8;
  end = str;

  /* sXXXav: which chars should be banned ??? */
  while (*end && !c_isspace (*end))
    end++;

  /* sXXXav: could strdupdelim return NULL ? */
  charset = strdupdelim (str, end);

  /* Do a minimum check on the charset value */
  if (!check_encoding_name (charset))
    {
      xfree (charset);
      return NULL;
    }

  /*logprintf (LOG_VERBOSE, "parse_charset: %s\n", quote (charset));*/

  return charset;
}

/* Find the locale used, or fall back on a default value */
char *
find_locale (void)
{
  return (char *) stringprep_locale_charset ();
}

/* Basic check of an encoding name. */
bool
check_encoding_name (const char *encoding)
{
  const char *s = encoding;

  while (*s)
    {
      if (!c_isascii (*s) || c_isspace (*s))
        {
          logprintf (LOG_VERBOSE, _("Encoding %s isn't valid\n"), quote (encoding));
          return false;
        }

      s++;
    }

  return true;
}

/* Do the conversion according to the passed conversion descriptor cd. *out
   will contain the transcoded string on success. *out content is
   unspecified otherwise. */
static bool
do_conversion (const char *tocode, const char *fromcode, char const *in_org, size_t inlen, char **out)
{
  iconv_t cd;
  /* sXXXav : hummm hard to guess... */
  size_t len, done, outlen;
  int invalid = 0, tooshort = 0;
  char *s, *in, *in_save;

  cd = iconv_open (tocode, fromcode);
  if (cd == (iconv_t)(-1))
    {
      logprintf (LOG_VERBOSE, _("Conversion from %s to %s isn't supported\n"),
                 quote (fromcode), quote (tocode));
      *out = NULL;
      return false;
    }

  /* iconv() has to work on an unescaped string */
  in_save = in = xstrndup (in_org, inlen);
  url_unescape_except_reserved (in);
  inlen = strlen(in);

  len = outlen = inlen * 2;
  *out = s = xmalloc (outlen + 1);
  done = 0;

  for (;;)
    {
      if (iconv (cd, (ICONV_CONST char **) &in, &inlen, out, &outlen) != (size_t)(-1) &&
          iconv (cd, NULL, NULL, out, &outlen) != (size_t)(-1))
        {
          *out = s;
          *(s + len - outlen - done) = '\0';
          xfree(in_save);
          iconv_close(cd);
          IF_DEBUG
          {
            /* not not print out embedded passwords, in_org might be an URL */
            if (!strchr(in_org, '@') && !strchr(*out, '@'))
              debug_logprintf ("converted '%s' (%s) -> '%s' (%s)\n", in_org, fromcode, *out, tocode);
            else
              debug_logprintf ("%s: logging suppressed, strings may contain password\n", __func__);
          }
          return true;
        }

      /* Incomplete or invalid multibyte sequence */
      if (errno == EINVAL || errno == EILSEQ)
        {
          if (!invalid)
            logprintf (LOG_VERBOSE,
                      _("Incomplete or invalid multibyte sequence encountered\n"));

          invalid++;
          **out = *in;
          in++;
          inlen--;
          (*out)++;
          outlen--;
        }
      else if (errno == E2BIG) /* Output buffer full */
        {
          tooshort++;
          done = len;
          len = outlen = done + inlen * 2;
          s = xrealloc (s, outlen + 1);
          *out = s + done;
        }
      else /* Weird, we got an unspecified error */
        {
          logprintf (LOG_VERBOSE, _("Unhandled errno %d\n"), errno);
          break;
        }
    }

    xfree(in_save);
    iconv_close(cd);
    IF_DEBUG
    {
      /* not not print out embedded passwords, in_org might be an URL */
      if (!strchr(in_org, '@') && !strchr(*out, '@'))
        debug_logprintf ("converted '%s' (%s) -> '%s' (%s)\n", in_org, fromcode, *out, tocode);
      else
        debug_logprintf ("%s: logging suppressed, strings may contain password\n", __func__);
    }
    return false;
}

/* Try converting string str from locale to UTF-8. Return a new string
   on success, or str on error or if conversion isn't needed. */
const char *
locale_to_utf8 (const char *str)
{
  char *new;

  /* That shouldn't happen, just in case */
  if (!opt.locale)
    {
      logprintf (LOG_VERBOSE, _("locale_to_utf8: locale is unset\n"));
      opt.locale = find_locale ();
    }

  if (!opt.locale || !c_strcasecmp (opt.locale, "utf-8"))
    return str;

  if (do_conversion ("UTF-8", opt.locale, (char *) str, strlen ((char *) str), &new))
    return (const char *) new;

  xfree (new);
  return str;
}

/*
 * Work around a libidn <= 1.30 vulnerability.
 *
 * The function checks for a valid UTF-8 character sequence before
 * passing it to idna_to_ascii_8z().
 *
 * [1] http://lists.gnu.org/archive/html/help-libidn/2015-05/msg00002.html
 * [2] https://lists.gnu.org/archive/html/bug-wget/2015-06/msg00002.html
 * [3] http://curl.haxx.se/mail/lib-2015-06/0143.html
 */
static bool
_utf8_is_valid(const char *utf8)
{
  const unsigned char *s = (const unsigned char *) utf8;

  while (*s)
    {
      if ((*s & 0x80) == 0) /* 0xxxxxxx ASCII char */
        s++;
      else if ((*s & 0xE0) == 0xC0) /* 110xxxxx 10xxxxxx */
        {
          if ((s[1] & 0xC0) != 0x80)
            return false;
          s+=2;
        }
      else if ((*s & 0xF0) == 0xE0) /* 1110xxxx 10xxxxxx 10xxxxxx */
        {
          if ((s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80)
            return false;
          s+=3;
        }
      else if ((*s & 0xF8) == 0xF0) /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
        {
          if ((s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80 || (s[3] & 0xC0) != 0x80)
            return false;
          s+=4;
        }
      else
        return false;
    }

  return true;
}

/* Try to "ASCII encode" UTF-8 host. Return the new domain on success or NULL
   on error. */
char *
idn_encode (const struct iri *i, const char *host)
{
  int ret;
  char *ascii_encoded;
  char *utf8_encoded = NULL;

  /* Encode to UTF-8 if not done */
  if (!i->utf8_encode)
    {
      if (!remote_to_utf8 (i, host, &utf8_encoded))
          return NULL;  /* Nothing to encode or an error occured */
    }

  if (!_utf8_is_valid(utf8_encoded ? utf8_encoded : host))
    {
      logprintf (LOG_VERBOSE, _("Invalid UTF-8 sequence: %s\n"),
                 quote(utf8_encoded ? utf8_encoded : host));
      xfree (utf8_encoded);
      return NULL;
    }

  /* Store in ascii_encoded the ASCII UTF-8 NULL terminated string */
  ret = idna_to_ascii_8z (utf8_encoded ? utf8_encoded : host, &ascii_encoded, IDNA_FLAGS);
  xfree (utf8_encoded);

  if (ret != IDNA_SUCCESS)
    {
      logprintf (LOG_VERBOSE, _("idn_encode failed (%d): %s\n"), ret,
                 quote (idna_strerror (ret)));
      return NULL;
    }

  return ascii_encoded;
}

/* Try to decode an "ASCII encoded" host. Return the new domain in the locale
   on success or NULL on error. */
char *
idn_decode (const char *host)
{
  char *new;
  int ret;

  ret = idna_to_unicode_8zlz (host, &new, IDNA_FLAGS);
  if (ret != IDNA_SUCCESS)
    {
      logprintf (LOG_VERBOSE, _("idn_decode failed (%d): %s\n"), ret,
                 quote (idna_strerror (ret)));
      return NULL;
    }

  return new;
}

/* Try to transcode string str from remote encoding to UTF-8. On success, *new
   contains the transcoded string. *new content is unspecified otherwise. */
bool
remote_to_utf8 (const struct iri *iri, const char *str, char **new)
{
  bool ret = false;

  if (!iri->uri_encoding)
    return false;

  /* When `i->uri_encoding' == "UTF-8" there is nothing to convert.  But we must
     test for non-ASCII symbols for correct hostname processing in `idn_encode'
     function. */
  if (!c_strcasecmp (iri->uri_encoding, "UTF-8"))
    {
      const unsigned char *p;
      for (p = (unsigned char *) str; *p; p++)
        if (*p > 127)
          {
            *new = strdup (str);
            return true;
          }
      return false;
    }

  if (do_conversion ("UTF-8", iri->uri_encoding, str, strlen (str), new))
    ret = true;

  /* Test if something was converted */
  if (*new && !strcmp (str, *new))
    {
      xfree (*new);
      return false;
    }

  return ret;
}

/* Allocate a new iri structure and return a pointer to it. */
struct iri *
iri_new (void)
{
  struct iri *i = xmalloc (sizeof *i);
  i->uri_encoding = opt.encoding_remote ? xstrdup (opt.encoding_remote) : NULL;
  i->content_encoding = NULL;
  i->orig_url = NULL;
  i->utf8_encode = opt.enable_iri;
  return i;
}

struct iri *iri_dup (const struct iri *src)
{
  struct iri *i = xmalloc (sizeof *i);
  i->uri_encoding = src->uri_encoding ? xstrdup (src->uri_encoding) : NULL;
  i->content_encoding = (src->content_encoding ?
                         xstrdup (src->content_encoding) : NULL);
  i->orig_url = src->orig_url ? xstrdup (src->orig_url) : NULL;
  i->utf8_encode = src->utf8_encode;
  return i;
}

/* Completely free an iri structure. */
void
iri_free (struct iri *i)
{
  if (i)
    {
      xfree (i->uri_encoding);
      xfree (i->content_encoding);
      xfree (i->orig_url);
      xfree (i);
    }
}

/* Set uri_encoding of struct iri i. If a remote encoding was specified, use
   it unless force is true. */
void
set_uri_encoding (struct iri *i, const char *charset, bool force)
{
  DEBUGP (("URI encoding = %s\n", charset ? quote (charset) : "None"));
  if (!force && opt.encoding_remote)
    return;
  if (i->uri_encoding)
    {
      if (charset && !c_strcasecmp (i->uri_encoding, charset))
        return;
      xfree (i->uri_encoding);
    }

  i->uri_encoding = charset ? xstrdup (charset) : NULL;
}

/* Set content_encoding of struct iri i. */
void
set_content_encoding (struct iri *i, const char *charset)
{
  DEBUGP (("URI content encoding = %s\n", charset ? quote (charset) : "None"));
  if (opt.encoding_remote)
    return;
  if (i->content_encoding)
    {
      if (charset && !c_strcasecmp (i->content_encoding, charset))
        return;
      xfree (i->content_encoding);
    }

  i->content_encoding = charset ? xstrdup (charset) : NULL;
}
