/* HTML parser for Wget.
   Copyright (C) 1998, 2000 Free Software Foundation, Inc.

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

/* The only entry point to this module is map_html_tags(), which see.  */

/* TODO:

   - Allow hooks for callers to process contents outside tags.  This
     is needed to implement handling <style> and <script>.  The
     taginfo structure already carries the information about where the
     tags are, but this is not enough, because one would also want to
     skip the comments.  (The funny thing is that for <style> and
     <script> you *don't* want to skip comments!)

   - Create a test suite for regression testing. */

/* HISTORY:

   This is the third HTML parser written for Wget.  The first one was
   written some time during the Geturl 1.0 beta cycle, and was very
   inefficient and buggy.  It also contained some very complex code to
   remember a list of parser states, because it was supposed to be
   reentrant.  The idea was that several parsers would be running
   concurrently, and you'd have pass the function a unique ID string
   (for example, the URL) by which it found the relevant parser state
   and returned the next URL.  Over-engineering at its best.

   The second HTML parser was written for Wget 1.4 (the first version
   by the name `Wget'), and was a complete rewrite.  Although the new
   parser behaved much better and made no claims of reentrancy, it
   still shared many of the fundamental flaws of the old version -- it
   only regarded HTML in terms tag-attribute pairs, where the
   attribute's value was a URL to be returned.  Any other property of
   HTML, such as <base href=...>, or strange way to specify a URL,
   such as <meta http-equiv=Refresh content="0; URL=..."> had to be
   crudely hacked in -- and the caller had to be aware of these hacks.
   Like its predecessor, this parser did not support HTML comments.

   After Wget 1.5.1 was released, I set out to write a third HTML
   parser.  The objectives of the new parser were to: (1) provide a
   clean way to analyze HTML lexically, (2) separate interpretation of
   the markup from the parsing process, (3) be as correct as possible,
   e.g. correctly skipping comments and other SGML declarations, (4)
   understand the most common errors in markup and skip them or be
   relaxed towrds them, and (5) be reasonably efficient (no regexps,
   minimum copying and minimum or no heap allocation).

   I believe this parser meets all of the above goals.  It is
   reasonably well structured, and could be relatively easily
   separated from Wget and used elsewhere.  While some of its
   intrinsic properties limit its value as a general-purpose HTML
   parser, I believe that, with minimum modifications, it could serve
   as a backend for one.

   Due to time and other constraints, this parser was not integrated
   into Wget until the version 1.7. */

/* DESCRIPTION:

   The single entry point of this parser is map_html_tags(), which
   works by calling a function you specify for each tag.  The function
   gets called with the pointer to a structure describing the tag and
   its attributes.  */

/* To test as standalone, compile with `-DSTANDALONE -I.'.  You'll
   still need Wget headers to compile.  */

#include <config.h>

#ifdef STANDALONE
# define I_REALLY_WANT_CTYPE_MACROS
#endif

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <assert.h>

#include "wget.h"
#include "html-parse.h"

#ifdef STANDALONE
# define xmalloc malloc
# define xrealloc realloc
# define xfree free

# define ISSPACE(x) isspace (x)
# define ISDIGIT(x) isdigit (x)
# define ISALPHA(x) isalpha (x)
# define ISALNUM(x) isalnum (x)
# define TOLOWER(x) tolower (x)
#endif /* STANDALONE */

/* Pool support.  A pool is a resizable chunk of memory.  It is first
   allocated on the stack, and moved to the heap if it needs to be
   larger than originally expected.  map_html_tags() uses it to store
   the zero-terminated names and values of tags and attributes.

   Thus taginfo->name, and attr->name and attr->value for each
   attribute, do not point into separately allocated areas, but into
   different parts of the pool, separated only by terminating zeros.
   This ensures minimum amount of allocation and, for most tags, no
   allocation because the entire pool is kept on the stack.  */

struct pool {
  char *contents;		/* pointer to the contents. */
  int size;			/* size of the pool. */
  int index;			/* next unoccupied position in
                                   contents. */

