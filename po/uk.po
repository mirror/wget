# Ukrainian messages for GNU Wget.
# Copyright (C) 2000 Free Software Foundation, Inc.
# Olexander Kunytsa <xakep@snark.ukma.kiev.ua>, 2000
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.7\n"
"POT-Creation-Date: 2001-06-03 15:27+0200\n"
"PO-Revision-Date: 2001-07-24 14:43+0200\n"
"Last-Translator: Olexander Kunytsa <xakep@snark.ukma.kiev.ua>\n"
"Language-Team: Ukrainian <kick@renome.rovno.ua>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=koi8-u\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/cookies.c:588
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Помилка в куках, поле `%s'"

#: src/cookies.c:612
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Синтаксична помилка в куках, на символ╕ `%c'.\n"

#: src/cookies.c:620
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Синтаксична помилка в куках: неоч╕куваний к╕нець файлу.\n"

#: src/cookies.c:1352
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Не можу в╕дкрити файл з куками `%s': %s\n"

#: src/cookies.c:1364
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Помилка запису в `%s': %s\n"

#: src/cookies.c:1368
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Помилка закриття `%s': %s\n"

#: src/ftp-ls.c:787
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Тип л╕ст╕нго нев╕домий, спроба роз╕брати в стил╕ л╕стингу Unix.\n"

#: src/ftp-ls.c:832 src/ftp-ls.c:834
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Л╕стинг каталогу /%s на %s:%d"

#: src/ftp-ls.c:856
msgid "time unknown       "
msgstr "час нев╕домий      "

#: src/ftp-ls.c:860
msgid "File        "
msgstr "Файл        "

#: src/ftp-ls.c:863
msgid "Directory   "
msgstr "Каталог     "

#: src/ftp-ls.c:866
msgid "Link        "
msgstr "Посилання   "

#: src/ftp-ls.c:869
msgid "Not sure    "
msgstr "Неточно     "

#: src/ftp-ls.c:887
#, c-format
msgid " (%s bytes)"
msgstr " (%s байт)"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:150 src/http.c:624
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Встановлення з'╓днання з %s:%hu... "

#: src/ftp.c:172 src/ftp.c:539 src/http.c:641
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Сервер %s:%hu в╕дмовив у з'╓днанн╕.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:193 src/http.c:652
msgid "connected!\n"
msgstr "п╕д'╓днано!\n"

#: src/ftp.c:194
#, c-format
msgid "Logging in as %s ... "
msgstr "Ре╓стру╓мось як %s ... "

#: src/ftp.c:203 src/ftp.c:256 src/ftp.c:288 src/ftp.c:336 src/ftp.c:429
#: src/ftp.c:481 src/ftp.c:575 src/ftp.c:648 src/ftp.c:709 src/ftp.c:757
msgid "Error in server response, closing control connection.\n"
msgstr "Помилка в реакц╕╖ серверу, закриття керуючого з'╓днання.\n"

#: src/ftp.c:211
msgid "Error in server greeting.\n"
msgstr "Помилка в прив╕танн╕ серверу.\n"

#: src/ftp.c:219 src/ftp.c:345 src/ftp.c:438 src/ftp.c:490 src/ftp.c:585
#: src/ftp.c:658 src/ftp.c:719 src/ftp.c:767
msgid "Write failed, closing control connection.\n"
msgstr "Помилка запису, закриття керуючого з'╓днання.\n"

#: src/ftp.c:226
msgid "The server refuses login.\n"
msgstr "Сервер в╕дмовив у ре╓страц╕╖.\n"

#: src/ftp.c:233
msgid "Login incorrect.\n"
msgstr "╤м'я чи пароль неправильн╕.\n"

#: src/ftp.c:240
msgid "Logged in!\n"
msgstr "Ре╓страц╕я вдалась!\n"

#: src/ftp.c:265
msgid "Server error, can't determine system type.\n"
msgstr "Помилка серверу, не можу визначити тип системи.\n"

#: src/ftp.c:275 src/ftp.c:560 src/ftp.c:632 src/ftp.c:689
msgid "done.    "
msgstr "зроблено.    "

#: src/ftp.c:325 src/ftp.c:459 src/ftp.c:740 src/ftp.c:788 src/url.c:1429
msgid "done.\n"
msgstr "зроблено.\n"

#: src/ftp.c:353
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Нев╕домий тип `%c', закриття керуючого з'╓днання.\n"

