/* Read and parse the .netrc file to get hosts, accounts, and passwords.
   Copyright (C) 1996, Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* This file used to be kept in synch with the code in Fetchmail, but
   the latter has diverged since.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <sys/types.h>
#include <errno.h>

#include "wget.h"
#include "utils.h"
#include "netrc.h"
#include "init.h"

#ifndef errno
extern int errno;
#endif

#define NETRC_FILE_NAME ".netrc"

acc_t *netrc_list;

static acc_t *parse_netrc PARAMS ((const char *));

/* Return the correct user and password, given the host, user (as
   given in the URL), and password (as given in the URL).  May return
   NULL.

   If SLACK_DEFAULT is set, allow looking for a "default" account.
   You will typically turn it off for HTTP.  */
void
search_netrc (const char *host, const char **acc, const char **passwd,
	      int slack_default)
{
  acc_t *l;
  static int processed_netrc;

  if (!opt.netrc)
    return;
  /* Find ~/.netrc.  */
  if (!processed_netrc)
    {
      char *home = home_dir();

      netrc_list = NULL;
      processed_netrc = 1;
      if (home)
	{
	  int err;
	  struct stat buf;
	  char *path = (char *)alloca (strlen (home) + 1
				       + strlen (NETRC_FILE_NAME) + 1);
	  sprintf (path, "%s/%s", home, NETRC_FILE_NAME);
	  free (home);
	  err = stat (path, &buf);
	  if (err == 0)
	    netrc_list = parse_netrc (path);
	}
    }
  /* If nothing to do...  */
  if (!netrc_list)
    return;
  /* Acc and password found; all OK.  */
  if (*acc && *passwd)
    return;
  if (!*acc && !slack_default)
    return;
  /* Some data not given -- try finding the host.  */
  for (l = netrc_list; l; l = l->next)
    {
      if (!l->host)
	continue;
      else if (!strcasecmp (l->host, host))
	break;
    }
  if (l)
    {
      if (*acc)
	{
	  /* Looking for password in .netrc.  */
	  if (!strcmp (l->acc, *acc))
	    *passwd = l->passwd; /* usernames match; password OK */
	  else
	    *passwd = NULL;     /* usernames don't match */
	}
      else			/* NOT *acc */
	{
	  /* If password was given, use it.  The account is l->acc.  */
	  *acc = l->acc;
	  if (l->passwd)
	    *passwd = l->passwd;
	}
      return;
    }
  else
    {
      if (!slack_default)
	return;
      if (*acc)
	return;
      /* Try looking for the default account.  */
      for (l = netrc_list; l; l = l->next)
	if (!l->host)
	  break;
      if (!l)
	return;
      *acc = l->acc;
      if (!*passwd)
	*passwd = l->passwd;
      return;
    }
}


#ifdef STANDALONE
/* Normally, these functions would be defined by your package.  */
# define xmalloc malloc
# define xstrdup strdup

/* The function reads a whole line.  It reads the line realloc-ing the
   storage exponentially, doubling the storage after each overflow to
   minimize the number of calls to realloc().

   It is not an exemplary of correctness, since it kills off the
   newline (and no, there is no way to know if there was a newline at
   EOF).  */
# define xrealloc realloc
# define DYNAMIC_LINE_BUFFER 40

char *
read_whole_line (FILE *fp)
{
  char *line;
  int i, bufsize, c;

  i = 0;
  bufsize = DYNAMIC_LINE_BUFFER;
  line = xmalloc(bufsize);
  /* Construct the line.  */
  while ((c = getc(fp)) != EOF && c != '\n')
    {
      if (i > bufsize - 1)
	line = (char *)xrealloc(line, (bufsize <<= 1));
      line[i++] = c;
    }
  if (c == EOF && !i)
    {
      free(line);
      return NULL;
    }

  /* Check for overflow at zero-termination (no need to double the
     buffer in this case.  */
  if (i == bufsize)
    line = (char *)xrealloc(line, i + 1);
  line[i] = '\0';
  return line;
}

#endif /* STANDALONE */

/* Maybe add NEWENTRY to the account information list, LIST.  NEWENTRY is
   set to a ready-to-use acc_t, in any event.  */
static void
maybe_add_to_list (acc_t **newentry, acc_t **list)
{
  acc_t *a, *l;
  a = *newentry;
  l = *list;

  /* We need an account name in order to add the entry to the list.  */
  if (a && ! a->acc)
    {
      /* Free any allocated space.  */
      free (a->host);
      free (a->acc);
      free (a->passwd);
    }
  else
    {
      if (a)
	{
	  /* Add the current machine into our list.  */
	  a->next = l;
	  l = a;
	}

      /* Allocate a new acc_t structure.  */
      a = (acc_t *)xmalloc (sizeof (acc_t));
    }

  /* Zero the structure, so that it is ready to use.  */
  memset (a, 0, sizeof(*a));

  /* Return the new pointers.  */
  *newentry = a;
  *list = l;
  return;
}


