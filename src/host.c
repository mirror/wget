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

#ifndef WINDOWS
#include <netdb.h>
#endif

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
# define SET_H_ERRNO(err) WSASetLastError (err)
#else
# include <sys/socket.h>
# include <netinet/in.h>
# ifndef __BEOS__
#  include <arpa/inet.h>
# endif
# include <netdb.h>
# define SET_H_ERRNO(err) ((void)(h_errno = (err)))
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

#ifdef ENABLE_IPV6
int ip_default_family = AF_UNSPEC;
#else
int ip_default_family = AF_INET;
#endif

/* Mapping between known hosts and to lists of their addresses. */

static struct hash_table *host_name_addresses_map;

/* Lists of addresses.  This should eventually be extended to handle
   IPv6.  */

struct address_list {
  int count;			/* number of adrresses */
  ip_address *addresses;	/* pointer to the string of addresses */

  int faulty;			/* number of addresses known not to work. */
  int refcount;			/* so we know whether to free it or not. */
};

/* Get the bounds of the address list.  */

void
address_list_get_bounds (const struct address_list *al, int *start, int *end)
{
  *start = al->faulty;
  *end   = al->count;
}

/* Copy address number INDEX to IP_STORE.  */

void
address_list_copy_one (const struct address_list *al, int index, ip_address *ip_store)
{
  assert (index >= al->faulty && index < al->count);
  memcpy (ip_store, al->addresses + index, sizeof (ip_address));
}

/* Check whether two address lists have all their IPs in common.  */

int
address_list_match_all (const struct address_list *al1, const struct address_list *al2)
{
  int i;
  if (al1 == al2)
    return 1;
  if (al1->count != al2->count)
    return 0;
  for (i = 0; i < al1->count; ++i) 
    {
#ifdef ENABLE_IPv6
      if (al1->addresses[i].type != al2->addresses[i].type) 
	return 0;
      if (al1->addresses[i].type == IPv6_ADDRESS)
	{
	  const struct in6_addr *addr1 = &al1->addresses[i].addr.ipv6.addr;
	  const struct in6_addr *addr2 = &al2->addresses[i].addr.ipv6.addr;

#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
	  if ((al1->addresses[i].address.scope_id
	       != al2->addresses[i].address.scope_id)
	      || !IN6_ARE_ADDR_EQUAL (addr1, addr2))
#else
	  if (!IN6_ARE_ADDR_EQUAL (addr1, addr2))
#endif
	    return 0;
	}
      else
#endif
	{
	  const struct in_addr *addr1 = (const struct in_addr *)&al1->addresses[i].addr.ipv4.addr;
	  const struct in_addr *addr2 = (const struct in_addr *)&al2->addresses[i].addr.ipv4.addr;
	  
	  if (addr1->s_addr != addr2->s_addr)
	    return 0;
	}
    }
  return 1;
}

/* Mark the INDEXth element of AL as faulty, so that the next time
   this address list is used, the faulty element will be skipped.  */

void
address_list_set_faulty (struct address_list *al, int index)
{
  /* We assume that the address list is traversed in order, so that a
     "faulty" attempt is always preceded with all-faulty addresses,
     and this is how Wget uses it.  */
  assert (index == al->faulty);

  ++al->faulty;
  if (al->faulty >= al->count)
    /* All addresses have been proven faulty.  Since there's not much
       sense in returning the user an empty address list the next
       time, we'll rather make them all clean, so that they can be
       retried anew.  */
    al->faulty = 0;
}

#ifdef ENABLE_IPV6
/**
  * address_list_from_addrinfo
  *
  * This function transform an addrinfo links list in and address_list.
  *
  * Input:
  * addrinfo*		Linkt list of addrinfo
  *
  * Output:
  * address_list*	New allocated address_list
  */
