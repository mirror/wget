/* File Transfer Protocol support.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <ctype.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

#include "wget.h"
#include "utils.h"
#include "url.h"
#include "rbuf.h"
#include "retr.h"
#include "ftp.h"
#include "html.h"
#include "connect.h"
#include "host.h"
#include "fnmatch.h"
#include "netrc.h"

#ifndef errno
extern int errno;
#endif
#ifndef h_errno
extern int h_errno;
#endif

/* File where the "ls -al" listing will be saved.  */
#define LIST_FILENAME ".listing"

extern char ftp_last_respline[];

/* Look for regexp "( *[0-9]+ *byte" (literal parenthesis) anywhere in
   the string S, and return the number converted to long, if found, 0
   otherwise.  */
static long
ftp_expected_bytes (const char *s)
{
  long res;

  while (1)
    {
      while (*s && *s != '(')
	++s;
      if (!*s)
	return 0;
      for (++s; *s && ISSPACE (*s); s++);
      if (!*s)
	return 0;
      if (!ISDIGIT (*s))
	continue;
      res = 0;
      do
	{
	  res = (*s - '0') + 10 * res;
	  ++s;
	}
      while (*s && ISDIGIT (*s));
      if (!*s)
	return 0;
      while (*s && ISSPACE (*s))
	++s;
      if (!*s)
	return 0;
      if (tolower (*s) != 'b')
	continue;
      if (strncasecmp (s, "byte", 4))
	continue;
      else
	break;
    }
  return res;
}

/* Retrieves a file with denoted parameters through opening an FTP
   connection to the server.  It always closes the data connection,
   and closes the control connection in case of error.  */