  int alloca_p;			/* whether contents was allocated
                                   using alloca(). */
  char *orig_contents;		/* orig_contents, allocated by
                                   alloca().  this is used by
                                   POOL_FREE to restore the pool to
                                   the "initial" state. */
  int orig_size;
};

/* Initialize the pool to hold INITIAL_SIZE bytes of storage. */

#define POOL_INIT(pool, initial_size) do {		\
  (pool).size = (initial_size);				\
  (pool).contents = ALLOCA_ARRAY (char, (pool).size);	\
  (pool).index = 0;					\
  (pool).alloca_p = 1;					\
  (pool).orig_contents = (pool).contents;		\
  (pool).orig_size = (pool).size;			\
} while (0)

/* Grow the pool to accomodate at least SIZE new bytes.  If the pool
   already has room to accomodate SIZE bytes of data, this is a no-op.  */

#define POOL_GROW(pool, increase) do {					\
  int PG_newsize = (pool).index + increase;				\
  DO_REALLOC_FROM_ALLOCA ((pool).contents, (pool).size, PG_newsize,	\
			  (pool).alloca_p, char);			\
} while (0)

/* Append text in the range [beg, end) to POOL.  No zero-termination
   is done.  */

#define POOL_APPEND(pool, beg, end) do {			\
  const char *PA_beg = beg;					\
  int PA_size = end - PA_beg;					\
  POOL_GROW (pool, PA_size);					\
  memcpy ((pool).contents + (pool).index, PA_beg, PA_size);	\
  (pool).index += PA_size;					\
} while (0)

/* The same as the above, but with zero termination. */

#define POOL_APPEND_ZT(pool, beg, end) do {			\
  const char *PA_beg = beg;					\
  int PA_size = end - PA_beg;					\
  POOL_GROW (pool, PA_size + 1);				\
  memcpy ((pool).contents + (pool).index, PA_beg, PA_size);	\
  (pool).contents[(pool).index + PA_size] = '\0';		\
  (pool).index += PA_size + 1;					\
} while (0)

/* Forget old pool contents.  The allocated memory is not freed. */
#define POOL_REWIND(pool) pool.index = 0

/* Free heap-allocated memory for contents of POOL.  This calls
   xfree() if the memory was allocated through malloc.  It also
   restores `contents' and `size' to their original, pre-malloc
   values.  That way after POOL_FREE, the pool is fully usable, just
   as if it were freshly initialized with POOL_INIT.  */

#define POOL_FREE(pool) do {			\
  if (!(pool).alloca_p)				\
    xfree ((pool).contents);			\
  (pool).contents = (pool).orig_contents;	\
  (pool).size = (pool).orig_size;		\
  (pool).index = 0;				\
  (pool).alloca_p = 1;				\
} while (0)


#define AP_DOWNCASE		1
#define AP_PROCESS_ENTITIES	2
#define AP_SKIP_BLANKS		4

/* Copy the text in the range [BEG, END) to POOL, optionally
   performing operations specified by FLAGS.  FLAGS may be any
   combination of AP_DOWNCASE, AP_PROCESS_ENTITIES and AP_SKIP_BLANKS
   with the following meaning:

   * AP_DOWNCASE -- downcase all the letters;

   * AP_PROCESS_ENTITIES -- process the SGML entities and write out
   the decoded string.  Recognized entities are &lt, &gt, &amp, &quot,
   &nbsp and the numerical entities.

   * AP_SKIP_BLANKS -- ignore blanks at the beginning and at the end
   of text.  */
