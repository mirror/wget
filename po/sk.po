# Slovak translations for GNU wget
# Copyright (C) 1998 Free Software Foundation, Inc.
# Miroslav Vasko <vasko@debian.cz>, 1999
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08 +02:00\n"
"PO-Revision-Date: 1999-04-02 11:00 +01:00\n"
"Last-Translator: Miroslav Vasko <vasko@debian.cz>\n"
"Language-Team: Slovak <sk-i18n@rak.isternet.sk>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8-bit\n"

# , c-format
#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Naväzujem spojenie s %s:%hu... "

# , c-format
#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Spojenie s %s:%hu odmietnuté.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "spojené!\n"

# , c-format
#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Prihlasujem sa ako %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Server odpovedal chybne, uzatváram riadiace spojenie.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Úvodná odpoveï serveru je chybná.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Nemô¾em zapísa» dáta, uzatváram riadiace spojenie.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Server odmieta prihlásenie.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Chyba pri prihlásení.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Prihlásený!\n"

# , c-format
#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Neznámy typ `%c', uzatváram riadiace spojenie.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "hotovo."

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD nie je potrebné.\n"

# , c-format
#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Adresár `%s' neexistuje.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "hotovo.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD nie je potrebné.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Nemo¾no inicializova» prenos príkazom PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Odpovrï na PASV je nepochopiteµná.\n"

# , c-format
#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Pokúsim sa spoji» s %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "hotovo.  "

# , c-format
#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Chyba pri operácii \"bind\" (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Neplatný PORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nPríkaz REST zlyhal, prená¹am súbor od zaèiatku.\n"

# , c-format
#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Súbor `%s' neexistuje.\n\n"

# , c-format
#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Súbor alebo adresár `%s' neexistuje.\n\n"

# , c-format
#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Då¾ka: %s"

# , c-format
#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [ostáva %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (nie je smerodajné)\n"

# , c-format
#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, uzatváram riadiace spojenie.\n"

# , c-format
#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Dátové spojenie: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Riadiace spojenie uzatvorené.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Prenos dát bol predèasne ukonèený.\n"

# , c-format
#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Súbor `%s' je u¾ tu, nebudem ho prená¹a».\n"

# , c-format
#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(pokus:%2d)"

# , c-format
#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' ulo¾ený [%ld]\n\n"

# , c-format
#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Zoznam súborov bude doèasne ulo¾ený v `%s'.\n"

# , c-format
#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Vymazané `%s'.\n"

# , c-format
#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Håbka rekurzie %d prekroèila maximálnu povolenú håbku %d.\n"

# , c-format
#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Súbor `%s' nebudem prená¹a», preto¾e je lokálna verzia nov¹ia.\n\n"

# , c-format
#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Veµkosti se nezhodujú (lokálne %ld), prená¹am.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Neplatný názov symoblického odkazu, preskakujem.\n"

# , c-format
#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Korektný symbolický odkaz %s -> %s u¾ existuje.\n\n"

# , c-format
#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Vytváram symbolický odkaz %s -> %s\n"

# , c-format
#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr ""
"Preskakujem symbolický odkaz `%s', preto¾e tento systém symbolické odkazy\n"
"nepodporuje.\n"

# , c-format
#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Preskakujem adresár `%s'.\n"

# , c-format
#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: neznámy/nepodporovaný typ súboru.\n"

# , c-format
#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: èasové razítko súboru je poru¹ené.\n"

# , c-format
#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Podadresáre nebudem prená¹a», preto¾e sme u¾ v håbke %d (maximum je %d).\n"

# , c-format
#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr ""
"Nezostupujem do adresára `%s', preto¾e tento adresár sa má vynecha» alebo\n"
"nebol urèený na prechádzanie.\n"

# , c-format
#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Odmietam `%s'.\n"

# , c-format
#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Vzorke `%s' niè nezodpovedá.\n"

# , c-format
#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Výpis adresára v HTML formáte bol zapísaný do `%s' [%ld].\n"

# , c-format
#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Výpis adresára v HTML formáte bol zapísaný do `%s'.\n"

# , c-format
#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: prepínaè `%s' nie je jednoznaèný\n"

# , c-format
#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: prepínaè `--%s' nemá argument\n"

# , c-format
#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: prepínaè `%c%s' nemá argument\n"

# , c-format
#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: prepínaè `%s' vy¾aduje argument\n"

# , c-format
#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: neznámy prepínaè `--%s'\n"

# , c-format
#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: neznámy prepínaè `%c%s'\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: neprípustný prepínaè -- %c\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: prepínaè vy¾aduje argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Nemo¾no identifikova» u¾ívateµa.\n"

