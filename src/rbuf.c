/* Buffering read.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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

/* This is a simple implementation of buffering IO-read functions.  */

#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif

#include "wget.h"
#include "rbuf.h"
#include "connect.h"

#ifdef HAVE_SSL
#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include "gen_sslfunc.h"	/* for ssl_iread */
#endif /* HAVE_SSL */

void
rbuf_initialize (struct rbuf *rbuf, int fd)
{
  rbuf->fd = fd;
#ifdef HAVE_SSL
/* pointing ssl to NULL results in an unchanged behaviour */
  rbuf->ssl = NULL;
#endif /* HAVE_SSL */
  rbuf->buffer_pos = rbuf->buffer;
  rbuf->buffer_left = 0;
}

int
rbuf_initialized_p (struct rbuf *rbuf)
{
  return rbuf->fd != -1;
}

void
rbuf_uninitialize (struct rbuf *rbuf)
{
  rbuf->fd = -1;
}

int
rbuf_read_bufferful (struct rbuf *rbuf)
{
#ifdef HAVE_SSL
  if (rbuf->ssl)
    return ssl_iread (rbuf->ssl, rbuf->buffer, sizeof (rbuf->buffer));
  else
#endif
    return iread (rbuf->fd, rbuf->buffer, sizeof (rbuf->buffer));
}

/* Currently unused -- see RBUF_READCHAR.  */
#if 0
/* Function version of RBUF_READCHAR.  */
int
rbuf_readchar (struct rbuf *rbuf, char *store)
{
  return RBUF_READCHAR (rbuf, store);
}
#endif

/* Like rbuf_readchar(), only don't move the buffer position.  */
int
rbuf_peek (struct rbuf *rbuf, char *store)
{
  if (!rbuf->buffer_left)
    {
      int res;
      rbuf->buffer_pos = rbuf->buffer;
      rbuf->buffer_left = 0;
#ifdef HAVE_SSL
		if (rbuf->ssl != NULL) {
		res = ssl_iread (rbuf->ssl, rbuf->buffer, sizeof (rbuf->buffer));
		} else {
#endif /* HAVE_SSL */
		res = iread (rbuf->fd, rbuf->buffer, sizeof (rbuf->buffer));
#ifdef HAVE_SSL
      }
#endif /* HAVE_SSL */
      if (res <= 0)
	return res;
      rbuf->buffer_left = res;
    }
  *store = *rbuf->buffer_pos;
  return 1;
}

/* Flush RBUF's buffer to WHERE.  Flush MAXSIZE bytes at most.
   Returns the number of bytes actually copied.  If the buffer is
   empty, 0 is returned.  */
int
rbuf_flush (struct rbuf *rbuf, char *where, int maxsize)
{
  if (!rbuf->buffer_left)
    return 0;
  else
    {
      int howmuch = MINVAL (rbuf->buffer_left, maxsize);

      if (where)
	memcpy (where, rbuf->buffer_pos, howmuch);
      rbuf->buffer_left -= howmuch;
      rbuf->buffer_pos += howmuch;
      return howmuch;
    }
}

/* Discard any cached data in RBUF.  */
void
rbuf_discard (struct rbuf *rbuf)
{
  rbuf->buffer_left = 0;
  rbuf->buffer_pos = rbuf->buffer;
}
