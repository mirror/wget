/* Support for cookies.
   Copyright (C) 2001 Free Software Foundation, Inc.

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
   code submitted by Tomasz Wegrzanowski.  */

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
#include "url.h"
#include "cookies.h"

/* Hash table that maps domain names to cookie chains. */

static struct hash_table *cookies_hash_table;

/* This should be set by entry points in this file, so the low-level
   functions don't need to call time() all the time.  */

static time_t cookies_now;

/* This should *really* be in a .h file!  */
time_t http_atotm PARAMS ((char *));


/* Definition of `struct cookie' and the most basic functions. */

struct cookie {
  char *domain;			/* domain of the cookie */
  int port;			/* port number */
  char *path;			/* path prefix of the cookie */
  int secure;			/* whether cookie should be
				   transmitted over non-https
				   connections. */
  int permanent;		/* whether the cookie should outlive
				   the session */
  unsigned long expiry_time;	/* time when the cookie expires */
  int discard_requested;	/* whether cookie was created to
				   request discarding another
				   cookie */

  char *attr;			/* cookie attribute name */
  char *value;			/* cookie attribute value */

  struct cookie *next;		/* used for chaining of cookies in the
				   same domain. */
};

/* Allocate and return a new, empty cookie structure. */

static struct cookie *
cookie_new (void)
{
  struct cookie *cookie = xmalloc (sizeof (struct cookie));
  memset (cookie, '\0', sizeof (struct cookie));

  /* If we don't know better, assume cookie is non-permanent and valid
     for the entire session. */
  cookie->expiry_time = ~0UL;

  /* Assume default port. */
  cookie->port = 80;

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

   All cookies can be referenced through cookies_hash_table.  The key
   in that table is the domain name, and the value is a linked list of
   all cookies from that domain.  Every new cookie is placed on the
   head of the list.  */

/* Write "HOST:PORT" to a stack-allocated area and make RESULT point
  to that area.  RESULT should be a character pointer.  Useful for
  creating HOST:PORT strings, which are the keys in the hash
  table.  */

#define SET_HOSTPORT(host, port, result) do {		\
  int HP_len = strlen (host);				\
  result = alloca (HP_len + 1 + numdigit (port) + 1);	\
  memcpy (result, host, HP_len);			\
  result[HP_len] = ':';					\
  long_to_string (result + HP_len + 1, port);		\
} while (0)

/* Find cookie chain that corresponds to DOMAIN (exact) and PORT.  */

static struct cookie *
find_cookie_chain_exact (const char *domain, int port)
{
  char *key;
  if (!cookies_hash_table)
    return NULL;
  SET_HOSTPORT (domain, port, key);
  return hash_table_get (cookies_hash_table, key);
}

/* Find and return the cookie whose domain, path, and attribute name
   correspond to COOKIE.  If found, PREVPTR will point to the location
   of the cookie previous in chain, or NULL if the found cookie is the
   head of a chain.

   If no matching cookie is found, return NULL. */

static struct cookie *
find_matching_cookie (struct cookie *cookie, struct cookie **prevptr)
{
  struct cookie *chain, *prev;

  if (!cookies_hash_table)
    goto nomatch;

  chain = find_cookie_chain_exact (cookie->domain, cookie->port);
  if (!chain)
    goto nomatch;

  prev = NULL;
  for (; chain; prev = chain, chain = chain->next)
    if (!strcmp (cookie->path, chain->path)
	&& !strcmp (cookie->attr, chain->attr))
      {
	*prevptr = prev;
	return chain;
      }

 nomatch:
  *prevptr = NULL;
  return NULL;
}

/* Store COOKIE to memory.

   This is done by placing COOKIE at the head of its chain.  However,
   if COOKIE matches a cookie already in memory, as determined by
   find_matching_cookie, the old cookie is unlinked and destroyed.

   The key of each chain's hash table entry is allocated only the
   first time; next hash_table_put's reuse the same key.  */

