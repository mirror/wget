# Mesajele în limba românã pentru wget.
# Copyright (C) 2003 Free Software Foundation, Inc.
# Eugen Hoanca <eugenh@urban-grafx.ro>, 2003.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.8.2\n"
"POT-Creation-Date: 2001-12-17 16:30+0100\n"
"PO-Revision-Date: 2003-04-16 08:40+0300\n"
"Last-Translator: Eugen Hoanca <eugenh@urban-grafx.ro>\n"
"Language-Team: Romanian <translation-team-ro@lists.sourceforge.net>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/connect.c:94
#, c-format
msgid "Connecting to %s[%s]:%hu... "
msgstr "Conectare la %s[%s]:%hu..."

#: src/connect.c:97
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Conectare la %s:%hu..."

#: src/connect.c:131
msgid "connected.\n"
msgstr "conectat.\n"

#: src/cookies.c:595
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Eroare în Set-Cookie, câmpul `%s'"

#: src/cookies.c:619
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Eroare de sintaxã în Set-Cookie la caracterul `%c'.\n"

#: src/cookies.c:627
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Eroare de sintaxã în Set-Cookie: sfârºit prematur de ºir.\n"

#: src/cookies.c:1329
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Nu pot deschide fiºierul de cookies `%s': %s\n"

#: src/cookies.c:1341
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Eroare la scriere în `%s': %s\n"

#: src/cookies.c:1345
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Eroare la închiderea `%s': %s\n"

#: src/ftp-ls.c:802
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Tip de listare nesuportat, se încearcã trecere la listare Unix.\n"

#: src/ftp-ls.c:847 src/ftp-ls.c:849
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index al /%s pe %s:%d"

#: src/ftp-ls.c:871
msgid "time unknown       "
msgstr "duratã necunoscutã "

#: src/ftp-ls.c:875
msgid "File        "
msgstr "Fiºier      "

#: src/ftp-ls.c:878
msgid "Directory   "
msgstr "Director    "

#: src/ftp-ls.c:881
msgid "Link        "
msgstr "Link        "

#: src/ftp-ls.c:884
msgid "Not sure    "
msgstr "Nesigur     "

#: src/ftp-ls.c:902
#, c-format
msgid " (%s bytes)"
msgstr " (%s octeþi)"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:179
#, c-format
msgid "Logging in as %s ... "
msgstr "Login ca %s ... "

#: src/ftp.c:188 src/ftp.c:241 src/ftp.c:272 src/ftp.c:326 src/ftp.c:419
#: src/ftp.c:470 src/ftp.c:500 src/ftp.c:564 src/ftp.c:628 src/ftp.c:689
#: src/ftp.c:737
msgid "Error in server response, closing control connection.\n"
msgstr "Eroare în rãspunsul serverului, închid conexiunea.\n"

#: src/ftp.c:196
msgid "Error in server greeting.\n"
msgstr "Eroare în salutul serverului.\n"

#: src/ftp.c:204 src/ftp.c:335 src/ftp.c:428 src/ftp.c:509 src/ftp.c:574
#: src/ftp.c:638 src/ftp.c:699 src/ftp.c:747
msgid "Write failed, closing control connection.\n"
msgstr "Scriere eºuatã, închid conexiunea.\n"

#: src/ftp.c:211
msgid "The server refuses login.\n"
msgstr "Serverul refuzã loginul.\n"

#: src/ftp.c:218
msgid "Login incorrect.\n"
msgstr "Login incorect.\n"

#: src/ftp.c:225
msgid "Logged in!\n"
msgstr "Admis!\n"

#: src/ftp.c:250
msgid "Server error, can't determine system type.\n"
msgstr "Eroare server, nu se poate determina tipul sistemului.\n"

#: src/ftp.c:260 src/ftp.c:549 src/ftp.c:612 src/ftp.c:669
msgid "done.    "
msgstr "terminat."

#: src/ftp.c:314 src/ftp.c:449 src/ftp.c:484 src/ftp.c:720 src/ftp.c:768
#: src/host.c:283
msgid "done.\n"
msgstr "terminat.\n"

#: src/ftp.c:343
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tip `%c' necunoscut, conexiune închisã.\n"

