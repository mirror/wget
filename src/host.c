/* Dealing with host names.
   Copyright (C) 1995, 1996, 1997, 2000 Free Software Foundation, Inc.

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
# include <arpa/inet.h>
# include <netdb.h>
#endif /* WINDOWS */

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

/* Mapping between all known hosts to their addresses (n.n.n.n). */
struct hash_table *host_name_address_map;

/* Mapping between all known addresses (n.n.n.n) to their hosts.  This
   is the inverse of host_name_address_map.  These two tables share
   the strdup'ed strings. */
struct hash_table *host_address_name_map;

/* Mapping between auxilliary (slave) and master host names. */
struct hash_table *host_slave_master_map;

/* Utility function: like xstrdup(), but also lowercases S.  */

static char *
xstrdup_lower (const char *s)
{
  char *copy = xstrdup (s);
  char *p = copy;
  for (; *p; p++)
    *p = TOLOWER (*p);
  return copy;
}

/* The same as gethostbyname, but supports internet addresses of the
   form `N.N.N.N'.  On some systems gethostbyname() knows how to do
   this automatically.  */
struct hostent *
ngethostbyname (const char *name)
{
  struct hostent *hp;
  unsigned long addr;

  addr = (unsigned long)inet_addr (name);
  if ((int)addr != -1)
    hp = gethostbyaddr ((char *)&addr, sizeof (addr), AF_INET);
  else
    hp = gethostbyname (name);
  return hp;
}

/* Add host name HOST with the address ADDR_TEXT to the cache.
   Normally this means that the (HOST, ADDR_TEXT) pair will be to
   host_name_address_map and to host_address_name_map.  (It is the
   caller's responsibility to make sure that HOST is not already in
   host_name_address_map.)

   If the ADDR_TEXT has already been seen and belongs to another host,
   HOST will be added to host_slave_master_map instead.  */

static void
add_host_to_cache (const char *host, const char *addr_text)
{
  char *canonical_name = hash_table_get (host_address_name_map, addr_text);
  if (canonical_name)
    {
      DEBUGP (("Mapping %s to %s in host_slave_master_map.\n",
	       host, canonical_name));
      /* We've already dealt with that host under another name. */
      hash_table_put (host_slave_master_map,
		      xstrdup_lower (host),
		      xstrdup_lower (canonical_name));
    }
  else
    {
      /* This is really the first time we're dealing with that host.  */
      char *h_copy = xstrdup_lower (host);
      char *a_copy = xstrdup (addr_text);
      DEBUGP (("Caching %s <-> %s\n", h_copy, a_copy));
      hash_table_put (host_name_address_map, h_copy, a_copy);
      hash_table_put (host_address_name_map, a_copy, h_copy);
    }
}

/* Store the address of HOSTNAME, internet-style (four octets in
   network order), to WHERE.  First try to get the address from the
   cache; if it is not available, call the DNS functions and update
   the cache.

   Return 1 on successful finding of the hostname, 0 otherwise.  */
int
store_hostaddress (unsigned char *where, const char *hostname)
{
  unsigned long addr;
  char *addr_text;
  char *canonical_name;
  struct hostent *hptr;
  struct in_addr in;
  char *inet_s;

  /* If the address is of the form d.d.d.d, there will be no trouble
     with it.  */
  addr = (unsigned long)inet_addr (hostname);
  /* If we have the numeric address, just store it.  */
  if ((int)addr != -1)
    {
      /* ADDR is defined to be in network byte order, meaning the code
         works on little and big endian 32-bit architectures without
         change.  On big endian 64-bit architectures we need to be
         careful to copy the correct four bytes.  */
      int offset;
    have_addr:
#ifdef WORDS_BIGENDIAN
      offset = sizeof (unsigned long) - 4;
#else
      offset = 0;
#endif
      memcpy (where, (char *)&addr + offset, 4);
      return 1;
    }

  /* By now we know that the address is not of the form d.d.d.d.  Try
     to find it in our cache of host addresses.  */
  addr_text = hash_table_get (host_name_address_map, hostname);
  if (addr_text)
    {
      DEBUGP (("Found %s in host_name_address_map: %s\n",
	       hostname, addr_text));
      addr = (unsigned long)inet_addr (addr_text);
      goto have_addr;
    }

  /* Maybe this host is known to us under another name.  If so, we'll
     find it in host_slave_master_map, and use the master name to find
     its address in host_name_address_map. */
  canonical_name = hash_table_get (host_slave_master_map, hostname);
  if (canonical_name)
    {
      addr_text = hash_table_get (host_name_address_map, canonical_name);
      assert (addr_text != NULL);
      DEBUGP (("Found %s as slave of %s -> %s\n",
	       hostname, canonical_name, addr_text));
      addr = (unsigned long)inet_addr (addr_text);
      goto have_addr;
    }

  /* Since all else has failed, let's try gethostbyname().  Note that
     we use gethostbyname() rather than ngethostbyname(), because we
     already know that the address is not numerical.  */
  hptr = gethostbyname (hostname);
  if (!hptr)
    return 0;
  /* Copy the address of the host to socket description.  */
  memcpy (where, hptr->h_addr_list[0], hptr->h_length);
  assert (hptr->h_length == 4);

  /* Now that we've gone through the truoble of calling
     gethostbyname(), we can store this valuable information to the
     cache.  First, we have to look for it by address to know if it's
     already in the cache by another name.  */
  /* Originally, we copied to in.s_addr, but it appears to be missing
     on some systems.  */
  memcpy (&in, *hptr->h_addr_list, sizeof (in));
  inet_s = inet_ntoa (in);
  add_host_to_cache (hostname, inet_s);
  return 1;
}

