/* mswindows.c -- Windows-specific support
   Copyright (C) 1995, 1996, 1997, 1998  Free Software Foundation, Inc.

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

/* #### Someone please document what these functions do!  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#ifdef HACK_BCC_UTIME_BUG
# include <io.h>
# include <fcntl.h>
# ifdef HAVE_UTIME_H
#  include <utime.h>
# endif
# ifdef HAVE_SYS_UTIME_H
#  include <sys/utime.h>
# endif
#endif

#include "wget.h"
#include "utils.h"
#include "url.h"

#ifndef errno
extern int errno;
#endif

/* Defined in log.c.  */
void log_request_redirect_output PARAMS ((const char *));

static int windows_nt_p;


#ifndef HAVE_SLEEP
/* Emulation of Unix sleep.  */

unsigned int
sleep (unsigned seconds)
{
  return SleepEx (1000 * seconds, TRUE) ? 0U : 1000 * seconds;
}
#endif

#ifndef HAVE_USLEEP
/* Emulation of Unix usleep().  This has a granularity of
   milliseconds, but that's ok because:

   a) Wget is only using it with milliseconds [not anymore, but b)
      still applies];

   b) You can't rely on usleep's granularity anyway.  If a caller
   expects usleep to respect every microsecond, he's in for a
   surprise.  */

int
usleep (unsigned long usec)
{
  SleepEx (usec / 1000, TRUE);
  return 0;
}
#endif  /* HAVE_USLEEP */

static char *
read_registry (HKEY hkey, char *subkey, char *valuename, char *buf, int *len)
{
  HKEY result;
  DWORD size = *len;
  DWORD type = REG_SZ;
  if (RegOpenKeyEx (hkey, subkey, 0, KEY_READ, &result) != ERROR_SUCCESS)
    return NULL;
  if (RegQueryValueEx (result, valuename, NULL, &type, (LPBYTE)buf, &size) != ERROR_SUCCESS)
    buf = NULL;
  *len = size;
  RegCloseKey (result);
  return buf;
}

void
windows_main_junk (int *argc, char **argv, char **exec_name)
{
  char *p;

  /* Remove .EXE from filename if it has one.  */
  *exec_name = xstrdup (*exec_name);
  p = strrchr (*exec_name, '.');
  if (p)
    *p = '\0';
}

/* Winsock stuff. */

static void
ws_cleanup (void)
{
  WSACleanup ();
}

static void
ws_hangup (void)
{
  log_request_redirect_output ("CTRL+Break");
}

void
fork_to_background (void)
{
  /* Whether we arrange our own version of opt.lfilename here.  */
  int changedp = 0;

  if (!opt.lfilename)
    {
      opt.lfilename = unique_name (DEFAULT_LOGFILE, 0);
      changedp = 1;
    }
  printf (_("Continuing in background.\n"));
  if (changedp)
    printf (_("Output will be written to `%s'.\n"), opt.lfilename);

  ws_hangup ();
  if (!windows_nt_p)
    FreeConsole ();
}

static BOOL WINAPI
ws_handler (DWORD dwEvent)
{
  switch (dwEvent)
    {
#ifdef CTRLC_BACKGND
    case CTRL_C_EVENT:
#endif
#ifdef CTRLBREAK_BACKGND
    case CTRL_BREAK_EVENT:
#endif
      fork_to_background ();
      break;
    case CTRL_SHUTDOWN_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    default:
      WSACleanup ();
      return FALSE;
    }
  return TRUE;
}

void
ws_changetitle (char *url, int nurl)
{
  char *title_buf;
  if (!nurl)
    return;

  title_buf = (char *)alloca (strlen (url) + 20);
  sprintf (title_buf, "Wget %s%s", url, nurl == 1 ? "" : " ...");
  SetConsoleTitle (title_buf);
}

char *
ws_mypath (void)
{
  static char *wspathsave;
  char buffer[MAX_PATH];
  char *ptr;

  if (wspathsave)
    {
      return wspathsave;
    }

  GetModuleFileName (NULL, buffer, MAX_PATH);

  ptr = strrchr (buffer, '\\');
  if (ptr)
    {
      *(ptr + 1) = '\0';
      wspathsave = (char*) xmalloc (strlen (buffer) + 1);
      strcpy (wspathsave, buffer);
    }
  else
    wspathsave = NULL;
  return wspathsave;
}

void
ws_help (const char *name)
{
  char *mypath = ws_mypath ();

  if (mypath)
    {
      struct stat sbuf;
      char *buf = (char *)alloca (strlen (mypath) + strlen (name) + 4 + 1);
      sprintf (buf, "%s%s.HLP", mypath, name);
      if (stat (buf, &sbuf) == 0) 
	{
          printf (_("Starting WinHelp %s\n"), buf);
          WinHelp (NULL, buf, HELP_INDEX, NULL);
        }
      else
        {
          printf ("%s: %s\n", buf, strerror (errno));
        }
    }
}

void
ws_startup (void)
{
  WORD requested;
  WSADATA data;
  int err;
  OSVERSIONINFO os;

  if (GetVersionEx (&os) == TRUE
      && os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    windows_nt_p = 1;

  requested = MAKEWORD (1, 1);
  err = WSAStartup (requested, &data);

  if (err != 0)
    {
      fprintf (stderr, _("%s: Couldn't find usable socket driver.\n"),
	       exec_name);
      exit (1);
    }

  if (data.wVersion < requested)
    {
      fprintf (stderr, _("%s: Couldn't find usable socket driver.\n"),
	       exec_name);
      WSACleanup ();
      exit (1);
    }
  atexit (ws_cleanup);
  SetConsoleCtrlHandler (ws_handler, TRUE);
}

/* Replacement utime function for buggy Borland C++Builder 5.5 compiler.
   (The Borland utime function only works on Windows NT.)  */

#ifdef HACK_BCC_UTIME_BUG
int borland_utime(const char *path, const struct utimbuf *times)
{
  int fd;
  int res;
  struct ftime ft;
  struct tm *ptr_tm;

  if ((fd = open (path, O_RDWR)) < 0)
    return -1;

  ptr_tm = localtime (&times->modtime);
  ft.ft_tsec = ptr_tm->tm_sec >> 1;
  ft.ft_min = ptr_tm->tm_min;
  ft.ft_hour = ptr_tm->tm_hour;
  ft.ft_day = ptr_tm->tm_mday;
  ft.ft_month = ptr_tm->tm_mon + 1;
  ft.ft_year = ptr_tm->tm_year - 80;
  res = setftime (fd, &ft);
  close (fd);
  return res;
}
#endif
