/* Reading/parsing the initialization file.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

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

#include <config.h>

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <errno.h>

#ifdef HAVE_PWD_H
#include <pwd.h>
#endif

#include "wget.h"
#include "utils.h"
#include "init.h"
#include "host.h"
#include "recur.h"
#include "netrc.h"

#ifndef errno
extern int errno;
#endif


#define CMD_DECLARE(func) static int func \
  PARAMS ((const char *, const char *, void *))

CMD_DECLARE (cmd_boolean);
CMD_DECLARE (cmd_boolean);
CMD_DECLARE (cmd_number);
CMD_DECLARE (cmd_number_inf);
CMD_DECLARE (cmd_string);
CMD_DECLARE (cmd_vector);
CMD_DECLARE (cmd_directory_vector);
CMD_DECLARE (cmd_bytes);
CMD_DECLARE (cmd_time);

CMD_DECLARE (cmd_spec_dirstruct);
CMD_DECLARE (cmd_spec_dotstyle);
CMD_DECLARE (cmd_spec_header);
CMD_DECLARE (cmd_spec_htmlify);
CMD_DECLARE (cmd_spec_mirror);
CMD_DECLARE (cmd_spec_outputdocument);
CMD_DECLARE (cmd_spec_recursive);
CMD_DECLARE (cmd_spec_useragent);

/* List of recognized commands, each consisting of name, closure and
   function.  When adding a new command, simply add it to the list,
   but be sure to keep the list sorted alphabetically, as comind()
   depends on it.  */
static struct {
  char *name;
  void *closure;
  int (*action) PARAMS ((const char *, const char *, void *));
} commands[] = {
  { "accept",		&opt.accepts,		cmd_vector },
  { "addhostdir",	&opt.add_hostdir,	cmd_boolean },
  { "alwaysrest",	&opt.always_rest,	cmd_boolean }, /* deprecated */
  { "background",	&opt.background,	cmd_boolean },
  { "backups",		&opt.backups,		cmd_number },
  { "base",		&opt.base_href,		cmd_string },
  { "cache",		&opt.proxy_cache,	cmd_boolean },
  { "continue",		&opt.always_rest,	cmd_boolean },
  { "convertlinks",	&opt.convert_links,	cmd_boolean },
  { "cutdirs",		&opt.cut_dirs,		cmd_number },
#ifdef DEBUG
  { "debug",		&opt.debug,		cmd_boolean },
#endif
  { "deleteafter",	&opt.delete_after,	cmd_boolean },
  { "dirprefix",	&opt.dir_prefix,	cmd_string },
  { "dirstruct",	NULL,			cmd_spec_dirstruct },
  { "domains",		&opt.domains,		cmd_vector },
  { "dotbytes",		&opt.dot_bytes,		cmd_bytes },
  { "dotsinline",	&opt.dots_in_line,	cmd_number },
  { "dotspacing",	&opt.dot_spacing,	cmd_number },
  { "dotstyle",		NULL,			cmd_spec_dotstyle },
  { "excludedirectories", &opt.excludes,	cmd_directory_vector },
  { "excludedomains",	&opt.exclude_domains,	cmd_vector },
  { "followftp",	&opt.follow_ftp,	cmd_boolean },
  { "forcehtml",	&opt.force_html,	cmd_boolean },
  { "ftpproxy",		&opt.ftp_proxy,		cmd_string },
  { "glob",		&opt.ftp_glob,		cmd_boolean },
  { "header",		NULL,			cmd_spec_header },
  { "htmlify",		NULL,			cmd_spec_htmlify },
  { "httppasswd",	&opt.http_passwd,	cmd_string },
  { "httpproxy",	&opt.http_proxy,	cmd_string },
  { "httpuser",		&opt.http_user,		cmd_string },
  { "ignorelength",	&opt.ignore_length,	cmd_boolean },
  { "includedirectories", &opt.includes,	cmd_directory_vector },
  { "input",		&opt.input_filename,	cmd_string },
  { "killlonger",	&opt.kill_longer,	cmd_boolean },
  { "logfile",		&opt.lfilename,		cmd_string },
  { "login",		&opt.ftp_acc,		cmd_string },
  { "mirror",		NULL,			cmd_spec_mirror },
  { "netrc",		&opt.netrc,		cmd_boolean },
  { "noclobber",	&opt.noclobber,		cmd_boolean },
  { "noparent",		&opt.no_parent,		cmd_boolean },
  { "noproxy",		&opt.no_proxy,		cmd_vector },
  { "numtries",		&opt.ntry,		cmd_number_inf }, /* deprecated */
  { "outputdocument",	NULL,			cmd_spec_outputdocument },
  { "passiveftp",	&opt.ftp_pasv,		cmd_boolean },
  { "passwd",		&opt.ftp_pass,		cmd_string },
  { "proxypasswd",	&opt.proxy_passwd,	cmd_string },
  { "proxyuser",	&opt.proxy_user,	cmd_string },
  { "quiet",		&opt.quiet,		cmd_boolean },
  { "quota",		&opt.quota,		cmd_bytes },
  { "reclevel",		&opt.reclevel,		cmd_number_inf },
  { "recursive",	NULL,			cmd_spec_recursive },
  { "reject",		&opt.rejects,		cmd_vector },
  { "relativeonly",	&opt.relative_only,	cmd_boolean },
  { "removelisting",	&opt.remove_listing,	cmd_boolean },
  { "retrsymlinks",	&opt.retr_symlinks,	cmd_boolean },
  { "robots",		&opt.use_robots,	cmd_boolean },
  { "saveheaders",	&opt.save_headers,	cmd_boolean },
  { "serverresponse",	&opt.server_response,	cmd_boolean },
  { "simplehostcheck",	&opt.simple_check,	cmd_boolean },
  { "spanhosts",	&opt.spanhost,		cmd_boolean },
  { "spider",		&opt.spider,		cmd_boolean },
  { "timeout",		&opt.timeout,		cmd_time },
  { "timestamping",	&opt.timestamping,	cmd_boolean },
  { "tries",		&opt.ntry,		cmd_number_inf },
  { "useproxy",		&opt.use_proxy,		cmd_boolean },
  { "useragent",	NULL,			cmd_spec_useragent },
  { "verbose",		&opt.verbose,		cmd_boolean },
  { "wait",		&opt.wait,		cmd_time }
};

