#include "wget.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "multi.h"
#include "url.h"

int
spawn_thread (struct s_thread_ctx *thread_ctx, int index, int resource)
{
  static pthread_t thread;

  thread_ctx[index].url_parsed = url_parse (thread_ctx[index].url,
                       &(thread_ctx[index].url_err), thread_ctx[index].i, true);
  if(!thread_ctx[index].url_parsed)
    return 1;

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
