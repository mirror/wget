/* Basic FTP routines.
   Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.

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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <sys/types.h>

/* For inet_ntop. */
#ifndef WINDOWS
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef WINDOWS
# include <winsock.h>
#endif

#include "wget.h"
#include "utils.h"
#include "rbuf.h"
#include "connect.h"
#include "host.h"
#include "ftp.h"

char ftp_last_respline[128];


/* Get the response of FTP server and allocate enough room to handle
   it.  <CR> and <LF> characters are stripped from the line, and the
   line is 0-terminated.  All the response lines but the last one are
   skipped.  The last line is determined as described in RFC959.  */
uerr_t
ftp_response (struct rbuf *rbuf, char **line)
{
  int i;
  int bufsize = 40;

  *line = (char *)xmalloc (bufsize);
  do
    {
      for (i = 0; 1; i++)
        {
          int res;
          if (i > bufsize - 1)
            *line = (char *)xrealloc (*line, (bufsize <<= 1));
          res = RBUF_READCHAR (rbuf, *line + i);
          /* RES is number of bytes read.  */
          if (res == 1)
            {
              if ((*line)[i] == '\n')
                {
                  (*line)[i] = '\0';
                  /* Get rid of \r.  */
                  if (i > 0 && (*line)[i - 1] == '\r')
                    (*line)[i - 1] = '\0';
                  break;
                }
            }
          else
            return FTPRERR;
        }
      if (opt.server_response)
        logprintf (LOG_ALWAYS, "%s\n", *line);
      else
        DEBUGP (("%s\n", *line));
    }
  while (!(i >= 3 && ISDIGIT (**line) && ISDIGIT ((*line)[1]) &&
           ISDIGIT ((*line)[2]) && (*line)[3] == ' '));
  strncpy (ftp_last_respline, *line, sizeof (ftp_last_respline));
  ftp_last_respline[sizeof (ftp_last_respline) - 1] = '\0';
  return FTPOK;
}

/* Returns the malloc-ed FTP request, ending with <CR><LF>, printing
   it if printing is required.  If VALUE is NULL, just use
   command<CR><LF>.  */
static char *
ftp_request (const char *command, const char *value)
{
  char *res = (char *)xmalloc (strlen (command)
                               + (value ? (1 + strlen (value)) : 0)
                               + 2 + 1);
  sprintf (res, "%s%s%s\r\n", command, value ? " " : "", value ? value : "");
  if (opt.server_response)
    {
      /* Hack: don't print out password.  */
      if (strncmp (res, "PASS", 4) != 0)
        logprintf (LOG_ALWAYS, "--> %s\n", res);
      else
        logputs (LOG_ALWAYS, "--> PASS Turtle Power!\n\n");
    }
  else
    DEBUGP (("\n--> %s\n", res));
  return res;
}

#ifdef USE_OPIE
const char *calculate_skey_response PARAMS ((int, const char *, const char *));
#endif

/* Sends the USER and PASS commands to the server, to control
   connection socket csock.  */
