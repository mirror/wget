/* Establishing and handling network connections.
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <assert.h>

#ifdef WINDOWS
# include <winsock.h>
#else
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
#ifndef __BEOS__
# include <arpa/inet.h>
#endif
#endif /* WINDOWS */

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
#include "connect.h"
#include "host.h"

#ifndef errno
extern int errno;
#endif

/* Variables shared by bindport and acceptport: */
static int msock = -1;
static struct sockaddr *addr;

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
connect_to_one (const unsigned char *addr, unsigned short port, int silent)
{
  struct sockaddr_in sock_name;
  int sock, save_errno;

  /* Set port and protocol */
  sock_name.sin_family = AF_INET;
  sock_name.sin_port = htons (port);
  memcpy ((unsigned char *)&sock_name.sin_addr, addr, 4);

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
  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    goto out;

  if (opt.bind_address)
    {
      /* Bind the client side to the requested address. */
      if (bind (sock, (struct sockaddr *)opt.bind_address,
		sizeof (*opt.bind_address)))
	{
	  close (sock);
	  sock = -1;
	  goto out;
	}
    }

  /* Connect the socket to the remote host.  */
  if (connect (sock, (struct sockaddr *)&sock_name, sizeof (sock_name)) < 0)
    {
      close (sock);
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
      unsigned char addr[4];
      int sock;
      address_list_copy_one (al, i, addr);

      sock = connect_to_one (addr, port, silent);
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
bindport (unsigned short *port)
{
  int optval = 1;
  static struct sockaddr_in srv;

  msock = -1;
  addr = (struct sockaddr *) &srv;
  if ((msock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    return CONSOCKERR;
  if (setsockopt (msock, SOL_SOCKET, SO_REUSEADDR,
		  (char *)&optval, sizeof (optval)) < 0)
    return CONSOCKERR;

  if (opt.bind_address == NULL)
    {
      srv.sin_family = AF_INET;
      srv.sin_addr.s_addr = htonl (INADDR_ANY);
    }
  else
    srv = *opt.bind_address;

  srv.sin_port = htons (*port);
  if (bind (msock, addr, sizeof (struct sockaddr_in)) < 0)
    {
      CLOSE (msock);
      msock = -1;
      return BINDERR;
    }
  DEBUGP (("Master socket fd %d bound.\n", msock));
  if (!*port)
    {
      /* #### addrlen should be a 32-bit type, which int is not
         guaranteed to be.  Oh, and don't try to make it a size_t,
         because that can be 64-bit.  */
      int addrlen = sizeof (struct sockaddr_in);
      if (getsockname (msock, addr, &addrlen) < 0)
	{
	  CLOSE (msock);
	  msock = -1;
	  return CONPORTERR;
	}
      *port = ntohs (srv.sin_port);
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
/* Wait for file descriptor FD to be readable, MAXTIME being the
   timeout in seconds.  If WRITEP is non-zero, checks for FD being
   writable instead.

   Returns 1 if FD is accessible, 0 for timeout and -1 for error in
   select().  */
int
select_fd (int fd, int maxtime, int writep)
{
  fd_set fds, exceptfds;
  struct timeval timeout;

  FD_ZERO (&fds);
  FD_SET (fd, &fds);
  FD_ZERO (&exceptfds);
  FD_SET (fd, &exceptfds);
  timeout.tv_sec = maxtime;
  timeout.tv_usec = 0;
  /* HPUX reportedly warns here.  What is the correct incantation?  */
  return select (fd + 1, writep ? NULL : &fds, writep ? &fds : NULL,
		 &exceptfds, &timeout);
}
#endif /* HAVE_SELECT */

/* Call accept() on MSOCK and store the result to *SOCK.  This assumes
   that bindport() has been used to initialize MSOCK to a correct
   value.  It blocks the caller until a connection is established.  If
   no connection is established for OPT.TIMEOUT seconds, the function
   exits with an error status.  */
uerr_t
acceptport (int *sock)
{
  int addrlen = sizeof (struct sockaddr_in);

#ifdef HAVE_SELECT
  if (select_fd (msock, opt.timeout, 0) <= 0)
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

/* Return the local IP address associated with the connection on FD.
   It is returned in a static buffer.  */
unsigned char *
conaddr (int fd)
{
  static unsigned char res[4];
  struct sockaddr_in mysrv;
  struct sockaddr *myaddr;
  int addrlen = sizeof (mysrv);	/* see bindport() for discussion of
                                   using `int' here. */

  myaddr = (struct sockaddr *) (&mysrv);
  if (getsockname (fd, myaddr, (int *)&addrlen) < 0)
    return NULL;
  memcpy (res, &mysrv.sin_addr, 4);
  return res;
}

/* Read at most LEN bytes from FD, storing them to BUF.  This is
   virtually the same as read(), but takes care of EINTR braindamage
   and uses select() to timeout the stale connections (a connection is
   stale if more than OPT.TIMEOUT time is spent in select() or
   read()).  */
int
iread (int fd, char *buf, int len)
{
  int res;

  do
    {
#ifdef HAVE_SELECT
      if (opt.timeout)
	{
	  do
	    {
	      res = select_fd (fd, opt.timeout, 0);
	    }
	  while (res == -1 && errno == EINTR);
	  if (res <= 0)
	    {
	      /* Set errno to ETIMEDOUT on timeout.  */
	      if (res == 0)
		/* #### Potentially evil!  */
		errno = ETIMEDOUT;
	      return -1;
	    }
	}
#endif
      res = READ (fd, buf, len);
    }
  while (res == -1 && errno == EINTR);

  return res;
}

/* Write LEN bytes from BUF to FD.  This is similar to iread(), but
   doesn't bother with select().  Unlike iread(), it makes sure that
   all of BUF is actually written to FD, so callers needn't bother
   with checking that the return value equals to LEN.  Instead, you
   should simply check for -1.  */
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
      do
	{
#ifdef HAVE_SELECT
	  if (opt.timeout)
	    {
	      do
		{
		  res = select_fd (fd, opt.timeout, 1);
		}
	      while (res == -1 && errno == EINTR);
	      if (res <= 0)
		{
		  /* Set errno to ETIMEDOUT on timeout.  */
		  if (res == 0)
		    /* #### Potentially evil!  */
		    errno = ETIMEDOUT;
		  return -1;
		}
	    }
#endif
	  res = WRITE (fd, buf, len);
	}
      while (res == -1 && errno == EINTR);
      if (res <= 0)
	break;
      buf += res;
      len -= res;
    }
  return res;
}
