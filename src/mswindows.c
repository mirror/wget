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
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <math.h>

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

#ifndef ES_SYSTEM_REQUIRED
#define ES_SYSTEM_REQUIRED  0x00000001
#endif

#ifndef ES_CONTINUOUS
#define ES_CONTINUOUS       0x80000000
#endif


/* Defined in log.c.  */
void log_request_redirect_output PARAMS ((const char *));

static DWORD set_sleep_mode (DWORD mode);

static DWORD pwr_mode = 0;
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
  if (pwr_mode)
     set_sleep_mode (pwr_mode);
  pwr_mode = 0;
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
      ws_cleanup ();
      return FALSE;
    }
  return TRUE;
}

static char *title_buf = NULL;
static char *curr_url  = NULL;
static int   num_urls  = 0;

void
ws_changetitle (const char *url, int nurl)
{
  if (!nurl)
    return;

  num_urls = nurl;
  if (title_buf)
     xfree(title_buf);
  if (curr_url)
     xfree(curr_url);
  title_buf = (char *)xmalloc (strlen (url) + 20);
  curr_url = xstrdup(url);
  sprintf(title_buf, "Wget %s%s", url, nurl == 1 ? "" : " ...");
  SetConsoleTitle(title_buf);
}

void
ws_percenttitle (double percent)
{
  if (num_urls == 1 && title_buf && curr_url && fabs(percent) <= 100.0)
    {
      sprintf (title_buf, "Wget [%.0f%%] %s", percent, curr_url);
      SetConsoleTitle (title_buf);
    }
}

char *
ws_mypath (void)
{
  static char *wspathsave = NULL;
  char buffer[MAX_PATH];
  char *ptr;

  if (wspathsave)
    {
      return wspathsave;
    }

  if (GetModuleFileName (NULL, buffer, MAX_PATH) &&
      (ptr = strrchr (buffer, PATH_SEPARATOR)) != NULL)
    {
      *(ptr + 1) = '\0';
      wspathsave = xstrdup (buffer);
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
          WinHelp (NULL, buf, HELP_INDEX, 0);
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
  pwr_mode = set_sleep_mode (0);
  SetConsoleCtrlHandler (ws_handler, TRUE);
}

/* Replacement utime function for buggy Borland C++Builder 5.5 compiler.
   (The Borland utime function only works on Windows NT.)  */

#ifdef HACK_BCC_UTIME_BUG
int
borland_utime (const char *path, const struct utimbuf *times)
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

/*
 * Prevent Windows entering sleep/hibernation-mode while wget is doing
 * a lengthy transfer.  Windows does by default not consider network
 * activity in console-programs as activity !  Works on Win-98/ME/2K
 * and up.
 */
static DWORD
set_sleep_mode (DWORD mode)
{
  HMODULE mod = LoadLibrary ("kernel32.dll");
  DWORD (WINAPI *_SetThreadExecutionState) (DWORD) = NULL;
  DWORD rc = (DWORD)-1;

  if (mod)
     (void *)_SetThreadExecutionState
       = GetProcAddress ((HINSTANCE)mod, "SetThreadExecutionState");

  if (_SetThreadExecutionState)
    {
      if (mode == 0)  /* first time */
	mode = (ES_SYSTEM_REQUIRED | ES_CONTINUOUS);
      rc = (*_SetThreadExecutionState) (mode);
    }
  if (mod)
    FreeLibrary (mod);
  DEBUGP (("set_sleep_mode(): mode 0x%08lX, rc 0x%08lX\n", mode, rc));
  return rc;
}

/* run_with_timeout Windows implementation. */

 /* Stack size 0 uses default thread stack-size (reserve+commit).
  * Determined by what's in the PE header.
 */
#define THREAD_STACK_SIZE  0

struct thread_data {
   void (*fun) (void *);
   void  *arg;
   DWORD ws_error; 
};

/* The callback that runs FUN(ARG) in a separate thread.  This
   function exists for two reasons: a) to not require FUN to be
   declared WINAPI/__stdcall[1], and b) to retrieve Winsock errors,
   which are per-thread.  The latter is useful when FUN calls Winsock
   functions, which is how run_with_timeout is used in Wget.

   [1] MSVC can use __fastcall globally (cl /Gr) and on Watcom this is
   the default (wcc386 -3r).  */

static DWORD WINAPI 
thread_helper (void *arg)
{
  struct thread_data *td = (struct thread_data *) arg;

  /* Initialize Winsock error to what it was in the parent.  That way
     the subsequent call to WSAGetLastError will return the same value
     if td->fun doesn't change Winsock error state.  */
  WSASetLastError (td->ws_error);

  td->fun (td->arg);

  /* Return Winsock error to the caller, in case FUN ran Winsock
     code.  */
  td->ws_error = WSAGetLastError ();
  return 0; 
}

/* Call FUN(ARG), but don't allow it to run for more than TIMEOUT
   seconds.  Returns non-zero if the function was interrupted with a
   timeout, zero otherwise.

   This works by running FUN in a separate thread and terminating the
   thread if it doesn't finish in the specified time.  */

int
run_with_timeout (double seconds, void (*fun) (void *), void *arg)
{
  static HANDLE thread_hnd = NULL;
  struct thread_data thread_arg;
  DWORD  thread_id;
  int    rc = 0;

  DEBUGP (("seconds %.2f, ", seconds));
  
  if (seconds == 0)
    {
    blocking_fallback:
      fun (arg);
      return 0;
    }

  /* Should never happen, but test for recursivety anyway */
  assert (thread_hnd == NULL);  

  thread_arg.fun = fun;
  thread_arg.arg = arg;
  thread_arg.ws_error = WSAGetLastError ();
  thread_hnd = CreateThread (NULL, THREAD_STACK_SIZE, thread_helper,
			     &thread_arg, 0, &thread_id); 
  if (!thread_hnd)
    {
      DEBUGP (("CreateThread() failed; %s\n", strerror (GetLastError ())));
      goto blocking_fallback;
    }

  if (WaitForSingleObject (thread_hnd, (DWORD)(1000 * seconds))
      == WAIT_OBJECT_0)
    {
      /* Propagate error state (which is per-thread) to this thread,
	 so the caller can inspect it.  */
      WSASetLastError (thread_arg.ws_error);
      DEBUGP (("Winsock error: %d\n", WSAGetLastError ()));
      rc = 0;
    }
  else
    {
      TerminateThread (thread_hnd, 1);
      rc = 1;
    }

  CloseHandle (thread_hnd); /* clear-up after TerminateThread() */
  thread_hnd = NULL;
  return rc;
}
