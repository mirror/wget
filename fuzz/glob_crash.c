/*
 * Created 19.10.2017 by Tim Rühsen
 *
 * Call glob() using data from fuzzer crash file
 *
 * Build and execute with instrumented gnulib (amend -I paths as needed):
 *
 * clang build (spills out WRITE heap buffer overflow)
 * export CC=clang-6.0
 * export CFLAGS="-O1 -g -fno-omit-frame-pointer -fsanitize=address -fsanitize-address-use-after-scope"
 * $CC $CFLAGS -I.. -I../lib glob_crash.c -o glob_crash ../lib/.libs/libgnu.a
 * ./glob_crash
 *
 * gcc build (spills out READ heap buffer overflow):
 * export CC=gcc
 * export CFLAGS="-O1 -g -fno-omit-frame-pointer -fsanitize=address -fsanitize-address-use-after-scope"
 * $CC $CFLAGS -I.. -I../lib glob_crash.c -o glob_crash ../lib/.libs/libgnu.a
 * ./glob_crash
 */

#include <glob.h>

int main(int argc, char **argv)
{
static unsigned char data[] = "1e";

	glob_t pglob;
	if (glob(data, GLOB_TILDE|GLOB_ONLYDIR|GLOB_NOCHECK, NULL, &pglob) == 0)
		globfree(&pglob);

	return 0;
}