/* Return index of COM if it is a valid command, or -1 otherwise.  COM
   is looked up in `commands' using binary search algorithm.  */
static int
comind (const char *com)
{
  int min = 0, max = ARRAY_SIZE (commands);

  do
    {
      int i = (min + max) / 2;
      int cmp = strcasecmp (com, commands[i].name);
      if (cmp == 0)
	return i;
      else if (cmp < 0)
	max = i - 1;
      else
	min = i + 1;
    }
  while (min <= max);
  return -1;
}

/* Reset the variables to default values.  */
static void
defaults (void)
{
  char *tmp;

  /* Most of the default values are 0.  Just reset everything, and
     fill in the non-zero values.  Note that initializing pointers to
     NULL this way is technically illegal, but porting Wget to a
     machine where NULL is not all-zero bit pattern will be the least
     of the implementors' worries.  */
  memset (&opt, 0, sizeof (opt));

  opt.verbose = -1;
  opt.dir_prefix = xstrdup (".");
  opt.ntry = 20;
  opt.reclevel = 5;
  opt.add_hostdir = 1;
  opt.ftp_acc = xstrdup ("anonymous");
  /*opt.ftp_pass = xstrdup (ftp_getaddress ());*/
  opt.netrc = 1;
  opt.ftp_glob = 1;
  opt.htmlify = 1;
  opt.use_proxy = 1;
  tmp = getenv ("no_proxy");
  if (tmp)
    opt.no_proxy = sepstring (tmp);
  opt.proxy_cache = 1;

#ifdef HAVE_SELECT
  opt.timeout = 900;
#endif
  opt.use_robots = 1;

  opt.remove_listing = 1;

  opt.dot_bytes = 1024;
  opt.dot_spacing = 10;
  opt.dots_in_line = 50;
}