/* Determine the "real" name of HOST, as perceived by Wget.  If HOST
   is referenced by more than one name, "real" name is considered to
   be the first one encountered in the past.  */
char *
realhost (const char *host)
{
  struct in_addr in;
  struct hostent *hptr;
  char *master_name;

  DEBUGP (("Checking for %s in host_name_address_map.\n", host));
  if (hash_table_contains (host_name_address_map, host))
    {
      DEBUGP (("Found; %s was already used, by that name.\n", host));
      return xstrdup_lower (host);
    }

  DEBUGP (("Checking for %s in host_slave_master_map.\n", host));
  master_name = hash_table_get (host_slave_master_map, host);
  if (master_name)
    {
    has_master:
      DEBUGP (("Found; %s was already used, by the name %s.\n",
	       host, master_name));
      return xstrdup (master_name);
    }

  DEBUGP (("First time I hear about %s by that name; looking it up.\n",
	   host));
  hptr = ngethostbyname (host);
  if (hptr)
    {
      char *inet_s;
      /* Originally, we copied to in.s_addr, but it appears to be
	 missing on some systems.  */
      memcpy (&in, *hptr->h_addr_list, sizeof (in));
      inet_s = inet_ntoa (in);

      add_host_to_cache (host, inet_s);

      /* add_host_to_cache() can establish a slave-master mapping. */
      DEBUGP (("Checking again for %s in host_slave_master_map.\n", host));
      master_name = hash_table_get (host_slave_master_map, host);
      if (master_name)
	goto has_master;
    }

  return xstrdup_lower (host);
}

/* Compare two hostnames (out of URL-s if the arguments are URL-s),
   taking care of aliases.  It uses realhost() to determine a unique
   hostname for each of two hosts.  If simple_check is non-zero, only
   strcmp() is used for comparison.  */
int
same_host (const char *u1, const char *u2)
{
  const char *s;
  char *p1, *p2;
  char *real1, *real2;

  /* Skip protocol, if present.  */
  u1 += skip_proto (u1);
  u2 += skip_proto (u2);

  /* Skip username ans password, if present.  */
  u1 += skip_uname (u1);
  u2 += skip_uname (u2);

  for (s = u1; *u1 && *u1 != '/' && *u1 != ':'; u1++);
  p1 = strdupdelim (s, u1);
  for (s = u2; *u2 && *u2 != '/' && *u2 != ':'; u2++);
  p2 = strdupdelim (s, u2);
  DEBUGP (("Comparing hosts %s and %s...\n", p1, p2));
  if (strcasecmp (p1, p2) == 0)
    {
      xfree (p1);
      xfree (p2);
      DEBUGP (("They are quite alike.\n"));
      return 1;
    }
  else if (opt.simple_check)
    {
      xfree (p1);
      xfree (p2);
      DEBUGP (("Since checking is simple, I'd say they are not the same.\n"));
      return 0;
    }
  real1 = realhost (p1);
  real2 = realhost (p2);
  xfree (p1);
  xfree (p2);
  if (strcasecmp (real1, real2) == 0)
    {
      DEBUGP (("They are alike, after realhost()->%s.\n", real1));
      xfree (real1);
      xfree (real2);
      return 1;
    }
  else
    {
      DEBUGP (("They are not the same (%s, %s).\n", real1, real2));
      xfree (real1);
      xfree (real2);
      return 0;
    }
}

/* Determine whether a URL is acceptable to be followed, according to
   a list of domains to accept.  */
int
accept_domain (struct urlinfo *u)
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

void
clean_hosts (void)
{
  /* host_name_address_map and host_address_name_map share the
     strings.  Because of that, calling free_keys_and_values once
     suffices for both.  */
  free_keys_and_values (host_name_address_map);
  hash_table_destroy (host_name_address_map);
  hash_table_destroy (host_address_name_map);
  free_keys_and_values (host_slave_master_map);
  hash_table_destroy (host_slave_master_map);
}

void
host_init (void)
{
  host_name_address_map = make_string_hash_table (0);
  host_address_name_map = make_string_hash_table (0);
  host_slave_master_map = make_string_hash_table (0);
}
