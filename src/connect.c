/* Establishing and handling network connections.
   Copyright (C) 1995, 1996, 1997, 2001, 2002 Free Software Foundation, Inc.

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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <assert.h>

#ifndef WINDOWS
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# ifndef __BEOS__
#  include <arpa/inet.h>
# endif
#endif /* not WINDOWS */

#include <errno.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_SYS_SELECT_H
# include <sys/select.h>
#endif /* HAVE_SYS_SELECT_H */

#include "wget.h"
#include "utils.h"
#include "host.h"
#include "connect.h"

#ifndef errno
extern int errno;
#endif


/* Fill SA as per the data in IP and PORT.  SA shoult point to struct
   sockaddr_storage if ENABLE_IPV6 is defined, to struct sockaddr_in
   otherwise.  */

static void
sockaddr_set_data (struct sockaddr *sa, const ip_address *ip, int port)
{
  switch (ip->type)
    {
    case IPV4_ADDRESS:
      {
	struct sockaddr_in *sin = (struct sockaddr_in *)sa;
	sin->sin_family = AF_INET;
	sin->sin_port = htons (port);
	sin->sin_addr = ADDRESS_IPV4_IN_ADDR (ip);
	break;
      }
#ifdef ENABLE_IPV6
    case IPV6_ADDRESS:
      {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
	sin6->sin6_family = AF_INET6;
	sin6->sin6_port = htons (port);
	sin6->sin6_addr = ADDRESS_IPV6_IN6_ADDR (ip);
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
	sin6->sin6_scope_id = ADDRESS_IPV6_SCOPE (ip);
#endif
	break;
      }
#endif /* ENABLE_IPV6 */
    default:
      abort ();
    }
}

/* Get the data of SA, specifically the IP address and the port.  If
   you're not interested in one or the other information, pass NULL as
   the pointer.  */

void
sockaddr_get_data (const struct sockaddr *sa, ip_address *ip, int *port)
{
  switch (sa->sa_family)
    {
    case AF_INET:
      {
	struct sockaddr_in *sin = (struct sockaddr_in *)sa;
	if (ip)
	  {
	    ip->type = IPV4_ADDRESS;
	    ADDRESS_IPV4_IN_ADDR (ip) = sin->sin_addr;
	  }
	if (port)
	  *port = ntohs (sin->sin_port);
	break;
      }
#ifdef ENABLE_IPV6
    case AF_INET6:
      {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
	if (ip)
	  {
	    ip->type = IPV6_ADDRESS;
	    ADDRESS_IPV6_IN6_ADDR (ip) = sin6->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
	    ADDRESS_IPV6_SCOPE (ip) = sin6->sin6_scope_id;
#endif
	  }
	if (port)
	  *port = ntohs (sin6->sin6_port);
	break;
      }
#endif
    default:
      abort ();
    }
}

/* Return the size of the sockaddr structure depending on its
   family.  */

static socklen_t
sockaddr_size (const struct sockaddr *sa)
{
  switch (sa->sa_family)
    {
    case AF_INET:
      return sizeof (struct sockaddr_in);
#ifdef ENABLE_IPV6
    case AF_INET6:
      return sizeof (struct sockaddr_in6);
#endif
    default:
      abort ();
      return 0;			/* so the compiler shuts up. */
    }
}

static int
resolve_bind_address (const char *host, struct sockaddr *sa, int flags)
{
  struct address_list *al;

  /* #### Shouldn't we do this only once?  opt.bind_address won't
     change during a Wget run!  */

  al = lookup_host (host, flags | LH_SILENT | LH_PASSIVE);
  if (al == NULL)
    {
      logprintf (LOG_NOTQUIET,
		 _("Unable to convert `%s' to a bind address.  Reverting to ANY.\n"),
		 opt.bind_address);
      return 0;
    }

  /* Pick the first address in the list and use it as bind address.
     Perhaps we should try multiple addresses, but I don't think
     that's necessary in practice.  */
  sockaddr_set_data (sa, address_list_address_at (al, 0), 0);
  address_list_release (al);
  return 1;
}

