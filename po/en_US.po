# English translations for GNU wget package.
# Copyright (C) 2008 Free Software Foundation, Inc.
# This file is distributed under the same license as the GNU wget package.
# Automatically generated, 2008.
#
# All this catalog "translates" are quotation characters.
# The msgids must be ASCII and therefore cannot contain real quotation
# characters, only substitutes like grave accent (0x60), apostrophe (0x27)
# and double quote (0x22). These substitutes look strange; see
# http://www.cl.cam.ac.uk/~mgk25/ucs/quotes.html
#
# This catalog translates grave accent (0x60) and apostrophe (0x27) to
# left single quotation mark (U+2018) and right single quotation mark (U+2019).
# It also translates pairs of apostrophe (0x27) to
# left single quotation mark (U+2018) and right single quotation mark (U+2019)
# and pairs of quotation mark (0x22) to
# left double quotation mark (U+201C) and right double quotation mark (U+201D).
#
# When output to an UTF-8 terminal, the quotation characters appear perfectly.
# When output to an ISO-8859-1 terminal, the single quotation marks are
# transliterated to apostrophes (by iconv in glibc 2.2 or newer) or to
# grave/acute accent (by libiconv), and the double quotation marks are
# transliterated to 0x22.
# When output to an ASCII terminal, the single quotation marks are
# transliterated to apostrophes, and the double quotation marks are
# transliterated to 0x22.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.12-devel\n"
"Report-Msgid-Bugs-To: wget@sunsite.dk\n"
"POT-Creation-Date: 2008-01-24 23:27-0800\n"
"PO-Revision-Date: 2008-01-24 23:27-0800\n"
"Last-Translator: Automatically generated\n"
"Language-Team: none\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
"Plural-Forms: nplurals=2; plural=(n != 1);\n"

#: lib/getopt.c:530 lib/getopt.c:546
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: option ‘%s’ is ambiguous\n"

#: lib/getopt.c:579 lib/getopt.c:583
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: option ‘--%s’ doesn’t allow an argument\n"

#: lib/getopt.c:592 lib/getopt.c:597
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: option ‘%c%s’ doesn’t allow an argument\n"

#: lib/getopt.c:640 lib/getopt.c:659 lib/getopt.c:975 lib/getopt.c:994
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: option ‘%s’ requires an argument\n"

#: lib/getopt.c:697 lib/getopt.c:700
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: unrecognized option ‘--%s’\n"

#: lib/getopt.c:708 lib/getopt.c:711
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: unrecognized option ‘%c%s’\n"

#: lib/getopt.c:763 lib/getopt.c:766
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: illegal option -- %c\n"

#: lib/getopt.c:772 lib/getopt.c:775
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: invalid option -- %c\n"

#: lib/getopt.c:827 lib/getopt.c:843 lib/getopt.c:1047 lib/getopt.c:1065
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: option requires an argument -- %c\n"

#: lib/getopt.c:896 lib/getopt.c:912
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: option ‘-W %s’ is ambiguous\n"

#: lib/getopt.c:936 lib/getopt.c:954
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: option ‘-W %s’ doesn’t allow an argument\n"

#: src/connect.c:195
#, c-format
msgid "%s: unable to resolve bind address `%s'; disabling bind.\n"
msgstr "%s: unable to resolve bind address ‘%s’; disabling bind.\n"

#: src/connect.c:267
#, c-format
msgid "Connecting to %s|%s|:%d... "
msgstr "Connecting to %s|%s|:%d... "

#: src/connect.c:270
#, c-format
msgid "Connecting to %s:%d... "
msgstr "Connecting to %s:%d... "

#: src/connect.c:330
msgid "connected.\n"
msgstr "connected.\n"

#: src/connect.c:342 src/host.c:753 src/host.c:782
#, c-format
msgid "failed: %s.\n"
msgstr "failed: %s.\n"

#: src/connect.c:366 src/http.c:1629
#, c-format
msgid "%s: unable to resolve host address `%s'\n"
msgstr "%s: unable to resolve host address ‘%s’\n"

#: src/convert.c:169
#, c-format
msgid "Converted %d files in %s seconds.\n"
msgstr "Converted %d files in %s seconds.\n"

#: src/convert.c:196
#, c-format
msgid "Converting %s... "
msgstr "Converting %s... "

#: src/convert.c:209
msgid "nothing to do.\n"
msgstr "nothing to do.\n"

#: src/convert.c:217 src/convert.c:241
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Cannot convert links in %s: %s\n"

#: src/convert.c:232
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Unable to delete ‘%s’: %s\n"

#: src/convert.c:441
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Cannot back up %s as %s: %s\n"

#: src/cookies.c:443
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Syntax error in Set-Cookie: %s at position %d.\n"

#: src/cookies.c:685
#, c-format
msgid "Cookie coming from %s attempted to set domain to %s\n"
msgstr "Cookie coming from %s attempted to set domain to %s\n"

#: src/cookies.c:1132 src/cookies.c:1250
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Cannot open cookies file ‘%s’: %s\n"

#: src/cookies.c:1287
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Error writing to ‘%s’: %s\n"

#: src/cookies.c:1290
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Error closing ‘%s’: %s\n"

#: src/ftp-ls.c:836
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Unsupported listing type, trying Unix listing parser.\n"

#: src/ftp-ls.c:882 src/ftp-ls.c:884
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index of /%s on %s:%d"

#: src/ftp-ls.c:907
#, c-format
msgid "time unknown       "
msgstr "time unknown       "

#: src/ftp-ls.c:911
#, c-format
msgid "File        "
msgstr "File        "

#: src/ftp-ls.c:914
#, c-format
msgid "Directory   "
msgstr "Directory   "

#: src/ftp-ls.c:917
#, c-format
msgid "Link        "
msgstr "Link        "

#: src/ftp-ls.c:920
#, c-format
msgid "Not sure    "
msgstr "Not sure    "

#: src/ftp-ls.c:938
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#: src/ftp.c:214
#, c-format
msgid "Length: %s"
msgstr "Length: %s"

#: src/ftp.c:220 src/http.c:2174
#, c-format
msgid ", %s (%s) remaining"
msgstr ", %s (%s) remaining"

