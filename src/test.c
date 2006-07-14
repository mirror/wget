/* Unit testing.
   Copyright (C) 2005-2006 Free Software Foundation, Inc.

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
along with Wget; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#include <stdio.h>

#include "test.h"

#ifndef TESTING
#error "TESTING not set!!!"
#endif

const char *test_parse_content_disposition();
const char *test_subdir_p();
const char *test_dir_matches_p();
const char *test_cmd_spec_restrict_file_names();
const char *test_append_uri_pathel();
const char *test_are_urls_equal();
const char *test_is_robots_txt_url();

int tests_run;

static const char *
all_tests()
{
  mu_run_test (test_parse_content_disposition);
  mu_run_test (test_subdir_p);
  mu_run_test (test_dir_matches_p);
  mu_run_test (test_cmd_spec_restrict_file_names);
  mu_run_test (test_append_uri_pathel);
  mu_run_test (test_are_urls_equal);
  mu_run_test (test_is_robots_txt_url);
  
  return NULL;
}


int
main (void) 
{
  const char *result = all_tests();
  
  if (result != NULL) 
    {
      puts (result);
    }
  else 
    {
      printf ("ALL TESTS PASSED\n");
    }
  
  printf ("Tests run: %d\n", tests_run);
 
  return result != 0;
}

/*
 * vim: et ts=2 sw=2
 */

