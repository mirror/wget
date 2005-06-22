/* Declarations for log.c.
   Copyright (C) 2003 Free Software Foundation, Inc.

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

#ifndef LOG_H
#define LOG_H

/* The log file to which Wget writes to after HUP.  */
#define DEFAULT_LOGFILE "wget-log"

enum log_options { LOG_VERBOSE, LOG_NOTQUIET, LOG_NONVERBOSE, LOG_ALWAYS };

void logprintf (enum log_options, const char *, ...)
     GCC_FORMAT_ATTR (2, 3);
void debug_logprintf (const char *, ...) GCC_FORMAT_ATTR (1, 2);
void logputs (enum log_options, const char *);
void logflush (void);
void log_set_flush (bool);
bool log_set_save_context (bool);

void log_init (const char *, bool);
void log_close (void);
void log_cleanup (void);
void log_request_redirect_output (const char *);

const char *escnonprint (const char *);
const char *escnonprint_uri (const char *);

#endif /* LOG_H */
