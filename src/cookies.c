/* Support for cookies.
   Copyright (C) 2001, 2002 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* Written by Hrvoje Niksic.  Parts are loosely inspired by cookie
   code submitted by Tomasz Wegrzanowski.

   TODO: Implement limits on cookie-related sizes, such as max. cookie
   size, max. number of cookies, etc.  Add more "cookie jar" methods,
   such as methods to over stored cookies, to clear temporary cookies,
   to perform intelligent auto-saving, etc.  Ultimately support
   `Set-Cookie2' and `Cookie2' headers.  */

#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "wget.h"
#include "utils.h"
#include "hash.h"
#include "cookies.h"

/* This should *really* be in a .h file!  */
time_t http_atotm PARAMS ((const char *));

/* Declarations of `struct cookie' and the most basic functions. */

struct cookie_jar {
  /* Hash table that maps domain names to cookie chains.  A "cookie
     chain" is a linked list of cookies that belong to the same
     domain.  */
  struct hash_table *chains_by_domain;

  int cookie_count;		/* number of cookies in the jar. */
};

/* Value set by entry point functions, so that the low-level
   routines don't need to call time() all the time.  */
time_t cookies_now;

struct cookie_jar *
cookie_jar_new (void)
{
  struct cookie_jar *jar = xmalloc (sizeof (struct cookie_jar));
  jar->chains_by_domain = make_nocase_string_hash_table (0);
  jar->cookie_count = 0;
  return jar;
}

struct cookie {
  char *domain;			/* domain of the cookie */
  int port;			/* port number */
  char *path;			/* path prefix of the cookie */
  int secure;			/* whether cookie should be
				   transmitted over non-https
				   connections. */
  int permanent;		/* whether the cookie should outlive
				   the session */
  time_t expiry_time;		/* time when the cookie expires */
  int discard_requested;	/* whether cookie was created to
				   request discarding another
				   cookie */

  char *attr;			/* cookie attribute name */
  char *value;			/* cookie attribute value */

  struct cookie_jar *jar;	/* pointer back to the cookie jar, for
				   convenience. */
  struct cookie *next;		/* used for chaining of cookies in the
				   same domain. */
};

#define PORT_ANY (-1)
#define COOKIE_EXPIRED_P(c) ((c)->expiry_time != 0 && (c)->expiry_time < cookies_now)

/* Allocate and return a new, empty cookie structure. */

static struct cookie *
cookie_new (void)
{
  struct cookie *cookie = xmalloc (sizeof (struct cookie));
  memset (cookie, '\0', sizeof (struct cookie));

  /* Both cookie->permanent and cookie->expiry_time are now 0.  By
     default, we assume that the cookie is non-permanent and valid
     until the end of the session.  */

  cookie->port = PORT_ANY;
  return cookie;
}

/* Deallocate COOKIE and its components. */

static void
delete_cookie (struct cookie *cookie)
{
  FREE_MAYBE (cookie->domain);
  FREE_MAYBE (cookie->path);
  FREE_MAYBE (cookie->attr);
  FREE_MAYBE (cookie->value);
  xfree (cookie);
}

/* Functions for storing cookies.

   All cookies can be reached beginning with jar->chains_by_domain.
   The key in that table is the domain name, and the value is a linked
   list of all cookies from that domain.  Every new cookie is placed
   on the head of the list.  */

/* Find and return a cookie in JAR whose domain, path, and attribute
   name correspond to COOKIE.  If found, PREVPTR will point to the
   location of the cookie previous in chain, or NULL if the found
   cookie is the head of a chain.

   If no matching cookie is found, return NULL. */

static struct cookie *
find_matching_cookie (struct cookie_jar *jar, struct cookie *cookie,
		      struct cookie **prevptr)
{
  struct cookie *chain, *prev;

  chain = hash_table_get (jar->chains_by_domain, cookie->domain);
  if (!chain)
    goto nomatch;

  prev = NULL;
  for (; chain; prev = chain, chain = chain->next)
    if (0 == strcmp (cookie->path, chain->path)
	&& 0 == strcmp (cookie->attr, chain->attr)
	&& cookie->port == chain->port)
      {
	*prevptr = prev;
	return chain;
      }

 nomatch:
  *prevptr = NULL;
  return NULL;
}

/* Store COOKIE to the jar.

   This is done by placing COOKIE at the head of its chain.  However,
   if COOKIE matches a cookie already in memory, as determined by
   find_matching_cookie, the old cookie is unlinked and destroyed.

   The key of each chain's hash table entry is allocated only the
   first time; next hash_table_put's reuse the same key.  */

