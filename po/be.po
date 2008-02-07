# Беларускі пераклад wget-1.8.2.
# Copyright (C) 2003, 2004 Free Software Foundation, Inc.
# Hleb Valoska <el_globus@tut.by>, 2003.
# Alexander Nyakhaychyk <nyakhaychyk@gmail.com>, 2003, 2004, 2007
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.11-b2405\n"
"Report-Msgid-Bugs-To: \n"
"POT-Creation-Date: 2007-10-22 11:16-0700\n"
"PO-Revision-Date: 2007-11-08 09:56+0200\n"
"Last-Translator: Alexander Nyakhaychyk <nyakhaychyk@gmail.com>\n"
"Language-Team: Belarusian <i18n@mova.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
"X-Generator: KBabel 1.0.2\n"

#: src/connect.c:196
#, c-format
msgid "%s: unable to resolve bind address `%s'; disabling bind.\n"
msgstr ""

#: src/connect.c:268
#, c-format
msgid "Connecting to %s|%s|:%d... "
msgstr "Далучэньне да %s[%s]:%d... "

#: src/connect.c:271
#, c-format
msgid "Connecting to %s:%d... "
msgstr "Далучэньне да %s:%d... "

#: src/connect.c:331
msgid "connected.\n"
msgstr "далучэньне ўсталявана.\n"

#: src/connect.c:343 src/host.c:753 src/host.c:782
#, c-format
msgid "failed: %s.\n"
msgstr "збой: %s.\n"

#: src/connect.c:367 src/http.c:1629
#, c-format
msgid "%s: unable to resolve host address `%s'\n"
msgstr "%s: немагчыма разьвязаць назву вузла \"%s\"\n"

#: src/convert.c:171
#, c-format
msgid "Converted %d files in %s seconds.\n"
msgstr "Пераўтворана %d файлаў за %s сэк.\n"

#: src/convert.c:196
#, c-format
msgid "Converting %s... "
msgstr "Пераўтварэньне %s... "

#: src/convert.c:209
msgid "nothing to do.\n"
msgstr "няма чаго рабіць.\n"

#: src/convert.c:217 src/convert.c:241
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Немагчыма пераўтварыць спасылкі ў %s: %s\n"

#: src/convert.c:232
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Немагчыма выдаліць \"%s\": %s\n"

#: src/convert.c:441
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr ""

#: src/cookies.c:444
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Сынтаксычная памылка ў Set-Cookie: %s на месцы %d.\n"

#: src/cookies.c:686
#, c-format
msgid "Cookie coming from %s attempted to set domain to %s\n"
msgstr "Cookie з %s спрабуе выставіць дамэн у %s\n"

#: src/cookies.c:1133 src/cookies.c:1251
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Немагчыма адчыніць файл печыва \"%s\": %s\n"

#: src/cookies.c:1288
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Памылка запісу ў \"%s\": %s\n"

#: src/cookies.c:1291
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Памылка закрыцьця \"%s\": %s\n"

#: src/ftp-ls.c:837
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Гэты від сьпіса файлаў не падтрымліваецца, спроба ўжыць разбор Unix-сьпісаў.\n"

#: src/ftp-ls.c:883 src/ftp-ls.c:885
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Зьмест /%s на %s:%d"

#: src/ftp-ls.c:908
#, c-format
msgid "time unknown       "
msgstr "час невядомы       "

#: src/ftp-ls.c:912
#, c-format
msgid "File        "
msgstr "Файл        "

#: src/ftp-ls.c:915
#, c-format
msgid "Directory   "
msgstr "Дырэкторыя  "

#: src/ftp-ls.c:918
#, c-format
msgid "Link        "
msgstr "Лучыва      "

#: src/ftp-ls.c:921
#, c-format
msgid "Not sure    "
msgstr "Ня пэўны    "

#: src/ftp-ls.c:939
#, c-format
msgid " (%s bytes)"
msgstr " (%s байтаў)"

#: src/ftp.c:214
#, c-format
msgid "Length: %s"
msgstr "Даўжыня: %s"

#: src/ftp.c:220 src/http.c:2174
#, c-format
msgid ", %s (%s) remaining"
msgstr ""

#: src/ftp.c:224 src/http.c:2178
#, c-format
msgid ", %s remaining"
msgstr ""

#: src/ftp.c:227
msgid " (unauthoritative)\n"
msgstr " (неаўтарытэтны)\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:303
#, c-format
msgid "Logging in as %s ... "
msgstr "Уваходжу як %s ... "

#: src/ftp.c:316 src/ftp.c:362 src/ftp.c:391 src/ftp.c:443 src/ftp.c:555
#: src/ftp.c:601 src/ftp.c:630 src/ftp.c:687 src/ftp.c:748 src/ftp.c:808
#: src/ftp.c:855
msgid "Error in server response, closing control connection.\n"
msgstr "Памылка ў адказе паслужніка; кантрольнае далучэньне зачынена.\n"

#: src/ftp.c:323
msgid "Error in server greeting.\n"
msgstr "Памылка ў вітаньні сэрвэра.\n"

#: src/ftp.c:330 src/ftp.c:451 src/ftp.c:563 src/ftp.c:638 src/ftp.c:697
#: src/ftp.c:758 src/ftp.c:818 src/ftp.c:865
msgid "Write failed, closing control connection.\n"
msgstr "Памылка запісу, закрыю кіроўнае злучэньне.\n"

#: src/ftp.c:336
msgid "The server refuses login.\n"
msgstr "Сэрвэр адмаўляе ва ўваходзе.\n"

#: src/ftp.c:342
msgid "Login incorrect.\n"
msgstr "Уваход не карэктны.\n"

#: src/ftp.c:348
msgid "Logged in!\n"
msgstr "Увайшоў!\n"

