/* Declarations for HTTP.
   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2014 Free Software
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

#include "wget.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <metalink/metalink_parser.h>
#include <metalink/metalink_types.h>

#include "log.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "metalink.h"
#include "utils.h"


#define HASH_TYPES 3
/* Between MD5, SHA1 and SHA256, SHA256 has the greatest hash length, which is
   32. In the line below, 64 is written to have a more readable code. */
#define MAX_DIGEST_LENGTH 32

static char supported_hashes[HASH_TYPES][7] = {"sha256", "sha1", "md5"};
static int digest_sizes[HASH_TYPES] = {SHA256_DIGEST_SIZE, SHA1_DIGEST_SIZE, MD5_DIGEST_SIZE};
static int (*hash_function[HASH_TYPES]) (FILE *, void *) = {sha256_stream, sha1_stream, md5_stream};

/* First, parse the metalink using libmetalink functions and structures. Then
   pass the information to an internal set of structures. */
mlink *
parse_metalink(char *input_file)
{
  int err;
  metalink_t *metalink;
  metalink_file_t **files;
  metalink_resource_t **resources;
  metalink_checksum_t **checksums;
  metalink_chunk_checksum_t *chunk_checksum;
  metalink_piece_hash_t **piece_hashes;
  mlink *m_link;
  err = metalink_parse_file (input_file, &metalink);
  if(err != 0 || !metalink)
    {
      logprintf (LOG_VERBOSE, "Libmetalink could not parse the metalink file.\n");
      return NULL;
    }
  else if(metalink->files == NULL) {
    logprintf (LOG_VERBOSE, "PARSE METALINK: Metalink doesn't have any file data.\n");
    metalink_delete(metalink);
    return NULL;
  }

  m_link = malloc (sizeof *m_link);
  m_link->identity = (metalink->identity ? xstrdup (metalink->identity) : NULL);
  m_link->tags = (metalink->tags ? xstrdup (metalink->tags) : NULL);
  m_link->files = NULL;
  m_link->num_of_files = 0;

  for (files = metalink->files; *files; ++files)
    {
      mlink_file *file;

      if (!(*files)->name)
        {
          /* File name is missing */
          logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping file"
                     " due to missing name/path.\n");
          continue;
        }
      else if (!(*files)->resources)
        {
          /* URL is missing */
          logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping file(%s)"
                     " due to missing resources.\n", (*files)->name);
          continue;
        }

      file = malloc(sizeof(mlink_file));
      ++(m_link->num_of_files);
      file -> next = (m_link->files);
      (m_link->files) = file;

      file->name = xstrdup ((*files)->name);
      file->size = (*files)->size;
      file->maxconnections = (*files)->maxconnections;
      file->version = ((*files)->version ? xstrdup ((*files)->version) : NULL);
      file->language = ((*files)->language ? xstrdup ((*files)->language) : NULL);
      file->os = ((*files)->os ? xstrdup ((*files)->os) : NULL);
      file->resources = NULL;
      file->checksums = NULL;
      file->chunk_checksum = NULL;
      file->num_of_res = file->num_of_checksums = 0;

      for (resources = (*files)->resources; *resources; ++resources)
        {
          mlink_resource *resource;

          if (!(*resources)->url)
            {
              logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping resource"
                         " due to missing URL.\n");
              continue;
            }

          resource = malloc (sizeof(mlink_resource));
          ++(file->num_of_res);

          resource->url = xstrdup ((*resources)->url);
          resource->type = ((*resources)->type ? xstrdup ((*resources)->type) : NULL);
          resource->location = ((*resources)->location ? xstrdup ((*resources)->location) : NULL);
          resource->preference = (*resources)->preference;
          resource->maxconnections = (*resources)->maxconnections;

          resource->next = (file->resources);
          (file->resources) = resource;
        }

      for (checksums = (*files)->checksums; *checksums; ++checksums)
        {
          mlink_checksum *checksum = malloc (sizeof(mlink_checksum));

          if (!(*checksums)->type)
            {
              logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping checksum"
                         " due to missing hash type.\n");
              continue;
            }
          else if (!(*checksums)->hash)
            {
              logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping resource"
                         " due to missing hash value.\n");
              continue;
            }

          checksum->type = ((*checksums)->type ? xstrdup ((*checksums)->type) : NULL);
          checksum->hash = ((*checksums)->hash ? xstrdup ((*checksums)->hash) : NULL);

          checksum->next = (file->checksums);
          (file->checksums) = checksum;
        }

      if((chunk_checksum = (*files)->chunk_checksum))
        {
          mlink_chunk_checksum *chunk_sum;

          if(!chunk_checksum->type)
            logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping chunk checksum"
                       " due to missing type information.\n");
          else
            {
              chunk_sum = malloc (sizeof(mlink_chunk_checksum));
              chunk_sum->length = chunk_checksum->length;
              chunk_sum->type = (chunk_checksum->type ? xstrdup (chunk_checksum->type) : NULL);
              for (piece_hashes = chunk_checksum->piece_hashes; *piece_hashes; ++piece_hashes)
                {
                  mlink_piece_hash piece_hash;
                  if(!chunk_checksum->type)
                    {
                      logprintf (LOG_VERBOSE, "PARSE METALINK: Skipping chunk checksum"
                                 " due to missing hash value for piece(%d).\n",
                                 (*piece_hashes)->piece);
                      free (chunk_sum);
                      break;
                    }
                }
            }
        }
    }

  metalink_delete(metalink);
  return m_link;
}