static void
store_cookie (struct cookie_jar *jar, struct cookie *cookie)
{
  struct cookie *chain_head;
  char *chain_key;

  if (hash_table_get_pair (jar->chains_by_domain, cookie->domain,
			   &chain_key, &chain_head))
    {
      /* A chain of cookies in this domain already exists.  Check for
         duplicates -- if an extant cookie exactly matches our domain,
         port, path, and name, replace it.  */
      struct cookie *prev;
      struct cookie *victim = find_matching_cookie (jar, cookie, &prev);

      if (victim)
	{
	  /* Remove VICTIM from the chain.  COOKIE will be placed at
	     the head. */
	  if (prev)
	    {
	      prev->next = victim->next;
	      cookie->next = chain_head;
	    }
	  else
	    {
	      /* prev is NULL; apparently VICTIM was at the head of
		 the chain.  This place will be taken by COOKIE, so
		 all we need to do is:  */
	      cookie->next = victim->next;
	    }
	  delete_cookie (victim);
	  --jar->cookie_count;
	  DEBUGP (("Deleted old cookie (to be replaced.)\n"));
	}
      else
	cookie->next = chain_head;
    }
  else
    {
      /* We are now creating the chain.  Allocate the string that will
	 be used as a key.  It is unsafe to use cookie->domain for
	 that, because it might get deallocated by the above code at
	 some point later.  */
      cookie->next = NULL;
      chain_key = xstrdup (cookie->domain);
    }

  hash_table_put (jar->chains_by_domain, chain_key, cookie);
  ++jar->cookie_count;

  DEBUGP (("\nStored cookie %s %d%s %s %s %d %s %s %s\n",
	   cookie->domain, cookie->port,
	   cookie->port == PORT_ANY ? " (ANY)" : "",
	   cookie->path,
	   cookie->permanent ? "permanent" : "nonpermanent",
	   cookie->secure,
	   cookie->expiry_time
	   ? asctime (localtime (&cookie->expiry_time)) : "<indefinitely>",
	   cookie->attr, cookie->value));
}

/* Discard a cookie matching COOKIE's domain, port, path, and
   attribute name.  This gets called when we encounter a cookie whose
   expiry date is in the past, or whose max-age is set to 0.  The
   former corresponds to netscape cookie spec, while the latter is
   specified by rfc2109.  */

static void
discard_matching_cookie (struct cookie_jar *jar, struct cookie *cookie)
{
  struct cookie *prev, *victim;

  if (!hash_table_count (jar->chains_by_domain))
    /* No elements == nothing to discard. */
    return;

  victim = find_matching_cookie (jar, cookie, &prev);
  if (victim)
    {
      if (prev)
	/* Simply unchain the victim. */
	prev->next = victim->next;
      else
	{
	  /* VICTIM was head of its chain.  We need to place a new
	     cookie at the head.  */
	  char *chain_key = NULL;
	  int res;

	  res = hash_table_get_pair (jar->chains_by_domain, victim->domain,
				     &chain_key, NULL);
	  assert (res != 0);
	  if (!victim->next)
	    {
	      /* VICTIM was the only cookie in the chain.  Destroy the
		 chain and deallocate the chain key.  */
	      hash_table_remove (jar->chains_by_domain, victim->domain);
	      xfree (chain_key);
	    }
	  else
	    hash_table_put (jar->chains_by_domain, chain_key, victim->next);
	}
      delete_cookie (victim);
      DEBUGP (("Discarded old cookie.\n"));
    }
}

/* Functions for parsing the `Set-Cookie' header, and creating new
   cookies from the wire.  */


#define NAME_IS(string_literal)					\
  BOUNDED_EQUAL_NO_CASE (name_b, name_e, string_literal)

#define VALUE_EXISTS (value_b && value_e)

#define VALUE_NON_EMPTY (VALUE_EXISTS && (value_b != value_e))

/* Update the appropriate cookie field.  [name_b, name_e) are expected
   to delimit the attribute name, while [value_b, value_e) (optional)
   should delimit the attribute value.

   When called the first time, it will set the cookie's attribute name
   and value.  After that, it will check the attribute name for
   special fields such as `domain', `path', etc.  Where appropriate,
   it will parse the values of the fields it recognizes and fill the
   corresponding fields in COOKIE.

   Returns 1 on success.  Returns zero in case a syntax error is
   found; such a cookie should be discarded.  */

static int
update_cookie_field (struct cookie *cookie,
		     const char *name_b, const char *name_e,
		     const char *value_b, const char *value_e)
{
  assert (name_b != NULL && name_e != NULL);

  if (!cookie->attr)
    {
      if (!VALUE_EXISTS)
	return 0;
      cookie->attr = strdupdelim (name_b, name_e);
      cookie->value = strdupdelim (value_b, value_e);
      return 1;
    }

  if (NAME_IS ("domain"))
    {
      if (!VALUE_NON_EMPTY)
	return 0;
      FREE_MAYBE (cookie->domain);
      cookie->domain = strdupdelim (value_b, value_e);
      return 1;
    }
  else if (NAME_IS ("path"))
    {
      if (!VALUE_NON_EMPTY)
	return 0;
      FREE_MAYBE (cookie->path);
      cookie->path = strdupdelim (value_b, value_e);
      return 1;
    }
  else if (NAME_IS ("expires"))
    {
      char *value_copy;
      time_t expires;

      if (!VALUE_NON_EMPTY)
	return 0;
      BOUNDED_TO_ALLOCA (value_b, value_e, value_copy);

      expires = http_atotm (value_copy);
      if (expires != -1)
	{
	  cookie->permanent = 1;
	  cookie->expiry_time = (time_t)expires;
	}
      else
	/* Error in expiration spec.  Assume default (cookie valid for
	   this session.)  */
	;

      /* According to netscape's specification, expiry time in the
	 past means that discarding of a matching cookie is
	 requested.  */
      if (cookie->expiry_time < cookies_now)
	cookie->discard_requested = 1;

      return 1;
    }
  else if (NAME_IS ("max-age"))
    {
      double maxage = -1;
      char *value_copy;

      if (!VALUE_NON_EMPTY)
	return 0;
      BOUNDED_TO_ALLOCA (value_b, value_e, value_copy);

      sscanf (value_copy, "%lf", &maxage);
      if (maxage == -1)
	/* something went wrong. */
	return 0;
      cookie->permanent = 1;
      cookie->expiry_time = cookies_now + maxage;

      /* According to rfc2109, a cookie with max-age of 0 means that
	 discarding of a matching cookie is requested.  */
      if (maxage == 0)
	cookie->discard_requested = 1;

      return 1;
    }
  else if (NAME_IS ("secure"))
    {
      /* ignore value completely */
      cookie->secure = 1;
      return 1;
    }
  else
    /* Unrecognized attribute; ignore it. */
    return 1;
}

