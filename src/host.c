/* Host name resolution and matching.
   Copyright (C) 1995, 1996, 1997, 2000, 2001 Free Software Foundation, Inc.

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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <assert.h>
#include <sys/types.h>

#ifdef WINDOWS
# include <winsock.h>
#else
# include <sys/socket.h>
# include <netinet/in.h>
# ifndef __BEOS__
#  include <arpa/inet.h>
# endif
# include <netdb.h>
#endif /* WINDOWS */

#ifndef NO_ADDRESS
#define NO_ADDRESS NO_DATA
#endif

#ifdef HAVE_SYS_UTSNAME_H
# include <sys/utsname.h>
#endif
#include <errno.h>

#include "wget.h"
#include "utils.h"
#include "host.h"
#include "url.h"
#include "hash.h"

#ifndef errno
extern int errno;
#endif

#ifndef h_errno
# ifndef __CYGWIN__
extern int h_errno;
# endif
#endif

#define IP4_ADDRESS_LENGTH 4

/* Mapping between known hosts and to lists of their addresses. */

static struct hash_table *host_name_addresses_map;

/* Lists of addresses.  This should eventually be extended to handle
   IPv6.  */

struct address_list {
  int count;			/* number of adrresses */
  unsigned char *buffer;	/* buffer which holds all of them. */

  int faulty;			/* number of addresses known not to
				   work. */
  int refcount;			/* so we know whether to free it or
				   not. */
};

#define ADDR_LOCATION(al, index) ((al)->buffer + index * IP4_ADDRESS_LENGTH)

/* Get the bounds of the address list.  */

void
address_list_get_bounds (struct address_list *al, int *start, int *end)
{
  *start = al->faulty;
  *end   = al->count;
}

/* Copy address number INDEX to IP_STORE.  */

void
address_list_copy_one (struct address_list *al, int index,
		       unsigned char *ip_store)
{
  assert (index >= al->faulty && index < al->count);
  memcpy (ip_store, ADDR_LOCATION (al, index), IP4_ADDRESS_LENGTH);
}

/* Check whether two address lists have all their IPs in common.  */

int
address_list_match_all (struct address_list *al1, struct address_list *al2)
{
  if (al1 == al2)
    return 1;
  if (al1->count != al2->count)
    return 0;
  return 0 == memcmp (al1->buffer, al2->buffer,
		      al1->count * IP4_ADDRESS_LENGTH);
}

/* Mark the INDEXth element of AL as faulty, so that the next time
   this address list is used, the faulty element will be skipped.  */

void
address_list_set_faulty (struct address_list *al, int index)
{
#if 0
  /* Warning: INDEX is unused, so this assumes that the address list
     is traversed in order.  In the next release, either enable this
     assert, or use INDEX.  */
  assert (index == al->faulty);
#endif

  ++al->faulty;
  if (al->faulty >= al->count)
    /* All addresses have been proven faulty.  Since there's not much
       sense in returning the user an empty address list the next
       time, we'll rather make them all clean, so that they can be
       retried anew.  */
    al->faulty = 0;
}

/* Create an address_list out of a NULL-terminated list of addresses,
   as returned by gethostbyname.  */

static struct address_list *
address_list_new (char **h_addr_list)
{
  int count = 0, i;

  struct address_list *al = xmalloc (sizeof (struct address_list));

  while (h_addr_list[count])
    ++count;
  assert (count > 0);
  al->count    = count;
  al->faulty   = 0;
  al->buffer   = xmalloc (count * IP4_ADDRESS_LENGTH);
  al->refcount = 1;

  for (i = 0; i < count; i++)
    memcpy (ADDR_LOCATION (al, i), h_addr_list[i], IP4_ADDRESS_LENGTH);

  return al;
}

/* Like address_list_new, but initialized with only one address. */

static struct address_list *
address_list_new_one (const char *addr)
{
  struct address_list *al = xmalloc (sizeof (struct address_list));
  al->count    = 1;
  al->faulty   = 0;
  al->buffer   = xmalloc (IP4_ADDRESS_LENGTH);
  al->refcount = 1;
  memcpy (ADDR_LOCATION (al, 0), addr, IP4_ADDRESS_LENGTH);

  return al;
}

static void
address_list_delete (struct address_list *al)
{
  xfree (al->buffer);
  xfree (al);
}

void
address_list_release (struct address_list *al)
{
  --al->refcount;
  DEBUGP (("Releasing %p (new refcount %d).\n", al, al->refcount));
  if (al->refcount <= 0)
    {
      DEBUGP (("Deleting unused %p.\n", al));
      address_list_delete (al);
    }
}

/* The same as inet_ntoa, but without the need for a cast, or for
   #including the netinet stuff.  */

char *
pretty_print_address (const unsigned char *addr)
{
  return inet_ntoa (*(struct in_addr *)addr);
}