/* Return the user's home directory (strdup-ed), or NULL if none is
   found.  */
char *
home_dir (void)
{
  char *home = getenv ("HOME");

  if (!home)
    {
#ifndef WINDOWS
      /* If HOME is not defined, try getting it from the password
         file.  */
      struct passwd *pwd = getpwuid (getuid ());
      if (!pwd || !pwd->pw_dir)
	return NULL;
      home = pwd->pw_dir;
#else  /* WINDOWS */
      home = "C:\\";
      /* #### Maybe I should grab home_dir from registry, but the best
	 that I could get from there is user's Start menu.  It sucks!  */
#endif /* WINDOWS */
    }

  return home ? xstrdup (home) : NULL;
}

/* Return the path to the user's .wgetrc.  This is either the value of
   `WGETRC' environment variable, or `$HOME/.wgetrc'.

   If the `WGETRC' variable exists but the file does not exist, the
   function will exit().  */
static char *
wgetrc_file_name (void)
{
  char *env, *home;
  char *file = NULL;

  /* Try the environment.  */
  env = getenv ("WGETRC");
  if (env && *env)
    {
      if (!file_exists_p (env))
	{
	  fprintf (stderr, "%s: %s: %s.\n", exec_name, file, strerror (errno));
	  exit (1);
	}
      return xstrdup (env);
    }

#ifndef WINDOWS
  /* If that failed, try $HOME/.wgetrc.  */
  home = home_dir ();
  if (home)
    {
      file = (char *)xmalloc (strlen (home) + 1 + strlen (".wgetrc") + 1);
      sprintf (file, "%s/.wgetrc", home);
    }
#else  /* WINDOWS */
  /* Under Windows, "home" is (for the purposes of this function) the
     directory where `wget.exe' resides, and `wget.ini' will be used
     as file name.  SYSTEM_WGETRC should not be defined under WINDOWS.

     It is not as trivial as I assumed, because on 95 argv[0] is full
     path, but on NT you get what you typed in command line.  --dbudor */
  home = ws_mypath ();
  if (home)
    {
      file = (char *)xmalloc (strlen (home) + strlen ("wget.ini") + 1);
      sprintf (file, "%swget.ini", home);
    }
#endif /* WINDOWS */

  FREE_MAYBE (home);
  if (!file)
    return NULL;
  if (!file_exists_p (file))
    {
      free (file);
      return NULL;
    }
  return file;
}

/* Initialize variables from a wgetrc file */
static void
run_wgetrc (const char *file)
{
  FILE *fp;
  char *line;
  int ln;

  fp = fopen (file, "rb");
  if (!fp)
    {
      fprintf (stderr, _("%s: Cannot read %s (%s).\n"), exec_name,
	       file, strerror (errno));
      return;
    }
  /* Reset line number.  */
  ln = 1;
  while ((line = read_whole_line (fp)))
    {
      char *com, *val;
      int status;
      int length = strlen (line);

      if (length && line[length - 1] == '\r')
	line[length - 1] = '\0';
      /* Parse the line.  */
      status = parse_line (line, &com, &val);
      free (line);
      /* If everything is OK, set the value.  */
      if (status == 1)
	{
	  if (!setval (com, val))
	    fprintf (stderr, _("%s: Error in %s at line %d.\n"), exec_name,
		     file, ln);
	  free (com);
	  free (val);
	}
      else if (status == 0)
	fprintf (stderr, _("%s: Error in %s at line %d.\n"), exec_name,
		 file, ln);
      ++ln;
    }
  fclose (fp);
}

/* Initialize the defaults and run the system wgetrc and user's own
   wgetrc.  */