#: src/ftp.c:366
msgid "done.  "
msgstr "зроблено.  "

#: src/ftp.c:372
msgid "==> CWD not needed.\n"
msgstr "==> CWD не потр╕бно.\n"

#: src/ftp.c:445
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Каталог `%s' в╕дсутн╕й.\n\n"

#. do not CWD
#: src/ftp.c:463
msgid "==> CWD not required.\n"
msgstr "==> CWD не вимага╓ться.\n"

#: src/ftp.c:497
msgid "Cannot initiate PASV transfer.\n"
msgstr "Не можу ╕н╕ц╕ювати PASV-передачу.\n"

#: src/ftp.c:501
msgid "Cannot parse PASV response.\n"
msgstr "Помилка синтаксичного анал╕зу в╕дпов╕д╕ PASV.\n"

#: src/ftp.c:515
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Спробу╓мо ще з'╓днатися з %s:%hu.\n"

#: src/ftp.c:602
#, c-format
msgid "Bind error (%s).\n"
msgstr "Помилка зв'язування (%s).\n"

#: src/ftp.c:618
msgid "Invalid PORT.\n"
msgstr "Нев╕рний PORT.\n"

#: src/ftp.c:671
#, c-format
msgid "\nREST failed; will not truncate `%s'.\n"
msgstr "\nКоманда REST не вдалась, не обр╕за╓мо `%s'.\n"

#: src/ftp.c:678
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nКоманда REST не вдалась, почина╓мо з нуля.\n"

#: src/ftp.c:727
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Файл `%s' в╕дсутн╕й.\n\n"

#: src/ftp.c:775
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Файл чи каталог `%s' в╕дсутн╕й.\n\n"

#: src/ftp.c:859 src/ftp.c:867
#, c-format
msgid "Length: %s"
msgstr "Довжина: %s"

#: src/ftp.c:861 src/ftp.c:869
#, c-format
msgid " [%s to go]"
msgstr " [%s залишилось]"

#: src/ftp.c:871
msgid " (unauthoritative)\n"
msgstr " (не точно)\n"

#: src/ftp.c:898
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, закриття керуючого з'╓днання.\n"

#: src/ftp.c:906
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - З'╓днання: %s; "

#: src/ftp.c:923
msgid "Control connection closed.\n"
msgstr "Керуюче з'╓днання закрито.\n"

#: src/ftp.c:941
msgid "Data transfer aborted.\n"
msgstr "Передачу даних перервано.\n"

#: src/ftp.c:1005
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Файл `%s' вже ╓ тут, не завантажу╓мо.\n"

#: src/ftp.c:1075 src/http.c:1502
#, c-format
msgid "(try:%2d)"
msgstr "(спроба:%2d)"

#: src/ftp.c:1139 src/http.c:1753
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' збережено [%ld]\n\n"

#: src/ftp.c:1181 src/main.c:810 src/recur.c:483 src/retr.c:566
#, c-format
msgid "Removing %s.\n"
msgstr "Видалення %s.\n"

#: src/ftp.c:1221
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Л╕стинг буде збережено в тимчасовому файл╕ `%s'.\n"

#: src/ftp.c:1233
#, c-format
msgid "Removed `%s'.\n"
msgstr "`%s' видалено.\n"

#: src/ftp.c:1269
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Глибина рекурс╕╖ %d перевищила максимальну глибину %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1330
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Локальний файл `%s' нов╕ший -- не завантажу╓мо його.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1337
#, c-format
msgid "Remote file is newer than local file `%s' -- retrieving.\n\n"
msgstr "Файл `%s' на сервер╕ нов╕ший -- завантажу╓мо.\n\n"

#. Sizes do not match
#: src/ftp.c:1344
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n\n"
msgstr "Довжини файл╕в не сп╕впадають (локально: %ld) -- завантажу╓мо.\n\n"

#: src/ftp.c:1361
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Нев╕рне ╕м'я символьного посилання, пропука╓мо.\n"

#: src/ftp.c:1378
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Символьне посилання %s -> %s вже ╕сну╓.\n\n"

#: src/ftp.c:1386
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Створю╓мо символьне посилання %s -> %s\n"

#: src/ftp.c:1397
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Символьн╕ посилання не п╕дтримуються, пропуска╓мо `%s'.\n"

#: src/ftp.c:1409
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Пропуска╓мо каталог `%s'.\n"