uerr_t
ftp_login (struct rbuf *rbuf, const char *acc, const char *pass)
{
  uerr_t err;
  char *request, *respline;
  int nwritten;

  /* Get greeting.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPSRVERR;
    }
  xfree (respline);
  /* Send USER username.  */
  request = ftp_request ("USER", acc);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  /* An unprobable possibility of logging without a password.  */
  if (*respline == '2')
    {
      xfree (respline);
      return FTPOK;
    }
  /* Else, only response 3 is appropriate.  */
  if (*respline != '3')
    {
      xfree (respline);
      return FTPLOGREFUSED;
    }
#ifdef USE_OPIE
  {
    static const char *skey_head[] = {
      "331 s/key ",
      "331 opiekey "
    };
    int i;

    for (i = 0; i < countof (skey_head); i++)
      {
        if (strncasecmp (skey_head[i], respline, strlen (skey_head[i])) == 0)
          break;
      }
    if (i < countof (skey_head))
      {
        const char *cp;
        int skey_sequence = 0;

        for (cp = respline + strlen (skey_head[i]);
             '0' <= *cp && *cp <= '9';
             cp++)
          {
            skey_sequence = skey_sequence * 10 + *cp - '0';
          }
        if (*cp == ' ')
          cp++;
        else
          {
          bad:
            xfree (respline);
            return FTPLOGREFUSED;
          }
        if ((cp = calculate_skey_response (skey_sequence, cp, pass)) == 0)
          goto bad;
        pass = cp;
      }
  }
#endif /* USE_OPIE */
  xfree (respline);
  /* Send PASS password.  */
  request = ftp_request ("PASS", pass);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPLOGINC;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

static void
ip_address_to_port_repr (const ip_address *addr, unsigned short port, char *buf, 
                         size_t buflen)
{
  unsigned char *ptr;

  assert (addr != NULL);
  assert (addr->type == IPv4_ADDRESS);
  assert (buf != NULL);
  /* buf must contain the argument of PORT (of the form a,b,c,d,e,f). */
  assert (buflen >= 6 * 4);

  ptr = (unsigned char *)(&addr->addr.ipv4.addr.s_addr);
  snprintf (buf, buflen, "%d,%d,%d,%d,%d,%d", ptr[0], ptr[1],
            ptr[2], ptr[3], (unsigned) (port & 0xff00) >> 8, port & 0xff);
  buf[buflen - 1] = '\0';
}

/* Bind a port and send the appropriate PORT command to the FTP
   server.  Use acceptport after RETR, to get the socket of data
   connection.  */
uerr_t
ftp_port (struct rbuf *rbuf)
{
  uerr_t err;
  char *request, *respline;
  ip_address addr;
  int nwritten;
  unsigned short port;
  /* Must contain the argument of PORT (of the form a,b,c,d,e,f). */
  char bytes[6 * 4 + 1];

  assert (rbuf != NULL);
  assert (rbuf_initialized_p (rbuf));

  /* Get the address of this side of the connection. */
  if (!conaddr (RBUF_FD (rbuf), &addr))
    return BINDERR;

  assert (addr.type == IPv4_ADDRESS);

  /* Setting port to 0 lets the system choose a free port.  */
  port = 0;

  /* Bind the port.  */
  err = bindport (&addr, &port);
  if (err != BINDOK)
    return err;

  /* Construct the argument of PORT (of the form a,b,c,d,e,f). */
  ip_address_to_port_repr (&addr, port, bytes, sizeof (bytes));

  /* Send PORT request.  */
  request = ftp_request ("PORT", bytes);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      closeport (-1);
      return WRITEFAILED;
    }
  xfree (request);

  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      closeport (-1);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      closeport (-1);
      return FTPPORTERR;
    }
  xfree (respline);
  return FTPOK;
}

#ifdef ENABLE_IPV6
static void
ip_address_to_lprt_repr (const ip_address *addr, unsigned short port, char *buf, 
                         size_t buflen)
{
  unsigned char *ptr;

  assert (addr != NULL);
  assert (addr->type == IPv4_ADDRESS || addr->type == IPv6_ADDRESS);
  assert (buf != NULL);
  /* buf must contain the argument of LPRT (of the form af,n,h1,h2,...,hn,p1,p2). */
  assert (buflen >= 21 * 4);

  /* Construct the argument of LPRT (of the form af,n,h1,h2,...,hn,p1,p2). */
  switch (addr->type) 
    {
      case IPv4_ADDRESS: 
	ptr = (unsigned char *)(&addr->addr.ipv4.addr);
        snprintf (buf, buflen, "%d,%d,%d,%d,%d,%d,%d,%d,%d", 4, 4, 
                  ptr[0], ptr[1], ptr[2], ptr[3], 2,
                  (unsigned) (port & 0xff00) >> 8, port & 0xff);
        buf[buflen - 1] = '\0';
        break;
      case IPv6_ADDRESS: 
	ptr = (unsigned char *)(&addr->addr.ipv6.addr);
	snprintf (buf, buflen, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	          6, 16, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], 
		  ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15], 2,
		  (unsigned) (port & 0xff00) >> 8, port & 0xff);
	buf[buflen - 1] = '\0';
	break;
    }
}

/* Bind a port and send the appropriate PORT command to the FTP
   server.  Use acceptport after RETR, to get the socket of data
   connection.  */