#undef NAME_IS

/* Returns non-zero for characters that are legal in the name of an
   attribute.  This used to allow only alphanumerics, '-', and '_',
   but we need to be more lenient because a number of sites wants to
   use weirder attribute names.  rfc2965 "informally specifies"
   attribute name (token) as "a sequence of non-special, non-white
   space characters".  So we allow everything except the stuff we know
   could harm us.  */

#define ATTR_NAME_CHAR(c) ((c) > 32 && (c) < 127	\
			   && (c) != '"' && (c) != '='	\
			   && (c) != ';' && (c) != ',')

/* Fetch the next character without doing anything special if CH gets
   set to 0.  (The code executed next is expected to handle it.)  */

#define FETCH1(ch, ptr) do {			\
  ch = *ptr++;					\
} while (0)

/* Like FETCH1, but jumps to `eof' label if CH gets set to 0.  */

#define FETCH(ch, ptr) do {		\
  FETCH1 (ch, ptr);			\
  if (!ch)				\
    goto eof;				\
} while (0)

/* Parse the contents of the `Set-Cookie' header.  The header looks
   like this:

   name1=value1; name2=value2; ...

   Trailing semicolon is optional; spaces are allowed between all
   tokens.  Additionally, values may be quoted.

   A new cookie is returned upon success, NULL otherwise.  The
   function `update_cookie_field' is used to update the fields of the
   newly created cookie structure.  */

static struct cookie *
parse_set_cookies (const char *sc)
{
  struct cookie *cookie = cookie_new ();

  enum { S_NAME_PRE, S_NAME, S_NAME_POST,
	 S_VALUE_PRE, S_VALUE, S_VALUE_TRAILSPACE_MAYBE,
	 S_QUOTED_VALUE, S_QUOTED_VALUE_POST,
	 S_ATTR_ACTION,
	 S_DONE, S_ERROR } state = S_NAME_PRE;

  const char *p = sc;
  char c;

  const char *name_b  = NULL, *name_e  = NULL;
  const char *value_b = NULL, *value_e = NULL;

  FETCH (c, p);

  while (state != S_DONE && state != S_ERROR)
    {
      switch (state)
	{
	case S_NAME_PRE:
	  if (ISSPACE (c))
	    FETCH (c, p);
	  else if (ATTR_NAME_CHAR (c))
	    {
	      name_b = p - 1;
	      FETCH1 (c, p);
	      state = S_NAME;
	    }
	  else
	    /* empty attr name not allowed */
	    state = S_ERROR;
	  break;
	case S_NAME:
	  if (ATTR_NAME_CHAR (c))
	    FETCH1 (c, p);
	  else if (!c || c == ';' || c == '=' || ISSPACE (c))
	    {
	      name_e = p - 1;
	      state = S_NAME_POST;
	    }
	  else
	    state = S_ERROR;
	  break;
	case S_NAME_POST:
	  if (ISSPACE (c))
	    FETCH1 (c, p);
	  else if (!c || c == ';')
	    {
	      value_b = value_e = NULL;
	      state = S_ATTR_ACTION;
	    }
	  else if (c == '=')
	    {
	      FETCH1 (c, p);
	      state = S_VALUE_PRE;
	    }
	  else
	    state = S_ERROR;
	  break;
	case S_VALUE_PRE:
	  if (ISSPACE (c))
	    FETCH1 (c, p);
	  else if (c == '"')
	    {
	      value_b = p;
	      FETCH (c, p);
	      state = S_QUOTED_VALUE;
	    }
	  else if (c == ';' || c == '\0')
	    {
	      value_b = value_e = p - 1;
	      state = S_ATTR_ACTION;
	    }
	  else
	    {
	      value_b = p - 1;
	      value_e = NULL;
	      state = S_VALUE;
	    }
	  break;
	case S_VALUE:
	  if (c == ';' || c == '\0')
	    {
	      if (!value_e)
		value_e = p - 1;
	      state = S_ATTR_ACTION;
	    }
	  else if (ISSPACE (c))
	    {
	      value_e = p - 1;
	      FETCH1 (c, p);
	      state = S_VALUE_TRAILSPACE_MAYBE;
	    }
	  else
	    {
	      value_e = NULL;	/* no trailing space */
	      FETCH1 (c, p);
	    }
	  break;
	case S_VALUE_TRAILSPACE_MAYBE:
	  if (ISSPACE (c))
	    FETCH1 (c, p);
	  else
	    state = S_VALUE;
	  break;
	case S_QUOTED_VALUE:
	  if (c == '"')
	    {
	      value_e = p - 1;
	      FETCH1 (c, p);
	      state = S_QUOTED_VALUE_POST;
	    }
	  else
	    FETCH (c, p);
	  break;
	case S_QUOTED_VALUE_POST:
	  if (c == ';' || !c)
	    state = S_ATTR_ACTION;
	  else if (ISSPACE (c))
	    FETCH1 (c, p);
	  else
	    state = S_ERROR;
	  break;
	case S_ATTR_ACTION:
	  {
	    int legal = update_cookie_field (cookie, name_b, name_e,
					     value_b, value_e);
	    if (!legal)
	      {
		char *name;
		BOUNDED_TO_ALLOCA (name_b, name_e, name);
		logprintf (LOG_NOTQUIET,
			   _("Error in Set-Cookie, field `%s'"), name);
		state = S_ERROR;
		break;
	      }

	    if (c)
	      FETCH1 (c, p);
	    if (!c)
	      state = S_DONE;
	    else
	      state = S_NAME_PRE;
	  }
	  break;
	case S_DONE:
	case S_ERROR:
	  /* handled by loop condition */
	  break;
	}
    }
  if (state == S_DONE)
    return cookie;

  delete_cookie (cookie);
  if (state == S_ERROR)
    logprintf (LOG_NOTQUIET, _("Syntax error in Set-Cookie at character `%c'.\n"), c);
  else
    abort ();
  return NULL;

 eof:
  delete_cookie (cookie);
  logprintf (LOG_NOTQUIET,
	     _("Syntax error in Set-Cookie: premature end of string.\n"));
  return NULL;
}