#: src/ftp.c:224 src/http.c:2178
#, c-format
msgid ", %s remaining"
msgstr ", %s remaining"

#: src/ftp.c:227
msgid " (unauthoritative)\n"
msgstr " (unauthoritative)\n"

#: src/ftp.c:303
#, c-format
msgid "Logging in as %s ... "
msgstr "Logging in as %s ... "

#: src/ftp.c:316 src/ftp.c:362 src/ftp.c:391 src/ftp.c:443 src/ftp.c:555
#: src/ftp.c:601 src/ftp.c:630 src/ftp.c:687 src/ftp.c:748 src/ftp.c:808
#: src/ftp.c:855
msgid "Error in server response, closing control connection.\n"
msgstr "Error in server response, closing control connection.\n"

#: src/ftp.c:323
msgid "Error in server greeting.\n"
msgstr "Error in server greeting.\n"

#: src/ftp.c:330 src/ftp.c:451 src/ftp.c:563 src/ftp.c:638 src/ftp.c:697
#: src/ftp.c:758 src/ftp.c:818 src/ftp.c:865
msgid "Write failed, closing control connection.\n"
msgstr "Write failed, closing control connection.\n"

#: src/ftp.c:336
msgid "The server refuses login.\n"
msgstr "The server refuses login.\n"

#: src/ftp.c:342
msgid "Login incorrect.\n"
msgstr "Login incorrect.\n"

#: src/ftp.c:348
msgid "Logged in!\n"
msgstr "Logged in!\n"

#: src/ftp.c:370
msgid "Server error, can't determine system type.\n"
msgstr "Server error, can’t determine system type.\n"

#: src/ftp.c:379 src/ftp.c:674 src/ftp.c:731 src/ftp.c:774
msgid "done.    "
msgstr "done.    "

#: src/ftp.c:431 src/ftp.c:580 src/ftp.c:613 src/ftp.c:838 src/ftp.c:884
msgid "done.\n"
msgstr "done.\n"

#: src/ftp.c:458
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Unknown type ‘%c’, closing control connection.\n"

#: src/ftp.c:470
msgid "done.  "
msgstr "done.  "

#: src/ftp.c:476
msgid "==> CWD not needed.\n"
msgstr "==> CWD not needed.\n"

#: src/ftp.c:569
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"No such directory ‘%s’.\n"
"\n"

#: src/ftp.c:584
msgid "==> CWD not required.\n"
msgstr "==> CWD not required.\n"

#: src/ftp.c:644
msgid "Cannot initiate PASV transfer.\n"
msgstr "Cannot initiate PASV transfer.\n"

#: src/ftp.c:648
msgid "Cannot parse PASV response.\n"
msgstr "Cannot parse PASV response.\n"

#: src/ftp.c:665
#, c-format
msgid "couldn't connect to %s port %d: %s\n"
msgstr "couldn’t connect to %s port %d: %s\n"

#: src/ftp.c:713
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind error (%s).\n"

#: src/ftp.c:719
msgid "Invalid PORT.\n"
msgstr "Invalid PORT.\n"

#: src/ftp.c:765
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST failed, starting from scratch.\n"

#: src/ftp.c:826
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"No such file ‘%s’.\n"
"\n"

#: src/ftp.c:873
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"No such file or directory ‘%s’.\n"
"\n"

#: src/ftp.c:935 src/http.c:2236
#, c-format
msgid "%s has sprung into existence.\n"
msgstr "%s has sprung into existence.\n"

#: src/ftp.c:987
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, closing control connection.\n"

#: src/ftp.c:996
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Data connection: %s; "

#: src/ftp.c:1011
msgid "Control connection closed.\n"
msgstr "Control connection closed.\n"

#: src/ftp.c:1029
msgid "Data transfer aborted.\n"
msgstr "Data transfer aborted.\n"

#: src/ftp.c:1097
#, c-format
msgid "File `%s' already there; not retrieving.\n"
msgstr "File ‘%s’ already there; not retrieving.\n"

#: src/ftp.c:1165 src/http.c:2394
#, c-format
msgid "(try:%2d)"
msgstr "(try:%2d)"

#: src/ftp.c:1235 src/http.c:2717
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s]\n"
"\n"
msgstr ""
"%s (%s) - ‘%s’ saved [%s]\n"
"\n"

#: src/ftp.c:1277 src/main.c:1006 src/recur.c:378 src/retr.c:860
#, c-format
msgid "Removing %s.\n"
msgstr "Removing %s.\n"

#: src/ftp.c:1319
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Using ‘%s’ as listing tmp file.\n"

#: src/ftp.c:1334
#, c-format
msgid "Removed `%s'.\n"
msgstr "Removed ‘%s’.\n"

#: src/ftp.c:1367
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Recursion depth %d exceeded max. depth %d.\n"

#: src/ftp.c:1437
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Remote file no newer than local file ‘%s’ -- not retrieving.\n"

#: src/ftp.c:1444
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr ""
"Remote file is newer than local file ‘%s’ -- retrieving.\n"
"\n"

#: src/ftp.c:1451
#, c-format
msgid ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"
msgstr ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"

#: src/ftp.c:1469
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Invalid name of the symlink, skipping.\n"

#: src/ftp.c:1486
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Already have correct symlink %s -> %s\n"
"\n"

#: src/ftp.c:1494
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creating symlink %s -> %s\n"

#: src/ftp.c:1504
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symlinks not supported, skipping symlink ‘%s’.\n"

#: src/ftp.c:1516
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Skipping directory ‘%s’.\n"

#: src/ftp.c:1525
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: unknown/unsupported file type.\n"

#: src/ftp.c:1552
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: corrupt time-stamp.\n"

#: src/ftp.c:1580
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Will not retrieve dirs since depth is %d (max %d).\n"

#: src/ftp.c:1630
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Not descending to ‘%s’ as it is excluded/not-included.\n"

#: src/ftp.c:1696 src/ftp.c:1710
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rejecting ‘%s’.\n"

#: src/ftp.c:1733
#, c-format
msgid "Error matching %s against %s: %s\n"
msgstr "Error matching %s against %s: %s\n"

