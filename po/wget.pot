# SOME DESCRIPTIVE TITLE.
# Copyright (C) YEAR Free Software Foundation, Inc.
# FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.
#
#, fuzzy
msgid ""
msgstr ""
"Project-Id-Version: PACKAGE VERSION\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE\n"
"Last-Translator: FULL NAME <EMAIL@ADDRESS>\n"
"Language-Team: LANGUAGE <LL@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=CHARSET\n"
"Content-Transfer-Encoding: ENCODING\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr ""

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr ""

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr ""

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr ""

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr ""

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr ""

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr ""

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr ""

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr ""

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr ""

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr ""

#: src/ftp.c:283
msgid "done.  "
msgstr ""

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr ""

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr ""

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr ""

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr ""

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr ""

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr ""

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr ""

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr ""

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr ""

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr ""

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr ""

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr ""

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr ""

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr ""

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr ""

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr ""

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr ""

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr ""

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr ""

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr ""

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr ""

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr ""

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr ""

#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr ""

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr ""

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr ""

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr ""

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr ""

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr ""

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr ""

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr ""

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr ""

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr ""

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr ""

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr ""

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr ""

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr ""

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr ""

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr ""

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr ""

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr ""

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr ""

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr ""

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr ""

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr ""

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr ""

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr ""

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""

#: src/host.c:539
msgid "Host not found"
msgstr ""

#: src/host.c:541
msgid "Unknown error"
msgstr ""

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr ""

#: src/html.c:463
msgid "time unknown       "
msgstr ""

#: src/html.c:467
msgid "File        "
msgstr ""

#: src/html.c:470
msgid "Directory   "
msgstr ""

#: src/html.c:473
msgid "Link        "
msgstr ""

#: src/html.c:476
msgid "Not sure    "
msgstr ""

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr ""

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr ""

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr ""

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr ""

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr ""

#: src/http.c:587
msgid "No data received"
msgstr ""

#: src/http.c:589
msgid "Malformed status line"
msgstr ""

#: src/http.c:594
msgid "(no description)"
msgstr ""

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr ""

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr ""

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr ""

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr ""

#: src/http.c:750
msgid " [following]"
msgstr ""

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr ""

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr ""

#: src/http.c:774
msgid "ignored"
msgstr ""

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr ""

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr ""

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr ""

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr ""

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr ""

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr ""

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr ""

#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr ""

#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr ""

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr ""

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr ""

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr ""

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr ""

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr ""

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr ""

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr ""

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr ""

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr ""

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr ""

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""

#: src/main.c:123
msgid ""
"Logging and input file:\n"
"  -o,  --output-file=FILE     log messages to FILE.\n"
"  -a,  --append-output=FILE   append messages to FILE.\n"
"  -d,  --debug                print debug output.\n"
"  -q,  --quiet                quiet (no output).\n"
"  -v,  --verbose              be verbose (this is the default).\n"
"  -nv, --non-verbose          turn off verboseness, without being quiet.\n"
"  -i,  --input-file=FILE      read URL-s from file.\n"
"  -F,  --force-html           treat input file as HTML.\n"
"\n"
msgstr ""

#: src/main.c:133
msgid ""
"Download:\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 "
"unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files.\n"
"  -c,  --continue               restart getting an existing file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't retrieve files if older than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""

#: src/main.c:147
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory "
"components.\n"
"\n"
msgstr ""

#: src/main.c:154
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally "
"allowed).\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"\n"
msgstr ""

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""

#: src/main.c:170
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive             recursive web-suck -- use with care!.\n"
"  -l,  --level=NUMBER          maximum recursion depth (0 to unlimit).\n"
"       --delete-after          delete downloaded files.\n"
"  -k,  --convert-links         convert non-relative links to relative.\n"
"  -m,  --mirror                turn on options suitable for mirroring.\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"\n"
msgstr ""

#: src/main.c:178
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                list of accepted extensions.\n"
"  -R,  --reject=LIST                list of rejected extensions.\n"
"  -D,  --domains=LIST               list of accepted domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected "
"domains.\n"
"  -L,  --relative                   follow relative links only.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr ""

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr ""

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr ""

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr ""

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr ""

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr ""

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr ""

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr ""

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr ""

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr ""

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr ""

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr ""

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr ""

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr ""

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr ""

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr ""

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr ""

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr ""

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr ""

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr ""

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr ""

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr ""

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr ""

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr ""

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr ""

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr ""

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr ""

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr ""

#: src/utils.c:206
msgid "Invalid port specification"
msgstr ""

#: src/utils.c:209
msgid "Invalid host name"
msgstr ""

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr ""
