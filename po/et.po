# Estonian translations for GNU wget.
# Copyright (C) 1998 Free Software Foundation, Inc.
# Toomas Soome <tsoome@ut.ee>, 1998.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.5.3\n"
"POT-Creation-Date: 1998-06-23 23:53+0200\n"
"PO-Revision-Date: 1998-12-07 22:18 +0200\n"
"Last-Translator: Toomas Soome <tsoome@ut.ee>\n"
"Language-Team: Estonian <linux-ee@eenet.ee>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-1\n"
"Content-Transfer-Encoding: 8-bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Võtan ühendust serveriga %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Ei saa ühendust serveriga %s:%hu.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "ühendus loodud!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Meldin serverisse kasutajana %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Vigane serveri vastus, sulgen juhtühenduse.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Vigane serveri tervitus.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Kirjutamine ebaõnnestus, sulgen juhtühenduse.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Server ei luba meldida.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Vigane meldimine.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Melditud!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tundmatu tüüp `%c', sulgen juhtühenduse.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "tehtud.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD pole vajalik.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Kataloogi `%s' pole.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "tehtud.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD ei ole kohustuslik.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Ei saa algatada PASV ülekannet.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Ei suuda analüüsida PASV vastust.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Üritan ühenduda serveriga %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "tehtud.  "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind operatsiooni viga (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Vale PORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST ebaõnnestus, alustan algusest.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Faili `%s' pole.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Faili või kataloogi `%s' pole.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Pikkus: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s on veel]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (autoriseerimata)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, sulgen juhtühenduse.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - andme ühendus: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Juhtühendus suletud.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Andmete ülekanne katkestatud.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Fail `%s' on juba olemas, ei tõmba.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(katse:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' salvestatud [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Kasutan `%s' ajutise listingu failina.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Kustutatud `%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekursiooni sügavus %d ületab maksimum sügavust %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Lokaalne fail `%s' on uuem, ei tõmba.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Suurused ei klapi (lokaalne %ld), uuendan.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Vigane sümbol viite nimi, jätan vahele.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Korrektne sümbol viide on juba olemas %s -> %s\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Loon sümbol viite %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Ei toeta sümbol viiteid, jätan `%s' vahele.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Jätan kataloogi `%s' vahele.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tundmatu faili tüüp.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: vigane aeg.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Ei tõmba katalooge, kuna sügavus on %d (maks. %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Jätame `%s' vahele, ta on välistatud või pole kaasatud.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Keelame `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Jokker `%s' ei anna midagi.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Kirjutasin HTML-iseeritud indeksi faili `%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Kirjutasin HTML-iseeritud indeksi faili `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: võti `%s' on arusaamatu\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: võti `--%s' ei luba argumenti\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: võti `%c%s' ei luba argumenti\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: võti `%s' nquab argumenti\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: tundmatu võti `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: tundmatu võti `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: illegaalne võti -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: võti nõuab argumenti -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Ei suuda tuvastada kasutaja id'd.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Hoiatus: uname ebaõnnestus %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Hoiatus: gethostname ebaõnnestus\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Hoiatus: ei suuda tuvastada lokaalset IP aadressi.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Hoiatus: ei saa lokaalse IP aadressi reversit.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Hoiatus: lokaalse aadressi revers ei anna FQDN!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Hosti ei leitud"

#: src/host.c:541
msgid "Unknown error"
msgstr "Tundmatu viga"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s indeks serveris %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "tundmatu aeg       "

#: src/html.c:467
msgid "Fail        "
msgstr "Fail        "

#: src/html.c:470
msgid "Directory   "
msgstr "Kataloog    "

#: src/html.c:473
msgid "Link        "
msgstr "Viide       "

#: src/html.c:476
msgid "Not sure    "
msgstr "Pole kindel "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s baiti)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "HTTP päringu kirjutamine ebaõnnestus.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s päring saadetud, ootan vastust... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Päiste analüüsil sain faili lõpu teate.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Päiste lugemise viga (%s).\n"

#: src/http.c:587
msgid "No data received"
msgstr "Andmeid ei saanudki"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Katkine staatuse rida"

#: src/http.c:594
msgid "(no description)"
msgstr "(kirjeldus puudub)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Autoriseerimine ebaõnnestus.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Tundmatu autentimis skeem.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Asukoht: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "määramata"

#: src/http.c:750
msgid " [following]"
msgstr " [järgnev]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Pikkus: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s veel)"

#: src/http.c:774
msgid "ignored"
msgstr "ignoreerin"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Hoiatus: HTTP ei toeta jokkereid.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Fail `%s' on juba olemas, ei tõmba.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Ei saa kirjutada faili `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "VIGA: Ümbersuunamine (%d) ilma asukohata.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s VIGA %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified päist pole -- ei kasuta aja-stampe.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified päis on vigane -- ignoreerin aja-stampi.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Kauge fail on uuem, laen alla.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' salvestatud [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Ühendus suletud baidil %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' salvestatud [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Ühendus suletud baidil %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Lugemise viga baidil %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Lugemise viga baidil %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: %s ei saa lugeda (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Viga %s's real %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Hoiatus: Nii süsteemne kui kasutaja wgetrc on `%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: tundmatu käsklus`%s', väärtus `%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Palun kasuta `on' või `off'.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s %s: Vigane spetsifikatsioon `%s'.\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Vigane spetsifikatsioon `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Kasuta: %s [VÕTI]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, mitte-interaktiivne võrgu imeja.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr ""
"\n"
"Kohustuslikud argumendid pikkadele võtmetele\n"
"on kohustuslikud ka lühikestele võtmetele.\n"
"\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"Start:\n"
"  -V,  --version           anna Wget versioon ja lõpeta töö.\n"
"  -h,  --help              anna abi.\n"
"  -b,  --background        mine tausta.\n"
"  -e,  --execute=COMMAND   käivita `.wgetrc' käsk.\n"
"\n"

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
"Logimine ja sisendfail:\n"
"  -o,  --output-file=FAIL     logi teated faili FAIL.\n"
"  -a,  --append-output=FAIL   lisa teated faili FAIL.\n"
"  -d,  --debug                trüki silumise teated.\n"
"  -q,  --quiet                vaikselt.\n"
"  -v,  --verbose              lobise (see on vaikimisi).\n"
"  -nv, --non-verbose          keela lobisemine, luba asjalikud teated.\n"
"  -i,  --input-file=FAIL      loe URLid failist FAIL.\n"
"  -F,  --force-html           käsitle sisendfaili HTMLina.\n"
"\n"

#: src/main.c:133
msgid ""
"Download:\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
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
"Allalaadimine:\n"
"  -t,  --tries=NUMBER           katsete arvuks NUMBER (0 piiramata).\n"
"  -O   --output-document=FAIL   kirjuta dokumendid faili FAIL.\n"
"  -nc, --no-clobber             ära riku olemasolevaid faile.\n"
"  -c,  --continue               jätka olemasoleva faili allalaadimist.\n"
"       --dot-style=STIIL        kasuta laadimise näitamise stiili STIIL.\n"
"  -N,  --timestamping           ära tõmba vanemaid faile kui lokaalsed.\n"
"  -S,  --server-response        trüki serveri vastused.\n"
"       --spider                 ara tõmba midagi.\n"
"  -T,  --timeout=SEKUNDEID        kasuta lugemise timeoutina SEKUNDEID.\n"
"  -w,  --wait=SEKUNDEID           oota SEKUNDEID päringute vahel.\n"
"  -Y,  --proxy=on/off           proxy kasutamine.\n"
"  -Q,  --quota=NUMBER           kasuta kvooti NUMBER.\n"
"\n"

#: src/main.c:147
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Kataloogid:\n"
"  -nd  --no-directories            ära loo katalooge.\n"
"  -x,  --force-directories         kohustuslik kataloogide tekitamine.\n"
"  -nH, --no-host-directories       ära loo hosti kataloogi.\n"
"  -P,  --directory-prefix=PREFIX   salvesta failid kataloogi PREFIX/...\n"
"       --cut-dirs=NUMBER           ignoreeri kataloogi komponente > NUMBER.\n"
"\n"

#: src/main.c:154
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"\n"
msgstr ""
"HTTP võtmed:\n"
"       --http-user=USER      kasuta http kasutajat USER.\n"
"       --http-passwd=PASS    kasuta http parooli PASS.\n"
"  -C,  --cache=on/off        cache kasutamine (tavaliselt lubatud kasutada).\n"
"       --ignore-length       inoreeri `Content-Length' päise välja.\n"
"       --header=STRING       lisa STRING päisesse.\n"
"       --proxy-user=USER     USER proxy kasutajanimeks.\n"
"       --proxy-passwd=PASS   PASS proxy parooliks.\n"
"  -s,  --save-headers        salvesta HTTP päised.\n"
"  -U,  --user-agent=AGENT    identifitseeri kui AGENT, mitte kui Wget/VERSION.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP võtmed:\n"
"       --retr-symlinks   tõmba ka FTP sümbol lingid.\n"
"  -g,  --glob=on/off     lülita faili nime täiendamine sisse või välja.\n"
"       --passive-ftp     kasuta \"passive\" ülekande moodi.\n"
"\n"

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
"Rekursiivne pärimine:\n"
"  -r,  --recursive            rekursiivne imemine -- kasuta ettevaatlikult!.\n"
"  -l,  --level=NUMBER         maksimaalne rekursiooni sügavus (0 - piiramata).\n"
"       --delete-after         kustuta allalaetud failid.\n"
"  -k,  --convert-links        teisenda lingid suhtelisteks.\n"
"  -m,  --mirror               kasuta peegeldamiseks kasulikke vötmeid.\n"
"  -nr, --dont-remove-listing  ära kustuta `.listing' faile.\n"
"\n"

#: src/main.c:178
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                list of accepted extensions.\n"
"  -R,  --reject=LIST                list of rejected extensions.\n"
"  -D,  --domains=LIST               list of accepted domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected domains.\n"
"  -L,  --relative                   follow relative links only.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Rekursiivne accept/reject:\n"
"  -A,  --accept=LIST                lubatud laienduste list.\n"
"  -R,  --reject=LIST                keelatud laienduste list.\n"
"  -D,  --domains=LIST               lubatud doomenite list.\n"
"       --exclude-domains=LIST       komadega eraldatud keelatud doomenite list.\n"
"  -L,  --relative                   järgne ainult suhtelisi viiteid.\n"
"       --follow-ftp                 järgne HTML dokumentides FTP linkidele.\n"
"  -H,  --span-hosts                 mine ka teistesse serveritesse.\n"
"  -I,  --include-directories=LIST   lubatud kataloogide list.\n"
"  -X,  --exclude-directories=LIST   välistatud kataloogide list.\n"
"  -nh, --no-host-lookup             ära lahenda hostide nimesid.\n"
"  -np, --no-parent                  ära tõuse vanem kataloogini.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Saada soovitused ja vigade kirjeldused aadressil <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: silumise tugi pole sisse kompileeritud.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nSelle programmi kirjutas Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: vigane käsklus\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: illegaalne võti -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Proovi `%s --help' lisa võtmete saamiseks.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Ei saa korraga lobiseda ja vait olla.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Ei saa samaaegselt muuta failide aegu ja mitte puutuda vanu faile.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: puudub URL\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "%s ei sisalda URLe.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"LÕPETATUD --%s--\n"
"Alla laetud: %s baiti kokku %d failis\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Allalaadimise kvoot  (%s baiti) ON ÜLETATUD!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "sain %s, suunan väljundi faili `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Sain CTRL+Break, suunan väljundi aili `%s'.\n"
"Täitmine jatkub taustas.\n"
"Wgeti peatamiseks vajuta CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Jätkan taustas.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Väljund kirjutatakse faili `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Stardin WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Ei leia kasutuskõlblikku pistiku programmi.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: hoiatus: \"%s\" identifikaator on enne masina nime\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: tundmatu lekseem \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Kasuta: %s NETRC [HOSTINIMI]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: stat operatsioon ebaõnnestus %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Kustutan %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Kustutan %s, kuna see peaks olema tagasi lükatud.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Laen robots.txti faili; palun ignoreerige võimalikk vigu.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ hüppan üle %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Ei leia proxy serverit.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy: %s: Peab olema HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Ümbersuunamine iseendale.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Annan alla.\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Proovin uuesti.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Viga (%s): Viide %s on ilma baasita.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Viga(%s): Baas %s on suhteline, puudub viitav URL.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Teisendan %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Ei suuda teisendada linke %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: mälu ei jätku.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Tundmatu/mittetoetatav protokoll"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Vigane pordi spetsifikatsioon"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Vigane hosti nimi"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Ei õnnestu kustutada sümbol viidet `%s': %s\n"
