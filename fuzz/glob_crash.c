/*
 * Copyright (c) 2017-2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Wget.
 *
 * GNU Wget is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNU Wget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wget.  If not, see <https://www.gnu.org/licenses/>.


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
