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
        logputs (LOG_ALWAYS, "--> PASS Turtle Power!\n");
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

#ifdef ENABLE_IPV6
uerr_t
ftp_eprt (struct rbuf *rbuf)
{
  uerr_t err;

  char *request, *respline;
  ip_address in_addr;
  unsigned short port;

  char ipv6 [8 * (4 * 3 + 3) + 8];
  char *bytes;

  /* Setting port to 0 lets the system choose a free port.  */
  port = 0;
  err = bindport (&port, ip_default_family);
  if (err != BINDOK)	/* Bind the port.  */
    return err;

  /* Get the address of this side of the connection.  */
  if (!conaddr (RBUF_FD (rbuf), &in_addr))
    /* Huh?  This is not BINDERR! */
    return BINDERR;
  inet_ntop (AF_INET6, &in_addr, ipv6, sizeof (ipv6));

  /* Construct the argument of EPRT (of the form |2|IPv6.ascii|PORT.ascii|). */
  bytes = alloca (3 + strlen (ipv6) + 1 + numdigit (port) + 1 + 1);
  sprintf (bytes, "|2|%s|%u|", ipv6, port);
  /* Send PORT request.  */
  request = ftp_request ("EPRT", bytes);
  if (0 > iwrite (RBUF_FD (rbuf), request, strlen (request)))
    {
      closeport (port);
      xfree (request);
      return WRITEFAILED;
    }
  xfree (request);
  /* Get appropriate response.  */
  err = ftp_response (rbuf, &respline);
  if (err != FTPOK)
    {
      closeport (port);
      xfree (respline);
      return err;
    }
  if (*respline != '2')
    {
      closeport (port);
      xfree (respline);
      return FTPPORTERR;
    }
  xfree (respline);
  return FTPOK;
}
#endif

/* Bind a port and send the appropriate PORT command to the FTP
   server.  Use acceptport after RETR, to get the socket of data
   connection.  */
uerr_t
ftp_port (struct rbuf *rbuf)
{
  uerr_t err;
  char *request, *respline;
  char bytes[6 * 4 +1];

  ip_address in_addr;
  ip4_address in_addr_4;
  unsigned char *in_addr4_ptr = (unsigned char *)&in_addr_4;

  int nwritten;
  unsigned short port;
#ifdef ENABLE_IPV6
  /*
    Only try the Extented Version if we actually use IPv6
  */
  if (ip_default_family == AF_INET6)
    {
      err = ftp_eprt (rbuf);
      if (err == FTPOK)
	return err;
    }
#endif
  /* Setting port to 0 lets the system choose a free port.  */
  port = 0;

  err = bindport (&port, AF_INET);
  if (err != BINDOK)
    return err;

  /* Get the address of this side of the connection and convert it
     (back) to IPv4.  */
  if (!conaddr (RBUF_FD (rbuf), &in_addr))
    /* Huh?  This is not BINDERR! */
    return BINDERR;
  if (!map_ip_to_ipv4 (&in_addr, &in_addr_4))
    return BINDERR;

  /* Construct the argument of PORT (of the form a,b,c,d,e,f).  Port
     is unsigned short so (unsigned) (port & 0xff000) >> 8 is the same
     like port >> 8
   */
  sprintf (bytes, "%d,%d,%d,%d,%d,%d",
	   in_addr4_ptr[0], in_addr4_ptr[1], in_addr4_ptr[2], in_addr4_ptr[3],
	   port >> 8, port & 0xff);
  /* Send PORT request.  */
  request = ftp_request ("PORT", bytes);
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
      return FTPPORTERR;
    }
  xfree (respline);
  return FTPOK;
}

#ifdef ENABLE_IPV6
uerr_t
ftp_epsv (struct rbuf *rbuf, ip_address *addr, unsigned short *port, 
	  char *typ)
{
  int err;
  char *s, *respline;
  char *request = ftp_request ("EPSV", typ);
  if (0 > iwrite (RBUF_FD (rbuf), request, strlen (request)))
    {
      xfree (request);
      return WRITEFAILED;
    }
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
  /* respline::=229 Entering Extended Passive Mode (|||6446|) */
  for (s += 4; *s && !ISDIGIT (*s); s++);
  if (!*s)
    return FTPINVPASV;
  *port=0; 
  for (; ISDIGIT (*s); s++) 
    *port = (*s - '0') + 10 * (*port);
  xfree (respline);
  /* Now we have the port but we need the IPv6 :-( */
  {
    wget_sockaddr remote;
    socklen_t addrlen = sizeof (remote);
    struct sockaddr_in *ipv4_sock = (struct sockaddr_in *)&remote;
    getpeername (RBUF_FD (rbuf), (struct sockaddr *)&remote, &addrlen);
    switch(remote.sa.sa_family)
      {
        case AF_INET6:
          memcpy (addr, &remote.sin6.sin6_addr, 16);
	  break;
	case AF_INET:  
          map_ipv4_to_ip ((ip4_address *)&ipv4_sock->sin_addr, addr);
	  break;
	default:
	  abort();
	  return FTPINVPASV;
	  /* realy bad */
      }
  }
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
  unsigned char addr4[4];

#ifdef ENABLE_IPV6
  if (ip_default_family == AF_INET6) 
    {
      err = ftp_epsv (rbuf, addr, port, "2");	/* try IPv6 with EPSV */
      if (FTPOK == err) 
        return FTPOK;
      err = ftp_epsv (rbuf, addr, port, "1");	/* try IPv4 with EPSV */
      if (FTPOK == err) 
        return FTPOK;
    }
#endif  
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
  /* respline::=227 Entering Passive Mode (h1,h2,h3,h4,p1,p2). 	*/
  s = respline;
  for (s += 4; *s && !ISDIGIT (*s); s++);
  if (!*s)
    return FTPINVPASV;
  for (i = 0; i < 4; i++)
    {
      addr4[i] = 0;
      for (; ISDIGIT (*s); s++)
        addr4[i] = (*s - '0') + 10 * addr4[i];
      if (*s == ',')
        s++;
      else
        {
          xfree (respline);
          return FTPINVPASV;
        }
    }

  /* Eventually make an IPv4 in IPv6 adress if needed */
  map_ipv4_to_ip ((ip4_address *)addr4, addr);

  *port=0;
  for (; ISDIGIT (*s); s++)
    *port = (*s - '0') + 10 * (*port);
  if (*s == ',') 
    s++;
  else
    {
      xfree (respline);
      return FTPINVPASV;
    }

  {
    unsigned short port2 = 0; 
    for (; ISDIGIT (*s); s++) 
      port2 = (*s - '0') + 10 * port2;
    *port = (*port) * 256 + port2;
  }
  xfree (respline);
  return FTPOK;
}

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