# , c-format
#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Varovanie: volanie \"uname\" skonèilo s chybou %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Varovanie: volanie \"gethostname\" skonèilo s chybou\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Varovanie: nemo¾no urèi» lokálnu IP adresu.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Varovanie: lokálna IP adresa nemá reverzný záznam v DNS.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Varovanie: reverzné vyhµadanie lokálnej adresy nevrátilo plné\n"
"                kvalifikované meno!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Hostiteµ nebol nájdený"

#: src/host.c:541
msgid "Unknown error"
msgstr "Neznáma chyba"

# , c-format
#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Obsah /%s na %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "èas neznámy        "

#: src/html.c:467
msgid "File        "
msgstr "Súbor       "

#: src/html.c:470
msgid "Directory   "
msgstr "Adresár     "

#: src/html.c:473
msgid "Link        "
msgstr "Sym. odkaz  "

#: src/html.c:476
msgid "Not sure    "
msgstr "Neznámy typ "

# , c-format
#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytov)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Po¾iadavku HTTP nebolo mo¾né odosla».\n"

# , c-format
#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s po¾iadavka odoslaná, èakám na odpoveï ... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Hlavièka nie je úplná.\n"

# , c-format
#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Chyba (%s) pri èítaní hlavièiek.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Nepri¹li ¾iadne dáta"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Odpoveï serveru má skomolený stavový riadok"

#: src/http.c:594
msgid "(no description)"
msgstr "(¾iadny popis)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Autorizácia zlyhala.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Server po¾aduje neznámy spôsob autentifikácie.\n"

# , c-format
#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Presmerované na: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "neudané"

#: src/http.c:750
msgid " [following]"
msgstr " [nasledujem]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Då¾ka:  "

# , c-format
#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (ostáva %s)"

#: src/http.c:774
msgid "ignored"
msgstr "je ignorovaná"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Varovanie: HTTP nepodporuje ¾olíkové znaky.\n"

# , c-format
#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Súbor `%s' sa nebude prená¹a», je u¾ tu.\n"

# , c-format
#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Nemo¾no zapísa» do `%s' (%s).\n"

# , c-format
#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "CHYBA: Presmerovanie (%d) bez udanej novej adresy.\n"

# , c-format
#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s CHYBA %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr ""
"Nebudú sa pou¾íva» èasové razítka (`time-stamps'), preto¾e hlavièka\n"
"\"Last-modified\" v odpovedi serveru chýba.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""
"Ignorujem èasové razítko súboru (`time-stamp'), preto¾e hlavièka \n"
"\"Last-modified\" obsahuje neplatné údaje.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Vzdialený súbor má nov¹í dátum, prená¹am.\n"

# , c-format
#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' ulo¾ený [%ld/%ld]\n\n"

# , c-format
#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Spojenie uzatvorené na byte %ld. "

# , c-format
#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' ulo¾ené [%ld/%ld])\n\n"

# , c-format
#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Spojenie uzatvorené na byte %ld/%ld. "

# , c-format
#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Chyba pri èítaní dát na byte %ld (%s)."

# , c-format
#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Chyba pri èítaní dát na byte %ld/%ld (%s). "

# , c-format
#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Nemo¾no preèíta» %s (%s).\n"

# , c-format
#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Chyba v %s na riadku %d.\n"

# , c-format
#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Varovanie: Globálne aj u¾ívateµské wgetrc sú zhodne ulo¾ené v `%s'.\n"

# , c-format
#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Chyba: Neznámy príkaz `%s', hodnota `%s'.\n"

# , c-format
#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Zadajte prosím `on' alebo `off'.\n"

# , c-format
#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Neplatná ¹pecifikácia `%s'\n"

# , c-format
#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Neplatná ¹pecifikácia `%s'\n"

# , c-format
#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Pou¾itie: %s [PREPÍNAÈ]... [URL]...\n"

# , c-format
#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, program pre neinteraktívne s»ahovanie súborov.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr ""
"\n"
"Argumenty, povinné pri dlhých prepínaèoch, sú povinné aj pre krátke verzie\n"
"prepínaèov.\n"
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
"Zaèátek:\n"
"  -V,  --version           vypí¹e informáciu o verzii programu Wget a skonèí\n"
"  -h,  --help              vypí¹e túto nápovedu a skonèí\n"
"  -b,  --background        po spustení pokraèuje v behu na pozadí\n"
"  -e,  --execute=PRÍKAZ    vykonaj príkaz `.wgetrc'\n"
"\n"

