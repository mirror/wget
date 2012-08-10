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

#define BLOCKSIZE 32768
#if BLOCKSIZE % 64 != 0
# error "invalid BLOCKSIZE"
#endif

#define HASH_TYPES ALL
/* Between MD5, SHA1 and SHA256, SHA256 has the greatest hash length, which is
   32. In the line below, 64 is written to have a more readable code. */
#define MAX_DIGEST_LENGTH 32

static char supported_hashes[HASH_TYPES][7] = {"md5", "sha1", "sha256"};
static int digest_sizes[HASH_TYPES] = {MD5_DIGEST_SIZE, SHA1_DIGEST_SIZE, SHA256_DIGEST_SIZE};
static int (*hash_function[HASH_TYPES]) (FILE *, void *) = {md5_stream, sha1_stream, sha256_stream};

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
void
lower_hex_case (unsigned char *hash, int length)
{
  int i;

  /* 32 is the difference between the ascii codes of 'a' and 'A'. */
  for(i = 0; i < length; ++i)
    if('A' <= hash[i] && hash[i] <= 'Z')
      hash[i] += 32;
}

/* Verifies file hash by comparing the file hash(es) found by gnulib functions
   and hash(es) provided by metalink file. Returns;
   n<0    if n pairs of hashes that were compared turned out to be different.
   0      if all pairs of hashes compared turned out to be the same.
   1      if due to some error, comparisons could not be made/completed. */
int
verify_file_hash (const char *filename, metalink_checksum_t **checksums)
{
  int i, j, req_type, res = 0;
  unsigned char hash_raw[MAX_DIGEST_LENGTH];
  unsigned char hashes[HASH_TYPES][2 * MAX_DIGEST_LENGTH + 1];
  FILE *file;

  if (!checksums)
    {
      /* Metalink file has no hashes for this file. */
      logprintf (LOG_VERBOSE, "Validating(%s) failed: digest missing in metalink file.\n",
                 filename);
      return 1;
    }

  if (!(file = fopen(filename, "r")))
    {
      /* File could not be opened. */
      logprintf (LOG_VERBOSE, "Validating(%s) failed: file could not be opened.\n",
                 filename);
      return 1;
    }

  if (strcmp(opt.hashtype, "all"))
    {
      /* Estimate the type of hash we are requested to verify. */
      for (i = 0; i < HASH_TYPES; ++i)
          if(!strcmp(opt.hashtype, supported_hashes[i]))
            {
              req_type = i;
              break;
            }

      if (i == HASH_TYPES)
        {
          /* opt.hashtype contains an unsupported hash type. */
          logprintf (LOG_VERBOSE, "argument to --verify is either not supported or invalid.\n");
          fclose(file);
          exit(1);
        }
        
      /* Find file hash accordingly. */
      if ((*hash_function[req_type]) (file, hash_raw))
        {
          logprintf (LOG_VERBOSE, "File hash could not be found.\n");
          fclose(file);
          return 1;
        }

      /* Turn byte-form hash to hex form. */
      for(j = 0 ; j < digest_sizes[req_type]; ++j)
        sprintf(hashes[req_type] + 2 * j, "%02x", hash_raw[j]);
      fclose(file);

      /* Traverse checksums and make essential hash comparisons. */
      for (i = 0; checksums[i] != NULL; ++i)
        {
          if (!strcmp(checksums[i]->type, supported_hashes[req_type]))
            {
              lower_hex_case(checksums[i]->hash, 2 * digest_sizes[req_type]);
              if (strcmp(checksums[i]->hash, hashes[req_type]))
                {
                  logprintf (LOG_VERBOSE, "Verifying(%s) failed: hashes are different.\n",
                             filename);
                  --res;
                }
            }
        }
    }
  else
    {
      /* Find file hashes accordingly. */
      for (i = 0; i < HASH_TYPES; ++i)
        {
          if ((*hash_function[i]) (file, hash_raw))
            {
              logprintf (LOG_VERBOSE, "File hash could not be found.\n");
              fclose(file);
              return 1;
            }
          for(j = 0 ; j < digest_sizes[i]; ++j)
            sprintf(hashes[i] + 2 * j, "%02x", hash_raw[j]);
        }
      fclose(file);

      /* Traverse checksums and make essential hash comparisons. */
      for (i = 0; checksums[i] != NULL; ++i)
        {
          for (j = 0; j < HASH_TYPES; ++j)
            if (!strcmp(checksums[i]->type, supported_hashes[j]))
              {
                lower_hex_case(checksums[i]->hash, 2 * digest_sizes[j]);
                if (strcmp(checksums[i]->hash, hashes[j]))
                  {
                    logprintf (LOG_VERBOSE, "Verifying(%s) failed: hashes are different.\n",
                               filename);
                    --res;
                  }
                else
                  break;
              }
        }
    }

  return res;
}
