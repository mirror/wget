/* Declarations for rbuf.c.
   Copyright (C) 1998 Free Software Foundation, Inc.

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

#ifndef RBUF_H
#define RBUF_H

/* Retrieval stream */
struct rbuf
{
  int fd;
  char buffer[4096];		/* the input buffer */
  char *buffer_pos;		/* current position in the buffer */
  size_t buffer_left;		/* number of bytes left in the buffer:
				   buffer_left = buffer_end - buffer_pos */
  int internal_dont_touch_this;	/* used by RBUF_READCHAR macro */
};

/* Read a character from RBUF.  If there is anything in the buffer,
   the character is returned from the buffer.  Otherwise, refill the
   buffer and return the first character.

   The return value is the same as with read(2).  On buffered read,
   the function returns 1.

   #### That return value is totally screwed up, and is a direct
   result of historical implementation of header code.  The macro
   should return the character or EOF, and in case of error store it
   to rbuf->err or something.  */
#define RBUF_READCHAR(rbuf, store)					\
((rbuf)->buffer_left							\
 ? (--(rbuf)->buffer_left,						\
    *((char *) (store)) = *(rbuf)->buffer_pos++, 1)			\
 : ((rbuf)->buffer_pos = (rbuf)->buffer,				\
    ((((rbuf)->internal_dont_touch_this					\
       = iread ((rbuf)->fd, (rbuf)->buffer,				\
		sizeof ((rbuf)->buffer))) <= 0)				\
     ? (rbuf)->internal_dont_touch_this					\
     : ((rbuf)->buffer_left = (rbuf)->internal_dont_touch_this - 1,	\
	*((char *) (store)) = *(rbuf)->buffer_pos++,			\
	1))))

/* Return the file descriptor of RBUF.  */
#define RBUF_FD(rbuf) ((rbuf)->fd)

/* Function declarations */
void rbuf_initialize PARAMS ((struct rbuf *, int));
int rbuf_initialized_p PARAMS ((struct rbuf *));
void rbuf_uninitialize PARAMS ((struct rbuf *));
int rbuf_readchar PARAMS ((struct rbuf *, char *));
int rbuf_peek PARAMS ((struct rbuf *, char *));
int rbuf_flush PARAMS ((struct rbuf *, char *, int));
void rbuf_discard PARAMS ((struct rbuf *));

#endif /* RBUF_H */