static void
store_cookie (struct cookie *cookie)
{
  struct cookie *chain_head;
  char *hostport;
  char *chain_key;

  if (!cookies_hash_table)
    /* If the hash table is not initialized, do so now, because we'll
       need to store things.  */
    cookies_hash_table = make_nocase_string_hash_table (0);

  /* Initialize hash table key.  */
  SET_HOSTPORT (cookie->domain, cookie->port, hostport);

  if (hash_table_get_pair (cookies_hash_table, hostport,
			   &chain_key, &chain_head))
    {
      /* There already exists a chain of cookies with this exact
         domain.  We need to check for duplicates -- if an existing
         cookie exactly matches our domain, path and name, we replace
         it.  */
      struct cookie *prev;
      struct cookie *victim = find_matching_cookie (cookie, &prev);

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
      chain_key = xstrdup (hostport);
    }

  hash_table_put (cookies_hash_table, chain_key, cookie);

  DEBUGP (("\nStored cookie %s %d %s %s %d %s %s %s\n",
	   cookie->domain, cookie->port, cookie->path,
	   cookie->permanent ? "permanent" : "nonpermanent",
	   cookie->secure,
	   asctime (localtime ((time_t *)&cookie->expiry_time)),
	   cookie->attr, cookie->value));
}

/* Discard a cookie matching COOKIE's domain, path, and attribute
   name.  This gets called when we encounter a cookie whose expiry
   date is in the past, or whose max-age is set to 0.  The former
   corresponds to netscape cookie spec, while the latter is specified
   by rfc2109.  */