static void
convert_and_copy (struct pool *pool, const char *beg, const char *end, int flags)
{
  int old_index = pool->index;
  int size;

  /* First, skip blanks if required.  We must do this before entities
     are processed, so that blanks can still be inserted as, for
     instance, `&#32;'.  */
  if (flags & AP_SKIP_BLANKS)
    {
      while (beg < end && ISSPACE (*beg))
	++beg;
      while (end > beg && ISSPACE (end[-1]))
	--end;
    }
  size = end - beg;

  if (flags & AP_PROCESS_ENTITIES)
    {
      /* Stack-allocate a copy of text, process entities and copy it
         to the pool.  */
      char *local_copy = (char *)alloca (size + 1);
      const char *from = beg;
      char *to = local_copy;

      while (from < end)
	{
	  if (*from != '&')
	    *to++ = *from++;
	  else
	    {
	      const char *save = from;
	      int remain;

	      if (++from == end) goto lose;
	      remain = end - from;

	      if (*from == '#')
		{
		  int numeric;
		  ++from;
		  if (from == end || !ISDIGIT (*from)) goto lose;
		  for (numeric = 0; from < end && ISDIGIT (*from); from++)
		    numeric = 10 * numeric + (*from) - '0';
		  if (from < end && ISALPHA (*from)) goto lose;
		  numeric &= 0xff;
		  *to++ = numeric;
		}
#define FROB(x) (remain >= (sizeof (x) - 1)			\
		 && !memcmp (from, x, sizeof (x) - 1)		\
		 && (*(from + sizeof (x) - 1) == ';'		\
		     || remain == sizeof (x) - 1		\
		     || !ISALNUM (*(from + sizeof (x) - 1))))
	      else if (FROB ("lt"))
		*to++ = '<', from += 2;
	      else if (FROB ("gt"))
		*to++ = '>', from += 2;
	      else if (FROB ("amp"))
		*to++ = '&', from += 3;
	      else if (FROB ("quot"))
		*to++ = '\"', from += 4;
	      /* We don't implement the proposed "Added Latin 1"
		 entities (except for nbsp), because it is unnecessary
		 in the context of Wget, and would require hashing to
		 work efficiently.  */
	      else if (FROB ("nbsp"))
		*to++ = 160, from += 4;
	      else
		goto lose;
#undef FROB
	      /* If the entity was followed by `;', we step over the
		 `;'.  Otherwise, it was followed by either a
		 non-alphanumeric or EOB, in which case we do nothing.	*/
	      if (from < end && *from == ';')
		++from;
	      continue;

	    lose:
	      /* This was not an entity after all.  Back out.  */
	      from = save;
	      *to++ = *from++;
	    }
	}
      *to++ = '\0';
      POOL_APPEND (*pool, local_copy, to);
    }
  else
    {
      /* Just copy the text to the pool.  */
      POOL_APPEND_ZT (*pool, beg, end);
    }

  if (flags & AP_DOWNCASE)
    {
      char *p = pool->contents + old_index;
      for (; *p; p++)
	*p = TOLOWER (*p);
    }
}

/* Check whether the contents of [POS, POS+LENGTH) match any of the
   strings in the ARRAY.  */
static int
array_allowed (const char **array, const char *beg, const char *end)
{
  int length = end - beg;
  if (array)
    {
      for (; *array; array++)
	if (length >= strlen (*array)
	    && !strncasecmp (*array, beg, length))
	  break;
      if (!*array)
	return 0;
    }
  return 1;
}

/* RFC1866: name [of attribute or tag] consists of letters, digits,
   periods, or hyphens.  We also allow _, for compatibility with
   brain-damaged generators.  */
#define NAME_CHAR_P(x) (ISALNUM (x) || (x) == '.' || (x) == '-' || (x) == '_')

/* States while advancing through comments. */
#define AC_S_DONE	0
#define AC_S_BACKOUT	1
#define AC_S_BANG	2
#define AC_S_DEFAULT	3
#define AC_S_DCLNAME	4
#define AC_S_DASH1	5
#define AC_S_DASH2	6
#define AC_S_COMMENT	7
#define AC_S_DASH3	8
#define AC_S_DASH4	9
#define AC_S_QUOTE1	10
#define AC_S_IN_QUOTE	11
#define AC_S_QUOTE2	12