#: src/ftp.c:356
msgid "done.  "
msgstr "finalizat."

#: src/ftp.c:362
msgid "==> CWD not needed.\n"
msgstr "==> CWD nenecesar.\n"

#: src/ftp.c:435
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Nu existã directorul `%s'.\n"
"\n"

#. do not CWD
#: src/ftp.c:453
msgid "==> CWD not required.\n"
msgstr "==> CWD nu este necesar.\n"

#: src/ftp.c:516
msgid "Cannot initiate PASV transfer.\n"
msgstr "Nu s-a putut iniþia transferul PASV.\n"

#: src/ftp.c:520
msgid "Cannot parse PASV response.\n"
msgstr "Nu s-a putut analiza rãspunsul PASV.\n"

#: src/ftp.c:541
#, c-format
msgid "couldn't connect to %s:%hu: %s\n"
msgstr "conectare la %s:%hu nereuºitã: %s\n"

#: src/ftp.c:591
#, c-format
msgid "Bind error (%s).\n"
msgstr "Eroare de legãturã(bind) (%s).\n"

#: src/ftp.c:598
msgid "Invalid PORT.\n"
msgstr "PORT invalid.\n"

#: src/ftp.c:651
#, c-format
msgid ""
"\n"
"REST failed; will not truncate `%s'.\n"
msgstr ""
"\n"
"REST eºuat; nu se va trunchia `%s'.\n"

#: src/ftp.c:658
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST eºuat, start de la început.\n"

#: src/ftp.c:707
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Nu existã fiºierul `%s'.\n"
"\n"

#: src/ftp.c:755
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Nu existã fiºierul sau directorul `%s'.\n"
"\n"

#: src/ftp.c:839 src/ftp.c:847
#, c-format
msgid "Length: %s"
msgstr "Dimensiune: %s"

#: src/ftp.c:841 src/ftp.c:849
#, c-format
msgid " [%s to go]"
msgstr " [%s rãmaºi]"

#: src/ftp.c:851
msgid " (unauthoritative)\n"
msgstr " (neobligatoriu)\n"

#: src/ftp.c:877
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, închid controlul conexiunii.\n"

#: src/ftp.c:885
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Conexiune de date: %s; "

#: src/ftp.c:902
msgid "Control connection closed.\n"
msgstr "Controlul conexiunii închis.\n"

#: src/ftp.c:920
msgid "Data transfer aborted.\n"
msgstr "Transfer de date întrerupt.\n"

#: src/ftp.c:984
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Fiºierul `%s' existã deja, nu se mai aduce.\n"

#: src/ftp.c:1054 src/http.c:1527
#, c-format
msgid "(try:%2d)"
msgstr "(încercare:%2d)"

#: src/ftp.c:1118 src/http.c:1786
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr "%s (%s) - `%s' salvat [%ld]\n"

#: src/ftp.c:1160 src/main.c:819 src/recur.c:349 src/retr.c:587
#, c-format
msgid "Removing %s.\n"
msgstr "ªterg %s.\n"

#: src/ftp.c:1202
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Se utilizeazã `%s' ca fiºier temporar de listare.\n"

#: src/ftp.c:1217
#, c-format
msgid "Removed `%s'.\n"
msgstr "`%s' ºters.\n"

#: src/ftp.c:1252
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Adãncimea de recurenþã %d a depaºit max. de adãncime %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1317
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Fiºierul remote nu este mai nou decãt fiºierul local `%s'--nu se aduce.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1324
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr "Fiºierul remote este mai nou decãt fiºierul local `%s' -- se aduce.\n"

#. Sizes do not match
#: src/ftp.c:1331
#, c-format
msgid ""
"The sizes do not match (local %ld) -- retrieving.\n"
"\n"
msgstr ""
"Dimensiunile nu corespund (local %ld) -- se aduce.\n"
"\n"