void
initialize (void)
{
  char *file;

  /* Load the hard-coded defaults.  */
  defaults ();

  /* If SYSTEM_WGETRC is defined, use it.  */
#ifdef SYSTEM_WGETRC
  if (file_exists_p (SYSTEM_WGETRC))
    run_wgetrc (SYSTEM_WGETRC);
#endif
  /* Override it with your own, if one exists.  */
  file = wgetrc_file_name ();
  if (!file)
    return;
  /* #### We should somehow canonicalize `file' and SYSTEM_WGETRC,
     really.  */
#ifdef SYSTEM_WGETRC
  if (!strcmp (file, SYSTEM_WGETRC))
    {
      fprintf (stderr, _("\
%s: Warning: Both system and user wgetrc point to `%s'.\n"),
	       exec_name, file);
    }
  else
#endif
    run_wgetrc (file);
  free (file);
  return;
}

/* Parse the line pointed by line, with the syntax:
   <sp>* command <sp>* = <sp>* value <newline>
   Uses malloc to allocate space for command and value.
   If the line is invalid, data is freed and 0 is returned.

   Return values:
    1 - success
    0 - failure
   -1 - empty */
int
parse_line (const char *line, char **com, char **val)
{
  const char *p = line;
  const char *orig_comptr, *end;
  char *new_comptr;

  /* Skip spaces.  */
  while (*p == ' ' || *p == '\t')
    ++p;

  /* Don't process empty lines.  */
  if (!*p || *p == '\n' || *p == '#')
    return -1;

  for (orig_comptr = p; ISALPHA (*p) || *p == '_' || *p == '-'; p++)
    ;
  /* The next char should be space or '='.  */
  if (!ISSPACE (*p) && (*p != '='))
    return 0;
  *com = (char *)xmalloc (p - orig_comptr + 1);
  for (new_comptr = *com; orig_comptr < p; orig_comptr++)
    {
      if (*orig_comptr == '_' || *orig_comptr == '-')
	continue;
      *new_comptr++ = *orig_comptr;
    }
  *new_comptr = '\0';
  /* If the command is invalid, exit now.  */
  if (comind (*com) == -1)
    {
      free (*com);
      return 0;
    }

  /* Skip spaces before '='.  */
  for (; ISSPACE (*p); p++);
  /* If '=' not found, bail out.  */
  if (*p != '=')
    {
      free (*com);
      return 0;
    }
  /* Skip spaces after '='.  */
  for (++p; ISSPACE (*p); p++);
  /* Get the ending position.  */
  for (end = p; *end && *end != '\n'; end++);
  /* Allocate *val, and copy from line.  */
  *val = strdupdelim (p, end);
  return 1;
}

/* Set COM to VAL.  This is the meat behind processing `.wgetrc'.  No
   fatals -- error signal prints a warning and resets to default
   value.  All error messages are printed to stderr, *not* to
   opt.lfile, since opt.lfile wasn't even generated yet.  */
int
setval (const char *com, const char *val)
{
  int ind;

  if (!com || !val)
    return 0;
  ind = comind (com);
  if (ind == -1)
    {
      /* #### Should I just abort()?  */
#ifdef DEBUG
      fprintf (stderr, _("%s: BUG: unknown command `%s', value `%s'.\n"),
	       exec_name, com, val);
#endif
      return 0;
    }
  return ((*commands[ind].action) (com, val, commands[ind].closure));
}

/* Generic helper functions, for use with `commands'. */

static int myatoi PARAMS ((const char *s));

/* Store the boolean value from VAL to CLOSURE.  COM is ignored,
   except for error messages.  */
static int
cmd_boolean (const char *com, const char *val, void *closure)
{
  int bool_value;

  if (!strcasecmp (val, "on")
      || (*val == '1' && !*(val + 1)))
    bool_value = 1;
  else if (!strcasecmp (val, "off")
	   || (*val == '0' && !*(val + 1)))
    bool_value = 0;
  else
    {
      fprintf (stderr, _("%s: %s: Please specify on or off.\n"),
	       exec_name, com);
      return 0;
    }

  *(int *)closure = bool_value;
  return 1;
}