#ifdef STANDALONE
static int comment_backout_count;
#endif

/* Advance over an SGML declaration (the <!...> forms you find in HTML
   documents).  The function returns the location after the
   declaration.  The reason we need this is that HTML comments are
   expressed as comments in so-called "empty declarations".

   To recap: any SGML declaration may have comments associated with
   it, e.g.
       <!MY-DECL -- isn't this fun? -- foo bar>

   An HTML comment is merely an empty declaration (<!>) with a comment
   attached, like this:
       <!-- some stuff here -->

   Several comments may be embedded in one comment declaration:
       <!-- have -- -- fun -->

   Whitespace is allowed between and after the comments, but not
   before the first comment.

   Additionally, this function attempts to handle double quotes in
   SGML declarations correctly.  */
static const char *
advance_declaration (const char *beg, const char *end)
{
  const char *p = beg;
  char quote_char = '\0';	/* shut up, gcc! */
  char ch;
  int state = AC_S_BANG;

  if (beg == end)
    return beg;
  ch = *p++;

  /* It looked like a good idea to write this as a state machine, but
     now I wonder...  */

  while (state != AC_S_DONE && state != AC_S_BACKOUT)
    {
      if (p == end)
	state = AC_S_BACKOUT;
      switch (state)
	{
	case AC_S_DONE:
	case AC_S_BACKOUT:
	  break;
	case AC_S_BANG:
	  if (ch == '!')
	    {
	      ch = *p++;
	      state = AC_S_DEFAULT;
	    }
	  else
	    state = AC_S_BACKOUT;
	  break;
	case AC_S_DEFAULT:
	  switch (ch)
	    {
	    case '-':
	      state = AC_S_DASH1;
	      break;
	    case ' ':
	    case '\t':
	    case '\r':
	    case '\n':
	      ch = *p++;
	      break;
	    case '>':
	      state = AC_S_DONE;
	      break;
	    case '\'':
	    case '\"':
	      state = AC_S_QUOTE1;
	      break;
	    default:
	      if (NAME_CHAR_P (ch))
		state = AC_S_DCLNAME;
	      else
		state = AC_S_BACKOUT;
	      break;
	    }
	  break;
	case AC_S_DCLNAME:
	  if (NAME_CHAR_P (ch))
	    ch = *p++;
	  else if (ch == '-')
	    state = AC_S_DASH1;
	  else
	    state = AC_S_DEFAULT;
	  break;
	case AC_S_QUOTE1:
	  /* We must use 0x22 because broken assert macros choke on
	     '"' and '\"'.  */
	  assert (ch == '\'' || ch == 0x22);
	  quote_char = ch;	/* cheating -- I really don't feel like
				   introducing more different states for
				   different quote characters. */
	  ch = *p++;
	  state = AC_S_IN_QUOTE;
	  break;
	case AC_S_IN_QUOTE:
	  if (ch == quote_char)
	    state = AC_S_QUOTE2;
	  else
	    ch = *p++;
	  break;
	case AC_S_QUOTE2:
	  assert (ch == quote_char);
	  ch = *p++;
	  state = AC_S_DEFAULT;
	  break;
	case AC_S_DASH1:
	  assert (ch == '-');
	  ch = *p++;
	  state = AC_S_DASH2;
	  break;
	case AC_S_DASH2:
	  switch (ch)
	    {
	    case '-':
	      ch = *p++;
	      state = AC_S_COMMENT;
	      break;
	    default:
	      state = AC_S_BACKOUT;
	    }
	  break;
	case AC_S_COMMENT:
	  switch (ch)
	    {
	    case '-':
	      state = AC_S_DASH3;
	      break;
	    default:
	      ch = *p++;
	      break;
	    }
	  break;
	case AC_S_DASH3:
	  assert (ch == '-');
	  ch = *p++;
	  state = AC_S_DASH4;
	  break;
	case AC_S_DASH4:
	  switch (ch)
	    {
	    case '-':
	      ch = *p++;
	      state = AC_S_DEFAULT;
	      break;
	    default:
	      state = AC_S_COMMENT;
	      break;
	    }
	  break;
	}
    }

  if (state == AC_S_BACKOUT)
    {
#ifdef STANDALONE
      ++comment_backout_count;
#endif
      return beg + 1;
    }
  return p;
}