static void
discard_matching_cookie (struct cookie *cookie)
{
  struct cookie *prev, *victim;

  if (!cookies_hash_table
      || !hash_table_count (cookies_hash_table))
    /* No elements == nothing to discard. */
    return;

  victim = find_matching_cookie (cookie, &prev);
  if (victim)
    {
      if (prev)
	/* Simply unchain the victim. */
	prev->next = victim->next;
      else
	{
	  /* VICTIM was head of its chain.  We need to place a new
	     cookie at the head.  */

	  char *hostport;
	  char *chain_key = NULL;
	  int res;

	  SET_HOSTPORT (victim->domain, victim->port, hostport);
	  res = hash_table_get_pair (cookies_hash_table, hostport,
				     &chain_key, NULL);
	  assert (res != 0);
	  if (!victim->next)
	    {
	      /* VICTIM was the only cookie in the chain.  Destroy the
		 chain and deallocate the chain key.  */

	      hash_table_remove (cookies_hash_table, hostport);
	      xfree (chain_key);
	    }
	  else
	    hash_table_put (cookies_hash_table, chain_key, victim->next);
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
	  cookie->expiry_time = (unsigned long)expires;
	}
      else
	/* Error in expiration spec.  Assume default (cookie valid for
	   this session.)  #### Should we return 0 and invalidate the
	   cookie?  */
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
	/* something is wrong. */
	return 0;
      cookie->permanent = 1;
      cookie->expiry_time = (unsigned long)cookies_now + (unsigned long)maxage;

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
   attribute.  */

#define ATTR_NAME_CHAR(c) (ISALNUM (c) || (c) == '-' || (c) == '_')

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
   This check is compliant with rfc2109.  */

static int
check_domain_match (const char *cookie_domain, const char *host)
{
  int headlen;
  const char *tail;

  DEBUGP (("cdm: 1"));

  /* Numeric address requires exact match.  It also requires HOST to
     be an IP address.  I suppose we *could* resolve HOST with
     store_hostaddress (it would hit the hash table), but rfc2109
     doesn't require it, and it doesn't seem very useful, so we
     don't.  */
  if (numeric_address_p (cookie_domain))
    return !strcmp (cookie_domain, host);

  DEBUGP ((" 2"));

  /* The domain must contain at least one embedded dot. */
  {
    const char *rest = cookie_domain;
    int len = strlen (rest);
    if (*rest == '.')
      ++rest, --len;		/* ignore first dot */
    if (len <= 0)
      return 0;
    if (rest[len - 1] == '.')
      --len;			/* ignore last dot */

    if (!memchr (rest, '.', len))
      /* No dots. */
      return 0;
  }

  DEBUGP ((" 3"));

  /* For the sake of efficiency, check for exact match first. */
  if (!strcasecmp (cookie_domain, host))
    return 1;

  DEBUGP ((" 4"));

  /* In rfc2109 terminology, HOST needs domain-match COOKIE_DOMAIN.
     This means that COOKIE_DOMAIN needs to start with `.' and be an
     FQDN, and that HOST must end with COOKIE_DOMAIN.  */
  if (*cookie_domain != '.')
    return 0;

  DEBUGP ((" 5"));

  /* Two proceed, we need to examine two parts of HOST: its head and
     its tail.  Head and tail are defined in terms of the length of
     the domain, like this:

       HHHHTTTTTTTTTTTTTTT  <- host
           DDDDDDDDDDDDDDD  <- domain

     That is, "head" is the part of the host before (dlen - hlen), and
     "tail" is what follows.

     For the domain to match, two conditions need to be true:

     1. Tail must equal DOMAIN.
     2. Head must not contain an embedded dot.  */

  headlen = strlen (host) - strlen (cookie_domain);

  if (headlen <= 0)
    /* DOMAIN must be a proper subset of HOST. */
    return 0;
  tail = host + headlen;

  DEBUGP ((" 6"));

  /* (1) */
  if (strcasecmp (tail, cookie_domain))
    return 0;

  DEBUGP ((" 7"));

  /* Test (2) is not part of the "domain-match" itself, but is
     recommended by rfc2109 for reasons of privacy.  */

  /* (2) */
  if (memchr (host, '.', headlen))
    return 0;

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

/* Parse the `Set-Cookie' header and, if the cookie is legal, store it
   to memory.  */

int
set_cookie_header_cb (const char *hdr, void *closure)
{
  struct urlinfo *u = (struct urlinfo *)closure;
  struct cookie *cookie;

  cookies_now = time (NULL);

  cookie = parse_set_cookies (hdr);
  if (!cookie)
    goto out;

  /* Sanitize parts of cookie. */

  if (!cookie->domain)
    cookie->domain = xstrdup (u->host);
  else
    {
      if (!check_domain_match (cookie->domain, u->host))
	{
	  DEBUGP (("Attempt to fake the domain: %s, %s\n",
		   cookie->domain, u->host));
	  goto out;
	}
    }
  if (!cookie->path)
    cookie->path = xstrdup (u->path);
  else
    {
      if (!check_path_match (cookie->path, u->path))
	{
	  DEBUGP (("Attempt to fake the path: %s, %s\n",
		   cookie->path, u->path));
	  goto out;
	}
    }

  cookie->port = u->port;

  if (cookie->discard_requested)
    {
      discard_matching_cookie (cookie);
      delete_cookie (cookie);
      return 1;
    }

  store_cookie (cookie);
  return 1;

 out:
  if (cookie)
    delete_cookie (cookie);
  return 1;
}

/* Support for sending out cookies in HTTP requests, based on
   previously stored cookies.  Entry point is
   `build_cookies_request'.  */


/* Count how many times CHR occurs in STRING. */

static int
count_char (const char *string, char chr)
{
  const char *p;
  int count = 0;
  for (p = string; *p; p++)
    if (*p == chr)
      ++count;
  return count;
}

/* Store CHAIN to STORE if there is room in STORE.  If not, inrecement
   COUNT anyway, so that when the function is done, we end up with the
   exact count of how much place we actually need.  */

#define STORE_CHAIN(st_chain, st_store, st_size, st_count) do {	\
  if (st_count < st_size)					\
    store[st_count] = st_chain;					\
  ++st_count;							\
} while (0)

/* Store cookie chains that match HOST, PORT.  Since more than one
   chain can match, the matches are written to STORE.  No more than
   SIZE matches are written; if more matches are present, return the
   number of chains that would have been written.  */

int
find_matching_chains (const char *host, int port,
		      struct cookie *store[], int size)
{
  struct cookie *chain;
  int dot_count;
  char *hash_key;
  int count = 0;

  if (!cookies_hash_table)
    return 0;

  SET_HOSTPORT (host, port, hash_key);

  /* Exact match. */
  chain = hash_table_get (cookies_hash_table, hash_key);
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
      chain = hash_table_get (cookies_hash_table, p);
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
  int len = strlen (prefix);
  if (strncmp (full_path, prefix, len))
    /* FULL_PATH doesn't begin with PREFIX. */
    return 0;

  /* Length of PREFIX determines the quality of the match. */
  return len;
}

static int
matching_cookie (const struct cookie *cookie, const char *path,
		 int connection_secure_p, int *path_goodness)
{
  int pg;

  if (cookie->expiry_time < cookies_now)
    /* Ignore stale cookies.  There is no need to unchain the cookie
       at this point -- Wget is a relatively short-lived application,
       and stale cookies will not be saved by `save_cookies'.  */
    return 0;
  if (cookie->secure && !connection_secure_p)
    /* Don't transmit secure cookies over an insecure connection.  */
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

/* Build a `Cookie' header for a request that goes to HOST:PORT and
   requests PATH from the server.  The resulting string is allocated
   with `malloc', and the caller is responsible for freeing it.  If no
   cookies pertain to this request, i.e. no cookie header should be
   generated, NULL is returned.  */

char *
build_cookies_request (const char *host, int port, const char *path,
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
  chain_count = find_matching_chains (host, port, all_chains, chain_store_size);
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
      if (matching_cookie (cookie, path, connection_secure_p, NULL))
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
	if (!matching_cookie (cookie, path, connection_secure_p, &pg))
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
load_cookies (const char *file)
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
      else
	cookie->port = cookie->secure ? DEFAULT_HTTPS_PORT : DEFAULT_HTTP_PORT;

      cookie->domain  = strdupdelim (domain_b, domain_e);

      /* safe default in case EXPIRES field is garbled. */
      cookie->expiry_time = cookies_now - 1;

      /* I don't like changing the line, but it's completely safe.
	 (line is malloced.)  */
      *expires_e = '\0';
      sscanf (expires_b, "%lu", &cookie->expiry_time);
      if (cookie->expiry_time < cookies_now)
	/* ignore stale cookie. */
	goto abort;
      cookie->permanent = 1;

      store_cookie (cookie);

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
      if (chain->expiry_time < cookies_now)
	continue;
      fprintf (fp, "%s\t%s\t%s\t%s\t%lu\t%s\t%s\n",
	       domain, *domain == '.' ? "TRUE" : "FALSE",
	       chain->path, chain->secure ? "TRUE" : "FALSE",
	       chain->expiry_time,
	       chain->attr, chain->value);
      if (ferror (fp))
	return 1;		/* stop mapping */
    }
  return 0;
}

/* Save cookies, in format described above, to FILE. */

void
save_cookies (const char *file)
{
  FILE *fp;

  if (!cookies_hash_table
      || !hash_table_count (cookies_hash_table))
    /* no cookies stored; nothing to do. */
    return;

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

  hash_table_map (cookies_hash_table, save_cookies_mapper, fp);

  if (ferror (fp))
    logprintf (LOG_NOTQUIET, _("Error writing to `%s': %s\n"),
	       file, strerror (errno));

  if (fclose (fp) < 0)
    logprintf (LOG_NOTQUIET, _("Error closing `%s': %s\n"),
	       file, strerror (errno));

  DEBUGP (("Done saving cookies.\n"));
}

static int
delete_cookie_chain_mapper (void *value, void *key, void *arg_ignored)
{
  char *chain_key = (char *)value;
  struct cookie *chain = (struct cookie *)key;

  /* Remove the chain from the table and free the key. */
  hash_table_remove (cookies_hash_table, chain_key);
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
cookies_cleanup (void)
{
  if (!cookies_hash_table)
    return;
  hash_table_map (cookies_hash_table, delete_cookie_chain_mapper, NULL);
  hash_table_destroy (cookies_hash_table);
  cookies_hash_table = NULL;
}