/* Set the non-negative integer value from VAL to CLOSURE.  With
   incorrect specification, the number remains unchanged.  */
static int
cmd_number (const char *com, const char *val, void *closure)
{
  int num = myatoi (val);

  if (num == -1)
    {
      fprintf (stderr, _("%s: %s: Invalid specification `%s'.\n"),
	       exec_name, com, val);
      return 0;
    }
  *(int *)closure = num;
  return 1;
}

/* Similar to cmd_number(), only accepts `inf' as a synonym for 0.  */
static int
cmd_number_inf (const char *com, const char *val, void *closure)
{
  if (!strcasecmp (val, "inf"))
    {
      *(int *)closure = 0;
      return 1;
    }
  return cmd_number (com, val, closure);
}

/* Copy (strdup) the string at COM to a new location and place a
   pointer to *CLOSURE.  */
static int
cmd_string (const char *com, const char *val, void *closure)
{
  char **pstring = (char **)closure;

  FREE_MAYBE (*pstring);
  *pstring = xstrdup (val);
  return 1;
}

/* Merge the vector (array of strings separated with `,') in COM with
   the vector (NULL-terminated array of strings) pointed to by
   CLOSURE.  */
static int
cmd_vector (const char *com, const char *val, void *closure)
{
  char ***pvec = (char ***)closure;

  if (*val)
    *pvec = merge_vecs (*pvec, sepstring (val));
  else
    {
      free_vec (*pvec);
      *pvec = NULL;
    }
  return 1;
}

static int
cmd_directory_vector (const char *com, const char *val, void *closure)
{
  char ***pvec = (char ***)closure;

  if (*val)
    {
      /* Strip the trailing slashes from directories.  */
      char **t, **seps;

      seps = sepstring (val);
      for (t = seps; t && *t; t++)
	{
	  int len = strlen (*t);
	  /* Skip degenerate case of root directory.  */
	  if (len > 1)
	    {
	      if ((*t)[len - 1] == '/')
		(*t)[len - 1] = '\0';
	    }
	}
      *pvec = merge_vecs (*pvec, seps);
    }
  else
    {
      free_vec (*pvec);
      *pvec = NULL;
    }
  return 1;
}

/* Set the value stored in VAL to CLOSURE (which should point to a
   long int), allowing several postfixes, with the following syntax
   (regexp):

   [0-9]+       -> bytes
   [0-9]+[kK]   -> bytes * 1024
   [0-9]+[mM]   -> bytes * 1024 * 1024
   inf          -> 0

   Anything else is flagged as incorrect, and CLOSURE is unchanged.  */
static int
cmd_bytes (const char *com, const char *val, void *closure)
{
  long result;
  long *out = (long *)closure;
  const char *p;

  result = 0;
  p = val;
  /* Check for "inf".  */
  if (p[0] == 'i' && p[1] == 'n' && p[2] == 'f' && p[3] == '\0')
    {
      *out = 0;
      return 1;
    }
  /* Search for digits and construct result.  */
  for (; *p && ISDIGIT (*p); p++)
    result = (10 * result) + (*p - '0');
  /* If no digits were found, or more than one character is following
     them, bail out.  */
  if (p == val || (*p != '\0' && *(p + 1) != '\0'))
    {
      printf (_("%s: Invalid specification `%s'\n"), com, val);
      return 0;
    }
  /* Search for a designator.  */
  switch (tolower (*p))
    {
    case '\0':
      /* None */
      break;
    case 'k':
      /* Kilobytes */
      result *= 1024;
      break;
    case 'm':
      /* Megabytes */
      result *= (long)1024 * 1024;
      break;
    case 'g':
      /* Gigabytes */
      result *= (long)1024 * 1024 * 1024;
      break;
    default:
      printf (_("%s: Invalid specification `%s'\n"), com, val);
      return 0;
    }
  *out = result;
  return 1;
}

/* Store the value of VAL to *OUT, allowing suffixes for minutes and
   hours.  */