/* Advance P (a char pointer), with the explicit intent of being able
   to read the next character.  If this is not possible, go to finish.  */

#define ADVANCE(p) do {				\
  ++p;						\
  if (p >= end)					\
    goto finish;				\
} while (0)

/* Skip whitespace, if any. */

#define SKIP_WS(p) do {				\
  while (ISSPACE (*p)) {			\
    ADVANCE (p);				\
  }						\
} while (0)

/* Skip non-whitespace, if any. */

#define SKIP_NON_WS(p) do {			\
  while (!ISSPACE (*p)) {			\
    ADVANCE (p);				\
  }						\
} while (0)

#ifdef STANDALONE
static int tag_backout_count;
#endif

/* Map MAPFUN over HTML tags in TEXT, which is SIZE characters long.
   MAPFUN will be called with two arguments: pointer to an initialized
   struct taginfo, and CLOSURE.

   ALLOWED_TAG_NAMES should be a NULL-terminated array of tag names to
   be processed by this function.  If it is NULL, all the tags are
   allowed.  The same goes for attributes and ALLOWED_ATTRIBUTE_NAMES.

   (Obviously, the caller can filter out unwanted tags and attributes
   just as well, but this is just an optimization designed to avoid
   unnecessary copying for tags/attributes which the caller doesn't
   want to know about.  These lists are searched linearly; therefore,
   if you're interested in a large number of tags or attributes, you'd
   better set these to NULL and filter them out yourself with a
   hashing process most appropriate for your application.)  */