#: src/ftp.c:370
msgid "Server error, can't determine system type.\n"
msgstr "Памылка сэрвэра, немагчыма вызначыць тып сыстэмы.\n"

#: src/ftp.c:379 src/ftp.c:674 src/ftp.c:731 src/ftp.c:774
msgid "done.    "
msgstr "зроблена."

#: src/ftp.c:431 src/ftp.c:580 src/ftp.c:613 src/ftp.c:838 src/ftp.c:884
msgid "done.\n"
msgstr "зроблена.\n"

#: src/ftp.c:458
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Невядомы тып `%c', закрыю кіроўнае злучэньне.\n"

#: src/ftp.c:470
msgid "done.  "
msgstr "зроблена."

#: src/ftp.c:476
msgid "==> CWD not needed.\n"
msgstr "==> CWD непатрэбнае.\n"

#: src/ftp.c:569
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Няма такой дырэкторыи \"%s\".\n"
"\n"

#. do not CWD
#: src/ftp.c:584
msgid "==> CWD not required.\n"
msgstr "==> CWD непатрэбнае.\n"

#: src/ftp.c:644
msgid "Cannot initiate PASV transfer.\n"
msgstr "Немагчыма ініцыялізаваць PASV-перадачу.\n"

#: src/ftp.c:648
msgid "Cannot parse PASV response.\n"
msgstr "Немагчыма зрабіць разбор PASV адказу.\n"

#: src/ftp.c:665
#, c-format
msgid "couldn't connect to %s port %d: %s\n"
msgstr "немагчыма далучыцца да %s, порт %d: %s\n"

#: src/ftp.c:713
#, c-format
msgid "Bind error (%s).\n"
msgstr "Памылка bind (%s).\n"

#: src/ftp.c:719
msgid "Invalid PORT.\n"
msgstr "Нерэчаісны порт.\n"

#: src/ftp.c:765
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""

#: src/ftp.c:826
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Файл \"%s\" адсутнічае.\n"
"\n"

#: src/ftp.c:873
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Файл ці тэчка \"%s'\" адсутнічае.\n"
"\n"

#. We cannot just invent a new name and use it (which is
#. what functions like unique_create typically do)
#. because we told the user we'd use this name.
#. Instead, return and retry the download.
#: src/ftp.c:935 src/http.c:2236
#, c-format
msgid "%s has sprung into existence.\n"
msgstr ""

#: src/ftp.c:987
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, закрыцьцё кантрольнага далучэньня.\n"

#: src/ftp.c:996
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr ""

#: src/ftp.c:1011
msgid "Control connection closed.\n"
msgstr "Кантрольнае далучэньне зачынена.\n"

#: src/ftp.c:1029
msgid "Data transfer aborted.\n"
msgstr "Абарваная перадача даньняў.\n"

#: src/ftp.c:1097
#, c-format
msgid "File `%s' already there; not retrieving.\n"
msgstr "Файл \"%s\" ужо тут і ня будзе выцягвацца.\n"

#: src/ftp.c:1165 src/http.c:2394
#, c-format
msgid "(try:%2d)"
msgstr "(спроба: %2d)"

#: src/ftp.c:1235 src/http.c:2717
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s]\n"
"\n"
msgstr ""
"%s (%s) - \"%s\" захавана [%s]\n"
"\n"

#: src/ftp.c:1277 src/main.c:1005 src/recur.c:378 src/retr.c:860
#, c-format
msgid "Removing %s.\n"
msgstr "Выдаленьне %s.\n"

#: src/ftp.c:1319
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Выкарыстаньне \"%s\" у якасьці лістынгу tmp-файла\n"

#: src/ftp.c:1334
#, c-format
msgid "Removed `%s'.\n"
msgstr "Выдалены \"%s\".\n"

#: src/ftp.c:1367
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Значэньне рэкурсыўнае глыбіні %d большае за найбольшую дазволеную глыбіню %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1437
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Аддалены файл не навейшы за мясцовы файл \"%s\" -- не выцягваецца.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1444
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr "Аддалены файл навейшы за мясцовы файл \"%s\" -- выцягваецца.\n"

#. Sizes do not match
#: src/ftp.c:1451
#, c-format
msgid ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"
msgstr ""
"Памеры не супадаюць (мясцовы %s) -- выцягваецца.\n"
"\n"

#: src/ftp.c:1469
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Нерэчаісная назва спасылкі; мінаецца.\n"

#: src/ftp.c:1486
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Ужо маецца правільная спасылка %s -> %s\n"
"\n"

#: src/ftp.c:1494
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Стварэньне спасылкі %s -> %s\n"

#: src/ftp.c:1504
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Спасылкі не падтрымліваюцца; мінаецца спасылка \"%s\".\n"

#: src/ftp.c:1516
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Мінаецца тэчка \"%s\".\n"

#: src/ftp.c:1525
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: тып файла не падтрымліваецца або невядомы.\n"

#: src/ftp.c:1552
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: пашкоджаны адбітак часу.\n"

#: src/ftp.c:1580
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr ""

#: src/ftp.c:1630
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr ""

#: src/ftp.c:1696 src/ftp.c:1710
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Адхіленьне \"%s\".\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1758
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Адсутнічаюць супадзеньні з узорам \"%s\".\n"

#: src/ftp.c:1824
#, c-format
msgid "Wrote HTML-ized index to `%s' [%s].\n"
msgstr ""

#: src/ftp.c:1829
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr ""

#: src/getopt.c:670
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: акалічнасьць \"%s\" зьяўляецца неадназначнай\n"

#: src/getopt.c:695
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: акалічнасьць \"--%s\" не дазваляе довады\n"

