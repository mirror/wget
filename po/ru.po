# Russian messages for GNU Wget.
# Copyright (C) 1998, 1999, 2000 Free Software Foundation, Inc.
# Const Kaplinsky <const@ce.cctpu.edu.ru>, 1998, 1999, 2000.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.4\n"
"POT-Creation-Date: 2000-10-20 00:07-0700\n"
"PO-Revision-Date: 2000-09-18 01:16+08:00\n"
"Last-Translator: Const Kaplinsky <const@ce.cctpu.edu.ru>\n"
"Language-Team: Russian <ru@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=koi8-r\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:348
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Установка соединения с %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:365
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Сервер %s:%hu отклонил соединение.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:376
msgid "connected!\n"
msgstr "соединились!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Регистрация под именем %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Ошибка в реакции сервера, закрытие управляющего соединения.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Ошибка в приветствии сервера.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Ошибка записи, закрытие управляющего соединения.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Сервер отклонил регистрацию.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Недопустимое имя или пароль.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Регистрация прошла успешно!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Неизвестный тип `%c', закрытие управляющего соединения.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "сделано.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD не нужна.\n"

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Отсутствует каталог `%s'.\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1523
msgid "done.\n"
msgstr "сделано.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD не требуется.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Не удается начать PASV-передачу.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Ошибка синтаксического разбора ответа PASV.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Попытки соединения с %s:%hu будут продолжены.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "сделано.    "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Ошибка bind (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Недопустимый PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"Команда REST не выполнена, повтор с нулевой позиции.\n"

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Отсутствует файл `%s'.\n"
"\n"

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Отсутствует файл или каталог `%s'.\n"
"\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Длина: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [осталось %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (не достоверно)\n"

#: src/ftp.c:729
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, закрытие управляющего соединения.\n"

#: src/ftp.c:737
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Соединение: %s; "

#: src/ftp.c:754
msgid "Control connection closed.\n"
msgstr "Управляющее соединение закрыто.\n"

#: src/ftp.c:772
msgid "Data transfer aborted.\n"
msgstr "Передача данных прервана.\n"

#: src/ftp.c:838
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Файл `%s' уже существует, получать не требуется.\n"

#: src/ftp.c:915 src/http.c:1016
#, c-format
msgid "(try:%2d)"
msgstr "(попытка:%2d)"

#: src/ftp.c:979 src/http.c:1236
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' сохранен [%ld]\n"
"\n"

#: src/ftp.c:1025
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Листинг будет сохранен во временном файле `%s'.\n"

#: src/ftp.c:1037
#, c-format
msgid "Removed `%s'.\n"
msgstr "Удален `%s'.\n"

#: src/ftp.c:1073
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Глубина рекурсии %d превысила максимальную глубину %d.\n"

#: src/ftp.c:1125 src/http.c:1163
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr "Файл на сервере не новее локального файла `%s' -- пропуск.\n"

#: src/ftp.c:1131 src/http.c:1171
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Размеры файлов не совпадают (локальный размер %ld) -- получение.\n"

#: src/ftp.c:1148
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Недопустимое имя символьной ссылки, пропущено.\n"

#: src/ftp.c:1165
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Корректная ссылка %s -> %s уже существует.\n"
"\n"

#: src/ftp.c:1173
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Создание символьной ссылки %s -> %s\n"

#: src/ftp.c:1184
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Символьные ссылки не поддерживаются, пропуск `%s'.\n"

#: src/ftp.c:1196
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Пропуск каталога `%s'.\n"

#: src/ftp.c:1205
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: тип файла неизвестен или не поддерживается.\n"

#: src/ftp.c:1222
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: неверное время изменения файла.\n"

#: src/ftp.c:1243
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Каталоги не будут получены, глубина составляет %d (максимум %d).\n"

#: src/ftp.c:1282
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Каталог `%s' пропущен, так как находится в списке исключенных.\n"

#: src/ftp.c:1327
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Пропуск `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1374
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Нет совпадений с шаблоном `%s'.\n"

#: src/ftp.c:1434
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Листинг в формате HTML записан в файл `%s' [%ld].\n"

#: src/ftp.c:1439
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Листинг в формате HTML записан в файл `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: ключ `%s' недопустим в данном контексте\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: ключ `--%s' не позволяет задавать аргумент\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: ключ `%c%s' не позволяет задавать аргумент\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: ключ `%s' требует указания аргумента\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: нераспознанный ключ `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: нераспознанный ключ `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: недопустимый ключ командной строки -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: ключ требует указания аргумента -- %c\n"