struct cwt_context {
  int fd;
  const struct sockaddr *addr;
  socklen_t addrlen;
  int result;
};

static void
connect_with_timeout_callback (void *arg)
{
  struct cwt_context *ctx = (struct cwt_context *)arg;
  ctx->result = connect (ctx->fd, ctx->addr, ctx->addrlen);
}

/* Like connect, but specifies a timeout.  If connecting takes longer
   than TIMEOUT seconds, -1 is returned and errno is set to
   ETIMEDOUT.  */

static int
connect_with_timeout (int fd, const struct sockaddr *addr, socklen_t addrlen,
		      double timeout)
{
  struct cwt_context ctx;
  ctx.fd = fd;
  ctx.addr = addr;
  ctx.addrlen = addrlen;

  if (run_with_timeout (timeout, connect_with_timeout_callback, &ctx))
    {
      errno = ETIMEDOUT;
      return -1;
    }
  if (ctx.result == -1 && errno == EINTR)
    errno = ETIMEDOUT;
  return ctx.result;
}

/* Connect to a remote endpoint whose IP address is known.  */

int
connect_to_ip (const ip_address *ip, int port, const char *print)
{
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;
  int sock, save_errno;

  /* If PRINT is non-NULL, print the "Connecting to..." line, with
     PRINT being the host name we're connecting to.  */
  if (print)
    {
      const char *txt_addr = pretty_print_address (ip);
      if (print && 0 != strcmp (print, txt_addr))
	logprintf (LOG_VERBOSE,
		   _("Connecting to %s{%s}:%d... "), print, txt_addr, port);
      else
	logprintf (LOG_VERBOSE, _("Connecting to %s:%d... "), txt_addr, port);
    }

  /* Store the sockaddr info to SA.  */
  sockaddr_set_data (sa, ip, port);

  /* Create the socket of the family appropriate for the address.  */
  sock = socket (sa->sa_family, SOCK_STREAM, 0);
  if (sock < 0)
    goto out;

  /* For very small rate limits, set the buffer size (and hence,
     hopefully, the kernel's TCP window size) to the per-second limit.
     That way we should never have to sleep for more than 1s between
     network reads.  */
  if (opt.limit_rate && opt.limit_rate < 8192)
    {
      int bufsize = opt.limit_rate;
      if (bufsize < 512)
	bufsize = 512;		/* avoid pathologically small values */
#ifdef SO_RCVBUF
      setsockopt (sock, SOL_SOCKET, SO_RCVBUF,
		  (void *)&bufsize, (socklen_t)sizeof (bufsize));
#endif
      /* When we add limit_rate support for writing, which is useful
	 for POST, we should also set SO_SNDBUF here.  */
    }

  if (opt.bind_address)
    {
      /* Bind the client side of the socket to the requested
	 address.  */
      struct sockaddr_storage bind_ss;
      struct sockaddr *bind_sa = (struct sockaddr *)&bind_ss;
      if (resolve_bind_address (opt.bind_address, bind_sa, 0))
	{
          if (bind (sock, bind_sa, sockaddr_size (bind_sa)) < 0)
	    {
	      CLOSE (sock);
	      sock = -1;
	      goto out;
	    }
	}
    }

  /* Connect the socket to the remote endpoint.  */
  if (connect_with_timeout (sock, sa, sockaddr_size (sa),
			    opt.connect_timeout) < 0)
    {
      CLOSE (sock);
      sock = -1;
      goto out;
    }

 out:
  if (sock >= 0)
    {
      /* Success. */
      if (print)
	logprintf (LOG_VERBOSE, _("connected.\n"));
      DEBUGP (("Created socket %d.\n", sock));
    }
  else
    {
      save_errno = errno;
      if (print)
	logprintf (LOG_VERBOSE, "failed: %s.\n", strerror (errno));
      errno = save_errno;
    }

  return sock;
}

/* Connect to a remote endpoint specified by host name.  */

