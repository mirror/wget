#include <stdlib.h>
#include <string.h>
#include <metalink/metalink_parser.h>

metalink_t*
metalink_context (const char *url)
{
  metalink_error_t err;
  metalink_t* metalink;

  err = metalink_parse_memory (url, strlen(url), &metalink);

  if(err != 0)
    {
      return NULL;
    }
  return metalink;
}
