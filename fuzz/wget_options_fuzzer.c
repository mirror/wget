/*
 * Copyright(c) 2017-2018 Free Software Foundation, Inc.
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
 */

#include <config.h>

#include <sys/types.h>
#include <dirent.h> // opendir, readdir
#include <stdint.h> // uint8_t
#include <stdio.h>  // fmemopen
#include <string.h>  // strncmp
#include <fcntl.h>  // open flags
#include <unistd.h>  // close

#ifdef  __cplusplus
  extern "C" {
#endif
  // declarations for wget internal functions
  int main_wget(int argc, const char **argv);
  void cleanup(void);
#ifdef __cplusplus
  }
#endif

#include "fuzzer.h"

static const uint8_t *g_data;
static size_t g_size;
static int dont_write;

#if defined HAVE_DLFCN_H && defined HAVE_FMEMOPEN
#include <dlfcn.h>
#include <setjmp.h>
static jmp_buf jmpbuf;

#ifdef RTLD_NEXT /* Not defined e.g. on CygWin */
DIR *opendir(const char *name)
{
	DIR *(*libc_opendir)(const char *) =
		(DIR *(*)(const char *)) dlsym (RTLD_NEXT, "opendir");

	if (dont_write)
		return NULL;

	return libc_opendir(name);
/*
#ifdef TEST_RUN
	printf("opendir %s\n", name);
	if (!strcmp(name, SRCDIR"/wget_options_fuzzer.in"))
		return libc_opendir(name);
	if (!strcmp(name, SRCDIR"/wget_options_fuzzer.new"))
		return libc_opendir(name);
	if (!strcmp(name, SRCDIR"/wget_options_fuzzer.repro"))
		return libc_opendir(name);
#else
	if (!strcmp(name, "wget_options_fuzzer.in"))
		return libc_opendir(name);
	if (!strcmp(name, "wget_options_fuzzer.new"))
		return libc_opendir(name);
	if (!strcmp(name, "wget_options_fuzzer.repro"))
		return libc_opendir(name);
#endif

	return libc_opendir(name);
*/
}

FILE *fopen(const char *pathname, const char *mode)
{
	FILE *(*libc_fopen)(const char *, const char *) =
		(FILE *(*)(const char *, const char *)) dlsym (RTLD_NEXT, "fopen");

	if (dont_write) {
		size_t len = strlen(pathname);

		if (len >= 7 && !strcmp(pathname + len - 7, ".wgetrc") && !strcmp(mode, "r"))
			return fmemopen((void *) g_data, g_size, mode);


//		if (*mode == 'w')
			return libc_fopen("/dev/null", mode);

//		printf("open %s, %s\n", pathname, mode);
	}

	return libc_fopen(pathname, mode);
}

void exit(int status)
{
	if (dont_write)
		longjmp(jmpbuf, 1);

	void (*libc_exit)(int) =
		(void(*)(int)) dlsym (RTLD_NEXT, "exit");

	libc_exit(status);
}
#endif
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
//	static const char *argv[] = { "wget", "-q", "--no-config", "--config", "d41d8cd98f00b204e9800998ecf8427e" };
	static const char *argv[] = { "wget", "-q" };

	if (size > 2048) // same as max_len = ... in .options file
		return 0;

	g_data = data;
	g_size = size;

	FILE *bak = stderr;
	stderr = fopen("/dev/null", "w");

	dont_write = 1;

// try not to open/write to the file system
#if defined HAVE_DLFCN_H && defined HAVE_FMEMOPEN
	if (setjmp(jmpbuf)) {
		cleanup();
		dont_write = 0;
		fclose(stderr);
		stderr = bak;
		return 0;
	}

//	enable_testing(); // function in wget to prevent unwanted action while testing
	main_wget(sizeof(argv)/sizeof(argv[0]), argv);
	cleanup();
#endif

	dont_write = 0;
	fclose(stderr);
	stderr = bak;

	return 0;
}
