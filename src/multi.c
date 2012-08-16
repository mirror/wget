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

void
init_ranges(int numthreads)
{
  ranges = malloc (numthreads * (sizeof *ranges));
}

int
fill_ranges_data(int numthreads, int num_of_resources, long long int file_size,
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
}

int
spawn_thread (struct s_thread_ctx *thread_ctx, int index, int resource)
{
  static pthread_t thread;

  thread_ctx[index].url_parsed = url_parse (thread_ctx[index].url,
                       &(thread_ctx[index].url_err), thread_ctx[index].i, true);
  if(!thread_ctx[index].url_parsed)
    return 1;

  thread_ctx[index].range = ranges + index;
  (thread_ctx[index].range)->is_assigned = 1;
  (thread_ctx[index].range)->resources[resource] = true;
  thread_ctx[index].used = 1;
  thread_ctx[index].terminated = 0;

  return pthread_create (&thread, NULL, segmented_retrieve_url, &thread_ctx[index]);
}

int
collect_thread (sem_t *retr_sem, struct s_thread_ctx *thread_ctx, int numthreads)
{
  int k, ret;
  do
    ret = sem_wait (retr_sem);
  while (ret < 0 && errno == EINTR);

  for (k = 0; k < numthreads; k++)
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

void
merge_temp_files(char **inputs, const char *output, int numfiles)
{
  FILE *out, *in;
  int j, ret;
  void *buf = malloc (MIN_CHUNK_SIZE);

  out = fopen (output, "w");
  for(j = 0; j < numfiles; ++j)
    {
      in = fopen(inputs[j],"r");
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
delete_temp_files(char **files, int numfiles)
{
  int j = 0;

  while(j < numfiles)
    unlink(files[j++]);
}
