# Croatian messages for GNU Wget
# Copyright (C) 1998 Free Software Foundation, Inc.
# Hrvoje Niksic <hniksic@srce.hr>, 1998.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.2-b2\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1998-02-29 21:05+01:00\n"
"Last-Translator: Hrvoje Niksic <hniksic@srce.hr>\n"
"Language-Team: Croatian <hr-translation@bagan.srce.hr>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Spajam se na %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "%s:%hu odbija vezu.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "spojen!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Logiram se kao %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Gre¹ka u odgovoru, zatvaram kontrolnu vezu.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Gre¹ka u poslu¾iteljevom pozdravu.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Write nije uspio, zatvaram kontrolnu vezu.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Poslu¾itelj odbija prijavu.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Pogre¹na prijava.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Ulogiran!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Nepoznat tip `%c', zatvaram kontrolnu vezu.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "gotovo."

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD ne treba.\n"

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr "Nema direktorija `%s'.\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "gotovo.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD se ne tra¾i.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Ne mogu otpoèeti PASV prijenos.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Ne mogu raspoznati PASV odgovor.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Poku¹at æu se spojiti na %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "gotovo.  "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Gre¹ka u bindu (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Pogre¹an PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST nije uspio, poèinjem ispoèetka.\n"

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Nema datoteke `%s'.\n"
"\n"

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Nema datoteke ili direktorija `%s'.\n"
"\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Duljina: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [jo¹ %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (neautorizirana)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, zatvaram kontrolnu vezu.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Podatkovna veza: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Kontrolna veza prekinuta.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Prijenos podataka prekinut.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Datoteka `%s' veæ postoji, ne skidam.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(pok:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' snimljen [%ld]\n"
"\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Koristim `%s' kao privremenu datoteku za listing.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Izbrisao `%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Dubina rekurzije %d prelazi najveæu dozvoljenu %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""
"Lokalna datoteka `%s' je novija, ne skidam.\n"
"\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Velièine se ne sla¾u (lokalno %ld), skidam.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Pogre¹no ime simbolièkog linka, preskaèem.\n"

#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Veæ postoji ispravan link %s -> %s\n"
"\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Stvaram simbolièki link %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Linkovi nisu podr¾ani, preskaèem link `%s'.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Preskaèem direktorij `%s'.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: nepoznata/nepodr¾ana vrsta datoteke.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: pogre¹no vrijeme.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Ne skidam direktorije jer je dubina %d (maksimalno %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Ne idem u `%s' jer je iskljuèen ili nije ukljuèen.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Odbijam `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Ni¹ta ne ide uz `%s'.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Snimio HTML-iziran indeks u `%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Snimio HTML-iziran indeks u `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: opcija `%s' je dvosmislena\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: uz opciju `--%s' ne ide argument\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: opcija `%c%s' ne dozvoljava argument\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: opcija `%s' tra¾i argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: nepoznata opcija `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: nepoznata opcija `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: nedozvoljena opcija -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: opcija tra¾i argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Ne mogu utvrditi user-id.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Upozorenje: uname nije uspio: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Upozorenje: gethostname nije uspio\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Upozorenje: ne mogu utvrditi lokalnu IP adresu.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Upozorenje: ne mogu napraviti reverzni lookup lokalne IP adrese.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Upozorenje: reverzni lookup lokalne adrese ne daje FQDN!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Raèunalo nije pronaðeno"

#: src/host.c:541
msgid "Unknown error"
msgstr "Nepoznata gre¹ka"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Indeks direktorija /%s na %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "nepoznato vrijeme    "

#: src/html.c:467
msgid "File        "
msgstr "Datoteka    "

#: src/html.c:470
msgid "Directory   "
msgstr "Direktorij  "

#: src/html.c:473
msgid "Link        "
msgstr "Link        "

#: src/html.c:476
msgid "Not sure    "
msgstr "Ne znam     "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bajtova)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Nisam uspio poslati HTTP zahtjev.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s zahtjev poslan, èekam odgovor... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Kraj datoteke za vrijeme obrade zaglavlja.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Gre¹ka pri èitanju zaglavlja (%s).\n"

#: src/http.c:587
msgid "No data received"
msgstr "Podaci nisu primljeni"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Deformirana statusna linija"

#: src/http.c:594
msgid "(no description)"
msgstr "(bez opisa)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Ovjera nije uspjela.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Nepoznata metoda ovjere.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Polo¾aj: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "neodreðen"

#: src/http.c:750
msgid " [following]"
msgstr " [pratim]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Duljina: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (jo¹ %s)"