void
map_html_tags (const char *text, int size,
	       const char **allowed_tag_names,
	       const char **allowed_attribute_names,
	       void (*mapfun) (struct taginfo *, void *),
	       void *closure)
{
  const char *p = text;
  const char *end = text + size;

  int attr_pair_count = 8;
  int attr_pair_alloca_p = 1;
  struct attr_pair *pairs = ALLOCA_ARRAY (struct attr_pair, attr_pair_count);
  struct pool pool;

  if (!size)
    return;

  POOL_INIT (pool, 256);

  {
    int nattrs, end_tag;
    const char *tag_name_begin, *tag_name_end;
    const char *tag_start_position;
    int uninteresting_tag;

  look_for_tag:
    POOL_REWIND (pool);

    nattrs = 0;
    end_tag = 0;

    /* Find beginning of tag.  We use memchr() instead of the usual
       looping with ADVANCE() for speed. */
    p = memchr (p, '<', end - p);
    if (!p)
      goto finish;

    tag_start_position = p;
    ADVANCE (p);

    /* Establish the type of the tag (start-tag, end-tag or
       declaration).  */
    if (*p == '!')
      {
	/* This is an SGML declaration -- just skip it.  */
	p = advance_declaration (p, end);
	if (p == end)
	  goto finish;
	goto look_for_tag;
      }
    else if (*p == '/')
      {
	end_tag = 1;
	ADVANCE (p);
      }
    tag_name_begin = p;
    while (NAME_CHAR_P (*p))
      ADVANCE (p);
    if (p == tag_name_begin)
      goto look_for_tag;
    tag_name_end = p;
    SKIP_WS (p);
    if (end_tag && *p != '>')
      goto backout_tag;

    if (!array_allowed (allowed_tag_names, tag_name_begin, tag_name_end))
      /* We can't just say "goto look_for_tag" here because we need
         the loop below to properly advance over the tag's attributes.  */
      uninteresting_tag = 1;
    else
      {
	uninteresting_tag = 0;
	convert_and_copy (&pool, tag_name_begin, tag_name_end, AP_DOWNCASE);
      }

    /* Find the attributes. */
    while (1)
      {
	const char *attr_name_begin, *attr_name_end;
	const char *attr_value_begin, *attr_value_end;
	const char *attr_raw_value_begin, *attr_raw_value_end;
	int operation = AP_DOWNCASE; /* stupid compiler. */

	SKIP_WS (p);

	if (*p == '/')
	  {
	    /* A slash at this point means the tag is about to be
	       closed.  This is legal in XML and has been popularized
	       in HTML via XHTML.  */
	    /* <foo a=b c=d /> */
	    /*              ^  */
	    ADVANCE (p);
	    SKIP_WS (p);
	    if (*p != '>')
	      goto backout_tag;
	  }

	/* Check for end of tag definition. */
	if (*p == '>')
	  break;

	/* Establish bounds of attribute name. */
	attr_name_begin = p;	/* <foo bar ...> */
				/*      ^        */
	while (NAME_CHAR_P (*p))
	  ADVANCE (p);
	attr_name_end = p;	/* <foo bar ...> */
				/*         ^     */
	if (attr_name_begin == attr_name_end)
	  goto backout_tag;

	/* Establish bounds of attribute value. */
	SKIP_WS (p);
	if (NAME_CHAR_P (*p) || *p == '/' || *p == '>')
	  {
	    /* Minimized attribute syntax allows `=' to be omitted.
               For example, <UL COMPACT> is a valid shorthand for <UL
               COMPACT="compact">.  Even if such attributes are not
               useful to Wget, we need to support them, so that the
               tags containing them can be parsed correctly. */
	    attr_raw_value_begin = attr_value_begin = attr_name_begin;
	    attr_raw_value_end = attr_value_end = attr_name_end;
	  }
	else if (*p == '=')
	  {
	    ADVANCE (p);
	    SKIP_WS (p);
	    if (*p == '\"' || *p == '\'')
	      {
		int newline_seen = 0;
		char quote_char = *p;
		attr_raw_value_begin = p;
		ADVANCE (p);
		attr_value_begin = p; /* <foo bar="baz"> */
				      /*           ^     */
		while (*p != quote_char)
		  {
		    if (!newline_seen && *p == '\n')
		      {
			/* If a newline is seen within the quotes, it
			   is most likely that someone forgot to close
			   the quote.  In that case, we back out to
			   the value beginning, and terminate the tag
			   at either `>' or the delimiter, whichever
			   comes first.  Such a tag terminated at `>'
			   is discarded.  */
			p = attr_value_begin;
			newline_seen = 1;
			continue;
		      }
		    else if (newline_seen && *p == '>')
		      break;
		    ADVANCE (p);
		  }
		attr_value_end = p; /* <foo bar="baz"> */
				    /*              ^  */
		if (*p == quote_char)
		  ADVANCE (p);
		else
		  goto look_for_tag;
		attr_raw_value_end = p;	/* <foo bar="baz"> */
					/*               ^ */
		/* The AP_SKIP_BLANKS part is not entirely correct,
		   because we don't want to skip blanks for all the
		   attribute values.  */
		operation = AP_PROCESS_ENTITIES | AP_SKIP_BLANKS;
	      }
	    else
	      {
		attr_value_begin = p; /* <foo bar=baz> */
				      /*          ^    */
		/* According to SGML, a name token should consist only
		   of alphanumerics, . and -.  However, this is often
		   violated by, for instance, `%' in `width=75%'.
		   We'll be liberal and allow just about anything as
		   an attribute value.  */
		while (!ISSPACE (*p) && *p != '>')
		  ADVANCE (p);
		attr_value_end = p; /* <foo bar=baz qux=quix> */
				    /*             ^          */
		if (attr_value_begin == attr_value_end)
		  /* <foo bar=> */
		  /*          ^ */
		  goto backout_tag;
		attr_raw_value_begin = attr_value_begin;
		attr_raw_value_end = attr_value_end;
		operation = AP_PROCESS_ENTITIES;
	      }
	  }
	else
	  {
	    /* We skipped the whitespace and found something that is
	       neither `=' nor the beginning of the next attribute's
	       name.  Back out.  */
	    goto backout_tag;	/* <foo bar [... */
				/*          ^    */
	  }

	/* If we're not interested in the tag, don't bother with any
           of the attributes.  */
	if (uninteresting_tag)
	  continue;

	/* If we aren't interested in the attribute, skip it.  We
           cannot do this test any sooner, because our text pointer
           needs to correctly advance over the attribute.  */
	if (allowed_attribute_names
	    && !array_allowed (allowed_attribute_names, attr_name_begin,
			       attr_name_end))
	  continue;

	DO_REALLOC_FROM_ALLOCA (pairs, attr_pair_count, nattrs + 1,
				attr_pair_alloca_p, struct attr_pair);

	pairs[nattrs].name_pool_index = pool.index;
	convert_and_copy (&pool, attr_name_begin, attr_name_end, AP_DOWNCASE);

	pairs[nattrs].value_pool_index = pool.index;
	convert_and_copy (&pool, attr_value_begin, attr_value_end, operation);
	pairs[nattrs].value_raw_beginning = attr_raw_value_begin;
	pairs[nattrs].value_raw_size = (attr_raw_value_end
					- attr_raw_value_begin);
	++nattrs;
      }

    if (uninteresting_tag)
      {
	ADVANCE (p);
	goto look_for_tag;
      }

    /* By now, we have a valid tag with a name and zero or more
       attributes.  Fill in the data and call the mapper function.  */
    {
      int i;
      struct taginfo taginfo;

      taginfo.name      = pool.contents;
      taginfo.end_tag_p = end_tag;
      taginfo.nattrs    = nattrs;
      /* We fill in the char pointers only now, when pool can no
	 longer get realloc'ed.  If we did that above, we could get
	 hosed by reallocation.  Obviously, after this point, the pool
	 may no longer be grown.  */
      for (i = 0; i < nattrs; i++)
	{
	  pairs[i].name = pool.contents + pairs[i].name_pool_index;
	  pairs[i].value = pool.contents + pairs[i].value_pool_index;
	}
      taginfo.attrs = pairs;
      taginfo.start_position = tag_start_position;
      taginfo.end_position   = p + 1;
      /* Ta-dam! */
      (*mapfun) (&taginfo, closure);
      ADVANCE (p);
    }
    goto look_for_tag;

  backout_tag:
#ifdef STANDALONE
    ++tag_backout_count;
#endif
    /* The tag wasn't really a tag.  Treat its contents as ordinary
       data characters. */
    p = tag_start_position + 1;
    goto look_for_tag;
  }

 finish:
  POOL_FREE (pool);
  if (!attr_pair_alloca_p)
    xfree (pairs);
}

#undef ADVANCE
#undef SKIP_WS
#undef SKIP_NON_WS

#ifdef STANDALONE
static void
test_mapper (struct taginfo *taginfo, void *arg)
{
  int i;

  printf ("%s%s", taginfo->end_tag_p ? "/" : "", taginfo->name);
  for (i = 0; i < taginfo->nattrs; i++)
    printf (" %s=%s", taginfo->attrs[i].name, taginfo->attrs[i].value);
  putchar ('\n');
  ++*(int *)arg;
}

int main ()
{
  int size = 256;
  char *x = (char *)xmalloc (size);
  int length = 0;
  int read_count;
  int tag_counter = 0;

  while ((read_count = fread (x + length, 1, size - length, stdin)))
    {
      length += read_count;
      size <<= 1;
      x = (char *)xrealloc (x, size);
    }

  map_html_tags (x, length, NULL, NULL, test_mapper, &tag_counter);
  printf ("TAGS: %d\n", tag_counter);
  printf ("Tag backouts:     %d\n", tag_backout_count);
  printf ("Comment backouts: %d\n", comment_backout_count);
  return 0;
}
#endif /* STANDALONE */