#: src/ftp.c:1348
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Nume symlink invalid, se omite.\n"

#: src/ftp.c:1365
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Deja existã symlinkul corect %s -> %s\n"
"\n"

#: src/ftp.c:1373
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creare symlink %s -> %s\n"

#: src/ftp.c:1384
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symlinkuri nesuportate, se omite symlinkul `%s'.\n"

#: src/ftp.c:1396
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Se omite directorul `%s.\n"

#: src/ftp.c:1405
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tip fiºier necunoscut/nesuportat.\n"

#: src/ftp.c:1432
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: identificator-timp(time-stamp) corupt.\n"

#: src/ftp.c:1457
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Nu vor fi aduse directoare pentru adãncime setatã la %d (max %d).\n"

#: src/ftp.c:1507
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Nu se coboarã la `%s' daca este exclus/neinclus.\n"

#: src/ftp.c:1561
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Refuzare `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1608
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Nu s-au gãsit potriviri pentru tiparul `%s'.\n"

#: src/ftp.c:1673
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "S-a scris indexul HTML în `%s' [%ld].\n"

#: src/ftp.c:1678
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "S-a scris indexul HTML în `%s'\n"

#: src/gen_sslfunc.c:109
msgid "Could not seed OpenSSL PRNG; disabling SSL.\n"
msgstr "Nu s-a selectat OpenSSL PRNG; dezactivare SSL.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: opþiunea `%s' este ambiguã\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: opþiunea `--%s' nu permite un parametru\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: opþiunea `%c%s' nu permite un parametru\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: opþiunea `%s' necesitã un parametru\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opþiune nerecunoscutã `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opþiune nerecunoscutã `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opþiune ilegalã -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: opþiunea necesitã un parametru -- %c\n"

#: src/host.c:271
#, c-format
msgid "Resolving %s... "
msgstr "Rezolvare %s... "

#: src/host.c:278
#, c-format
msgid "failed: %s.\n"
msgstr "eºuare: %s.\n"

#: src/host.c:348
msgid "Host not found"
msgstr "Host negãsit"

#: src/host.c:350
msgid "Unknown error"
msgstr "Eroare necunoscutã"

#: src/html-url.c:336
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Nu s-a rezolvat linkul incomplet %s.\n"

#. this is fatal
#: src/http.c:573
msgid "Failed to set up an SSL context\n"
msgstr "S-a eºuat în setarea contextului SSL\n"

#: src/http.c:579
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "S-a eºuat în încãrcarea certificatelor din %s\n"

#: src/http.c:583 src/http.c:591
msgid "Trying without the specified certificate\n"
msgstr "Se încearcã fãrã certificatele specificate\n"

#: src/http.c:587
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Nu s-a putut primi codul(key) certificatului de la %s\n"

#: src/http.c:657 src/http.c:1620
msgid "Unable to establish SSL connection.\n"
msgstr "Nu s-a putut stabili o conexiune SSL.\n"

#: src/http.c:666
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Reutilizare conexiune cãtre %s:%hu.\n"

#: src/http.c:868
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Scriere cerere HTTP eºuatã: %s.\n"

#: src/http.c:873
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "Cerere %s trimisã, se aºteaptã rãspuns... "

#: src/http.c:917
msgid "End of file while parsing headers.\n"
msgstr "Sfârºit fiºier la analiza headerelor.\n"

#: src/http.c:927
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Eroare de citire (%s) în headere.\n"

#: src/http.c:962
msgid "No data received"
msgstr "Nici o datã recepþionatã"

#: src/http.c:964
msgid "Malformed status line"
msgstr "Linie de stare malformatã"

#: src/http.c:969
msgid "(no description)"
msgstr "(fãrã descriere)"

#: src/http.c:1101
msgid "Authorization failed.\n"
msgstr "Autorizare eºuatã.\n"

#: src/http.c:1108
msgid "Unknown authentication scheme.\n"
msgstr "Schemã autentificare necunoscutã.\n"

#: src/http.c:1148
#, c-format
msgid "Location: %s%s\n"
msgstr "Locaþie: %s%s\n"