#: src/http.c:774
msgid "ignored"
msgstr "zanemarena"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Upozorenje: wildcardi nisu podr¾ani za HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Datoteka `%s' veæ postoji, ne skidam.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Ne mogu pisati u `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "GRE©KA: Redirekcija (%d) bez novog polo¾aja (location).\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s GRE©KA %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Nedostaje Last-Modified zaglavlje -- ignoriram vremensku oznaku.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Nevaljan Last-Modified header -- ignoriram vremensku oznaku.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Datoteka na poslu¾itelju je novija, skidam.\n"

#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' snimljen [%ld/%ld]\n"
"\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Veza zatvorena na bajtu %ld. "

#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' snimljen [%ld/%ld])\n"
"\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Veza zatvorena na bajtu %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Gre¹ka pri èitanju na bajtu %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Gre¹ka pri èitanju na bajtu %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Ne mogu proèitati %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Gre¹ka u %s na liniji %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Upozorenje: sistemski i korisnikov wgetrc su `%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: Nepoznata naredba `%s', vrijednost `%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Molim postavite na on ili off.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Pogre¹na specifikacija `%s'\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "wget: %s: Pogre¹na specifikacija `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Uporaba: %s [OPCIJA]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, alat za neinteraktivno skidanje preko mre¾e.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Ako duga opcija zahtijeva argument, tada to vrijedi i za kratku.\n"
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
"Pokretanje:\n"
"  -V,  --version           prika¾i verziju Wget-a i izaði.\n"
"  -h,  --help              ispi¹i pomoæ.\n"
"  -b,  --background        radi u pozadini nakon pokretanja.\n"
"  -e,  --execute=NAREDBA   izvr¹i naredbu `.wgetrc'-a.\n"
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
"Logging and input file:\n"
"  -o,  --output-file=DATOTEKA     spremaj poruke u DATOTEKU.\n"
"  -a,  --append-output=DATOTEKA   dodaj poruke u DATOTEKU.\n"
"  -d,  --debug                    ispisuj debug izlaz.\n"
"  -q,  --quiet                    ti¹ina (bez ispisa).\n"
"  -v,  --verbose                  ukljuèi puni ispis (podrazumijeva se).\n"
"  -nv, --non-verbose              iskljuèi veæinu ispisa.\n"
"  -i,  --input-file=DATOTEKA      èitaj URL-ove iz DATOTEKE.\n"
"  -F,  --force-html               tretiraj ulaznu datoteku kao HTML.\n"
"\n"

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
"Download:\n"
"  -t,  --tries=BROJ                 broj poku¹aja na BROJ (0 je beskonaèno)\n"
"  -O   --output-document=DATOTEKA   pi¹i dokumente u DATOTEKU.\n"
"  -nc, --no-clobber                 nemoj prebrisati postojeæe datoteke.\n"
"  -c,  --continue                   restart getting an existing file.\n"
"       --dot-style=STIL             postavi stil prikaza skidanja.\n"
"  -N,  --timestamping               ne skidaj datoteke starije od lokalnih.\n"
"  -S,  --server-response            ispisuj poslu¾iteljev odaziv.\n"
"       --spider                     ni¹ta ne skidaj.\n"
"  -T,  --timeout=SEKUNDE            postavi timeout èitanja na SEKUNDE.\n"
"  -w,  --wait=SEKUNDE               èekaj SEKUNDE izmeðu skidanja.\n"
"  -Y,  --proxy=on/off               ukljuèi ili iskljuèi proxy.\n"
"  -Q,  --quota=BROJ                 postavi ogranièenje skidanja na BROJ.\n"
"\n"

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
"Direktoriji:\n"
"  -nd  --no-directories             ne stvaraj direktorije.\n"
"  -x,  --force-directories          uvijek stvaraj direktorije.\n"
"  -nH, --no-host-directories        ne stvaraj direktorije po raèunalima.\n"
"  -P,  --directory-prefix=PREFIKS   snimaj datoteke u PREFIKS/...\n"
"       --cut-dirs=BROJ              ignoriraj BROJ stranih direktorija.\n"
"\n"

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
"HTTP options:\n"
"       --http-user=KORISNIK     postavi HTTP korisnika na KORISNIK.\n"
"       --http-passwd=ZAPORKA    postavi HTTP zaporku na ZAPORKA.\n"
"  -C,  --cache=on/off           dozvoli ili zabrani ke¹iranje na "
"poslu¾itelju\n"
"                                  (obièno dozvoljeno).\n"
"       --ignore-length          ignoriraj `Content-Length' zaglavlje.\n"
"       --header=STRING          umetni STRING meðu zaglavlja.\n"
"       --proxy-user=KORISNIK    postavi KORISNIKA kao proxy korisnika\n"
"       --proxy-passwd=ZAPORKA   postavi proxy zaporku na ZAPORKU.\n"
"  -s,  --save-headers           snimaj HTTP zaglavlja na disk.\n"
"  -U,  --user-agent=KLIJENT     identificiraj se kao KLIJENT umjesto\n"
"                                  Wget/VERZIJA.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP options:\n"
"       --retr-symlinks   skidaj FTP simbolièke linkove.\n"
"  -g,  --glob=on/off     ukljuèi ili iskljuèi globbing.\n"
"       --passive-ftp     koristi \"pasivni\" mod prijenosa.\n"
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
"Rekurzivno skidanje:\n"
"  -r,  --recursive             rekurzivno skidanje -- koristi pa¾ljivo!\n"
"  -l,  --level=NUMBER          maksimalna dubina rekurzije (0 za "
"beskonaènu).\n"
"       --delete-after          bri¹i skinute datoteke.\n"
"  -k,  --convert-links         konvertiraj apsolutne linkove u relativne.\n"
"  -m,  --mirror                ukljuèi opcije pogodne za \"mirror\".\n"
"  -nr, --dont-remove-listing   ne uklanjaj `.listing' datoteke.\n"
"\n"

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
"Rekurzivno prihvaæanje/odbijanje:\n"
"  -A,  --accept=POPIS                popis prihvaæenih nastavaka.\n"
"  -R,  --reject=POPIS                popis odbijenih nastavaka.\n"
"  -D,  --domains=POPIS               popis prihvaæenih domena.\n"
"       --exclude-domains=POPIS       zarezom odvojen popis odbijenih "
"domena.\n"
"  -L,  --relative                    prati samo relativne linkove.\n"
"       --follow-ftp                  prati FTP linkove iz HTML dokumenata.\n"
"  -H,  --span-hosts                  idi na strana raèunala pri rekurzivnom\n"
"                                       skidanju.\n"
"  -I,  --include-directories=POPIS   popis dozvoljenih direktorija.\n"
"  -X,  --exclude-directories=POPIS   popis nedozvoljenih direktorija.\n"
"  -nh, --no-host-lookup              nemoj pregledavati hostove DNS-om.\n"
"  -np, --no-parent                   ne idi u direktorij vi¹e.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "©aljite izvje¹taje o bugovima i prijedloge na <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: podr¹ka za debugiranje nije ugraðena.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Sva prava zadr¾ana.  Ovaj program distribuira se u nadi da æe biti\n"
"koristan, ali BEZ IKAKVOG JAMSTVA; bez èak i impliciranog jamstva\n"
"PROIZVODNOSTI ili UPOTREBLJIVOSTI ZA ODREÐENU SVRHU.  Pogledajte GNU\n"
"General Public License za vi¹e detalja.\n"

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""
"\n"
"Napisao Hrvoje Nik¹iæ <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: nedozvoljena naredba\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: nedozvoljena opcija -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Poku¹ajte `%s --help' za vi¹e opcija.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Ne mogu istovremeno biti verbozan i tih.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Ne mogu istovremeno paziti na vrijeme i ne gaziti stare datoteke.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: nedostaje URL\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Nijedan URL nije pronaðen u %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"ZAVR©IO --%s--\n"
"Skinuo: %s bajta u %d datoteka\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Kvota (%s bajtova) je PREKORAÈENA!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s primljen, usmjeravam izlaz na `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break je pritisnut, usmjeravam izlaz u `%s'.\n"
"Izvr¹avanje se nastavlja u pozadini.\n"
"Mo¾ete prekinuti Wget pritiskom na CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Nastavljam u pozadini.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Izlaz se sprema u `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Pokreæem WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Ne mogu naæi upotrebljiv driver za sockete.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d: upozorenje: \"%s\" token se pojavljuje prije naziva stroja\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: nepoznat token \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Uporaba: %s NETRC [RAÈUNALO]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: ne mogu stat-irati %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Uklanjam %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Uklanjam %s buduæi da bi ga trebalo odbiti.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Uèitavam robots.txt; molim ne obazirati se na gre¹ke.\n"

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"         [ preskaèem %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Ne mogu naæi proxy raèunalo.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Mora biti HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Redirekcija na samog sebe.\n"

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Odustajem.\n"
"\n"

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Poku¹avam ponovo.\n"
"\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Gre¹ka (%s): Zadan je link %s bez osnove.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Gre¹ka (%s): Baza %s je relativna, bez referirajuæeg URL-a.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konvertiram %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Ne mogu konvertirati linkove u %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Nema dovoljno memorije.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Nepoznat/nepodr¾an protokol"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Pogre¹na specifikacija porta"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Pogre¹an naziv raèunala"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Ne mogu izbrisati link `%s': %s\n"