static int
cmd_time (const char *com, const char *val, void *closure)
{
  long result = 0;
  const char *p = val;

  /* Search for digits and construct result.  */
  for (; *p && ISDIGIT (*p); p++)
    result = (10 * result) + (*p - '0');
  /* If no digits were found, or more than one character is following
     them, bail out.  */
  if (p == val || (*p != '\0' && *(p + 1) != '\0'))
    {
      printf (_("%s: Invalid specification `%s'\n"), com, val);
      return 0;
    }
  /* Search for a suffix.  */
  switch (tolower (*p))
    {
    case '\0':
      /* None */
      break;
    case 'm':
      /* Minutes */
      result *= 60;
      break;
    case 'h':
      /* Seconds */
      result *= 3600;
      break;
    case 'd':
      /* Days (overflow on 16bit machines) */
      result *= 86400L;
      break;
    case 'w':
      /* Weeks :-) */
      result *= 604800L;
      break;
    default:
      printf (_("%s: Invalid specification `%s'\n"), com, val);
      return 0;
    }
  *(long *)closure = result;
  return 1;
}

/* Specialized helper functions, used by `commands' to handle some
   options specially.  */

static int check_user_specified_header PARAMS ((const char *));

static int
cmd_spec_dirstruct (const char *com, const char *val, void *closure)
{
  if (!cmd_boolean (com, val, &opt.dirstruct))
    return 0;
  /* Since dirstruct behaviour is explicitly changed, no_dirstruct
     must be affected inversely.  */
  if (opt.dirstruct)
    opt.no_dirstruct = 0;
  else
    opt.no_dirstruct = 1;
  return 1;
}

static int
cmd_spec_dotstyle (const char *com, const char *val, void *closure)
{
  /* Retrieval styles.  */
  if (!strcasecmp (val, "default"))
    {
      /* Default style: 1K dots, 10 dots in a cluster, 50 dots in a
	 line.  */
      opt.dot_bytes = 1024;
      opt.dot_spacing = 10;
      opt.dots_in_line = 50;
    }
  else if (!strcasecmp (val, "binary"))
    {
      /* "Binary" retrieval: 8K dots, 16 dots in a cluster, 48 dots
	 (384K) in a line.  */
      opt.dot_bytes = 8192;
      opt.dot_spacing = 16;
      opt.dots_in_line = 48;
    }
  else if (!strcasecmp (val, "mega"))
    {
      /* "Mega" retrieval, for retrieving very long files; each dot is
	 64K, 8 dots in a cluster, 6 clusters (3M) in a line.  */
      opt.dot_bytes = 65536L;
      opt.dot_spacing = 8;
      opt.dots_in_line = 48;
    }
  else if (!strcasecmp (val, "giga"))
    {
      /* "Giga" retrieval, for retrieving very very *very* long files;
	 each dot is 1M, 8 dots in a cluster, 4 clusters (32M) in a
	 line.  */
      opt.dot_bytes = (1L << 20);
      opt.dot_spacing = 8;
      opt.dots_in_line = 32;
    }
  else if (!strcasecmp (val, "micro"))
    {
      /* "Micro" retrieval, for retrieving very small files (and/or
	 slow connections); each dot is 128 bytes, 8 dots in a
	 cluster, 6 clusters (6K) in a line.  */
      opt.dot_bytes = 128;
      opt.dot_spacing = 8;
      opt.dots_in_line = 48;
    }
  else
    {
      fprintf (stderr, _("%s: %s: Invalid specification `%s'.\n"),
	       exec_name, com, val);
      return 0;
    }
  return 1;
}