#: src/ftp.c:1774
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "No matches on pattern ‘%s’.\n"

#: src/ftp.c:1840
#, c-format
msgid "Wrote HTML-ized index to `%s' [%s].\n"
msgstr "Wrote HTML-ized index to ‘%s’ [%s].\n"

#: src/ftp.c:1845
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Wrote HTML-ized index to ‘%s’.\n"

#: src/host.c:348
msgid "Unknown host"
msgstr "Unknown host"

#: src/host.c:352
msgid "Temporary failure in name resolution"
msgstr "Temporary failure in name resolution"

#: src/host.c:354
msgid "Unknown error"
msgstr "Unknown error"

#: src/host.c:715
#, c-format
msgid "Resolving %s... "
msgstr "Resolving %s... "

#: src/host.c:762
msgid "failed: No IPv4/IPv6 addresses for host.\n"
msgstr "failed: No IPv4/IPv6 addresses for host.\n"

#: src/host.c:785
msgid "failed: timed out.\n"
msgstr "failed: timed out.\n"

#: src/html-url.c:289
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Cannot resolve incomplete link %s.\n"

#: src/html-url.c:696
#, c-format
msgid "%s: Invalid URL %s: %s\n"
msgstr "%s: Invalid URL %s: %s\n"

#: src/http.c:368
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Failed writing HTTP request: %s.\n"

#: src/http.c:737
msgid "No headers, assuming HTTP/0.9"
msgstr "No headers, assuming HTTP/0.9"

#: src/http.c:1414
msgid "Disabling SSL due to encountered errors.\n"
msgstr "Disabling SSL due to encountered errors.\n"

#: src/http.c:1567
#, c-format
msgid "POST data file `%s' missing: %s\n"
msgstr "POST data file ‘%s’ missing: %s\n"

#: src/http.c:1616
#, c-format
msgid "Reusing existing connection to %s:%d.\n"
msgstr "Reusing existing connection to %s:%d.\n"

#: src/http.c:1684
#, c-format
msgid "Failed reading proxy response: %s\n"
msgstr "Failed reading proxy response: %s\n"

#: src/http.c:1704
#, c-format
msgid "Proxy tunneling failed: %s"
msgstr "Proxy tunneling failed: %s"

#: src/http.c:1749
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s request sent, awaiting response... "

#: src/http.c:1760
msgid "No data received.\n"
msgstr "No data received.\n"

#: src/http.c:1767
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Read error (%s) in headers.\n"

#: src/http.c:1813
#, c-format
msgid ""
"File `%s' already there; not retrieving.\n"
"\n"
msgstr ""
"File ‘%s’ already there; not retrieving.\n"
"\n"

#: src/http.c:1966
msgid "Unknown authentication scheme.\n"
msgstr "Unknown authentication scheme.\n"

#: src/http.c:1997
msgid "Authorization failed.\n"
msgstr "Authorization failed.\n"

#: src/http.c:2011
msgid "Malformed status line"
msgstr "Malformed status line"

#: src/http.c:2013
msgid "(no description)"
msgstr "(no description)"

#: src/http.c:2076
#, c-format
msgid "Location: %s%s\n"
msgstr "Location: %s%s\n"

#: src/http.c:2077 src/http.c:2184
msgid "unspecified"
msgstr "unspecified"

#: src/http.c:2078
msgid " [following]"
msgstr " [following]"

#: src/http.c:2134
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"

#: src/http.c:2164
msgid "Length: "
msgstr "Length: "

#: src/http.c:2184
msgid "ignored"
msgstr "ignored"

#: src/http.c:2255
#, c-format
msgid "Saving to: `%s'\n"
msgstr "Saving to: ‘%s’\n"

#: src/http.c:2336
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Warning: wildcards not supported in HTTP.\n"

#: src/http.c:2383
msgid "Spider mode enabled. Check if remote file exists.\n"
msgstr "Spider mode enabled. Check if remote file exists.\n"

#: src/http.c:2468
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Cannot write to ‘%s’ (%s).\n"

#: src/http.c:2477
msgid "Unable to establish SSL connection.\n"
msgstr "Unable to establish SSL connection.\n"

#: src/http.c:2485
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERROR: Redirection (%d) without location.\n"

#: src/http.c:2531
msgid "Remote file does not exist -- broken link!!!\n"
msgstr "Remote file does not exist -- broken link!!!\n"

#: src/http.c:2536
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERROR %d: %s.\n"

#: src/http.c:2552
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified header missing -- time-stamps turned off.\n"

#: src/http.c:2560
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified header invalid -- time-stamp ignored.\n"

#: src/http.c:2590
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"Server file no newer than local file ‘%s’ -- not retrieving.\n"
"\n"

#: src/http.c:2598
#, c-format
msgid "The sizes do not match (local %s) -- retrieving.\n"
msgstr "The sizes do not match (local %s) -- retrieving.\n"

#: src/http.c:2605
msgid "Remote file is newer, retrieving.\n"
msgstr "Remote file is newer, retrieving.\n"

#: src/http.c:2621
msgid ""
"Remote file exists and could contain links to other resources -- "
"retrieving.\n"
"\n"
msgstr ""
"Remote file exists and could contain links to other resources -- "
"retrieving.\n"
"\n"

#: src/http.c:2626
msgid ""
"Remote file exists but does not contain any link -- not retrieving.\n"
"\n"
msgstr ""
"Remote file exists but does not contain any link -- not retrieving.\n"
"\n"

#: src/http.c:2634
msgid ""
"Remote file exists but recursion is disabled -- not retrieving.\n"
"\n"
msgstr ""
"Remote file exists but recursion is disabled -- not retrieving.\n"
"\n"

#: src/http.c:2686
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s/%s]\n"
"\n"
msgstr ""
"%s (%s) - ‘%s’ saved [%s/%s]\n"
"\n"

#: src/http.c:2741
#, c-format
msgid "%s (%s) - Connection closed at byte %s. "
msgstr "%s (%s) - Connection closed at byte %s. "

#: src/http.c:2756
#, c-format
msgid "%s (%s) - Read error at byte %s (%s)."
msgstr "%s (%s) - Read error at byte %s (%s)."