static uerr_t
getftp (const struct urlinfo *u, long *len, long restval, ccon *con)
{
  int csock, dtsock, res;
  uerr_t err;
  FILE *fp;
  char *user, *passwd, *respline;
  char *tms, *tmrate;
  unsigned char pasv_addr[6];
  int cmd = con->cmd;
  int passive_mode_open = 0;
  long expected_bytes = 0L;

  assert (con != NULL);
  assert (u->local != NULL);
  /* Debug-check of the sanity of the request by making sure that LIST
     and RETR are never both requested (since we can handle only one
     at a time.  */
  assert (!((cmd & DO_LIST) && (cmd & DO_RETR)));
  /* Make sure that at least *something* is requested.  */
  assert ((cmd & (DO_LIST | DO_CWD | DO_RETR | DO_LOGIN)) != 0);

  user = u->user;
  passwd = u->passwd;
  search_netrc (u->host, (const char **)&user, (const char **)&passwd, 1);
  user = user ? user : opt.ftp_acc;
  if (!opt.ftp_pass)
    opt.ftp_pass = xstrdup (ftp_getaddress ());
  passwd = passwd ? passwd : opt.ftp_pass;
  assert (user && passwd);

  dtsock = -1;
  con->dltime = 0;

  if (!(cmd & DO_LOGIN))
    csock = RBUF_FD (&con->rbuf);
  else				/* cmd & DO_LOGIN */
    {
      /* Login to the server: */

      /* First: Establish the control connection.  */
      logprintf (LOG_VERBOSE, _("Connecting to %s:%hu... "), u->host, u->port);
      err = make_connection (&csock, u->host, u->port);
      if (cmd & LEAVE_PENDING)
	rbuf_initialize (&con->rbuf, csock);
      else
	rbuf_uninitialize (&con->rbuf);
      switch (err)
	{
	  /* Do not close the socket in first several cases, since it
	     wasn't created at all.  */
	case HOSTERR:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, "%s: %s\n", u->host, herrmsg (h_errno));
	  return HOSTERR;
	  break;
	case CONSOCKERR:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, "socket: %s\n", strerror (errno));
	  return CONSOCKERR;
	  break;
	case CONREFUSED:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Connection to %s:%hu refused.\n"),
		     u->host, u->port);
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return CONREFUSED;
	case CONERROR:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, "connect: %s\n", strerror (errno));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return CONERROR;
	  break;
	default:
	  DO_NOTHING;
	  /* #### Hmm?  */
	}
      /* Since this is a new connection, we may safely discard
	 anything left in the buffer.  */
      rbuf_discard (&con->rbuf);

      /* Second: Login with proper USER/PASS sequence.  */
      logputs (LOG_VERBOSE, _("connected!\n"));
      logprintf (LOG_VERBOSE, _("Logging in as %s ... "), user);
      if (opt.server_response)
	logputs (LOG_ALWAYS, "\n");
      err = ftp_login (&con->rbuf, user, passwd);
      /* FTPRERR, FTPSRVERR, WRITEFAILED, FTPLOGREFUSED, FTPLOGINC */
      switch (err)
	{
	case FTPRERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPSRVERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("Error in server greeting.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case WRITEFAILED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET,
		   _("Write failed, closing control connection.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPLOGREFUSED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("The server refuses login.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return FTPLOGREFUSED;
	  break;
	case FTPLOGINC:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("Login incorrect.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return FTPLOGINC;
	  break;
	case FTPOK:
	  if (!opt.server_response)
	    logputs (LOG_VERBOSE, _("Logged in!\n"));
	  break;
	default:
	  abort ();
	  exit (1);
	  break;
	}
      /* Third: Set type to Image (binary).  */
      if (!opt.server_response)
	logprintf (LOG_VERBOSE, "==> TYPE %c ... ", toupper (u->ftp_type));
      err = ftp_type (&con->rbuf, toupper (u->ftp_type));
      /* FTPRERR, WRITEFAILED, FTPUNKNOWNTYPE */
      switch (err)
	{
	case FTPRERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case WRITEFAILED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET,
		   _("Write failed, closing control connection.\n"));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPUNKNOWNTYPE:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET,
		     _("Unknown type `%c', closing control connection.\n"),
		     toupper (u->ftp_type));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	case FTPOK:
	  /* Everything is OK.  */
	  break;
	default:
	  abort ();
	  break;
	}
      if (!opt.server_response)
	logputs (LOG_VERBOSE, _("done.  "));
    } /* do login */

  if (cmd & DO_CWD)
    {
      if (!*u->dir)
	logputs (LOG_VERBOSE, _("==> CWD not needed.\n"));
      else
	{
	  /* Change working directory.  */
	  if (!opt.server_response)
	    logprintf (LOG_VERBOSE, "==> CWD %s ... ", u->dir);
	  err = ftp_cwd (&con->rbuf, u->dir);
	  /* FTPRERR, WRITEFAILED, FTPNSFOD */
	  switch (err)
	    {
	    case FTPRERR:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	      CLOSE (csock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case WRITEFAILED:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET,
		       _("Write failed, closing control connection.\n"));
	      CLOSE (csock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case FTPNSFOD:
	      logputs (LOG_VERBOSE, "\n");
	      logprintf (LOG_NOTQUIET, _("No such directory `%s'.\n\n"),
			 u->dir);
	      CLOSE (csock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case FTPOK:
	      /* fine and dandy */
	      break;
	    default:
	      abort ();
	      break;
	    }
	  if (!opt.server_response)
	    logputs (LOG_VERBOSE, _("done.\n"));
	}
    }
  else /* do not CWD */
    logputs (LOG_VERBOSE, _("==> CWD not required.\n"));

  /* If anything is to be retrieved, PORT (or PASV) must be sent.  */
  if (cmd & (DO_LIST | DO_RETR))
    {
      if (opt.ftp_pasv)
	{
	  char thost[256];
	  unsigned short tport;

	  if (!opt.server_response)
	    logputs (LOG_VERBOSE, "==> PASV ... ");
	  err = ftp_pasv (&con->rbuf, pasv_addr);
	  /* FTPRERR, WRITEFAILED, FTPNOPASV, FTPINVPASV */
	  switch (err)
	    {
	    case FTPRERR:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	      CLOSE (csock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case WRITEFAILED:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET,
		       _("Write failed, closing control connection.\n"));
	      CLOSE (csock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case FTPNOPASV:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("Cannot initiate PASV transfer.\n"));
	      break;
	    case FTPINVPASV:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("Cannot parse PASV response.\n"));
	      break;
	    case FTPOK:
	      /* fine and dandy */
	      break;
	    default:
	      abort ();
	      break;
	    }
	  if (err==FTPOK)
	    {
	      sprintf (thost, "%d.%d.%d.%d",
		       pasv_addr[0], pasv_addr[1], pasv_addr[2], pasv_addr[3]);
	      tport = (pasv_addr[4] << 8) + pasv_addr[5];
	      DEBUGP ((_("Will try connecting to %s:%hu.\n"), thost, tport));
	      err = make_connection (&dtsock, thost, tport);
	      switch (err)
		{
		  /* Do not close the socket in first several cases,
		     since it wasn't created at all.  */
		case HOSTERR:
		  logputs (LOG_VERBOSE, "\n");
		  logprintf (LOG_NOTQUIET, "%s: %s\n", thost,
			     herrmsg (h_errno));
		  CLOSE (csock);
		  rbuf_uninitialize (&con->rbuf);
		  return HOSTERR;
		  break;
		case CONSOCKERR:
		  logputs (LOG_VERBOSE, "\n");
		  logprintf (LOG_NOTQUIET, "socket: %s\n", strerror (errno));
		  CLOSE (csock);
		  rbuf_uninitialize (&con->rbuf);
		  return CONSOCKERR;
		  break;
		case CONREFUSED:
		  logputs (LOG_VERBOSE, "\n");
		  logprintf (LOG_NOTQUIET,
			     _("Connection to %s:%hu refused.\n"),
			     thost, tport);
		  CLOSE (csock);
		  rbuf_uninitialize (&con->rbuf);
		  closeport (dtsock);
		  return CONREFUSED;
		case CONERROR:
		  logputs (LOG_VERBOSE, "\n");
		  logprintf (LOG_NOTQUIET, "connect: %s\n",
			     strerror (errno));
		  CLOSE (csock);
		  rbuf_uninitialize (&con->rbuf);
		  closeport (dtsock);
		  return CONERROR;
		  break;
		default:
		  /* #### What?!  */
		  DO_NOTHING;
		}
	      passive_mode_open= 1;  /* Flag to avoid accept port */
	      if (!opt.server_response)
		logputs (LOG_VERBOSE, _("done.    "));
	    } /* err==FTP_OK */
	}

      if (!passive_mode_open)   /* Try to use a port command if PASV failed */
	{
	  if (!opt.server_response)
	    logputs (LOG_VERBOSE, "==> PORT ... ");
	  err = ftp_port (&con->rbuf);
	  /* FTPRERR, WRITEFAILED, bindport (CONSOCKERR, CONPORTERR, BINDERR,
	     LISTENERR), HOSTERR, FTPPORTERR */
	  switch (err)
	    {
	    case FTPRERR:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	      CLOSE (csock);
	      closeport (dtsock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case WRITEFAILED:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET,
		       _("Write failed, closing control connection.\n"));
	      CLOSE (csock);
	      closeport (dtsock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case CONSOCKERR:
	      logputs (LOG_VERBOSE, "\n");
	      logprintf (LOG_NOTQUIET, "socket: %s\n", strerror (errno));
	      CLOSE (csock);
	      closeport (dtsock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case CONPORTERR: case BINDERR: case LISTENERR:
	      /* What now?  These problems are local...  */
	      logputs (LOG_VERBOSE, "\n");
	      logprintf (LOG_NOTQUIET, _("Bind error (%s).\n"),
			 strerror (errno));
	      closeport (dtsock);
	      return err;
	      break;
	    case HOSTERR:
	      logputs (LOG_VERBOSE, "\n");
	      logprintf (LOG_NOTQUIET, "%s: %s\n", u->host,
			 herrmsg (h_errno));
	      CLOSE (csock);
	      closeport (dtsock);
	      rbuf_uninitialize (&con->rbuf);
	      return HOSTERR;
	      break;
	    case FTPPORTERR:
	      logputs (LOG_VERBOSE, "\n");
	      logputs (LOG_NOTQUIET, _("Invalid PORT.\n"));
	      CLOSE (csock);
	      closeport (dtsock);
	      rbuf_uninitialize (&con->rbuf);
	      return err;
	      break;
	    case FTPOK:
	      /* fine and dandy */
	      break;
	    default:
	      abort ();
	      break;
	    } /* port switch */
	  if (!opt.server_response)
	    logputs (LOG_VERBOSE, _("done.    "));
	} /* dtsock == -1 */
    } /* cmd & (DO_LIST | DO_RETR) */

  /* Restart if needed.  */
  if (restval && (cmd & DO_RETR))
    {
      if (!opt.server_response)
	logprintf (LOG_VERBOSE, "==> REST %ld ... ", restval);
      err = ftp_rest (&con->rbuf, restval);

      /* FTPRERR, WRITEFAILED, FTPRESTFAIL */
      switch (err)
	{
	case FTPRERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case WRITEFAILED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET,
		   _("Write failed, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPRESTFAIL:
	  logputs (LOG_VERBOSE, _("\nREST failed, starting from scratch.\n"));
	  restval = 0L;
	  break;
	case FTPOK:
	  /* fine and dandy */
	  break;
	default:
	  abort ();
	  break;
	}
      if (err != FTPRESTFAIL && !opt.server_response)
	logputs (LOG_VERBOSE, _("done.    "));
    } /* restval && cmd & DO_RETR */

  if (cmd & DO_RETR)
    {
      if (opt.verbose)
	{
	  if (!opt.server_response)
	    {
	      if (restval)
		logputs (LOG_VERBOSE, "\n");
	      logprintf (LOG_VERBOSE, "==> RETR %s ... ", u->file);
	    }
	}
      err = ftp_retr (&con->rbuf, u->file);
      /* FTPRERR, WRITEFAILED, FTPNSFOD */
      switch (err)
	{
	case FTPRERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case WRITEFAILED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET,
		   _("Write failed, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPNSFOD:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("No such file `%s'.\n\n"), u->file);
	  closeport (dtsock);
	  return err;
	  break;
	case FTPOK:
	  /* fine and dandy */
	  break;
	default:
	  abort ();
	  break;
	}

      if (!opt.server_response)
	logputs (LOG_VERBOSE, _("done.\n"));
      expected_bytes = ftp_expected_bytes (ftp_last_respline);
    } /* do retrieve */

  if (cmd & DO_LIST)
    {
      if (!opt.server_response)
	logputs (LOG_VERBOSE, "==> LIST ... ");
      /* As Maciej W. Rozycki (macro@ds2.pg.gda.pl) says, `LIST'
	 without arguments is better than `LIST .'; confirmed by
	 RFC959.  */
      err = ftp_list (&con->rbuf, NULL);
      /* FTPRERR, WRITEFAILED */
      switch (err)
	{
	case FTPRERR:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case WRITEFAILED:
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET,
		   _("Write failed, closing control connection.\n"));
	  CLOSE (csock);
	  closeport (dtsock);
	  rbuf_uninitialize (&con->rbuf);
	  return err;
	  break;
	case FTPNSFOD:
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("No such file or directory `%s'.\n\n"),
		     ".");
	  closeport (dtsock);
	  return err;
	  break;
	case FTPOK:
	  /* fine and dandy */
	  break;
	default:
	  abort ();
	  break;
	}
      if (!opt.server_response)
	logputs (LOG_VERBOSE, _("done.\n"));
      expected_bytes = ftp_expected_bytes (ftp_last_respline);
    } /* cmd & DO_LIST */

  /* If no transmission was required, then everything is OK.  */
  if (!(cmd & (DO_LIST | DO_RETR)))
    return RETRFINISHED;

  if (!passive_mode_open)  /* we are not using pasive mode so we need
			      to accept */
    {
      /* Open the data transmission socket by calling acceptport().  */
      err = acceptport (&dtsock);
      /* Possible errors: ACCEPTERR.  */
      if (err == ACCEPTERR)
	{
	  logprintf (LOG_NOTQUIET, "accept: %s\n", strerror (errno));
	  return err;
	}
    }

  /* Open the file -- if opt.dfp is set, use it instead.  */
  if (!opt.dfp || con->cmd & DO_LIST)
    {
      mkalldirs (u->local);
      if (opt.backups)
	rotate_backups (u->local);
      /* #### Is this correct? */
      chmod (u->local, 0600);

      fp = fopen (u->local, restval ? "ab" : "wb");
      if (!fp)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s\n", u->local, strerror (errno));
	  CLOSE (csock);
	  rbuf_uninitialize (&con->rbuf);
	  closeport (dtsock);
	  return FOPENERR;
	}
    }
  else
    fp = opt.dfp;

  if (*len)
    {
      logprintf (LOG_VERBOSE, _("Length: %s"), legible (*len));
      if (restval)
	logprintf (LOG_VERBOSE, _(" [%s to go]"), legible (*len - restval));
      logputs (LOG_VERBOSE, "\n");
    }
  else if (expected_bytes)
    {
      logprintf (LOG_VERBOSE, _("Length: %s"), legible (expected_bytes));
      if (restval)
	logprintf (LOG_VERBOSE, _(" [%s to go]"),
		   legible (expected_bytes - restval));
      logputs (LOG_VERBOSE, _(" (unauthoritative)\n"));
    }
  reset_timer ();
  /* Get the contents of the document.  */
  res = get_contents (dtsock, fp, len, restval, expected_bytes, &con->rbuf);
  con->dltime = elapsed_time ();
  tms = time_str (NULL);
  tmrate = rate (*len - restval, con->dltime);
  /* Close data connection socket.  */
  closeport (dtsock);
  /* Close the local file.  */
  if (!opt.dfp || con->cmd & DO_LIST)
    fclose (fp);
  else
    fflush (fp);
  /* If get_contents couldn't write to fp, bail out.  */
  if (res == -2)
    {
      logprintf (LOG_NOTQUIET, _("%s: %s, closing control connection.\n"),
		 u->local, strerror (errno));
      CLOSE (csock);
      rbuf_uninitialize (&con->rbuf);
      return FWRITEERR;
    }
  else if (res == -1)
    {
      logprintf (LOG_NOTQUIET, _("%s (%s) - Data connection: %s; "),
		 tms, tmrate, strerror (errno));
      if (opt.server_response)
	logputs (LOG_ALWAYS, "\n");
    }

  /* Get the server to tell us if everything is retrieved.  */
  err = ftp_response (&con->rbuf, &respline);
  /* ...and empty the buffer.  */
  rbuf_discard (&con->rbuf);
  if (err != FTPOK)
    {
      free (respline);
      /* The control connection is decidedly closed.  Print the time
	 only if it hasn't already been printed.  */
      if (res != -1)
	logprintf (LOG_NOTQUIET, "%s (%s) - ", tms, tmrate);
      logputs (LOG_NOTQUIET, _("Control connection closed.\n"));
      /* If there is an error on the control connection, close it, but
	 return FTPRETRINT, since there is a possibility that the
	 whole file was retrieved nevertheless (but that is for
	 ftp_loop_internal to decide).  */
      CLOSE (csock);
      rbuf_uninitialize (&con->rbuf);
      return FTPRETRINT;
    } /* err != FTPOK */
  /* If retrieval failed for any reason, return FTPRETRINT, but do not
     close socket, since the control connection is still alive.  If
     there is something wrong with the control connection, it will
     become apparent later.  */
  if (*respline != '2')
    {
      free (respline);
      if (res != -1)
	logprintf (LOG_NOTQUIET, "%s (%s) - ", tms, tmrate);
      logputs (LOG_NOTQUIET, _("Data transfer aborted.\n"));
      return FTPRETRINT;
    }
  free (respline);

  if (res == -1)
    {
      /* What now?  The data connection was erroneous, whereas the
	 response says everything is OK.  We shall play it safe.  */
      return FTPRETRINT;
    }

  if (!(cmd & LEAVE_PENDING))
    {
      /* I should probably send 'QUIT' and check for a reply, but this
	 is faster.  #### Is it OK, though?  */
      CLOSE (csock);
      rbuf_uninitialize (&con->rbuf);
    }
  /* If it was a listing, and opt.server_response is true,
     print it out.  */
  if (opt.server_response && (con->cmd & DO_LIST))
    {
      mkalldirs (u->local);
      fp = fopen (u->local, "r");
      if (!fp)
	logprintf (LOG_ALWAYS, "%s: %s\n", u->local, strerror (errno));
      else
	{
	  char *line;
	  /* The lines are being read with read_whole_line because of
	     no-buffering on opt.lfile.  */
	  while ((line = read_whole_line (fp)))
	    {
	      logprintf (LOG_ALWAYS, "%s\n", line);
	      free (line);
	    }
	  fclose (fp);
	}
    } /* con->cmd & DO_LIST && server_response */

  return RETRFINISHED;
}

/* A one-file FTP loop.  This is the part where FTP retrieval is
   retried, and retried, and retried, and...

   This loop either gets commands from con, or (if ON_YOUR_OWN is
   set), makes them up to retrieve the file given by the URL.  */
static uerr_t
ftp_loop_internal (struct urlinfo *u, struct fileinfo *f, ccon *con)
{
  static int first_retrieval = 1;

  int count, orig_lp;
  long restval, len;
  char *tms, *tmrate, *locf;
  uerr_t err;
  struct stat st;

  if (!u->local)
    u->local = url_filename (u);

  if (opt.noclobber && file_exists_p (u->local))
    {
      logprintf (LOG_VERBOSE,
		 _("File `%s' already there, not retrieving.\n"), u->local);
      /* If the file is there, we suppose it's retrieved OK.  */
      return RETROK;
    }

  /* Remove it if it's a link.  */
  remove_link (u->local);
  if (!opt.output_document)
    locf = u->local;
  else
    locf = opt.output_document;

  count = 0;

  if (con->st & ON_YOUR_OWN)
    con->st = ON_YOUR_OWN;

  orig_lp = con->cmd & LEAVE_PENDING ? 1 : 0;

  /* THE loop.  */
  do
    {
      /* Increment the pass counter.  */
      ++count;
      /* Wait before the retrieval (unless this is the very first
	 retrieval).  */
      if (!first_retrieval && opt.wait)
	sleep (opt.wait);
      if (first_retrieval)
	first_retrieval = 0;
      if (con->st & ON_YOUR_OWN)
	{
	  con->cmd = 0;
	  con->cmd |= (DO_RETR | LEAVE_PENDING);
	  if (rbuf_initialized_p (&con->rbuf))
	    con->cmd &= ~ (DO_LOGIN | DO_CWD);
	  else
	    con->cmd |= (DO_LOGIN | DO_CWD);
	}
      else /* not on your own */
	{
	  if (rbuf_initialized_p (&con->rbuf))
	    con->cmd &= ~DO_LOGIN;
	  else
	    con->cmd |= DO_LOGIN;
	  if (con->st & DONE_CWD)
	    con->cmd &= ~DO_CWD;
	  else
	    con->cmd |= DO_CWD;
	}
      /* Assume no restarting.  */
      restval = 0L;
      if ((count > 1 || opt.always_rest)
	  && !(con->cmd & DO_LIST)
	  && file_exists_p (u->local))
	if (stat (u->local, &st) == 0)
	  restval = st.st_size;
      /* Get the current time string.  */
      tms = time_str (NULL);
      /* Print fetch message, if opt.verbose.  */
      if (opt.verbose)
	{
	  char *hurl = str_url (u->proxy ? u->proxy : u, 1);
	  char tmp[15];
	  strcpy (tmp, "        ");
	  if (count > 1)
	    sprintf (tmp, _("(try:%2d)"), count);
	  logprintf (LOG_VERBOSE, "--%s--  %s\n  %s => `%s'\n",
		     tms, hurl, tmp, locf);
#ifdef WINDOWS
	  ws_changetitle (hurl, 1);
#endif
	  free (hurl);
	}
      /* Send getftp the proper length, if fileinfo was provided.  */
      if (f)
	len = f->size;
      else
	len = 0;
      err = getftp (u, &len, restval, con);
      /* Time?  */
      tms = time_str (NULL);
      tmrate = rate (len - restval, con->dltime);

      if (!rbuf_initialized_p (&con->rbuf))
	con->st &= ~DONE_CWD;
      else
	con->st |= DONE_CWD;

      switch (err)
	{
	case HOSTERR: case CONREFUSED: case FWRITEERR: case FOPENERR:
	case FTPNSFOD: case FTPLOGINC: case FTPNOPASV:
	  /* Fatal errors, give up.  */
	  return err;
	  break;
	case CONSOCKERR: case CONERROR: case FTPSRVERR: case FTPRERR:
	case WRITEFAILED: case FTPUNKNOWNTYPE: case CONPORTERR:
	case BINDERR: case LISTENERR: case ACCEPTERR:
	case FTPPORTERR: case FTPLOGREFUSED: case FTPINVPASV:
	  printwhat (count, opt.ntry);
	  /* non-fatal errors */
	  continue;
	  break;
	case FTPRETRINT:
	  /* If the control connection was closed, the retrieval
	     will be considered OK if f->size == len.  */
	  if (!f || len != f->size)
	    {
	      printwhat (count, opt.ntry);
	      continue;
	    }
	  break;
	case RETRFINISHED:
	  /* Great!  */
	  break;
	default:
	  /* Not as great.  */
	  abort ();
	}
      if (con->st & ON_YOUR_OWN)
	{
	  CLOSE (RBUF_FD (&con->rbuf));
	  rbuf_uninitialize (&con->rbuf);
	}
      logprintf (LOG_VERBOSE, _("%s (%s) - `%s' saved [%ld]\n\n"),
		 tms, tmrate, locf, len);
      logprintf (LOG_NONVERBOSE, "%s URL: %s [%ld] -> \"%s\" [%d]\n",
		 tms, u->url, len, locf, count);
      /* Do not count listings among the downloaded stuff, since they
	 will get deleted anyway.  */
      if (!(con->cmd & DO_LIST))
	{
	  ++opt.numurls;
	  opt.downloaded += len;
	}
      /* Restore the original leave-pendingness.  */
      if (orig_lp)
	con->cmd |= LEAVE_PENDING;
      else
	con->cmd &= ~LEAVE_PENDING;
      return RETROK;
    } while (!opt.ntry || (count < opt.ntry));

  if (rbuf_initialized_p (&con->rbuf) && (con->st & ON_YOUR_OWN))
    {
      CLOSE (RBUF_FD (&con->rbuf));
      rbuf_uninitialize (&con->rbuf);
    }
  return TRYLIMEXC;
}

/* Return the directory listing in a reusable format.  The directory
   is specifed in u->dir.  */
static struct fileinfo *
ftp_get_listing (struct urlinfo *u, ccon *con)
{
  struct fileinfo *f;
  uerr_t err;
  char *olocal = u->local;
  char *list_filename, *ofile;

  con->st &= ~ON_YOUR_OWN;
  con->cmd |= (DO_LIST | LEAVE_PENDING);
  con->cmd &= ~DO_RETR;
  /* Get the listing filename.  */
  ofile = u->file;
  u->file = LIST_FILENAME;
  list_filename = url_filename (u);
  u->file = ofile;
  u->local = list_filename;
  DEBUGP ((_("Using `%s' as listing tmp file.\n"), list_filename));
  err = ftp_loop_internal (u, NULL, con);
  u->local = olocal;
  if (err == RETROK)
    f = ftp_parse_ls (list_filename);
  else
    f = NULL;
  if (opt.remove_listing)
    {
      if (unlink (list_filename))
	logprintf (LOG_NOTQUIET, "unlink: %s\n", strerror (errno));
      else
	logprintf (LOG_VERBOSE, _("Removed `%s'.\n"), list_filename);
    }
  free (list_filename);
  con->cmd &= ~DO_LIST;
  return f;
}

static uerr_t ftp_retrieve_dirs PARAMS ((struct urlinfo *, struct fileinfo *,
					 ccon *));
static uerr_t ftp_retrieve_glob PARAMS ((struct urlinfo *, ccon *, int));
static struct fileinfo *delelement PARAMS ((struct fileinfo *,
					    struct fileinfo **));
static void freefileinfo PARAMS ((struct fileinfo *f));

/* Retrieve a list of files given in struct fileinfo linked list.  If
   a file is a symbolic link, do not retrieve it, but rather try to
   set up a similar link on the local disk, if the symlinks are
   supported.

   If opt.recursive is set, after all files have been retrieved,
   ftp_retrieve_dirs will be called to retrieve the directories.  */
static uerr_t
ftp_retrieve_list (struct urlinfo *u, struct fileinfo *f, ccon *con)
{
  static int depth = 0;
  uerr_t err;
  char *olocal, *ofile;
  struct fileinfo *orig;
  long local_size;
  time_t tml;
  int dlthis;

  /* Increase the depth.  */
  ++depth;
  if (opt.reclevel && depth > opt.reclevel)
    {
      DEBUGP ((_("Recursion depth %d exceeded max. depth %d.\n"),
	       depth, opt.reclevel));
      --depth;
      return RECLEVELEXC;
    }

  assert (f != NULL);
  orig = f;

  con->st &= ~ON_YOUR_OWN;
  if (!(con->st & DONE_CWD))
    con->cmd |= DO_CWD;
  else
    con->cmd &= ~DO_CWD;
  con->cmd |= (DO_RETR | LEAVE_PENDING);

  if (!rbuf_initialized_p (&con->rbuf))
    con->cmd |= DO_LOGIN;
  else
    con->cmd &= ~DO_LOGIN;

  err = RETROK;			/* in case it's not used */

  while (f)
    {
      if (opt.quota && opt.downloaded > opt.quota)
	{
	  --depth;
	  return QUOTEXC;
	}
      olocal = u->local;
      ofile = u->file;
      u->file = f->name;
      u->local = url_filename (u);
      err = RETROK;

      dlthis = 1;
      if (opt.timestamping && f->type == FT_PLAINFILE)
	{
	  struct stat st;
	  if (!stat (u->local, &st))
	    {
	      /* Else, get it from the file.  */
	      local_size = st.st_size;
	      tml = st.st_mtime;
	      if (local_size == f->size && tml >= f->tstamp)
		{
		  logprintf (LOG_VERBOSE, _("\
Local file `%s' is more recent, not retrieving.\n\n"), u->local);
		  dlthis = 0;
		}
	      else if (local_size != f->size)
		{
		  logprintf (LOG_VERBOSE, _("\
The sizes do not match (local %ld), retrieving.\n"), local_size);
		}
	    }
	}	/* opt.timestamping && f->type == FT_PLAINFILE */
      switch (f->type)
	{
	case FT_SYMLINK:
	  /* If opt.retr_symlinks is defined, we treat symlinks as
	     if they were normal files.  There is currently no way
	     to distinguish whether they might be directories, and
	     follow them.  */
	  if (!opt.retr_symlinks)
	    {
#ifdef HAVE_SYMLINK
	      if (!f->linkto)
		logputs (LOG_NOTQUIET,
			 _("Invalid name of the symlink, skipping.\n"));
	      else
		{
                  struct stat st;
		  /* Check whether we already have the correct
                     symbolic link.  */
                  int rc = lstat (u->local, &st);
                  if (rc == 0)
		    {
		      size_t len = strlen (f->linkto) + 1;
		      if (S_ISLNK (st.st_mode))
			{
			  char *link_target = (char *)alloca (len);
			  size_t n = readlink (u->local, link_target, len);
			  if ((n == len - 1)
			      && (memcmp (link_target, f->linkto, n) == 0))
			    {
			      logprintf (LOG_VERBOSE, _("\
Already have correct symlink %s -> %s\n\n"),
					 u->local, f->linkto);
                              dlthis = 0;
			      break;
			    }
			}
		    }
		  logprintf (LOG_VERBOSE, _("Creating symlink %s -> %s\n"),
			     u->local, f->linkto);
		  /* Unlink before creating symlink!  */
		  unlink (u->local);
		  if (symlink (f->linkto, u->local) == -1)
		    logprintf (LOG_NOTQUIET, "symlink: %s\n",
			       strerror (errno));
		  logputs (LOG_VERBOSE, "\n");
		} /* have f->linkto */
#else  /* not HAVE_SYMLINK */
	      logprintf (LOG_NOTQUIET,
			 _("Symlinks not supported, skipping symlink `%s'.\n"),
			 u->local);
#endif /* not HAVE_SYMLINK */
	    }
	  else                /* opt.retr_symlinks */
	    {
	      if (dlthis)
		err = ftp_loop_internal (u, f, con);
	    } /* opt.retr_symlinks */
	  break;
	case FT_DIRECTORY:
	  if (!opt.recursive)
	    logprintf (LOG_NOTQUIET, _("Skipping directory `%s'.\n"),
		       f->name);
	  break;
	case FT_PLAINFILE:
	  /* Call the retrieve loop.  */
	  if (dlthis)
	    err = ftp_loop_internal (u, f, con);
	  break;
	case FT_UNKNOWN:
	  logprintf (LOG_NOTQUIET, _("%s: unknown/unsupported file type.\n"),
		     f->name);
	  break;
	}	/* switch */

      /* Set the time-stamp information to the local file.  Symlinks
	 are not to be stamped because it sets the stamp on the
	 original.  :( */
      if (!opt.dfp
	  && !(f->type == FT_SYMLINK && !opt.retr_symlinks)
	  && f->tstamp != -1
          && dlthis
	  && file_exists_p (u->local))
	{
	  touch (u->local, f->tstamp);
	}
      else if (f->tstamp == -1)
	logprintf (LOG_NOTQUIET, _("%s: corrupt time-stamp.\n"), u->local);

      if (f->perms && dlthis)
	chmod (u->local, f->perms);
      else
	DEBUGP (("Unrecognized permissions for %s.\n", u->local));

      free (u->local);
      u->local = olocal;
      u->file = ofile;
      /* Break on fatals.  */
      if (err == QUOTEXC || err == HOSTERR || err == FWRITEERR)
	break;
      con->cmd &= ~ (DO_CWD | DO_LOGIN);
      f = f->next;
    } /* while */
  /* We do not want to call ftp_retrieve_dirs here */
  if (opt.recursive && !(opt.reclevel && depth >= opt.reclevel))
    err = ftp_retrieve_dirs (u, orig, con);
  else if (opt.recursive)
    DEBUGP ((_("Will not retrieve dirs since depth is %d (max %d).\n"),
	     depth, opt.reclevel));
  --depth;
  return err;
}

/* Retrieve the directories given in a file list.  This function works
   by simply going through the linked list and calling
   ftp_retrieve_glob on each directory entry.  The function knows
   about excluded directories.  */
static uerr_t
ftp_retrieve_dirs (struct urlinfo *u, struct fileinfo *f, ccon *con)
{
  char *odir;
  char *current_container = NULL;
  int current_length = 0;

  for (; f; f = f->next)
    {
      int len;

      if (opt.quota && opt.downloaded > opt.quota)
	break;
      if (f->type != FT_DIRECTORY)
	continue;
      odir = u->dir;
      len = 1 + strlen (u->dir) + 1 + strlen (f->name) + 1;
      /* Allocate u->dir off stack, but reallocate only if a larger
         string is needed.  */
      if (len > current_length)
	current_container = (char *)alloca (len);
      u->dir = current_container;
      /* When retrieving recursively, all directories must be
	 absolute.  This restriction will (hopefully!) be lifted in
	 the future.  */
      sprintf (u->dir, "/%s%s%s", odir + (*odir == '/'),
	      (!*odir || (*odir == '/' && !* (odir + 1))) ? "" : "/", f->name);
      if (!accdir (u->dir, ALLABS))
	{
	  logprintf (LOG_VERBOSE, _("\
Not descending to `%s' as it is excluded/not-included.\n"), u->dir);
	  u->dir = odir;
	  continue;
	}
      con->st &= ~DONE_CWD;
      ftp_retrieve_glob (u, con, GETALL);
      /* Set the time-stamp?  */
      u->dir = odir;
    }
  if (opt.quota && opt.downloaded > opt.quota)
    return QUOTEXC;
  else
    return RETROK;
}


/* A near-top-level function to retrieve the files in a directory.
   The function calls ftp_get_listing, to get a linked list of files.
   Then it weeds out the file names that do not match the pattern.
   ftp_retrieve_list is called with this updated list as an argument.

   If the argument ACTION is GETONE, just download the file (but first
   get the listing, so that the time-stamp is heeded); if it's GLOBALL,
   use globbing; if it's GETALL, download the whole directory.  */
static uerr_t
ftp_retrieve_glob (struct urlinfo *u, ccon *con, int action)
{
  struct fileinfo *orig, *start;
  uerr_t res;

  con->cmd |= LEAVE_PENDING;

  orig = ftp_get_listing (u, con);
  start = orig;
  /* First: weed out that do not conform the global rules given in
     opt.accepts and opt.rejects.  */
  if (opt.accepts || opt.rejects)
    {
      struct fileinfo *f = orig;

      while (f)
	{
	  if (f->type != FT_DIRECTORY && !acceptable (f->name))
	    {
	      logprintf (LOG_VERBOSE, _("Rejecting `%s'.\n"), f->name);
	      f = delelement (f, &start);
	    }
	  else
	    f = f->next;
	}
    }
  /* Now weed out the files that do not match our globbing pattern.
     If we are dealing with a globbing pattern, that is.  */
  if (*u->file && (action == GLOBALL || action == GETONE))
    {
      int matchres = 0;
      struct fileinfo *f = start;

      while (f)
	{
	  matchres = fnmatch (u->file, f->name, 0);
	  if (matchres == -1)
	    {
	      logprintf (LOG_NOTQUIET, "%s: %s\n", u->local,
			 strerror (errno));
	      break;
	    }
	  if (matchres == FNM_NOMATCH)
	    f = delelement (f, &start); /* delete the element from the list */
	  else
	    f = f->next;        /* leave the element in the list */
	}
      if (matchres == -1)
	{
	  freefileinfo (start);
	  return RETRBADPATTERN;
	}
    }
  res = RETROK;
  if (start)
    {
      /* Just get everything.  */
      ftp_retrieve_list (u, start, con);
    }
  else if (!start)
    {
      if (action == GLOBALL)
	{
	  /* No luck.  */
	  /* #### This message SUCKS.  We should see what was the
	     reason that nothing was retrieved.  */
	  logprintf (LOG_VERBOSE, _("No matches on pattern `%s'.\n"), u->file);
	}
      else /* GETONE or GETALL */
	{
	  /* Let's try retrieving it anyway.  */
	  con->st |= ON_YOUR_OWN;
	  res = ftp_loop_internal (u, NULL, con);
	  return res;
	}
    }
  freefileinfo (start);
  if (opt.quota && opt.downloaded > opt.quota)
    return QUOTEXC;
  else
    /* #### Should we return `res' here?  */
    return RETROK;
}

/* The wrapper that calls an appropriate routine according to contents
   of URL.  Inherently, its capabilities are limited on what can be
   encoded into a URL.  */
uerr_t
ftp_loop (struct urlinfo *u, int *dt)
{
  ccon con;			/* FTP connection */
  uerr_t res;

  *dt = 0;

  rbuf_uninitialize (&con.rbuf);
  con.st = ON_YOUR_OWN;
  res = RETROK;			/* in case it's not used */

  /* If the file name is empty, the user probably wants a directory
     index.  We'll provide one, properly HTML-ized.  Unless
     opt.htmlify is 0, of course.  :-) */
  if (!*u->file && !opt.recursive)
    {
      struct fileinfo *f = ftp_get_listing (u, &con);

      if (f)
	{
	  if (opt.htmlify)
	    {
	      char *filename = (opt.output_document
				? xstrdup (opt.output_document)
				: (u->local ? xstrdup (u->local)
				   : url_filename (u)));
	      res = ftp_index (filename, u, f);
	      if (res == FTPOK && opt.verbose)
		{
		  if (!opt.output_document)
		    {
		      struct stat st;
		      long sz;
		      if (stat (filename, &st) == 0)
			sz = st.st_size;
		      else
			sz = -1;
		      logprintf (LOG_NOTQUIET,
				 _("Wrote HTML-ized index to `%s' [%ld].\n"),
				 filename, sz);
		    }
		  else
		    logprintf (LOG_NOTQUIET,
			       _("Wrote HTML-ized index to `%s'.\n"),
			       filename);
		}
	      free (filename);
	    }
	  freefileinfo (f);
	}
    }
  else
    {
      int wild = has_wildcards_p (u->file);
      if ((opt.ftp_glob && wild) || opt.recursive || opt.timestamping)
	{
	  /* ftp_retrieve_glob is a catch-all function that gets called
	     if we need globbing, time-stamping or recursion.  Its
	     third argument is just what we really need.  */
	  ftp_retrieve_glob (u, &con,
			     (opt.ftp_glob && wild) ? GLOBALL : GETONE);
	}
      else
	res = ftp_loop_internal (u, NULL, &con);
    }
  if (res == FTPOK)
    res = RETROK;
  if (res == RETROK)
    *dt |= RETROKF;
  /* If a connection was left, quench it.  */
  if (rbuf_initialized_p (&con.rbuf))
    CLOSE (RBUF_FD (&con.rbuf));
  return res;
}

/* Delete an element from the fileinfo linked list.  Returns the
   address of the next element, or NULL if the list is exhausted.  It
   can modify the start of the list.  */
static struct fileinfo *
delelement (struct fileinfo *f, struct fileinfo **start)
{
  struct fileinfo *prev = f->prev;
  struct fileinfo *next = f->next;

  free (f->name);
  FREE_MAYBE (f->linkto);
  free (f);

  if (next)
    next->prev = prev;
  if (prev)
    prev->next = next;
  else
    *start = next;
  return next;
}

/* Free the fileinfo linked list of files.  */
static void
freefileinfo (struct fileinfo *f)
{
  while (f)
    {
      struct fileinfo *next = f->next;
      free (f->name);
      if (f->linkto)
	free (f->linkto);
      free (f);
      f = next;
    }
}
