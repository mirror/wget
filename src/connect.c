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
#include "hash.h"

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

static void
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
resolve_bind_address (struct sockaddr *sa)
{
  struct address_list *al;

  /* Make sure this is called only once.  opt.bind_address doesn't
     change during a Wget run.  */
  static int called, should_bind;
  static ip_address ip;
  if (called)
    {
      if (should_bind)
	sockaddr_set_data (sa, &ip, 0);
      return should_bind;
    }
  called = 1;

  al = lookup_host_passive (opt.bind_address);
  if (!al)
    {
      /* #### We should be able to print the error message here. */
      logprintf (LOG_NOTQUIET,
		 _("%s: unable to resolve bind address `%s'; disabling bind.\n"),
		 exec_name, opt.bind_address);
      should_bind = 0;
      return 0;
    }

  /* Pick the first address in the list and use it as bind address.
     Perhaps we should try multiple addresses in succession, but I
     don't think that's necessary in practice.  */
  ip = *address_list_address_at (al, 0);
  address_list_release (al);

  sockaddr_set_data (sa, &ip, 0);
  should_bind = 1;
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
  int sock = -1;

  /* If PRINT is non-NULL, print the "Connecting to..." line, with
     PRINT being the host name we're connecting to.  */
  if (print)
    {
      const char *txt_addr = pretty_print_address (ip);
      if (print && 0 != strcmp (print, txt_addr))
	logprintf (LOG_VERBOSE,
		   _("Connecting to %s|%s|:%d... "), print, txt_addr, port);
      else
	logprintf (LOG_VERBOSE, _("Connecting to %s:%d... "), txt_addr, port);
    }

  /* Store the sockaddr info to SA.  */
  sockaddr_set_data (sa, ip, port);

  /* Create the socket of the family appropriate for the address.  */
  sock = socket (sa->sa_family, SOCK_STREAM, 0);
  if (sock < 0)
    goto err;

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
      if (resolve_bind_address (bind_sa))
	{
          if (bind (sock, bind_sa, sockaddr_size (bind_sa)) < 0)
	    goto err;
	}
    }

  /* Connect the socket to the remote endpoint.  */
  if (connect_with_timeout (sock, sa, sockaddr_size (sa),
			    opt.connect_timeout) < 0)
    goto err;

  /* Success. */
  assert (sock >= 0);
  if (print)
    logprintf (LOG_VERBOSE, _("connected.\n"));
  DEBUGP (("Created socket %d.\n", sock));
  return sock;

 err:
  {
    /* Protect errno from possible modifications by close and
       logprintf.  */
    int save_errno = errno;
    if (sock >= 0)
      xclose (sock);
    if (print)
      logprintf (LOG_VERBOSE, "failed: %s.\n", strerror (errno));
    errno = save_errno;
    return -1;
  }
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
  int sock;
  int family = AF_INET;
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;

  /* For setting options with setsockopt. */
  int setopt_val = 1;
  void *setopt_ptr = (void *)&setopt_val;
  socklen_t setopt_size = sizeof (setopt_val);

#ifdef ENABLE_IPV6
  if (bind_address->type == IPV6_ADDRESS) 
    family = AF_INET6;
#endif

  if ((sock = socket (family, SOCK_STREAM, 0)) < 0)
    return CONSOCKERR;

#ifdef SO_REUSEADDR
  setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, setopt_ptr, setopt_size);
#endif

#ifdef ENABLE_IPV6
# ifdef HAVE_IPV6_V6ONLY
  if (family == AF_INET6)
    setsockopt (sock, IPPROTO_IPV6, IPV6_V6ONLY, setopt_ptr, setopt_size);
# endif
#endif

  xzero (ss);
  sockaddr_set_data (sa, bind_address, *port);
  if (bind (sock, sa, sockaddr_size (sa)) < 0)
    {
      xclose (sock);
      return BINDERR;
    }
  DEBUGP (("Local socket fd %d bound.\n", sock));
  if (!*port)
    {
      socklen_t sa_len = sockaddr_size (sa);
      if (getsockname (sock, sa, &sa_len) < 0)
	{
	  xclose (sock);
	  return CONPORTERR;
	}
      sockaddr_get_data (sa, NULL, port);
      DEBUGP (("binding to address %s using port %i.\n", 
	       pretty_print_address (bind_address), *port));
    }
  if (listen (sock, 1) < 0)
    {
      xclose (sock);
      return LISTENERR;
    }
  *local_sock = sock;
  return BINDOK;
}

