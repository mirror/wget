# Slovenian messages for GNU Wget
# Copyright (C) 1999 Free Software Foundation, Inc.
# Roman Maurer <roman.maurer@fmf.uni-lj.si>, 1999.
# $Id: sl.po 176 2000-11-23 18:05:26Z hniksic $
#
# Spremembe:
#
# LLLL-MM-DD     avtor     sprememba
# -------------------------------------------------------------------
# 1999-10-04     roman     sprememba e-naslova
# 1999-07-09     roman     razlièica, ki jo je TP-robot sprejel
# 1999-05-06     roman     kot je bila poslana na lugos-slo@lugos.si
# 1999-03-11     roman     prva razlièica
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1999-03-11 19:00+0100\n"
"PO-Revision-Date: 1999-10-04 10:30+02:00\n"
"Last-Translator: Roman Maurer <roman.maurer@hermes.si>\n"
"Language-Team: Slovenian <sl@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Povezujem se na %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "%s:%hu zavraèa zvezo.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "prikljuèen!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Prijavljam se kot %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Napaèen odgovor, zapiram nadzorno povezavo.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Napaka v pozdravu stre¾nika.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Pisanje neuspe¹no, zapiram nadzorno povezavo.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Stre¾nik zavraèa prijavo.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Napaèna prijava.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Prijavljen!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Neznan tip `%c', zapiram nadzorno zvezo.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "opravljeno."

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD ni potreben.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Ni imenika z imenom `%s'.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "konèano.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD ni zahtevan.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Ne morem zaèeti prenosa PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Ne morem razèleniti odgovora PASV.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Poskusil se bom prikljuèiti na %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "opravljeno. "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Napaka pri povezovanju (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Neveljaven PORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST neuspe¹en, zaèenjam znova.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Ni datoteke `%s'.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Ni datoteke ali imenika `%s'.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Dol¾ina: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [¹e %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (neavtorizirana)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, zapiram nadzorno zvezo.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Podatkovna zveza: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Nadzorna zveza prekinjena.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Prenos podatkov prekinjen.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Datoteka `%s' ¾e obstaja, ne jemljem.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(posk:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' posnet [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Uporabljam `%s' kot zaèasno datoteko za izpis.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Odstranil `%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Globina rekurzije %d presega najveèjo dovoljeno %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Lokalna datoteka `%s' je novej¹a, ne jemljem.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Velikosti se ne ujemata (lokalno %ld), jemljem.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Neveljavno ime simbolne povezave, preskakujem.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Obstaja ¾e pravilna simbolna povezava %s -> %s\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Ustvarjam simbolno povezavo %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Povezave niso podprte, preskakujem simbolno povezavo `%s'.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Preskakujem imenik `%s'.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: neznana/nepodprta vrsta datoteke.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: okvarjena oznaèba èasa.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Ne jemljem imenikov, ker je globina %d (maksimalno %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Ne grem v `%s', ker je izkljuèen ali pa ni vkljuèen.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Zavraèam `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Ni zadetkov za vzorec `%s'.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Kazalo v HTML zapisal kot `%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Kazalo v HTML zapisal kot `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: izbira `%s' je dvoumna\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: izbira `--%s' ne dopu¹èa dodatnih argumentov\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: izbira `%c%s' ne dopu¹èa dodatnih argumentov\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: izbira `%s' zahteva argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: neprepoznana izbira `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: neznana izbira `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: nedovoljena izbira -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: izbira zahteva argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Ne morem doloèiti identitete uporabnika.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Opozorilo: klic uname neuspe¹en: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Opozorilo: klic gethostname neuspe¹en\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Opozorilo: ne morem doloèiti lokalnega naslova IP.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Opozorilo: lokalnemu naslovu IP ni mo¾no pripisati imena.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Opozorilo: nepopolno ime za lokalni naslov IP!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Gostitelj ni bil najden"

#: src/host.c:541
msgid "Unknown error"
msgstr "Neznana napaka"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Kazalo imenika /%s na %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "neznan èas         "

#: src/html.c:467
msgid "File        "
msgstr "Datoteka    "

#: src/html.c:470
msgid "Directory   "
msgstr "Imenik      "

#: src/html.c:473
msgid "Link        "
msgstr "Povezava    "

#: src/html.c:476
msgid "Not sure    "
msgstr "Neznano     "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bajtov)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Ni mi uspelo poslati zahteve HTTP.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s zahteva poslana, èakam odgovor... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Pri razèlenjevanju glave naletel na konec datoteke.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Napaka pri branju glave (%s).\n"

#: src/http.c:587
msgid "No data received"
msgstr "Brez sprejetih podatkov"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Zmalièena statusna linija"

#: src/http.c:594
msgid "(no description)"
msgstr "(brez opisa)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Avtorizacija neuspe¹na.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Neznata metoda avtentifikacije.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Polo¾aj: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "nedoloèen"

