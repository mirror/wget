/*  
 *  string_t.c - dynamic string handling module
 *  
 *  Copyright (C) 2005 Free Software Foundation, Inc.
 *  
 *  This file is part of GNU Wget.
 *  
 *  GNU Wget is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  GNU Wget is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  In addition, as a special exception, the Free Software Foundation
 *  gives permission to link the code of its release of Wget with the
 *  OpenSSL project's "OpenSSL" library (or with modified versions of it
 *  that use the same license as the "OpenSSL" library), and distribute
 *  the linked executables.  You must obey the GNU General Public License
 *  in all respects for all of the code used other than "OpenSSL".  If you
 *  modify this file, you may extend this exception to your version of the
 *  file, but you are not obligated to do so.  If you do not wish to do
 *  so, delete this exception statement from your version.
 */  

#include "config.h"

#include <assert.h>
#include <stdlib.h>
#include <wchar.h>

#include "wget.h"

#ifdef STANDALONE
#undef xmalloc
#undef xrealloc
#undef xfree_null
#define xmalloc malloc
#define xrealloc realloc
#define xfree_null(p) if (!(p)) ; else free (p)
#else
#include "xmalloc.h"
#endif

#ifdef WINDOWS
static const wchar_t w_line_delim[] = L"\r\n";
static const char line_delim[] = "\r\n";
static const unsigned int line_delim_len = 2;
#else
static const wchar_t w_line_delim[] = L"\n";
static const char line_delim[] = "\n";
static const unsigned int line_delim_len = 2;
#endif

typedef struct string_t {
  char *sz;           /* standard null-terminated string */
  unsigned int len;   /* number of chars in the allocated buffer */
  unsigned int used;  /* number of used chars */
} *string;

#ifdef STRING_MODULE_DEBUG

#define assert_valid_string(str) \
  assert (((str) != NULL) \
          && ((str)->sz != NULL) \
          && ((str)->used + 1 <= (str)->len));

static void
string_dump (struct string_t *str, FILE *out)
{  
  assert_valid_string (str);
  assert (out);
  
  fprintf (out, "string_dump: str->sz = %s (%p)\n", str->sz, str->sz);
  fprintf (out, "string_dump: *(str->sz) = %d\n", *(str->sz));
  fprintf (out, "string_dump: str->len = %u\n", str->len);
  fprintf (out, "string_dump: str->used = %u\n", str->used);
}

#define DEBUG_PRINTF(x) printf x

#else /* not defined STRING_MODULE_DEBUG */

#define assert_valid_string(str) do {} while (0);
#define string_dump(str, out) do {} while (0);
#define DEBUG_PRINTF(x) do {} while (0);

#endif


void
string_init (struct string_t *s, unsigned int len)
{
  size_t to_alloc;
  
  /* no need to check that len > 0, since the len == 0 case is ok */
  assert (s != NULL);

  /* 
   * for the moment we try to perform a reasonable allocation by rounding up
   * the number of requested chars (including the trailing zero) to the 
   * closest multiple of 256, but we should probably find a better allocation
   * policy or completely leave the optimization of memory allocation to malloc
   */
  to_alloc = ((len + 1 + 256) & (~0xFF));
  
  s->sz = (char *) xmalloc (to_alloc * sizeof (char));
  *(s->sz) = '\0';
  s->len = to_alloc;
  s->used = 0;

  string_dump (s, stdout);
}

void
string_copy (struct string_t *dst, const void *src, unsigned int len)
{
  assert_valid_string (dst);
  assert (src != NULL);
  
  /* no need to do anything */
  if (len == 0) return;
  
  if (dst->sz == NULL) {
    string_init (dst, len); 
  }

  strncpy (dst->sz, (const char *) src, len);
  dst->sz[len] = '\0';

  dst->used = len;
}

