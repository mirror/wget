/* Declarations for FTP support.
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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

#ifndef FTP_H
#define FTP_H

/* Need it for struct rbuf.  */
#include "rbuf.h"

uerr_t ftp_response PARAMS ((struct rbuf *, char **));
uerr_t ftp_login PARAMS ((struct rbuf *, const char *, const char *));
uerr_t ftp_port PARAMS ((struct rbuf *));
uerr_t ftp_pasv PARAMS ((struct rbuf *, unsigned char *));
uerr_t ftp_type PARAMS ((struct rbuf *, int));
uerr_t ftp_cwd PARAMS ((struct rbuf *, const char *));
uerr_t ftp_retr PARAMS ((struct rbuf *, const char *));
uerr_t ftp_rest PARAMS ((struct rbuf *, long));
uerr_t ftp_list PARAMS ((struct rbuf *, const char *));

struct urlinfo;

/* File types.  */
enum ftype
{
  FT_PLAINFILE,
  FT_DIRECTORY,
  FT_SYMLINK,
  FT_UNKNOWN
};


/* Globbing (used by ftp_retrieve_glob).  */
enum
{
  GLOBALL, GETALL, GETONE
};

/* Information about one filename in a linked list.  */
struct fileinfo
{
  enum ftype type;		/* file type */
  char *name;			/* file name */
  long size;			/* file size */
  long tstamp;			/* time-stamp */
  int perms;			/* file permissions */
  char *linkto;			/* link to which file points */
  struct fileinfo *prev;	/* previous... */
  struct fileinfo *next;	/* ...and next structure. */
};

/* Commands for FTP functions.  */
enum command
{
  DO_LOGIN      = 0x0001,	/* Connect and login to the server.  */
  DO_CWD        = 0x0002,	/* Change current directory.  */
  DO_RETR       = 0x0004,	/* Retrieve the file.  */
  DO_LIST       = 0x0008,	/* Retrieve the directory list.  */
  LEAVE_PENDING = 0x0010	/* Do not close the socket.  */
};

enum fstatus
{
  NOTHING       = 0x0000,	/* Nothing done yet.  */
  ON_YOUR_OWN   = 0x0001,	/* The ftp_loop_internal sets the
				   defaults.  */
  DONE_CWD      = 0x0002	/* The current working directory is
				   correct.  */
};

typedef struct
{
  int st;			/* connection status */
  int cmd;			/* command code */
  struct rbuf rbuf;		/* control connection buffer */
  long dltime;			/* time of the download */
} ccon;

struct fileinfo *ftp_parse_ls PARAMS ((const char *));
uerr_t ftp_loop PARAMS ((struct urlinfo *, int *));

#endif /* FTP_H */