#: src/http.c:1149 src/http.c:1282
msgid "unspecified"
msgstr "nespecificat(ã)"

#: src/http.c:1150
msgid " [following]"
msgstr " [urmeazã]"

#: src/http.c:1213
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    Fiºierul este deja complet; nu mai e nimic de fãcut.\n"
"\n"

#: src/http.c:1229
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Continuarea downloadului a eºuat la acest fiºier, ceea ce intrã în \n"
"conflict cu `-c'.\n"
"Se refuzã trunchierea fiºierului `%s' existent. \n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1272
msgid "Length: "
msgstr "Dimensiune: "

#: src/http.c:1277
#, c-format
msgid " (%s to go)"
msgstr " (%s rãmaºi)"

#: src/http.c:1282
msgid "ignored"
msgstr "ignorat"

#: src/http.c:1413
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Avertisment: selecþiile globale(wildcards) nu sunt permise în HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1443
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Fiºierul `%s' existã deja, nu se mai aduce.\n"

#: src/http.c:1611
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Nu se poate scrie în `%s' (%s).\n"

#: src/http.c:1630
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "EROARE: Redirectare (%d) fãrã locaþie.\n"

#: src/http.c:1662
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "EROARE %s %d: %s.\n"

#: src/http.c:1675
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Lipseºte headerul Last-modified -- identificatori de timp opriþi.\n"

#: src/http.c:1683
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Headerul Last-modified invalid -- identificator de timp ignorat.\n"

#: src/http.c:1706
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"Fisierul de pe server nu e mai nou decât fiºierul local `%s' -- nu se aduce.\n"
"\n"

#: src/http.c:1714
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Dimensiunile diferã (local %ld) -- se aduce.\n"

#: src/http.c:1718
msgid "Remote file is newer, retrieving.\n"
msgstr "Fiºierul remote este mai nou, se aduce.\n"

#: src/http.c:1759
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s(%s) - `%s' salvat [%ld%ld]\n"
"\n"

#: src/http.c:1809
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Conexiune închisã la octetul %ld. "

#: src/http.c:1818
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr "%s (%s) - `%s' salvat [%ld%ld])\n"

#: src/http.c:1839
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Conexiune închisã la octetul %ld/%ld. "

#: src/http.c:1851
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Eroare de citire la octetul %ld (%s)."

#: src/http.c:1860
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Eroare de citire la octetul %ld/%ld (%s)."

#: src/init.c:355 src/netrc.c:265
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Nu s-a putut citi %s (%s).\n"

#: src/init.c:373 src/init.c:379
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Eroare în %s la linia %d.\n"

#: src/init.c:411
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Avertisment: Fiºierele wgetrc ºi sistem ºi user trimit cãtre `%s'.\n"

#: src/init.c:503
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: comandã necunoscutã `%s', valoare `%s'.\n"

#: src/init.c:537
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: Nu se poate converti `%s' în adresã IP.\n"

#: src/init.c:570
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Specificaþi `on`-activ  sau `off`-inactiv.\n"

#: src/init.c:614
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Specificaþi always, on, off sau never.\n"

#: src/init.c:633 src/init.c:900 src/init.c:981
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Specificaþie invalidã `%s'.\n"

#: src/init.c:789 src/init.c:811 src/init.c:833 src/init.c:859
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Specificaþie invalidã `%s'\n"

#: src/init.c:949
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Tip evoluþie `%s' invalid.\n"

#: src/log.c:641
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""
"\n"
"%s recepþionaþi, redirectare output cãtre `%s'.\n"

#. Eek!  Opening the alternate log file has failed.  Nothing we
#. can do but disable printing completely.
#: src/log.c:648
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; logging dezactivat.\n"

#: src/main.c:116
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Folosire: %s [OPÞIUNE]... [URL]...\n"

#: src/main.c:124
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, un manager de descãrcare non-interactiv.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:129
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Parametrii obligatorii pentru opþiuni lungi sunt obligatorii ºi la cele scurte.\n"