/* Parse a .netrc file (as described in the ftp(1) manual page).  */
static acc_t *
parse_netrc (const char *path)
{
  FILE *fp;
  char *line, *p, *tok, *premature_token;
  acc_t *current, *retval;
  int ln;

  /* The latest token we've seen in the file.  */
  enum
  {
    tok_nothing, tok_account, tok_login, tok_macdef, tok_machine, tok_password
  } last_token = tok_nothing;

  current = retval = NULL;

  fp = fopen (path, "r");
  if (!fp)
    {
      fprintf (stderr, _("%s: Cannot read %s (%s).\n"), exec_name,
	       path, strerror (errno));
      return retval;
    }

  /* Initialize the file data.  */
  ln = 0;
  premature_token = NULL;

  /* While there are lines in the file...  */
  while ((line = read_whole_line (fp)))
    {
      ln ++;

      /* Parse the line.  */
      p = line;

      /* If the line is empty, then end any macro definition.  */
      if (last_token == tok_macdef && !*p)
	/* End of macro if the line is empty.  */
	last_token = tok_nothing;

      /* If we are defining macros, then skip parsing the line.  */
      while (*p && last_token != tok_macdef)
	{
	  /* Skip any whitespace.  */
	  while (*p && ISSPACE (*p))
	    p ++;

	  /* Discard end-of-line comments.  */
	  if (*p == '#')
	    break;

	  tok = p;

	  /* Find the end of the token.  */
	  while (*p && !ISSPACE (*p))
	    p ++;

	  /* Null-terminate the token, if it isn't already.  */
	  if (*p)
	    *p ++ = '\0';

	  switch (last_token)
	    {
	    case tok_login:
	      if (current)
		current->acc = xstrdup (tok);
	      else
		premature_token = "login";
	      break;

	    case tok_machine:
	      /* Start a new machine entry.  */
	      maybe_add_to_list (&current, &retval);
	      current->host = xstrdup (tok);
	      break;

	    case tok_password:
	      if (current)
		current->passwd = xstrdup (tok);
	      else
		premature_token = "password";
	      break;

	      /* We handle most of tok_macdef above.  */
	    case tok_macdef:
	      if (!current)
		premature_token = "macdef";
	      break;

	      /* We don't handle the account keyword at all.  */
	    case tok_account:
	      if (!current)
		premature_token = "account";
	      break;

	      /* We handle tok_nothing below this switch.  */
	    case tok_nothing:
	      break;
	    }

	  if (premature_token)
	    {
	      fprintf (stderr, _("\
%s: %s:%d: warning: \"%s\" token appears before any machine name\n"),
		       exec_name, path, ln, premature_token);
	      premature_token = NULL;
	    }

	  if (last_token != tok_nothing)
	    /* We got a value, so reset the token state.  */
	    last_token = tok_nothing;
	  else
	    {
	      /* Fetch the next token.  */
	      if (!strcmp (tok, "account"))
		last_token = tok_account;
	      else if (!strcmp (tok, "default"))
		{
		  maybe_add_to_list (&current, &retval);
		}
	      else if (!strcmp (tok, "login"))
		last_token = tok_login;

	      else if (!strcmp (tok, "macdef"))
		last_token = tok_macdef;

	      else if (!strcmp (tok, "machine"))
		last_token = tok_machine;

	      else if (!strcmp (tok, "password"))
		last_token = tok_password;

	      else
		fprintf (stderr, _("%s: %s:%d: unknown token \"%s\"\n"),
			 exec_name, path, ln, tok);
	    }
	}

      free (line);
    }

  fclose (fp);

  /* Finalize the last machine entry we found.  */
  maybe_add_to_list (&current, &retval);
  free (current);

  /* Reverse the order of the list so that it appears in file order.  */
  current = retval;
  retval = NULL;
  while (current)
    {
      acc_t *saved_reference;

      /* Change the direction of the pointers.  */
      saved_reference = current->next;
      current->next = retval;

      /* Advance to the next node.  */
      retval = current;
      current = saved_reference;
    }

  return retval;
}


/* Free a netrc list.  */
void
free_netrc(acc_t *l)
{
  acc_t *t;

  while (l)
    {
      t = l->next;
      FREE_MAYBE (l->acc);
      FREE_MAYBE (l->passwd);
      FREE_MAYBE (l->host);
      free(l);
      l = t;
    }
}

#ifdef STANDALONE
#include <sys/types.h>
#include <sys/stat.h>

int
main (int argc, char **argv)
{
  struct stat sb;
  char *program_name, *file, *target;
  acc_t *head, *a;

  if (argc < 2 || argc > 3)
    {
      fprintf (stderr, _("Usage: %s NETRC [HOSTNAME]\n"), argv[0]);
      exit (1);
    }

  program_name = argv[0];
  file = argv[1];
  target = argv[2];

  if (stat (file, &sb))
    {
      fprintf (stderr, _("%s: cannot stat %s: %s\n"), argv[0], file,
	       strerror (errno));
      exit (1);
    }

  head = parse_netrc (file);
  a = head;
  while (a)
    {
      /* Skip if we have a target and this isn't it.  */
      if (target && a->host && strcmp (target, a->host))
	{
	  a = a->next;
	  continue;
	}

      if (!target)
	{
	  /* Print the host name if we have no target.  */
	  if (a->host)
	    fputs (a->host, stdout);
	  else
	    fputs ("DEFAULT", stdout);

	  fputc (' ', stdout);
	}

      /* Print the account name.  */
      fputs (a->acc, stdout);

      if (a->passwd)
	{
	  /* Print the password, if there is any.  */
	  fputc (' ', stdout);
	  fputs (a->passwd, stdout);
	}

      fputc ('\n', stdout);

      /* Exit if we found the target.  */
      if (target)
	exit (0);
      a = a->next;
    }

  /* Exit with failure if we had a target, success otherwise.  */
  if (target)
    exit (1);

  exit (0);
}
#endif /* STANDALONE */
