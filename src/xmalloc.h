/* xmalloc.c declarations.
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

#ifndef XMALLOC_H
#define XMALLOC_H

/* Define this if you want primitive but extensive malloc debugging.
   It will make Wget extremely slow, so only do it in development
   builds.  */
#define DEBUG_MALLOC

/* When DEBUG_MALLOC is not defined (which is normally the case), the
   allocation functions directly map to *_real wrappers.  In the
   DEBUG_MALLOC mode, they also record the file and line where the
   offending malloc/free/... was invoked.

   *Note*: xfree(NULL) aborts.  If the pointer you're freeing can be
   NULL, use xfree_null instead.  */

#ifndef DEBUG_MALLOC

#define xmalloc  xmalloc_real
#define xmalloc0 xmalloc0_real
#define xrealloc xrealloc_real
#define xstrdup  xstrdup_real
#define xfree    xfree_real

void *xmalloc_real PARAMS ((size_t));
void *xmalloc0_real PARAMS ((size_t));
void *xrealloc_real PARAMS ((void *, size_t));
char *xstrdup_real PARAMS ((const char *));
void xfree_real PARAMS ((void *));

#else  /* DEBUG_MALLOC */

#define xmalloc(s)     xmalloc_debug (s, __FILE__, __LINE__)
#define xmalloc0(s)    xmalloc0_debug (s, __FILE__, __LINE__)
#define xrealloc(p, s) xrealloc_debug (p, s, __FILE__, __LINE__)
#define xstrdup(p)     xstrdup_debug (p, __FILE__, __LINE__)
#define xfree(p)       xfree_debug (p, __FILE__, __LINE__)

void *xmalloc_debug PARAMS ((size_t, const char *, int));
void *xmalloc0_debug PARAMS ((size_t, const char *, int));
void *xrealloc_debug PARAMS ((void *, size_t, const char *, int));
char *xstrdup_debug PARAMS ((const char *, const char *, int));
void xfree_debug PARAMS ((void *, const char *, int));

#endif /* DEBUG_MALLOC */

/* Macros that interface to malloc, but know about type sizes, and
   cast the result to the appropriate type.  The casts are not
   necessary in standard C, but Wget performs them anyway for the sake
   of pre-standard environments and possibly C++.  */

#define xnew(type) ((type *) xmalloc (sizeof (type)))
#define xnew0(type) ((type *) xmalloc0 (sizeof (type)))
#define xnew_array(type, len) ((type *) xmalloc ((len) * sizeof (type)))
#define xnew0_array(type, len) ((type *) xmalloc0 ((len) * sizeof (type)))

#define alloca_array(type, size) ((type *) alloca ((size) * sizeof (type)))

/* Free P if it is non-NULL.  C requires free() to behaves this way by
   default, but Wget's code is historically careful not to pass NULL
   to free.  This allows us to assert p!=NULL in xfree to check
   additional errors.  (But we currently don't do that!)  */
#define xfree_null(p) if (!(p)) ; else xfree (p)

#endif /* XMALLOC_H */
