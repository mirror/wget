#!/bin/sh
# 
# Do some checking before 'git push'.

CORES=`grep -c ^processor /proc/cpuinfo 2>/dev/null || echo 0`
if [ $CORES -lt 1 ]; then CORES=1; fi

make -f Makefile distclean 2>/dev/null

# automatically exit on error
set -e

export CFLAGS="-std=c89 -pedantic -O2 -g -Wall -Wextra -Wstrict-prototypes -Wold-style-definition -Wwrite-strings -Wshadow -Wformat -Wformat-security -Wunreachable-code -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition"

CACHEFILE=$PWD/config_check.cache

# measure time consumed and and print it at the end of the script
START=$(date +%s.%N)

echo "./bootstrap"
./bootstrap >/dev/null
echo

for CC in gcc clang; do
  export CC
  echo "*** checking CC=$CC"

  # the compiler changed, so we have to remove the cache file here
  rm -f $CACHEFILE

  for options in "" "--with-ssl=openssl"; do
    export DISTCHECK_CONFIGURE_FLAGS="-C --cache-file=$CACHEFILE $options"
    echo "  ./configure $DISTCHECK_CONFIGURE_FLAGS"
    ./configure $DISTCHECK_CONFIGURE_FLAGS >/dev/null

    for xVALGRIND in 0 1; do
      for xLCALL in C tr_TR.utf8; do
        export TESTS_ENVIRONMENT="LC_ALL=$xLCALL VALGRIND_TESTS=$xVALGRIND"
        echo "    TESTS_ENVIRONMENT=\"$TESTS_ENVIRONMENT\"" make check -j$CORES
        make check -j$CORES >/dev/null
      done
    done

    unset TESTS_ENVIRONMENT
    export TESTS_ENVIRONMENT
    echo "  make distcheck -j$CORES"
    make distcheck -j$CORES
  done
done

END=$(date +%s.%N)
echo "Duration: "$(echo "$END - $START" | bc)
