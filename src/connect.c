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

/* Variables shared by bindport and acceptport: */
static int msock = -1;
static struct sockaddr *addr;

static ip_address bind_address;
static int bind_address_resolved;

static void
resolve_bind_address (void)
{
  struct address_list *al;

  if (bind_address_resolved || opt.bind_address == NULL)
    /* Nothing to do. */
    return;

  al = lookup_host (opt.bind_address, 1);
  if (!al)
    {
      logprintf (LOG_NOTQUIET,
		 _("Unable to convert `%s' to a bind address.  Reverting to ANY.\n"),
		 opt.bind_address);
      return;
    }

  address_list_copy_one (al, 0, &bind_address);
  address_list_release (al);
  bind_address_resolved = 1;
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

/* A kludge, but still better than passing the host name all the way
   to connect_to_one.  */
static const char *connection_host_name;

void
set_connection_host_name (const char *host)
{
  if (host)
    assert (connection_host_name == NULL);
  else
    assert (connection_host_name != NULL);

  connection_host_name = host;
}

/* Connect to a remote host whose address has been resolved. */
int
connect_to_one (ip_address *addr, unsigned short port, int silent)
{
  wget_sockaddr sa;
  int sock, save_errno;

  /* Set port and protocol */
  wget_sockaddr_set_address (&sa, ip_default_family, port, addr);

  if (!silent)
    {
      char *pretty_addr = pretty_print_address (addr);
      if (connection_host_name
	  && 0 != strcmp (connection_host_name, pretty_addr))
	logprintf (LOG_VERBOSE, _("Connecting to %s[%s]:%hu... "),
		   connection_host_name, pretty_addr, port);
      else
	logprintf (LOG_VERBOSE, _("Connecting to %s:%hu... "),
		   pretty_addr, port);
    }

  /* Make an internet socket, stream type.  */
  sock = socket (ip_default_family, SOCK_STREAM, 0);
  if (sock < 0)
    goto out;

  /* For very small rate limits, set the buffer size (and hence,
     hopefully, the size of the kernel window) to the size of the
     limit.  That way we don't sleep for more than 1s between network
     reads.  */
  if (opt.limit_rate && opt.limit_rate < 8192)
    {
      int bufsize = opt.limit_rate;
      if (bufsize < 512)
	bufsize = 512;
#ifdef SO_RCVBUF
      setsockopt (sock, SOL_SOCKET, SO_RCVBUF,
		  (char *)&bufsize, sizeof (bufsize));
#endif
      /* When we add opt.limit_rate support for writing, as with
	 `--post-file', also set SO_SNDBUF here.  */
    }

  resolve_bind_address ();
  if (bind_address_resolved)
    {
      /* Bind the client side to the requested address. */
      wget_sockaddr bsa;
      wget_sockaddr_set_address (&bsa, ip_default_family, 0, &bind_address);
      if (bind (sock, &bsa.sa, sockaddr_len ()))
	{
	  CLOSE (sock);
	  sock = -1;
	  goto out;
	}
    }

  /* Connect the socket to the remote host.  */
  if (connect_with_timeout (sock, &sa.sa, sockaddr_len (),
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
      if (!silent)
	logprintf (LOG_VERBOSE, _("connected.\n"));
      DEBUGP (("Created socket %d.\n", sock));
    }
  else
    {
      save_errno = errno;
      if (!silent)
	logprintf (LOG_VERBOSE, "failed: %s.\n", strerror (errno));
      errno = save_errno;
    }

  return sock;
}

/* Connect to a remote host whose address has been resolved. */
int
connect_to_many (struct address_list *al, unsigned short port, int silent)
{
  int i, start, end;

  address_list_get_bounds (al, &start, &end);
  for (i = start; i < end; i++)
    {
      ip_address addr;
      int sock;
      address_list_copy_one (al, i, &addr);

      sock = connect_to_one (&addr, port, silent);
      if (sock >= 0)
	/* Success. */
	return sock;

      address_list_set_faulty (al, i);

      /* The attempt to connect has failed.  Continue with the loop
	 and try next address. */
    }

  return -1;
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

/* Bind the local port PORT.  This does all the necessary work, which
   is creating a socket, setting SO_REUSEADDR option on it, then
   calling bind() and listen().  If *PORT is 0, a random port is
   chosen by the system, and its value is stored to *PORT.  The
   internal variable MPORT is set to the value of the ensuing master
   socket.  Call acceptport() to block for and accept a connection.  */
uerr_t
bindport (unsigned short *port, int family)
{
  int optval = 1;
  wget_sockaddr srv;
  memset (&srv, 0, sizeof (wget_sockaddr));

  msock = -1;

  if ((msock = socket (family, SOCK_STREAM, 0)) < 0)
    return CONSOCKERR;

#ifdef SO_REUSEADDR
  if (setsockopt (msock, SOL_SOCKET, SO_REUSEADDR,
		  (char *)&optval, sizeof (optval)) < 0)
    return CONSOCKERR;
#endif

  resolve_bind_address ();
  wget_sockaddr_set_address (&srv, ip_default_family, htons (*port),
			     bind_address_resolved ? &bind_address : NULL);
  if (bind (msock, &srv.sa, sockaddr_len ()) < 0)
    {
      CLOSE (msock);
      msock = -1;
      return BINDERR;
    }
  DEBUGP (("Master socket fd %d bound.\n", msock));
  if (!*port)
    {
      socklen_t sa_len = sockaddr_len ();
      if (getsockname (msock, &srv.sa, &sa_len) < 0)
	{
	  CLOSE (msock);
	  msock = -1;
	  return CONPORTERR;
	}
      *port = wget_sockaddr_get_port (&srv);
      DEBUGP (("using port %i.\n", *port));
    }
  if (listen (msock, 1) < 0)
    {
      CLOSE (msock);
      msock = -1;
      return LISTENERR;
    }
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

/* Call accept() on MSOCK and store the result to *SOCK.  This assumes
   that bindport() has been used to initialize MSOCK to a correct
   value.  It blocks the caller until a connection is established.  If
   no connection is established for OPT.CONNECT_TIMEOUT seconds, the
   function exits with an error status.  */
uerr_t
acceptport (int *sock)
{
  socklen_t addrlen = sockaddr_len ();

#ifdef HAVE_SELECT
  if (select_fd (msock, opt.connect_timeout, 0) <= 0)
    return ACCEPTERR;
#endif
  if ((*sock = accept (msock, addr, &addrlen)) < 0)
    return ACCEPTERR;
  DEBUGP (("Created socket fd %d.\n", *sock));
  return ACCEPTOK;
}

/* Close SOCK, as well as the most recently remembered MSOCK, created
   via bindport().  If SOCK is -1, close MSOCK only.  */
void
closeport (int sock)
{
  /*shutdown (sock, 2);*/
  if (sock != -1)
    CLOSE (sock);
  if (msock != -1)
    CLOSE (msock);
  msock = -1;
}

/* Return the local IP address associated with the connection on FD.  */

int
conaddr (int fd, ip_address *ip)
{
  wget_sockaddr mysrv;
  socklen_t addrlen = sizeof (mysrv);	
  if (getsockname (fd, &mysrv.sa, &addrlen) < 0)
    return 0;

  switch (mysrv.sa.sa_family)
    {
#ifdef ENABLE_IPV6
    case AF_INET6:
      memcpy (ip, &mysrv.sin6.sin6_addr, 16);
      return 1;
#endif
    case AF_INET:
      map_ipv4_to_ip ((ip4_address *)&mysrv.sin.sin_addr, ip);
      return 1;
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