static struct address_list *
address_list_from_addrinfo (const struct addrinfo *ai)
{
  struct address_list *al;
  const struct addrinfo *ptr;
  int cnt = 0;
  int i;

  for (ptr = ai; ptr != NULL ; ptr = ptr->ai_next)
    if (ptr->ai_family == AF_INET || ptr->ai_family == AF_INET6)
      ++cnt;
  if (cnt == 0)
    return NULL;

  al = xmalloc (sizeof (struct address_list));
  al->addresses = xmalloc (cnt * sizeof (ip_address));
  al->count     = cnt;
  al->faulty    = 0;
  al->refcount  = 1;

  for (i = 0, ptr = ai; ptr != NULL; ptr = ptr->ai_next)
    if (ptr->ai_family == AF_INET6) 
      {
	const struct sockaddr_in6 *sin6 =
	  (const struct sockaddr_in6 *)ptr->ai_addr;
	al->addresses[i].addr.ipv6.addr = sin6->sin6_addr;
	al->addresses[i].type = IPv6_ADDRESS;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
	al->addresses[i].addr.ipv6.scope_id = sin6->sin6_scope_id;
#endif
	++i;
      } 
    else if (ptr->ai_family == AF_INET)
      {
	const struct sockaddr_in *sin =
	  (const struct sockaddr_in *)ptr->ai_addr;
	al->addresses[i].addr.ipv4.addr = sin->sin_addr;
	al->addresses[i].type = IPv4_ADDRESS;
	++i;
      }
  assert (i == cnt);
  return al;
}
#else
/* Create an address_list out of a NULL-terminated vector of
   addresses, as returned by gethostbyname.  */
static struct address_list *
address_list_from_vector (char **h_addr_list)
{
  int count = 0, i;

  struct address_list *al = xmalloc (sizeof (struct address_list));

  while (h_addr_list[count])
    ++count;
  assert (count > 0);
  al->count     = count;
  al->faulty    = 0;
  al->addresses = xmalloc (count * sizeof (ip_address));
  al->refcount  = 1;

  for (i = 0; i < count; i++) {
    /* Mauro Tortonesi: is this safe? */
    memcpy (&((al->addresses + i)->addr.ipv4.addr.s_addr), h_addr_list[i], 4);
    (al->addresses + i)->type = IPv4_ADDRESS;
  }

  return al;
}

/* Like address_list_from_vector, but initialized with a single
   address. */

static struct address_list *
address_list_from_single (const ip_address *addr)
{
  struct address_list *al = xmalloc (sizeof (struct address_list));
  al->count     = 1;
  al->faulty    = 0;
  al->addresses = xmalloc (sizeof (ip_address));
  al->refcount  = 1;
  memcpy (al->addresses, addr, sizeof (ip_address));

  return al;
}
#endif