#: src/getopt.c:700
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: акалічнасьць \"%c%s\" не дазваляе довады\n"

#: src/getopt.c:718 src/getopt.c:891
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: акалічнасьць \"%s\" патрабуе довад\n"

#. --option
#: src/getopt.c:747
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: нераспазнаная акалічнасьць \"--%s\"\n"

#. +option or -option
#: src/getopt.c:751
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: нераспазнаная акалічнасьць \"%c%s\"\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:777
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr ""

#: src/getopt.c:780
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: недапушчальная опцыя -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:810 src/getopt.c:940
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: опцыя патрабуе аргумэнт -- %c\n"

#: src/getopt.c:857
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: опцыя  \"-W %s\" зьяўляецца неадназначнай\n"

#: src/getopt.c:875
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: опцыя \"-W %s\" не дазваляе аргумэнты\n"

#: src/host.c:348
msgid "Unknown host"
msgstr "Невядомы вузел"

#. Message modeled after what gai_strerror returns in similar
#. circumstances.
#: src/host.c:352
msgid "Temporary failure in name resolution"
msgstr ""

#: src/host.c:354
msgid "Unknown error"
msgstr "Невядомая памылка"

#: src/host.c:715
#, c-format
msgid "Resolving %s... "
msgstr "Пошук %s... "

#: src/host.c:762
msgid "failed: No IPv4/IPv6 addresses for host.\n"
msgstr ""

#: src/host.c:785
msgid "failed: timed out.\n"
msgstr "збой: скончыўся час.\n"

#: src/html-url.c:289
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr ""

#: src/html-url.c:696
#, c-format
msgid "%s: Invalid URL %s: %s\n"
msgstr ""

#: src/http.c:368
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Памылка запісу HTTP зварота: %s.\n"

#: src/http.c:737
msgid "No headers, assuming HTTP/0.9"
msgstr "Адсутнічаюць загалоўкі; верагодна, HTTP/0.9"

#: src/http.c:1414
msgid "Disabling SSL due to encountered errors.\n"
msgstr ""

#: src/http.c:1567
#, c-format
msgid "POST data file `%s' missing: %s\n"
msgstr ""

#: src/http.c:1616
#, fuzzy, c-format
msgid "Reusing existing connection to %s:%d.\n"
msgstr "Паўторнае выкарыстаньне далучэньня да %s:%hu.\n"

#: src/http.c:1684
#, c-format
msgid "Failed reading proxy response: %s\n"
msgstr "Памылка чытаньня адказу проксі: %s.\n"

#: src/http.c:1704
#, c-format
msgid "Proxy tunneling failed: %s"
msgstr "Збой проксі-тунэлю: %s"

#: src/http.c:1749
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s зварот дасланы, чакаецца адказ... "

#: src/http.c:1760
msgid "No data received.\n"
msgstr "Даныя не атрыманы.\n"

#: src/http.c:1767
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Памылка чытаньня (%s) у загалоўках.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1813
#, c-format
msgid ""
"File `%s' already there; not retrieving.\n"
"\n"
msgstr ""
"Файл \"%s\" ужо тут і ня будзе выцягвацца.\n"
"\n"

#. If the authentication header is missing or
#. unrecognized, there's no sense in retrying.
#: src/http.c:1966
msgid "Unknown authentication scheme.\n"
msgstr "Невядомая схема аўтарызаваньня.\n"

#: src/http.c:1997
msgid "Authorization failed.\n"
msgstr "Збой аўтарызаваньня.\n"

#: src/http.c:2011
msgid "Malformed status line"
msgstr "Дрэннаскладзены радок стану"

#: src/http.c:2013
msgid "(no description)"
msgstr "(апісаньне адсутнічае)"

#: src/http.c:2076
#, c-format
msgid "Location: %s%s\n"
msgstr "Знаходжаньне: %s%s\n"

#: src/http.c:2077 src/http.c:2184
msgid "unspecified"
msgstr "незаданы"

#: src/http.c:2078
msgid " [following]"
msgstr ""

#. If `-c' is in use and the file has been fully downloaded (or
#. the remote file has shrunk), Wget effectively requests bytes
#. after the end of file and the server response with 416.
#: src/http.c:2134
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    Файл ужо цалкам атрыманы; рабіць нічога ня трэба.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:2164
msgid "Length: "
msgstr "Даўжыня: "

#: src/http.c:2184
msgid "ignored"
msgstr "праігнаравана"

#: src/http.c:2255
#, c-format
msgid "Saving to: `%s'\n"
msgstr "Захаваньне ў \"%s\".\n"

#: src/http.c:2336
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Увага! Узоры не падтрымліваюцца ў HTTP.\n"

#: src/http.c:2383
msgid "Spider mode enabled. Check if remote file exists.\n"
msgstr ""

#: src/http.c:2468
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Немагчыма запісаць у \"%s\" (%s).\n"

#. Another fatal error.
#: src/http.c:2477
msgid "Unable to establish SSL connection.\n"
msgstr "Немагчыма ўсталяваць SSL злучэньне.\n"

#: src/http.c:2485
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ПАМЫЛКА: перанакіраваньне (%d) без знаходжаньня.\n"

#: src/http.c:2531
msgid "Remote file does not exist -- broken link!!!\n"
msgstr ""

#: src/http.c:2536
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ПАМЫЛКА %d: %s.\n"

#: src/http.c:2552
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr ""

#: src/http.c:2560
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""

#: src/http.c:2590
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""

#: src/http.c:2598
#, c-format
msgid "The sizes do not match (local %s) -- retrieving.\n"
msgstr "Памеры не супадаюць (мясцовы %s) -- выцягваем.\n"

#: src/http.c:2605
msgid "Remote file is newer, retrieving.\n"
msgstr "Аддалены файл навейшы, загружаю.\n"

