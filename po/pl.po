# Polish translation of wget.
# Copyright (C) 2000 Free Software Foundation, Inc.
# Grzegorz Kowal <g_kowal@poczta.onet.pl>, 2000.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 2000-10-20 00:07-0700\n"
"PO-Revision-Date: 2000-09-15 23:44+0200\n"
"Last-Translator: Grzegorz Kowal <g_kowal@poczta.onet.pl>\n"
"Language-Team: Polish <pl@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:348
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "??czenie si? z %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:365
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Po??czenie z %s:%hu zosta?o odrzucone.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:376
msgid "connected!\n"
msgstr "po??czony!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Logowanie si? jako %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "B??d w odpowiedzi serwera, zamykanie po??czenia kontrolnego.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "B??d w powitaniu serwera.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "B??d zapisu, zamykanie po??czenia kontrolnego.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Serwer odrzuci? login.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Nieprawid?owy login.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Zalogowany!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Nieznany typ `%c', zamykanie po??czenia kontrolnego.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "zrobione. "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD nie jest potrzebne.\n"

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Nie ma takiego katalogu `%s'.\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1523
msgid "done.\n"
msgstr "zrobione.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD nie jest wymagany.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Nie mog? zainicjowa? transferu PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Nie mog? przetworzy? odpowiedzi PASV.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Spróbuj? po??czy? si? z %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "zrobione.  "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "B??d przywi?zania (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Nieprawid?owy PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"Wykonanie REST nie powiod?o si?, zaczynam od pocz?tku.\n"

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Nie ma takiego pliku `%s'.\n"
"\n"

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Nie ma takiego pliku lub katalogu `%s'.\n"
"\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "D?ugo??: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [pozosta?o %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (nieautorytatywny)\n"

#: src/ftp.c:729
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, zamykam po??czenie kontrolne.\n"

#: src/ftp.c:737
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Po??czenie danych: %s; "

#: src/ftp.c:754
msgid "Control connection closed.\n"
msgstr "Po??czenie kontrolne zosta?o zamkni?te.\n"

#: src/ftp.c:772
msgid "Data transfer aborted.\n"
msgstr "Transfer danych zosta? przerwany.\n"

#: src/ftp.c:838
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Plik `%s' jest ju? tam, wi?c go nie pobieram.\n"

#: src/ftp.c:915 src/http.c:1016
#, c-format
msgid "(try:%2d)"
msgstr "(próba:%2d)"

#: src/ftp.c:979 src/http.c:1236
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - zapisano `%s' [%ld]\n"
"\n"

#: src/ftp.c:1025
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "U?ycie `%s' jako tymczasowego pliku wylistowania.\n"

#: src/ftp.c:1037
#, c-format
msgid "Removed `%s'.\n"
msgstr "Usuni?to `%s'.\n"

#: src/ftp.c:1073
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "G??boko?? rekursji %d przekroczy?a g??boko?? maksymaln? %d.\n"

#: src/ftp.c:1125 src/http.c:1163
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""

#: src/ftp.c:1131 src/http.c:1171
#, fuzzy, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Rozmiary nie s? zgodne (lokalny %ld), wi?c pobieram.\n"

#: src/ftp.c:1148
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Nieprawid?owa nazwa ??cza symbolicznego, wi?c pomijam go.\n"

#: src/ftp.c:1165
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Istnieje ju? prawid?owe ??cze symboliczne %s -> %s\n"
"\n"

#: src/ftp.c:1173
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Tworz? ??cze symboliczne %s -> %s\n"

#: src/ftp.c:1184
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "??cza symboliczne nie s? obs?ugiwane, wi?c pomijam ??cze `%s'.\n"

#: src/ftp.c:1196
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Pomijam katalog `%s'.\n"

#: src/ftp.c:1205
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: nieznany/nieobs?ugiwany typ pliku.\n"

#: src/ftp.c:1222
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: zniszczony znacznik czasu.\n"

#: src/ftp.c:1243
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Nie b?d? pobiera? katalogów dopóki g??boko?? wynosi %d (maks. %d).\n"

#: src/ftp.c:1282
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Brak zej?cia do `%s', tak jak to jest wykluczone/nie w??czone.\n"

#: src/ftp.c:1327
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Odrzucam `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1374
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Brak dopasowa? do wzorca `%s'.\n"

#: src/ftp.c:1434
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Indeks w formacie HTML zosta? zapisany w `%s' [%ld].\n"

#: src/ftp.c:1439
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Indeks w formacie HTML zosta? zapisany w `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: opcja `%s' jest niejasna\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: opcja `--%s' nie posiada argumentu\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: opcja `%c%s' nie posiada argumentu\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: opcja `%s' wymaga argumentu\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: nierozpoznana opcja `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: nierozpoznana opcja `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: nielegalna opcja -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: opcja wymaga argumentu -- %c\n"

#: src/host.c:437
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Nie mog? okre?li? identyfikatora u?ytkownika.\n"

#: src/host.c:449
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Ostrze?enie: wykonanie uname nie powiod?o si?: %s\n"

#: src/host.c:461
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Ostrze?enie: wykonanie gethostname nie powiod?o si?\n"

#: src/host.c:489
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Ostrze?enie: nie mog? okre?li? lokalnego adresu IP.\n"

#: src/host.c:503
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Ostrze?enie: nie mog? odszuka? lokalnego adresu IP.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:516
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Ostrze?enie: odszukanie lokalnego adresu nie wyprodukowa?o FQDN!\n"

#: src/host.c:544
msgid "Host not found"
msgstr "Serwer nie zosta? odnaleziony"

#: src/host.c:546
msgid "Unknown error"
msgstr "Nieznany b??d"

#: src/html.c:539 src/html.c:541
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Indeks /%s dla %s:%d"

#: src/html.c:563
msgid "time unknown       "
msgstr "nieznany czas      "

#: src/html.c:567
msgid "File        "
msgstr "Plik        "

#: src/html.c:570
msgid "Directory   "
msgstr "Katalog     "

#: src/html.c:573
msgid "Link        "
msgstr "??cze       "

#: src/html.c:576
msgid "Not sure    "
msgstr "Niepewne    "

#: src/html.c:594
#, c-format
msgid " (%s bytes)"
msgstr " (%s bajtów)"

#: src/http.c:508
msgid "Failed writing HTTP request.\n"
msgstr "Zapisanie ??dania o HTTP nie powiod?o si?.\n"

#: src/http.c:512
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "??danie o %s zosta?o wys?ane, oczekiwanie na odpowied?... "

#: src/http.c:551
msgid "End of file while parsing headers.\n"
msgstr "Wyst?pi? koniec pliku podczas przetwarzania nag?ówków.\n"

#: src/http.c:562
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "B??d odczytu (%s) w nag?ówkach.\n"

#: src/http.c:602
msgid "No data received"
msgstr "Nie pobrano ?adnych danych"

#: src/http.c:604
msgid "Malformed status line"
msgstr "Zniekszta?cona linia stanu"

#: src/http.c:609
msgid "(no description)"
msgstr "(brak opisu)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:693
msgid "Authorization failed.\n"
msgstr "Autoryzacja nie powiod?a si?.\n"

#: src/http.c:700
msgid "Unknown authentication scheme.\n"
msgstr "Nieznany schemat autentyfikacji.\n"

#: src/http.c:783
#, c-format
msgid "Location: %s%s\n"
msgstr "Po?o?enie: %s%s\n"

#: src/http.c:784 src/http.c:809
msgid "unspecified"
msgstr "nieokre?lony"

#: src/http.c:785
msgid " [following]"
msgstr " [nast?puj?cy]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:799
msgid "Length: "
msgstr "D?ugo??: "

#: src/http.c:804
#, c-format
msgid " (%s to go)"
msgstr " (pozosta?o %s)"

#: src/http.c:809
msgid "ignored"
msgstr "zignorowano"

#: src/http.c:903
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Ostrze?enie: znaki specjalne nie s? obs?ugiwane z HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:924
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Plik `%s' ju? tam jest, wi?c nie zostanie pobrany.\n"

#: src/http.c:1083
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Nie mog? zapisa? do `%s' (%s).\n"

#: src/http.c:1094
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "B??D: Przekierowanie (%d) bez po?o?enia.\n"

#: src/http.c:1119
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s B??D %d: %s.\n"

#: src/http.c:1132
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr ""
"Brak nag?ówka ostatniej modyfikacji -- znaczniki czasowe zosta?y wy??czone.\n"

#: src/http.c:1140
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""
"Nieprawid?owy nag?ówek ostatniej modyfikacji -- znacznik czasowy zosta? "
"zignorowany.\n"

#: src/http.c:1175
msgid "Remote file is newer, retrieving.\n"
msgstr "Odleg?y plik jest nowszy, wi?c pobieram go.\n"

#: src/http.c:1210
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' zosta? zapisany [%ld/%ld]\n"
"\n"

#: src/http.c:1258
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Po??czenie zosta?o zamkni?te przy bajcie %ld. "

#: src/http.c:1266
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' zosta? zapisany [%ld/%ld])\n"
"\n"

#: src/http.c:1286
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Po??czenie zosta?o zamkni?te przy bajcie %ld/%ld. "

#: src/http.c:1297
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - B??d odczytu przy bajcie %ld (%s)."

#: src/http.c:1305
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - B??d odczytu przy bajcie %ld/%ld (%s). "

#: src/init.c:320 src/netrc.c:260
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Nie mog? odczyta? %s (%s).\n"

#: src/init.c:341 src/init.c:347
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: B??d w %s w linii %d.\n"

#: src/init.c:378
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""
"%s: Ostrze?enie: Zarówno plik systemowy wgetrc jak i u?ytkownika odnosz? si? "
"do `%s'.\n"

#: src/init.c:466
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: B??D W PROGRAMIE: nieznane polecenie `%s', warto?? `%s'.\n"

#: src/init.c:493
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Prosz? okre?li?: on lub off.\n"

#: src/init.c:537
#, fuzzy, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Prosz? okre?li?: on lub off.\n"

#: src/init.c:556 src/init.c:813 src/init.c:835 src/init.c:908
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Nieprawid?owa specyfikacja `%s'.\n"

#: src/init.c:669 src/init.c:691 src/init.c:713 src/init.c:739
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Nieprawid?owa specyfikacja `%s'\n"

#: src/main.c:105
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "U?ycie: %s [OPCJA]... [URL]...\n"

#: src/main.c:113
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, nieinteraktywna ?ci?garka sieciowa.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:118
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Argumenty obowi?zkowe dla opcji d?ugich s? równie? obowi?zkowe dla opcji "
"krótkich.\n"
"\n"

#: src/main.c:121
#, fuzzy
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Wywo?anie:\n"
"  -V,  --version           wy?wietla wersj? Wget i ko?czy dzia?anie.\n"
"  -h,  --help              drukuje t? pomoc.\n"
"  -b,  --background        po starcie przechodzi do pracy w tle.\n"
"  -e,  --execute=KOMENDA   wykonuje komend? `.wgetrc'.\n"
"\n"

#: src/main.c:127
#, fuzzy
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
"Logowanie i plik wej?ciowy:\n"
"  -o,  --output-file=PLIK     zapisuj komunikaty do PLIK.\n"
"  -a,  --append-output=PLIK   do??czaj komunikaty do PLIK.\n"
"  -d,  --debug                drukuj komunikaty debugowania.\n"
"  -q,  --quiet                cicho (bez komunikatów wyj?ciowych).\n"
"  -v,  --verbose              wypisuj informacje o pracy (domy?lne).\n"
"  -nv, --non-verbose          wy??cz komunikaty, ale nie b?d? cicho.\n"
"  -i,  --input-file=PLIK      odczytaj URL'e z pliku.\n"
"  -F,  --force-html           potraktuj plik jako HTML.\n"
"\n"

#: src/main.c:138
#, fuzzy
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
"Pobieranie:\n"
"  -t,  --tries=NUMER            ustaw liczb? prób równ? NUMER (0 bez "
"ograniczenia).\n"
"  -O   --output-document=PLIK   zapisz dokumenty do PLIK.\n"
"  -nc, --no-clobber             nie pobieraj lokalnie istniej?cych plików.\n"
"  -c,  --continue               wznów pobieranie istniej?cego pliku.\n"
"       --dot-style=STYL         ustaw styl wy?wietlania stopnia pobrania.\n"
"  -N,  --timestamping           nie pobieraj plików starszych ni? lokalne.\n"
"  -S,  --server-response        drukuj odpowied? serwera.\n"
"       --spider                 nic nie pobieraj.\n"
"  -T,  --timeout=SEKUNDY        ustaw limit czasu odczytu na SEKUNDY.\n"
"  -w,  --wait=SEKUNDY           czekaj przez SEKUNDY pomi?dzy pobieraniami.\n"
"  -Y,  --proxy=on/off           w??cz (on) lub wy??cz (off) proxy.\n"
"  -Q,  --quota=NUMER            ustaw ograniczenie pobieranego rozmiaru na "
"NUMER.\n"
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
"Katalogi:\n"
"  -nd  --no-directories            nie twórz katalogów.\n"
"  -x,  --force-directories         wymuszaj tworzenie katalogów.\n"
"  -nH, --no-host-directories       nie twórz katalogów serwera.\n"
"  -P,  --directory-prefix=PREFIKS  zapisz pliki do PREFIKS/...\n"
"       --cut-dirs=NUMER            ignoruj sk?adowe odleg?ego katalogu "
"NUMER.\n"
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
"Opcje HTTP:\n"
"       --http-user=U?YT      ustaw u?ytkownika http jako U?YT.\n"
"       --http-passwd=HAS?O   ustaw has?o http jako HAS?O.\n"
"  -C,  --cache=on/off        pozwól/zabro? na buforowanie danych z serwera "
"(normalnie zezwolone).\n"
"       --ignore-length       ignoruj pole nag?ówka `Content-Length'.\n"
"       --header=TEKST        wstaw TEKST pomi?dzy nag?ówki.\n"
"       --proxy-user=U?YT     ustaw u?ytkownika dla proxy jako U?YT.\n"
"       --proxy-passwd=HAS?O  ustaw has?o dla proxy jako HAS?O.\n"
"  -s,  --save-headers        zapisz nag?ówki HTTP do pliku.\n"
"  -U,  --user-agent=AGENT    identyfikuj si? jako AGENT, zamiast "
"Wget/WERSJA.\n"
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
"Opcje FTP:\n"
"       --retr-symlinks   pobierz ??cza symboliczne FTP.\n"
"  -g,  --glob=on/off     w??cz lub wy??cz uogólnienie nazw plików.\n"
"       --passive-ftp     u?yj \"pasywnego\" trybu dla transferu.\n"
"\n"

#: src/main.c:178
#, fuzzy
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
"Pobieranie rekursywne:\n"
"  -r,  --recursive             rekursywne pobieranie - u?ywaj ostro?nie!.\n"
"  -l,  --level=NUMER           maksymalna g??boko?? rekursji (0 - "
"nieograniczona).\n"
"       --delete-after          usu? pobrane pliki.\n"
"  -k,  --convert-links         przekonwertuj ??cza bezwzgl?dne do "
"wzgl?dnych.\n"
"  -m,  --mirror                w??cz opcje odpowiednie dla obrazowania.\n"
"  -nr, --dont-remove-listing   nie usuwaj plików `.listing'.\n"
"\n"

#: src/main.c:188
#, fuzzy
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
"Rekursywne akceptacje/odrzucenia:\n"
"  -A,  --accept=LISTA               lista akceptowanych rozszerze?.\n"
"  -R,  --reject=LISTA               lista odrzucanych rozszerze?.\n"
"  -D,  --domains=LISTA              lista akceptowanych domen.\n"
"       --exclude-domains=LISTA      lista odrzucanych domen, oddzielonych "
"przecinkami.\n"
"  -L,  --relative                   pod??aj tylko za wzgl?dnymi ??czami.\n"
"       --follow-ftp                 pod??aj za ??czami FTP z dokumentów "
"HTML.\n"
"  -H,  --span-hosts                 przechod? do innych serwerów podczas "
"pobierania rekursywnego.\n"
"  -I,  --include-directories=LISTA  lista zezwolonych katalogów.\n"
"  -X,  --exclude-directories=LISTA  lista wykluczonych katalogów.\n"
"  -nh, --no-host-lookup             nie odszukuj serwerów poprzez DNS.\n"
"  -np, --no-parent                  nie przechod? do katalogu nadrz?dnego.\n"
"\n"

#: src/main.c:203
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Raporty b??dów i sugestie prosz? wysy?a? do <bug-wget@gnu.org>.\n"

#: src/main.c:378
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: wsparcie dla debugowania nie zosta?o wkompilowane.\n"

#: src/main.c:430
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Prawa autorskie (C) 1995 - 1998 Free Software Foundation, Inc.\n"
"Program ten rozprowadzany jest z nadziej?, ?e b?dzie u?yteczny,\n"
"ale BEZ ?ADNEJ GWARANCJI; nie zawieraj?cej nawet gwarancji\n"
"HANDLOWEJ lub ZASTOSOWANIA DO SZCZEGÓLNEGO CELU. Zobacz do\n"
"GNU General Public License, aby uzyska? wi?cej informacji.\n"

#: src/main.c:436
#, fuzzy
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@iskon.hr>.\n"
msgstr ""
"\n"
"Napisany przez Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:510
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: nieprawid?owa komenda\n"

#: src/main.c:563
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: nielegalna opcja -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:566 src/main.c:608 src/main.c:666
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Spróbuj `%s --help' w celu uzyskania opisu opcji.\n"

#: src/main.c:646
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Nie mog? wy?wietla? komunikatów i by? cicho w tym samym czasie.\n"

#: src/main.c:652
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""
"Nie mog? jednocze?nie zwraca? uwagi na znaczniki czasowe i nie pobiera? "
"starszych plików ni? lokalne.\n"

#. No URL specified.
#: src/main.c:661
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: brak URL'a\n"

#: src/main.c:749
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Nie znaleziono ?adnych URL'i w %s.\n"

#: src/main.c:758
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"ZAKO?CZONO --%s--\n"
"Pobrano: %s bajtów w %d plikach\n"

#: src/main.c:763
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Ograniczenie rozmiaru pobierania (%s bajtów) zosta?o PRZEKROCZONE!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:790
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "pobrano %s, przekierowanie wyj?cia do `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Przechwycono CTRL+Break, przekierowanie wyj?cia do `%s'.\n"
"Wykonywanie b?dzie kontynuowane w tle.\n"
"Mo?esz zatrzyma? Wget poprzez wci?ni?cie CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Kontynuacja w tle.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Wyj?cie zostanie zapisane w `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Uruchomienie WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Nie mog? znale?? u?ytecznego sterownika gniazdka.\n"

#: src/netrc.c:359
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d: ostrze?enie: pojawia si? znak \"%s\" przed jak?kolwiek nazw? "
"maszyny\n"

#: src/netrc.c:390
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: nieznany znak \"%s\"\n"

#: src/netrc.c:454
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "U?ycie: %s NETRC [NAZWA_SERWERA]\n"

#: src/netrc.c:464
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: nie mog? przeprowadzi? statystyki %s: %s\n"

#: src/recur.c:463 src/retr.c:468
#, c-format
msgid "Removing %s.\n"
msgstr "Usuwanie %s.\n"

#: src/recur.c:464
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Usuni?cie %s poniewa? powinien by? odrzucony.\n"

#: src/recur.c:624
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "?adowanie robots.txt; prosz? zignorowa? b??dy.\n"

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ pomijam %d kB ]"

#: src/retr.c:349
msgid "Could not find proxy host.\n"
msgstr "Nie mog? odnale?? serwera proxy.\n"

#: src/retr.c:360
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Musi by? HTTP.\n"

#: src/retr.c:403
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Przekierowanie na samego siebie.\n"

#: src/retr.c:489
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Poddaj? si?.\n"
"\n"

#: src/retr.c:489
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Ponawiam prób?.\n"
"\n"

#: src/url.c:951
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "B??d (%s): ??cze %s zosta?o dostarczone bez bazy.\n"

#: src/url.c:966
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "B??d (%s): Baza %s jest wzgl?dna, bez odniesienia do URL'a.\n"

#: src/url.c:1385
#, c-format
msgid "Converting %s... "
msgstr "Konwersja %s... "

#: src/url.c:1390 src/url.c:1477
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Nie mog? przekonwertowa? ??cza w %s: %s\n"

#: src/url.c:1453
#, fuzzy, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Nie mog? przekonwertowa? ??cza w %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Brak pami?ci.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Nieznany/nieobs?ugiwany protokó?"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Nieprawid?owa specyfikacja portu"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Nieprawid?owa nazwa serwera"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Od??czenie ??cza symbolicznego `%s' nie powiod?o si?: %s\n"

#~ msgid ""
#~ "Local file `%s' is more recent, not retrieving.\n"
#~ "\n"
#~ msgstr ""
#~ "Plik lokalny `%s' jest nowszy, wi?c go nie pobieram.\n"
#~ "\n"
