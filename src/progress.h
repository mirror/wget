/* Download progress.
   Copyright (C) 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
\(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef PROGRESS_H
#define PROGRESS_H

int valid_progress_implementation_p PARAMS ((const char *));
void set_progress_implementation PARAMS ((const char *));
void progress_schedule_redirect PARAMS ((void));

void *progress_create PARAMS ((long, long));
void progress_update PARAMS ((void *, long, long));
void progress_finish PARAMS ((void *, long));

RETSIGTYPE progress_handle_sigwinch PARAMS ((int));

#endif /* PROGRESS_H */
