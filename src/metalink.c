/* Declarations for HTTP.
   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012 Free Software
   Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget.  If not, see <http://www.gnu.org/licenses/>.

Additional permission under GNU GPL version 3 section 7

If you modify this program, or any covered work, by linking or
combining it with the OpenSSL project's OpenSSL library (or a
modified version of that library), containing parts covered by the
terms of the OpenSSL or SSLeay licenses, the Free Software Foundation
grants you additional permission to convey the resulting work.
Corresponding Source for a non-source form of such a combination
shall include the source code for the parts of OpenSSL used as well
as that of the covered work.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <metalink/metalink_parser.h>
#include <metalink/metalink_types.h>

#include "wget.h"

#include "log.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "metalink.h"

#define HASH_TYPES 3
/* Between MD5, SHA1 and SHA256, SHA256 has the greatest hash length, which is
   32. In the line below, 64 is written to have a more readable code. */
#define MAX_DIGEST_LENGTH 32

static char supported_hashes[HASH_TYPES][7] = {"sha256", "sha1", "md5"};
static int digest_sizes[HASH_TYPES] = {SHA256_DIGEST_SIZE, SHA1_DIGEST_SIZE, MD5_DIGEST_SIZE};
static int (*hash_function[HASH_TYPES]) (FILE *, void *) = {sha256_stream, sha1_stream, md5_stream};

/* Parses metalink into type metalink_t and returns a pointer to it.
   Returns NULL if the parsing is failed. */
metalink_t*
metalink_context (const char *url)
{
  metalink_error_t err;
  metalink_t* metalink;

  err = metalink_parse_file (url, &metalink);

  if(err != 0)
      metalink = NULL;
  return metalink;
}

/* It should be taken into account that file hashes in metalink files may
   include uppercase letter. This function turns the case of the first length
   letters in the space pointed by hash into lowercase. */
static void
lower_hex_case (unsigned char *hash, int length)
{
  int i;

  /* 32 is the difference between the ascii codes of 'a' and 'A'. */
  for(i = 0; i < length; ++i)
    if('A' <= hash[i] && hash[i] <= 'Z')
      hash[i] += 32;
}

/* Verifies file hash by comparing the file hashes found by gnulib functions
   and hashes provided by metalink file. Works by comparing strongest supported
   hash type available in the metalink file.
   
   Returns;
   -1      if hashes that were compared turned out to be different.
    0      if all pairs of hashes compared turned out to be the same.
    1      if due to some error, comparisons could not be made.  */
int
verify_file_hash (const char *filename, metalink_checksum_t **checksums)
{
  int i, j, req_type, res = 0;
  
  unsigned char hash_raw[MAX_DIGEST_LENGTH];
  /* Points to a hash of supported type from the metalink file. The index dedicated
     to a type is inversely proportional to its strength. (check supported_types
     to see the supported hash types listed in decreasing order of strength)*/
  unsigned char *metalink_hashes[HASH_TYPES];
  unsigned char file_hash[2 * MAX_DIGEST_LENGTH + 1];
  FILE *file;

  if (!checksums)
    {
      /* Metalink file has no hashes for this file. */
      logprintf (LOG_VERBOSE, "Validating(%s) failed: digest missing in metalink file.\n",
                 filename);
      return 1;
    }

  for (i = 0; i < HASH_TYPES; ++i)
    metalink_hashes[i] = NULL;

  /* Fill metalink_hashes to contain an instance of supported types of hashes. */
  for (i = 0; checksums[i] != NULL; ++i)
    for (j = 0; j < HASH_TYPES; ++j)
      if (!strcmp(checksums[i]->type, supported_hashes[j]))
        {
          if(metalink_hashes[j])
            {
              /* As of libmetalin-0.03, it is not checked during parsing the
                 information in the metalink file whether there are multiple
                 hashes of same type for one file. That case should be checked,
                 as none of those hashes can be trusted above the other. */
              logprintf (LOG_VERBOSE, "Validating(%s) failed: metalink file contains different hashes of same type.\n",
                         filename);
              return 1;
            }
          else
            metalink_hashes[j] = checksums[i]->hash;
        }

  for (i = 0; !metalink_hashes[i]; ++i);

  if (i == HASH_TYPES)
    {
      /* no hash of supported types could be found. */
      logprintf (LOG_VERBOSE, "Validating(%s) failed: No hash of supported types could be found in metalink file.\n",
                 filename);
      return 1;
    }
  req_type = i;

  if (!(file = fopen(filename, "r")))
    {
      /* File could not be opened. */
      logprintf (LOG_VERBOSE, "Validating(%s) failed: file could not be opened.\n",
                 filename);
      return 1;
    }

  res = (*hash_function[req_type]) (file, hash_raw);
  fclose(file);

  /* Find file hash accordingly. */
  if (res)
    {
      logprintf (LOG_VERBOSE, "Validating(%s) failed: File hash could not be found.\n",
                 filename);
      return 1;
    }

  /* Turn byte-form hash to hex form. */
  for(j = 0 ; j < digest_sizes[req_type]; ++j)
    sprintf(file_hash + 2 * j, "%02x", hash_raw[j]);

  lower_hex_case(metalink_hashes[req_type], 2 * digest_sizes[req_type]);
  if (strcmp(checksums[req_type]->hash, file_hash))
    {
      logprintf (LOG_VERBOSE, "Verifying(%s) failed: %s hashes are different.\n",
                 filename, supported_hashes[i]);
      return -1;
    }

  logprintf (LOG_VERBOSE, "Verifying(%s): %s hashes are the same.\n",
             filename, supported_hashes[i]);
  return 0;
}