#: src/http.c:2621
#, fuzzy
msgid ""
"Remote file exists and could contain links to other resources -- retrieving.\n"
"\n"
msgstr "Аддалены файл навейшы за мясцовы файл \"%s\" -- выцягваецца.\n"

#: src/http.c:2626
#, fuzzy
msgid ""
"Remote file exists but does not contain any link -- not retrieving.\n"
"\n"
msgstr "Аддалены файл не навейшы за мясцовы файл \"%s\" -- не выцягваецца.\n"

#: src/http.c:2634
#, fuzzy
msgid ""
"Remote file exists but recursion is disabled -- not retrieving.\n"
"\n"
msgstr "Аддалены файл не навейшы за мясцовы файл \"%s\" -- не выцягваецца.\n"

#: src/http.c:2686
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s/%s]\n"
"\n"
msgstr ""
"%s (%s) - `%s' захавана [%s/%s]\n"
"\n"

#: src/http.c:2741
#, c-format
msgid "%s (%s) - Connection closed at byte %s. "
msgstr "%s (%s) - злучэньне закрыта на байце %s. "

#: src/http.c:2756
#, c-format
msgid "%s (%s) - Read error at byte %s (%s)."
msgstr "%s (%s) - памылка чытаньня на байце %s (%s)."

#: src/http.c:2765
#, c-format
msgid "%s (%s) - Read error at byte %s/%s (%s). "
msgstr "%s (%s) - памылка чытаньня на байце %s/%s (%s). "

#: src/init.c:387
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC спасылаецца на %s, але ён(яна) адсутнічае.\n"

#: src/init.c:450 src/netrc.c:267
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Немагчыма прачытаць %s (%s).\n"

#: src/init.c:468
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Памылка ў %s, радок %d.\n"

#: src/init.c:474
#, fuzzy, c-format
msgid "%s: Syntax error in %s at line %d.\n"
msgstr "%s: Памылка ў %s, радок %d.\n"

#: src/init.c:479
#, fuzzy, c-format
msgid "%s: Unknown command `%s' in %s at line %d.\n"
msgstr "%s: ХІБА: невядомая каманда `%s', значэньне `%s'.\n"

#: src/init.c:524
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""

#: src/init.c:677
#, fuzzy, c-format
msgid "%s: Invalid --execute command `%s'\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:722
#, fuzzy, c-format
msgid "%s: %s: Invalid boolean `%s'; use `on' or `off'.\n"
msgstr "%s: %s: Вызначы, калі ласка, уключана (on) ці выключана (off).\n"

#: src/init.c:739
#, fuzzy, c-format
msgid "%s: %s: Invalid number `%s'.\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:970 src/init.c:989
#, fuzzy, c-format
msgid "%s: %s: Invalid byte value `%s'\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:1014
#, fuzzy, c-format
msgid "%s: %s: Invalid time period `%s'\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:1068 src/init.c:1158 src/init.c:1261 src/init.c:1286
#, fuzzy, c-format
msgid "%s: %s: Invalid value `%s'.\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:1105
#, fuzzy, c-format
msgid "%s: %s: Invalid header `%s'.\n"
msgstr "%s: %s: нерэчаісны загад\n"

#: src/init.c:1171
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr ""

#: src/init.c:1230
#, c-format
msgid "%s: %s: Invalid restriction `%s', use [unix|windows],[lowercase|uppercase],[nocontrol].\n"
msgstr ""

#: src/log.c:784
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""

#. Eek!  Opening the alternate log file has failed.  Nothing we
#. can do but disable printing completely.
#: src/log.c:794
#, fuzzy, c-format
msgid ""
"\n"
"%s received.\n"
msgstr "Даньні не атрыманы"

#: src/log.c:795
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr ""

#: src/main.c:358
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Выкарыстаньне: %s [АКАЛІЧНАСЬЦЬ]... [URL]...\n"

#: src/main.c:370
#, fuzzy
msgid ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Довады, абавязкоўвыя для доўгіх выбараў, абавязковыя й для кароткіх.\n"
"\n"

#: src/main.c:372
msgid "Startup:\n"
msgstr "Запуск:\n"

#: src/main.c:374
msgid "  -V,  --version           display the version of Wget and exit.\n"
msgstr ""

#: src/main.c:376
msgid "  -h,  --help              print this help.\n"
msgstr ""

#: src/main.c:378
msgid "  -b,  --background        go to background after startup.\n"
msgstr ""

#: src/main.c:380
msgid "  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
msgstr ""

#: src/main.c:384
msgid "Logging and input file:\n"
msgstr ""

#: src/main.c:386
msgid "  -o,  --output-file=FILE    log messages to FILE.\n"
msgstr ""

#: src/main.c:388
msgid "  -a,  --append-output=FILE  append messages to FILE.\n"
msgstr ""

#: src/main.c:391
msgid "  -d,  --debug               print lots of debugging information.\n"
msgstr ""

#: src/main.c:395
msgid "       --wdebug              print Watt-32 debug output.\n"
msgstr ""

#: src/main.c:398
msgid "  -q,  --quiet               quiet (no output).\n"
msgstr ""

#: src/main.c:400
msgid "  -v,  --verbose             be verbose (this is the default).\n"
msgstr ""

#: src/main.c:402
msgid "  -nv, --no-verbose          turn off verboseness, without being quiet.\n"
msgstr ""

#: src/main.c:404
msgid "  -i,  --input-file=FILE     download URLs found in FILE.\n"
msgstr ""

#: src/main.c:406
msgid "  -F,  --force-html          treat input file as HTML.\n"
msgstr ""

#: src/main.c:408
msgid "  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"
msgstr ""

