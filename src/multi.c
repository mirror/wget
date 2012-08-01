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
spawn_thread (struct s_thread_ctx *thread_ctx, char * name, int index, int resource)
{
  static pthread_t thread;

  sprintf(thread_ctx[index].file, TEMP_PREFIX "%s.%d", name, index);

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

void
merge_temp_files(const char *file, int numfiles)
{
  FILE *out, *in;
  char *file_name = malloc(strlen("temp_") + strlen(file) + (sizeof ".")-1
                        + (numfiles/10 + 1) + sizeof "");
  int j, ret;
  void *buf = malloc(MIN_CHUNK_SIZE);
  /* FIXME: Check for errors in allocations. */

  sprintf(file_name, "%s", file);
  out = fopen(file_name,"w");
  for(j = 0; j < numfiles; ++j)
    {
      sprintf(file_name, TEMP_PREFIX "%s.%d", file, j);
      in = fopen(file_name,"r");
      ret = MIN_CHUNK_SIZE;
      while(ret == MIN_CHUNK_SIZE)
        {
          ret = fread(buf, 1, MIN_CHUNK_SIZE, in);
          fwrite(buf, 1, ret, out);
          /* FIXME: CHECK FOR ERRORS. */
        }
      fclose(in);
    }
  fclose(out);

  free(buf);
  free(file_name);
}

void
delete_temp_files(const char *file, int numfiles)
{
  char *file_name = malloc(strlen("temp_") + strlen(file) + (sizeof ".")-1
                        + (numfiles/10 + 1) + sizeof "");
  int j = 0;

  while(j < numfiles)
  {
    sprintf(file_name, TEMP_PREFIX "%s.%d", file, j++);
    unlink(file_name);
    /* FIXME: CHECK FOR ERRORS. */
  }
  free(file_name);
}