int
connect_to_host (const char *host, int port)
{
  int i, start, end;
  struct address_list *al;
  int sock = -1;

 again:
  al = lookup_host (host, 0);
  if (!al)
    return E_HOST;

  address_list_get_bounds (al, &start, &end);
  for (i = start; i < end; i++)
    {
      const ip_address *ip = address_list_address_at (al, i);
      sock = connect_to_ip (ip, port, host);
      if (sock >= 0)
	/* Success. */
	break;

      address_list_set_faulty (al, i);

      /* The attempt to connect has failed.  Continue with the loop
	 and try next address. */
    }
  address_list_release (al);

  if (sock < 0 && address_list_cached_p (al))
    {
      /* We were unable to connect to any address in a list we've
	 obtained from cache.  There is a possibility that the host is
	 under dynamic DNS and has changed its address.  Resolve it
	 again.  */
      forget_host_lookup (host);
      goto again;
    }

  return sock;
}

int
test_socket_open (int sock)
{
#ifdef HAVE_SELECT
  fd_set check_set;
  struct timeval to;

  /* Check if we still have a valid (non-EOF) connection.  From Andrew
   * Maholski's code in the Unix Socket FAQ.  */

  FD_ZERO (&check_set);
  FD_SET (sock, &check_set);

  /* Wait one microsecond */
  to.tv_sec = 0;
  to.tv_usec = 1;

  /* If we get a timeout, then that means still connected */
  if (select (sock + 1, &check_set, NULL, NULL, &to) == 0)
    {
      /* Connection is valid (not EOF), so continue */
      return 1;
    }
  else
    return 0;
#else
  /* Without select, it's hard to know for sure. */
  return 1;
#endif
}

/* Create a socket and bind it to PORT locally.  Calling accept() on
   such a socket waits for and accepts incoming TCP connections.  The
   resulting socket is stored to LOCAL_SOCK.  */

uerr_t
bindport (const ip_address *bind_address, int *port, int *local_sock)
{
  int msock;
  int family = AF_INET;
  int optval;
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;
  xzero (ss);

#ifdef ENABLE_IPV6
  if (bind_address->type == IPV6_ADDRESS) 
    family = AF_INET6;
#endif

  if ((msock = socket (family, SOCK_STREAM, 0)) < 0)
    return CONSOCKERR;

#ifdef SO_REUSEADDR
  optval = 1;
  if (setsockopt (msock, SOL_SOCKET, SO_REUSEADDR,
		  (void *)&optval, (socklen_t)sizeof (optval)) < 0)
    {
      CLOSE (msock);
      return CONSOCKERR;
    }
#endif

#ifdef ENABLE_IPV6
# ifdef HAVE_IPV6_V6ONLY
  if (family == AF_INET6)
    {
      optval = 1;
      /* if setsockopt fails, go on anyway */
      setsockopt (msock, IPPROTO_IPV6, IPV6_V6ONLY,
                  (void *)&optval, (socklen_t)sizeof (optval));
    }
# endif
#endif

  sockaddr_set_data (sa, bind_address, *port);
  if (bind (msock, sa, sockaddr_size (sa)) < 0)
    {
      CLOSE (msock);
      return BINDERR;
    }
  DEBUGP (("Local socket fd %d bound.\n", msock));
  if (!*port)
    {
      socklen_t sa_len = sockaddr_size (sa);
      if (getsockname (msock, sa, &sa_len) < 0)
	{
	  CLOSE (msock);
	  return CONPORTERR;
	}
      sockaddr_get_data (sa, NULL, port);
      DEBUGP (("binding to address %s using port %i.\n", 
	       pretty_print_address (bind_address), *port));
    }
  if (listen (msock, 1) < 0)
    {
      CLOSE (msock);
      return LISTENERR;
    }
  *local_sock = msock;
  return BINDOK;
}

#ifdef HAVE_SELECT
/* Wait for file descriptor FD to be available, timing out after
   MAXTIME seconds.  "Available" means readable if writep is 0,
   writeable otherwise.

   Returns 1 if FD is available, 0 for timeout and -1 for error.  */

