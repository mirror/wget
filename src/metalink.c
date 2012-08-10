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
   32. In the line below, 64 is written instead of a more complex expression
   to have a more readable code. */
#define MAX_DIGEST_LENGTH 64

enum {MD5, SHA1, SHA256, ALL};
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

void
init_hash_ctx (void *ctx, int type)
{
  switch (type)
    {
      case MD5:
        md5_init_ctx ((struct md5_ctx *)ctx);
        break;
      case SHA1:
        sha1_init_ctx ((struct sha1_ctx *)ctx);
        break;
      case SHA256:
        sha256_init_ctx ((struct sha256_ctx *)ctx);
        break;
    }
}

void
finish_hash_ctx (void *ctx, int type, void *hash)
{
  switch (type)
    {
      case MD5:
        md5_finish_ctx ((struct md5_ctx *)ctx, hash);
        break;
      case SHA1:
        sha1_finish_ctx ((struct sha1_ctx *)ctx, hash);
        break;
      case SHA256:
        sha256_finish_ctx ((struct sha256_ctx *)ctx, hash);
        break;
    }
}

void
process_block(void *ctx, int type, char *buffer)
{
  switch (type)
    {
      case MD5:
        md5_process_block (buffer, BLOCKSIZE, (struct md5_ctx *)ctx);
        break;
      case SHA1:
        sha1_process_block (buffer, BLOCKSIZE, (struct sha1_ctx *)ctx);
        break;
      case SHA256:
        sha256_process_block (buffer, BLOCKSIZE, (struct sha256_ctx *)ctx);
        break;
    }
}

void
process_bytes(void *ctx, int type, char *buffer, size_t sum)
{
  switch (type)
    {
      case MD5:
        md5_process_bytes (buffer, sum, (struct md5_ctx *)ctx);
        break;
      case SHA1:
        sha1_process_bytes (buffer, sum, (struct sha1_ctx *)ctx);
        break;
      case SHA256:
        sha256_process_bytes (buffer, sum, (struct sha256_ctx *)ctx);
        break;
    }
}

/* Function finds hash of a file. Type of the hash can be one of the supported
   types listed in the enum above. Returns;
   1    if there is an allocation or read error.
   0    if hash successfuilly found. */
int
find_file_hash(FILE *file, int type, void *hash)
{
  size_t sum;
  void *ctx = NULL;
  char *buffer;

  switch(type)
    {
      case MD5:
        ctx = malloc(sizeof(struct md5_ctx));
        break;
      case SHA1:
        ctx = malloc(sizeof(struct sha1_ctx));
        break;
      case SHA256:
        ctx = malloc(sizeof(struct sha256_ctx));
        break;
    }
  if(!ctx)
      return 1;

  /* Initialize the computation context.  */
  init_hash_ctx (ctx, type);

  buffer = malloc (BLOCKSIZE + 72);
  if (!buffer)
    {
      finish_hash_ctx(ctx, type, hash);
      free(ctx);
      return 1;
    }

  /* Iterate over full file contents.  */
  while (1)
    {
      /* We read the file in blocks of BLOCKSIZE bytes.  One call of the
         computation function processes the whole buffer so that with the
         next round of the loop another block can be read.  */
      size_t n;
      sum = 0;

      /* Read block.  Take care for partial reads.  */
      while (1)
        {
          n = fread (buffer, 1, BLOCKSIZE - sum, file);

          sum += n;

          if (sum == BLOCKSIZE)
            break;

          if (n == 0)
            {
              /* Check for the error flag IFF N == 0, so that we don't
                 exit the loop after a partial read due to e.g., EAGAIN
                 or EWOULDBLOCK.  */
              if (ferror (file))
                {
                  free (buffer);
                  free (ctx);
                  return 1;
                }
              goto process_partial_block;
            }

          /* We've read at least one byte, so ignore errors.  But always
             check for EOF, since feof may be true even though N > 0.
             Otherwise, we could end up calling fread after EOF.  */
          if (feof (file))
            goto process_partial_block;
        }

      /* Process buffer with BLOCKSIZE bytes.  Note that
         BLOCKSIZE % 64 == 0
       */
      process_block (ctx, type, buffer);
    }

process_partial_block:

  /* Process any remaining bytes.  */
  if (sum > 0)
      process_bytes (ctx, type, buffer, sum);

  /* Construct result in desired memory.  */
  finish_hash_ctx (ctx, type, hash);
  free (buffer);
  free (ctx);
  return 0;
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
  unsigned char hashes[HASH_TYPES][MAX_DIGEST_LENGTH];
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
      if (find_file_hash(file, req_type, hash_raw))
        {
          logprintf (LOG_VERBOSE, "File hash could not be found.\n");
          fclose(file);
          return 1;
        }

      /* Turn byte-form hash to hex form. */
      for(j = 0 ; j < digest_sizes[i]; ++j)
        sprintf(hashes[i] + 2 * j, "%x", hash_raw[j]);
      fclose(file);

      /* Traverse checksums and make essential hash comparisons. */
      for (i = 0; checksums[i] != NULL; ++i)
        {
          if (!strcmp(checksums[i]->type, supported_hashes[req_type]))
            {
              lower_hex_case(checksums[i]->hash, digest_sizes[req_type]);
              if (memcmp(checksums[i]->hash, hashes[req_type], digest_sizes[req_type]))
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
          if (find_file_hash(file, req_type, hash_raw))
            {
              logprintf (LOG_VERBOSE, "File hash could not be found.\n");
              fclose(file);
              return 1;
            }
          for(j = 0 ; j < digest_sizes[i]; ++j)
            sprintf(hashes[i] + 2 * j, "%x", hash_raw[j]);
        }
      fclose(file);

      /* Traverse checksums and make essential hash comparisons. */
      for (i = 0; checksums[i] != NULL; ++i)
        {
          for (j = 0; j < HASH_TYPES; ++j)
            if (!strcmp(checksums[i]->type, supported_hashes[j]))
              {
                lower_hex_case(checksums[i]->hash, digest_sizes[j]);
                if (memcmp(checksums[i]->hash, hashes[j], digest_sizes[j]))
                  {
                    logprintf (LOG_VERBOSE, "Verifying(%s) failed: hashes are different.\n",
                               filename);
                    --res;
                  }
              }
        }
    }

  return res;
}