static void
address_list_delete (struct address_list *al)
{
  xfree (al->addresses);
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

/**
  * sockaddr_set_address
  *
  * This function takes a sockaddr struct and fills in the protocol type,
  * the port number and the address. If ENABLE_IPV6 is defined, the sa
  * parameter should point to a sockaddr_storage structure; if not, it 
  * should point to a sockaddr_in structure.
  * If the address parameter is NULL, the function will use the unspecified 
  * address (0.0.0.0 for IPv4 and :: for IPv6). 
  * Unsupported address family will abort the whole programm.
  *
  * Input:
  * struct sockaddr*	The space to be filled
  * unsigned short	The port
  * const ip_address	The IP address
  *
  * Return:
  * -			Only modifies 1st parameter.
  */
void
sockaddr_set_address (struct sockaddr *sa, unsigned short port, 
		      const ip_address *addr)
{
  if (addr->type == IPv4_ADDRESS)
    {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;

      sin->sin_family = AF_INET;
      sin->sin_port = htons (port);
      if (addr == NULL) 
	sin->sin_addr.s_addr = INADDR_ANY;
      else
	sin->sin_addr = addr->addr.ipv4.addr;
    }
#ifdef ENABLE_IPV6
  else if (addr->type == IPv6_ADDRESS) 
    {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

      sin6->sin6_family = AF_INET6;
      sin6->sin6_port = htons (port);
      if (addr == NULL) 
	sin6->sin6_addr = in6addr_any;
      else
	sin6->sin6_addr = addr->addr.ipv6.addr;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
      sin6->sin6_scope_id = addr->addr.ipv6.scope_id;
#endif /* HAVE_SOCKADDR_IN6_SCOPE_ID */
    }
#endif /* ENABLE_IPV6 */
  else
    abort ();
}

void
sockaddr_get_address (const struct sockaddr *sa, unsigned short *port, 
		      ip_address *addr)
{
  if (sa->sa_family == AF_INET)
    {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;

      addr->type = IPv4_ADDRESS;
      addr->addr.ipv4.addr = sin->sin_addr;
      if (port != NULL) 
	*port = ntohs (sin->sin_port);
    }
#ifdef ENABLE_IPV6
  else if (sa->sa_family == AF_INET6) 
    {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

      addr->type = IPv6_ADDRESS;
      addr->addr.ipv6.addr = sin6->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
      addr->addr.ipv6.scope_id = sin6->sin6_scope_id;
#endif  
      if (port != NULL) 
	*port = ntohs (sin6->sin6_port);
    }
#endif  
  else
    abort ();
}

#if 0				/* currently unused */
/**
  * sockaddr_set_port
  *
  * This funtion only fill the port of the socket information.
  * If the protocol is not supported nothing is done.
  * Unsuported adress family will abort the whole programm.
  * 
  * Require:
  * that the IP-Protocol already is set.
  *
  * Input:
  * wget_sockaddr*	The space there port should be entered
  * unsigned int	The port that should be entered in host order
  *
  * Return:
  * -			Only modify 1. param
  */
void 
sockaddr_set_port (struct sockaddr *sa, unsigned short port)
{
  if (sa->sa_family == AF_INET)
    {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;
      sin->sin_port = htons (port);
    }  
#ifdef ENABLE_IPV6
  else if (sa->sa_family == AF_INET6)
    {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
      sin6->sin6_port = htons (port);
    }
#endif
  else
    abort ();
}
#endif

/**
  * sockaddr_get_port
  *
  * This function only return the port from the input structure
  * Unsuported adress family will abort the whole programm.
  * 
  * Require:
  * that the IP-Protocol already is set.
  *
  * Input:
  * wget_sockaddr*	Information where to get the port
  *
  * Output:
  * unsigned short	Port Number in host order.
  */
unsigned short 
sockaddr_get_port (const struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
      const struct sockaddr_in *sin = (const struct sockaddr_in *)sa;
      return htons (sin->sin_port);
#ifdef ENABLE_IPV6
  } else if (sa->sa_family == AF_INET6) {
      const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sa;
      return htons (sin6->sin6_port);
#endif
  } else
    abort ();
  /* do not complain about return nothing */
  return -1;
}

/**
  * sockaddr_len
  *
  * This function return the length of the sockaddr corresponding to 
  * the acutall prefered protocol for (bind, connect etc...)
  * Unsuported adress family will abort the whole programm.
  * 
  * Require:
  * that the IP-Protocol already is set.
  *
  * Input:
  * -		Public IP-Family Information
  *
  * Output:
  * int		structure length for socket options
  */
socklen_t
sockaddr_len (const struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    {
      return sizeof (struct sockaddr_in);
    }  
#ifdef ENABLE_IPV6
  else if (sa->sa_family == AF_INET6)
    {
      return sizeof (struct sockaddr_in6);
    }
#endif
  else
    abort ();
  /* do not complain about return nothing */
  return 0;
}

/* Versions of gethostbyname and getaddrinfo that support timeout. */

#ifndef ENABLE_IPV6

struct ghbnwt_context {
  const char *host_name;
  struct hostent *hptr;
};