#: src/main.c:412
msgid "Download:\n"
msgstr ""

#: src/main.c:414
msgid "  -t,  --tries=NUMBER            set number of retries to NUMBER (0 unlimits).\n"
msgstr ""

#: src/main.c:416
msgid "       --retry-connrefused       retry even if connection is refused.\n"
msgstr ""

#: src/main.c:418
msgid "  -O,  --output-document=FILE    write documents to FILE.\n"
msgstr ""

#: src/main.c:420
msgid ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"
msgstr ""

#: src/main.c:423
msgid "  -c,  --continue                resume getting a partially-downloaded file.\n"
msgstr ""

#: src/main.c:425
msgid "       --progress=TYPE           select progress gauge type.\n"
msgstr ""

#: src/main.c:427
msgid ""
"  -N,  --timestamping            don't re-retrieve files unless newer than\n"
"                                 local.\n"
msgstr ""

#: src/main.c:430
msgid "  -S,  --server-response         print server response.\n"
msgstr ""

#: src/main.c:432
msgid "       --spider                  don't download anything.\n"
msgstr ""

#: src/main.c:434
msgid "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"
msgstr ""

#: src/main.c:436
msgid "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"
msgstr ""

#: src/main.c:438
msgid "       --connect-timeout=SECS    set the connect timeout to SECS.\n"
msgstr ""

#: src/main.c:440
msgid "       --read-timeout=SECS       set the read timeout to SECS.\n"
msgstr ""

#: src/main.c:442
msgid "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"
msgstr ""

#: src/main.c:444
msgid "       --waitretry=SECONDS       wait 1..SECONDS between retries of a retrieval.\n"
msgstr ""

#: src/main.c:446
msgid "       --random-wait             wait from 0...2*WAIT secs between retrievals.\n"
msgstr ""

#: src/main.c:448
msgid "  -Y,  --proxy                   explicitly turn on proxy.\n"
msgstr ""

#: src/main.c:450
msgid "       --no-proxy                explicitly turn off proxy.\n"
msgstr ""

#: src/main.c:452
msgid "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"
msgstr ""

#: src/main.c:454
msgid "       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local host.\n"
msgstr ""

#: src/main.c:456
msgid "       --limit-rate=RATE         limit download rate to RATE.\n"
msgstr ""

#: src/main.c:458
msgid "       --no-dns-cache            disable caching DNS lookups.\n"
msgstr ""

#: src/main.c:460
msgid "       --restrict-file-names=OS  restrict chars in file names to ones OS allows.\n"
msgstr ""

#: src/main.c:462
msgid "       --ignore-case             ignore case when matching files/directories.\n"
msgstr ""

#: src/main.c:465
msgid "  -4,  --inet4-only              connect only to IPv4 addresses.\n"
msgstr ""

#: src/main.c:467
msgid "  -6,  --inet6-only              connect only to IPv6 addresses.\n"
msgstr ""

#: src/main.c:469
msgid ""
"       --prefer-family=FAMILY    connect first to addresses of specified family,\n"
"                                 one of IPv6, IPv4, or none.\n"
msgstr ""

#: src/main.c:473
msgid "       --user=USER               set both ftp and http user to USER.\n"
msgstr ""

#: src/main.c:475
msgid "       --password=PASS           set both ftp and http password to PASS.\n"
msgstr ""

#: src/main.c:479
#, fuzzy
msgid "Directories:\n"
msgstr "Каталёг     "

#: src/main.c:481
msgid "  -nd, --no-directories           don't create directories.\n"
msgstr ""

#: src/main.c:483
msgid "  -x,  --force-directories        force creation of directories.\n"
msgstr ""

#: src/main.c:485
msgid "  -nH, --no-host-directories      don't create host directories.\n"
msgstr ""

#: src/main.c:487
msgid "       --protocol-directories     use protocol name in directories.\n"
msgstr ""

#: src/main.c:489
msgid "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"
msgstr ""

#: src/main.c:491
msgid "       --cut-dirs=NUMBER          ignore NUMBER remote directory components.\n"
msgstr ""

#: src/main.c:495
msgid "HTTP options:\n"
msgstr ""

#: src/main.c:497
msgid "       --http-user=USER        set http user to USER.\n"
msgstr ""

#: src/main.c:499
msgid "       --http-password=PASS    set http password to PASS.\n"
msgstr ""

#: src/main.c:501
msgid "       --no-cache              disallow server-cached data.\n"
msgstr ""

#: src/main.c:503
msgid "  -E,  --html-extension        save HTML documents with `.html' extension.\n"
msgstr ""

#: src/main.c:505
msgid "       --ignore-length         ignore `Content-Length' header field.\n"
msgstr ""

#: src/main.c:507
msgid "       --header=STRING         insert STRING among the headers.\n"
msgstr ""

#: src/main.c:509
msgid "       --max-redirect          maximum redirections allowed per page.\n"
msgstr ""

#: src/main.c:511
msgid "       --proxy-user=USER       set USER as proxy username.\n"
msgstr ""

#: src/main.c:513
msgid "       --proxy-password=PASS   set PASS as proxy password.\n"
msgstr ""

#: src/main.c:515
msgid "       --referer=URL           include `Referer: URL' header in HTTP request.\n"
msgstr ""

#: src/main.c:517
msgid "       --save-headers          save the HTTP headers to file.\n"
msgstr ""

#: src/main.c:519
msgid "  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"
msgstr ""

#: src/main.c:521
msgid "       --no-http-keep-alive    disable HTTP keep-alive (persistent connections).\n"
msgstr ""

#: src/main.c:523
msgid "       --no-cookies            don't use cookies.\n"
msgstr ""

#: src/main.c:525
msgid "       --load-cookies=FILE     load cookies from FILE before session.\n"
msgstr ""