void
string_cat (struct string_t *dst, const void *src, unsigned int len)
{
  assert_valid_string (dst);
  assert (src != NULL);

  /* no need to do anything */
  if (len == 0) return;
  
  if (dst->sz == NULL) {
    string_init (dst, len);    
  }

  strncpy (dst->sz + dst->used, (const char *) src, len);
  dst->sz[dst->used + len] = '\0';
  
  dst->used += len;
}

void
string_ready (struct string_t *str, unsigned int len)
{
  assert_valid_string (str);
  
  /* no need to do anything */
  if (len == 0) return;

  if (str->len - str->used < len)
    {
      DEBUG_PRINTF (("calling xrealloc"));
      str->sz = xrealloc (str->sz, str->len + len);
    }

  str->len += len;
}

void
string_destroy (struct string_t *str)
{
  assert_valid_string (str);
  
  xfree_null (str->sz);
  memset (str, 0, sizeof (*str));
}

static void
string_append_delim (struct string_t *dst)
{
  assert_valid_string (dst);
  string_cat (dst, line_delim, line_delim_len);
}

static int 
is_line_delim (const wchar_t *wsz)
{
  assert (wsz != NULL);
 
  if (*wsz == L'\r' && *(wsz + 1) == L'\n') {
    return 2;
  } else if (*wsz == L'\r' || *wsz == L'\n') {
    return 1;
  }
  
  return 0;
}

/*
 * DEST is the string to which the multibyte stuff will be added
 * TO_ESC is the null wide char string to add
 */
static void
string_append_multibyte (struct string_t *dest, const wchar_t *wstr, unsigned int len, mbstate_t *state)
{
  int i;

  assert_valid_string (dest);
  assert (wstr != NULL);
  assert (state != NULL);
  
  /* nothing to do */
  if (len == 0) return;

  string_ready (dest, 4 * MB_CUR_MAX * (len + 1));

  DEBUG_PRINTF (("string_append_multibyte: len = %u\n", len));
  string_dump (dest, stdout);
  
  for (i = 0; len > 0; ++i, --len) {    
    size_t copied = wcrtomb (dest->sz + dest->used, *(wstr + i), state);

    DEBUG_PRINTF (("string_append_multibyte (loop): i = %d\n", i));
    DEBUG_PRINTF (("string_append_multibyte (loop): copied = %u\n", copied));
    string_dump (dest, stdout);
    
    if (copied == (size_t)(-1)) {
      perror ("wcrtomb");
      exit (EXIT_FAILURE);
    }    
    dest->used += copied;
    *(dest->sz + dest->used) = '\0';

    DEBUG_PRINTF (("string_append_multibyte (loop): processed %s\n", dest->sz + dest->used - copied));
  }
}

static void
string_append_multibyte_newline (struct string_t *dest, mbstate_t *state)
{
  assert_valid_string (dest);
  string_append_multibyte(dest, w_line_delim, line_delim_len, state);
}

static void
string_append_multibyte_terminator (struct string_t *dest, mbstate_t *state)
{
  const wchar_t terminator = L'\0';

  assert_valid_string (dest);
  string_append_multibyte(dest, &terminator, 1, state);
}

/* 
 * DEST is the string to which the escape code will be added
 * TO_ESC is the (not necessarily null terminated) string to escape
 * LEN is the length of the string to escape
 */
static void
do_escape (struct string_t *dest, const char *to_esc, unsigned int len, mbstate_t *state)
{
  /* we only need to allocate 5 chars for byte: 
   * - one for the leading backslash
   * - three for the octal representation
   * - one for the trailing zero */
  wchar_t buf[8] = L"";
  size_t buf_elems = sizeof(buf)/sizeof(buf[0]);
  int i;

  assert_valid_string (dest);
  assert (to_esc != NULL);
  assert (state != NULL);

  /* nothing to do */
  if (len == 0) return;
  
  DEBUG_PRINTF (("do_escape: len = %d\n", len));
  string_dump (dest, stdout);
  
  for (i = 0; len > 0; ++i, --len) {
    int j = (unsigned char)*(to_esc + i);
    int cc = swprintf (buf, buf_elems, L"\\%03o", j);
    assert(cc > 0 && cc < buf_elems);
    DEBUG_PRINTF (("do_escape (loop): escaping \\%03o\n", j));
    buf[buf_elems - 1] = L'\0';
    assert (wcslen(buf) == 4);
    string_append_multibyte (dest, buf, 4, state);
  }
}

