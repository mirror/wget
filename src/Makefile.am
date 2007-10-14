# Makefile for `wget' utility
# Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003,
# 2004, 2005, 2006, 2007 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with Wget.  If not, see <http://www.gnu.org/licenses/>.

# In addition, as a special exception, the Free Software Foundation
# gives permission to link the code of its release of Wget with the
# OpenSSL project's "OpenSSL" library (or with modified versions of it
# that use the same license as the "OpenSSL" library), and distribute
# the linked executables.  You must obey the GNU General Public License
# in all respects for all of the code used other than "OpenSSL".  If you
# modify this file, you may extend this exception to your version of the
# file, but you are not obligated to do so.  If you do not wish to do
# so, delete this exception statement from your version.

#
# Version: @VERSION@
#

# The following line is losing on some versions of make!
DEFS     = @DEFS@ -DSYSTEM_WGETRC=\"$(sysconfdir)/wgetrc\" -DLOCALEDIR=\"$(localedir)\"
LIBS     = @LIBS@ @LIBSSL@ @LIBGNUTLS@ @LIBINTL@

bin_PROGRAMS = wget
wget_SOURCES = cmpt.c connect.c convert.c cookies.c ftp.c ftp-basic.c	\
	       ftp-ls.c hash.c host.c html-parse.c html-url.c http.c	\
	       init.c log.c main.c netrc.c progress.c ptimer.c recur.c	\
	       res.c retr.c safe-ctype.c snprintf.c spider.c url.c	\
	       utils.c version.c xmalloc.c				\
	       config-post.h connect.h convert.h cookies.h 		\
	       ftp.h gen-md5.h gnu-md5.h hash.h host.h html-parse.h \
	       http.h http-ntlm.h init.h log.h mswindows.h netrc.h \
	       options.h progress.h ptimer.h recur.h res.h retr.h safe-ctype.h \
	       spider.h ssl.h sysdep.h url.h utils.h wget.h xmalloc.h
EXTRA_wget_SOURCES = mswindows.c
LDADD = $(ALLOCA) $(LIBOBJS) ../lib/libgnu.a

version.c: hg-id
	printf '%s' 'const char *version_string = "@VERSION@' > $@
	-HG_ID=$$(cat hg-id); [ "$$HG_ID" ] && printf '%s' " ($${HG_ID})" >> $@
	printf '%s\n' '";' >> $@

.INTERMEDIATE: hg-id
.PHONY: hg-id
hg-id: $(wget_SOURCES) $(LDADD)
	-( hg id | cut -f 1 -d ' ' ) 2>/dev/null > $@

check_LIBRARIES = libunittest.a
libunittest_a_SOURCES = $(wget_SOURCES) test.c test.h
libunittest_a_CPPFLAGS = -DTESTING
libunittest_a_LIBADD = $(ALLOCA) $(LIBOBJS)

CLEANFILES = *~ *.bak core core.[0-9]*
