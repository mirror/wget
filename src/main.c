/* Command line parsing.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001
   Free Software Foundation, Inc.

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
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <sys/types.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif
#ifdef HAVE_NLS
#ifdef HAVE_LOCALE_H
# include <locale.h>
#endif /* HAVE_LOCALE_H */
#endif /* HAVE_NLS */
#include <errno.h>

#define OPTIONS_DEFINED_HERE	/* for options.h */

#include "wget.h"
#include "utils.h"
#include "getopt.h"
#include "init.h"
#include "retr.h"
#include "recur.h"
#include "host.h"
#include "cookies.h"

#ifndef PATH_SEPARATOR
# define PATH_SEPARATOR '/'
#endif

extern char *version_string;

#ifndef errno
extern int errno;
#endif

struct options opt;

/* From log.c.  */
void log_init PARAMS ((const char *, int));
void log_close PARAMS ((void));
void redirect_output PARAMS ((const char *));

static RETSIGTYPE redirect_output_signal PARAMS ((int));

const char *exec_name;

/* Initialize I18N.  The initialization amounts to invoking
   setlocale(), bindtextdomain() and textdomain().
   Does nothing if NLS is disabled or missing.  */
static void
i18n_initialize (void)
{
  /* If HAVE_NLS is defined, assume the existence of the three
     functions invoked here.  */
#ifdef HAVE_NLS
  /* Set the current locale.  */
  /* Here we use LC_MESSAGES instead of LC_ALL, for two reasons.
     First, message catalogs are all of I18N Wget uses anyway.
     Second, setting LC_ALL has a dangerous potential of messing
     things up.  For example, when in a foreign locale, Solaris
     strptime() fails to handle international dates correctly, which
     makes http_atotm() malfunction.  */
#ifdef LC_MESSAGES
  setlocale (LC_MESSAGES, "");
  setlocale (LC_CTYPE, "");
#else
  setlocale (LC_ALL, "");
#endif
  /* Set the text message domain.  */
  bindtextdomain ("wget", LOCALEDIR);
  textdomain ("wget");
#endif /* HAVE_NLS */
}

/* It's kosher to declare these here because their interface _has_ to
   be void foo(void).  */
void host_init PARAMS ((void));

/* This just calls the various initialization functions from the
   modules that need one-time initialization. */
static void
private_initialize (void)
{
  host_init ();
}

/* Print the usage message.  */
static void
print_usage (void)
{
  printf (_("Usage: %s [OPTION]... [URL]...\n"), exec_name);
}

/* Print the help message, describing all the available options.  If
   you add an option, be sure to update this list.  */