#: src/main.c:527
msgid "       --save-cookies=FILE     save cookies to FILE after session.\n"
msgstr ""

#: src/main.c:529
msgid "       --keep-session-cookies  load and save session (non-permanent) cookies.\n"
msgstr ""

#: src/main.c:531
msgid "       --post-data=STRING      use the POST method; send STRING as the data.\n"
msgstr ""

#: src/main.c:533
msgid "       --post-file=FILE        use the POST method; send contents of FILE.\n"
msgstr ""

#: src/main.c:535
msgid "       --no-content-disposition  don't honor Content-Disposition header.\n"
msgstr ""

#: src/main.c:540
msgid "HTTPS (SSL/TLS) options:\n"
msgstr ""

#: src/main.c:542
msgid ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"
msgstr ""

#: src/main.c:545
msgid "       --no-check-certificate   don't validate the server's certificate.\n"
msgstr ""

#: src/main.c:547
msgid "       --certificate=FILE       client certificate file.\n"
msgstr ""

#: src/main.c:549
msgid "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"
msgstr ""

#: src/main.c:551
msgid "       --private-key=FILE       private key file.\n"
msgstr ""

#: src/main.c:553
msgid "       --private-key-type=TYPE  private key type, PEM or DER.\n"
msgstr ""

#: src/main.c:555
msgid "       --ca-certificate=FILE    file with the bundle of CA's.\n"
msgstr ""

#: src/main.c:557
msgid "       --ca-directory=DIR       directory where hash list of CA's is stored.\n"
msgstr ""

#: src/main.c:559
msgid "       --random-file=FILE       file with random data for seeding the SSL PRNG.\n"
msgstr ""

#: src/main.c:561
msgid "       --egd-file=FILE          file naming the EGD socket with random data.\n"
msgstr ""

#: src/main.c:566
msgid "FTP options:\n"
msgstr ""

#: src/main.c:568
msgid "       --ftp-user=USER         set ftp user to USER.\n"
msgstr ""

#: src/main.c:570
msgid "       --ftp-password=PASS     set ftp password to PASS.\n"
msgstr ""

#: src/main.c:572
msgid "       --no-remove-listing     don't remove `.listing' files.\n"
msgstr ""

#: src/main.c:574
msgid "       --no-glob               turn off FTP file name globbing.\n"
msgstr ""

#: src/main.c:576
msgid "       --no-passive-ftp        disable the \"passive\" transfer mode.\n"
msgstr ""

#: src/main.c:578
msgid "       --retr-symlinks         when recursing, get linked-to files (not dir).\n"
msgstr ""

#: src/main.c:580
msgid "       --preserve-permissions  preserve remote file permissions.\n"
msgstr ""

#: src/main.c:584
msgid "Recursive download:\n"
msgstr ""

#: src/main.c:586
msgid "  -r,  --recursive          specify recursive download.\n"
msgstr ""

#: src/main.c:588
msgid "  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
msgstr ""

#: src/main.c:590
msgid "       --delete-after       delete files locally after downloading them.\n"
msgstr ""

#: src/main.c:592
msgid "  -k,  --convert-links      make links in downloaded HTML point to local files.\n"
msgstr ""

#: src/main.c:594
msgid "  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
msgstr ""

#: src/main.c:596
msgid "  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"
msgstr ""

#: src/main.c:598
msgid "  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
msgstr ""

#: src/main.c:600
msgid "       --strict-comments    turn on strict (SGML) handling of HTML comments.\n"
msgstr ""

#: src/main.c:604
msgid "Recursive accept/reject:\n"
msgstr ""

#: src/main.c:606
msgid "  -A,  --accept=LIST               comma-separated list of accepted extensions.\n"
msgstr ""

#: src/main.c:608
msgid "  -R,  --reject=LIST               comma-separated list of rejected extensions.\n"
msgstr ""

#: src/main.c:610
msgid "  -D,  --domains=LIST              comma-separated list of accepted domains.\n"
msgstr ""

#: src/main.c:612
msgid "       --exclude-domains=LIST      comma-separated list of rejected domains.\n"
msgstr ""

#: src/main.c:614
msgid "       --follow-ftp                follow FTP links from HTML documents.\n"
msgstr ""

#: src/main.c:616
msgid "       --follow-tags=LIST          comma-separated list of followed HTML tags.\n"
msgstr ""

#: src/main.c:618
msgid "       --ignore-tags=LIST          comma-separated list of ignored HTML tags.\n"
msgstr ""

#: src/main.c:620
msgid "  -H,  --span-hosts                go to foreign hosts when recursive.\n"
msgstr ""

#: src/main.c:622
msgid "  -L,  --relative                  follow relative links only.\n"
msgstr ""

#: src/main.c:624
msgid "  -I,  --include-directories=LIST  list of allowed directories.\n"
msgstr ""

#: src/main.c:626
msgid "  -X,  --exclude-directories=LIST  list of excluded directories.\n"
msgstr ""

#: src/main.c:628
msgid "  -np, --no-parent                 don't ascend to the parent directory.\n"
msgstr ""

#: src/main.c:632
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Лістуйце паведамленьні аб памылках і пажаданьні на <bug-wget@gnu.org>.\n"

#: src/main.c:637
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "Неінтэрактыўны сеткавы выцягвальнік GNU Wget %s.\n"

#: src/main.c:677
#, fuzzy
msgid "Copyright (C) 2007 Free Software Foundation, Inc.\n"
msgstr "Аўтарскія правы © 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"

#: src/main.c:679
msgid ""
"License GPLv3+: GNU GPL version 3 or later\n"
"<http://www.gnu.org/licenses/gpl.html>.\n"
"This is free software: you are free to change and redistribute it.\n"
"There is NO WARRANTY, to the extent permitted by law.\n"
msgstr ""