uerr_t
ftp_lprt (struct rbuf *rbuf)
{
  uerr_t err;
  char *request, *respline;
  ip_address addr;
  int nwritten;
  unsigned short port;
  /* Must contain the argument of LPRT (of the form af,n,h1,h2,...,hn,p1,p2). */
  char bytes[21 * 4 + 1];

  assert (rbuf != NULL);
  assert (rbuf_initialized_p (rbuf));

  /* Get the address of this side of the connection. */
  if (!conaddr (RBUF_FD (rbuf), &addr))
    return BINDERR;

  assert (addr.type == IPv4_ADDRESS || addr.type == IPv6_ADDRESS);

  /* Setting port to 0 lets the system choose a free port.  */
  port = 0;

  /* Bind the port.  */
  err = bindport (&addr, &port);
  if (err != BINDOK)
    return err;

  /* Construct the argument of LPRT (of the form af,n,h1,h2,...,hn,p1,p2). */
  ip_address_to_lprt_repr (&addr, port, bytes, sizeof (bytes));

  /* Send PORT request.  */
  request = ftp_request ("LPRT", bytes);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      closeport (-1);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      closeport (-1);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      closeport (-1);
      return FTPPORTERR;
    }
  xfree (respline);
  return FTPOK;
}

static void
ip_address_to_eprt_repr (const ip_address *addr, unsigned short port, char *buf, 
                         size_t buflen)
{
  int afnum;

  assert (addr != NULL);
  assert (addr->type == IPv4_ADDRESS || addr->type == IPv6_ADDRESS);
  assert (buf != NULL);
  /* buf must contain the argument of EPRT (of the form |af|addr|port|). 
   * 4 chars for the | separators, INET6_ADDRSTRLEN chars for addr  
   * 1 char for af (1-2) and 5 chars for port (0-65535) */
  assert (buflen >= 4 + INET6_ADDRSTRLEN + 1 + 5); 

  /* Construct the argument of EPRT (of the form |af|addr|port|). */
  afnum = (addr->type == IPv4_ADDRESS ? 1 : 2);
  snprintf (buf, buflen, "|%d|%s|%d|", afnum, pretty_print_address (addr), port);
  buf[buflen - 1] = '\0';
}

/* Bind a port and send the appropriate PORT command to the FTP
   server.  Use acceptport after RETR, to get the socket of data
   connection.  */
uerr_t
ftp_eprt (struct rbuf *rbuf)
{
  uerr_t err;
  char *request, *respline;
  ip_address addr;
  int nwritten;
  unsigned short port;
  /* Must contain the argument of EPRT (of the form |af|addr|port|). 
   * 4 chars for the | separators, ENABLE_IPV6_ADDRSTRLEN chars for addr  
   * 1 char for af (1-2) and 5 chars for port (0-65535) */
  char bytes[4 + INET6_ADDRSTRLEN + 1 + 5 + 1];

  assert (rbuf != NULL);
  assert (rbuf_initialized_p(rbuf));

  /* Get the address of this side of the connection. */
  if (!conaddr (RBUF_FD (rbuf), &addr))
    return BINDERR;

  assert (addr.type == IPv4_ADDRESS || addr.type == IPv6_ADDRESS);

  /* Setting port to 0 lets the system choose a free port.  */
  port = 0;

  /* Bind the port.  */
  err = bindport (&addr, &port);
  if (err != BINDOK)
    return err;

  /* Construct the argument of LPRT (of the form af,n,h1,h2,...,hn,p1,p2). */
  ip_address_to_eprt_repr (&addr, port, bytes, sizeof (bytes));

  /* Send PORT request.  */
  request = ftp_request ("EPRT", bytes);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      closeport (-1);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      closeport (-1);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      closeport (-1);
      return FTPPORTERR;
    }
  xfree (respline);
  return FTPOK;
}
#endif

/* Similar to ftp_port, but uses `PASV' to initiate the passive FTP
   transfer.  Reads the response from server and parses it.  Reads the
   host and port addresses and returns them.  */