#ifdef HAVE_SELECT
/* Wait for file descriptor FD to be readable or writable or both,
   timing out after MAXTIME seconds.  Returns 1 if FD is available, 0
   for timeout and -1 for error.  The argument WAIT_FOR can be a
   combination of WAIT_READ and WAIT_WRITE.

   This is a mere convenience wrapper around the select call, and
   should be taken as such.  */

int
select_fd (int fd, double maxtime, int wait_for)
{
  fd_set fdset;
  fd_set *rd = NULL, *wr = NULL;
  struct timeval tmout;
  int result;

  FD_ZERO (&fdset);
  FD_SET (fd, &fdset);
  if (wait_for & WAIT_FOR_READ)
    rd = &fdset;
  if (wait_for & WAIT_FOR_WRITE)
    wr = &fdset;

  tmout.tv_sec = (long) maxtime;
  tmout.tv_usec = 1000000L * (maxtime - (long) maxtime);

  do
    result = select (fd + 1, rd, wr, NULL, &tmout);
  while (result < 0 && errno == EINTR);

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
  if (opt.connect_timeout)
    if (select_fd (local_sock, opt.connect_timeout, WAIT_FOR_READ) <= 0)
      return ACCEPTERR;
#endif
  if ((*sock = accept (local_sock, sa, &addrlen)) < 0)
    return ACCEPTERR;
  DEBUGP (("Created socket fd %d.\n", *sock));
  return ACCEPTOK;
}

/* Get the IP address associated with the connection on FD and store
   it to IP.  Return 1 on success, 0 otherwise.

   If ENDPOINT is ENDPOINT_LOCAL, it returns the address of the local
   (client) side of the socket.  Else if ENDPOINT is ENDPOINT_PEER, it
   returns the address of the remote (peer's) side of the socket.  */

int
socket_ip_address (int sock, ip_address *ip, int endpoint)
{
  struct sockaddr_storage storage;
  struct sockaddr *sockaddr = (struct sockaddr *)&storage;
  socklen_t addrlen = sizeof (storage);
  int ret;

  if (endpoint == ENDPOINT_LOCAL)
    ret = getsockname (sock, sockaddr, &addrlen);
  else if (endpoint == ENDPOINT_PEER)
    ret = getpeername (sock, sockaddr, &addrlen);
  else
    abort ();
  if (ret < 0)
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

/* Basic socket operations, mostly EINTR wrappers.  */

#ifdef WINDOWS
# define read(fd, buf, cnt) recv (fd, buf, cnt, 0)
# define write(fd, buf, cnt) send (fd, buf, cnt, 0)
# define close(fd) closesocket (fd)
#endif

#ifdef __BEOS__
# define read(fd, buf, cnt) recv (fd, buf, cnt, 0)
# define write(fd, buf, cnt) send (fd, buf, cnt, 0)
#endif

static int
sock_read (int fd, char *buf, int bufsize)
{
  int res;
  do
    res = read (fd, buf, bufsize);
  while (res == -1 && errno == EINTR);
  return res;
}

static int
sock_write (int fd, char *buf, int bufsize)
{
  int res = 0;
  do
    res = write (fd, buf, bufsize);
  while (res == -1 && errno == EINTR);
  return res;
}

static int
sock_poll (int fd, double timeout, int wait_for)
{
#ifdef HAVE_SELECT
  return select_fd (fd, timeout, wait_for);
#else
  return 1;
#endif
}

static void
sock_close (int fd)
{
  close (fd);
  DEBUGP (("Closed fd %d\n", fd));
}
#undef read
#undef write
#undef close

/* Reading and writing from the network.  We build around the socket
   (file descriptor) API, but support "extended" operations for things
   that are not mere file descriptors under the hood, such as SSL
   sockets.

   That way the user code can call xread(fd, ...) and we'll run read
   or SSL_read or whatever is necessary.  */

static struct hash_table *extended_map;
static int extended_map_modified_tick;

struct extended_info {
  xreader_t reader;
  xwriter_t writer;
  xpoller_t poller;
  xcloser_t closer;
  void *ctx;
};

void
register_extended (int fd, xreader_t reader, xwriter_t writer,
		   xpoller_t poller, xcloser_t closer, void *ctx)
{
  struct extended_info *info;

  /* The file descriptor must be non-negative to be registered.
     Negative values are ignored by xclose(), and -1 cannot be used as
     hash key.  */
  assert (fd >= 0);

  info = xnew (struct extended_info);
  info->reader = reader;
  info->writer = writer;
  info->poller = poller;
  info->closer = closer;
  info->ctx = ctx;
  if (!extended_map)
    extended_map = hash_table_new (0, NULL, NULL);
  hash_table_put (extended_map, (void *) fd, info);
  ++extended_map_modified_tick;
}

/* When xread/xwrite are called multiple times in a loop, they should
   remember the INFO pointer instead of fetching it every time.  It is
   not enough to compare FD to LAST_FD because FD might have been
   closed and reopened.  modified_tick ensures that changes to
   extended_map will not be unnoticed.

   This is a macro because we want the static storage variables to be
   per-function.  */

#define LAZY_RETRIEVE_INFO(info) do {					\
  static struct extended_info *last_info;				\
  static int last_fd = -1, last_tick;					\
  if (!extended_map)							\
    info = NULL;							\
  else if (last_fd == fd && last_tick == extended_map_modified_tick)	\
    info = last_info;							\
  else									\
    {									\
      info = hash_table_get (extended_map, (void *) fd);		\
      last_fd = fd;							\
      last_info = info;							\
      last_tick = extended_map_modified_tick;				\
    }									\
} while (0)

