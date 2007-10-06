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

PERL     = perl
PERLRUN = $(PERL) -I$(srcdir)

.PHONY: test run-unit-tests run-px-tests

check-local: test

test: ../src/wget$(EXEEXT) run-unit-tests run-px-tests

../src/wget$(EXEEXT):
	cd ../src && $(MAKE) $(AM_MAKEFLAGS)

run-unit-tests: unit-tests$(EXEEXT)
	./unit-tests$(EXEEXT)

run-px-tests: WgetTest.pm
	$(PERLRUN) $(srcdir)/Test-auth-basic.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-c-full.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-c-partial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-c.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-E-k-K.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-E-k.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-ftp.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-HTTP-Content-Disposition-1.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-HTTP-Content-Disposition-2.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-HTTP-Content-Disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N-current-HTTP-CD.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N-current.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N-HTTP-Content-Disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N--no-content-disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N--no-content-disposition-trivial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--no-content-disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--no-content-disposition-trivial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N-old.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-nonexisting-quiet.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-noop.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-np.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-N.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-O-HTTP-Content-Disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-O--no-content-disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-O--no-content-disposition-trivial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-O-nonexisting.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-O.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-Restrict-Lowercase.px && echo && echo
	$(PERLRUN) $(srcdir)/Test-Restrict-Uppercase.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-fail.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-HTTP-Content-Disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider--no-content-disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider--no-content-disposition-trivial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-r-HTTP-Content-Disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-r--no-content-disposition.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-r--no-content-disposition-trivial.px && echo && echo
	$(PERLRUN) $(srcdir)/Test--spider-r.px && echo && echo

EXTRA_DIST = FTPServer.pm FTPTest.pm HTTPServer.pm HTTPTest.pm \
	     Test-auth-basic.px Test-c-full.px Test-c-partial.px \
	     Test-c.px Test-E-k-K.px Test-E-k.px Test-ftp.px \
	     Test-HTTP-Content-Disposition-1.px \
	     Test-HTTP-Content-Disposition-2.px \
	     Test-HTTP-Content-Disposition.px \
	     Test-N-current.px Test-N-old.px Test-nonexisting-quiet.px \
	     Test-noop.px Test-np.px Test-N.px \
	     Test-O-nonexisting.px Test-O.px \
	     Test-Restrict-Lowercase.px Test-Restrict-Uppercase.px \
	     Test--spider-fail.px Test--spider.px Test--spider-r.px

check_PROGRAMS = unit-tests
unit_tests_SOURCES = 
LDADD = ../src/libunittest.a

CLEANFILES = *~ *.bak core core.[0-9]*