/* Sanity checks.  These are important, otherwise it is possible for
   mailcious attackers to destroy important cookie information and/or
   violate your privacy.  */


#define REQUIRE_DIGITS(p) do {			\
  if (!ISDIGIT (*p))				\
    return 0;					\
  for (++p; ISDIGIT (*p); p++)			\
    ;						\
} while (0)

#define REQUIRE_DOT(p) do {			\
  if (*p++ != '.')				\
    return 0;					\
} while (0)

/* Check whether ADDR matches <digits>.<digits>.<digits>.<digits>.

  We don't want to call network functions like inet_addr() because all
  we need is a check, preferrably one that is small, fast, and
  well-defined.  */

static int
numeric_address_p (const char *addr)
{
  const char *p = addr;

  REQUIRE_DIGITS (p);		/* A */
  REQUIRE_DOT (p);		/* . */
  REQUIRE_DIGITS (p);		/* B */
  REQUIRE_DOT (p);		/* . */
  REQUIRE_DIGITS (p);		/* C */
  REQUIRE_DOT (p);		/* . */
  REQUIRE_DIGITS (p);		/* D */

  if (*p != '\0')
    return 0;
  return 1;
}

/* Check whether COOKIE_DOMAIN is an appropriate domain for HOST.
   Originally I tried to make the check compliant with rfc2109, but
   the sites deviated too often, so I had to fall back to "tail
   matching", as defined by the original Netscape's cookie spec.  */

static int
check_domain_match (const char *cookie_domain, const char *host)
{
  DEBUGP (("cdm: 1"));

  /* Numeric address requires exact match.  It also requires HOST to
     be an IP address.  */
  if (numeric_address_p (cookie_domain))
    return 0 == strcmp (cookie_domain, host);

  DEBUGP ((" 2"));

  /* For the sake of efficiency, check for exact match first. */
  if (!strcasecmp (cookie_domain, host))
    return 1;

  DEBUGP ((" 3"));

  /* HOST must match the tail of cookie_domain. */
  if (!match_tail (host, cookie_domain))
    return 0;

  /* We know that COOKIE_DOMAIN is a subset of HOST; however, we must
     make sure that somebody is not trying to set the cookie for a
     subdomain shared by many entities.  For example, "company.co.uk"
     must not be allowed to set a cookie for ".co.uk".  On the other
     hand, "sso.redhat.de" should be able to set a cookie for
     ".redhat.de".

     The only marginally sane way to handle this I can think of is to
     reject on the basis of the length of the second-level domain name
     (but when the top-level domain is unknown), with the assumption
     that those of three or less characters could be reserved.  For
     example:

          .co.org -> works because the TLD is known
           .co.uk -> doesn't work because "co" is only two chars long
          .com.au -> doesn't work because "com" is only 3 chars long
          .cnn.uk -> doesn't work because "cnn" is also only 3 chars long (ugh)
          .cnn.de -> doesn't work for the same reason (ugh!!)
         .abcd.de -> works because "abcd" is 4 chars long
      .img.cnn.de -> works because it's not trying to set the 2nd level domain
       .cnn.co.uk -> works for the same reason

    That should prevent misuse, while allowing reasonable usage.  If
    someone knows of a better way to handle this, please let me
    know.  */
  {
    const char *p = cookie_domain;
    int dccount = 1;		/* number of domain components */
    int ldcl  = 0;		/* last domain component length */
    int nldcl = 0;		/* next to last domain component length */
    int out;
    if (*p == '.')
      /* Ignore leading period in this calculation. */
      ++p;
    DEBUGP ((" 4"));
    for (out = 0; !out; p++)
      switch (*p)
	{
	case '\0':
	  out = 1;
	  break;
	case '.':
	  if (ldcl == 0)
	    /* Empty domain component found -- the domain is invalid. */
	    return 0;
	  if (*(p + 1) == '\0')
	    {
	      /* Tolerate trailing '.' by not treating the domain as
		 one ending with an empty domain component.  */
	      out = 1;
	      break;
	    }
	  nldcl = ldcl;
	  ldcl  = 0;
	  ++dccount;
	  break;
	default:
	  ++ldcl;
	}

    DEBUGP ((" 5"));

    if (dccount < 2)
      return 0;

    DEBUGP ((" 6"));

    if (dccount == 2)
      {
	int i;
	int known_toplevel = 0;
	static char *known_toplevel_domains[] = {
	  ".com", ".edu", ".net", ".org", ".gov", ".mil", ".int"
	};
	for (i = 0; i < ARRAY_SIZE (known_toplevel_domains); i++)
	  if (match_tail (cookie_domain, known_toplevel_domains[i]))
	    {
	      known_toplevel = 1;
	      break;
	    }
	if (!known_toplevel && nldcl <= 3)
	  return 0;
      }
  }

  DEBUGP ((" 7"));

  /* Don't allow domain "bar.com" to match host "foobar.com".  */
  if (*cookie_domain != '.')
    {
      int dlen = strlen (cookie_domain);
      int hlen = strlen (host);
      /* cookie host:    hostname.foobar.com */
      /* desired domain:             bar.com */
      /* '.' must be here in host-> ^        */
      if (hlen > dlen && host[hlen - dlen - 1] != '.')
	return 0;
    }

  DEBUGP ((" 8"));

  return 1;
}