int
select_fd (int fd, double maxtime, int writep)
{
  fd_set fds;
  fd_set *rd = NULL, *wrt = NULL;
  struct timeval tmout;
  int result;

  FD_ZERO (&fds);
  FD_SET (fd, &fds);
  *(writep ? &wrt : &rd) = &fds;

  tmout.tv_sec = (long)maxtime;
  tmout.tv_usec = 1000000L * (maxtime - (long)maxtime);

  do
    result = select (fd + 1, rd, wrt, NULL, &tmout);
  while (result < 0 && errno == EINTR);

  /* When we've timed out, set errno to ETIMEDOUT for the convenience
     of the caller. */
  if (result == 0)
    errno = ETIMEDOUT;

  return result;
}
#endif /* HAVE_SELECT */

/* Accept a connection on LOCAL_SOCK, and store the new socket to
   *SOCK.  It blocks the caller until a connection is established.  If
   no connection is established for opt.connect_timeout seconds, the
   function exits with an error status.  */

uerr_t
acceptport (int local_sock, int *sock)
{
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;
  socklen_t addrlen = sizeof (ss);

#ifdef HAVE_SELECT
  if (select_fd (local_sock, opt.connect_timeout, 0) <= 0)
    return ACCEPTERR;
#endif
  if ((*sock = accept (local_sock, sa, &addrlen)) < 0)
    return ACCEPTERR;
  DEBUGP (("Created socket fd %d.\n", *sock));
  return ACCEPTOK;
}

/* Return the local IP address associated with the connection on FD.  */

int
conaddr (int fd, ip_address *ip)
{
  struct sockaddr_storage storage;
  struct sockaddr *sockaddr = (struct sockaddr *)&storage;
  socklen_t addrlen = sizeof (storage);

  if (getsockname (fd, sockaddr, &addrlen) < 0)
    return 0;

  switch (sockaddr->sa_family)
    {
#ifdef ENABLE_IPV6
    case AF_INET6:
      {
	struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)&storage;
	ip->type = IPV6_ADDRESS;
	ADDRESS_IPV6_IN6_ADDR (ip) = sa6->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
	ADDRESS_IPV6_SCOPE (ip) = sa6->sin6_scope_id;
#endif
	DEBUGP (("conaddr is: %s\n", pretty_print_address (ip)));
	return 1;
      }
#endif
    case AF_INET:
      {
	struct sockaddr_in *sa = (struct sockaddr_in *)&storage;
	ip->type = IPV4_ADDRESS;
	ADDRESS_IPV4_IN_ADDR (ip) = sa->sin_addr;
	DEBUGP (("conaddr is: %s\n", pretty_print_address (ip)));
	return 1;
      }
    default:
      abort ();
    }

  return 0;
}

/* Read at most LEN bytes from FD, storing them to BUF.  This is
   virtually the same as read(), but takes care of EINTR braindamage
   and uses select() to timeout the stale connections (a connection is
   stale if more than OPT.READ_TIMEOUT time is spent in select() or
   read()).  */

int
iread (int fd, char *buf, int len)
{
  int res;

#ifdef HAVE_SELECT
  if (opt.read_timeout)
    if (select_fd (fd, opt.read_timeout, 0) <= 0)
      return -1;
#endif
  do
    res = READ (fd, buf, len);
  while (res == -1 && errno == EINTR);

  return res;
}

/* Write LEN bytes from BUF to FD.  This is similar to iread(), but
   unlike iread(), it makes sure that all of BUF is actually written
   to FD, so callers needn't bother with checking that the return
   value equals to LEN.  Instead, you should simply check for -1.  */

int
iwrite (int fd, char *buf, int len)
{
  int res = 0;

  /* `write' may write less than LEN bytes, thus the outward loop
     keeps trying it until all was written, or an error occurred.  The
     inner loop is reserved for the usual EINTR f*kage, and the
     innermost loop deals with the same during select().  */
  while (len > 0)
    {
#ifdef HAVE_SELECT
      if (opt.read_timeout)
	if (select_fd (fd, opt.read_timeout, 1) <= 0)
	  return -1;
#endif
      do
	res = WRITE (fd, buf, len);
      while (res == -1 && errno == EINTR);
      if (res <= 0)
	break;
      buf += res;
      len -= res;
    }
  return res;
}