#: src/ftp.c:1418
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: нев╕домий тип файлу (або не п╕дтриму╓ться).\n"

#: src/ftp.c:1445
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: пошкоджена м╕тка часу.\n"

#: src/ftp.c:1466
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Не завантажу╓мо каталоги оск╕льки глибина вже %d (максимум %d).\n"

#: src/ftp.c:1512
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Пропуска╓мо каталог `%s' з╕ списку виключення.\n"

#: src/ftp.c:1559
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Пропуска╓мо `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1606
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Нема╓ сп╕впадань з шаблоном `%s'.\n"

#: src/ftp.c:1671
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Л╕стинг у HTML-формат╕ записано у файл `%s' [%ld].\n"

#: src/ftp.c:1676
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Л╕стинг у HTML-формат╕ записано у файл `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: неоднозначний параметр `%s'\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: параметр `--%s' не може мати аргументу\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: параметр `%c%s' не може мати аргументу\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: параметру `%s' необх╕дний аргумент\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: нерозп╕знаний параметр `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: нерозп╕знаний параметр `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: нев╕рний параметр -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: параметру необх╕дний аргумент -- %c\n"

#: src/host.c:374
msgid "Host not found"
msgstr "Хост не знайдено"

#: src/host.c:376
msgid "Unknown error"
msgstr "Нев╕дома помилка"

#. this is fatal
#: src/http.c:555
msgid "Failed to set up an SSL context\n"
msgstr "Не вдалося встановити SSL\n"

#: src/http.c:561
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "Не вдалося завантажити сертиф╕кат з %s\n"

#: src/http.c:565 src/http.c:573
msgid "Trying without the specified certificate\n"
msgstr "Пробу╓мо без вказаного сертиф╕кату\n"

#: src/http.c:569
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Невдалося отримати ключ-сертиф╕кат з %s\n"

#: src/http.c:663 src/http.c:1593
msgid "Unable to establish SSL connection.\n"
msgstr "Не можу встановити SSL-з'╓днання.\n"

#: src/http.c:671
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Повторне використання зв'язку з %s:%hu.\n"

#: src/http.c:861
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Помилка запису HTTP-запиту: %s.\n"

#: src/http.c:866
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s-запит над╕слано, оч╕ку╓м в╕дпов╕д╕... "

#: src/http.c:910
msgid "End of file while parsing headers.\n"
msgstr "К╕нець файлу п╕д час синтаксичного розбору заголовк╕в.\n"

#: src/http.c:920
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Помилка читання в заголовках (%s).\n"

#: src/http.c:959
msgid "No data received"
msgstr "Не отримано даних"

#: src/http.c:961
msgid "Malformed status line"
msgstr "Несформований статусний рядок"

#: src/http.c:966
msgid "(no description)"
msgstr "(без опису)"

#: src/http.c:1089
msgid "Authorization failed.\n"
msgstr "Авторизац╕я невдалася.\n"

#: src/http.c:1096
msgid "Unknown authentication scheme.\n"
msgstr "Нев╕дома схема аутентиф╕кац╕╖.\n"

#: src/http.c:1136
#, c-format
msgid "Location: %s%s\n"
msgstr "Адресa: %s%s\n"

#: src/http.c:1137 src/http.c:1269
msgid "unspecified"
msgstr "не вказано"

#: src/http.c:1138
msgid " [following]"
msgstr " [перех╕д]"

#: src/http.c:1200
msgid "\n    The file is already fully retrieved; nothing to do.\n\n"
msgstr "\n    Файл вже повн╕стю завантажено; нема чого робити.\n\n"

#: src/http.c:1216
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Невдача в╕дновлення завантаженяя файлу, конфл╕кт з параметром `-c'.\n"
"В╕дмова в╕д обр╕зання ╕снуючого файлу `%s'.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1259
msgid "Length: "
msgstr "Довжина: "

#: src/http.c:1264
#, c-format
msgid " (%s to go)"
msgstr " (%s залишилось)"

#: src/http.c:1269
msgid "ignored"
msgstr "╕гнору╓ться"

#: src/http.c:1399
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Увага: в HTTP не п╕дтримуються шаблони.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1417
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Файл `%s' вже ╓ тут, не завантажу╓мо його.\n"

#: src/http.c:1585
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Помилка запису в `%s' (%s).\n"