uerr_t
ftp_pasv (struct rbuf *rbuf, ip_address *addr, unsigned short *port)
{
  char *request, *respline, *s;
  int nwritten, i;
  uerr_t err;
  unsigned char tmp[6];

  assert (rbuf != NULL);
  assert (rbuf_initialized_p(rbuf));
  assert (addr != NULL);
  assert (port != NULL);

  memset (addr, 0, sizeof (ip_address));

  /* Form the request.  */
  request = ftp_request ("PASV", NULL);
  /* And send it.  */
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get the server response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPNOPASV;
    }
  /* Parse the request.  */
  s = respline;
  for (s += 4; *s && !ISDIGIT (*s); s++);
  if (!*s)
    return FTPINVPASV;
  for (i = 0; i < 6; i++)
    {
      tmp[i] = 0;
      for (; ISDIGIT (*s); s++)
        tmp[i] = (*s - '0') + 10 * tmp[i];
      if (*s == ',')
        s++;
      else if (i < 5)
        {
          /* When on the last number, anything can be a terminator.  */
          xfree (respline);
          return FTPINVPASV;
        }
    }
  xfree (respline);

  addr->type = IPv4_ADDRESS;
  /* Mauro Tortonesi: is this safe and/or elegant enough? */
  memcpy (&addr->addr.ipv4.addr, tmp, 4);
  *port = ((tmp[4] << 8) & 0xff00) + tmp[5];

  return FTPOK;
}

#ifdef ENABLE_IPV6
/* Similar to ftp_lprt, but uses `LPSV' to initiate the passive FTP
   transfer.  Reads the response from server and parses it.  Reads the
   host and port addresses and returns them.  */
uerr_t
ftp_lpsv (struct rbuf *rbuf, ip_address *addr, unsigned short *port)
{
  char *request, *respline, *s;
  int nwritten, i, af, addrlen, portlen;
  uerr_t err;
  unsigned char tmp[16];
  unsigned char tmpprt[2];

  assert (rbuf != NULL);
  assert (rbuf_initialized_p(rbuf));
  assert (addr != NULL);
  assert (port != NULL);

  memset (addr, 0, sizeof (ip_address));

  /* Form the request.  */
  request = ftp_request ("LPSV", NULL);

  /* And send it.  */
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);

  /* Get the server response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPNOPASV;
    }  

  /* Parse the response.  */
  s = respline;
  for (s += 4; *s && !ISDIGIT (*s); s++);
  if (!*s)
    return FTPINVPASV;

  /* First, get the address family */
  af = 0;
  for (; ISDIGIT (*s); s++)
    af = (*s - '0') + 10 * af;

  if (af != 4 && af != 6)
    {
      xfree (respline);
      return FTPINVPASV;
    }

  if (!*s || *s++ != ',')
    {
      xfree (respline);
      return FTPINVPASV;
    }

  /* Then, get the address length */
  addrlen = 0;
  for (; ISDIGIT (*s); s++)
    addrlen = (*s - '0') + 10 * addrlen;

  if (!*s || *s++ != ',')
    {
      xfree (respline);
      return FTPINVPASV;
    }

  if (addrlen > 16)
    {
      xfree (respline);
      return FTPINVPASV;
    }

  if ((af == 4 && addrlen != 4)
      || (af == 6 && addrlen != 16))
    {
      xfree (respline);
      return FTPINVPASV;
    }

  /* Now, we get the actual address */
  for (i = 0; i < addrlen; i++)
    {
      tmp[i] = 0;
      for (; ISDIGIT (*s); s++)
        tmp[i] = (*s - '0') + 10 * tmp[i];
      if (*s == ',')
        s++;
      else
        {
          xfree (respline);
          return FTPINVPASV;
        }
    }

  /* Now, get the port length */
  portlen = 0;
  for (; ISDIGIT (*s); s++)
    portlen = (*s - '0') + 10 * portlen;

  if (!*s || *s++ != ',')
    {
      xfree (respline);
      return FTPINVPASV;
    }

  if (portlen > 2)
    {
      xfree (respline);
      return FTPINVPASV;
    }

  /* Finally, we get the port number */
  tmpprt[0] = 0;
  for (; ISDIGIT (*s); s++)
    tmpprt[0] = (*s - '0') + 10 * tmpprt[0];

  if (!*s || *s++ != ',')
    {
      xfree (respline);
      return FTPINVPASV;
    }

  tmpprt[1] = 0;
  for (; ISDIGIT (*s); s++)
    tmpprt[1] = (*s - '0') + 10 * tmpprt[1];

  assert (s != NULL);

  if (af == 4)
    {
      addr->type = IPv4_ADDRESS;
      memcpy (&addr->addr.ipv4.addr, tmp, 4);
      *port = ((tmpprt[0] << 8) & 0xff00) + tmpprt[1];
      DEBUGP (("lpsv addr is: %s\n", pretty_print_address(addr)));
      DEBUGP (("tmpprt[0] is: %d\n", tmpprt[0]));
      DEBUGP (("tmpprt[1] is: %d\n", tmpprt[1]));
      DEBUGP (("*port is: %d\n", *port));
    }
  else
    {
      assert (af == 6);
      addr->type = IPv6_ADDRESS;
      memcpy (&addr->addr.ipv6.addr, tmp, 16);
      *port = ((tmpprt[0] << 8) & 0xff00) + tmpprt[1];
      DEBUGP (("lpsv addr is: %s\n", pretty_print_address(addr)));
      DEBUGP (("tmpprt[0] is: %d\n", tmpprt[0]));
      DEBUGP (("tmpprt[1] is: %d\n", tmpprt[1]));
      DEBUGP (("*port is: %d\n", *port));
    }

  xfree (respline);
  return FTPOK;
}