#: src/host.c:437
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Не удается определить идентификатор пользователя.\n"

#: src/host.c:449
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Предупреждение: неудачный вызов uname: %s\n"

#: src/host.c:461
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Предупреждение: неудачный вызов gethostname\n"

#: src/host.c:489
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Предупреждение: ошибка определения локального IP-адреса.\n"

#: src/host.c:503
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr ""
"%s: Предупреждение: ошибка обратного преобразования локального IP-адреса.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:516
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Предупреждение: при обратном преобразовании IP-адреса не получено FQDN!\n"

#: src/host.c:544
msgid "Host not found"
msgstr "Хост не найден"

#: src/host.c:546
msgid "Unknown error"
msgstr "Неизвестная ошибка"

#: src/html.c:539 src/html.c:541
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Листинг каталога /%s на %s:%d"

#: src/html.c:563
msgid "time unknown       "
msgstr "время неизвестно   "

#: src/html.c:567
msgid "File        "
msgstr "Файл        "

#: src/html.c:570
msgid "Directory   "
msgstr "Каталог     "

#: src/html.c:573
msgid "Link        "
msgstr "Ссылка      "

#: src/html.c:576
msgid "Not sure    "
msgstr "Неизвестно  "

#: src/html.c:594
#, c-format
msgid " (%s bytes)"
msgstr " (%s байт)"

#: src/http.c:508
msgid "Failed writing HTTP request.\n"
msgstr "Ошибка записи запроса HTTP.\n"

#: src/http.c:512
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "Запрос %s послан, ожидание ответа... "

#: src/http.c:551
msgid "End of file while parsing headers.\n"
msgstr "Конец файла во время разбора заголовков.\n"

#: src/http.c:562
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Ошибка чтения (%s) в заголовках.\n"

#: src/http.c:602
msgid "No data received"
msgstr "Не получено никаких данных"

#: src/http.c:604
msgid "Malformed status line"
msgstr "Неполная строка статуса"

#: src/http.c:609
msgid "(no description)"
msgstr "(нет описания)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:693
msgid "Authorization failed.\n"
msgstr "Авторизация прошла неудачно.\n"

#: src/http.c:700
msgid "Unknown authentication scheme.\n"
msgstr "Неизвестная схема проверки полномочий.\n"

#: src/http.c:783
#, c-format
msgid "Location: %s%s\n"
msgstr "Адрес: %s%s\n"

#: src/http.c:784 src/http.c:809
msgid "unspecified"
msgstr "нет информации"

#: src/http.c:785
msgid " [following]"
msgstr " [переход]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:799
msgid "Length: "
msgstr "Длина: "

#: src/http.c:804
#, c-format
msgid " (%s to go)"
msgstr " (осталось %s)"

#: src/http.c:809
msgid "ignored"
msgstr "игнорируется"

#: src/http.c:903
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Предупреждение: в HTTP шаблоны не поддерживаются.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:924
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Файл `%s' уже существует, получение не производится.\n"

#: src/http.c:1083
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Ошибка записи в `%s' (%s).\n"

#: src/http.c:1094
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ОШИБКА: Перенаправление (%d) без указания адреса.\n"

#: src/http.c:1119
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ОШИБКА %d: %s.\n"

#: src/http.c:1132
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Нет заголовка last-modified -- временные отметки выключены.\n"

#: src/http.c:1140
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""
"Заголовок last-modified некорректен -- временные отметки игнорируются.\n"

#: src/http.c:1175
msgid "Remote file is newer, retrieving.\n"
msgstr "Файл новее локального, получение.\n"

#: src/http.c:1210
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' сохранен [%ld/%ld]\n"
"\n"

#: src/http.c:1258
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Соединение закрыто, позиция %ld. "

#: src/http.c:1266
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' сохранен [%ld/%ld])\n"
"\n"

#: src/http.c:1286
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Соединение закрыто, позиция %ld/%ld. "

#: src/http.c:1297
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Ошибка чтения, позиция %ld (%s)."

#: src/http.c:1305
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Ошибка чтения, позиция %ld/%ld (%s). "

#: src/init.c:320 src/netrc.c:260
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Ошибка чтения %s (%s).\n"

#: src/init.c:341 src/init.c:347
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Ошибка в %s в строке %d.\n"