static void
string_escape (struct string_t *str)
{
  wchar_t c;
  int i;
  mbstate_t state1, state2;  
  size_t ret;
  unsigned int to_read;
  struct string_t src;
  int delim_size;
  
  assert_valid_string (str);

  memset (&state1, '\0', sizeof (state1));
  memset (&state2, '\0', sizeof (state2));
  
  src = *str;
  to_read = src.used + 1;
  
  /* this value is completely arbitrary */
  string_init (str, 4 * to_read);

  DEBUG_PRINTF (("string_escape: dumping string src"));
  string_dump (&src, stdout);
  DEBUG_PRINTF (("string_escape: dumping string str"));
  string_dump (str, stdout);

  i = 0;
  while ((ret = mbrtowc (&c, src.sz + i, to_read, &state1)) != 0) {
    DEBUG_PRINTF (("string_escape (loop): ret = %d\n", ret));
    if (ret == (size_t)(-2)) {
      DEBUG_PRINTF (("string_escape (loop): handling ret == -2"));
      /* mauro: should we just return the portion of the string already 
       * processed and print an error message? */
      perror ("mbrtowc");
      exit (EXIT_FAILURE);
    } else if (ret == (size_t)(-1)) {
      DEBUG_PRINTF (("string_escape (loop): handling ret == -1"));
      do_escape (str, src.sz + i, 1, &state2);
      i++;
    } else if ((delim_size = is_line_delim(&c))) {
      DEBUG_PRINTF (("string_escape (loop): handling ret == line_delim"));
      i += delim_size;
      string_append_multibyte_newline (str, &state2);
    } else if (iswprint(c) || iswblank(c)) {
      DEBUG_PRINTF (("string_escape (loop): handling ret == blank | printable"));
      string_append_multibyte (str, &c, 1, &state2);
      if (c == L'\\') {
        /* since the backslash character is used to escape unprintable data, 
         * in order to avoid ambiguities in the escaped string we have to 
         * escape backslashes as well */
        string_append_multibyte (str, &c, 1, &state2);
      }
      i += ret;
    } else { 
      DEBUG_PRINTF (("string_escape (loop): handling ret == toescape"));
      do_escape (str, src.sz + i, ret, &state2);
      i += ret;
    }
  }
  
  string_append_multibyte_terminator (str, &state2);
  
  string_destroy (&src);
}

/*
 * BUF must be a null-terminated dynamically allocated string
 * LEN is the size of the string BUF
 */
void
escape_buffer (char **buf, size_t len)
{
  struct string_t s;

  assert (buf != NULL && *buf != NULL);

  /* nothing to do */
  if (len == 0) return;
  
  DEBUG_PRINTF (("escape_buffer processing: %s (len %u)\n", *buf, len));
  
  s.sz = *buf; 
  s.used = len;
  s.len = len + 1;
  
  string_escape (&s);
  
  *buf = s.sz;
}

#ifdef STANDALONE
int main(void)
{
  char *buf;
  const size_t buflen = 512;
  buf = (char *) xmalloc(buflen);
  assert (buf != NULL);
  
  puts ("--------------------------------------------------------------------------------");
  
  while (fgets (buf, buflen - 1, stdin) != NULL)
    {
      /* just in case... */
      buf[buflen - 1] = '\0';
      printf ("before escape: %s", buf);
      escape_buffer (&buf, strlen(buf));
      printf ("after escape: %s", buf);
    }

  puts ("--------------------------------------------------------------------------------");

  return 0;
}
#endif

/*
 * vim: et ts=2 sw=2
 */

