/* Command line parsing.
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
#include <stdlib.h>
#include <ctype.h>
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

#define OPTIONS_DEFINED_HERE	/* for options.h */

#include "wget.h"
#include "utils.h"
#include "getopt.h"
#include "init.h"
#include "retr.h"
#include "recur.h"
#include "host.h"

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
  setlocale (LC_MESSAGES, "");
  /* Set the text message domain.  */
  bindtextdomain ("wget", LOCALEDIR);
  textdomain ("wget");
#endif /* HAVE_NLS */
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
  printf ("%s%s%s%s%s%s%s%s%s%s", _("\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n"), _("\
Startup:\n\
  -V,  --version           display the version of Wget and exit.\n\
  -h,  --help              print this help.\n\
  -b,  --background        go to background after startup.\n\
  -e,  --execute=COMMAND   execute a `.wgetrc\' command.\n\
\n"), _("\
Logging and input file:\n\
  -o,  --output-file=FILE     log messages to FILE.\n\
  -a,  --append-output=FILE   append messages to FILE.\n\
  -d,  --debug                print debug output.\n\
  -q,  --quiet                quiet (no output).\n\
  -v,  --verbose              be verbose (this is the default).\n\
  -nv, --non-verbose          turn off verboseness, without being quiet.\n\
  -i,  --input-file=FILE      read URL-s from file.\n\
  -F,  --force-html           treat input file as HTML.\n\
\n"), _("\
Download:\n\
  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n\
  -O   --output-document=FILE   write documents to FILE.\n\
  -nc, --no-clobber             don\'t clobber existing files.\n\
  -c,  --continue               restart getting an existing file.\n\
       --dot-style=STYLE        set retrieval display style.\n\
  -N,  --timestamping           don\'t retrieve files if older than local.\n\
  -S,  --server-response        print server response.\n\
       --spider                 don\'t download anything.\n\
  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n\
  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n\
  -Y,  --proxy=on/off           turn proxy on or off.\n\
  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n\
\n"),  _("\
Directories:\n\
  -nd  --no-directories            don\'t create directories.\n\
  -x,  --force-directories         force creation of directories.\n\
  -nH, --no-host-directories       don\'t create host directories.\n\
  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n\
       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n\
\n"), _("\
HTTP options:\n\
       --http-user=USER      set http user to USER.\n\
       --http-passwd=PASS    set http password to PASS.\n\
  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\n\
       --ignore-length       ignore `Content-Length\' header field.\n\
       --header=STRING       insert STRING among the headers.\n\
       --proxy-user=USER     set USER as proxy username.\n\
       --proxy-passwd=PASS   set PASS as proxy password.\n\
  -s,  --save-headers        save the HTTP headers to file.\n\
  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n\
\n"), _("\
FTP options:\n\
       --retr-symlinks   retrieve FTP symbolic links.\n\
  -g,  --glob=on/off     turn file name globbing on or off.\n\
       --passive-ftp     use the \"passive\" transfer mode.\n\
\n"), _("\
Recursive retrieval:\n\
  -r,  --recursive             recursive web-suck -- use with care!.\n\
  -l,  --level=NUMBER          maximum recursion depth (0 to unlimit).\n\
       --delete-after          delete downloaded files.\n\
  -k,  --convert-links         convert non-relative links to relative.\n\
  -m,  --mirror                turn on options suitable for mirroring.\n\
  -nr, --dont-remove-listing   don\'t remove `.listing\' files.\n\
\n"), _("\
Recursive accept/reject:\n\
  -A,  --accept=LIST                list of accepted extensions.\n\
  -R,  --reject=LIST                list of rejected extensions.\n\
  -D,  --domains=LIST               list of accepted domains.\n\
       --exclude-domains=LIST       comma-separated list of rejected domains.\n\
  -L,  --relative                   follow relative links only.\n\
       --follow-ftp                 follow FTP links from HTML documents.\n\
  -H,  --span-hosts                 go to foreign hosts when recursive.\n\
  -I,  --include-directories=LIST   list of allowed directories.\n\
  -X,  --exclude-directories=LIST   list of excluded directories.\n\
  -nh, --no-host-lookup             don\'t DNS-lookup hosts.\n\
  -np, --no-parent                  don\'t ascend to the parent directory.\n\
\n"), _("Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"));
}