/* Similar to ftp_eprt, but uses `EPSV' to initiate the passive FTP
   transfer.  Reads the response from server and parses it.  Reads the
   host and port addresses and returns them.  */
uerr_t
ftp_epsv (struct rbuf *rbuf, ip_address *addr, unsigned short *port)
{
  char *request, *respline, *start, delim, *s;
  int nwritten, i;
  uerr_t err;
  unsigned short tport;
  socklen_t addrlen;
  struct sockaddr_storage ss;
  struct sockaddr *sa = (struct sockaddr *)&ss;

  assert (rbuf != NULL);
  assert (rbuf_initialized_p(rbuf));
  assert (addr != NULL);
  assert (port != NULL);

  addrlen = sizeof (ss);
  if (getpeername (rbuf->fd, sa, &addrlen) < 0)
    /* Mauro Tortonesi: HOW DO WE HANDLE THIS ERROR? */
    return CONPORTERR;

  assert (sa->sa_family == AF_INET || sa->sa_family == AF_INET6);

  sockaddr_get_address (sa, NULL, addr);

  /* Form the request.  */
  /* EPSV 1 means that we ask for IPv4 and EPSV 2 means that we ask for IPv6. */
  request = ftp_request ("EPSV", (sa->sa_family == AF_INET ? "1" : "2"));

  /* And send it.  */
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);

  /* Get the server response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPNOPASV;
    }  

  assert (respline != NULL);

  DEBUGP(("respline is %s\n", respline));

  /* Parse the response.  */
  s = respline;

  /* Skip the useless stuff and get what's inside the parentheses */
  start = strchr (respline, '(');
  if (start == NULL)
    {
      xfree (respline);
      return FTPINVPASV;
    }  

  /* Skip the first two void fields */
  s = start + 1;
  delim = *s++;
  if (delim < 33 || delim > 126)
    {
      xfree (respline);
      return FTPINVPASV;
    }  

  for (i = 0; i < 2; i++)
    {
      if (*s++ != delim) 
        {
          xfree (respline);
        return FTPINVPASV;
        }  
    }

  /* Finally, get the port number */
  tport = 0; 
  for (i = 1; ISDIGIT (*s); s++) 
    {
      if (i > 5)
        {
          xfree (respline);
          return FTPINVPASV;
        }  
      tport = (*s - '0') + 10 * tport;
    }

  /* Make sure that the response terminates correcty */
  if (*s++ != delim)
    {
      xfree (respline);
      return FTPINVPASV;
    }  

  if (*s++ != ')')
    {
      xfree (respline);
      return FTPINVPASV;
    }  

  *port = tport;

  xfree (respline);
  return FTPOK;
}
#endif

/* Sends the TYPE request to the server.  */
uerr_t
ftp_type (struct rbuf *rbuf, int type)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;
  char stype[2];

  /* Construct argument.  */
  stype[0] = type;
  stype[1] = 0;
  /* Send TYPE request.  */
  request = ftp_request ("TYPE", stype);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPUNKNOWNTYPE;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Changes the working directory by issuing a CWD command to the
   server.  */