#: src/main.c:133
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"De start:\n"
"  -V,  --version\t\t    afiºeazã versiunea Wget ºi iese.\n"
"  -h,  --help\t\t\t    tipãreºte acest help.\n"
"  -b,  --background\t\trulare în fundal dupa startare.\n"
"  -e,  --execute=COMANDÃ\texecutã o comandã în stilul `.wgetrc'.\n"
"\n"

#: src/main.c:140
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
"       --egd-file=FILE        file name of the EGD socket.\n"
"\n"
msgstr ""
"Logãri ºi fiºiere de intrare:\n"
"  -o,  --output-file=FIªIER\tlogare mesaje în FIªIER.\n"
"  -a,  --append-output=FIªIER\tadãugare mesaje în FIªIER.\n"
"  -d,  --debug\t\t\t        tipãrire output debug.\n"
"  -q,  --quiet\t\t\t        silenþios (fãrã output).\n"
"  -v,  --verbose\t\t        detaliat (este implicit).\n"
"  -nv, --non-verbose\t\t    nedetaliat, fãrã a fi silenþios.\n"
"  -i,  --input-file=FIªIER\t    download de URL-uri gãsite în FIªIER.\n"
"  -F,  --force-html\t\t    considerã fiºierul de intrare ca HTML.\n"
"  -B,  --base=URL\t            prefixare URL la linkuri relative în -F -i fiºier.\n"
"       --sslcertfil=FIªIER\t    certificat client opþional.\n"
"\t--sslcertkey=FIªIERCOD\t    fiºier cod opþional pentru acest certificat.\n"
"\t--egd-file=FIªIER\t        nume fiºier pentru socketul EGD.\n"

#: src/main.c:155
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --progress=TYPE          select progress gauge type.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"       --random-wait            wait from 0...2*WAIT secs between retrievals.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"       --limit-rate=RATE        limit download rate to RATE.\n"
"\n"
msgstr ""
"Download:\n"
"\t--bind-address=ADRESÃ\tlegãturã (bind) la ADRESÃ (nume host sau ip)host local\n"
"  -t,\t--tries=NUMÃR\t\tseteazã numãrul de încercãri ca NUMÃR (0 este nelimitat\n"
"  -O,\t--output-document=FIºIER \tscrie documentele în FIªIER.\n"
"  -nc, --no-clobber\t\tnu secþiona fiºierele existente sau utilizeazã  sufixe .#\n"
"  -c,  --continue\t\t    continuã sã iei un fiºier downloadat parþial.\n"
"\t--progress=TIP\t\t    selecteazã mod mãsurare desfaºurare download.\n"
"  -N,  --timestamping\t\tnu aduce fiºierele dacã nu sunt mai noi decât cele locale.\n"
"  -S,  --server-response\ttipãreºte rãspunsul serverului.\n"
"       --spider\t\t    nu descãrca nimic.\n"
"  -T,  --timeout=SECUNDE\taºteaptã 1...SECUNDE între reîncercãrile de aducere.\n"
"  -Y,  --proxy=on/off\t\tactiveazã (on) sau dezactiveazã(off) proxy.\n"
"  -Q,  --quota=NUMÃR\t\tseteazã cotã de descãrcare la NUMÃR.\n"
"\t--limit-rate=RATÃ\t    limiteazã ratã descãrcare la RATã.\n"
"\n"

#: src/main.c:174
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Directoare:\n"
"  -nd  --no-directories            nu crea directoare.\n"
"  -x,  --force-directories         forþeazã crearea directoarelor.\n"
"  -nH, --no-host-directories       nu crea directoare gazdã.\n"
"  -P,  --directory-prefix=PREFIX   salveazã fiºierele în PREFIX/...\n"
"       --cut-dirs=NUMÃR            Ignorã NUMÃR componente director remote.\n"
"\n"