#: src/http.c:1602
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ПОМИЛКА: Перенаправлення (%d) без вказування адреси.\n"

#: src/http.c:1630
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ПОМИЛКА %d: %s.\n"

#: src/http.c:1642
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "В╕дсутн╕й заголовок last-modified -- м╕тки часу вимкнено.\n"

#: src/http.c:1650
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Некоректний заголовок last-modified -- ╕гнору╓мо м╕тки часу.\n"

#: src/http.c:1673
#, c-format
msgid "Server file no newer than local file `%s' -- not retrieving.\n\n"
msgstr "Локальний файл `%s' нов╕ший -- не завантажу╓мо його.\n\n"

#: src/http.c:1680
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Довжини файл╕в не сп╕впадають (локально: %ld) -- завантажу╓мо.\n"

#: src/http.c:1684
msgid "Remote file is newer, retrieving.\n"
msgstr "Файл нов╕ший, н╕ж локальний, завантажу╓мо.\n"

#: src/http.c:1728
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' збережено [%ld/%ld]\n\n"

#: src/http.c:1774
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - З'╓днання закрито в позиц╕╖ %ld. "

#: src/http.c:1782
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' збережено [%ld/%ld]\n\n"

#: src/http.c:1801
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - З'╓днання закрито в позиц╕╖ %ld/%ld. "

#: src/http.c:1812
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Помилка читання в позиц╕╖ %ld (%s)."

#: src/http.c:1820
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Помилка читання в позиц╕╖ %ld/%ld (%s). "

#: src/init.c:349 src/netrc.c:267
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Неможливо прочитати %s (%s).\n"

#: src/init.c:367 src/init.c:373
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Помилка в %s (рядок %d).\n"

#: src/init.c:405
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Увага: Як системний wgetrc так ╕ wgetrc користувача вказують на `%s'.\n"

#: src/init.c:497
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: ПОМИЛКА: нев╕дома команда `%s', значення `%s'.\n"

#: src/init.c:529
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: Не можу перетворити `%s' на ip-адресу.\n"

#: src/init.c:559
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Будь-ласка вкаж╕ть on чи off.\n"

#: src/init.c:603
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Будь-ласка вкаж╕ть always, on, off чи never.\n"

#: src/init.c:622 src/init.c:919 src/init.c:941 src/init.c:1005
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Неправильне вказання `%s'.\n"

#: src/init.c:775 src/init.c:797 src/init.c:819 src/init.c:845
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Неправильне вказання `%s'.\n"

#: src/main.c:120
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Використання: %s [ПАРАМЕТР]... [URL]...\n"

#: src/main.c:128
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, Автоматичний завантажувач файл╕в з мереж╕.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:133
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\n'Довг╕' параметри сприймають т╕ ж аргументи, що ╕ коротк╕.\n\n"

#: src/main.c:137
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Запуск:\n"
"  -V,  --version           показати верс╕ю Wget.\n"
"  -h,  --help              вивести цю п╕дказку.\n"
"  -b,  --background        перейти в фоновий режим п╕сля запуску.\n"
"  -e,  --execute=КОМАНДА   виконати команду типу `.wgetrc'.\n"
"\n"

#: src/main.c:144
msgid ""
"Logging and input file:\n"
"  -o,  --output-file=FILE     log messages to FILE.\n"
"  -a,  --append-output=FILE   append messages to FILE.\n"
"  -d,  --debug                print debug output.\n"
"  -q,  --quiet                quiet (no output).\n"
"  -v,  --verbose              be verbose (this is the default).\n"
"  -nv, --non-verbose          turn off verboseness, without being quiet.\n"
"  -i,  --input-file=FILE      download URLs found in FILE.\n"
"  -F,  --force-html           treat input file as HTML.\n"
"  -B,  --base=URL             prepends URL to relative links in -F -i file.\n"
"       --sslcertfile=FILE     optional client certificate.\n"
"       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n"
"\n"
msgstr ""
"Протоколювання та вх╕дний файл:\n"
"  -o,  --output-file=ФАЙЛ     записувати пов╕домлення у ФАЙЛ.\n"
"  -a,  --append-output=ФАЙЛ   додавати пов╕домлення до ФАЙЛу.\n"
"  -d,  --debug                друкувати в╕длагоджувальн╕ пов╕домлення.\n"
"  -q,  --quiet                працювати без виведення пов╕домлень.\n"
"  -v,  --verbose              багатосл╕вне виведення (за змовчанням).\n"
"  -nv, --non-verbose          вимкнути багатосл╕вн╕сть.\n"
"  -i,  --input-file=ФАЙЛ      читати URL з файлу.\n"
"  -F,  --force-html           трактувати вх╕дний файл як HTML.\n"
"  -B,  --base=URL             додавати URL до в╕дносних посилань у -F -i файл╕.\n"
"       --sslcertfile=FILE     опц╕онально сертиф╕кат кл╕╓нта.\n"
"       --sslcertkey=KEYFILE   опц╕онально ключ для цього сертиф╕кату.\n"
"\n"