static int
cmd_spec_header (const char *com, const char *val, void *closure)
{
  if (!*val)
    {
      /* Empty header means reset headers.  */
      FREE_MAYBE (opt.user_header);
      opt.user_header = NULL;
    }
  else
    {
      int i;

      if (!check_user_specified_header (val))
	{
	  fprintf (stderr, _("%s: %s: Invalid specification `%s'.\n"),
		   exec_name, com, val);
	  return 0;
	}
      i = opt.user_header ? strlen (opt.user_header) : 0;
      opt.user_header = (char *)xrealloc (opt.user_header, i + strlen (val)
					  + 2 + 1);
      strcpy (opt.user_header + i, val);
      i += strlen (val);
      opt.user_header[i++] = '\r';
      opt.user_header[i++] = '\n';
      opt.user_header[i] = '\0';
    }
  return 1;
}

static int
cmd_spec_htmlify (const char *com, const char *val, void *closure)
{
  int flag = cmd_boolean (com, val, &opt.htmlify);
  if (flag && !opt.htmlify)
    opt.remove_listing = 0;
  return flag;
}

static int
cmd_spec_mirror (const char *com, const char *val, void *closure)
{
  int mirror;

  if (!cmd_boolean (com, val, &mirror))
    return 0;
  if (mirror)
    {
      opt.recursive = 1;
      if (!opt.no_dirstruct)
	opt.dirstruct = 1;
      opt.timestamping = 1;
      opt.reclevel = 0;
      opt.remove_listing = 0;
    }
  return 1;
}

static int
cmd_spec_outputdocument (const char *com, const char *val, void *closure)
{
  FREE_MAYBE (opt.output_document);
  opt.output_document = xstrdup (val);
  opt.ntry = 1;
  return 1;
}

static int
cmd_spec_recursive (const char *com, const char *val, void *closure)
{
  if (!cmd_boolean (com, val, &opt.recursive))
    return 0;
  else
    {
      if (opt.recursive && !opt.no_dirstruct)
	opt.dirstruct = 1;
    }
  return 1;
}

static int
cmd_spec_useragent (const char *com, const char *val, void *closure)
{
  /* Just check for empty string and newline, so we don't throw total
     junk to the server.  */
  if (!*val || strchr (val, '\n'))
    {
      fprintf (stderr, _("%s: %s: Invalid specification `%s'.\n"),
	       exec_name, com, val);
      return 0;
    }
  opt.useragent = xstrdup (val);
  return 1;
}

/* Miscellaneous useful routines.  */

/* Return the integer value of a positive integer written in S, or -1
   if an error was encountered.  */
static int
myatoi (const char *s)
{
  int res;
  const char *orig = s;

  for (res = 0; *s && ISDIGIT (*s); s++)
    res = 10 * res + (*s - '0');
  if (*s || orig == s)
    return -1;
  else
    return res;
}

#define ISODIGIT(x) ((x) >= '0' && (x) <= '7')

static int
check_user_specified_header (const char *s)
{
  const char *p;

  for (p = s; *p && *p != ':' && !ISSPACE (*p); p++);
  /* The header MUST contain `:' preceded by at least one
     non-whitespace character.  */
  if (*p != ':' || p == s)
    return 0;
  /* The header MUST NOT contain newlines.  */
  if (strchr (s, '\n'))
    return 0;
  return 1;
}

/* Free the memory allocated by global variables.  */
void
cleanup (void)
{
  extern acc_t *netrc_list;

  recursive_cleanup ();
  clean_hosts ();
  free_netrc (netrc_list);
  if (opt.dfp)
    fclose (opt.dfp);
  FREE_MAYBE (opt.lfilename);
  free (opt.dir_prefix);
  FREE_MAYBE (opt.input_filename);
  FREE_MAYBE (opt.output_document);
  free_vec (opt.accepts);
  free_vec (opt.rejects);
  free_vec (opt.excludes);
  free_vec (opt.includes);
  free_vec (opt.domains);
  free (opt.ftp_acc);
  free (opt.ftp_pass);
  FREE_MAYBE (opt.ftp_proxy);
  FREE_MAYBE (opt.http_proxy);
  free_vec (opt.no_proxy);
  FREE_MAYBE (opt.useragent);
  FREE_MAYBE (opt.http_user);
  FREE_MAYBE (opt.http_passwd);
  FREE_MAYBE (opt.user_header);
}
