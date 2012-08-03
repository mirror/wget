#include <stdlib.h>
#include <string.h>
#include <metalink/metalink_parser.h>
#include <metalink/metalink_types.h>

#include "wget.h"

#include "log.h"
#include "md5.h"
#include "sha1.h"
#include "metalink.h"



#define HASH_TYPES 2
#define MAX_DIGEST_VALUE 1024

static char supported_hashes[HASH_TYPES][5] = {"md5", "sha1"};
int digest_values[HASH_TYPES] = {MD5_DIGEST_SIZE, SHA1_DIGEST_SIZE};
int (*hash_function[HASH_TYPES]) (FILE *, void *);

/* Parses metalink into type metalink_t and returns a pointer to it.
   Returns NULL if the parsing is failed. */
metalink_t*
metalink_context (const char *url)
{
  metalink_error_t err;
  metalink_t* metalink;

  err = metalink_parse_file (url, &metalink);

  if(err != 0)
      return NULL;
  return metalink;
}

/* Function checks the hashes of files based on the given values
   in metalink file.
   Its return values are;
   -1    no comparisons could be made. Possible reasons include;
             - Hash format entered to opt.hashtype is not supported.
             - Metalink file does not contain the desired/supported hash type(s)
    0    if at least 1 hash comparisons are made and all turned out to be equal.
    1    if at least 1 hash comparison turned out to be different */
int
verify_hash(FILE *file, char *type, metalink_checksum_t **checksums)
{
  int i, j, h, t=-2, res = 0, comparisons = 0;
  unsigned char hash[MAX_DIGEST_VALUE];

  hash_function[0] = md5_stream;
  hash_function[1] = sha1_stream;

  for(i = 0; i < HASH_TYPES; ++i)
    if(!strcmp(type, supported_hashes[i]))
      {
        t=i;
        break;
      }
  if (t < 0)
    {
      if(strcmp(type, "all"))
        {
          /* Entered hash type is not supported. Print out an error message and
             exit appropriately. */
        }
      else
        t = -1;
    }

  for (i = 0; checksums[i] != NULL; ++i)
    {
      /* Pick the hash function and digest value to use. */
      if(t<0)
        {
          /* If any supported hash is asked to be inspected, then find if
             type of checksums [i] is supported and in what index the relevant
             function is. */
          for(j = 0; j < HASH_TYPES; ++j)
            if(!strcmp(checksums[i]->type, supported_hashes[j]))
              {
                h = j;
                break;
              }
          /*checksums[i] has a hash type that is not supported. Skip it.*/
          if(h < 0)
            continue;
        }
      else if(strcmp(checksums[i]->type, type))
        continue;
      else
        h = t;

      (*hash_function[h]) (file, hash);
      ++comparisons;

      if (memcmp(hash, checksums[i]->hash, digest_values[h]))
        {
          res = 1;
          break;
        }
      else if(opt.verbose)
        logprintf (LOG_NOTQUIET, _("%s checksum verified.\n"), checksums[i]->type);
    }

  if(comparisons)
    return res;
  else
    return -1;
}
