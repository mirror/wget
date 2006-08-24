/* Keep track of visited URLs in spider mode.
   Copyright (C) 2006 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#include <config.h>

#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "wget.h"
#include "spider.h"
#include "url.h"
#include "utils.h"
#include "hash.h"
#include "res.h"


static struct hash_table *visited_urls_hash;
static struct hash_table *nonexisting_urls_set;

/* Cleanup the data structures associated with this file.  */

void
spider_cleanup (void)
{
  if (visited_urls_hash)
    {
      free_keys_and_values (visited_urls_hash);
      hash_table_destroy (visited_urls_hash);
      visited_urls_hash = NULL;
    }
  if (nonexisting_urls_set)
    string_set_free (nonexisting_urls_set);
}

/* Remembers visited files.  */

struct url_list 
{
  char *url;
  struct url_list *next;
};

static bool
in_url_list_p (const struct url_list *list, const char *url, bool verbose)
{
  const struct url_list *ptr;
  
  for (ptr = list; ptr; ptr = ptr->next)
    {
      /* str[case]cmp is inadequate for URL comparison */
      if (are_urls_equal (url, ptr->url)) 
        return true;
    }
 
  return false;
}

void
visited_url (const char *url, const char *referrer)
{
  struct url_list *list;

  /* Ignore robots.txt URLs */
  if (is_robots_txt_url (url))
    return;
  
  if (!visited_urls_hash)
    visited_urls_hash = make_string_hash_table (0);

  list = hash_table_get (visited_urls_hash, url);
  if (!list)
    {
      list = (struct url_list *) xnew0 (struct url_list);
      list->url = referrer ? xstrdup (referrer) : NULL;
      hash_table_put (visited_urls_hash, xstrdup (url), list);
    }
  else if (referrer && !in_url_list_p (list, referrer, false)) 
    {
      /* Append referrer at the end of the list */
      struct url_list *newnode;
      
      while (list->next) 
        list = list->next;
      
      newnode = (struct url_list *) xnew0 (struct url_list);
      newnode->url = xstrdup (referrer);
      list->next = newnode;
    }
}

/* Remembers broken links.  */
void
nonexisting_url (const char *url)
{
  /* Ignore robots.txt URLs */
  if (is_robots_txt_url (url))
    return;
  if (!nonexisting_urls_set)
    nonexisting_urls_set = make_string_hash_table (0);
  string_set_add (nonexisting_urls_set, url);
}

void
print_broken_links (void)
{
  hash_table_iterator iter;
  int num_elems;
  
  if (!nonexisting_urls_set) 
    {
      logprintf (LOG_NOTQUIET, _("Found no broken links.\n\n"));
      return;
    }
  
  num_elems = hash_table_count (nonexisting_urls_set);
  assert (num_elems > 0);
  
  if (num_elems > 1) 
    {
      logprintf (LOG_NOTQUIET, _("Found %d broken links.\n\n"), 
                 num_elems);
    }
  else
    {
      logprintf (LOG_NOTQUIET, _("Found 1 broken link.\n\n"));
    }
  
  for (hash_table_iterate (nonexisting_urls_set, &iter);
       hash_table_iter_next (&iter); )
    {
      struct url_list *list;
      const char *url = (const char *) iter.key;
          
      logprintf (LOG_NOTQUIET, _("%s referred by:\n"), url);
      
      for (list = (struct url_list *) hash_table_get (visited_urls_hash, url); 
           list; list = list->next) 
        {
          logprintf (LOG_NOTQUIET, _("    %s\n"), list->url);
        }
    }
  logputs (LOG_NOTQUIET, "\n");
}

/*
 * vim: et ts=2 sw=2
 */

