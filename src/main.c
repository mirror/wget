/* Command line parsing.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001, 2002
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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

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
#ifndef errno
extern int errno;
#endif

#include "wget.h"
#include "utils.h"
#include "init.h"
#include "retr.h"
#include "recur.h"
#include "host.h"
#include "cookies.h"
#include "url.h"
#include "progress.h"		/* for progress_handle_sigwinch */
#include "convert.h"

#ifdef HAVE_SSL
# include "gen_sslfunc.h"
#endif

/* On GNU system this will include system-wide getopt.h. */
#include "getopt.h"

#ifndef PATH_SEPARATOR
# define PATH_SEPARATOR '/'
#endif

struct options opt;

extern LARGE_INT total_downloaded_bytes;
extern char *version_string;

extern struct cookie_jar *wget_cookie_jar;

/* From log.c.  */
void log_init PARAMS ((const char *, int));
void log_close PARAMS ((void));
void log_request_redirect_output PARAMS ((const char *));

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
\n"),stdout);
  fputs (_("\
Download:\n\
  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n\
       --retry-connrefused      retry even if connection is refused.\n\
  -O   --output-document=FILE   write documents to FILE.\n\
  -nc, --no-clobber             don\'t clobber existing files or use .# suffixes.\n\
  -c,  --continue               resume getting a partially-downloaded file.\n\
       --progress=TYPE          select progress gauge type.\n\
  -N,  --timestamping           don\'t re-retrieve files unless newer than local.\n\
  -S,  --server-response        print server response.\n\
       --spider                 don\'t download anything.\n\
  -T,  --timeout=SECONDS        set all timeout values to SECONDS.\n\
       --dns-timeout=SECS       set the DNS lookup timeout to SECS.\n\
       --connect-timeout=SECS   set the connect timeout to SECS.\n\
       --read-timeout=SECS      set the read timeout to SECS.\n\
  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n\
       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n\
       --random-wait            wait from 0...2*WAIT secs between retrievals.\n\
  -Y,  --proxy=on/off           turn proxy on or off.\n\
  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n\
       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n\
       --limit-rate=RATE        limit download rate to RATE.\n\
       --dns-cache=off          disable caching DNS lookups.\n\
       --restrict-file-names=OS restrict chars in file names to ones OS allows.\n\
\n"), stdout);
  fputs (_("\
Directories:\n\
  -nd, --no-directories            don\'t create directories.\n\
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
       --post-data=STRING    use the POST method; send STRING as the data.\n\
       --post-file=FILE      use the POST method; send contents of FILE.\n\
\n"), stdout);
#ifdef HAVE_SSL
  fputs (_("\
HTTPS (SSL) options:\n\
       --sslcertfile=FILE     optional client certificate.\n\
       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n\
       --egd-file=FILE        file name of the EGD socket.\n\
       --sslcadir=DIR         dir where hash list of CA's are stored.\n\
       --sslcafile=FILE       file with bundle of CA's\n\
       --sslcerttype=0/1      Client-Cert type 0=PEM (default) / 1=ASN1 (DER)\n\
       --sslcheckcert=0/1     Check the server cert agenst given CA\n\
       --sslprotocol=0-3      choose SSL protocol; 0=automatic,\n\
                              1=SSLv2 2=SSLv3 3=TLSv1\n\
\n"), stdout);
#endif
  fputs (_("\
FTP options:\n\
  -nr, --dont-remove-listing   don\'t remove `.listing\' files.\n\
  -g,  --glob=on/off           turn file name globbing on or off.\n\
       --passive-ftp           use the \"passive\" transfer mode.\n\
       --retr-symlinks         when recursing, get linked-to files (not dirs).\n\
\n"), stdout);
  fputs (_("\
Recursive retrieval:\n\
  -r,  --recursive          recursive download.\n\
  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n\
       --delete-after       delete files locally after downloading them.\n\
  -k,  --convert-links      convert non-relative links to relative.\n\
  -K,  --backup-converted   before converting file X, back up as X.orig.\n\
  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n\
  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n\
       --strict-comments    turn on strict (SGML) handling of HTML comments.\n\
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
    { "random-wait", no_argument, NULL, 165 },
    { "recursive", no_argument, NULL, 'r' },
    { "relative", no_argument, NULL, 'L' },
    { "retr-symlinks", no_argument, NULL, 137 },
    { "retry-connrefused", no_argument, NULL, 174 },
    { "save-headers", no_argument, NULL, 's' },
    { "server-response", no_argument, NULL, 'S' },
    { "span-hosts", no_argument, NULL, 'H' },
    { "spider", no_argument, NULL, 132 },
    { "strict-comments", no_argument, NULL, 177 },
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
    { "connect-timeout", required_argument, NULL, 180 },
    { "cookies", required_argument, NULL, 160 },
    { "cut-dirs", required_argument, NULL, 145 },
    { "dns-timeout", required_argument, NULL, 178 },
    { "directory-prefix", required_argument, NULL, 'P' },
    { "dns-cache", required_argument, NULL, 175 },
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
    { "limit-rate", required_argument, NULL, 164 },
    { "load-cookies", required_argument, NULL, 161 },
    { "no", required_argument, NULL, 'n' },
    { "output-document", required_argument, NULL, 'O' },
    { "output-file", required_argument, NULL, 'o' },
    { "post-data", required_argument, NULL, 167 },
    { "post-file", required_argument, NULL, 168 },
    { "progress", required_argument, NULL, 163 },
    { "proxy", required_argument, NULL, 'Y' },
    { "proxy-passwd", required_argument, NULL, 144 },
    { "proxy-user", required_argument, NULL, 143 },
    { "quota", required_argument, NULL, 'Q' },
    { "read-timeout", required_argument, NULL, 179 },
    { "reject", required_argument, NULL, 'R' },
    { "restrict-file-names", required_argument, NULL, 176 },
    { "save-cookies", required_argument, NULL, 162 },
    { "timeout", required_argument, NULL, 'T' },
    { "tries", required_argument, NULL, 't' },
    { "user-agent", required_argument, NULL, 'U' },
    { "referer", required_argument, NULL, 157 },
    { "use-proxy", required_argument, NULL, 'Y' },
#ifdef HAVE_SSL
    { "sslcertfile", required_argument, NULL, 158 },
    { "sslcertkey", required_argument, NULL, 159 },
    { "egd-file", required_argument, NULL, 166 },
    { "sslcadir",         required_argument, NULL, 169},
    { "sslcafile",        required_argument, NULL, 170},
    { "sslcerttype",      required_argument, NULL, 171},
    { "sslcheckcert",     required_argument, NULL, 172},
    { "sslprotocol",      required_argument, NULL, 173},
#endif /* HAVE_SSL */
    { "wait", required_argument, NULL, 'w' },
    { "waitretry", required_argument, NULL, 152 },
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
	  setoptval ("spider", "on");
	  break;
	case 133:
	  setoptval ("noparent", "on");
	  break;
	case 136:
	  setoptval ("deleteafter", "on");
	  break;
	case 137:
	  setoptval ("retrsymlinks", "on");
	  break;
	case 138:
	  setoptval ("ignorelength", "on");
	  break;
	case 139:
	  setoptval ("passiveftp", "on");
	  break;
	case 141:
	  setoptval ("noclobber", "on");
	  break;
	case 142:
	  setoptval ("followftp", "on");
	  break;
	case 145:
	  setoptval ("cutdirs", optarg);
	  break;
	case 146:
	  setoptval ("verbose", "off");
	  break;
	case 147:
	  setoptval ("dirstruct", "off");
	  break;
	case 148:
	  setoptval ("addhostdir", "off");
	  break;
	case 149:
	  setoptval ("removelisting", "off");
	  break;
	case 155:
	  setoptval ("bindaddress", optarg);
 	  break;
	case 156:
	  setoptval ("httpkeepalive", "off");
	  break;
	case 165:
	  setoptval ("randomwait", "on");
	  break;
	case 'b':
	  setoptval ("background", "on");
	  break;
	case 'c':
	  setoptval ("continue", "on");
	  break;
	case 'd':
#ifdef ENABLE_DEBUG
	  setoptval ("debug", "on");
#else
	  fprintf (stderr, _("%s: debug support not compiled in.\n"),
		   exec_name);
#endif
	  break;
	case 'E':
	  setoptval ("htmlextension", "on");
	  break;
	case 'F':
	  setoptval ("forcehtml", "on");
	  break;
	case 'H':
	  setoptval ("spanhosts", "on");
	  break;
	case 'h':
	  print_help ();
#ifdef WINDOWS
	  ws_help (exec_name);
#endif
	  exit (0);
	  break;
	case 'K':
	  setoptval ("backupconverted", "on");
	  break;
	case 'k':
	  setoptval ("convertlinks", "on");
	  break;
	case 'L':
	  setoptval ("relativeonly", "on");
	  break;
	case 'm':
	  setoptval ("mirror", "on");
	  break;
	case 'N':
	  setoptval ("timestamping", "on");
	  break;
	case 'p':
	  setoptval ("pagerequisites", "on");
	  break;
	case 'S':
	  setoptval ("serverresponse", "on");
	  break;
	case 's':
	  setoptval ("saveheaders", "on");
	  break;
	case 'q':
	  setoptval ("quiet", "on");
	  break;
	case 'r':
	  setoptval ("recursive", "on");
	  break;
	case 'V':
	  printf ("GNU Wget %s\n\n", version_string);
	  printf ("%s", _("\
Copyright (C) 2003 Free Software Foundation, Inc.\n"));
	  printf ("%s", _("\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n"));
	  printf (_("\nOriginally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"));
	  exit (0);
	  break;
	case 'v':
	  setoptval ("verbose", "on");
	  break;
	case 'x':
	  setoptval ("dirstruct", "on");
	  break;
	case 174:
	  setoptval ("retryconnrefused", "on");
	  break;
	case 177:
	  setoptval ("strictcomments", "on");
	  break;

	  /* Options accepting an argument: */
	case 129:
	  setoptval ("httpuser", optarg);
	  break;
	case 130:
	  setoptval ("httppasswd", optarg);
	  break;
	case 131:
	  setoptval ("header", optarg);
	  break;
	case 134:
	  setoptval ("dotstyle", optarg);
	  break;
	case 135:
	  setoptval ("htmlify", optarg);
	  break;
	case 140:
	  setoptval ("excludedomains", optarg);
	  break;
	case 143:
	  setoptval ("proxyuser", optarg);
	  break;
	case 144:
	  setoptval ("proxypasswd", optarg);
	  break;
	case 151:
	  setoptval ("backups", optarg);
	  break;
	case 152:
	  setoptval ("waitretry", optarg);
	  break;
	case 153:
	  setoptval ("followtags", optarg);
	  break;
	case 160:
	  setoptval ("cookies", optarg);
	  break;
	case 161:
	  setoptval ("loadcookies", optarg);
	  break;
	case 162:
	  setoptval ("savecookies", optarg);
	  break;
	case 163:
	  setoptval ("progress", optarg);
	  break;
	case 164:
	  setoptval ("limitrate", optarg);
	  break;
	case 157:
	  setoptval ("referer", optarg);
	  break;
#ifdef HAVE_SSL
	case 158:
	  setoptval ("sslcertfile", optarg);
	  break;
	case 159:
	  setoptval ("sslcertkey", optarg);
	  break;
	case 166:
	  setoptval ("egdfile", optarg);
	  break;
	case 169:
	  setoptval ("sslcadir", optarg);
	  break;
	case 170:
	  setoptval ("sslcafile", optarg);
	  break;
	case 171:
	  setoptval ("sslcerttype", optarg);
	  break;
	case 172:
	  setoptval ("sslcheckcert", optarg);
	  break;
	case 173:
	  setoptval ("sslprotocol", optarg);
	  break;
#endif /* HAVE_SSL */
	case 167:
	  setoptval ("postdata", optarg);
	  break;
	case 168:
	  setoptval ("postfile", optarg);
	  break;
	case 175:
	  setoptval ("dnscache", optarg);
	  break;
	case 176:
	  setoptval ("restrictfilenames", optarg);
	  break;
	case 178:
	  setoptval ("dnstimeout", optarg);
	  break;
	case 179:
	  setoptval ("readtimeout", optarg);
	  break;
	case 180:
	  setoptval ("connecttimeout", optarg);
	  break;
	case 'A':
	  setoptval ("accept", optarg);
	  break;
	case 'a':
	  setoptval ("logfile", optarg);
	  append_to_log = 1;
	  break;
	case 'B':
	  setoptval ("base", optarg);
	  break;
	case 'C':
	  setoptval ("cache", optarg);
	  break;
	case 'D':
	  setoptval ("domains", optarg);
	  break;
	case 'e':
	  run_command (optarg);
	  break;
	case 'G':
	  setoptval ("ignoretags", optarg);
	  break;
	case 'g':
	  setoptval ("glob", optarg);
	  break;
	case 'I':
	  setoptval ("includedirectories", optarg);
	  break;
	case 'i':
	  setoptval ("input", optarg);
	  break;
	case 'l':
	  setoptval ("reclevel", optarg);
	  break;
	case 'n':
	  {
	    /* #### What we really want here is --no-foo. */
	    char *p;

	    for (p = optarg; *p; p++)
	      switch (*p)
		{
		case 'v':
		  setoptval ("verbose", "off");
		  break;
		case 'H':
		  setoptval ("addhostdir", "off");
		  break;
		case 'd':
		  setoptval ("dirstruct", "off");
		  break;
		case 'c':
		  setoptval ("noclobber", "on");
		  break;
		case 'r':
		  setoptval ("removelisting", "off");
		  break;
		case 'p':
		  setoptval ("noparent", "on");
		  break;
		case 'k':
		  setoptval ("httpkeepalive", "off");
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
	  setoptval ("outputdocument", optarg);
	  break;
	case 'o':
	  setoptval ("logfile", optarg);
	  break;
	case 'P':
	  setoptval ("dirprefix", optarg);
	  break;
	case 'Q':
	  setoptval ("quota", optarg);
	  break;
	case 'R':
	  setoptval ("reject", optarg);
	  break;
	case 'T':
	  setoptval ("timeout", optarg);
	  break;
	case 't':
	  setoptval ("tries", optarg);
	  break;
	case 'U':
	  setoptval ("useragent", optarg);
	  break;
	case 'w':
	  setoptval ("wait", optarg);
	  break;
	case 'X':
	  setoptval ("excludedirectories", optarg);
	  break;
	case 'Y':
	  setoptval ("useproxy", optarg);
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

  /* Initialize progress.  Have to do this after the options are
     processed so we know where the log file is.  */
  if (opt.verbose)
    set_progress_implementation (opt.progress_type);

  /* Fill in the arguments.  */
  url = alloca_array (char *, nurl + 1);
  for (i = 0; i < nurl; i++, optind++)
    {
      char *rewritten = rewrite_shorthand_url (argv[optind]);
      if (rewritten)
	url[i] = rewritten;
      else
	url[i] = xstrdup (argv[optind]);
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
#ifdef SIGWINCH
  signal (SIGWINCH, progress_handle_sigwinch);
#endif
#endif /* HAVE_SIGNAL */

#ifdef HAVE_SSL
  /* Must call this before resolving any URLs because it has the power
     to disable `https'.  */
  ssl_init_prng ();
#endif

  status = RETROK;		/* initialize it, just-in-case */
  /* Retrieve the URLs from argument list.  */
  for (t = url; *t; t++)
    {
      char *filename = NULL, *redirected_URL = NULL;
      int dt;

      if (opt.recursive && url_scheme (*t) != SCHEME_FTP)
	status = retrieve_tree (*t);
      else
	status = retrieve_url (*t, &filename, &redirected_URL, NULL, &dt);

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
      || (opt.input_filename && total_downloaded_bytes != 0))
    {
      logprintf (LOG_NOTQUIET,
		 _("\nFINISHED --%s--\nDownloaded: %s bytes in %d files\n"),
		 time_str (NULL), legible_large_int (total_downloaded_bytes),
		 opt.numurls);
      /* Print quota warning, if exceeded.  */
      if (opt.quota && total_downloaded_bytes > opt.quota)
	logprintf (LOG_NOTQUIET,
		   _("Download quota (%s bytes) EXCEEDED!\n"),
		   legible (opt.quota));
    }

  if (opt.cookies_output && wget_cookie_jar)
    cookie_jar_save (wget_cookie_jar, opt.cookies_output);

  if (opt.convert_links && !opt.delete_after)
    convert_all_links ();

  log_close ();
  for (i = 0; i < nurl; i++)
    xfree (url[i]);
  cleanup ();

#ifdef DEBUG_MALLOC
  print_malloc_debug_stats ();
#endif
  if (status == RETROK)
    return 0;
  else
    return 1;
}

#ifdef HAVE_SIGNAL
/* Hangup signal handler.  When wget receives SIGHUP or SIGUSR1, it
   will proceed operation as usual, trying to write into a log file.
   If that is impossible, the output will be turned off.

   #### It is unsafe to do call libc functions from a signal handler.
   What we should do is, set a global variable, and have the code in
   log.c pick it up.  */

static RETSIGTYPE
redirect_output_signal (int sig)
{
  char *signal_name = (sig == SIGHUP ? "SIGHUP" :
		       (sig == SIGUSR1 ? "SIGUSR1" :
			"WTF?!"));
  log_request_redirect_output (signal_name);
  progress_schedule_redirect ();
  signal (sig, redirect_output_signal);
}
#endif /* HAVE_SIGNAL */