static void
print_help (void)
{
  printf (_("GNU Wget %s, a non-interactive network retriever.\n"),
	  version_string);
  print_usage ();
  /* Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
     don't bitch.  Also, it makes translation much easier.  */
  fputs (_("\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n"), stdout);
  fputs (_("\
Startup:\n\
  -V,  --version           display the version of Wget and exit.\n\
  -h,  --help              print this help.\n\
  -b,  --background        go to background after startup.\n\
  -e,  --execute=COMMAND   execute a `.wgetrc\'-style command.\n\
\n"), stdout);
  fputs (_("\
Logging and input file:\n\
  -o,  --output-file=FILE     log messages to FILE.\n\
  -a,  --append-output=FILE   append messages to FILE.\n\
  -d,  --debug                print debug output.\n\
  -q,  --quiet                quiet (no output).\n\
  -v,  --verbose              be verbose (this is the default).\n\
  -nv, --non-verbose          turn off verboseness, without being quiet.\n\
  -i,  --input-file=FILE      download URLs found in FILE.\n\
  -F,  --force-html           treat input file as HTML.\n\
  -B,  --base=URL             prepends URL to relative links in -F -i file.\n\
       --sslcertfile=FILE     optional client certificate.\n\
       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n\
\n"), stdout);
  fputs (_("\
Download:\n\
       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n\
  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n\
  -O   --output-document=FILE   write documents to FILE.\n\
  -nc, --no-clobber             don\'t clobber existing files or use .# suffixes.\n\
  -c,  --continue               resume getting a partially-downloaded file.\n\
       --dot-style=STYLE        set retrieval display style.\n\
  -N,  --timestamping           don\'t re-retrieve files unless newer than local.\n\
  -S,  --server-response        print server response.\n\
       --spider                 don\'t download anything.\n\
  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n\
  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n\
       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n\
  -Y,  --proxy=on/off           turn proxy on or off.\n\
  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n\
\n"), stdout);
  fputs (_("\
Directories:\n\
  -nd  --no-directories            don\'t create directories.\n\
  -x,  --force-directories         force creation of directories.\n\
  -nH, --no-host-directories       don\'t create host directories.\n\
  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n\
       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n\
\n"), stdout);
  fputs (_("\
HTTP options:\n\
       --http-user=USER      set http user to USER.\n\
       --http-passwd=PASS    set http password to PASS.\n\
  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\n\
  -E,  --html-extension      save all text/html documents with .html extension.\n\
       --ignore-length       ignore `Content-Length\' header field.\n\
       --header=STRING       insert STRING among the headers.\n\
       --proxy-user=USER     set USER as proxy username.\n\
       --proxy-passwd=PASS   set PASS as proxy password.\n\
       --referer=URL         include `Referer: URL\' header in HTTP request.\n\
  -s,  --save-headers        save the HTTP headers to file.\n\
  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n\
       --no-http-keep-alive  disable HTTP keep-alive (persistent connections).\n\
       --cookies=off         don't use cookies.\n\
       --load-cookies=FILE   load cookies from FILE before session.\n\
       --save-cookies=FILE   save cookies to FILE after session.\n\
\n"), stdout);
  fputs (_("\
FTP options:\n\
  -nr, --dont-remove-listing   don\'t remove `.listing\' files.\n\
  -g,  --glob=on/off           turn file name globbing on or off.\n\
       --passive-ftp           use the \"passive\" transfer mode.\n\
       --retr-symlinks         when recursing, get linked-to files (not dirs).\n\
\n"), stdout);
  fputs (_("\
Recursive retrieval:\n\
  -r,  --recursive          recursive web-suck -- use with care!\n\
  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n\
       --delete-after       delete files locally after downloading them.\n\
  -k,  --convert-links      convert non-relative links to relative.\n\
  -K,  --backup-converted   before converting file X, back up as X.orig.\n\
  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n\
  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n\
\n"), stdout);
  fputs (_("\
Recursive accept/reject:\n\
  -A,  --accept=LIST                comma-separated list of accepted extensions.\n\
  -R,  --reject=LIST                comma-separated list of rejected extensions.\n\
  -D,  --domains=LIST               comma-separated list of accepted domains.\n\
       --exclude-domains=LIST       comma-separated list of rejected domains.\n\
       --follow-ftp                 follow FTP links from HTML documents.\n\
       --follow-tags=LIST           comma-separated list of followed HTML tags.\n\
  -G,  --ignore-tags=LIST           comma-separated list of ignored HTML tags.\n\
  -H,  --span-hosts                 go to foreign hosts when recursive.\n\
  -L,  --relative                   follow relative links only.\n\
  -I,  --include-directories=LIST   list of allowed directories.\n\
  -X,  --exclude-directories=LIST   list of excluded directories.\n\
  -nh, --no-host-lookup             don\'t DNS-lookup hosts.\n\
  -np, --no-parent                  don\'t ascend to the parent directory.\n\
\n"), stdout);
  fputs (_("Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"),
	 stdout);
}

