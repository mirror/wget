# Makefile for `wget' utility for MSVC 4.0
# Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#
# Version: 1.4.4
#

SHELL = command

VPATH       = .
o           = .obj
OUTDIR      = .

CC       = cl
LD       = link

CFLAGS   = /nologo /MT /W0 /O2
#DEBUGCF  = /DDEBUG /Zi /Od #/Fd /FR
CPPFLAGS = 
DEFS     = /DWINDOWS /D_CONSOLE /DHAVE_CONFIG_H /DSYSTEM_WGETRC=\"wgetrc\"
LDFLAGS  = /subsystem:console /incremental:no /warn:3
#DEBUGLF  = /pdb:wget.pdb /debug /debugtype:cv /map:wget.map /opt:noref
LIBS     = kernel32.lib advapi32.lib wsock32.lib user32.lib

INCLUDES = /I.

COMPILE = $(CC) $(INCLUDES) $(CPPFLAGS) $(DEBUGCF) $(DEFS) $(CFLAGS)
LINK    = $(LD) $(LDFLAGS) $(DEBUGLF) /out:$@

#INSTALL = @INSTALL@
#INSTALL_PROGRAM = @INSTALL_PROGRAM@

RM      = del

SRC = alloca.c cmpt.c connect.c host.c http.c netrc.c ftp-basic.c ftp.c ftp-ls.c \
      ftp-opie.c getopt.c headers.c html.c retr.c recur.c url.c init.c utils.c main.c \
      version.c mswindows.c fnmatch.c md5.c rbuf.c log.c

OBJ = alloca$o cmpt$o connect$o host$o http$o netrc$o ftp-basic$o ftp$o ftp-ls$o \
      ftp-opie$o headers$o html$o retr$o recur$o url$o init$o utils$o main$o \
      getopt$o version$o mswindows$o fnmatch$o md5$o rbuf$o log$o

.SUFFIXES: .c .obj

.c.obj:
        $(COMPILE) /c $<

# Dependencies for building

wget: wget.exe

wget.exe: $(OBJ)
         $(LD) @<< $(LDFLAGS) $(DEBUGLF) /out:$@ $(LIBS) $(OBJ)
<<
        ren wget.exe WGET.EXE


#
# Dependencies for cleanup
#

clean:
        $(RM) *.obj
        $(RM) *.exe
        $(RM) *.bak
        $(RM) *.pdb
        $(RM) *.map

distclean: clean
	$(RM) Makefile

realclean: distclean
	$(RM) TAGS

# Dependencies:

!include "..\windows\wget.dep"