static int path_matches PARAMS ((const char *, const char *));

/* Check whether PATH begins with COOKIE_PATH. */

static int
check_path_match (const char *cookie_path, const char *path)
{
  return path_matches (path, cookie_path);
}

/* Process the HTTP `Set-Cookie' header.  This results in storing the
   cookie or discarding a matching one, or ignoring it completely, all
   depending on the contents.  */

void
cookie_jar_process_set_cookie (struct cookie_jar *jar,
			       const char *host, int port,
			       const char *path, const char *set_cookie)
{
  struct cookie *cookie;
  cookies_now = time (NULL);

  cookie = parse_set_cookies (set_cookie);
  if (!cookie)
    goto out;

  /* Sanitize parts of cookie. */

  if (!cookie->domain)
    {
    copy_domain:
      cookie->domain = xstrdup (host);
      cookie->port = port;
    }
  else
    {
      if (!check_domain_match (cookie->domain, host))
	{
	  logprintf (LOG_NOTQUIET,
		     "Cookie coming from %s attempted to set domain to %s\n",
		     host, cookie->domain);
	  goto copy_domain;
	}
    }
  if (!cookie->path)
    cookie->path = xstrdup (path);
  else
    {
      if (!check_path_match (cookie->path, path))
	{
	  DEBUGP (("Attempt to fake the path: %s, %s\n",
		   cookie->path, path));
	  goto out;
	}
    }

  if (cookie->discard_requested)
    {
      discard_matching_cookie (jar, cookie);
      goto out;
    }

  store_cookie (jar, cookie);
  return;

 out:
  if (cookie)
    delete_cookie (cookie);
}

/* Support for sending out cookies in HTTP requests, based on
   previously stored cookies.  Entry point is
   `build_cookies_request'.  */

/* Store CHAIN to STORE if there is room in STORE.  If not, inrecement
   COUNT anyway, so that when the function is done, we end up with the
   exact count of how much place we actually need.  */

#define STORE_CHAIN(st_chain, st_store, st_size, st_count) do {	\
  if (st_count < st_size)					\
    store[st_count] = st_chain;					\
  ++st_count;							\
} while (0)

/* Store cookie chains that match HOST.  Since more than one chain can
   match, the matches are written to STORE.  No more than SIZE matches
   are written; if more matches are present, return the number of
   chains that would have been written.  */

static int
find_matching_chains (struct cookie_jar *jar, const char *host,
		      struct cookie *store[], int size)
{
  struct cookie *chain;
  int dot_count;
  char *hash_key;
  int count = 0;

  if (!hash_table_count (jar->chains_by_domain))
    return 0;

  STRDUP_ALLOCA (hash_key, host);

  /* Look for an exact match. */
  chain = hash_table_get (jar->chains_by_domain, hash_key);
  if (chain)
    STORE_CHAIN (chain, store, size, count);

  dot_count = count_char (host, '.');

  /* Match less and less specific domains.  For instance, given
     fly.srk.fer.hr, we match .srk.fer.hr, then .fer.hr.  */
  while (dot_count-- > 1)
    {
      /* Note: we operate directly on hash_key (in form host:port)
	 because we don't want to allocate new hash keys in a
	 loop.  */
      char *p = strchr (hash_key, '.');
      assert (p != NULL);
      chain = hash_table_get (jar->chains_by_domain, p);
      if (chain)
	STORE_CHAIN (chain, store, size, count);
      hash_key = p + 1;
    }
  return count;
}

/* If FULL_PATH begins with PREFIX, return the length of PREFIX, zero
   otherwise.  */

static int
path_matches (const char *full_path, const char *prefix)
{
  int len;

  if (*prefix != '/')
    /* Wget's HTTP paths do not begin with '/' (the URL code treats it
       as a separator), but the '/' is assumed when matching against
       the cookie stuff.  */
    return 0;

  ++prefix;
  len = strlen (prefix);

  if (0 != strncmp (full_path, prefix, len))
    /* FULL_PATH doesn't begin with PREFIX. */
    return 0;

  /* Length of PREFIX determines the quality of the match. */
  return len + 1;
}

/* Return non-zero iff COOKIE matches the given PATH, PORT, and
   security flag.  HOST is not a flag because it is assumed that the
   cookie comes from the correct chain.

   If PATH_GOODNESS is non-NULL, store the "path goodness" there.  The
   said goodness is a measure of how well COOKIE matches PATH.  It is
   used for ordering cookies.  */

