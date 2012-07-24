#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#include "multi.h"
#include "url.h"
#include "wget.h"

int
spawn_thread (struct s_thread_ctx *thread_ctx, char * name, int index, int resource)
{
  static pthread_t *thread;
  char *command;

  sprintf(thread_ctx[index].file, TEMP_PREFIX "%s.%d", name, index);

  thread_ctx[index].url_parsed = url_parse (thread_ctx[index].url,
                       &(thread_ctx[index].url_err), thread_ctx[index].i, true);
  if(!thread_ctx[index].url_parsed)
    return 1;

  /* TODO: Update this when configuring fallbacking code so that downloading
     goes on from where the previous resource failed.
     TODO: size of the bytes allocated by malloc should be recalculated and
     the string assignment to that space should be readjusted to contain only
     the files created by wget.(ONLY the files[] elements) */
  if(file_exists_p(thread_ctx[index].file))
    {
      command = malloc(sizeof("rm -f ") + sizeof(TEMP_PREFIX) + strlen(name)
                     + (sizeof(".")-1) + (opt.jobs/10 + 1) + sizeof(""));

      sprintf(command, "rm -f " TEMP_PREFIX "%s.%d", name, index);
      system(command);
      free(command);
    }

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