#: src/http.c:2765
#, c-format
msgid "%s (%s) - Read error at byte %s/%s (%s). "
msgstr "%s (%s) - Read error at byte %s/%s (%s). "

#: src/init.c:387
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC points to %s, which doesn’t exist.\n"

#: src/init.c:450 src/netrc.c:265
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Cannot read %s (%s).\n"

#: src/init.c:468
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Error in %s at line %d.\n"

#: src/init.c:474
#, c-format
msgid "%s: Syntax error in %s at line %d.\n"
msgstr "%s: Syntax error in %s at line %d.\n"

#: src/init.c:479
#, c-format
msgid "%s: Unknown command `%s' in %s at line %d.\n"
msgstr "%s: Unknown command ‘%s’ in %s at line %d.\n"

#: src/init.c:524
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Warning: Both system and user wgetrc point to ‘%s’.\n"

#: src/init.c:677
#, c-format
msgid "%s: Invalid --execute command `%s'\n"
msgstr "%s: Invalid --execute command ‘%s’\n"

#: src/init.c:722
#, c-format
msgid "%s: %s: Invalid boolean `%s'; use `on' or `off'.\n"
msgstr "%s: %s: Invalid boolean ‘%s’; use ‘on’ or ‘off’.\n"

#: src/init.c:739
#, c-format
msgid "%s: %s: Invalid number `%s'.\n"
msgstr "%s: %s: Invalid number ‘%s’.\n"

#: src/init.c:970 src/init.c:989
#, c-format
msgid "%s: %s: Invalid byte value `%s'\n"
msgstr "%s: %s: Invalid byte value ‘%s’\n"

#: src/init.c:1014
#, c-format
msgid "%s: %s: Invalid time period `%s'\n"
msgstr "%s: %s: Invalid time period ‘%s’\n"

#: src/init.c:1068 src/init.c:1158 src/init.c:1261 src/init.c:1286
#, c-format
msgid "%s: %s: Invalid value `%s'.\n"
msgstr "%s: %s: Invalid value ‘%s’.\n"

#: src/init.c:1105
#, c-format
msgid "%s: %s: Invalid header `%s'.\n"
msgstr "%s: %s: Invalid header ‘%s’.\n"

#: src/init.c:1171
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Invalid progress type ‘%s’.\n"

#: src/init.c:1230
#, c-format
msgid ""
"%s: %s: Invalid restriction `%s', use [unix|windows],[lowercase|uppercase],"
"[nocontrol].\n"
msgstr ""
"%s: %s: Invalid restriction ‘%s’, use [unix|windows],[lowercase|uppercase],"
"[nocontrol].\n"

#: src/log.c:784
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""
"\n"
"%s received, redirecting output to ‘%s’.\n"

#: src/log.c:794
#, c-format
msgid ""
"\n"
"%s received.\n"
msgstr ""
"\n"
"%s received.\n"

#: src/log.c:795
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; disabling logging.\n"

#: src/main.c:357
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Usage: %s [OPTION]... [URL]...\n"

#: src/main.c:369
msgid ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"

#: src/main.c:371
msgid "Startup:\n"
msgstr "Startup:\n"

#: src/main.c:373
msgid "  -V,  --version           display the version of Wget and exit.\n"
msgstr "  -V,  --version           display the version of Wget and exit.\n"

#: src/main.c:375
msgid "  -h,  --help              print this help.\n"
msgstr "  -h,  --help              print this help.\n"

#: src/main.c:377
msgid "  -b,  --background        go to background after startup.\n"
msgstr "  -b,  --background        go to background after startup.\n"

#: src/main.c:379
msgid "  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
msgstr "  -e,  --execute=COMMAND   execute a ‘.wgetrc’-style command.\n"

#: src/main.c:383
msgid "Logging and input file:\n"
msgstr "Logging and input file:\n"

#: src/main.c:385
msgid "  -o,  --output-file=FILE    log messages to FILE.\n"
msgstr "  -o,  --output-file=FILE    log messages to FILE.\n"

#: src/main.c:387
msgid "  -a,  --append-output=FILE  append messages to FILE.\n"
msgstr "  -a,  --append-output=FILE  append messages to FILE.\n"

#: src/main.c:390
msgid "  -d,  --debug               print lots of debugging information.\n"
msgstr "  -d,  --debug               print lots of debugging information.\n"

#: src/main.c:394
msgid "       --wdebug              print Watt-32 debug output.\n"
msgstr "       --wdebug              print Watt-32 debug output.\n"

#: src/main.c:397
msgid "  -q,  --quiet               quiet (no output).\n"
msgstr "  -q,  --quiet               quiet (no output).\n"

#: src/main.c:399
msgid "  -v,  --verbose             be verbose (this is the default).\n"
msgstr "  -v,  --verbose             be verbose (this is the default).\n"

#: src/main.c:401
msgid ""
"  -nv, --no-verbose          turn off verboseness, without being quiet.\n"
msgstr ""
"  -nv, --no-verbose          turn off verboseness, without being quiet.\n"

#: src/main.c:403
msgid "  -i,  --input-file=FILE     download URLs found in FILE.\n"
msgstr "  -i,  --input-file=FILE     download URLs found in FILE.\n"

#: src/main.c:405
msgid "  -F,  --force-html          treat input file as HTML.\n"
msgstr "  -F,  --force-html          treat input file as HTML.\n"

#: src/main.c:407
msgid ""
"  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"
msgstr ""
"  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"

#: src/main.c:411
msgid "Download:\n"
msgstr "Download:\n"

#: src/main.c:413
msgid ""
"  -t,  --tries=NUMBER            set number of retries to NUMBER (0 "
"unlimits).\n"
msgstr ""
"  -t,  --tries=NUMBER            set number of retries to NUMBER (0 "
"unlimits).\n"

#: src/main.c:415
msgid "       --retry-connrefused       retry even if connection is refused.\n"
msgstr ""
"       --retry-connrefused       retry even if connection is refused.\n"

#: src/main.c:417
msgid "  -O,  --output-document=FILE    write documents to FILE.\n"
msgstr "  -O,  --output-document=FILE    write documents to FILE.\n"