uerr_t
ftp_cwd (struct rbuf *rbuf, const char *dir)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send CWD request.  */
  request = ftp_request ("CWD", dir);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline == '5')
    {
      xfree (respline);
      return FTPNSFOD;
    }
  if (*respline != '2')
    {
      xfree (respline);
      return FTPRERR;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends REST command to the FTP server.  */
uerr_t
ftp_rest (struct rbuf *rbuf, long offset)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;
  static char numbuf[24]; /* Buffer for the number */

  number_to_string (numbuf, offset);
  request = ftp_request ("REST", numbuf);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline != '3')
    {
      xfree (respline);
      return FTPRESTFAIL;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends RETR command to the FTP server.  */
uerr_t
ftp_retr (struct rbuf *rbuf, const char *file)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send RETR request.  */
  request = ftp_request ("RETR", file);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline == '5')
    {
      xfree (respline);
      return FTPNSFOD;
    }
  if (*respline != '1')
    {
      xfree (respline);
      return FTPRERR;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends the LIST command to the server.  If FILE is NULL, send just
   `LIST' (no space).  */
uerr_t
ftp_list (struct rbuf *rbuf, const char *file)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send LIST request.  */
  request = ftp_request ("LIST", file);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate respone.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline == '5')
    {
      xfree (respline);
      return FTPNSFOD;
    }
  if (*respline != '1')
    {
      xfree (respline);
      return FTPRERR;
    }
  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends the SYST command to the server. */
uerr_t
ftp_syst (struct rbuf *rbuf, enum stype *server_type)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send SYST request.  */
  request = ftp_request ("SYST", NULL);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);

  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline == '5')
    {
      xfree (respline);
      return FTPSRVERR;
    }

  /* Skip the number (215, but 200 (!!!) in case of VMS) */
  strtok (respline, " ");

  /* Which system type has been reported (we are interested just in the
     first word of the server response)?  */
  request = strtok (NULL, " ");

  if (!strcasecmp (request, "VMS"))
    *server_type = ST_VMS;
  else if (!strcasecmp (request, "UNIX"))
    *server_type = ST_UNIX;
  else if (!strcasecmp (request, "WINDOWS_NT"))
    *server_type = ST_WINNT;
  else if (!strcasecmp (request, "MACOS"))
    *server_type = ST_MACOS;
  else if (!strcasecmp (request, "OS/400"))
    *server_type = ST_OS400;
  else
    *server_type = ST_OTHER;

  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends the PWD command to the server. */
uerr_t
ftp_pwd (struct rbuf *rbuf, char **pwd)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send PWD request.  */
  request = ftp_request ("PWD", NULL);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      return err;
    }
  if (*respline == '5')
    {
      xfree (respline);
      return FTPSRVERR;
    }

  /* Skip the number (257), leading citation mark, trailing citation mark
     and everything following it. */
  strtok (respline, "\"");
  request = strtok (NULL, "\"");

  /* Has the `pwd' been already allocated?  Free! */
  FREE_MAYBE (*pwd);

  *pwd = xstrdup (request);

  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* Sends the SIZE command to the server, and returns the value in 'size'.
 * If an error occurs, size is set to zero. */
uerr_t
ftp_size (struct rbuf *rbuf, const char *file, long int *size)
{
  char *request, *respline;
  int nwritten;
  uerr_t err;

  /* Send PWD request.  */
  request = ftp_request ("SIZE", file);
  nwritten = iwrite (RBUF_FD (rbuf), request, strlen (request));
  if (nwritten < 0)
    {
      xfree (request);
      *size = 0;
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      xfree (respline);
      *size = 0;
      return err;
    }
  if (*respline == '5')
    {
      /* 
       * Probably means SIZE isn't supported on this server.
       * Error is nonfatal since SIZE isn't in RFC 959 
       */
      xfree (respline);
      *size = 0;
      return FTPOK;
    }

  errno = 0;
  *size = strtol (respline + 4, NULL, 0);
  if (errno) 
    {
      /* 
       * Couldn't parse the response for some reason.  On the (few)
       * tests I've done, the response is 213 <SIZE> with nothing else -
       * maybe something a bit more resilient is necessary.  It's not a
       * fatal error, however.
       */
      xfree (respline);
      *size = 0;
      return FTPOK;
    }

  xfree (respline);
  /* All OK.  */
  return FTPOK;
}

/* If URL's params are of the form "type=X", return character X.
   Otherwise, return 'I' (the default type).  */
char
ftp_process_type (const char *params)
{
  if (params
      && 0 == strncasecmp (params, "type=", 5)
      && params[5] != '\0')
    return TOUPPER (params[5]);
  else
    return 'I';
}