/* Add host name HOST with the address ADDR_TEXT to the cache.
   ADDR_LIST is a NULL-terminated list of addresses, as in struct
   hostent.  */

static void
cache_host_lookup (const char *host, struct address_list *al)
{
  if (!host_name_addresses_map)
    host_name_addresses_map = make_nocase_string_hash_table (0);

  ++al->refcount;
  hash_table_put (host_name_addresses_map, xstrdup_lower (host), al);

#ifdef DEBUG
  if (opt.debug)
    {
      int i;
      debug_logprintf ("Caching %s =>", host);
      for (i = 0; i < al->count; i++)
	debug_logprintf (" %s",
			 pretty_print_address (ADDR_LOCATION (al, i)));
      debug_logprintf ("\n");
    }
#endif
}

struct address_list *
lookup_host (const char *host, int silent)
{
  struct address_list *al = NULL;
  unsigned long addr;
  struct hostent *hptr;

  /* If the address is of the form d.d.d.d, no further lookup is
     needed.  */
  addr = (unsigned long)inet_addr (host);
  if ((int)addr != -1)
    {
      /* ADDR is defined to be in network byte order, which is what
	 this returns, so we can just copy it to STORE_IP.  However,
	 on big endian 64-bit architectures the value will be stored
	 in the *last*, not first four bytes.  OFFSET makes sure that
	 we copy the correct four bytes.  */
      int offset;
#ifdef WORDS_BIGENDIAN
      offset = sizeof (unsigned long) - IP4_ADDRESS_LENGTH;
#else
      offset = 0;
#endif
      return address_list_new_one ((char *)&addr + offset);
    }

  /* By now we know that the host name we got is not of the form
     d.d.d.d.  Try to find it in our cache of host names.  */
  if (host_name_addresses_map)
    al = hash_table_get (host_name_addresses_map, host);

  if (al)
    {
      DEBUGP (("Found %s in host_name_addresses_map (%p)\n", host, al));
      ++al->refcount;
      return al;
    }

  if (!silent)
    logprintf (LOG_VERBOSE, _("Resolving %s... "), host);

  /* Look up the host using gethostbyname().  */
  hptr = gethostbyname (host);
  if (!hptr)
    {
      if (!silent)
	logprintf (LOG_VERBOSE, _("failed: %s.\n"), herrmsg (h_errno));
      return NULL;
    }

  if (!silent)
    logprintf (LOG_VERBOSE, _("done.\n"));

  /* Do all systems have h_addr_list, or is it a newer thing?  If the
     latter, use address_list_new_one.  */
  al = address_list_new (hptr->h_addr_list);

  /* Cache the lookup information. */
  cache_host_lookup (host, al);

  return al;
}

/* Determine whether a URL is acceptable to be followed, according to
   a list of domains to accept.  */
int
accept_domain (struct url *u)
{
  assert (u->host != NULL);
  if (opt.domains)
    {
      if (!sufmatch ((const char **)opt.domains, u->host))
	return 0;
    }
  if (opt.exclude_domains)
    {
      if (sufmatch ((const char **)opt.exclude_domains, u->host))
	return 0;
    }
  return 1;
}

/* Check whether WHAT is matched in LIST, each element of LIST being a
   pattern to match WHAT against, using backward matching (see
   match_backwards() in utils.c).

   If an element of LIST matched, 1 is returned, 0 otherwise.  */
int
sufmatch (const char **list, const char *what)
{
  int i, j, k, lw;

  lw = strlen (what);
  for (i = 0; list[i]; i++)
    {
      for (j = strlen (list[i]), k = lw; j >= 0 && k >= 0; j--, k--)
	if (TOLOWER (list[i][j]) != TOLOWER (what[k]))
	  break;
      /* The domain must be first to reach to beginning.  */
      if (j == -1)
	return 1;
    }
  return 0;
}

/* Print error messages for host errors.  */
char *
herrmsg (int error)
{
  /* Can't use switch since some constants are equal (at least on my
     system), and the compiler signals "duplicate case value".  */
  if (error == HOST_NOT_FOUND
      || error == NO_RECOVERY
      || error == NO_DATA
      || error == NO_ADDRESS
      || error == TRY_AGAIN)
    return _("Host not found");
  else
    return _("Unknown error");
}

static int
host_cleanup_mapper (void *key, void *value, void *arg_ignored)
{
  struct address_list *al;

  xfree (key);			/* host */

  al = (struct address_list *)value;
  assert (al->refcount == 1);
  address_list_delete (al);

  return 0;
}

void
host_cleanup (void)
{
  if (host_name_addresses_map)
    {
      hash_table_map (host_name_addresses_map, host_cleanup_mapper, NULL);
      hash_table_destroy (host_name_addresses_map);
      host_name_addresses_map = NULL;
    }
}