# , fuzzy
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
"Protokolovanie a vstupný súbor:\n"
"  -o,  --output-file=SÚBOR    do tohoto súboru ukladaj protokol\n"
"  -a,  --append-output=SÚBOR  protokol pripoj na koniec tohoto súboru\n"
"  -d,  --debug                vypisuj ladiace informácie\n"
"  -q,  --quiet                nevypisuj vôbec niè\n"
"  -v,  --verbose              buï uhovorený (¹tandardne zapnuté)\n"
"  -nv, --non-verbose          vypisuj iba najdôle¾itej¹ie informácie\n"
"  -i,  --input-file=SÚBOR     odkazy URL naèítaj z tohoto súboru\n"
"  -F,  --force-html           súbor s URL je v HTML formáte\n"
"\n"

# , fuzzy
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
"S»ahovanie:\n"
"  -t,  --tries=ÈÍSLO            poèet pokusov stiahnu» URL (0 nekoneèný)\n"
"  -O   --output-document=SÚBOR  stiahnuté dokumenty ukladaj do tohoto súboru\n"
"  -nc, --no-clobber             neprepisuj existujúce súbory\n"
"  -c,  --continue               zaèni s»ahova» u¾ èiastoène prenesené dáta\n"
"       --dot-style=STYL         nastav spôsob zobrazenia pri s»ahovaní dát\n"
"  -N,  --timestamping           nes»ahuj star¹ie súbory (zapni èasové razítka)\n"
"  -S,  --server-response        vypisuj odpovede serveru\n"
"       --spider                 niè nes»ahuj\n"
"  -T,  --timeout=SEKÚND         nastav timeout pri èítaní na túto hodnotu\n"
"  -w,  --wait=SEKÚND            pred ka¾dým s»ahovaním poèkaj SEKÚND sekúnd\n"
"  -Y,  --proxy=on/off           zapni prenos cez proxy (¹tandardne `off')\n"
"  -Q,  --quota=ÈÍSLO            nastav limit objemu ulo¾ených dát\n"
"\n"

# , fuzzy
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
"Adresáre:\n"
"  -nd  --no-directories            nevytváraj adresáre\n"
"  -x,  --force-directories         v¾dy vytváraj adresáre\n"
"  -nH, --no-host-directories       nevytváraj adresáre s adresou serveru\n"
"  -P,  --directory-prefix=PREFIX   ukladaj dáta do PREFIX/...\n"
"       --cut-dirs=POÈET            nevytváraj prvých POÈET podadresárov\n"
"\n"

# , fuzzy
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
"Prepínaèe pre HTTP:\n"
"       --http-user=U®ÍVATE¥  u¾ívateµské meno pre autorizovaný prenos http\n"
"       --http-passwd=HESLO   heslo pre autorizovaný prenos http \n"
"  -C,  --cache=on/off        povoµ alebo zaká¾ pou¾itie vyrovnávacej pamäte\n"
"                             na strane serveru (¹tandardne `on')\n"
"       --ignore-length       ignoruj pole `Content-Length' v hlavièke\n"
"       --header=RE«AZEC      po¹li RE«AZEC serveru ako súèas» hlavièiek\n"
"       --proxy-user=U®ÍVATE¥ meno u¾ívateµa vy¾adované pre prenos proxy\n"
"       --proxy-passwd=HESLO  heslo pre prenos proxy\n"
"  -s,  --save-headers        do s»ahovaného súboru ulo¾ aj hlavièky HTTP\n"
"  -U,  --user-agent=AGENT    namiesto identifikácie `Wget/VERZE' posielaj\n"
"                             v hlavièke identifikaèný re»azec AGENT\n"

# , fuzzy
#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Prepínaèe pre protokol FTP:\n"
"       --retr-symlinks   s»ahuj aj symbolické odkazy\n"
"  -g,  --glob=on/off     zapni alebo vypni expanziu ¾olíkov v menách súborov\n"
"                         (¹tandardne `on')\n"
"       --passive-ftp     pou¾i pasívny mód prenosu dát\n"
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
"Rekurzívne s»ahovanie:\n"
"  -r,  --recursive             rekurzívne s»ahovanie -- buïte opatrní!\n"
"  -l,  --level=NUMBER          maximálna håbka rekurzie (0 bez limitu)\n"
"       --delete-after          po prenose zma¾ stiahnuté súbory\n"
"  -k,  --convert-links         absolutné URL preveï na relatívne\n"
"  -m,  --mirror                zapni prepínaèe vhodné pre zrkadlenie dát\n"
"  -nr, --dont-remove-listing   nema¾ súbory `.listing' s obsahmi adresárov\n"
"\n"

