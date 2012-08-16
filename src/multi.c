#include "wget.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "multi.h"
#include "url.h"

static struct range *ranges;
char *temp, **files;

void
init_temp_files()
{
  int i;

  if(!(files = malloc (opt.jobs * (sizeof *files))))
    {
      logprintf (LOG_VERBOSE, "Space for temporary file data could not be allocated.\n");
      exit(1);
    }
  for (i = 0; i < opt.jobs; ++i)
    if(!(files[i] = malloc (L_tmpnam * sizeof(char))))
      {
        logprintf (LOG_VERBOSE, "Space for temporary file names could not be allocated.\n");
        exit(1);
      }
}

void
name_temp_files()
{
  int i;

  for (i = 0; i < opt.jobs; ++i)
    if(!tmpnam(files[i]))
      {
        logprintf (LOG_VERBOSE, "Temporary file name could not be assigned.\n");
        exit(1);
      }
}

void
merge_temp_files(const char *output)
{
  FILE *out, *in;
  int j, ret;
  void *buf = malloc (MIN_CHUNK_SIZE);

  out = fopen (output, "w");
  for(j = 0; j < opt.jobs; ++j)
    {
      in = fopen(files[j],"r");
      ret = MIN_CHUNK_SIZE;
      while(ret == MIN_CHUNK_SIZE)
        {
          ret = fread(buf, 1, MIN_CHUNK_SIZE, in);
          fwrite(buf, 1, ret, out);
        }
      fclose(in);
    }
  fclose(out);
  free(buf);
}

void
delete_temp_files()
{
  int j = 0;

  while(j < opt.jobs)
    unlink(files[j++]);
}

void
clean_temp_files()
{
  int i;

  for (i = 0; i < opt.jobs; ++i)
    free (files[i]);
  free(files);
}

void
init_ranges()
{
  if(!(ranges = malloc (opt.jobs * (sizeof *ranges))))
    logprintf (LOG_VERBOSE, "Space for ranges data could not be allocated.\n");
}

int
fill_ranges_data(int num_of_resources, long long int file_size,
                 long int chunk_size)
{
  int i, r;
  i = 0;
  do
  {
      ranges[i].first_byte = i * chunk_size;
      ranges[i].last_byte = (i+1) * chunk_size - 1;
      ranges[i].bytes_covered = ranges[i].is_assigned = 0;
      ranges[i].resources = malloc(num_of_resources * sizeof(bool));
      ranges[i].status_least_severe = RETROK;
      for (r = 0; r < num_of_resources; ++r)
        ranges[i].resources[r] = false;
      ++i;
    } while (ranges[i-1].last_byte < (file_size - 1));
  ranges[i-1].last_byte = file_size -1;

  return i;
}

void
clean_range_res_data(int num_of_resources)
{
  int i;
  for (i = 0; i < num_of_resources; ++i)
    free (ranges[i].resources);
}

void
clean_ranges()
{
  free (ranges);
  ranges = NULL;
}

int
spawn_thread (struct s_thread_ctx *thread_ctx, int index, int resource)
{
  static pthread_t thread;

  thread_ctx[index].url_parsed = url_parse (thread_ctx[index].url,
                       &(thread_ctx[index].url_err), thread_ctx[index].i, true);
  if(!thread_ctx[index].url_parsed)
    return 1;

  thread_ctx[index].file = files[index];
  thread_ctx[index].range = ranges + index;
  (thread_ctx[index].range)->is_assigned = 1;
  (thread_ctx[index].range)->resources[resource] = true;
  thread_ctx[index].used = 1;
  thread_ctx[index].terminated = 0;

  return pthread_create (&thread, NULL, segmented_retrieve_url, &thread_ctx[index]);
}

int
collect_thread (sem_t *retr_sem, struct s_thread_ctx *thread_ctx)
{
  int k, ret;
  do
    ret = sem_wait (retr_sem);
  while (ret < 0 && errno == EINTR);

  for (k = 0; k < opt.jobs; k++)
    if (thread_ctx[k].used && thread_ctx[k].terminated)
      {
        url_free (thread_ctx[k].url_parsed);
        thread_ctx[k].used = 0;
        thread_ctx[k].terminated = 0;
        (thread_ctx[k].range)->is_assigned = 0;
        return k;
      }
}

static void *
segmented_retrieve_url (void *arg)
{
  struct s_thread_ctx *ctx = (struct s_thread_ctx *) arg;

  ctx->status = retrieve_url (ctx->url_parsed, ctx->url,
                              &ctx->file, &ctx->redirected,
                              ctx->referer, &ctx->dt,
                              false, ctx->i, true, ctx->range);
  ctx->terminated = 1;
  sem_post (ctx->retr_sem);
}