int
main (int argc, char *const *argv)
{
  char **url, **t;
  int i, c, nurl, status, append_to_log;

  static struct option long_options[] =
  {
    { "background", no_argument, NULL, 'b' },
    { "continue", no_argument, NULL, 'c' },
    { "convert-links", no_argument, NULL, 'k' },
    { "debug", no_argument, NULL, 'd' },
    { "dont-remove-listing", no_argument, NULL, 21 },
    { "email-address", no_argument, NULL, 'E' }, /* undocumented (debug) */
    { "follow-ftp", no_argument, NULL, 14 },
    { "force-directories", no_argument, NULL, 'x' },
    { "force-hier", no_argument, NULL, 'x' }, /* obsolete */
    { "force-html", no_argument, NULL, 'F'},
    { "help", no_argument, NULL, 'h' },
    { "ignore-length", no_argument, NULL, 10 },
    { "mirror", no_argument, NULL, 'm' },
    { "no-clobber", no_argument, NULL, 13 },
    { "no-directories", no_argument, NULL, 19 },
    { "no-host-directories", no_argument, NULL, 20 },
    { "no-host-lookup", no_argument, NULL, 22 },
    { "no-parent", no_argument, NULL, 5 },
    { "non-verbose", no_argument, NULL, 18 },
    { "passive-ftp", no_argument, NULL, 11 },
    { "quiet", no_argument, NULL, 'q' },
    { "recursive", no_argument, NULL, 'r' },
    { "relative", no_argument, NULL, 'L' },
    { "retr-symlinks", no_argument, NULL, 9 },
    { "save-headers", no_argument, NULL, 's' },
    { "server-response", no_argument, NULL, 'S' },
    { "span-hosts", no_argument, NULL, 'H' },
    { "spider", no_argument, NULL, 4 },
    { "timestamping", no_argument, NULL, 'N' },
    { "verbose", no_argument, NULL, 'v' },
    { "version", no_argument, NULL, 'V' },

    { "accept", required_argument, NULL, 'A' },
    { "append-output", required_argument, NULL, 'a' },
    { "backups", required_argument, NULL, 23 }, /* undocumented */
    { "base", required_argument, NULL, 'B' },
    { "cache", required_argument, NULL, 'C' },
    { "cut-dirs", required_argument, NULL, 17 },
    { "delete-after", no_argument, NULL, 8 },
    { "directory-prefix", required_argument, NULL, 'P' },
    { "domains", required_argument, NULL, 'D' },
    { "dot-style", required_argument, NULL, 6 },
    { "execute", required_argument, NULL, 'e' },
    { "exclude-directories", required_argument, NULL, 'X' },
    { "exclude-domains", required_argument, NULL, 12 },
    { "glob", required_argument, NULL, 'g' },
    { "header", required_argument, NULL, 3 },
    { "htmlify", required_argument, NULL, 7 },
    { "http-passwd", required_argument, NULL, 2 },
    { "http-user", required_argument, NULL, 1 },
    { "include-directories", required_argument, NULL, 'I' },
    { "input-file", required_argument, NULL, 'i' },
    { "level", required_argument, NULL, 'l' },
    { "no", required_argument, NULL, 'n' },
    { "output-document", required_argument, NULL, 'O' },
    { "output-file", required_argument, NULL, 'o' },
    { "proxy", required_argument, NULL, 'Y' },
    { "proxy-passwd", required_argument, NULL, 16 },
    { "proxy-user", required_argument, NULL, 15 },
    { "quota", required_argument, NULL, 'Q' },
    { "reject", required_argument, NULL, 'R' },
    { "timeout", required_argument, NULL, 'T' },
    { "tries", required_argument, NULL, 't' },
    { "user-agent", required_argument, NULL, 'U' },
    { "use-proxy", required_argument, NULL, 'Y' },
    { "wait", required_argument, NULL, 'w' },
    { 0, 0, 0, 0 }
  };

  i18n_initialize ();

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

  initialize ();

  while ((c = getopt_long (argc, argv, "\
hVqvdksxmNWrHSLcFbEY:g:T:U:O:l:n:i:o:a:t:D:A:R:P:B:e:Q:X:I:w:",
			   long_options, (int *)0)) != EOF)
    {
      switch (c)
	{
	  /* Options without arguments: */
	case 4:
	  setval ("spider", "on");
	  break;
	case 5:
	  setval ("noparent", "on");
	  break;
	case 8:
	  setval ("deleteafter", "on");
	  break;
	case 9:
	  setval ("retrsymlinks", "on");
	  break;
	case 10:
	  setval ("ignorelength", "on");
	  break;
	case 11:
	  setval ("passiveftp", "on");
	  break;
	case 13:
	  setval ("noclobber", "on");
	  break;
	case 14:
	  setval ("followftp", "on");
	  break;
	case 17:
	  setval ("cutdirs", optarg);
	  break;
	case 18:
	  setval ("verbose", "off");
	  break;
	case 19:
	  setval ("dirstruct", "off");
	  break;
	case 20:
	  setval ("addhostdir", "off");
	  break;
	case 21:
	  setval ("removelisting", "off");
	  break;
	case 22:
	  setval ("simplehostcheck", "on");
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
	  /* For debugging purposes.  */
	  printf ("%s\n", ftp_getaddress ());
	  exit (0);
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
Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n"));
	  printf (_("\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"));
	  exit (0);
	  break;
	case 'v':
	  setval ("verbose", "on");
	  break;
	case 'x':
	  setval ("dirstruct", "on");
	  break;

	  /* Options accepting an argument: */
	case 1:
	  setval ("httpuser", optarg);
	  break;
	case 2:
	  setval ("httppasswd", optarg);
	  break;
	case 3:
	  setval ("header", optarg);
	  break;
	case 6:
	  setval ("dotstyle", optarg);
	  break;
	case 7:
	  setval ("htmlify", optarg);
	  break;
	case 12:
	  setval ("excludedomains", optarg);
	  break;
	case 15:
	  setval ("proxyuser", optarg);
	  break;
	case 16:
	  setval ("proxypasswd", optarg);
	  break;
	case 23:
	  setval ("backups", optarg);
	  break;
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
	    free (com);
	    free (val);
	  }
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
  if (opt.verbose == -1)
    opt.verbose = !opt.quiet;

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
	  opt.dfp = fopen (opt.output_document, "wb");
	  if (opt.dfp == NULL)
	    {
	      perror (opt.output_document);
	      exit (1);
	    }
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
      char *filename, *new_file;
      int dt;

      status = retrieve_url (*t, &filename, &new_file, NULL, &dt);
      if (opt.recursive && status == RETROK && (dt & TEXTHTML))
	status = recursive_retrieve (filename, new_file ? new_file : *t);
      FREE_MAYBE (new_file);
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
		 time_str (NULL), legible (opt.downloaded), opt.numurls);
      /* Print quota warning, if exceeded.  */
      if (opt.quota && opt.downloaded > opt.quota)
	logprintf (LOG_NOTQUIET,
		   _("Download quota (%s bytes) EXCEEDED!\n"),
		   legible (opt.quota));
    }
  if (opt.convert_links)
    {
      convert_all_links ();
    }
  log_close ();
  cleanup ();
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
