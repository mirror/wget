# English translations for GNU wget package.
# Copyright (C) 2009 Free Software Foundation, Inc.
# This file is distributed under the same license as the GNU wget package.
# Automatically generated, 2009.
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
# This catalog furthermore displays the text between the quotation marks in
# bold face, assuming the VT100/XTerm escape sequences.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.12-devel\n"
"Report-Msgid-Bugs-To: wget@sunsite.dk\n"
"POT-Creation-Date: 2009-07-05 10:12-0700\n"
"PO-Revision-Date: 2009-07-05 10:12-0700\n"
"Last-Translator: Automatically generated\n"
"Language-Team: none\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
"Plural-Forms: nplurals=2; plural=(n != 1);\n"

#: lib/error.c:125
msgid "Unknown system error"
msgstr "Unknown system error"

#: lib/getopt.c:526 lib/getopt.c:542
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: option ‘[1m%s[0m’ is ambiguous\n"

#: lib/getopt.c:575 lib/getopt.c:579
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: option ‘[1m--%s[0m’ doesn’t allow an argument\n"

#: lib/getopt.c:588 lib/getopt.c:593
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: option ‘[1m%c%s[0m’ doesn’t allow an argument\n"

#: lib/getopt.c:636 lib/getopt.c:655 lib/getopt.c:971 lib/getopt.c:990
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: option ‘[1m%s[0m’ requires an argument\n"

#: lib/getopt.c:693 lib/getopt.c:696
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: unrecognized option ‘[1m--%s[0m’\n"

#: lib/getopt.c:704 lib/getopt.c:707
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: unrecognized option ‘[1m%c%s[0m’\n"

#: lib/getopt.c:759 lib/getopt.c:762
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: illegal option -- %c\n"

#: lib/getopt.c:768 lib/getopt.c:771
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: invalid option -- %c\n"

#: lib/getopt.c:823 lib/getopt.c:839 lib/getopt.c:1043 lib/getopt.c:1061
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: option requires an argument -- %c\n"

#: lib/getopt.c:892 lib/getopt.c:908
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: option ‘[1m-W %s[0m’ is ambiguous\n"

#: lib/getopt.c:932 lib/getopt.c:950
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: option ‘[1m-W %s[0m’ doesn’t allow an argument\n"

#. TRANSLATORS:
#. Get translations for open and closing quotation marks.
#.
#. The message catalog should translate "`" to a left
#. quotation mark suitable for the locale, and similarly for
#. "'".  If the catalog has no translation,
#. locale_quoting_style quotes `like this', and
#. clocale_quoting_style quotes "like this".
#.
#. For example, an American English Unicode locale should
#. translate "`" to U+201C (LEFT DOUBLE QUOTATION MARK), and
#. should translate "'" to U+201D (RIGHT DOUBLE QUOTATION
#. MARK).  A British English Unicode locale should instead
#. translate these to U+2018 (LEFT SINGLE QUOTATION MARK) and
#. U+2019 (RIGHT SINGLE QUOTATION MARK), respectively.
#.
#. If you don't know what to put here, please see
#. <http://en.wikipedia.org/wiki/Quotation_mark#Glyphs>
#. and use glyphs suitable for your language.
#: lib/quotearg.c:249
msgid "`"
msgstr "“[1m[1m"

#: lib/quotearg.c:250
msgid "'"
msgstr "[0m”[0m"

#: lib/xalloc-die.c:34
msgid "memory exhausted"
msgstr "memory exhausted"

#: src/connect.c:207
#, c-format
msgid "%s: unable to resolve bind address %s; disabling bind.\n"
msgstr "%s: unable to resolve bind address %s; disabling bind.\n"

#: src/connect.c:291
#, c-format
msgid "Connecting to %s|%s|:%d... "
msgstr "Connecting to %s|%s|:%d... "

#: src/connect.c:298
#, c-format
msgid "Connecting to %s:%d... "
msgstr "Connecting to %s:%d... "

#: src/connect.c:358
msgid "connected.\n"
msgstr "connected.\n"

#: src/connect.c:370 src/host.c:780 src/host.c:809
#, c-format
msgid "failed: %s.\n"
msgstr "failed: %s.\n"

#: src/connect.c:394 src/http.c:1674
#, c-format
msgid "%s: unable to resolve host address %s\n"
msgstr "%s: unable to resolve host address %s\n"

#: src/convert.c:185
#, c-format
msgid "Converted %d files in %s seconds.\n"
msgstr "Converted %d files in %s seconds.\n"

#: src/convert.c:213
#, c-format
msgid "Converting %s... "
msgstr "Converting %s... "

#: src/convert.c:226
msgid "nothing to do.\n"
msgstr "nothing to do.\n"

#: src/convert.c:234 src/convert.c:258
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Cannot convert links in %s: %s\n"

#: src/convert.c:249
#, c-format
msgid "Unable to delete %s: %s\n"
msgstr "Unable to delete %s: %s\n"

#: src/convert.c:464
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Cannot back up %s as %s: %s\n"

#: src/cookies.c:443
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Syntax error in Set-Cookie: %s at position %d.\n"

#: src/cookies.c:686
#, c-format
msgid "Cookie coming from %s attempted to set domain to %s\n"
msgstr "Cookie coming from %s attempted to set domain to %s\n"

#: src/cookies.c:1134 src/cookies.c:1252
#, c-format
msgid "Cannot open cookies file %s: %s\n"
msgstr "Cannot open cookies file %s: %s\n"

#: src/cookies.c:1289
#, c-format
msgid "Error writing to %s: %s\n"
msgstr "Error writing to %s: %s\n"

#: src/cookies.c:1292
#, c-format
msgid "Error closing %s: %s\n"
msgstr "Error closing %s: %s\n"

#: src/ftp-ls.c:1065
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Unsupported listing type, trying Unix listing parser.\n"

#: src/ftp-ls.c:1116 src/ftp-ls.c:1118
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index of /%s on %s:%d"

#: src/ftp-ls.c:1143
#, c-format
msgid "time unknown       "
msgstr "time unknown       "

#: src/ftp-ls.c:1147
#, c-format
msgid "File        "
msgstr "File        "

#: src/ftp-ls.c:1150
#, c-format
msgid "Directory   "
msgstr "Directory   "

#: src/ftp-ls.c:1153
#, c-format
msgid "Link        "
msgstr "Link        "

#: src/ftp-ls.c:1156
#, c-format
msgid "Not sure    "
msgstr "Not sure    "

#: src/ftp-ls.c:1179
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#: src/ftp.c:220
#, c-format
msgid "Length: %s"
msgstr "Length: %s"

#: src/ftp.c:226 src/http.c:2248
#, c-format
msgid ", %s (%s) remaining"
msgstr ", %s (%s) remaining"

#: src/ftp.c:230 src/http.c:2252
#, c-format
msgid ", %s remaining"
msgstr ", %s remaining"

#: src/ftp.c:233
msgid " (unauthoritative)\n"
msgstr " (unauthoritative)\n"

#: src/ftp.c:311
#, c-format
msgid "Logging in as %s ... "
msgstr "Logging in as %s ... "

#: src/ftp.c:325 src/ftp.c:371 src/ftp.c:400 src/ftp.c:465 src/ftp.c:695
#: src/ftp.c:748 src/ftp.c:777 src/ftp.c:834 src/ftp.c:895 src/ftp.c:987
#: src/ftp.c:1034
msgid "Error in server response, closing control connection.\n"
msgstr "Error in server response, closing control connection.\n"

#: src/ftp.c:332
msgid "Error in server greeting.\n"
msgstr "Error in server greeting.\n"

#: src/ftp.c:339 src/ftp.c:473 src/ftp.c:703 src/ftp.c:785 src/ftp.c:844
#: src/ftp.c:905 src/ftp.c:997 src/ftp.c:1044
msgid "Write failed, closing control connection.\n"
msgstr "Write failed, closing control connection.\n"

#: src/ftp.c:345
msgid "The server refuses login.\n"
msgstr "The server refuses login.\n"

#: src/ftp.c:351
msgid "Login incorrect.\n"
msgstr "Login incorrect.\n"

#: src/ftp.c:357
msgid "Logged in!\n"
msgstr "Logged in!\n"

#: src/ftp.c:379
msgid "Server error, can't determine system type.\n"
msgstr "Server error, can’t determine system type.\n"

#: src/ftp.c:388 src/ftp.c:821 src/ftp.c:878 src/ftp.c:921
msgid "done.    "
msgstr "done.    "

#: src/ftp.c:453 src/ftp.c:720 src/ftp.c:760 src/ftp.c:1017 src/ftp.c:1063
msgid "done.\n"
msgstr "done.\n"

#: src/ftp.c:480
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Unknown type ‘[1m%c[0m’, closing control connection.\n"

#: src/ftp.c:492
msgid "done.  "
msgstr "done.  "

#: src/ftp.c:498
msgid "==> CWD not needed.\n"
msgstr "==> CWD not needed.\n"

#: src/ftp.c:709
#, c-format
msgid ""
"No such directory %s.\n"
"\n"
msgstr ""
"No such directory %s.\n"
"\n"

#: src/ftp.c:730
msgid "==> CWD not required.\n"
msgstr "==> CWD not required.\n"

#: src/ftp.c:791
msgid "Cannot initiate PASV transfer.\n"
msgstr "Cannot initiate PASV transfer.\n"

#: src/ftp.c:795
msgid "Cannot parse PASV response.\n"
msgstr "Cannot parse PASV response.\n"

#: src/ftp.c:812
#, c-format
msgid "couldn't connect to %s port %d: %s\n"
msgstr "couldn’t connect to %s port %d: %s\n"

#: src/ftp.c:860
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind error (%s).\n"

#: src/ftp.c:866
msgid "Invalid PORT.\n"
msgstr "Invalid PORT.\n"

#: src/ftp.c:912
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST failed, starting from scratch.\n"

#: src/ftp.c:953
#, c-format
msgid "File %s exists.\n"
msgstr "File %s exists.\n"

#: src/ftp.c:959
#, c-format
msgid "No such file %s.\n"
msgstr "No such file %s.\n"

#: src/ftp.c:1005
#, c-format
msgid ""
"No such file %s.\n"
"\n"
msgstr ""
"No such file %s.\n"
"\n"

#: src/ftp.c:1052
#, c-format
msgid ""
"No such file or directory %s.\n"
"\n"
msgstr ""
"No such file or directory %s.\n"
"\n"

#: src/ftp.c:1183 src/http.c:2339
#, c-format
msgid "%s has sprung into existence.\n"
msgstr "%s has sprung into existence.\n"

#: src/ftp.c:1235
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, closing control connection.\n"

#: src/ftp.c:1244
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Data connection: %s; "

#: src/ftp.c:1259
msgid "Control connection closed.\n"
msgstr "Control connection closed.\n"

#: src/ftp.c:1277
msgid "Data transfer aborted.\n"
msgstr "Data transfer aborted.\n"

#: src/ftp.c:1377
#, c-format
msgid "File %s already there; not retrieving.\n"
msgstr "File %s already there; not retrieving.\n"

#: src/ftp.c:1443 src/http.c:2524
#, c-format
msgid "(try:%2d)"
msgstr "(try:%2d)"

#: src/ftp.c:1518 src/http.c:2868
#, c-format
msgid ""
"%s (%s) - written to stdout %s[%s]\n"
"\n"
msgstr ""
"%s (%s) - written to stdout %s[%s]\n"
"\n"

#: src/ftp.c:1519 src/http.c:2869
#, c-format
msgid ""
"%s (%s) - %s saved [%s]\n"
"\n"
msgstr ""
"%s (%s) - %s saved [%s]\n"
"\n"

#: src/ftp.c:1564 src/main.c:1292 src/recur.c:438 src/retr.c:982
#, c-format
msgid "Removing %s.\n"
msgstr "Removing %s.\n"

#: src/ftp.c:1606
#, c-format
msgid "Using %s as listing tmp file.\n"
msgstr "Using %s as listing tmp file.\n"

#: src/ftp.c:1623
#, c-format
msgid "Removed %s.\n"
msgstr "Removed %s.\n"

#: src/ftp.c:1660
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Recursion depth %d exceeded max. depth %d.\n"

#: src/ftp.c:1730
#, c-format
msgid "Remote file no newer than local file %s -- not retrieving.\n"
msgstr "Remote file no newer than local file %s -- not retrieving.\n"

#: src/ftp.c:1737
#, c-format
msgid ""
"Remote file is newer than local file %s -- retrieving.\n"
"\n"
msgstr ""
"Remote file is newer than local file %s -- retrieving.\n"
"\n"

#: src/ftp.c:1744
#, c-format
msgid ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"
msgstr ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"

#: src/ftp.c:1762
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Invalid name of the symlink, skipping.\n"

#: src/ftp.c:1779
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Already have correct symlink %s -> %s\n"
"\n"

#: src/ftp.c:1788
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creating symlink %s -> %s\n"

#: src/ftp.c:1798
#, c-format
msgid "Symlinks not supported, skipping symlink %s.\n"
msgstr "Symlinks not supported, skipping symlink %s.\n"

#: src/ftp.c:1810
#, c-format
msgid "Skipping directory %s.\n"
msgstr "Skipping directory %s.\n"

#: src/ftp.c:1819
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: unknown/unsupported file type.\n"

#: src/ftp.c:1856
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: corrupt time-stamp.\n"

#: src/ftp.c:1878
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Will not retrieve dirs since depth is %d (max %d).\n"

#: src/ftp.c:1928
#, c-format
msgid "Not descending to %s as it is excluded/not-included.\n"
msgstr "Not descending to %s as it is excluded/not-included.\n"

#: src/ftp.c:1994 src/ftp.c:2008
#, c-format
msgid "Rejecting %s.\n"
msgstr "Rejecting %s.\n"

#: src/ftp.c:2031
#, c-format
msgid "Error matching %s against %s: %s\n"
msgstr "Error matching %s against %s: %s\n"

#: src/ftp.c:2073
#, c-format
msgid "No matches on pattern %s.\n"
msgstr "No matches on pattern %s.\n"

#: src/ftp.c:2144
#, c-format
msgid "Wrote HTML-ized index to %s [%s].\n"
msgstr "Wrote HTML-ized index to %s [%s].\n"

#: src/ftp.c:2149
#, c-format
msgid "Wrote HTML-ized index to %s.\n"
msgstr "Wrote HTML-ized index to %s.\n"

#: src/gnutls.c:219 src/openssl.c:495
msgid "ERROR"
msgstr "ERROR"

#: src/gnutls.c:219 src/openssl.c:495
msgid "WARNING"
msgstr "WARNING"

#: src/gnutls.c:225 src/openssl.c:504
#, c-format
msgid "%s: No certificate presented by %s.\n"
msgstr "%s: No certificate presented by %s.\n"

#: src/gnutls.c:233
#, c-format
msgid "%s: The certificate of %s is not trusted.\n"
msgstr "%s: The certificate of %s is not trusted.\n"

#: src/gnutls.c:239
#, c-format
msgid "%s: The certificate of %s hasn't got a known issuer.\n"
msgstr "%s: The certificate of %s hasn’t got a known issuer.\n"

#: src/gnutls.c:245
#, c-format
msgid "%s: The certificate of %s has been revoked.\n"
msgstr "%s: The certificate of %s has been revoked.\n"

#: src/gnutls.c:259
#, c-format
msgid "Error initializing X509 certificate: %s\n"
msgstr "Error initializing X509 certificate: %s\n"

#: src/gnutls.c:268
msgid "No certificate found\n"
msgstr "No certificate found\n"

#: src/gnutls.c:275
#, c-format
msgid "Error parsing certificate: %s\n"
msgstr "Error parsing certificate: %s\n"

#: src/gnutls.c:282
msgid "The certificate has not yet been activated\n"
msgstr "The certificate has not yet been activated\n"

#: src/gnutls.c:287
msgid "The certificate has expired\n"
msgstr "The certificate has expired\n"

#: src/gnutls.c:293
#, c-format
msgid "The certificate's owner does not match hostname '%s'\n"
msgstr "The certificate’s owner does not match hostname ‘[1m%s[0m’\n"

#: src/host.c:358
msgid "Unknown host"
msgstr "Unknown host"

#: src/host.c:362
msgid "Temporary failure in name resolution"
msgstr "Temporary failure in name resolution"

#: src/host.c:364
msgid "Unknown error"
msgstr "Unknown error"

#: src/host.c:737
#, c-format
msgid "Resolving %s... "
msgstr "Resolving %s... "

#: src/host.c:789
msgid "failed: No IPv4/IPv6 addresses for host.\n"
msgstr "failed: No IPv4/IPv6 addresses for host.\n"

#: src/host.c:812
msgid "failed: timed out.\n"
msgstr "failed: timed out.\n"

#: src/html-url.c:286
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Cannot resolve incomplete link %s.\n"

#: src/html-url.c:762
#, c-format
msgid "%s: Invalid URL %s: %s\n"
msgstr "%s: Invalid URL %s: %s\n"

#: src/http.c:377
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Failed writing HTTP request: %s.\n"

#: src/http.c:754
msgid "No headers, assuming HTTP/0.9"
msgstr "No headers, assuming HTTP/0.9"

#: src/http.c:1456
msgid "Disabling SSL due to encountered errors.\n"
msgstr "Disabling SSL due to encountered errors.\n"

#: src/http.c:1576
#, c-format
msgid "POST data file %s missing: %s\n"
msgstr "POST data file %s missing: %s\n"

#: src/http.c:1660
#, c-format
msgid "Reusing existing connection to %s:%d.\n"
msgstr "Reusing existing connection to %s:%d.\n"

#: src/http.c:1729
#, c-format
msgid "Failed reading proxy response: %s\n"
msgstr "Failed reading proxy response: %s\n"

#: src/http.c:1750
#, c-format
msgid "Proxy tunneling failed: %s"
msgstr "Proxy tunneling failed: %s"

#: src/http.c:1795
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s request sent, awaiting response... "

#: src/http.c:1806
msgid "No data received.\n"
msgstr "No data received.\n"

#: src/http.c:1813
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Read error (%s) in headers.\n"

#: src/http.c:1884
msgid "Unknown authentication scheme.\n"
msgstr "Unknown authentication scheme.\n"

#: src/http.c:1918
msgid "Authorization failed.\n"
msgstr "Authorization failed.\n"

#: src/http.c:1956 src/http.c:2466
#, c-format
msgid ""
"File %s already there; not retrieving.\n"
"\n"
msgstr ""
"File %s already there; not retrieving.\n"
"\n"

#: src/http.c:2070
msgid "Malformed status line"
msgstr "Malformed status line"

#: src/http.c:2072
msgid "(no description)"
msgstr "(no description)"

#: src/http.c:2149
#, c-format
msgid "Location: %s%s\n"
msgstr "Location: %s%s\n"

#: src/http.c:2150 src/http.c:2258
msgid "unspecified"
msgstr "unspecified"

#: src/http.c:2151
msgid " [following]"
msgstr " [following]"

#: src/http.c:2203
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"

#: src/http.c:2238
msgid "Length: "
msgstr "Length: "

#: src/http.c:2258
msgid "ignored"
msgstr "ignored"

#: src/http.c:2360
#, c-format
msgid "Saving to: %s\n"
msgstr "Saving to: %s\n"

#: src/http.c:2442
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Warning: wildcards not supported in HTTP.\n"

#: src/http.c:2513
msgid "Spider mode enabled. Check if remote file exists.\n"
msgstr "Spider mode enabled. Check if remote file exists.\n"

#: src/http.c:2598
#, c-format
msgid "Cannot write to %s (%s).\n"
msgstr "Cannot write to %s (%s).\n"

#: src/http.c:2607
msgid "Unable to establish SSL connection.\n"
msgstr "Unable to establish SSL connection.\n"

#: src/http.c:2615
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERROR: Redirection (%d) without location.\n"

#: src/http.c:2663
msgid "Remote file does not exist -- broken link!!!\n"
msgstr "Remote file does not exist -- broken link!!!\n"

#: src/http.c:2668
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERROR %d: %s.\n"

#: src/http.c:2685
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified header missing -- time-stamps turned off.\n"

#: src/http.c:2693
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified header invalid -- time-stamp ignored.\n"

#: src/http.c:2723
#, c-format
msgid ""
"Server file no newer than local file %s -- not retrieving.\n"
"\n"
msgstr ""
"Server file no newer than local file %s -- not retrieving.\n"
"\n"

#: src/http.c:2731
#, c-format
msgid "The sizes do not match (local %s) -- retrieving.\n"
msgstr "The sizes do not match (local %s) -- retrieving.\n"

#: src/http.c:2738
msgid "Remote file is newer, retrieving.\n"
msgstr "Remote file is newer, retrieving.\n"

#: src/http.c:2755
msgid ""
"Remote file exists and could contain links to other resources -- "
"retrieving.\n"
"\n"
msgstr ""
"Remote file exists and could contain links to other resources -- "
"retrieving.\n"
"\n"

#: src/http.c:2761
msgid ""
"Remote file exists but does not contain any link -- not retrieving.\n"
"\n"
msgstr ""
"Remote file exists but does not contain any link -- not retrieving.\n"
"\n"

#: src/http.c:2770
msgid ""
"Remote file exists and could contain further links,\n"
"but recursion is disabled -- not retrieving.\n"
"\n"
msgstr ""
"Remote file exists and could contain further links,\n"
"but recursion is disabled -- not retrieving.\n"
"\n"

#: src/http.c:2776
msgid ""
"Remote file exists.\n"
"\n"
msgstr ""
"Remote file exists.\n"
"\n"

#: src/http.c:2785
#, c-format
msgid "%s URL:%s %2d %s\n"
msgstr "%s URL:%s %2d %s\n"

#: src/http.c:2832
#, c-format
msgid ""
"%s (%s) - written to stdout %s[%s/%s]\n"
"\n"
msgstr ""
"%s (%s) - written to stdout %s[%s/%s]\n"
"\n"

#: src/http.c:2833
#, c-format
msgid ""
"%s (%s) - %s saved [%s/%s]\n"
"\n"
msgstr ""
"%s (%s) - %s saved [%s/%s]\n"
"\n"

#: src/http.c:2894
#, c-format
msgid "%s (%s) - Connection closed at byte %s. "
msgstr "%s (%s) - Connection closed at byte %s. "

#: src/http.c:2917
#, c-format
msgid "%s (%s) - Read error at byte %s (%s)."
msgstr "%s (%s) - Read error at byte %s (%s)."

#: src/http.c:2926
#, c-format
msgid "%s (%s) - Read error at byte %s/%s (%s). "
msgstr "%s (%s) - Read error at byte %s/%s (%s). "

#: src/init.c:404
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC points to %s, which doesn’t exist.\n"

#: src/init.c:508 src/netrc.c:282
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Cannot read %s (%s).\n"

#: src/init.c:525
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Error in %s at line %d.\n"

#: src/init.c:531
#, c-format
msgid "%s: Syntax error in %s at line %d.\n"
msgstr "%s: Syntax error in %s at line %d.\n"

#: src/init.c:536
#, c-format
msgid "%s: Unknown command %s in %s at line %d.\n"
msgstr "%s: Unknown command %s in %s at line %d.\n"

#: src/init.c:585
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to %s.\n"
msgstr "%s: Warning: Both system and user wgetrc point to %s.\n"

#: src/init.c:775
#, c-format
msgid "%s: Invalid --execute command %s\n"
msgstr "%s: Invalid --execute command %s\n"

#: src/init.c:820
#, c-format
msgid "%s: %s: Invalid boolean %s; use `on' or `off'.\n"
msgstr "%s: %s: Invalid boolean %s; use ‘[1mon[0m’ or ‘[1moff[0m’.\n"

#: src/init.c:837
#, c-format
msgid "%s: %s: Invalid number %s.\n"
msgstr "%s: %s: Invalid number %s.\n"

#: src/init.c:1042 src/init.c:1061
#, c-format
msgid "%s: %s: Invalid byte value %s\n"
msgstr "%s: %s: Invalid byte value %s\n"

#: src/init.c:1086
#, c-format
msgid "%s: %s: Invalid time period %s\n"
msgstr "%s: %s: Invalid time period %s\n"

#: src/init.c:1140 src/init.c:1230 src/init.c:1333 src/init.c:1358
#, c-format
msgid "%s: %s: Invalid value %s.\n"
msgstr "%s: %s: Invalid value %s.\n"

#: src/init.c:1177
#, c-format
msgid "%s: %s: Invalid header %s.\n"
msgstr "%s: %s: Invalid header %s.\n"

#: src/init.c:1243
#, c-format
msgid "%s: %s: Invalid progress type %s.\n"
msgstr "%s: %s: Invalid progress type %s.\n"

#: src/init.c:1302
#, c-format
msgid ""
"%s: %s: Invalid restriction %s, use [unix|windows],[lowercase|uppercase],"
"[nocontrol].\n"
msgstr ""
"%s: %s: Invalid restriction %s, use [unix|windows],[lowercase|uppercase],"
"[nocontrol].\n"

#: src/iri.c:104
#, c-format
msgid "Encoding %s isn't valid\n"
msgstr "Encoding %s isn’t valid\n"

#: src/iri.c:132
msgid "locale_to_utf8: locale is unset\n"
msgstr "locale_to_utf8: locale is unset\n"

#: src/iri.c:142
#, c-format
msgid "Conversion from %s to %s isn't supported\n"
msgstr "Conversion from %s to %s isn’t supported\n"

#: src/iri.c:183
msgid "Incomplete or invalide multibyte sequence encountered\n"
msgstr "Incomplete or invalide multibyte sequence encountered\n"

#: src/iri.c:208
#, c-format
msgid "Unhandled errno %d\n"
msgstr "Unhandled errno %d\n"

#: src/iri.c:237
#, c-format
msgid "idn_encode failed (%d): %s\n"
msgstr "idn_encode failed (%d): %s\n"

#: src/iri.c:256
#, c-format
msgid "idn_decode failed (%d): %s\n"
msgstr "idn_decode failed (%d): %s\n"

#: src/log.c:809
#, c-format
msgid ""
"\n"
"%s received, redirecting output to %s.\n"
msgstr ""
"\n"
"%s received, redirecting output to %s.\n"

#: src/log.c:819
#, c-format
msgid ""
"\n"
"%s received.\n"
msgstr ""
"\n"
"%s received.\n"

#: src/log.c:820
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; disabling logging.\n"

#: src/main.c:384
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Usage: %s [OPTION]... [URL]...\n"

#: src/main.c:396
msgid ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"

#: src/main.c:398
msgid "Startup:\n"
msgstr "Startup:\n"

#: src/main.c:400
msgid "  -V,  --version           display the version of Wget and exit.\n"
msgstr "  -V,  --version           display the version of Wget and exit.\n"

#: src/main.c:402
msgid "  -h,  --help              print this help.\n"
msgstr "  -h,  --help              print this help.\n"

#: src/main.c:404
msgid "  -b,  --background        go to background after startup.\n"
msgstr "  -b,  --background        go to background after startup.\n"

#: src/main.c:406
msgid "  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
msgstr "  -e,  --execute=COMMAND   execute a ‘[1m.wgetrc[0m’-style command.\n"

#: src/main.c:410
msgid "Logging and input file:\n"
msgstr "Logging and input file:\n"

#: src/main.c:412
msgid "  -o,  --output-file=FILE    log messages to FILE.\n"
msgstr "  -o,  --output-file=FILE    log messages to FILE.\n"

#: src/main.c:414
msgid "  -a,  --append-output=FILE  append messages to FILE.\n"
msgstr "  -a,  --append-output=FILE  append messages to FILE.\n"

#: src/main.c:417
msgid "  -d,  --debug               print lots of debugging information.\n"
msgstr "  -d,  --debug               print lots of debugging information.\n"

#: src/main.c:421
msgid "       --wdebug              print Watt-32 debug output.\n"
msgstr "       --wdebug              print Watt-32 debug output.\n"

#: src/main.c:424
msgid "  -q,  --quiet               quiet (no output).\n"
msgstr "  -q,  --quiet               quiet (no output).\n"

#: src/main.c:426
msgid "  -v,  --verbose             be verbose (this is the default).\n"
msgstr "  -v,  --verbose             be verbose (this is the default).\n"

#: src/main.c:428
msgid ""
"  -nv, --no-verbose          turn off verboseness, without being quiet.\n"
msgstr ""
"  -nv, --no-verbose          turn off verboseness, without being quiet.\n"

#: src/main.c:430
msgid ""
"  -i,  --input-file=FILE     download URLs found in local or external FILE.\n"
msgstr ""
"  -i,  --input-file=FILE     download URLs found in local or external FILE.\n"

#: src/main.c:432
msgid "  -F,  --force-html          treat input file as HTML.\n"
msgstr "  -F,  --force-html          treat input file as HTML.\n"

#: src/main.c:434
msgid ""
"  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"
msgstr ""
"  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"

#: src/main.c:438
msgid "Download:\n"
msgstr "Download:\n"

#: src/main.c:440
msgid ""
"  -t,  --tries=NUMBER            set number of retries to NUMBER (0 "
"unlimits).\n"
msgstr ""
"  -t,  --tries=NUMBER            set number of retries to NUMBER (0 "
"unlimits).\n"

#: src/main.c:442
msgid "       --retry-connrefused       retry even if connection is refused.\n"
msgstr ""
"       --retry-connrefused       retry even if connection is refused.\n"

#: src/main.c:444
msgid "  -O,  --output-document=FILE    write documents to FILE.\n"
msgstr "  -O,  --output-document=FILE    write documents to FILE.\n"

#: src/main.c:446
msgid ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"
msgstr ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"

#: src/main.c:449
msgid ""
"  -c,  --continue                resume getting a partially-downloaded "
"file.\n"
msgstr ""
"  -c,  --continue                resume getting a partially-downloaded "
"file.\n"

#: src/main.c:451
msgid "       --progress=TYPE           select progress gauge type.\n"
msgstr "       --progress=TYPE           select progress gauge type.\n"

#: src/main.c:453
msgid ""
"  -N,  --timestamping            don't re-retrieve files unless newer than\n"
"                                 local.\n"
msgstr ""
"  -N,  --timestamping            don’t re-retrieve files unless newer than\n"
"                                 local.\n"

#: src/main.c:456
msgid "  -S,  --server-response         print server response.\n"
msgstr "  -S,  --server-response         print server response.\n"

#: src/main.c:458
msgid "       --spider                  don't download anything.\n"
msgstr "       --spider                  don’t download anything.\n"

#: src/main.c:460
msgid "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"
msgstr "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"

#: src/main.c:462
msgid "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"
msgstr "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"

#: src/main.c:464
msgid "       --connect-timeout=SECS    set the connect timeout to SECS.\n"
msgstr "       --connect-timeout=SECS    set the connect timeout to SECS.\n"

#: src/main.c:466
msgid "       --read-timeout=SECS       set the read timeout to SECS.\n"
msgstr "       --read-timeout=SECS       set the read timeout to SECS.\n"

#: src/main.c:468
msgid "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"
msgstr "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"

#: src/main.c:470
msgid ""
"       --waitretry=SECONDS       wait 1..SECONDS between retries of a "
"retrieval.\n"
msgstr ""
"       --waitretry=SECONDS       wait 1..SECONDS between retries of a "
"retrieval.\n"

#: src/main.c:472
msgid ""
"       --random-wait             wait from 0...2*WAIT secs between "
"retrievals.\n"
msgstr ""
"       --random-wait             wait from 0...2*WAIT secs between "
"retrievals.\n"

#: src/main.c:474
msgid "       --no-proxy                explicitly turn off proxy.\n"
msgstr "       --no-proxy                explicitly turn off proxy.\n"

#: src/main.c:476
msgid "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"
msgstr "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"

#: src/main.c:478
msgid ""
"       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local "
"host.\n"
msgstr ""
"       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local "
"host.\n"

#: src/main.c:480
msgid "       --limit-rate=RATE         limit download rate to RATE.\n"
msgstr "       --limit-rate=RATE         limit download rate to RATE.\n"

#: src/main.c:482
msgid "       --no-dns-cache            disable caching DNS lookups.\n"
msgstr "       --no-dns-cache            disable caching DNS lookups.\n"

#: src/main.c:484
msgid ""
"       --restrict-file-names=OS  restrict chars in file names to ones OS "
"allows.\n"
msgstr ""
"       --restrict-file-names=OS  restrict chars in file names to ones OS "
"allows.\n"

#: src/main.c:486
msgid ""
"       --ignore-case             ignore case when matching files/"
"directories.\n"
msgstr ""
"       --ignore-case             ignore case when matching files/"
"directories.\n"

#: src/main.c:489
msgid "  -4,  --inet4-only              connect only to IPv4 addresses.\n"
msgstr "  -4,  --inet4-only              connect only to IPv4 addresses.\n"

#: src/main.c:491
msgid "  -6,  --inet6-only              connect only to IPv6 addresses.\n"
msgstr "  -6,  --inet6-only              connect only to IPv6 addresses.\n"

#: src/main.c:493
msgid ""
"       --prefer-family=FAMILY    connect first to addresses of specified "
"family,\n"
"                                 one of IPv6, IPv4, or none.\n"
msgstr ""
"       --prefer-family=FAMILY    connect first to addresses of specified "
"family,\n"
"                                 one of IPv6, IPv4, or none.\n"

#: src/main.c:497
msgid "       --user=USER               set both ftp and http user to USER.\n"
msgstr "       --user=USER               set both ftp and http user to USER.\n"

#: src/main.c:499
msgid ""
"       --password=PASS           set both ftp and http password to PASS.\n"
msgstr ""
"       --password=PASS           set both ftp and http password to PASS.\n"

#: src/main.c:501
msgid "       --ask-password            prompt for passwords.\n"
msgstr "       --ask-password            prompt for passwords.\n"

#: src/main.c:505
msgid "Directories:\n"
msgstr "Directories:\n"

#: src/main.c:507
msgid "  -nd, --no-directories           don't create directories.\n"
msgstr "  -nd, --no-directories           don’t create directories.\n"

#: src/main.c:509
msgid "  -x,  --force-directories        force creation of directories.\n"
msgstr "  -x,  --force-directories        force creation of directories.\n"

#: src/main.c:511
msgid "  -nH, --no-host-directories      don't create host directories.\n"
msgstr "  -nH, --no-host-directories      don’t create host directories.\n"

#: src/main.c:513
msgid "       --protocol-directories     use protocol name in directories.\n"
msgstr "       --protocol-directories     use protocol name in directories.\n"

#: src/main.c:515
msgid "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"
msgstr "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"

#: src/main.c:517
msgid ""
"       --cut-dirs=NUMBER          ignore NUMBER remote directory "
"components.\n"
msgstr ""
"       --cut-dirs=NUMBER          ignore NUMBER remote directory "
"components.\n"

#: src/main.c:521
msgid "HTTP options:\n"
msgstr "HTTP options:\n"

#: src/main.c:523
msgid "       --http-user=USER        set http user to USER.\n"
msgstr "       --http-user=USER        set http user to USER.\n"

#: src/main.c:525
msgid "       --http-password=PASS    set http password to PASS.\n"
msgstr "       --http-password=PASS    set http password to PASS.\n"

#: src/main.c:527
msgid "       --no-cache              disallow server-cached data.\n"
msgstr "       --no-cache              disallow server-cached data.\n"

#: src/main.c:529
msgid ""
"       --default-page=NAME     Change the default page name (normally\n"
"                               this is `index.html'.).\n"
msgstr ""
"       --default-page=NAME     Change the default page name (normally\n"
"                               this is ‘[1mindex.html[0m’.).\n"

#: src/main.c:532
msgid ""
"  -E,  --html-extension        save HTML documents with `.html' extension.\n"
msgstr ""
"  -E,  --html-extension        save HTML documents with ‘[1m.html[0m’ "
"extension.\n"

#: src/main.c:534
msgid "       --ignore-length         ignore `Content-Length' header field.\n"
msgstr ""
"       --ignore-length         ignore ‘[1mContent-Length[0m’ header field.\n"

#: src/main.c:536
msgid "       --header=STRING         insert STRING among the headers.\n"
msgstr "       --header=STRING         insert STRING among the headers.\n"

#: src/main.c:538
msgid "       --max-redirect          maximum redirections allowed per page.\n"
msgstr ""
"       --max-redirect          maximum redirections allowed per page.\n"

#: src/main.c:540
msgid "       --proxy-user=USER       set USER as proxy username.\n"
msgstr "       --proxy-user=USER       set USER as proxy username.\n"

#: src/main.c:542
msgid "       --proxy-password=PASS   set PASS as proxy password.\n"
msgstr "       --proxy-password=PASS   set PASS as proxy password.\n"

#: src/main.c:544
msgid ""
"       --referer=URL           include `Referer: URL' header in HTTP "
"request.\n"
msgstr ""
"       --referer=URL           include ‘[1mReferer: URL[0m’ header in HTTP "
"request.\n"

#: src/main.c:546
msgid "       --save-headers          save the HTTP headers to file.\n"
msgstr "       --save-headers          save the HTTP headers to file.\n"

#: src/main.c:548
msgid ""
"  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"
msgstr ""
"  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"

#: src/main.c:550
msgid ""
"       --no-http-keep-alive    disable HTTP keep-alive (persistent "
"connections).\n"
msgstr ""
"       --no-http-keep-alive    disable HTTP keep-alive (persistent "
"connections).\n"

#: src/main.c:552
msgid "       --no-cookies            don't use cookies.\n"
msgstr "       --no-cookies            don’t use cookies.\n"

#: src/main.c:554
msgid "       --load-cookies=FILE     load cookies from FILE before session.\n"
msgstr ""
"       --load-cookies=FILE     load cookies from FILE before session.\n"

#: src/main.c:556
msgid "       --save-cookies=FILE     save cookies to FILE after session.\n"
msgstr "       --save-cookies=FILE     save cookies to FILE after session.\n"

#: src/main.c:558
msgid ""
"       --keep-session-cookies  load and save session (non-permanent) "
"cookies.\n"
msgstr ""
"       --keep-session-cookies  load and save session (non-permanent) "
"cookies.\n"

#: src/main.c:560
msgid ""
"       --post-data=STRING      use the POST method; send STRING as the "
"data.\n"
msgstr ""
"       --post-data=STRING      use the POST method; send STRING as the "
"data.\n"

#: src/main.c:562
msgid ""
"       --post-file=FILE        use the POST method; send contents of FILE.\n"
msgstr ""
"       --post-file=FILE        use the POST method; send contents of FILE.\n"

#: src/main.c:564
msgid ""
"       --content-disposition   honor the Content-Disposition header when\n"
"                               choosing local file names (EXPERIMENTAL).\n"
msgstr ""
"       --content-disposition   honor the Content-Disposition header when\n"
"                               choosing local file names (EXPERIMENTAL).\n"

#: src/main.c:567
msgid ""
"       --auth-no-challenge     Send Basic HTTP authentication information\n"
"                               without first waiting for the server's\n"
"                               challenge.\n"
msgstr ""
"       --auth-no-challenge     Send Basic HTTP authentication information\n"
"                               without first waiting for the server’s\n"
"                               challenge.\n"

#: src/main.c:574
msgid "HTTPS (SSL/TLS) options:\n"
msgstr "HTTPS (SSL/TLS) options:\n"

#: src/main.c:576
msgid ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"
msgstr ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"

#: src/main.c:579
msgid ""
"       --no-check-certificate   don't validate the server's certificate.\n"
msgstr ""
"       --no-check-certificate   don’t validate the server’s certificate.\n"

#: src/main.c:581
msgid "       --certificate=FILE       client certificate file.\n"
msgstr "       --certificate=FILE       client certificate file.\n"

#: src/main.c:583
msgid "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"
msgstr "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"

#: src/main.c:585
msgid "       --private-key=FILE       private key file.\n"
msgstr "       --private-key=FILE       private key file.\n"

#: src/main.c:587
msgid "       --private-key-type=TYPE  private key type, PEM or DER.\n"
msgstr "       --private-key-type=TYPE  private key type, PEM or DER.\n"

#: src/main.c:589
msgid "       --ca-certificate=FILE    file with the bundle of CA's.\n"
msgstr "       --ca-certificate=FILE    file with the bundle of CA’s.\n"

#: src/main.c:591
msgid ""
"       --ca-directory=DIR       directory where hash list of CA's is "
"stored.\n"
msgstr ""
"       --ca-directory=DIR       directory where hash list of CA’s is "
"stored.\n"

#: src/main.c:593
msgid ""
"       --random-file=FILE       file with random data for seeding the SSL "
"PRNG.\n"
msgstr ""
"       --random-file=FILE       file with random data for seeding the SSL "
"PRNG.\n"

#: src/main.c:595
msgid ""
"       --egd-file=FILE          file naming the EGD socket with random "
"data.\n"
msgstr ""
"       --egd-file=FILE          file naming the EGD socket with random "
"data.\n"

#: src/main.c:600
msgid "FTP options:\n"
msgstr "FTP options:\n"

#: src/main.c:603
msgid ""
"       --ftp-stmlf             Use Stream_LF format for all binary FTP "
"files.\n"
msgstr ""
"       --ftp-stmlf             Use Stream_LF format for all binary FTP "
"files.\n"

#: src/main.c:606
msgid "       --ftp-user=USER         set ftp user to USER.\n"
msgstr "       --ftp-user=USER         set ftp user to USER.\n"

#: src/main.c:608
msgid "       --ftp-password=PASS     set ftp password to PASS.\n"
msgstr "       --ftp-password=PASS     set ftp password to PASS.\n"

#: src/main.c:610
msgid "       --no-remove-listing     don't remove `.listing' files.\n"
msgstr "       --no-remove-listing     don’t remove ‘[1m.listing[0m’ files.\n"

#: src/main.c:612
msgid "       --no-glob               turn off FTP file name globbing.\n"
msgstr "       --no-glob               turn off FTP file name globbing.\n"

#: src/main.c:614
msgid "       --no-passive-ftp        disable the \"passive\" transfer mode.\n"
msgstr ""
"       --no-passive-ftp        disable the “[1mpassive[0m” transfer mode.\n"

#: src/main.c:616
msgid ""
"       --retr-symlinks         when recursing, get linked-to files (not "
"dir).\n"
msgstr ""
"       --retr-symlinks         when recursing, get linked-to files (not "
"dir).\n"

#: src/main.c:618
msgid "       --preserve-permissions  preserve remote file permissions.\n"
msgstr "       --preserve-permissions  preserve remote file permissions.\n"

#: src/main.c:622
msgid "Recursive download:\n"
msgstr "Recursive download:\n"

#: src/main.c:624
msgid "  -r,  --recursive          specify recursive download.\n"
msgstr "  -r,  --recursive          specify recursive download.\n"

#: src/main.c:626
msgid ""
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for "
"infinite).\n"
msgstr ""
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for "
"infinite).\n"

#: src/main.c:628
msgid ""
"       --delete-after       delete files locally after downloading them.\n"
msgstr ""
"       --delete-after       delete files locally after downloading them.\n"

#: src/main.c:630
msgid ""
"  -k,  --convert-links      make links in downloaded HTML or CSS point to\n"
"                            local files.\n"
msgstr ""
"  -k,  --convert-links      make links in downloaded HTML or CSS point to\n"
"                            local files.\n"

#: src/main.c:634
msgid ""
"  -K,  --backup-converted   before converting file X, back up as X_orig.\n"
msgstr ""
"  -K,  --backup-converted   before converting file X, back up as X_orig.\n"

#: src/main.c:637
msgid ""
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
msgstr ""
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"

#: src/main.c:640
msgid ""
"  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"
msgstr ""
"  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"

#: src/main.c:642
msgid ""
"  -p,  --page-requisites    get all images, etc. needed to display HTML "
"page.\n"
msgstr ""
"  -p,  --page-requisites    get all images, etc. needed to display HTML "
"page.\n"

#: src/main.c:644
msgid ""
"       --strict-comments    turn on strict (SGML) handling of HTML "
"comments.\n"
msgstr ""
"       --strict-comments    turn on strict (SGML) handling of HTML "
"comments.\n"

#: src/main.c:648
msgid "Recursive accept/reject:\n"
msgstr "Recursive accept/reject:\n"

#: src/main.c:650
msgid ""
"  -A,  --accept=LIST               comma-separated list of accepted "
"extensions.\n"
msgstr ""
"  -A,  --accept=LIST               comma-separated list of accepted "
"extensions.\n"

#: src/main.c:652
msgid ""
"  -R,  --reject=LIST               comma-separated list of rejected "
"extensions.\n"
msgstr ""
"  -R,  --reject=LIST               comma-separated list of rejected "
"extensions.\n"

#: src/main.c:654
msgid ""
"  -D,  --domains=LIST              comma-separated list of accepted "
"domains.\n"
msgstr ""
"  -D,  --domains=LIST              comma-separated list of accepted "
"domains.\n"

#: src/main.c:656
msgid ""
"       --exclude-domains=LIST      comma-separated list of rejected "
"domains.\n"
msgstr ""
"       --exclude-domains=LIST      comma-separated list of rejected "
"domains.\n"

#: src/main.c:658
msgid ""
"       --follow-ftp                follow FTP links from HTML documents.\n"
msgstr ""
"       --follow-ftp                follow FTP links from HTML documents.\n"

#: src/main.c:660
msgid ""
"       --follow-tags=LIST          comma-separated list of followed HTML "
"tags.\n"
msgstr ""
"       --follow-tags=LIST          comma-separated list of followed HTML "
"tags.\n"

#: src/main.c:662
msgid ""
"       --ignore-tags=LIST          comma-separated list of ignored HTML "
"tags.\n"
msgstr ""
"       --ignore-tags=LIST          comma-separated list of ignored HTML "
"tags.\n"

#: src/main.c:664
msgid ""
"  -H,  --span-hosts                go to foreign hosts when recursive.\n"
msgstr ""
"  -H,  --span-hosts                go to foreign hosts when recursive.\n"

#: src/main.c:666
msgid "  -L,  --relative                  follow relative links only.\n"
msgstr "  -L,  --relative                  follow relative links only.\n"

#: src/main.c:668
msgid "  -I,  --include-directories=LIST  list of allowed directories.\n"
msgstr "  -I,  --include-directories=LIST  list of allowed directories.\n"

#: src/main.c:670
msgid "  -X,  --exclude-directories=LIST  list of excluded directories.\n"
msgstr "  -X,  --exclude-directories=LIST  list of excluded directories.\n"

#: src/main.c:672
msgid ""
"  -np, --no-parent                 don't ascend to the parent directory.\n"
msgstr ""
"  -np, --no-parent                 don’t ascend to the parent directory.\n"

#: src/main.c:676
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"

#: src/main.c:681
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, a non-interactive network retriever.\n"

#: src/main.c:721
#, c-format
msgid "Password for user %s: "
msgstr "Password for user %s: "

#: src/main.c:723
#, c-format
msgid "Password: "
msgstr "Password: "

#: src/main.c:773
msgid "Wgetrc: "
msgstr "Wgetrc: "

#: src/main.c:774
msgid "Locale: "
msgstr "Locale: "

#: src/main.c:775
msgid "Compile: "
msgstr "Compile: "

#: src/main.c:776
msgid "Link: "
msgstr "Link: "

#. TRANSLATORS: When available, an actual copyright character
#. (cirle-c) should be used in preference to "(C)".
#: src/main.c:836
msgid "Copyright (C) 2008 Free Software Foundation, Inc.\n"
msgstr "Copyright © 2008 Free Software Foundation, Inc.\n"

#: src/main.c:838
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

#. TRANSLATORS: When available, please use the proper diacritics for
#. names such as this one. See en_US.po for reference.
#: src/main.c:845
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Originally written by Hrvoje Nikšić <hniksic@xemacs.org>.\n"

#: src/main.c:847
msgid "Currently maintained by Micah Cowan <micah@cowan.name>.\n"
msgstr "Currently maintained by Micah Cowan <micah@cowan.name>.\n"

#: src/main.c:849
msgid "Please send bug reports and questions to <bug-wget@gnu.org>.\n"
msgstr "Please send bug reports and questions to <bug-wget@gnu.org>.\n"

#: src/main.c:899 src/main.c:968 src/main.c:1090
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Try ‘[1m%s --help[0m’ for more options.\n"

#: src/main.c:965
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: illegal option -- ‘[1m-n%c[0m’\n"

#: src/main.c:1023
#, c-format
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Can’t be verbose and quiet at the same time.\n"

#: src/main.c:1029
#, c-format
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Can’t timestamp and not clobber old files at the same time.\n"

#: src/main.c:1037
#, c-format
msgid "Cannot specify both --inet4-only and --inet6-only.\n"
msgstr "Cannot specify both --inet4-only and --inet6-only.\n"

#: src/main.c:1047
msgid ""
"Cannot specify both -k and -O if multiple URLs are given, or in combination\n"
"with -p or -r. See the manual for details.\n"
"\n"
msgstr ""
"Cannot specify both -k and -O if multiple URLs are given, or in combination\n"
"with -p or -r. See the manual for details.\n"
"\n"

#: src/main.c:1056
msgid ""
"WARNING: combining -O with -r or -p will mean that all downloaded content\n"
"will be placed in the single file you specified.\n"
"\n"
msgstr ""
"WARNING: combining -O with -r or -p will mean that all downloaded content\n"
"will be placed in the single file you specified.\n"
"\n"

#: src/main.c:1062
msgid ""
"WARNING: timestamping does nothing in combination with -O. See the manual\n"
"for details.\n"
"\n"
msgstr ""
"WARNING: timestamping does nothing in combination with -O. See the manual\n"
"for details.\n"
"\n"

#: src/main.c:1070
#, c-format
msgid "File `%s' already there; not retrieving.\n"
msgstr "File ‘[1m%s[0m’ already there; not retrieving.\n"

#: src/main.c:1077
#, c-format
msgid "Cannot specify both --ask-password and --password.\n"
msgstr "Cannot specify both --ask-password and --password.\n"

#: src/main.c:1085
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: missing URL\n"

#: src/main.c:1110
#, c-format
msgid "This version does not have support for IRIs\n"
msgstr "This version does not have support for IRIs\n"

#: src/main.c:1174
msgid ""
"WARNING: Can't reopen standard output in binary mode;\n"
"         downloaded file may contain inappropriate line endings.\n"
msgstr ""
"WARNING: Can’t reopen standard output in binary mode;\n"
"         downloaded file may contain inappropriate line endings.\n"

#: src/main.c:1309
#, c-format
msgid "No URLs found in %s.\n"
msgstr "No URLs found in %s.\n"

#: src/main.c:1327
#, c-format
msgid ""
"FINISHED --%s--\n"
"Downloaded: %d files, %s in %s (%s)\n"
msgstr ""
"FINISHED --%s--\n"
"Downloaded: %d files, %s in %s (%s)\n"

#: src/main.c:1336
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

#: src/mswindows.c:294 src/utils.c:472
#, c-format
msgid "Output will be written to %s.\n"
msgstr "Output will be written to %s.\n"

#: src/mswindows.c:462 src/mswindows.c:469
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Couldn’t find usable socket driver.\n"

#: src/netrc.c:390
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: warning: “[1m%s[0m” token appears before any machine name\n"

#: src/netrc.c:421
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: unknown token “[1m%s[0m”\n"

#: src/netrc.c:485
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Usage: %s NETRC [HOSTNAME]\n"

#: src/netrc.c:495
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: cannot stat %s: %s\n"

#: src/openssl.c:113
msgid "WARNING: using a weak random seed.\n"
msgstr "WARNING: using a weak random seed.\n"

#: src/openssl.c:173
msgid "Could not seed PRNG; consider using --random-file.\n"
msgstr "Could not seed PRNG; consider using --random-file.\n"

#: src/openssl.c:526
#, c-format
msgid "%s: cannot verify %s's certificate, issued by %s:\n"
msgstr "%s: cannot verify %s’s certificate, issued by %s:\n"

#: src/openssl.c:535
msgid "  Unable to locally verify the issuer's authority.\n"
msgstr "  Unable to locally verify the issuer’s authority.\n"

#: src/openssl.c:539
msgid "  Self-signed certificate encountered.\n"
msgstr "  Self-signed certificate encountered.\n"

#: src/openssl.c:542
msgid "  Issued certificate not yet valid.\n"
msgstr "  Issued certificate not yet valid.\n"

#: src/openssl.c:545
msgid "  Issued certificate has expired.\n"
msgstr "  Issued certificate has expired.\n"

#: src/openssl.c:577
#, c-format
msgid "%s: certificate common name %s doesn't match requested host name %s.\n"
msgstr "%s: certificate common name %s doesn’t match requested host name %s.\n"

#: src/openssl.c:590
#, c-format
msgid "To connect to %s insecurely, use `--no-check-certificate'.\n"
msgstr "To connect to %s insecurely, use ‘[1m--no-check-certificate[0m’.\n"

#: src/progress.c:242
#, c-format
msgid ""
"\n"
"%*s[ skipping %sK ]"
msgstr ""
"\n"
"%*s[ skipping %sK ]"

#: src/progress.c:456
#, c-format
msgid "Invalid dot style specification %s; leaving unchanged.\n"
msgstr "Invalid dot style specification %s; leaving unchanged.\n"

#: src/progress.c:805
#, c-format
msgid "  eta %s"
msgstr "  eta %s"

#: src/progress.c:1050
msgid "   in "
msgstr "   in "

#: src/ptimer.c:161
#, c-format
msgid "Cannot get REALTIME clock frequency: %s\n"
msgstr "Cannot get REALTIME clock frequency: %s\n"

#: src/recur.c:439
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Removing %s since it should be rejected.\n"

#: src/res.c:390
#, c-format
msgid "Cannot open %s: %s"
msgstr "Cannot open %s: %s"

#: src/res.c:549
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Loading robots.txt; please ignore errors.\n"

#: src/retr.c:666
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Error parsing proxy URL %s: %s.\n"

#: src/retr.c:675
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Error in proxy URL %s: Must be HTTP.\n"

#: src/retr.c:772
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d redirections exceeded.\n"

#: src/retr.c:1006
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Giving up.\n"
"\n"

#: src/retr.c:1006
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

#: src/url.c:633
msgid "No error"
msgstr "No error"

#: src/url.c:635
#, c-format
msgid "Unsupported scheme %s"
msgstr "Unsupported scheme %s"

#: src/url.c:637
msgid "Scheme missing"
msgstr "Scheme missing"

#: src/url.c:639
msgid "Invalid host name"
msgstr "Invalid host name"

#: src/url.c:641
msgid "Bad port number"
msgstr "Bad port number"

#: src/url.c:643
msgid "Invalid user name"
msgstr "Invalid user name"

#: src/url.c:645
msgid "Unterminated IPv6 numeric address"
msgstr "Unterminated IPv6 numeric address"

#: src/url.c:647
msgid "IPv6 addresses not supported"
msgstr "IPv6 addresses not supported"

#: src/url.c:649
msgid "Invalid IPv6 numeric address"
msgstr "Invalid IPv6 numeric address"

#: src/url.c:951
msgid "HTTPS support not compiled in"
msgstr "HTTPS support not compiled in"

#: src/utils.c:108
#, c-format
msgid "%s: %s: Failed to allocate enough memory; memory exhausted.\n"
msgstr "%s: %s: Failed to allocate enough memory; memory exhausted.\n"

#: src/utils.c:114
#, c-format
msgid "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"
msgstr "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"

#: src/utils.c:327
#, c-format
msgid "%s: aprintf: text buffer is too big (%ld bytes), aborting.\n"
msgstr "%s: aprintf: text buffer is too big (%ld bytes), aborting.\n"

#: src/utils.c:470
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Continuing in background, pid %d.\n"

#: src/utils.c:521
#, c-format
msgid "Failed to unlink symlink %s: %s\n"
msgstr "Failed to unlink symlink %s: %s\n"