static int
matching_cookie (const struct cookie *cookie, const char *path, int port,
		 int connection_secure_p, int *path_goodness)
{
  int pg;

  if (COOKIE_EXPIRED_P (cookie))
    /* Ignore stale cookies.  Don't bother unchaining the cookie at
       this point -- Wget is a relatively short-lived application, and
       stale cookies will not be saved by `save_cookies'.  On the
       other hand, this function should be as efficient as
       possible.  */
    return 0;

  if (cookie->secure && !connection_secure_p)
    /* Don't transmit secure cookies over an insecure connection.  */
    return 0;
  if (cookie->port != PORT_ANY && cookie->port != port)
    return 0;
  pg = path_matches (path, cookie->path);
  if (!pg)
    return 0;

  if (path_goodness)
    /* If the caller requested path_goodness, we return it.  This is
       an optimization, so that the caller doesn't need to call
       path_matches() again.  */
    *path_goodness = pg;
  return 1;
}

struct weighed_cookie {
  struct cookie *cookie;
  int domain_goodness;
  int path_goodness;
};

/* Comparator used for uniquifying the list. */

static int
equality_comparator (const void *p1, const void *p2)
{
  struct weighed_cookie *wc1 = (struct weighed_cookie *)p1;
  struct weighed_cookie *wc2 = (struct weighed_cookie *)p2;

  int namecmp  = strcmp (wc1->cookie->attr, wc2->cookie->attr);
  int valuecmp = strcmp (wc1->cookie->value, wc2->cookie->value);

  /* We only really care whether both name and value are equal.  We
     return them in this order only for consistency...  */
  return namecmp ? namecmp : valuecmp;
}

/* Eliminate duplicate cookies.  "Duplicate cookies" are any two
   cookies whose name and value are the same.  Whenever a duplicate
   pair is found, one of the cookies is removed.  */

static int
eliminate_dups (struct weighed_cookie *outgoing, int count)
{
  int i;

  /* We deploy a simple uniquify algorithm: first sort the array
     according to our sort criterion, then uniquify it by comparing
     each cookie with its neighbor.  */

  qsort (outgoing, count, sizeof (struct weighed_cookie), equality_comparator);

  for (i = 0; i < count - 1; i++)
    {
      struct cookie *c1 = outgoing[i].cookie;
      struct cookie *c2 = outgoing[i + 1].cookie;
      if (!strcmp (c1->attr, c2->attr) && !strcmp (c1->value, c2->value))
	{
	  /* c1 and c2 are the same; get rid of c2. */
	  if (count > i + 1)
	    /* move all ptrs from positions [i + 1, count) to i. */
	    memmove (outgoing + i, outgoing + i + 1,
		     (count - (i + 1)) * sizeof (struct weighed_cookie));
	  /* We decrement i to counter the ++i above.  Remember that
	     we've just removed the element in front of us; we need to
	     remain in place to check whether outgoing[i] matches what
	     used to be outgoing[i + 2].  */
	  --i;
	  --count;
	}
    }
  return count;
}

/* Comparator used for sorting by quality. */

static int
goodness_comparator (const void *p1, const void *p2)
{
  struct weighed_cookie *wc1 = (struct weighed_cookie *)p1;
  struct weighed_cookie *wc2 = (struct weighed_cookie *)p2;

  /* Subtractions take `wc2' as the first argument becauase we want a
     sort in *decreasing* order of goodness.  */
  int dgdiff = wc2->domain_goodness - wc1->domain_goodness;
  int pgdiff = wc2->path_goodness - wc1->path_goodness;

  /* Sort by domain goodness; if these are the same, sort by path
     goodness.  (The sorting order isn't really specified; maybe it
     should be the other way around.)  */
  return dgdiff ? dgdiff : pgdiff;
}

/* Generate a `Cookie' header for a request that goes to HOST:PORT and
   requests PATH from the server.  The resulting string is allocated
   with `malloc', and the caller is responsible for freeing it.  If no
   cookies pertain to this request, i.e. no cookie header should be
   generated, NULL is returned.  */