#: src/init.c:378
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""
"%s: Предупреждение: системный и пользовательский wgetrc указывают на `%s'.\n"

#: src/init.c:466
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: ОШИБКА В ПРОГРАММЕ: неизвестная команда `%s', значение `%s'.\n"

#: src/init.c:493
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Пожалуйста, укажите on или off.\n"

#: src/init.c:537
#, fuzzy, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Пожалуйста, укажите on или off.\n"

#: src/init.c:556 src/init.c:813 src/init.c:835 src/init.c:908
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Недопустимое описание `%s'.\n"

#: src/init.c:669 src/init.c:691 src/init.c:713 src/init.c:739
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Недопустимое описание `%s'\n"

#: src/main.c:105
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Использование: %s [КЛЮЧ]... [URL]...\n"

#: src/main.c:113
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, программа автоматического получения файлов по сети.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:118
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Короткие ключи требуют указания тех же аргументов, что и длинные ключи.\n"
"\n"

#: src/main.c:121
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Запуск:\n"
"  -V,  --version           отобразить версию Wget и выйти.\n"
"  -h,  --help              вывести данную подсказку.\n"
"  -b,  --background        перейти в фоновый режим после запуска.\n"
"  -e,  --execute=КОМАНДА   выполнить команду в стиле `.wgetrc'.\n"
"\n"

#: src/main.c:127
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
"\n"
msgstr ""
"Ведение протоколов и входные файлы:\n"
"  -o,  --output-file=ФАЙЛ     направлять сообщения в указанный ФАЙЛ.\n"
"  -a,  --append-output=ФАЙЛ   добавлять сообщения в конец ФАЙЛА.\n"
"  -d,  --debug                выводить отладочную информацию.\n"
"  -q,  --quiet                тихий режим (не выводить ничего).\n"
"  -v,  --verbose              быть многословной (включено по умолчанию).\n"
"  -nv, --non-verbose          быть немногословной.\n"
"  -i,  --input-file=ФАЙЛА     читать адреса URL из ФАЙЛА.\n"
"  -F,  --force-html           обрабатывать входной файл как HTML.\n"
"  -B,  --base=URL             добавлять URL к относительнымм ссылкам при\n"
"                              использовании ключей -F -i.\n"
"\n"

#: src/main.c:138
msgid ""
"Download:\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 "
"unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# "
"suffixes.\n"
"  -c,  --continue               restart getting an existing file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't retrieve files if older than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS\twait 1...SECONDS between retries of a "
"retrieval.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""
"Получение файлов:\n"
"  -t,  --tries=ЧИСЛО            указать ЧИСЛО попыток (0 -- бесконечность).\n"
"  -O   --output-document=ФАЙЛ   записывать документы в ФАЙЛ.\n"
"  -nc, --no-clobber             не получать существующие файлы повторно.\n"
"  -c,  --continue               продолжать получение существующих файлов.\n"
"       --dot-style=СТИЛЬ        установить СТИЛЬ отображения прогресса.\n"
"  -N,  --timestamping           не замещать имеющиеся файлы более ранними.\n"
"  -S,  --server-response        выводить ответ сервера.\n"
"       --spider                 не запрашивать реального получения файлов.\n"
"  -T,  --timeout=СЕКУНДЫ        ограничить время ожидания при приеме "
"данных.\n"
"  -w,  --wait=СЕКУНДЫ           установить паузу между получением файлов.\n"
"       --waitretry=СЕКУНДЫ      пауза 0..СЕКУНДЫ между повторными "
"попытками.\n"
"  -Y,  --proxy=on/off           включить или выключить поддержку proxy.\n"
"  -Q,  --quota=ЧИСЛО            ограничить суммарный объем получаемых "
"файлов.\n"
"\n"

#: src/main.c:153
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
"Каталоги:\n"
"  -nd  --no-directories            не создавать каталоги.\n"
"  -x,  --force-directories         создавать все недостающие каталоги.\n"
"  -nH, --no-host-directories       не создавать каталоги с именами хостов.\n"
"  -P,  --directory-prefix=PREFIX   сохранять файлы в PREFIX/...\n"
"       --cut-dirs=ЧИСЛО            усечь заданное ЧИСЛО компонент каталога.\n"
"\n"