# , fuzzy
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
"Obmedzenie pri rekurzii:\n"
"  -A,  --accept=ZOZNAM              zoznam povolených prípon súborov\n"
"  -R,  --reject=ZOZNAM              zoznam nepovolených prípon súborov\n"
"  -D,  --domains=ZOZNAM             zoznam povolených domén\n"
"       --exclude-domains=ZOZNAM     zoznam nepovolených domén\n"
"  -L,  --relative                   nasleduj iba relatívne odkazy\n"
"       --follow-ftp                 nasleduj FTP odkazy v HTML dokumentoch\n"
"  -H,  --span-hosts                 naèítaj dokumenty aj z ostatných serverov\n"
"  -I,  --include-directories=ZOZNAM zoznam povolených adresárov\n"
"  -X,  --exclude-directories=ZOZNAM zoznam vylúèených adresárov\n"
"  -nh, --no-host-lookup             nevyhµadávaj adresy v DNS\n"
"  -np, --no-parent                  nezostupuj do rodièovského adresára\n"
"\n"

# , fuzzy
#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Správy o chybách a návrhy na vylep¹enie programu zasielajte na adresu\n"
"<bug-wget@gnu.org> (iba anglicky).\n"
"Komentáre k slovenskému prekladu zasielajte na adresu <sk@li.org>. \n"

# , fuzzy
#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: program nebol skompilovaný s podporou pre ladenie.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Tento program je ¹írený v nádeji, ¾e bude u¾itoèný, av¹ak\n"
"BEZ AKEJKO¥VEK ZÁRUKY; neposkytujú sa ani odvodené záruky PREDAJNOSTI \n"
"alebo VHODNOSTI PRE URÈITÝ ÚÈEL. Ïaµ¹ie podrobnosti hµadajte \n"
"vo V¹eobecnej verejnej licencii GNU.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nAutorom tohoto programu je Hrvoje Nik¹iæ <hniksic@srce.hr>\n"

# , c-format
#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: neplatný príkaz\n"

# , c-format
#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: neprípustný prepínaè -- `-n%c'\n"

# , c-format
#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Príkaz `%s --help' vypí¹e význam platných prepínaèov.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Nie je mo¾né by» uhovorený a by» ticho zároveò.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Nie je mo¾né pou¾íva» èasové razítka a nemaza» pritom staré súbory.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: chýba URL\n"

# , c-format
#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "V súbore `%s' nebol nájdený ¾iadny odkaz URL.\n"

# , c-format
#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"KONEC --%s--\n"
"Celkem naèítaných %s bytov v %d súboroch\n"

# , c-format
#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Prekroèený limit objemu ulo¾ených dát (%s bytov)!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "Zachytený signál %s , výstup presmerovaný do `%%s'.\n"

# , c-format
#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Stlaèený CTRL+Break, výstup bol presmerovaný do `%s'\n"
"Program pokraèuje v behu na pozadí.\n"
"Wget je mo¾né zastavi» stlaèením CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Pokraèujem v behu na pozadí.\n"

# , c-format
#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Výstup bude zapísaný do `%s'.\n"

# , c-format
#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Spú¹»am WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Nemô¾em nájs» pou¾iteµný ovládaè soketov.\n"

# , c-format
#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d varovanie: token \"%s\" je uvedený e¹te pred akýmkoµvek\n"
"      názvom poèítaèa\n"

# , c-format
#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: neznámy token \"%s\"\n"

# , c-format
#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Pou¾itie: %s NETRC [NÁZOV POÈÍTAÈA]\n"

# , c-format
#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: volanie `stat %s' skonèilo s chybou: %s\n"

# , c-format
#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Ma¾e sa %s.\n"

# , c-format
#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Ma¾e sa %s, preto¾e tento súbor nie je po¾adovaný.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Naèítavam `robots.txt'. Chybové hlásenia ignorujte, prosím.\n"

# , c-format
#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ preskakujem %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Nemô¾em nájs» proxy server.\n"

# , c-format
#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Musí by» HTTP.\n"

# , c-format
#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Presmerovanie na seba samého.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Vzdávam to.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Skú¹am to znovu.\n\n"

# , c-format
#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Chyba (%s): K relatívnemu odkazu %s nie je mo¾né nájs» bázový odkaz.\n"

# , c-format
#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Chyba (%s): Bázový odkaz %s nesmie by» relatívny.\n"

# , c-format
#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konvertujem %s... "

# , c-format
#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Nedoká¾em previes» odkazy v %s: %s\n"

# , c-format
#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Nie je dos» pamäte.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Neznámy/nepodporovaný protokol"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Neplatná ¹pecifikácia portu"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Neplatné meno stroja"

# , c-format
#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Nebylo mo¾né odstráni» symbolický odkaz `%s': %s\n"