char *
cookie_jar_generate_cookie_header (struct cookie_jar *jar, const char *host,
				   int port, const char *path,
				   int connection_secure_p)
{
  struct cookie *chain_default_store[20];
  struct cookie **all_chains = chain_default_store;
  int chain_store_size = ARRAY_SIZE (chain_default_store);
  int chain_count;

  struct cookie *cookie;
  struct weighed_cookie *outgoing;
  int count, i, ocnt;
  char *result;
  int result_size, pos;

 again:
  chain_count = find_matching_chains (jar, host, all_chains, chain_store_size);
  if (chain_count > chain_store_size)
    {
      /* It's extremely unlikely that more than 20 chains will ever
	 match.  But since find_matching_chains reports the exact size
	 it needs, it's easy to not have the limitation, so we
	 don't.  */
      all_chains = alloca (chain_count * sizeof (struct cookie *));
      chain_store_size = chain_count;
      goto again;
    }

  if (!chain_count)
    return NULL;

  cookies_now = time (NULL);

  /* Count the number of cookies whose path matches. */
  count = 0;
  for (i = 0; i < chain_count; i++)
    for (cookie = all_chains[i]; cookie; cookie = cookie->next)
      if (matching_cookie (cookie, path, port, connection_secure_p, NULL))
	++count;
  if (!count)
    /* No matching cookies. */
    return NULL;

  /* Allocate the array. */
  outgoing = alloca (count * sizeof (struct weighed_cookie));

  /* Fill the array with all the matching cookies from all the
     matching chains. */
  ocnt = 0;
  for (i = 0; i < chain_count; i++)
    for (cookie = all_chains[i]; cookie; cookie = cookie->next)
      {
	int pg;
	if (!matching_cookie (cookie, path, port, connection_secure_p, &pg))
	  continue;
	outgoing[ocnt].cookie = cookie;
	outgoing[ocnt].domain_goodness = strlen (cookie->domain);
	outgoing[ocnt].path_goodness   = pg;
	++ocnt;
      }
  assert (ocnt == count);

  /* Eliminate duplicate cookies; that is, those whose name and value
     are the same.  */
  count = eliminate_dups (outgoing, count);

  /* Sort the array so that best-matching domains come first, and
     that, within one domain, best-matching paths come first. */
  qsort (outgoing, count, sizeof (struct weighed_cookie), goodness_comparator);

  /* Count the space the name=value pairs will take. */
  result_size = 0;
  for (i = 0; i < count; i++)
    {
      struct cookie *c = outgoing[i].cookie;
      /* name=value */
      result_size += strlen (c->attr) + 1 + strlen (c->value);
    }

  /* Allocate output buffer:
     "Cookie: "       -- 8
     name=value pairs -- result_size
     "; " separators  -- (count - 1) * 2
     \r\n line ending -- 2
     \0 terminator    -- 1 */
  result_size = 8 + result_size + (count - 1) * 2 + 2 + 1;
  result = xmalloc (result_size);
  pos = 0;
  strcpy (result, "Cookie: ");
  pos += 8;
  for (i = 0; i < count; i++)
    {
      struct cookie *c = outgoing[i].cookie;
      int namlen = strlen (c->attr);
      int vallen = strlen (c->value);

      memcpy (result + pos, c->attr, namlen);
      pos += namlen;
      result[pos++] = '=';
      memcpy (result + pos, c->value, vallen);
      pos += vallen;
      if (i < count - 1)
	{
	  result[pos++] = ';';
	  result[pos++] = ' ';
	}
    }
  result[pos++] = '\r';
  result[pos++] = '\n';
  result[pos++] = '\0';
  assert (pos == result_size);
  return result;
}

/* Support for loading and saving cookies.  The format used for
   loading and saving roughly matches the format of `cookies.txt' file
   used by Netscape and Mozilla, at least the Unix versions.  The
   format goes like this:

       DOMAIN DOMAIN-FLAG PATH SECURE-FLAG TIMESTAMP ATTR-NAME ATTR-VALUE

     DOMAIN      -- cookie domain, optionally followed by :PORT
     DOMAIN-FLAG -- whether all hosts in the domain match
     PATH        -- cookie path
     SECURE-FLAG -- whether cookie requires secure connection
     TIMESTAMP   -- expiry timestamp, number of seconds since epoch
     ATTR-NAME   -- name of the cookie attribute
     ATTR-VALUE  -- value of the cookie attribute (empty if absent)

   The fields are separated by TABs (but Wget's loader recognizes any
   whitespace).  All fields are mandatory, except for ATTR-VALUE.  The
   `-FLAG' fields are boolean, their legal values being "TRUE" and
   "FALSE'.  Empty lines, lines consisting of whitespace only, and
   comment lines (beginning with # optionally preceded by whitespace)
   are ignored.

   Example line from cookies.txt (split in two lines for readability):

       .google.com	TRUE	/	FALSE	2147368447	\
       PREF	ID=34bb47565bbcd47b:LD=en:NR=20:TM=985172580:LM=985739012

   DOMAIN-FLAG is currently not honored by Wget.  The cookies whose
   domain begins with `.' are treated as if DOMAIN-FLAG were true,
   while all other cookies are treated as if it were FALSE. */


/* If the region [B, E) ends with :<digits>, parse the number, return
   it, and store new boundary (location of the `:') to DOMAIN_E_PTR.
   If port is not specified, return 0.  */

static int
domain_port (const char *domain_b, const char *domain_e,
	     const char **domain_e_ptr)
{
  int port = 0;
  const char *p;
  const char *colon = memchr (domain_b, ':', domain_e - domain_b);
  if (!colon)
    return 0;
  for (p = colon + 1; p < domain_e && ISDIGIT (*p); p++)
    port = 10 * port + (*p - '0');
  if (p < domain_e)
    /* Garbage following port number. */
    return 0;
  *domain_e_ptr = colon;
  return port;
}

#define SKIP_WS(p) do {				\
  while (*p && ISSPACE (*p))			\
    ++p;					\
} while (0)

#define SET_WORD_BOUNDARIES(p, b, e) do {	\
  SKIP_WS (p);					\
  b = p;					\
  /* skip non-ws */				\
  while (*p && !ISSPACE (*p))			\
    ++p;					\
  e = p;					\
  if (b == e)					\
    goto next;					\
} while (0)

/* Load cookies from FILE.  */

