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
# define SET_H_ERRNO(err) WSASetLastError(err)
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
int     ip_default_family = AF_INET6;
#else
int     ip_default_family = AF_INET;
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
address_list_get_bounds (struct address_list *al, int *start, int *end)
{
  *start = al->faulty;
  *end   = al->count;
}

/* Copy address number INDEX to IP_STORE.  */

void
address_list_copy_one (struct address_list *al, int index, ip_address *ip_store)
{
  assert (index >= al->faulty && index < al->count);
  memcpy (ip_store, al->addresses + index, sizeof (ip_address));
}

/* Check whether two address lists have all their IPs in common.  */

int
address_list_match_all (struct address_list *al1, struct address_list *al2)
{
  if (al1 == al2)
    return 1;
  if (al1->count != al2->count)
    return 0;
  return 0 == memcmp (al1->addresses, al2->addresses,
		      al1->count * sizeof (ip_address));
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

#ifdef HAVE_GETADDRINFO
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
address_list_from_addrinfo (struct addrinfo *ai)
{
  struct address_list *al;
  struct addrinfo *ai_head = ai;
  int cnt = 0;
  int i;

  for (ai = ai_head; ai; ai = ai->ai_next)
    if (ai->ai_family == AF_INET || ai->ai_family == AF_INET6)
      ++cnt;
  if (cnt == 0)
    return NULL;

  al = xmalloc (sizeof (struct address_list));
  al->addresses = xmalloc (cnt * sizeof (ip_address));
  al->count     = cnt;
  al->faulty    = 0;
  al->refcount  = 1;

  for (i = 0, ai = ai_head; ai; ai = ai->ai_next)
    if (ai->ai_family == AF_INET6) 
      {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)ai->ai_addr;
	memcpy (al->addresses + i, &sin6->sin6_addr, 16);
	++i;
      } 
    else if (ai->ai_family == AF_INET)
      {
	struct sockaddr_in *sin = (struct sockaddr_in *)ai->ai_addr;
        map_ipv4_to_ip ((ip4_address *)&sin->sin_addr, al->addresses + i);
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

  for (i = 0; i < count; i++)
    map_ipv4_to_ip ((ip4_address *)h_addr_list[i], al->addresses + i);

  return al;
}
#endif

/* Like address_list_from_vector, but initialized with a single
   address. */

static struct address_list *
address_list_from_single (ip_address *addr)
{
  struct address_list *al = xmalloc (sizeof (struct address_list));
  al->count     = 1;
  al->faulty    = 0;
  al->addresses = xmalloc (sizeof (ip_address));
  al->refcount  = 1;
  memcpy (al->addresses, addr, sizeof (ip_address));

  return al;
}

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
  * wget_sockaddr_set_address
  *
  * This function takes an wget_sockaddr and fill in the protocol type,
  * the port number and the address, there NULL in address means wildcard.
  * Unsuported adress family will abort the whole programm.
  *
  * Input:
  * wget_sockaddr*	The space to be filled
  * int			The wished protocol
  * unsigned short	The port
  * const ip_address	The Binary IP adress
  *
  * Return:
  * -			Only modify 1. param
  */
void
wget_sockaddr_set_address (wget_sockaddr *sa, 
			   int ip_family, unsigned short port, ip_address *addr)
{
  if (ip_family == AF_INET) 
    {
      sa->sin.sin_family = ip_family;
      sa->sin.sin_port = htons (port);
      if (addr == NULL) 
	memset (&sa->sin.sin_addr, 0,      sizeof(ip4_address));
      else
	{
	  ip4_address addr4;
	  if (!map_ip_to_ipv4 (addr, &addr4))
	    /* should the callers have prevented this? */
	    abort ();
	  memcpy (&sa->sin.sin_addr, &addr4, sizeof(ip4_address));
	}
      return;
    }
#ifdef ENABLE_IPV6
  if (ip_family == AF_INET6) 
    {
      sa->sin6.sin6_family = ip_family;
      sa->sin6.sin6_port = htons (port);
      if (addr == NULL) 
	memset (&sa->sin6.sin6_addr, 0   , 16);
      else	     
	memcpy (&sa->sin6.sin6_addr, addr, 16);
      return;
    }
#endif  
  abort();
}

/**
  * wget_sockaddr_set_port
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
wget_sockaddr_set_port (wget_sockaddr *sa, unsigned short port)
{
  if (sa->sa.sa_family == AF_INET)
    {
      sa->sin.sin_port = htons (port);
      return;
    }  
#ifdef ENABLE_IPV6
  if (sa->sa.sa_family == AF_INET6)
    {
      sa->sin6.sin6_port = htons (port);
      return;
    }
#endif
  abort();
}

/**
  * wget_sockaddr_get_addr
  *
  * This function return the adress from an sockaddr as byte string.
  * Unsuported adress family will abort the whole programm.
  * 
  * Require:
  * that the IP-Protocol already is set.
  *
  * Input:
  * wget_sockaddr*	Socket Information
  *
  * Output:
  * unsigned char *	IP address as byte string.
  */
void *
wget_sockaddr_get_addr (wget_sockaddr *sa)
{ 
  if (sa->sa.sa_family == AF_INET)
    return &sa->sin.sin_addr;
#ifdef ENABLE_IPV6
  if (sa->sa.sa_family == AF_INET6)
    return &sa->sin6.sin6_addr;
#endif
  abort();
  /* unreached */
  return NULL;
}

/**
  * wget_sockaddr_get_port
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
wget_sockaddr_get_port (const wget_sockaddr *sa)
{
  if (sa->sa.sa_family == AF_INET)
      return htons (sa->sin.sin_port);
#ifdef ENABLE_IPV6
  if (sa->sa.sa_family == AF_INET6)
      return htons (sa->sin6.sin6_port);
#endif
  abort();
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
  * socklen_t	structure length for socket options
  */
socklen_t
sockaddr_len () 
{
  if (ip_default_family == AF_INET) 
    return sizeof (struct sockaddr_in);
#ifdef ENABLE_IPV6
  if (ip_default_family == AF_INET6) 
    return sizeof (struct sockaddr_in6);
#endif
  abort();
  /* do not complain about return nothing */
  return 0;
}

/**
  * Map an IPv4 adress to the internal adress format.
  */
void 
map_ipv4_to_ip (ip4_address *ipv4, ip_address *ip) 
{
#ifdef ENABLE_IPV6
  static unsigned char ipv64[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xff};
  memcpy ((char *)ip + 12, ipv4 , 4);
  memcpy ((char *)ip + 0, ipv64, 12);
#else
  if ((char *)ip != (char *)ipv4)
    memcpy (ip, ipv4, 4);
#endif
}

/* Detect whether an IP adress represents an IPv4 address and, if so,
   copy it to IPV4.  0 is returned on failure.
   This operation always succeeds when Wget is compiled without IPv6.
   If IPV4 is NULL, don't copy, just detect.  */

int 
map_ip_to_ipv4 (ip_address *ip, ip4_address *ipv4) 
{
#ifdef ENABLE_IPV6
  static unsigned char ipv64[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xff};
  if (0 != memcmp (ip, ipv64, 12))
    return 0;
  if (ipv4)
    memcpy (ipv4, (char *)ip + 12, 4);
#else
  if (ipv4)
    memcpy (ipv4, (char *)ip, 4);
#endif
  return 1;
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

char *
pretty_print_address (ip_address *addr)
{
#ifdef ENABLE_IPV6
  ip4_address addr4;
  static char buf[128];

  if (map_ip_to_ipv4 (addr, &addr4))
    return inet_ntoa (*(struct in_addr *)&addr4);

  if (!inet_ntop (AF_INET6, addr, buf, sizeof (buf)))
    return "<unknown>";
  return buf;
#endif
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
lookup_host (const char *host, int silent)
{
  struct address_list *al = NULL;
  u_int32_t addr_ipv4;
  ip_address addr;

  /* First, try to check whether the address is already a numeric
     address.  */

#ifdef ENABLE_IPV6
  if (inet_pton (AF_INET6, host, &addr) > 0)
    return address_list_from_single (&addr);
#endif

  addr_ipv4 = (u_int32_t)inet_addr (host);
  if (addr_ipv4 != (u_int32_t)-1)
    {
      /* ADDR is defined to be in network byte order, which is what
	 this returns, so we can just copy it to STORE_IP.  */
      map_ipv4_to_ip ((ip4_address *)&addr_ipv4, &addr);
      return address_list_from_single (&addr);
    }

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

  if (!silent)
    logprintf (LOG_VERBOSE, _("Resolving %s... "), host);

  /* Host name lookup goes on below. */

#ifdef HAVE_GETADDRINFO
  {
    struct addrinfo hints, *ai;
    int err;

    memset (&hints, 0, sizeof (hints));
    if (ip_default_family == AF_INET)
      hints.ai_family   = AF_INET;
    else
      hints.ai_family   = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo_with_timeout (host, NULL, &hints, &ai, opt.dns_timeout);

    if (err != 0 || ai == NULL)
      {
        if (!silent)
	  logprintf (LOG_VERBOSE, _("failed: %s.\n"),
		     err != EAI_SYSTEM ? gai_strerror (err) : strerror (errno));
        return NULL;
      }
    al = address_list_from_addrinfo (ai);
    freeaddrinfo (ai);
  }
#else
  {
    struct hostent *hptr;
    hptr = gethostbyname_with_timeout (host, opt.dns_timeout);
    if (!hptr)
      {
	if (!silent)
	  {
	    if (errno != ETIMEDOUT)
	      logprintf (LOG_VERBOSE, _("failed: %s.\n"), herrmsg (h_errno));
	    else
	      logputs (LOG_VERBOSE, _("failed: timed out.\n"));
	  }
	return NULL;
      }
    /* Do all systems have h_addr_list, or is it a newer thing?  If
       the latter, use address_list_from_single.  */
    al = address_list_from_vector (hptr->h_addr_list);
  }
#endif

  /* Print the addresses determined by DNS lookup, but no more than
     three.  */
  if (!silent)
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