#: src/main.c:419
msgid ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"
msgstr ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"

#: src/main.c:422
msgid ""
"  -c,  --continue                resume getting a partially-downloaded "
"file.\n"
msgstr ""
"  -c,  --continue                resume getting a partially-downloaded "
"file.\n"

#: src/main.c:424
msgid "       --progress=TYPE           select progress gauge type.\n"
msgstr "       --progress=TYPE           select progress gauge type.\n"

#: src/main.c:426
msgid ""
"  -N,  --timestamping            don't re-retrieve files unless newer than\n"
"                                 local.\n"
msgstr ""
"  -N,  --timestamping            don’t re-retrieve files unless newer than\n"
"                                 local.\n"

#: src/main.c:429
msgid "  -S,  --server-response         print server response.\n"
msgstr "  -S,  --server-response         print server response.\n"

#: src/main.c:431
msgid "       --spider                  don't download anything.\n"
msgstr "       --spider                  don’t download anything.\n"

#: src/main.c:433
msgid "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"
msgstr "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"

#: src/main.c:435
msgid "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"
msgstr "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"

#: src/main.c:437
msgid "       --connect-timeout=SECS    set the connect timeout to SECS.\n"
msgstr "       --connect-timeout=SECS    set the connect timeout to SECS.\n"

#: src/main.c:439
msgid "       --read-timeout=SECS       set the read timeout to SECS.\n"
msgstr "       --read-timeout=SECS       set the read timeout to SECS.\n"

#: src/main.c:441
msgid "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"
msgstr "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"

#: src/main.c:443
msgid ""
"       --waitretry=SECONDS       wait 1..SECONDS between retries of a "
"retrieval.\n"
msgstr ""
"       --waitretry=SECONDS       wait 1..SECONDS between retries of a "
"retrieval.\n"

#: src/main.c:445
msgid ""
"       --random-wait             wait from 0...2*WAIT secs between "
"retrievals.\n"
msgstr ""
"       --random-wait             wait from 0...2*WAIT secs between "
"retrievals.\n"

#: src/main.c:447
msgid "       --no-proxy                explicitly turn off proxy.\n"
msgstr "       --no-proxy                explicitly turn off proxy.\n"

#: src/main.c:449
msgid "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"
msgstr "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"

#: src/main.c:451
msgid ""
"       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local "
"host.\n"
msgstr ""
"       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local "
"host.\n"

#: src/main.c:453
msgid "       --limit-rate=RATE         limit download rate to RATE.\n"
msgstr "       --limit-rate=RATE         limit download rate to RATE.\n"

#: src/main.c:455
msgid "       --no-dns-cache            disable caching DNS lookups.\n"
msgstr "       --no-dns-cache            disable caching DNS lookups.\n"

#: src/main.c:457
msgid ""
"       --restrict-file-names=OS  restrict chars in file names to ones OS "
"allows.\n"
msgstr ""
"       --restrict-file-names=OS  restrict chars in file names to ones OS "
"allows.\n"

#: src/main.c:459
msgid ""
"       --ignore-case             ignore case when matching files/"
"directories.\n"
msgstr ""
"       --ignore-case             ignore case when matching files/"
"directories.\n"

#: src/main.c:462
msgid "  -4,  --inet4-only              connect only to IPv4 addresses.\n"
msgstr "  -4,  --inet4-only              connect only to IPv4 addresses.\n"

#: src/main.c:464
msgid "  -6,  --inet6-only              connect only to IPv6 addresses.\n"
msgstr "  -6,  --inet6-only              connect only to IPv6 addresses.\n"

#: src/main.c:466
msgid ""
"       --prefer-family=FAMILY    connect first to addresses of specified "
"family,\n"
"                                 one of IPv6, IPv4, or none.\n"
msgstr ""
"       --prefer-family=FAMILY    connect first to addresses of specified "
"family,\n"
"                                 one of IPv6, IPv4, or none.\n"

#: src/main.c:470
msgid "       --user=USER               set both ftp and http user to USER.\n"
msgstr "       --user=USER               set both ftp and http user to USER.\n"

#: src/main.c:472
msgid ""
"       --password=PASS           set both ftp and http password to PASS.\n"
msgstr ""
"       --password=PASS           set both ftp and http password to PASS.\n"

#: src/main.c:476
msgid "Directories:\n"
msgstr "Directories:\n"

#: src/main.c:478
msgid "  -nd, --no-directories           don't create directories.\n"
msgstr "  -nd, --no-directories           don’t create directories.\n"

#: src/main.c:480
msgid "  -x,  --force-directories        force creation of directories.\n"
msgstr "  -x,  --force-directories        force creation of directories.\n"

#: src/main.c:482
msgid "  -nH, --no-host-directories      don't create host directories.\n"
msgstr "  -nH, --no-host-directories      don’t create host directories.\n"

#: src/main.c:484
msgid "       --protocol-directories     use protocol name in directories.\n"
msgstr "       --protocol-directories     use protocol name in directories.\n"

#: src/main.c:486
msgid "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"
msgstr "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"

#: src/main.c:488
msgid ""
"       --cut-dirs=NUMBER          ignore NUMBER remote directory "
"components.\n"
msgstr ""
"       --cut-dirs=NUMBER          ignore NUMBER remote directory "
"components.\n"

#: src/main.c:492
msgid "HTTP options:\n"
msgstr "HTTP options:\n"

#: src/main.c:494
msgid "       --http-user=USER        set http user to USER.\n"
msgstr "       --http-user=USER        set http user to USER.\n"

#: src/main.c:496
msgid "       --http-password=PASS    set http password to PASS.\n"
msgstr "       --http-password=PASS    set http password to PASS.\n"

#: src/main.c:498
msgid "       --no-cache              disallow server-cached data.\n"
msgstr "       --no-cache              disallow server-cached data.\n"

#: src/main.c:500
msgid ""
"  -E,  --html-extension        save HTML documents with `.html' extension.\n"
msgstr ""
"  -E,  --html-extension        save HTML documents with ‘.html’ extension.\n"