/* Read no more than BUFSIZE bytes of data from FD, storing them to
   BUF.  If TIMEOUT is non-zero, the operation aborts if no data is
   received after that many seconds.  If TIMEOUT is -1, the value of
   opt.timeout is used for TIMEOUT.  */

int
xread (int fd, char *buf, int bufsize, double timeout)
{
  struct extended_info *info;
  LAZY_RETRIEVE_INFO (info);
  if (timeout == -1)
    timeout = opt.read_timeout;
  if (timeout)
    {
      int test;
      if (info && info->poller)
	test = info->poller (fd, timeout, WAIT_FOR_READ, info->ctx);
      else
	test = sock_poll (fd, timeout, WAIT_FOR_READ);
      if (test == 0)
	errno = ETIMEDOUT;
      if (test <= 0)
	return -1;
    }
  if (info && info->reader)
    return info->reader (fd, buf, bufsize, info->ctx);
  else
    return sock_read (fd, buf, bufsize);
}

/* Write the entire contents of BUF to FD.  If TIMEOUT is non-zero,
   the operation aborts if no data is received after that many
   seconds.  If TIMEOUT is -1, the value of opt.timeout is used for
   TIMEOUT.  */

int
xwrite (int fd, char *buf, int bufsize, double timeout)
{
  int res;
  struct extended_info *info;
  LAZY_RETRIEVE_INFO (info);
  if (timeout == -1)
    timeout = opt.read_timeout;

  /* `write' may write less than LEN bytes, thus the loop keeps trying
     it until all was written, or an error occurred.  */
  res = 0;
  while (bufsize > 0)
    {
      if (timeout)
	{
	  int test;
	  if (info && info->poller)
	    test = info->poller (fd, timeout, WAIT_FOR_WRITE, info->ctx);
	  else
	    test = sock_poll (fd, timeout, WAIT_FOR_WRITE);
	  if (test == 0)
	    errno = ETIMEDOUT;
	  if (test <= 0)
	    return -1;
	}
      if (info && info->writer)
	res = info->writer (fd, buf, bufsize, info->ctx);
      else
	res = sock_write (fd, buf, bufsize);
      if (res <= 0)
	break;
      buf += res;
      bufsize -= res;
    }
  return res;
}

/* Close the file descriptor FD.  */

void
xclose (int fd)
{
  struct extended_info *info;
  if (fd < 0)
    return;

  /* We don't need to be extra-fast here, so save some code by
     avoiding LAZY_RETRIEVE_INFO. */
  info = NULL;
  if (extended_map)
    info = hash_table_get (extended_map, (void *) fd);

  if (info && info->closer)
    info->closer (fd, info->ctx);
  else
    sock_close (fd);

  if (info)
    {
      hash_table_remove (extended_map, (void *) fd);
      xfree (info);
      ++extended_map_modified_tick;
    }
}
