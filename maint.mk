# -*-Makefile-*-
# This Makefile fragment is intended to be useful by any GNU-like project.
# This file originate from coreutils, CPPI, Bison, and Autoconf.

# Copyright (C) 2001-2007 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

ME := maint.mk

# List of all C-like source code files that will be tested for
# stylistic "errors".  You may want to define this to something 
# more complex in Makefile.cfg.
C_SOURCES ?= $(shell find . -name '*.[chly]')

# Add some more files to check, typically set in Makefile.cfg.
C_SOURCES += $(C_SOURCES_ADD)

# Do not save the original name or timestamp in the .tar.gz file.
# Use --rsyncable if available.
gzip_rsyncable := \
  $(shell gzip --help 2>/dev/null|grep rsyncable >/dev/null && echo --rsyncable)
GZIP_ENV = '--no-name --best $(gzip_rsyncable)'

# Prevent programs like 'sort' from considering distinct strings to be equal.
# Doing it here saves us from having to set LC_ALL elsewhere in this file.
export LC_ALL = C

# Casting arguments to free is never necessary.
sc_cast_of_argument_to_free:
	@grep -nE '\<free *\( *\(' $(C_SOURCES) &&			\
	  { echo '$(ME): don'\''t cast free argument' 1>&2;		\
	    exit 1; } || :

sc_cast_of_x_alloc_return_value:
	@grep -nE '\*\) *x(m|c|re)alloc\>' $(C_SOURCES) &&		\
	  { echo '$(ME): don'\''t cast x*alloc return value' 1>&2;	\
	    exit 1; } || :

sc_cast_of_alloca_return_value:
	@grep -nE '\*\) *alloca\>' $(C_SOURCES) &&			\
	  { echo '$(ME): don'\''t cast alloca return value' 1>&2;	\
	    exit 1; } || :

sc_space_tab:
	@grep -n '[ ]	' $(C_SOURCES) &&				\
	  { echo '$(ME): found SPACE-TAB sequence; remove the SPACE'	\
		1>&2; exit 1; } || :

# Don't use the old ato* functions in `real' code.
# They provide no error checking mechanism.
# Instead, use strto* functions.
sc_prohibit_atoi_atof:
	@grep -nE '\<ato([filq]|ll)\>' $(C_SOURCES) &&			\
	  { echo '$(ME): do not use ato''f, ato''i, ato''l, ato''ll, or ato''q'	\
		1>&2; exit 1; } || :

# Using EXIT_SUCCESS as the first argument to error is misleading,
# since when that parameter is 0, error does not exit.  Use `0' instead.
sc_error_exit_success:
	@grep -nF 'error (EXIT_SUCCESS,' $(C_SOURCES) &&		\
	  { echo '$(ME): found error (EXIT_SUCCESS' 1>&2;		\
	    exit 1; } || :

# Stylistic, use #ifdef instead of #if
sc_no_if_have_config_h:
	@grep -n '^# *if HAVE_CONFIG_H' $(C_SOURCES) &&			\
	  { echo '$(ME): found use of #if HAVE_CONFIG_H; use #ifdef'	\
		1>&2; exit 1; } || :

# Prohibit the inclusion of assert.h without an actual use of assert.
sc_prohibit_assert_without_use:
	@files=$$(grep -l '# *include [<"]assert\.h[>"]' $(C_SOURCES)	\
			| grep '\.[cy]$$') &&				\
	grep -L '\<assert (' $$files					\
	    | grep . &&							\
	  { echo "$(ME): the above files include <assert.h> but don't use it" \
		1>&2; exit 1; } || :

sc_obsolete_symbols:
	@grep -nE '\<(HAVE''_FCNTL_H|O''_NDELAY)\>' $(C_SOURCES) &&	\
	  { echo '$(ME): do not use HAVE''_FCNTL_H or O''_NDELAY'	\
		1>&2; exit 1; } || :

# Each nonempty line must start with a year number, or a TAB.
sc_changelog:
	@grep -n '^[^12	]' $$(find . -name ChangeLog) &&	\
	  { echo '$(ME): found unexpected prefix in a ChangeLog' 1>&2;	\
	    exit 1; } || :

# Collect the names of rules starting with `sc_'.
syntax-check-rules := $(shell sed -n 's/^\(sc_[a-zA-Z0-9_-]*\):.*/\1/p' $(ME))
.PHONY: $(syntax-check-rules)

syntax-check: $(syntax-check-rules)

# Update gettext files.
PACKAGE ?= $(shell basename $(PWD))
POURL = http://translationproject.org/latest/$(PACKAGE)/
PODIR ?= po
refresh-po:
	rm -f $(PODIR)/*.po && \
	echo "$(ME): getting translations into po (please ignore the robots.txt ERROR 404)..." && \
	wget --no-verbose --directory-prefix $(PODIR) --no-directories --recursive --level 1 --accept .po --accept .po.1 $(POURL) && \
	echo 'en@boldquot' > $(PODIR)/LINGUAS && \
	echo 'en@quot' >> $(PODIR)/LINGUAS && \
	ls $(PODIR)/*.po | sed 's/.po//' | sed 's,$(PODIR)/,,' | sort >> $(PODIR)/LINGUAS

INDENT_SOURCES ?= $(C_SOURCES)
.PHONY: indent
indent:
	indent $(INDENT_SOURCES)