#: src/main.c:502
msgid "       --ignore-length         ignore `Content-Length' header field.\n"
msgstr "       --ignore-length         ignore ‘Content-Length’ header field.\n"

#: src/main.c:504
msgid "       --header=STRING         insert STRING among the headers.\n"
msgstr "       --header=STRING         insert STRING among the headers.\n"

#: src/main.c:506
msgid "       --max-redirect          maximum redirections allowed per page.\n"
msgstr ""
"       --max-redirect          maximum redirections allowed per page.\n"

#: src/main.c:508
msgid "       --proxy-user=USER       set USER as proxy username.\n"
msgstr "       --proxy-user=USER       set USER as proxy username.\n"

#: src/main.c:510
msgid "       --proxy-password=PASS   set PASS as proxy password.\n"
msgstr "       --proxy-password=PASS   set PASS as proxy password.\n"

#: src/main.c:512
msgid ""
"       --referer=URL           include `Referer: URL' header in HTTP "
"request.\n"
msgstr ""
"       --referer=URL           include ‘Referer: URL’ header in HTTP "
"request.\n"

#: src/main.c:514
msgid "       --save-headers          save the HTTP headers to file.\n"
msgstr "       --save-headers          save the HTTP headers to file.\n"

#: src/main.c:516
msgid ""
"  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"
msgstr ""
"  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"

#: src/main.c:518
msgid ""
"       --no-http-keep-alive    disable HTTP keep-alive (persistent "
"connections).\n"
msgstr ""
"       --no-http-keep-alive    disable HTTP keep-alive (persistent "
"connections).\n"

#: src/main.c:520
msgid "       --no-cookies            don't use cookies.\n"
msgstr "       --no-cookies            don’t use cookies.\n"

#: src/main.c:522
msgid "       --load-cookies=FILE     load cookies from FILE before session.\n"
msgstr ""
"       --load-cookies=FILE     load cookies from FILE before session.\n"

#: src/main.c:524
msgid "       --save-cookies=FILE     save cookies to FILE after session.\n"
msgstr "       --save-cookies=FILE     save cookies to FILE after session.\n"

#: src/main.c:526
msgid ""
"       --keep-session-cookies  load and save session (non-permanent) "
"cookies.\n"
msgstr ""
"       --keep-session-cookies  load and save session (non-permanent) "
"cookies.\n"

#: src/main.c:528
msgid ""
"       --post-data=STRING      use the POST method; send STRING as the "
"data.\n"
msgstr ""
"       --post-data=STRING      use the POST method; send STRING as the "
"data.\n"

#: src/main.c:530
msgid ""
"       --post-file=FILE        use the POST method; send contents of FILE.\n"
msgstr ""
"       --post-file=FILE        use the POST method; send contents of FILE.\n"

#: src/main.c:532
msgid ""
"       --content-disposition   honor the Content-Disposition header when\n"
"                               choosing local file names (EXPERIMENTAL).\n"
msgstr ""
"       --content-disposition   honor the Content-Disposition header when\n"
"                               choosing local file names (EXPERIMENTAL).\n"

#: src/main.c:538
msgid "HTTPS (SSL/TLS) options:\n"
msgstr "HTTPS (SSL/TLS) options:\n"

#: src/main.c:540
msgid ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"
msgstr ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"

#: src/main.c:543
msgid ""
"       --no-check-certificate   don't validate the server's certificate.\n"
msgstr ""
"       --no-check-certificate   don’t validate the server’s certificate.\n"

#: src/main.c:545
msgid "       --certificate=FILE       client certificate file.\n"
msgstr "       --certificate=FILE       client certificate file.\n"

#: src/main.c:547
msgid "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"
msgstr "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"

#: src/main.c:549
msgid "       --private-key=FILE       private key file.\n"
msgstr "       --private-key=FILE       private key file.\n"

#: src/main.c:551
msgid "       --private-key-type=TYPE  private key type, PEM or DER.\n"
msgstr "       --private-key-type=TYPE  private key type, PEM or DER.\n"

#: src/main.c:553
msgid "       --ca-certificate=FILE    file with the bundle of CA's.\n"
msgstr "       --ca-certificate=FILE    file with the bundle of CA’s.\n"

#: src/main.c:555
msgid ""
"       --ca-directory=DIR       directory where hash list of CA's is "
"stored.\n"
msgstr ""
"       --ca-directory=DIR       directory where hash list of CA’s is "
"stored.\n"

#: src/main.c:557
msgid ""
"       --random-file=FILE       file with random data for seeding the SSL "
"PRNG.\n"
msgstr ""
"       --random-file=FILE       file with random data for seeding the SSL "
"PRNG.\n"

#: src/main.c:559
msgid ""
"       --egd-file=FILE          file naming the EGD socket with random "
"data.\n"
msgstr ""
"       --egd-file=FILE          file naming the EGD socket with random "
"data.\n"

#: src/main.c:564
msgid "FTP options:\n"
msgstr "FTP options:\n"

#: src/main.c:566
msgid "       --ftp-user=USER         set ftp user to USER.\n"
msgstr "       --ftp-user=USER         set ftp user to USER.\n"

#: src/main.c:568
msgid "       --ftp-password=PASS     set ftp password to PASS.\n"
msgstr "       --ftp-password=PASS     set ftp password to PASS.\n"

#: src/main.c:570
msgid "       --no-remove-listing     don't remove `.listing' files.\n"
msgstr "       --no-remove-listing     don’t remove ‘.listing’ files.\n"

#: src/main.c:572
msgid "       --no-glob               turn off FTP file name globbing.\n"
msgstr "       --no-glob               turn off FTP file name globbing.\n"

#: src/main.c:574
msgid "       --no-passive-ftp        disable the \"passive\" transfer mode.\n"
msgstr "       --no-passive-ftp        disable the “passive” transfer mode.\n"

#: src/main.c:576
msgid ""
"       --retr-symlinks         when recursing, get linked-to files (not "
"dir).\n"
msgstr ""
"       --retr-symlinks         when recursing, get linked-to files (not "
"dir).\n"

#: src/main.c:578
msgid "       --preserve-permissions  preserve remote file permissions.\n"
msgstr "       --preserve-permissions  preserve remote file permissions.\n"