static void
gethostbyname_with_timeout_callback (void *arg)
{
  struct ghbnwt_context *ctx = (struct ghbnwt_context *)arg;
  ctx->hptr = gethostbyname (ctx->host_name);
}

/* Just like gethostbyname, except it times out after TIMEOUT seconds.
   In case of timeout, NULL is returned and errno is set to ETIMEDOUT.
   The function makes sure that when NULL is returned for reasons
   other than timeout, errno is reset.  */

static struct hostent *
gethostbyname_with_timeout (const char *host_name, double timeout)
{
  struct ghbnwt_context ctx;
  ctx.host_name = host_name;
  if (run_with_timeout (timeout, gethostbyname_with_timeout_callback, &ctx))
    {
      SET_H_ERRNO (HOST_NOT_FOUND);
      errno = ETIMEDOUT;
      return NULL;
    }
  if (!ctx.hptr)
    errno = 0;
  return ctx.hptr;
}

#else  /* ENABLE_IPV6 */

struct gaiwt_context {
  const char *node;
  const char *service;
  const struct addrinfo *hints;
  struct addrinfo **res;
  int exit_code;
};

static void
getaddrinfo_with_timeout_callback (void *arg)
{
  struct gaiwt_context *ctx = (struct gaiwt_context *)arg;
  ctx->exit_code = getaddrinfo (ctx->node, ctx->service, ctx->hints, ctx->res);
}

/* Just like getaddrinfo, except it times out after TIMEOUT seconds.
   In case of timeout, the EAI_SYSTEM error code is returned and errno
   is set to ETIMEDOUT.  */

static int
getaddrinfo_with_timeout (const char *node, const char *service,
			  const struct addrinfo *hints, struct addrinfo **res,
			  double timeout)
{
  struct gaiwt_context ctx;
  ctx.node = node;
  ctx.service = service;
  ctx.hints = hints;
  ctx.res = res;

  if (run_with_timeout (timeout, getaddrinfo_with_timeout_callback, &ctx))
    {
      errno = ETIMEDOUT;
      return EAI_SYSTEM;
    }
  return ctx.exit_code;
}

#endif /* ENABLE_IPV6 */

/* Pretty-print ADDR.  When compiled without IPv6, this is the same as
   inet_ntoa.  With IPv6, it either prints an IPv6 address or an IPv4
   address.  */

const char *
pretty_print_address (const ip_address *addr)
{
  switch (addr->type) 
    {
    case IPv4_ADDRESS:
      return inet_ntoa (addr->addr.ipv4.addr);
#ifdef ENABLE_IPV6
    case IPv6_ADDRESS:
      {
        int len;
        static char buf[128];
	inet_ntop (AF_INET6, &addr->addr.ipv6.addr, buf, sizeof (buf));
#if 0
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
        /* print also scope_id for all ?non-global? addresses */
        snprintf (buf + len, sizeof (buf) - len, "%%%d", addr->addr.ipv6.scope_id);
#endif
#endif
        len = strlen (buf);
        buf[sizeof (buf) - 1] = '\0';
        return buf;
      }
#endif
    }
  abort ();
  return NULL;
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

#ifdef ENABLE_DEBUG
  if (opt.debug)
    {
      int i;
      debug_logprintf ("Caching %s =>", host);
      for (i = 0; i < al->count; i++)
	debug_logprintf (" %s", pretty_print_address (al->addresses + i));
      debug_logprintf ("\n");
    }
#endif
}