int
main (int argc, char *const *argv)
{
  char **url, **t;
  int i, c, nurl, status, append_to_log;
  int wr = 0;

  static struct option long_options[] =
  {
    /* Options without arguments: */
    { "background", no_argument, NULL, 'b' },
    { "backup-converted", no_argument, NULL, 'K' },
    { "continue", no_argument, NULL, 'c' },
    { "convert-links", no_argument, NULL, 'k' },
    { "debug", no_argument, NULL, 'd' },
    { "delete-after", no_argument, NULL, 136 },
    { "dont-remove-listing", no_argument, NULL, 149 },
    { "follow-ftp", no_argument, NULL, 142 },
    { "force-directories", no_argument, NULL, 'x' },
    { "force-hier", no_argument, NULL, 'x' }, /* obsolete */
    { "force-html", no_argument, NULL, 'F'},
    { "help", no_argument, NULL, 'h' },
    { "html-extension", no_argument, NULL, 'E' },
    { "ignore-length", no_argument, NULL, 138 },
    { "mirror", no_argument, NULL, 'm' },
    { "no-clobber", no_argument, NULL, 141 },
    { "no-directories", no_argument, NULL, 147 },
    { "no-host-directories", no_argument, NULL, 148 },
    { "no-host-lookup", no_argument, NULL, 150 },
    { "no-http-keep-alive", no_argument, NULL, 156 },
    { "no-parent", no_argument, NULL, 133 },
    { "non-verbose", no_argument, NULL, 146 },
    { "passive-ftp", no_argument, NULL, 139 },
    { "page-requisites", no_argument, NULL, 'p' },
    { "quiet", no_argument, NULL, 'q' },
    { "recursive", no_argument, NULL, 'r' },
    { "relative", no_argument, NULL, 'L' },
    { "retr-symlinks", no_argument, NULL, 137 },
    { "save-headers", no_argument, NULL, 's' },
    { "server-response", no_argument, NULL, 'S' },
    { "span-hosts", no_argument, NULL, 'H' },
    { "spider", no_argument, NULL, 132 },
    { "timestamping", no_argument, NULL, 'N' },
    { "verbose", no_argument, NULL, 'v' },
    { "version", no_argument, NULL, 'V' },

    /* Options accepting an argument: */
    { "accept", required_argument, NULL, 'A' },
    { "append-output", required_argument, NULL, 'a' },
    { "backups", required_argument, NULL, 151 }, /* undocumented */
    { "base", required_argument, NULL, 'B' },
    { "bind-address", required_argument, NULL, 155 },
    { "cache", required_argument, NULL, 'C' },
    { "cookies", required_argument, NULL, 160 },
    { "cut-dirs", required_argument, NULL, 145 },
    { "directory-prefix", required_argument, NULL, 'P' },
    { "domains", required_argument, NULL, 'D' },
    { "dot-style", required_argument, NULL, 134 },
    { "execute", required_argument, NULL, 'e' },
    { "exclude-directories", required_argument, NULL, 'X' },
    { "exclude-domains", required_argument, NULL, 140 },
    { "follow-tags", required_argument, NULL, 153 },
    { "glob", required_argument, NULL, 'g' },
    { "header", required_argument, NULL, 131 },
    { "htmlify", required_argument, NULL, 135 },
    { "http-passwd", required_argument, NULL, 130 },
    { "http-user", required_argument, NULL, 129 },
    { "ignore-tags", required_argument, NULL, 'G' },
    { "include-directories", required_argument, NULL, 'I' },
    { "input-file", required_argument, NULL, 'i' },
    { "level", required_argument, NULL, 'l' },
    { "load-cookies", required_argument, NULL, 161 },
    { "no", required_argument, NULL, 'n' },
    { "output-document", required_argument, NULL, 'O' },
    { "output-file", required_argument, NULL, 'o' },
    { "proxy", required_argument, NULL, 'Y' },
    { "proxy-passwd", required_argument, NULL, 144 },
    { "proxy-user", required_argument, NULL, 143 },
    { "quota", required_argument, NULL, 'Q' },
    { "reject", required_argument, NULL, 'R' },
    { "save-cookies", required_argument, NULL, 162 },
    { "timeout", required_argument, NULL, 'T' },
    { "tries", required_argument, NULL, 't' },
    { "user-agent", required_argument, NULL, 'U' },
    { "referer", required_argument, NULL, 157 },
    { "use-proxy", required_argument, NULL, 'Y' },
#ifdef HAVE_SSL
    { "sslcertfile", required_argument, NULL, 158 },
    { "sslcertkey", required_argument, NULL, 159 },
#endif /* HAVE_SSL */
    { "wait", required_argument, NULL, 'w' },
    { "waitretry", required_argument, NULL, 152 },
    { 0, 0, 0, 0 }
  };

  i18n_initialize ();
  private_initialize ();

  append_to_log = 0;

  /* Construct the name of the executable, without the directory part.  */
  exec_name = strrchr (argv[0], PATH_SEPARATOR);
  if (!exec_name)
    exec_name = argv[0];
  else
    ++exec_name;

#ifdef WINDOWS
  windows_main_junk (&argc, (char **) argv, (char **) &exec_name);
#endif

  initialize (); /* sets option defaults; reads the system wgetrc and .wgetrc */

  /* [Is the order of the option letters significant?  If not, they should be
      alphabetized, like the long_options.  The only thing I know for sure is
      that the options with required arguments must be followed by a ':'.
      -- Dan Harkless <wget@harkless.org>] */
  while ((c = getopt_long (argc, argv, "\
hpVqvdkKsxmNWrHSLcFbEY:G:g:T:U:O:l:n:i:o:a:t:D:A:R:P:B:e:Q:X:I:w:C:",
			   long_options, (int *)0)) != EOF)
    {
      switch (c)
	{
	  /* Options without arguments: */
	case 132:
	  setval ("spider", "on");
	  break;
	case 133:
	  setval ("noparent", "on");
	  break;
	case 136:
	  setval ("deleteafter", "on");
	  break;
	case 137:
	  setval ("retrsymlinks", "on");
	  break;
	case 138:
	  setval ("ignorelength", "on");
	  break;
	case 139:
	  setval ("passiveftp", "on");
	  break;
	case 141:
	  setval ("noclobber", "on");
	  break;
	case 142:
	  setval ("followftp", "on");
	  break;
	case 145:
	  setval ("cutdirs", optarg);
	  break;
	case 146:
	  setval ("verbose", "off");
	  break;
	case 147:
	  setval ("dirstruct", "off");
	  break;
	case 148:
	  setval ("addhostdir", "off");
	  break;
	case 149:
	  setval ("removelisting", "off");
	  break;
	case 150:
	  setval ("simplehostcheck", "on");
	  break;
	case 155:
	  setval ("bindaddress", optarg);
 	  break;
	case 156:
	  setval ("httpkeepalive", "off");
	  break;
	case 'b':
	  setval ("background", "on");
	  break;
	case 'c':
	  setval ("continue", "on");
	  break;
	case 'd':
#ifdef DEBUG
	  setval ("debug", "on");
#else  /* not DEBUG */
	  fprintf (stderr, _("%s: debug support not compiled in.\n"),
		   exec_name);
#endif /* not DEBUG */
	  break;
	case 'E':
	  setval ("htmlextension", "on");
	  break;
	case 'F':
	  setval ("forcehtml", "on");
	  break;
	case 'H':
	  setval ("spanhosts", "on");
	  break;
	case 'h':
	  print_help ();
#ifdef WINDOWS
	  ws_help (exec_name);
#endif
	  exit (0);
	  break;
	case 'K':
	  setval ("backupconverted", "on");
	  break;
	case 'k':
	  setval ("convertlinks", "on");
	  break;
	case 'L':
	  setval ("relativeonly", "on");
	  break;
	case 'm':
	  setval ("mirror", "on");
	  break;
	case 'N':
	  setval ("timestamping", "on");
	  break;
	case 'p':
	  setval ("pagerequisites", "on");
	  break;
	case 'S':
	  setval ("serverresponse", "on");
	  break;
	case 's':
	  setval ("saveheaders", "on");
	  break;
	case 'q':
	  setval ("quiet", "on");
	  break;
	case 'r':
	  setval ("recursive", "on");
	  break;
	case 'V':
	  printf ("GNU Wget %s\n\n", version_string);
	  printf ("%s", _("\
Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n"));
	  printf (_("\nOriginally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"));
	  exit (0);
	  break;
	case 'v':
	  setval ("verbose", "on");
	  break;
	case 'x':
	  setval ("dirstruct", "on");
	  break;

	  /* Options accepting an argument: */
	case 129:
	  setval ("httpuser", optarg);
	  break;
	case 130:
	  setval ("httppasswd", optarg);
	  break;
	case 131:
	  setval ("header", optarg);
	  break;
	case 134:
	  setval ("dotstyle", optarg);
	  break;
	case 135:
	  setval ("htmlify", optarg);
	  break;
	case 140:
	  setval ("excludedomains", optarg);
	  break;
	case 143:
	  setval ("proxyuser", optarg);
	  break;
	case 144:
	  setval ("proxypasswd", optarg);
	  break;
	case 151:
	  setval ("backups", optarg);
	  break;
	case 152:
	  setval ("waitretry", optarg);
	  wr = 1;
	  break;
	case 153:
	  setval ("followtags", optarg);
	  break;
	case 160:
	  setval ("cookies", optarg);
	  break;
	case 161:
	  setval ("loadcookies", optarg);
	  break;
	case 162:
	  setval ("savecookies", optarg);
	  break;
	case 157:
	  setval ("referer", optarg);
	  break;
#ifdef HAVE_SSL
	case 158:
	  setval ("sslcertfile", optarg);
	  break;
	case 159:
	  setval ("sslcertkey", optarg);
	  break;
#endif /* HAVE_SSL */
	case 'A':
	  setval ("accept", optarg);
	  break;
	case 'a':
	  setval ("logfile", optarg);
	  append_to_log = 1;
	  break;
	case 'B':
	  setval ("base", optarg);
	  break;
	case 'C':
	  setval ("cache", optarg);
	  break;
	case 'D':
	  setval ("domains", optarg);
	  break;
	case 'e':
	  {
	    char *com, *val;
	    if (parse_line (optarg, &com, &val))
	      {
		if (!setval (com, val))
		  exit (1);
	      }
	    else
	      {
		fprintf (stderr, _("%s: %s: invalid command\n"), exec_name,
			 optarg);
		exit (1);
	      }
	    xfree (com);
	    xfree (val);
	  }
	  break;
	case 'G':
	  setval ("ignoretags", optarg);
	  break;
	case 'g':
	  setval ("glob", optarg);
	  break;
	case 'I':
	  setval ("includedirectories", optarg);
	  break;
	case 'i':
	  setval ("input", optarg);
	  break;
	case 'l':
	  setval ("reclevel", optarg);
	  break;
	case 'n':
	  {
	    /* #### The n? options are utter crock!  */
	    char *p;

	    for (p = optarg; *p; p++)
	      switch (*p)
		{
		case 'v':
		  setval ("verbose", "off");
		  break;
		case 'h':
		  setval ("simplehostcheck", "on");
		  break;
		case 'H':
		  setval ("addhostdir", "off");
		  break;
		case 'd':
		  setval ("dirstruct", "off");
		  break;
		case 'c':
		  setval ("noclobber", "on");
		  break;
		case 'r':
		  setval ("removelisting", "off");
		  break;
		case 'p':
		  setval ("noparent", "on");
		  break;
		case 'k':
		  setval ("httpkeepalive", "off");
		  break;
		default:
		  printf (_("%s: illegal option -- `-n%c'\n"), exec_name, *p);
		  print_usage ();
		  printf ("\n");
		  printf (_("Try `%s --help\' for more options.\n"), exec_name);
		  exit (1);
		}
	    break;
	  }
	case 'O':
	  setval ("outputdocument", optarg);
	  break;
	case 'o':
	  setval ("logfile", optarg);
	  break;
	case 'P':
	  setval ("dirprefix", optarg);
	  break;
	case 'Q':
	  setval ("quota", optarg);
	  break;
	case 'R':
	  setval ("reject", optarg);
	  break;
	case 'T':
	  setval ("timeout", optarg);
	  break;
	case 't':
	  setval ("tries", optarg);
	  break;
	case 'U':
	  setval ("useragent", optarg);
	  break;
	case 'w':
	  setval ("wait", optarg);
	  break;
	case 'X':
	  setval ("excludedirectories", optarg);
	  break;
	case 'Y':
	  setval ("useproxy", optarg);
	  break;

	case '?':
	  print_usage ();
	  printf ("\n");
	  printf (_("Try `%s --help' for more options.\n"), exec_name);
	  exit (0);
	  break;
	}
    }

  /* All user options have now been processed, so it's now safe to do
     interoption dependency checks. */

  if (opt.reclevel == 0)
    opt.reclevel = INFINITE_RECURSION;  /* see wget.h for commentary on this */

  if (opt.page_requisites && !opt.recursive)
    {
      opt.recursive = TRUE;
      opt.reclevel = 0;
      if (!opt.no_dirstruct)
	opt.dirstruct = TRUE;  /* usually handled by cmd_spec_recursive() */
    }

  if (opt.verbose == -1)
    opt.verbose = !opt.quiet;

  /* Retain compatibility with previous scripts.
     if wait has been set, but waitretry has not, give it the wait value.
     A simple check on the values is not enough, I could have set
     wait to n>0 and waitretry to 0 - HEH */
  if (opt.wait && !wr)
    {
      char  opt_wait_str[256];  /* bigger than needed buf to prevent overflow */

      sprintf(opt_wait_str, "%ld", opt.wait);
      setval ("waitretry", opt_wait_str);
    }
    
  /* Sanity checks.  */
  if (opt.verbose && opt.quiet)
    {
      printf (_("Can't be verbose and quiet at the same time.\n"));
      print_usage ();
      exit (1);
    }
  if (opt.timestamping && opt.noclobber)
    {
      printf (_("\
Can't timestamp and not clobber old files at the same time.\n"));
      print_usage ();
      exit (1);
    }
  nurl = argc - optind;
  if (!nurl && !opt.input_filename)
    {
      /* No URL specified.  */
      printf (_("%s: missing URL\n"), exec_name);
      print_usage ();
      printf ("\n");
      /* #### Something nicer should be printed here -- similar to the
	 pre-1.5 `--help' page.  */
      printf (_("Try `%s --help' for more options.\n"), exec_name);
      exit (1);
    }

  if (opt.background)
    fork_to_background ();

  /* Allocate basic pointer.  */
  url = ALLOCA_ARRAY (char *, nurl + 1);
  /* Fill in the arguments.  */
  for (i = 0; i < nurl; i++, optind++)
    {
      char *irix4_cc_needs_this;
      STRDUP_ALLOCA (irix4_cc_needs_this, argv[optind]);
      url[i] = irix4_cc_needs_this;
    }
  url[i] = NULL;

  /* Change the title of console window on Windows.  #### I think this
     statement should belong to retrieve_url().  --hniksic.  */
#ifdef WINDOWS
  ws_changetitle (*url, nurl);
#endif

  /* Initialize logging.  */
  log_init (opt.lfilename, append_to_log);

  DEBUGP (("DEBUG output created by Wget %s on %s.\n\n", version_string,
	   OS_TYPE));

  /* Open the output filename if necessary.  */
  if (opt.output_document)
    {
      if (HYPHENP (opt.output_document))
	opt.dfp = stdout;
      else
	{
	  struct stat st;
	  opt.dfp = fopen (opt.output_document, opt.always_rest ? "ab" : "wb");
	  if (opt.dfp == NULL)
	    {
	      perror (opt.output_document);
	      exit (1);
	    }
	  if (fstat (fileno (opt.dfp), &st) == 0 && S_ISREG (st.st_mode))
	    opt.od_known_regular = 1;
	}
    }

#ifdef WINDOWS
  ws_startup ();
#endif

  /* Setup the signal handler to redirect output when hangup is
     received.  */
#ifdef HAVE_SIGNAL
  if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
    signal(SIGHUP, redirect_output_signal);
  /* ...and do the same for SIGUSR1.  */
  signal (SIGUSR1, redirect_output_signal);
  /* Writing to a closed socket normally signals SIGPIPE, and the
     process exits.  What we want is to ignore SIGPIPE and just check
     for the return value of write().  */
  signal (SIGPIPE, SIG_IGN);
#endif /* HAVE_SIGNAL */

  status = RETROK;		/* initialize it, just-in-case */
  recursive_reset ();
  /* Retrieve the URLs from argument list.  */
  for (t = url; *t; t++)
    {
      char *filename, *redirected_URL;
      int dt;

      status = retrieve_url (*t, &filename, &redirected_URL, NULL, &dt);
      if (opt.recursive && status == RETROK && (dt & TEXTHTML))
	status = recursive_retrieve (filename,
				     redirected_URL ? redirected_URL : *t);

      if (opt.delete_after && file_exists_p(filename))
	{
	  DEBUGP (("Removing file due to --delete-after in main():\n"));
	  logprintf (LOG_VERBOSE, _("Removing %s.\n"), filename);
	  if (unlink (filename))
	    logprintf (LOG_NOTQUIET, "unlink: %s\n", strerror (errno));
	}

      FREE_MAYBE (redirected_URL);
      FREE_MAYBE (filename);
    }

  /* And then from the input file, if any.  */
  if (opt.input_filename)
    {
      int count;
      status = retrieve_from_file (opt.input_filename, opt.force_html, &count);
      if (!count)
	logprintf (LOG_NOTQUIET, _("No URLs found in %s.\n"),
		   opt.input_filename);
    }
  /* Print the downloaded sum.  */
  if (opt.recursive
      || nurl > 1
      || (opt.input_filename && opt.downloaded != 0))
    {
      logprintf (LOG_NOTQUIET,
		 _("\nFINISHED --%s--\nDownloaded: %s bytes in %d files\n"),
		 time_str (NULL),
		 (opt.downloaded_overflow ?
		  "<overflow>" : legible_very_long (opt.downloaded)),
		 opt.numurls);
      /* Print quota warning, if exceeded.  */
      if (downloaded_exceeds_quota ())
	logprintf (LOG_NOTQUIET,
		   _("Download quota (%s bytes) EXCEEDED!\n"),
		   legible (opt.quota));
    }

  if (opt.cookies_output)
    save_cookies (opt.cookies_output);

  if (opt.convert_links && !opt.delete_after)
    {
      convert_all_links ();
    }
  log_close ();
  cleanup ();
#ifdef DEBUG_MALLOC
  print_malloc_debug_stats ();
#endif
  if (status == RETROK)
    return 0;
  else
    return 1;
}

/* Hangup signal handler.  When wget receives SIGHUP or SIGUSR1, it
   will proceed operation as usual, trying to write into a log file.
   If that is impossible, the output will be turned off.  */

#ifdef HAVE_SIGNAL
static RETSIGTYPE
redirect_output_signal (int sig)
{
  char tmp[100];
  signal (sig, redirect_output_signal);
  /* Please note that the double `%' in `%%s' is intentional, because
     redirect_output passes tmp through printf.  */
  sprintf (tmp, _("%s received, redirecting output to `%%s'.\n"),
	   (sig == SIGHUP ? "SIGHUP" :
	    (sig == SIGUSR1 ? "SIGUSR1" :
	     "WTF?!")));
  redirect_output (tmp);
}
#endif /* HAVE_SIGNAL */