#: src/http.c:750
msgid " [following]"
msgstr " [spremljam]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Dol¾ina: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (¹e %s)"

#: src/http.c:774
msgid "ignored"
msgstr "prezrta"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Pozor: HTTP ne podpira d¾okerjev.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Datoteka `%s' ¾e obstaja, ne jemljem.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Ne morem pisati v `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "NAPAKA: Preusmeritev (%d) brez nove lokacije.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s NAPAKA %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Glava ,Last-Modified` manjka - izklapljam oznako èasa.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Neveljavna glava `Last-Modified' -- ignoriram èasovno oznako.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Oddaljena datoteka je novej¹a, jemljem.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' shranjen [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Zveza zaprta z bajtom ¹t. %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' shranjen [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Zveza zaprta z bajtom ¹t. %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Napaka pri branju na bajtu %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Napaka pri èitanju na bajtu %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Ne morem prebrati %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Napaka v %s na liniji %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Pozor: sistemska in uporabnikova wgetrc ka¾eta na `%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: HRO©È: Neznani ukaz `%s', vrednost `%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Prosim doloèite `on' ali `off'.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Neveljavna doloèitev `%s'\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Neveljavna doloèitev `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Uporaba: %s [IZBIRA]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, orodje za neinteraktivno jemanje preko mre¾e.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nObvezni argumenti za dolge izbire so obvezni tudi za kratke izbire.\n\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"Zagon:\n"
"  -V,  --version           prika¾i razlièico Wgeta in se vrni.\n"
"  -h,  --help              izpi¹i pomoè.\n"
"  -b,  --background        po zagonu pojdi v ozadje.\n"
"  -e,  --execute=UKAZ      izvedi ukaz iz datoteke `.wgetrc'.\n"
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
"Bele¾enje in vhodna datoteka:\n"
"  -o,  --output-file=DATOTEKA     shranjuj dnevnik v DATOTEKO.\n"
"  -a,  --append-output=DATOTEKA   dodaj dnevnik v DATOTEKO.\n"
"  -d,  --debug                    izpisuj razhro¹èevalni izhod.\n"
"  -q,  --quiet                    ti¹ina (brez izpisa).\n"
"  -v,  --verbose                  vkljuèi polni izpis (privzeto).\n"
"  -nv, --non-verbose              izkljuèi veèino izpisa.\n"
"  -i,  --input-file=DATOTEKA      preberi URL-je iz DATOTEKE.\n"
"  -F,  --force-html               privzemi, da je vhodna datoteka HTML.\n"
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
"Jemanje:\n"
"  -t,  --tries=©TEVILO              nastavi ©TEVILO poskusov (0 za neskonèno)\n"
"  -O   --output-document=DATOTEKA   pi¹i dokumente v DATOTEKO.\n"
"  -nc, --no-clobber                 ne pi¹i prek obstojeèih datotek.\n"
"  -c,  --continue                   nadaljuj z jemanjem obstojeèe datoteke.\n"
"       --dot-style=STIL             doloèi slog prikaza jemanja.\n"
"  -N,  --timestamping               ne jemlji starej¹ih datotek od lokalnih.\n"
"  -S,  --server-response            izpisuj gostiteljev odziv.\n"
"       --spider                     nièesar ne jemlji.\n"
"  -T,  --timeout=SEKUNDE            doloèi bralno zakasnitev na SEKUNDE.\n"
"  -w,  --wait=SEKUNDE               poèakaj toliko SEKUND med jemanji.\n"
"  -Y,  --proxy=on/off               vkljuèi ali izkljuèi proxy.\n"
"  -Q,  --quota=©TEVILO              doloèi omejitev jemanja na ©TEVILO.\n"
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
"Imeniki:\n"
"  -nd  --no-directories             ne ustvarjaj imenikov.\n"
"  -x,  --force-directories          vedno ustvarjaj imenike.\n"
"  -nH, --no-host-directories        ne ustvarjaj imenikov po gostiteljih.\n"
"  -P,  --directory-prefix=PREDPONA  shranjuj datoteke v PREDPONA/...\n"
"       --cut-dirs=©TEVILO           ignoriraj ©TEVILO oddaljenih imenikov.\n"
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
"Izbire za HTTP:\n"
"       --http-user=UPORABNIK    doloèi uporabnika HTTP na UPORABNIK.\n"
"       --http-passwd=GESLO      doloèi geslo za HTTP kot GESLO.\n"
"  -C,  --cache=on/off           dovolitev predpomnenja (navadno dovoljeno).\n"
"       --ignore-length          ignoriraj glavo `Content-Length'.\n"
"       --header=NIZ             vstavi NIZ v glavo.\n"
"       --proxy-user=UPORABNIK   doloèi UPORABNIKA kot uporabnika proxy-ja.\n"
"       --proxy-passwd=GESLO     doloèi geslo za proxy GESLO.\n"
"  -s,  --save-headers           shranjuj glave HTTP na disk.\n"
"  -U,  --user-agent=ODJEMNIK    predstavi se kot ODJEMNIK namesto Wget/VERZIJA.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Izbire za FTP:\n"
"       --retr-symlinks   jemlji simbolne povezave s FTP.\n"
"  -g,  --glob=on/off     vkljuèi ali izkljuèi `globbing'.\n"
"       --passive-ftp     uporabljaj \"pasivni\" naèin prenosa.\n"
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
"Rekurzivno jemanje:\n"
"  -r,  --recursive             rekurzivno jemanje -- uporabljaj previdno!\n"
"  -l,  --level=NUMBER          maksimalna globina rekurzije (0 za neskonèno).\n"
"       --delete-after          bri¹i pobrane datoteke.\n"
"  -k,  --convert-links         pretvori absolutne povezave v relativne.\n"
"  -m,  --mirror                vkljuèi izbire, primerne za \"zrcaljenje\".\n"
"  -nr, --dont-remove-listing   ne odstranjuj datoteke `.listing'.\n"
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
"Rekurzivno sprejemanje/zavraèanje:\n"
"  -A,  --accept=SEZNAM               seznam sprejemljivih pripon.\n"
"  -R,  --reject=SEZNAM               seznam zavrnljivih pripon.\n"
"  -D,  --domains=SEZNAM              seznam sprejemljivih domen.\n"
"       --exclude-domains=SEZNAM      seznam (z vejicami) zavrnljivih domen.\n"
"  -L,  --relative                    spremljaj samo relativne povezave.\n"
"       --follow-ftp                  spremljaj povezave FTP iz sestavkov HTML.\n"
"  -H,  --span-hosts                  pri rekurzivneh shranjevanju pojdi tudi\n"
"                                       na druge raèunalnike.\n"
"  -I,  --include-directories=SEZNAM  seznam dovoljenih imenikov.\n"
"  -X,  --exclude-directories=SEZNAM  seznam nedovoljenih imenikov.\n"
"  -nh, --no-host-lookup              ne pregleduj gostitelje z imenskim\n"
"                                       stre¾nikom (DNS).\n"
"  -np, --no-parent                   ne pojdi v star¹evski imenik.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Po¹iljajte poroèila o hro¹èih in predloge na <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: podpora za razhro¹èevanje ni vgrajena.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Vse pravice pridr¾ane.  Ta program se raz¹irja v upanju, da bo koristen,\n"
"vendar BREZ KAKR©NEGAKOLI JAMSTVA; celo brez impliciranega jamstva\n"
"CENOVNE VREDNOSTI ali PRIMERNOSTI ZA DOLOÈEN NAMEN.  Poglejte licenco\n"
"GNU General Public License za podrobnosti.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nNapisal Hrvoje Nik¹iæ <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: neveljaven ukaz\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: nedovoljena izbira -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Poskusite `%s --help' za veè izbir.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Ne morem biti istoèasno izèrpen in tih.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Ne morem istoèasno upo¹tevati èasa in prepisovati starih datotek.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: manjka URL\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "V %s nisem na¹el nobenega URL.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"KONÈAL --%s--\n"
"Prenesel: %s bajtov v %d datotekah\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Kvota (%s bajtov) je PREKORAÈENA!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s prejet, preusmerjam izhod na `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break je sprejet, preusmerjam izhod v `%s'.\n"
"Izvajanje se nadaljuje v ozadju.\n"
"Wget lahko prekinete s pritiskom na CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Nadaljujem v ozadju.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Izhod bo zapisan v `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Zaganjam WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Ne morem najti uporabnega gonilnika za vtiènice.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: pozor: beseda \"%s\" se pojavlja pred vsakim imenom stroja\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: neznana beseda \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Uporaba: %s NETRC [RAÈUNALNIK]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: ne morem pognati stat na %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Odstranjujem %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Odstranjam %s, saj bi moral biti zavrnjen.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Nalagam robots.txt; prosim, prezrite napake.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n         [ preskakujem %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Ne morem najti zastopnika.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Zastopnik %s: Mora biti HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Preusmeritev na samega sebe.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Odneham.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Posku¹am ponovno.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Napaka (%s): Podana je povezava %s brez osnove.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Napaka (%s): Osnova %s je relativna, brez sklicujoèega se URL-ja.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Pretvarjam %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Ne morem pretvoriti povezav v %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Ni dovolj pomnilnika.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Neznan/nepodprt protokol"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Neveljavna doloèitev vrat"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Neveljavno gostiteljsko ime"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Ne morem odstraniti simbolne povezave `%s': %s\n"