#: src/main.c:158
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""
"Скачування:\n"
"       --bind-address=АДРЕСА    прив'язка до локально╖ адреси.\n"
"  -t,  --tries=ЧИСЛО            обмежити к╕льк╕сть спроб (0 - безл╕ч).\n"
"  -O   --output-document=ФАЙЛ   записувати документи у ФАЙЛ.\n"
"  -nc, --no-clobber             не перезаписувати ╕снуюч╕ файли або + суф╕кс .#\n"
"  -c,  --continue               довантажувати ╕снуючий файл.\n"
"       --dot-style=СТИЛЬ        встановити СТИЛЬ в╕дображення прогресу.\n"
"  -N,  --timestamping           не завантажувати файли, як╕ старш╕, н╕ж локальн╕.\n"
"  -S,  --server-response        друкувати в╕дпов╕дь серверу.\n"
"       --spider                 н╕чого не завантажувати.\n"
"  -T,  --timeout=СЕКУНДИ        обмежити час оч╕кування в╕дпов╕д╕.\n"
"  -w,  --wait=СЕКУНДИ           встановити затримку м╕ж завантаженнями.\n"
"       --waitretry=СЕКУНДИ      зачекати 1...СЕКУНД м╕ж спробами отримання.\n"
"  -Y,  --proxy=on/off           перемикач використання прокс╕.\n"
"  -Q,  --quota=БАЙТИ            обмежити загальний об'╓м файл╕в.\n"
"\n"

#: src/main.c:175
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Каталоги:\n"
"  -nd  --no-directories            не створювати каталоги.\n"
"  -x,  --force-directories         примусове створення каталог╕в.\n"
"  -nH, --no-host-directories       не створювати каталоги з ╕менами хост╕в.\n"
"  -P,  --directory-prefix=ПРЕФ╤КС  збер╕гати файли в ПРЕФ╤КС/...\n"
"       --cut-dirs=ЧИСЛО            ╕гнорувати певне ЧИСЛО компонент╕в каталогу.\n"
"\n"

#: src/main.c:183
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\n"
"  -E,  --html-extension      save all text/html documents with .html extension.\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"       --referer=URL         include `Referer: URL' header in HTTP request.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"       --no-http-keep-alive  disable HTTP keep-alive (persistent connections).\n"
"       --cookies=off         don't use cookies.\n"
"       --load-cookies=FILE   load cookies from FILE before session.\n"
"       --save-cookies=FILE   save cookies to FILE after session.\n"
"\n"
msgstr ""
"Параметри HTTP:\n"
"       --http-user=╤М'Я      визначити ╤М'Я http-користувача.\n"
"       --http-passwd=ПАРОЛЬ  визначити ПАРОЛЬ для http-запит╕в.\n"
"  -C,  --cache=on/off        дозволити/н╕ дан╕, кешован╕ на сервер╕.\n"
"  -E,  --html-extension      записувати вс╕ файли text/html з розширенням .html\n"
"       --ignore-length       ╕гнорувати поле заголовку `Content-Length'.\n"
"       --header=РЯДОК        вставляти РЯДОК в HTTP-заголовки.\n"
"       --proxy-user=╤М'Я     визначити ╤М'Я користувача для прокс╕-серверу.\n"
"       --proxy-passwd=ПАРОЛЬ визначити ПАРОЛЬ для прокс╕-серверу.\n"
"       --referer=URL         включити `Referer: URL' заголовок в HTTP-запит.\n"
"  -s,  --save-headers        записувати HTTP-заголовки у файл.\n"
"  -U,  --user-agent=АГЕНТ    задати ╕м'я АГЕНТу зам╕сть Wget/ВЕРС╤Я.\n"
"       --no-http-keep-alive  заборонити HTTP keep-alive (потс╕йн╕ з'╓днання).\n"
"       --cookies=off         не використовувати куки.\n"
"       --load-cookies=FILE   перед сес╕╓ю брати куки з ФАЙЛу.\n"
"       --save-cookies=FILE   в к╕нц╕ сес╕╖ записати куки у ФАЙЛ.\n"
"\n"