#: src/main.c:160
#, fuzzy
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally "
"allowed).\n"
"  -E,  --html-extension      save all text/html documents with .html "
"extension.\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"       --referer=URL         include `Referer: URL' header in HTTP request.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"\n"
msgstr ""
"Параметры HTTP:\n"
"       --http-user=ИМЯ        установить ИМЯ пользователя для "
"http-запросов.\n"
"       --http-passwd=ПАРОЛЬ   установить ПАРОЛЬ для http-запросов.\n"
"  -C,  --cache=on/off         включить/выключить кеширование на сервере.\n"
"       --ignore-length        игнорировать поле заголовка `Content-Length'.\n"
"       --header=СТРОКА        вставить СТРОКУ в заголовки HTTP.\n"
"       --proxy-user=ИМЯ       установить ИМЯ пользователя для "
"прокси-сервера.\n"
"       --proxy-passwd=ПАРОЛЬ  установить ПАРОЛЬ для прокси-сервера.\n"
"       --referer=URL          включить заголовок `Referer: URL' в запрос "
"HTTP.\n"
"  -s,  --save-headers         сохранять заголовки HTTP в файл.\n"
"  -U,  --user-agent=СТРОКА    задать имя агента СТРОКА вместо Wget/ВЕРСИЯ.\n"
"\n"

#: src/main.c:173
#, fuzzy
msgid ""
"FTP options:\n"
"       --retr-symlinks   when recursing, retrieve linked-to files (not "
"dirs).\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Параметры FTP:\n"
"       --retr-symlinks   получать по FTP символьные ссылки.\n"
"  -g,  --glob=on/off     включить или выключить работу с шаблонами в "
"именах.\n"
"       --passive-ftp     использовать \"пассивный\" режим передачи.\n"
"\n"

#: src/main.c:178
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive             recursive web-suck -- use with care!.\n"
"  -l,  --level=NUMBER          maximum recursion depth (inf or 0 for "
"infinite).\n"
"       --delete-after          delete downloaded files.\n"
"  -k,  --convert-links         convert non-relative links to relative.\n"
"  -K,  --backup-converted      before converting file X, back up as X.orig.\n"
"  -m,  --mirror                shortcut option equivalent to -r -N -l inf "
"-nr.\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -p,  --page-requisites       get all images, etc. needed to display HTML "
"page.\n"
"\n"
msgstr ""
"Рекурсивное получение файлов:\n"
"  -r,  --recursive             рекурсивный режим -- пользуйтесь осторожно!.\n"
"  -l,  --level=ЧИСЛО           макс. глубина рекурсии (0 - бесконечность).\n"
"       --delete-after          удалить полученные файлы.\n"
"  -k,  --convert-links         перевести абсолютные ссылки в относительные.\n"
"  -K,  --backup-converted      скопировать X в X.orig перед изменением "
"ссылок.\n"
"  -m,  --mirror                включить режимы, полезные для "
"\"зеркалирования\".\n"
"  -nr, --dont-remove-listing   не удалять файлы `.listing'.\n"
"  -p,  --page-requisites       получать изображения и все прочие файлы,\n"
"                               необходимые для отображения HTML-страницы.\n"
"\n"

#: src/main.c:188
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                comma-separated list of accepted "
"extensions.\n"
"  -R,  --reject=LIST                comma-separated list of rejected "
"extensions.\n"
"  -D,  --domains=LIST               comma-separated list of accepted "
"domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected "
"domains.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"       --follow-tags=LIST           comma-separated list of followed HTML "
"tags.\n"
"  -G,  --ignore-tags=LIST           comma-separated list of ignored HTML "
"tags.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -L,  --relative                   follow relative links only.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Включение/исключение файлов при рекурсии:\n"
"  -A,  --accept=СПИСОК               список разрешенных суффиксов.\n"
"  -R,  --reject=СПИСОК               список запрещенных суффиксов.\n"
"  -D,  --domains=СПИСОК              список разрешенных доменов.\n"
"       --exclude-domains=СПИСОК      список запрещенных доменов.\n"
"       --follow-ftp                  идти по FTP-ссылкам в HTML-документах.\n"
"       --follow-tags=СПИСОК          HTML-теги, по которым переходы "
"разрешены.\n"
"  -G,  --ignore-tags=СПИСОК          список игнорируемых HTML-тегов.\n"
"  -H,  --span-hosts                  переходить на другие хосты при "
"рекурсии.\n"
"  -L,  --relative                    идти только по относительным ссылкам.\n"
"  -I,  --include-directories=СПИСОК  список разрешенных каталогов.\n"
"  -X,  --exclude-directories=СПИСОК  список запрещенных каталогов.\n"
"  -nh, --no-host-lookup              не выполнять поиск имен хостов в DNS.\n"
"  -np, --no-parent                   не подниматься в родительский каталог.\n"
"\n"