#: src/main.c:582
msgid "Recursive download:\n"
msgstr "Recursive download:\n"

#: src/main.c:584
msgid "  -r,  --recursive          specify recursive download.\n"
msgstr "  -r,  --recursive          specify recursive download.\n"

#: src/main.c:586
msgid ""
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for "
"infinite).\n"
msgstr ""
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for "
"infinite).\n"

#: src/main.c:588
msgid ""
"       --delete-after       delete files locally after downloading them.\n"
msgstr ""
"       --delete-after       delete files locally after downloading them.\n"

#: src/main.c:590
msgid ""
"  -k,  --convert-links      make links in downloaded HTML point to local "
"files.\n"
msgstr ""
"  -k,  --convert-links      make links in downloaded HTML point to local "
"files.\n"

#: src/main.c:592
msgid ""
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
msgstr ""
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"

#: src/main.c:594
msgid ""
"  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"
msgstr ""
"  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"

#: src/main.c:596
msgid ""
"  -p,  --page-requisites    get all images, etc. needed to display HTML "
"page.\n"
msgstr ""
"  -p,  --page-requisites    get all images, etc. needed to display HTML "
"page.\n"

#: src/main.c:598
msgid ""
"       --strict-comments    turn on strict (SGML) handling of HTML "
"comments.\n"
msgstr ""
"       --strict-comments    turn on strict (SGML) handling of HTML "
"comments.\n"

#: src/main.c:602
msgid "Recursive accept/reject:\n"
msgstr "Recursive accept/reject:\n"

#: src/main.c:604
msgid ""
"  -A,  --accept=LIST               comma-separated list of accepted "
"extensions.\n"
msgstr ""
"  -A,  --accept=LIST               comma-separated list of accepted "
"extensions.\n"

#: src/main.c:606
msgid ""
"  -R,  --reject=LIST               comma-separated list of rejected "
"extensions.\n"
msgstr ""
"  -R,  --reject=LIST               comma-separated list of rejected "
"extensions.\n"

#: src/main.c:608
msgid ""
"  -D,  --domains=LIST              comma-separated list of accepted "
"domains.\n"
msgstr ""
"  -D,  --domains=LIST              comma-separated list of accepted "
"domains.\n"

#: src/main.c:610
msgid ""
"       --exclude-domains=LIST      comma-separated list of rejected "
"domains.\n"
msgstr ""
"       --exclude-domains=LIST      comma-separated list of rejected "
"domains.\n"

#: src/main.c:612
msgid ""
"       --follow-ftp                follow FTP links from HTML documents.\n"
msgstr ""
"       --follow-ftp                follow FTP links from HTML documents.\n"

#: src/main.c:614
msgid ""
"       --follow-tags=LIST          comma-separated list of followed HTML "
"tags.\n"
msgstr ""
"       --follow-tags=LIST          comma-separated list of followed HTML "
"tags.\n"

#: src/main.c:616
msgid ""
"       --ignore-tags=LIST          comma-separated list of ignored HTML "
"tags.\n"
msgstr ""
"       --ignore-tags=LIST          comma-separated list of ignored HTML "
"tags.\n"

#: src/main.c:618
msgid ""
"  -H,  --span-hosts                go to foreign hosts when recursive.\n"
msgstr ""
"  -H,  --span-hosts                go to foreign hosts when recursive.\n"

#: src/main.c:620
msgid "  -L,  --relative                  follow relative links only.\n"
msgstr "  -L,  --relative                  follow relative links only.\n"

#: src/main.c:622
msgid "  -I,  --include-directories=LIST  list of allowed directories.\n"
msgstr "  -I,  --include-directories=LIST  list of allowed directories.\n"

#: src/main.c:624
msgid "  -X,  --exclude-directories=LIST  list of excluded directories.\n"
msgstr "  -X,  --exclude-directories=LIST  list of excluded directories.\n"

#: src/main.c:626
msgid ""
"  -np, --no-parent                 don't ascend to the parent directory.\n"
msgstr ""
"  -np, --no-parent                 don’t ascend to the parent directory.\n"

#: src/main.c:630
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"

#: src/main.c:635
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, a non-interactive network retriever.\n"

#: src/main.c:675
msgid "Copyright (C) 2007 Free Software Foundation, Inc.\n"
msgstr "Copyright (C) 2007 Free Software Foundation, Inc.\n"

#: src/main.c:677
msgid ""
"License GPLv3+: GNU GPL version 3 or later\n"
"<http://www.gnu.org/licenses/gpl.html>.\n"
"This is free software: you are free to change and redistribute it.\n"
"There is NO WARRANTY, to the extent permitted by law.\n"
msgstr ""
"License GPLv3+: GNU GPL version 3 or later\n"
"<http://www.gnu.org/licenses/gpl.html>.\n"
"This is free software: you are free to change and redistribute it.\n"
"There is NO WARRANTY, to the extent permitted by law.\n"

#: src/main.c:682
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Originally written by Hrvoje Nikšić <hniksic@xemacs.org>.\n"

#: src/main.c:684
msgid "Currently maintained by Micah Cowan <micah@cowan.name>.\n"
msgstr "Currently maintained by Micah Cowan <micah@cowan.name>.\n"

#: src/main.c:731 src/main.c:800 src/main.c:900
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Try ‘%s --help’ for more options.\n"

#: src/main.c:797
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: illegal option -- ‘-n%c’\n"

#: src/main.c:855
#, c-format
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Can’t be verbose and quiet at the same time.\n"

#: src/main.c:861
#, c-format
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Can’t timestamp and not clobber old files at the same time.\n"

#: src/main.c:869
#, c-format
msgid "Cannot specify both --inet4-only and --inet6-only.\n"
msgstr "Cannot specify both --inet4-only and --inet6-only.\n"

#: src/main.c:879
#, c-format
msgid "Cannot specify -r, -p or -N if -O is given.\n"
msgstr "Cannot specify -r, -p or -N if -O is given.\n"

#: src/main.c:887
#, c-format
msgid "Cannot specify both -k and -O if multiple URLs are given.\n"
msgstr "Cannot specify both -k and -O if multiple URLs are given.\n"