#: src/main.c:201
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"Параметри FTP:\n"
"  -nr, --dont-remove-listing не видаляти файли `.listing'.\n"
"  -g,  --glob=on/off         перемикач роботи з шаблонами ╕мен файл╕в.\n"
"       --passive-ftp         використовувати \"пасивний\" тип передач╕.\n"
"       --retr-symlinks       завантажувати з FTP символ╕чн╕ посилання.\n"
"\n"

#: src/main.c:208
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive          recursive web-suck -- use with care!\n"
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
"       --delete-after       delete files locally after downloading them.\n"
"  -k,  --convert-links      convert non-relative links to relative.\n"
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
"  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n"
"  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
"\n"
msgstr ""
"Рекурсивне завантаження:\n"
"  -r,  --recursive             рекурсивний режим -- будьте обережн╕!\n"
"  -l,  --level=ЧИСЛО           макс. глибина рекурс╕╖ (0 - без обеження).\n"
"       --delete-after          локально видалити отриман╕ файли.\n"
"  -k,  --convert-links         перетворювати посилання в╕дносн╕.\n"
"  -K,  --backup-converted      збер╕гати стар╕ файли перед конвертац╕╓ю.\n"
"  -m,  --mirror                ув╕мкнути режими, корисн╕ для задзеркалення.\n"
"  -p,  --page-requisites       отримувати вс╕ файли для повного збереження HTML\n"
"\n"

#: src/main.c:218
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                comma-separated list of accepted extensions.\n"
"  -R,  --reject=LIST                comma-separated list of rejected extensions.\n"
"  -D,  --domains=LIST               comma-separated list of accepted domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected domains.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"       --follow-tags=LIST           comma-separated list of followed HTML tags.\n"
"  -G,  --ignore-tags=LIST           comma-separated list of ignored HTML tags.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -L,  --relative                   follow relative links only.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Рекурсивне включення/виключення файл╕в:\n"
"  -A,  --accept=СПИСОК               список розширень на включення.\n"
"  -R,  --reject=СПИСОК               список розширень на виключення.\n"
"  -D,  --domains=СПИСОК              список дозволених домен╕в.\n"
"       --exclude-domains=СПИСОК      через кому список домен╕в, як╕ виключати.\n"
"  -L,  --relative                    переходити лише за в╕дносними посиланнями.\n"
"       --follow-ftp                  йти за FTP-посиланнями в HTML-документах.\n"
"       --follow-tags=СПИСОК          HTML тег╕в через кому, за якими можна йти.\n"
"  -G,  --ignore-tags=СПИСОК          HTML тег╕в через кому, як╕ треба ╕гнор.\n"
"  -H,  --span-hosts                  переходити на ╕нш╕ хости п╕д час рекурс╕╖.\n"
"  -L,  --relative                    йти лиш за в╕дносними посиланнями.\n"
"  -I,  --include-directories=СПИСОК  список дозволених каталог╕в.\n"
"  -X,  --exclude-directories=СПИСОК  список каталог╕в на виключення.\n"
"  -nh, --no-host-lookup              не визначати DNS-╕мена хост╕в.\n"
"  -np, --no-parent                   не п╕дн╕матися в батьк╕вский каталог.\n"
"\n"

#: src/main.c:234
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Пов╕домлення про помилки та пропозиц╕╖ надсилайте до <bug-wget@gnu.org>.\n"

#: src/main.c:420
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: п╕дтримку в╕длагодження не вкомп╕льовано.\n"

#: src/main.c:472
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995-2001 Фундац╕я В╕льного Програмного Забезпечення.\n"
"Ця програма поширю╓ться з над╕╓ю, що вона буде корисною,\n"
"але БЕЗ БУДЬ-ЯКИХ ГАРАНТ╤Й; нав╕ть без гарант╕╖ КОРИСНОСТ╤\n"
"чи ПРИДАТНОСТ╤ ДЛЯ ПЕВНО╥ КОНКРЕТНО╥ МЕТИ. Див╕ться\n"
"GNU General Public License для отримання детальн╕шо╖ ╕нформац╕╖.\n"