#: src/main.c:684
#, fuzzy
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Першы аўтар -- Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:686
msgid "Currently maintained by Micah Cowan <micah@cowan.name>.\n"
msgstr ""

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:733 src/main.c:802 src/main.c:899
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Паспрабуйце \"%s --help\", каб атрымаць больш акалічнасьцяў.\n"

#: src/main.c:799
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: недапушчальная акалічнасьць -- \"-n%c\"\n"

#: src/main.c:854
#, c-format
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Немагчыма адначасова быць падрабязным і маўклівым.\n"

#: src/main.c:860
#, c-format
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""

#: src/main.c:868
#, c-format
msgid "Cannot specify both --inet4-only and --inet6-only.\n"
msgstr ""

#: src/main.c:878
#, c-format
msgid "Cannot specify -r, -p or -N if -O is given.\n"
msgstr ""

#: src/main.c:886
#, c-format
msgid "Cannot specify both -k and -O if multiple URLs are given.\n"
msgstr ""

#. No URL specified.
#: src/main.c:894
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: прапушчаны URL\n"

#: src/main.c:1020
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Ня знойдзены URL у %s.\n"

#: src/main.c:1038
#, c-format
msgid ""
"FINISHED --%s--\n"
"Downloaded: %d files, %s in %s (%s)\n"
msgstr ""
"ЗАВЕРШАНА --%s--\n"
"Выгружана: %d файлаў, %s у %s (%s)\n"

#: src/main.c:1047
#, fuzzy, c-format
msgid "Download quota of %s EXCEEDED!\n"
msgstr "Абмежаваньне выгрузкі (%s байтаў) вычарпана!\n"

#: src/mswindows.c:98
#, c-format
msgid "Continuing in background.\n"
msgstr "Праца працягваецца ў тле.\n"

#: src/mswindows.c:291
#, fuzzy, c-format
msgid "Continuing in background, pid %lu.\n"
msgstr "Праца працягваецца ў тле, pid %d.\n"

#: src/mswindows.c:293 src/utils.c:330
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Вывад будзе скіраваны ў  \"%s\".\n"

#: src/mswindows.c:461 src/mswindows.c:468
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr ""

#: src/netrc.c:375
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""

#: src/netrc.c:406
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr ""

#: src/netrc.c:470
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr ""

#: src/netrc.c:480
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr ""

#. Still not random enough, presumably because neither /dev/random
#. nor EGD were available.  Try to seed OpenSSL's PRNG with libc
#. PRNG.  This is cryptographically weak and defeats the purpose
#. of using OpenSSL, which is why it is highly discouraged.
#: src/openssl.c:113
msgid "WARNING: using a weak random seed.\n"
msgstr ""

#: src/openssl.c:173
msgid "Could not seed PRNG; consider using --random-file.\n"
msgstr ""

#. If the user has specified --no-check-cert, we still want to warn
#. him about problems with the server's certificate.
#: src/openssl.c:488
msgid "ERROR"
msgstr "ПАМЫЛКА"

#: src/openssl.c:488
msgid "WARNING"
msgstr "УВАГА"

#: src/openssl.c:497
#, c-format
msgid "%s: No certificate presented by %s.\n"
msgstr ""

#: src/openssl.c:518
#, c-format
msgid "%s: cannot verify %s's certificate, issued by `%s':\n"
msgstr ""

#: src/openssl.c:526
msgid "  Unable to locally verify the issuer's authority.\n"
msgstr ""

#: src/openssl.c:530
msgid "  Self-signed certificate encountered.\n"
msgstr ""

#: src/openssl.c:533
msgid "  Issued certificate not yet valid.\n"
msgstr ""

#: src/openssl.c:536
msgid "  Issued certificate has expired.\n"
msgstr ""

#: src/openssl.c:568
#, c-format
msgid "%s: certificate common name `%s' doesn't match requested host name `%s'.\n"
msgstr ""

#: src/openssl.c:581
#, c-format
msgid "To connect to %s insecurely, use `--no-check-certificate'.\n"
msgstr ""

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:239
#, c-format
msgid ""
"\n"
"%*s[ skipping %sK ]"
msgstr ""

#: src/progress.c:453
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr ""

#. Translation note: "ETA" is English-centric, but this must
#. be short, ideally 3 chars.  Abbreviate if necessary.
#: src/progress.c:947
#, c-format
msgid "  eta %s"
msgstr ""

#. When the download is done, print the elapsed time.
#. Note to translators: this should not take up more room than
#. available here.  Abbreviate if necessary.
#: src/progress.c:962
msgid "   in "
msgstr ""

#. If no clock was found, it means that clock_getres failed for
#. the realtime clock.
#: src/ptimer.c:160
#, c-format
msgid "Cannot get REALTIME clock frequency: %s\n"
msgstr ""

#: src/recur.c:379
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr ""

#: src/res.c:392
#, c-format
msgid "Cannot open %s: %s"
msgstr "Немагчыма адкрыць %s: %s"

#: src/res.c:544
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Загружаецца robots.txt; калі ласка, не зьвяртайце ўвагі на памылкі.\n"

#: src/retr.c:652
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Памылка разбору URL паўнамоцнага паслужніка %s: %s.\n"

#: src/retr.c:660
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Памылка ў URL паўнамоцнага паслужніка %s: мусіць быць HTTP.\n"

#: src/retr.c:746
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "перавышэньне колькасьці перанакіраваньняў (%d).\n"

#: src/retr.c:881
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Здаемся.\n"
"\n"

#: src/retr.c:881
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Паўтараем спробу.\n"
"\n"