void
cookie_jar_load (struct cookie_jar *jar, const char *file)
{
  char *line;
  FILE *fp = fopen (file, "r");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, "Cannot open cookies file `%s': %s\n",
		 file, strerror (errno));
      return;
    }
  cookies_now = time (NULL);

  for (; ((line = read_whole_line (fp)) != NULL); xfree (line))
    {
      struct cookie *cookie;
      char *p = line;

      double expiry;
      int port;

      char *domain_b  = NULL, *domain_e  = NULL;
      char *ignore_b  = NULL, *ignore_e  = NULL;
      char *path_b    = NULL, *path_e    = NULL;
      char *secure_b  = NULL, *secure_e  = NULL;
      char *expires_b = NULL, *expires_e = NULL;
      char *name_b    = NULL, *name_e    = NULL;
      char *value_b   = NULL, *value_e   = NULL;

      SKIP_WS (p);

      if (!*p || *p == '#')
	/* empty line */
	continue;

      SET_WORD_BOUNDARIES (p, domain_b,  domain_e);
      SET_WORD_BOUNDARIES (p, ignore_b,  ignore_e);
      SET_WORD_BOUNDARIES (p, path_b,    path_e);
      SET_WORD_BOUNDARIES (p, secure_b,  secure_e);
      SET_WORD_BOUNDARIES (p, expires_b, expires_e);
      SET_WORD_BOUNDARIES (p, name_b,    name_e);

      /* Don't use SET_WORD_BOUNDARIES for value because it may
	 contain whitespace.  Instead, set value_e to the end of line,
	 modulo trailing space (this will skip the line separator.) */
      SKIP_WS (p);
      value_b = p;
      value_e = p + strlen (p);
      while (value_e > value_b && ISSPACE (*(value_e - 1)))
	--value_e;
      if (value_b == value_e)
	/* Hmm, should we check for empty value?  I guess that's
	   legal, so I leave it.  */
	;

      cookie = cookie_new ();

      cookie->attr    = strdupdelim (name_b, name_e);
      cookie->value   = strdupdelim (value_b, value_e);
      cookie->path    = strdupdelim (path_b, path_e);

      if (BOUNDED_EQUAL (secure_b, secure_e, "TRUE"))
	cookie->secure = 1;

      /* DOMAIN needs special treatment because we might need to
	 extract the port.  */
      port = domain_port (domain_b, domain_e, (const char **)&domain_e);
      if (port)
	cookie->port = port;
      cookie->domain  = strdupdelim (domain_b, domain_e);

      /* safe default in case EXPIRES field is garbled. */
      expiry = (double)cookies_now - 1;

      /* I don't like changing the line, but it's completely safe.
	 (line is malloced.)  */
      *expires_e = '\0';
      sscanf (expires_b, "%lf", &expiry);
      if (expiry < cookies_now)
	/* ignore stale cookie. */
	goto abort;
      cookie->expiry_time = expiry;

      /* If the cookie has survived being saved into an external file,
	 it is obviously permanent.  */
      cookie->permanent = 1;

      store_cookie (jar, cookie);

    next:
      continue;

    abort:
      delete_cookie (cookie);
    }
  fclose (fp);
}

/* Mapper for save_cookies callable by hash_table_map.  VALUE points
   to the head in a chain of cookies.  The function prints the entire
   chain.  */

static int
save_cookies_mapper (void *key, void *value, void *arg)
{
  FILE *fp = (FILE *)arg;
  char *domain = (char *)key;
  struct cookie *chain = (struct cookie *)value;
  for (; chain; chain = chain->next)
    {
      if (!chain->permanent)
	continue;
      if (COOKIE_EXPIRED_P (chain))
	continue;
      fputs (domain, fp);
      if (chain->port != PORT_ANY)
	fprintf (fp, ":%d", chain->port);
      fprintf (fp, "\t%s\t%s\t%s\t%.0f\t%s\t%s\n",
	       *domain == '.' ? "TRUE" : "FALSE",
	       chain->path, chain->secure ? "TRUE" : "FALSE",
	       (double)chain->expiry_time,
	       chain->attr, chain->value);
      if (ferror (fp))
	return 1;		/* stop mapping */
    }
  return 0;
}

/* Save cookies, in format described above, to FILE. */

void
cookie_jar_save (struct cookie_jar *jar, const char *file)
{
  FILE *fp;

  DEBUGP (("Saving cookies to %s.\n", file));

  cookies_now = time (NULL);

  fp = fopen (file, "w");
  if (!fp)
    {
      logprintf (LOG_NOTQUIET, _("Cannot open cookies file `%s': %s\n"),
		 file, strerror (errno));
      return;
    }

  fputs ("# HTTP cookie file.\n", fp);
  fprintf (fp, "# Generated by Wget on %s.\n", datetime_str (NULL));
  fputs ("# Edit at your own risk.\n\n", fp);

  hash_table_map (jar->chains_by_domain, save_cookies_mapper, fp);

  if (ferror (fp))
    logprintf (LOG_NOTQUIET, _("Error writing to `%s': %s\n"),
	       file, strerror (errno));

  if (fclose (fp) < 0)
    logprintf (LOG_NOTQUIET, _("Error closing `%s': %s\n"),
	       file, strerror (errno));

  DEBUGP (("Done saving cookies.\n"));
}

/* Destroy all the elements in the chain and unhook it from the cookie
   jar.  This is written in the form of a callback to hash_table_map
   and used by cookie_jar_delete to delete all the cookies in a
   jar.  */

static int
nuke_cookie_chain (void *value, void *key, void *arg)
{
  char *chain_key = (char *)value;
  struct cookie *chain = (struct cookie *)key;
  struct cookie_jar *jar = (struct cookie_jar *)arg;

  /* Remove the chain from the table and free the key. */
  hash_table_remove (jar->chains_by_domain, chain_key);
  xfree (chain_key);

  /* Then delete all the cookies in the chain. */
  while (chain)
    {
      struct cookie *next = chain->next;
      delete_cookie (chain);
      chain = next;
    }

  /* Keep mapping. */
  return 0;
}

/* Clean up cookie-related data. */

void
cookie_jar_delete (struct cookie_jar *jar)
{
  hash_table_map (jar->chains_by_domain, nuke_cookie_chain, jar);
  hash_table_destroy (jar->chains_by_domain);
  xfree (jar);
}
