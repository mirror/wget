#!/bin/sh -eu

# Copyright (c) 2017, 2019-2024 Free Software Foundation, Inc.
#
# This file is part of GNU Wget.
#
# GNU Wget is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GNU Wget is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with GNU Wget.  If not, see <https://www.gnu.org/licenses/>.

if ! grep '^CC=.afl-clang-fast' ../config.log >/dev/null; then
	echo "compile first library as:"
	echo "CC=afl-clang-fast ./configure"
	exit 1
fi

if test -z "$1"; then
	echo "Usage: $0 test-case"
	echo "Example: $0 wget_options_fuzzer"
	exit 1
fi

fuzzer=$1
#rm -f $fuzzer
#afl-clang-fast -O2 -g -I.. main.c "${fuzzer}.c" -o "${fuzzer}"

### minimize test corpora
if test -d ${fuzzer}.in; then
  mkdir -p ${fuzzer}.min
  for i in `ls ${fuzzer}.in`; do
    fin="${fuzzer}.in/$i"
    fmin="${fuzzer}.min/$i"
    if ! test -e $fmin || test $fin -nt $fmin; then
      afl-tmin -m 500 -i $fin -o $fmin -- ./${fuzzer}
    fi
  done
fi

TMPOUT=${fuzzer}.out
mkdir -p ${TMPOUT}

if test -f ${fuzzer}.dict; then
  afl-fuzz -m 500 -i ${fuzzer}.min -o ${TMPOUT} -x ${fuzzer}.dict -- ./${fuzzer}
else
  afl-fuzz -m 500 -i ${fuzzer}.min -o ${TMPOUT} -- ./${fuzzer}
fi

echo "output was stored in $TMPOUT"

exit 0