struct address_list *
lookup_host (const char *host, int flags)
{
  struct address_list *al = NULL;

#ifdef ENABLE_IPV6
  int err, family;
  struct addrinfo hints, *res;

  /* This ip_default_family+flags business looks like bad design to
     me.  This function should rather accept a FAMILY argument.  */
  if (flags & LH_IPv4_ONLY)
    family = AF_INET;
  else if (flags & LH_IPv6_ONLY)
    family = AF_INET6;
  else
    family = ip_default_family;
#endif
	  
  /* First, try to check whether the address is already a numeric
     address.  Where getaddrinfo is available, we do it using the
     AI_NUMERICHOST flag.  Without IPv6, we check whether inet_addr
     succeeds.  */

#ifdef ENABLE_IPV6
  memset (&hints, 0, sizeof (hints));
  hints.ai_family   = family;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_NUMERICHOST;
  if (flags & LH_PASSIVE)
    hints.ai_flags = AI_PASSIVE;

  /* no need to call getaddrinfo_with_timeout here, as we're not
   * relying on the DNS, but we're only doing an address translation
   * from presentation (ASCII) to network format */
  err = getaddrinfo (host, NULL, &hints, &res);
  if (err == 0 && res != NULL)
    {
      al = address_list_from_addrinfo (res);
      freeaddrinfo (res);
      return al;
    }
#else
  {
    uint32_t addr_ipv4 = (uint32_t)inet_addr (host);
    if (addr_ipv4 != (uint32_t) -1)
      {
	/* The return value of inet_addr is in network byte order, so
	   we can just copy it to ADDR.  */
	ip_address addr;
	/* This has a huge number of dereferences because C doesn't
	   support anonymous unions and because struct in_addr adds a
	   cast.  */
	addr.addr.ipv4.addr.s_addr = addr_ipv4;
	addr.type = IPv4_ADDRESS;
	return address_list_from_single (&addr);
      }
  }
#endif

  /* Then, try to find the host in the cache. */

  if (host_name_addresses_map)
    {
      al = hash_table_get (host_name_addresses_map, host);
      if (al)
	{
	  DEBUGP (("Found %s in host_name_addresses_map (%p)\n", host, al));
	  ++al->refcount;
	  return al;
	}
    }

  if (!(flags & LH_SILENT))
    logprintf (LOG_VERBOSE, _("Resolving %s... "), host);

  /* Host name lookup goes on below. */

#ifdef ENABLE_IPV6
  {
    memset (&hints, 0, sizeof (hints));
    hints.ai_family   = family;
    hints.ai_socktype = SOCK_STREAM;
    if (flags & LH_PASSIVE) 
      hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo_with_timeout (host, NULL, &hints, &res, opt.dns_timeout);

    if (err != 0 || res == NULL)
      {
        if (!(flags & LH_SILENT))
	  logprintf (LOG_VERBOSE, _("failed: %s.\n"),
		     err != EAI_SYSTEM ? gai_strerror (err) : strerror (errno));
        return NULL;
      }
    al = address_list_from_addrinfo (res);
    freeaddrinfo (res);
  }
#else
  {
    struct hostent *hptr = gethostbyname_with_timeout (host, opt.dns_timeout);
    if (!hptr)
      {
	if (!(flags & LH_SILENT))
	  {
	    if (errno != ETIMEDOUT)
	      logprintf (LOG_VERBOSE, _("failed: %s.\n"), herrmsg (h_errno));
	    else
	      logputs (LOG_VERBOSE, _("failed: timed out.\n"));
	  }
	return NULL;
      }
    assert (hptr->h_length == 4);
    /* Do all systems have h_addr_list, or is it a newer thing?  If
       the latter, use address_list_from_single.  */
    al = address_list_from_vector (hptr->h_addr_list);
  }
#endif

  /* Print the addresses determined by DNS lookup, but no more than
     three.  */
  if (!(flags & LH_SILENT))
    {
      int i;
      int printmax = al->count <= 3 ? al->count : 3;
      for (i = 0; i < printmax; i++)
	{
	  logprintf (LOG_VERBOSE, "%s",
		     pretty_print_address (al->addresses + i));
	  if (i < printmax - 1)
	    logputs (LOG_VERBOSE, ", ");
	}
      if (printmax != al->count)
	logputs (LOG_VERBOSE, ", ...");
      logputs (LOG_VERBOSE, "\n");
    }

  /* Cache the lookup information. */
  if (opt.dns_cache)
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