#: src/main.c:182
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
"Opþiuni HTTP:\n"
"       --http-user=USER      seteazã userul http ca USER.\n"
"       --http-passwd=PASS    seteazã parola http ca PASS.\n"
"  -C,  --cache=on/off        (nu)permite date server-cached (în mod normal permis).\n"
"  -E,  --html-extension      salveazã toate documentele text/html cu extensie .html.\n"
"       --ignore-length       ignorã câmpul header `Content-Length'.\n"
"       --header=ªIR          insereazã ªIR în headere.\n"
"       --proxy-user=USER     seteazã USER drept nume utilizator proxy.\n"
"       --proxy-passwd=PASS   seteazã PASS drept parolã proxy.\n"
"       --referer=URL         include headerul `Referer: URL' în cererea HTTP.\n"
"  -s,  --save-headers        salveazã headerele HTTP în fiºier.\n"
"  -U,  --user-agent=AGENT    identificare ca AGENT în loc de Wget/VERSIUNE.\n"
"       --no-http-keep-alive  dezactiveazã HTTP keep-alive (conexiuni persistente).\n"
"       --cookies=off         nu utiliza cookies.\n"
"       --load-cookies=FIªIER încãrcã cookies din FIªIER înainte de sesiune.\n"
"       --save-cookies=FIªIER salveazã cookies în FIªIER dupã sesiune.\n"
"\n"

#: src/main.c:200
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"Opþiuni FTP:\n"
"  -nr, --dont-remove-listing   nu ºterge fiºierele `.listing'.\n"
"  -g,  --glob=on/off           activare/dezactivare nume globale.\n"
"       --passive-ftp           utilizeazã modul de transfer \"pasiv\".\n"
"       --retr-symlinks         în recursiune, adu fiºierele linkuite (nu directoarele).\n"
"\n"

#: src/main.c:207
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
"Aducere recursivã:\n"
"  -r,  --recursive          absorbire web recursivã -- folosiþi cu atenþie!\n"
"  -l,  --level=NUMBÃR       adâncime recursiune maximã (inf sau 0 pentru infinitã).\n"
"       --delete-after       ºterge fiºierele locale dupa descãrcare.\n"
"  -k,  --convert-links      converteºte linkuri non-relative în relative.\n"
"  -K,  --backup-converted   înainte de a converti fiºierul X, back-up ca X.orig.\n"
"  -m,  --mirror             opþiune scurtã echivalentã cu -r -N -l inf -nr.\n"
"  -p,  --page-requisites    aducere toate imaginile, etc. necesare pentru afiºarea paginii HTML.\n"
"\n"

#: src/main.c:217
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
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Acceptare/refuz recursive:\n"
"  -A,  --accept=LISTÃ             listã separatã prin virgule a extensiilor acceptate.\n"
"  -R,  --reject=LISTÃ             listã separatã prin virgule a extensiilor refuzate.\n"
"  -D,  --domains=LISTÃ            listã separatã prin virgule a domeniilor acceptate.\n"
"       --exclude-domains=LISTÃ    listã separatã prin virgule a domeniilor refuzate.\n"
"       --follow-ftp               urmeazã legãturile FTP din documente HTML.\n"
"       --follow-tags=LISTÃ        listã separatã prin virgule a tagurilor HTML urmate.\n"
"  -G,  --ignore-tags=LISTÃ        listã separatã prin virgule a tagurilor HTML ignorate.\n"
"  -H,  --span-hosts                 viziteazã ºi site-uri strãine în recursiune.\n"
"  -L,  --relative                   urmeazã doar linkurile relative.\n"
"  -I,  --include-directories=LISTÃ  listã directoare permise.\n"
"  -X,  --exclude-directories=LISTÃ  listã directoare excluse.\n"
"  -np, --no-parent                  nu urca la directorul pãrinte.\n"
"\n"

#: src/main.c:232
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Rapoarte de bug-uri prin mail ºi sugestii la <bug-wget@gnu.org>.\n"

#: src/main.c:420
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: suport de debug necompilat.\n"

#: src/main.c:472
msgid "Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"
msgstr "Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"