#: src/main.c:478
msgid "\nOriginally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr "\nАвтор: Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:569
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: нев╕рна команда\n"

#: src/main.c:625
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: нев╕рний параметр -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:628 src/main.c:670 src/main.c:728
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Спробуйте `%s --help' для отримання детально╖ ╕нформац╕╖.\n"

#: src/main.c:708
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Режими verbose та quiet не можна використовувати одночасно.\n"

#: src/main.c:714
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Режими п╕дтримки м╕ток часу та збереження старих файл╕в несум╕сн╕.\n"

#. No URL specified.
#: src/main.c:723
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: не вказано URL\n"

#: src/main.c:825
#, c-format
msgid "No URLs found in %s.\n"
msgstr "В %s не знайдено URL'╕в.\n"

#: src/main.c:834
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"ЗАК╤НЧЕНО --%s--\n"
"Скачано: %s байт╕в в %d файлах(╕)\n"

#: src/main.c:842
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "ВИЧЕРПАНО обмеження на завантаження (%s байт╕в)!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:876
#, c-format
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "отримано %s, перенаправлю╓мо виведення в `%%s'.\n"

#: src/mswindows.c:89
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Отримано CTRL+Break, виведення перенаправля╓мо в `%s'.\n"
"Виконання буде продовжено на тл╕.\n"
"Натиснувши CTRL+ALT+DELETE Ви зможете зупинити Wget.\n"

#. parent, no error
#: src/mswindows.c:106 src/utils.c:458
msgid "Continuing in background.\n"
msgstr "Продовжу╓мо у фоновому режим╕.\n"

#: src/mswindows.c:108 src/utils.c:460
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Виведення буде записано до `%s'.\n"

#: src/mswindows.c:188
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Запуска╓мо WinHelp %s\n"

#: src/mswindows.c:215 src/mswindows.c:222
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Не можу знайти потр╕бний драйвер.\n"

#: src/netrc.c:367
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: попередження: лексема \"%s\" перед ╕менем машини\n"

#: src/netrc.c:398
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: нев╕дома лексема \"%s\"\n"

#: src/netrc.c:462
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Використання: %s NETRC [╤М'Я МАШИНИ]\n"

#: src/netrc.c:472
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: не можу виконати stat %s: %s\n"

#: src/recur.c:484
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Видяля╓мо %s, оск╕льки його треба пропустити.\n"

#: src/recur.c:679
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Завантажу╓мо файл robots.txt; не зважайте на помилки.\n"

#: src/retr.c:227
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ пропуск %dK ]"

#: src/retr.c:373
msgid "Could not find proxy host.\n"
msgstr "Не знайдено прокс╕-сервер.\n"

#: src/retr.c:387
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Прокс╕-сервер %s ма╓ бути HTTP.\n"

#: src/retr.c:481
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Зациклення перенаправлення.\n"

#: src/retr.c:587
msgid "Giving up.\n\n"
msgstr "Авар╕йне завершення.\n\n"

#: src/retr.c:587
msgid "Retrying.\n\n"
msgstr "Продовження спроб.\n\n"

#: src/url.c:1329
#, c-format
msgid "Converting %s... "
msgstr "Перетворення %s... "

#: src/url.c:1342
msgid "nothing to do.\n"
msgstr "нема чого робити.\n"

#: src/url.c:1350 src/url.c:1374
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Не можу перетворити посилання в %s: %s\n"

#: src/url.c:1365
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Не можу видалити `%s': %s\n"

#: src/url.c:1555
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Не можу зберегти коп╕ю %s п╕д ╕менем %s: %s\n"

#: src/utils.c:94
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Недостатньо пам'ят╕.\n"

#: src/utils.c:417
msgid "Unknown/unsupported protocol"
msgstr "Протокол нев╕домий чи не п╕дтриму╓ться"

#: src/utils.c:420
msgid "Invalid port specification"
msgstr "Неправильний номер порту"

#: src/utils.c:423
msgid "Invalid host name"
msgstr "Неправильне ╕м'я машини"

#: src/utils.c:620
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Не вдалося видалити символьне посилання `%s': %s\n"