#: src/main.c:895
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: missing URL\n"

#: src/main.c:1021
#, c-format
msgid "No URLs found in %s.\n"
msgstr "No URLs found in %s.\n"

#: src/main.c:1039
#, c-format
msgid ""
"FINISHED --%s--\n"
"Downloaded: %d files, %s in %s (%s)\n"
msgstr ""
"FINISHED --%s--\n"
"Downloaded: %d files, %s in %s (%s)\n"

#: src/main.c:1048
#, c-format
msgid "Download quota of %s EXCEEDED!\n"
msgstr "Download quota of %s EXCEEDED!\n"

#: src/mswindows.c:99
#, c-format
msgid "Continuing in background.\n"
msgstr "Continuing in background.\n"

#: src/mswindows.c:292
#, c-format
msgid "Continuing in background, pid %lu.\n"
msgstr "Continuing in background, pid %lu.\n"

#: src/mswindows.c:294 src/utils.c:330
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Output will be written to ‘%s’.\n"

#: src/mswindows.c:462 src/mswindows.c:469
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Couldn’t find usable socket driver.\n"

#: src/netrc.c:373
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: warning: “%s” token appears before any machine name\n"

#: src/netrc.c:404
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: unknown token “%s”\n"

#: src/netrc.c:468
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Usage: %s NETRC [HOSTNAME]\n"

#: src/netrc.c:478
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: cannot stat %s: %s\n"

#: src/openssl.c:113
msgid "WARNING: using a weak random seed.\n"
msgstr "WARNING: using a weak random seed.\n"

#: src/openssl.c:173
msgid "Could not seed PRNG; consider using --random-file.\n"
msgstr "Could not seed PRNG; consider using --random-file.\n"

#: src/openssl.c:488
msgid "ERROR"
msgstr "ERROR"

#: src/openssl.c:488
msgid "WARNING"
msgstr "WARNING"

#: src/openssl.c:497
#, c-format
msgid "%s: No certificate presented by %s.\n"
msgstr "%s: No certificate presented by %s.\n"

#: src/openssl.c:518
#, c-format
msgid "%s: cannot verify %s's certificate, issued by `%s':\n"
msgstr "%s: cannot verify %s’s certificate, issued by ‘%s’:\n"

#: src/openssl.c:526
msgid "  Unable to locally verify the issuer's authority.\n"
msgstr "  Unable to locally verify the issuer’s authority.\n"

#: src/openssl.c:530
msgid "  Self-signed certificate encountered.\n"
msgstr "  Self-signed certificate encountered.\n"

#: src/openssl.c:533
msgid "  Issued certificate not yet valid.\n"
msgstr "  Issued certificate not yet valid.\n"

#: src/openssl.c:536
msgid "  Issued certificate has expired.\n"
msgstr "  Issued certificate has expired.\n"

#: src/openssl.c:568
#, c-format
msgid ""
"%s: certificate common name `%s' doesn't match requested host name `%s'.\n"
msgstr ""
"%s: certificate common name ‘%s’ doesn’t match requested host name ‘%s’.\n"

#: src/openssl.c:581
#, c-format
msgid "To connect to %s insecurely, use `--no-check-certificate'.\n"
msgstr "To connect to %s insecurely, use ‘--no-check-certificate’.\n"

#: src/progress.c:239
#, c-format
msgid ""
"\n"
"%*s[ skipping %sK ]"
msgstr ""
"\n"
"%*s[ skipping %sK ]"

#: src/progress.c:453
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Invalid dot style specification ‘%s’; leaving unchanged.\n"

#: src/progress.c:947
#, c-format
msgid "  eta %s"
msgstr "  eta %s"

#: src/progress.c:962
msgid "   in "
msgstr "   in "

#: src/ptimer.c:160
#, c-format
msgid "Cannot get REALTIME clock frequency: %s\n"
msgstr "Cannot get REALTIME clock frequency: %s\n"

#: src/recur.c:379
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Removing %s since it should be rejected.\n"

#: src/res.c:390
#, c-format
msgid "Cannot open %s: %s"
msgstr "Cannot open %s: %s"

#: src/res.c:542
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Loading robots.txt; please ignore errors.\n"

#: src/retr.c:652
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Error parsing proxy URL %s: %s.\n"

#: src/retr.c:660
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Error in proxy URL %s: Must be HTTP.\n"

#: src/retr.c:746
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d redirections exceeded.\n"

#: src/retr.c:881
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Giving up.\n"
"\n"

#: src/retr.c:881
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Retrying.\n"
"\n"

#: src/spider.c:74
msgid ""
"Found no broken links.\n"
"\n"
msgstr ""
"Found no broken links.\n"
"\n"

#: src/spider.c:81
#, c-format
msgid ""
"Found %d broken link.\n"
"\n"
msgid_plural ""
"Found %d broken links.\n"
"\n"
msgstr[0] ""
"Found %d broken link.\n"
"\n"
msgstr[1] ""
"Found %d broken links.\n"
"\n"

#: src/spider.c:91
#, c-format
msgid "%s\n"
msgstr "%s\n"

#: src/url.c:620
msgid "No error"
msgstr "No error"

#: src/url.c:622
msgid "Unsupported scheme"
msgstr "Unsupported scheme"

#: src/url.c:624
msgid "Invalid host name"
msgstr "Invalid host name"

#: src/url.c:626
msgid "Bad port number"
msgstr "Bad port number"

#: src/url.c:628
msgid "Invalid user name"
msgstr "Invalid user name"

#: src/url.c:630
msgid "Unterminated IPv6 numeric address"
msgstr "Unterminated IPv6 numeric address"

#: src/url.c:632
msgid "IPv6 addresses not supported"
msgstr "IPv6 addresses not supported"

#: src/url.c:634
msgid "Invalid IPv6 numeric address"
msgstr "Invalid IPv6 numeric address"

#: src/utils.c:328
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Continuing in background, pid %d.\n"

#: src/utils.c:376
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Failed to unlink symlink ‘%s’: %s\n"

#: src/xmalloc.c:63
#, c-format
msgid "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"
msgstr "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"