#: src/main.c:474
msgid ""
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Acest program este distribuit în speranþa cã va fi folositor,\n"
"dar FÃRÃ NICI O GARANÞIE; chiar fãrã garanþia presupusã a\n"
"VANDABILITÃÞII sau POTRIVIRII PENT UN SCOP ANUME.  Citiþi\n"
"Licenþa Publicã Generalã GNU pentru mai multe detalii.\n"

#: src/main.c:479
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr ""
"\n"
"Original scris de Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:578
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: comandã invalidã\n"

#: src/main.c:631
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opþiune ilegalã -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:634 src/main.c:676 src/main.c:722
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Încercaþi `%s --help' pentru mai multe opþiuni.\n"

#: src/main.c:702
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Nu pot fi ºi detaliat ºi silenþios în acelaºi timp.\n"

#: src/main.c:708
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Nu pot ºi identifica pentru timp (timestamp) ºi lãsa fiºierele nesecþionate în acelaºi timp.\n"

#. No URL specified.
#: src/main.c:717
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL lipsã\n"

#: src/main.c:834
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Nici un URL gãsit în %s.\n"

#: src/main.c:843
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"FINALIZAT --%s--\n"
"Downloadat: %s octeþi în %d fiºiere\n"

#: src/main.c:851
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Cotã de download (%s octeþi) DEPÃªITÃ!\n"

#: src/mswindows.c:120
msgid "Continuing in background.\n"
msgstr "Continui în fundal.\n"

#: src/mswindows.c:122 src/utils.c:457
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Output-ul va fi scris în `%s'.\n"

#: src/mswindows.c:202
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Startare WinHelp %s\n"

#: src/mswindows.c:229 src/mswindows.c:236
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Nu am putut gãsi un driver de socket folosibil.\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: avertisment: Simbolul \"%s\" apare înainte de numele maºinii\n"

#: src/netrc.c:396
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: simbol necunoscut \"%s\"\n"

#: src/netrc.c:460
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Folosire: %s NETRC [NUME_HOST]\n"

#: src/netrc.c:470
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: n-am putut stabili %s: %s\n"

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:224
#, c-format
msgid ""
"\n"
"%*s[ skipping %dK ]"
msgstr ""
"\n"
"%*s[ omitere %dK ]"

#: src/progress.c:391
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Specificare punct invalidã `%s'; lãsat neschimbat.\n"

#: src/recur.c:350
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "ªtergere %s pentru cã oricum ar fi trebuit refuzat.\n"

#: src/recur.c:935
#, c-format
msgid "Converted %d files in %.2f seconds.\n"
msgstr "%d fiºiere convertite în %.2f secunde.\n"

#: src/res.c:540
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Se încarcã robots.txt; ignoraþi erorile.\n"

#: src/retr.c:363
msgid "Could not find proxy host.\n"
msgstr "Nu s-a putut gãsi serverul proxy.\n"

#: src/retr.c:375
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Eroare în analiza URL proxy: %s: %s.\n"

#: src/retr.c:384
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Eroare în URL proxy %s: Trebuie sã fie HTTP.\n"

#: src/retr.c:476
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d redirectãri depãºite.\n"

#: src/retr.c:491
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Ciclu de redirectare detectat.\n"

#: src/retr.c:608
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Renunþ.\n"
"\n"

#: src/retr.c:608
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Reîncerc.\n"
"\n"

#: src/url.c:1875
#, c-format
msgid "Converting %s... "
msgstr "Convertire %s... "

#: src/url.c:1888
msgid "nothing to do.\n"
msgstr "nimic de fãcut.\n"

#: src/url.c:1896 src/url.c:1920
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Nu pot converti linkurile în %s: %s\n"

#: src/url.c:1911
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Nu pot ºterge `%s': %s\n"

#: src/url.c:2117
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Nu pot face backup la %s ca %s: %s\n"

#: src/utils.c:90
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Memorie plinã.\n"

#. parent, no error
#: src/utils.c:455
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Continui în fundal, pid %d.\n"

#: src/utils.c:499
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Nu am putut scoate(unlink) symlinkul `%s': %s\n"