/* Elect resouces so that only the URLs with type HTTP and FTP (i.e. the
   protocols supported by Metalink&GNU Wget) remain on the list of resources. */
void
elect_resources (mlink *mlink)
{
  mlink_file *file;
  mlink_resource *res, *res_next;

  for (file = mlink->files; file; file = file->next)
    {
      res = file->resources;
      if (!res)
        continue;

      while (res_next = res->next)
        {
          if (strcmp(res_next->type, "ftp") && strcmp(res_next->type, "http"))
            {
              res->next = res_next->next;
              free(res_next);
            }
          else
            res = res_next;
        }
      res = file->resources;
      if (strcmp(res->type, "ftp") && strcmp(res->type, "http"))
        {
          file->resources = res->next;
          free(res);
        }
    }
}

/* Elect checksums so that only the hashes with types MD5, SHA-1 or SHA-256
   (i.e. the hashes supported by Metalink) remain on the list of checksums. */
void
elect_checksums (mlink *mlink)
{
  int i;
  mlink_file *file = mlink -> files;
  mlink_checksum *csum, *csum_next;

  for (; file; file = file->next)
    {
      csum = file->checksums;
      if (!csum)
        continue;

      while (csum_next = csum->next)
        {
          /* Traverse supported hash types & break if csum->type is the same. */
          for (i = 0; i < HASH_TYPES; ++i)
            if (!strcmp(csum_next->type, supported_hashes[i]))
              break;

          if(i == HASH_TYPES)
            {
              csum->next = csum_next->next;
              free(csum_next);
            }
          else
            csum=csum_next;
        }
      csum = file->checksums;
      for (i = 0; i < HASH_TYPES; ++i)
        if (!strcmp(csum->type, supported_hashes[i]))
          break;
      if(i == HASH_TYPES)
        {
          file->checksums = csum->next;
          free(csum);
        }
    }
}

/* Free the space allocated for the whole mlink structure. */
void
delete_mlink(mlink *metalink)
{
  mlink_file *file, *file_temp;
  mlink_resource *res, *res_temp;
  mlink_checksum *csum, *csum_temp;
  mlink_piece_hash *phash, *phash_temp;

  if(!metalink)
    return;

  xfree_null (metalink->tags);
  xfree_null (metalink->identity);

  file = metalink->files;
  while (file)
    {
      xfree_null(file->os);
      xfree_null(file->language);
      xfree_null(file->version);
      xfree_null(file->name);

      res = file->resources;
      while (res)
        {
          xfree_null (res->url);
          xfree_null (res->type);
          xfree_null (res->location);

          res_temp = res;
          res = res->next;
          free (res_temp);
        }

      csum = file->checksums;
      while (csum)
        {
          xfree_null (csum->type);
          xfree_null (csum->hash);

          csum_temp = csum;
          csum = csum->next;
          free (csum_temp);
        }

      if(file->chunk_checksum)
        {
          free (file->chunk_checksum->type);
          phash = file->chunk_checksum->piece_hashes;
          while (phash)
            {
              xfree_null (phash->hash);

              phash_temp = phash;
              phash = phash->next;
              free (phash_temp);
            }
        }

      file_temp = file;
      file = file->next;
      free (file_temp);
    }
  free (metalink);
}

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
verify_file_hash (const char *filename, mlink_checksum *checksums)
{
  int i, j, req_type, res = 0;

  unsigned char hash_raw[MAX_DIGEST_LENGTH];
  /* Points to a hash of supported type from the metalink file. The index dedicated
     to a type is inversely proportional to its strength. (check supported_types
     to see the supported hash types listed in decreasing order of strength)*/
  unsigned char *metalink_hashes[HASH_TYPES];
  unsigned char file_hash[2 * MAX_DIGEST_LENGTH + 1];
  FILE *file;
  mlink_checksum *checksum;

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
  for (checksum = checksums; checksum; checksum = checksum->next)
    for (j = 0; j < HASH_TYPES; ++j)
      if (!strcmp(checksum->type, supported_hashes[j]))
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
            metalink_hashes[j] = checksum->hash;
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

  if (!(file = fopen(filename, "rb")))
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
  if (strcmp(metalink_hashes[req_type], file_hash))
    {
      logprintf (LOG_VERBOSE, "Verifying(%s) failed: %s hashes are different.\n",
                 filename, supported_hashes[i]);
      return -1;
    }

  logprintf (LOG_VERBOSE, "Verifying(%s): %s hashes are the same.\n",
             filename, supported_hashes[i]);
  return 0;
}