#: src/main.c:203
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Сообщения о замеченных ошибках отправляйте по адресу <bug-wget@gnu.org>.\n"

#: src/main.c:378
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: поддержка отладки не была включена при компиляции.\n"

#: src/main.c:430
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Данная программа распространяется в надежде, что она принесет пользу,\n"
"но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ; в том числе подразумеваемой гарантии\n"
"ПОЛЕЗНОСТИ или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННОЙ ЦЕЛИ. Для получения более\n"
"подробной информации смотрите GNU General Public License.\n"

#: src/main.c:436
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@iskon.hr>.\n"
msgstr ""
"\n"
"Первоначально разработано автором: Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:510
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: недопустимая команда\n"

#: src/main.c:563
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: недопустимый ключ -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:566 src/main.c:608 src/main.c:666
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Запустите `%s --help' для получения более подробной справки.\n"

#: src/main.c:646
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Режимы verbose и quiet противоречат друг другу.\n"

#: src/main.c:652
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""
"Режимы поддержки отметок времени и сохранения старых файлов несовместимы.\n"

#. No URL specified.
#: src/main.c:661
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: не указан URL\n"

#: src/main.c:749
#, c-format
msgid "No URLs found in %s.\n"
msgstr "В файле %s не обнаружено строк URL.\n"

#: src/main.c:758
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"ЗАВЕРШЕНО --%s--\n"
"Принято: %s байт в %d файлax\n"

#: src/main.c:763
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "ПРЕВЫШЕНО ограничение объема (%s байт)!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:790
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "Получен сигнал %s, вывод перенаправлен в `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Нажаты CTRL+Break, вывод перенаправляется в `%s'.\n"
"Выполнение программы будет продолжено в фоновом режиме.\n"
"Вы можете остановить работу Wget нажатием CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Продолжение работы в фоновом режиме.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Выходная информация будет записана в файл `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Запуск WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Не найден подходящий драйвер TCP/IP.\n"

#: src/netrc.c:359
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d: предупреждение: лексема \"%s\" встречена ранее имени машины\n"

#: src/netrc.c:390
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: неизвестная лексема \"%s\"\n"

#: src/netrc.c:454
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Использование: %s NETRC [HOSTNAME]\n"

#: src/netrc.c:464
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: не удается выполнить stat для %s: %s\n"

#: src/recur.c:463 src/retr.c:468
#, c-format
msgid "Removing %s.\n"
msgstr "Удаление %s.\n"

#: src/recur.c:464
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Удаление %s, так как этот файл должен быть исключен.\n"

#: src/recur.c:624
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Загрузка robots.txt; не обращайте внимания на ошибки.\n"

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ пропуск %dK ]"

#: src/retr.c:349
msgid "Could not find proxy host.\n"
msgstr "Не найден прокси-сервер.\n"

#: src/retr.c:360
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Прокси-сервер %s: Должен быть HTTP.\n"

#: src/retr.c:403
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Перенаправление на самого себя.\n"

#: src/retr.c:489
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Завершение.\n"
"\n"

#: src/retr.c:489
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Продолжение попыток.\n"
"\n"

#: src/url.c:951
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Ошибка (%s): Ссылка %s без базового адреса.\n"

#: src/url.c:966
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Ошибка (%s): Базовый адрес %s относителен, URL не определен.\n"

#: src/url.c:1385
#, c-format
msgid "Converting %s... "
msgstr "Преобразование %s... "

#: src/url.c:1390 src/url.c:1477
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Не удается преобразовать ссылки в %s: %s\n"

#: src/url.c:1453
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Не удается сохранить %s под именем %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Недостаточно памяти.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Протокол неизвестен или не поддерживается"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Указание недопустимого порта"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Недопустимое имя машины (hostname)"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Ошибка удаления символьной ссылки `%s': %s\n"

#~ msgid ""
#~ "Server file no newer than local file `%s.orig' -- not retrieving.\n"
#~ "\n"
#~ msgstr "Файл на сервере не новее локального файла `%s.orig' -- пропуск.\n"