#: src/spider.c:74
msgid ""
"Found no broken links.\n"
"\n"
msgstr ""

#: src/spider.c:81
#, c-format
msgid ""
"Found %d broken link.\n"
"\n"
msgid_plural ""
"Found %d broken links.\n"
"\n"
msgstr[0] ""
msgstr[1] ""

#: src/spider.c:91
#, c-format
msgid "%s\n"
msgstr "%s\n"

#: src/url.c:620
msgid "No error"
msgstr "Памылкі няма"

#: src/url.c:622
msgid "Unsupported scheme"
msgstr "Схема не падтрымліваецца"

#: src/url.c:624
msgid "Invalid host name"
msgstr "Нерэчаісная назва вузла"

#: src/url.c:626
msgid "Bad port number"
msgstr "Кепскі нумар порта"

#: src/url.c:628
msgid "Invalid user name"
msgstr "Нерэчаісная ўліковае імя"

#: src/url.c:630
msgid "Unterminated IPv6 numeric address"
msgstr "Незавершаны адрас IPv6"

#: src/url.c:632
msgid "IPv6 addresses not supported"
msgstr "Адрасы IPv6 не падтрымліваюцца"

#: src/url.c:634
msgid "Invalid IPv6 numeric address"
msgstr "Кепскі адрас IPv6"

#. parent, no error
#: src/utils.c:328
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Праца працягваецца ў тле, pid %d.\n"

#: src/utils.c:376
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Немагчыма выдаліць спасылку \"%s\": %s\n"

#: src/xmalloc.c:63
#, c-format
msgid "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"
msgstr ""

#~ msgid "Error in Set-Cookie, field `%s'"
#~ msgstr "Памылка ў Set-Cookie, поле \"%s\""

#~ msgid "Syntax error in Set-Cookie at character `%c'.\n"
#~ msgstr "Сынтаксычная памылка ў Set-Cookie на знаку \"%c\".\n"

#~ msgid " [%s to go]"
#~ msgstr " [%s засталося]"

#~ msgid "Host not found"
#~ msgstr "Вузел ня знойдзен"

#~ msgid "Failed to set up an SSL context\n"
#~ msgstr "Немагчыма наладзіць кантэкст SSL\n"

#~ msgid "Failed to load certificates from %s\n"
#~ msgstr "Немагчыма загрузіць пасьведчаньні з %s\n"

#~ msgid "Trying without the specified certificate\n"
#~ msgstr "Спроба без заданага пасьведчаньня\n"

#~ msgid "Failed to get certificate key from %s\n"
#~ msgstr "Немагчыма атрымаць ключ пасьведчаньня з %s\n"

#~ msgid "End of file while parsing headers.\n"
#~ msgstr "EOF (канец файла) пад час разбору загалоўкаў.\n"

#~ msgid " (%s to go)"
#~ msgstr " (%s засталося)"

#~ msgid "File `%s' already there, will not retrieve.\n"
#~ msgstr "Файл \"%s\" ужо тутака й ня будзе выцягвацца.\n"

#~ msgid ""
#~ "%s (%s) - `%s' saved [%ld/%ld])\n"
#~ "\n"
#~ msgstr ""
#~ "%s (%s) - `%s' захавана [%ld/%ld])\n"
#~ "\n"

#~ msgid "%s (%s) - Connection closed at byte %ld/%ld. "
#~ msgstr "%s (%s) - Злучэньне закрыта на байце %ld/%ld. "

#~ msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
#~ msgstr "%s: %s: Немагчыма пераўтварыць `%s' у адрас IP.\n"

#~ msgid "%s: %s: Please specify always, on, off, or never.\n"
#~ msgstr "%s: %s: Вызначы, калі ласка, заўжды (always), уключана (on), выключана (off) ці ніколі (never).\n"

#~ msgid ""
#~ "Startup:\n"
#~ "  -V,  --version           display the version of Wget and exit.\n"
#~ "  -h,  --help              print this help.\n"
#~ "  -b,  --background        go to background after startup.\n"
#~ "  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
#~ "\n"
#~ msgstr ""
#~ "Запуск:\n"
#~ "  -V,  --version           адлюстраваць вэрсыю Wget і выйсьці.\n"
#~ "  -h,  --help              надрукаваць гэтую даведку.\n"
#~ "  -b,  --background        перайсьці ў тло пасьля запуску.\n"
#~ "  -e,  --execute=ЗАГАД     выканаць загад у стылі \".wgetrc\".\n"
#~ "\n"

#~ msgid "%s: debug support not compiled in.\n"
#~ msgstr "%s: праграма зкампілявана без падтрымкі адладкі.\n"

#~ msgid ""
#~ "This program is distributed in the hope that it will be useful,\n"
#~ "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
#~ "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
#~ "GNU General Public License for more details.\n"
#~ msgstr ""
#~ "Гэтая праграма разпаўсюджваецца з надзеяй, што яна будзе карыснай,\n"
#~ "але БЕЗЬ НІЯКАЕ ГАРАНТЫІ; нават без гарантыі КАШТОЎНАСЬЦІ ці\n"
#~ "ПРЫДАТНАСЬЦІ ДЛЯ КАНКРЭТНАЕ МЭТЫ. Глядзі падрабязнасьці ў Аснонай\n"
#~ "Публічнай Лцэнзіі GNU (GNU GPL).\n"

#~ msgid "Could not find proxy host.\n"
#~ msgstr "Немагчыма адшукаць вузел паўнамоцнага паслужніка.\n"

#~ msgid "%s: Redirection cycle detected.\n"
#~ msgstr "%s: знойдзены цыкал перанакіроўваньня.\n"

#~ msgid "%s: %s: Not enough memory.\n"
#~ msgstr "%s: %s: нестае памяці.\n"
