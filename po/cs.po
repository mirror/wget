# Czech translations for GNU wget
# Copyright (C) 1998 Free Software Foundation, Inc.
# Jan Prikryl <prikryl@acm.org>, 1998
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.5.2-b1\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1998-06-05 08:47\n"
"Last-Translator: Jan Prikryl <prikryl@acm.org>\n"
"Language-Team: Czech <cs@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8-bit\n"

# , c-format
#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Navazuji spojení s %s:%hu... "

# , c-format
#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Spojení s %s:%hu odmítnuto.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "spojeno!\n"

# , c-format
#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Pøihla¹uji se jako %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Server odpovìdìl chybnì, uzavírám øídicí spojení.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Úvodní odpovìï serveru je chybná.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Nemohu zapsat data, uzavírám øídicí spojení.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Server odmítá pøihlá¹ení.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Chyba pøi pøihlá¹ení.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Pøihlá¹en!\n"

# , c-format
#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Neznámý typ `%c', uzavírám øídicí spojení.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "hotovo."

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD není potøeba.\n"

# , c-format
#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Adresáø `%s' neexistuje.\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "hotovo.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD není potøeba.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Nemohu inicializovat pøenos pøíkazem PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Odpovìï na PASV není pochopitelná.\n"

# , c-format
#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Pokusím se spojit s %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "hotovo.  "

# , c-format
#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Chyba pøi operaci \"bind\" (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Neplatný PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"Pøíkaz REST selhal, pøená¹ím soubor od zaèátku.\n"

# , c-format
#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Soubor `%s' neexistuje.\n"
"\n"

# , c-format
#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Soubor èi adresáø `%s' neexistuje.\n"
"\n"

# , c-format
#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Délka: %s"

# , c-format
#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s zbývá]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (není smìrodatné)\n"

# , c-format
#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, uzavírám øídicí spojení.\n"

# , c-format
#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Datové spojení: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Øídicí spojení uzavøeno.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Pøenos dat byl pøedèasnì ukonèen.\n"

# , c-format
#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Soubor `%s' je ji¾ zde, nebudu jej pøená¹et.\n"

# , c-format
#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(pokus:%2d)"

# , c-format
#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' ulo¾en [%ld]\n"
"\n"

# , c-format
#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Seznam souborù bude doèasnì ulo¾en v `%s'.\n"

# , c-format
#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Vymazal jsem `%s'.\n"

# , c-format
#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Hloubka rekurze %d pøekroèila maximální povolenou hloubku %d.\n"

# , c-format
#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""
"Soubor `%s' nebudu pøená¹et, proto¾e lokální verze je novìj¹í.\n"
"\n"

# , c-format
#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Velikosti se neshodují (lokálnì %ld), pøená¹ím.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Neplatný název symoblického odkazu, pøeskakuji.\n"

# , c-format
#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Korektní symbolický odkaz %s -> %s ji¾ existuje.\n"
"\n"

# , c-format
#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Vytváøím symbolický odkaz %s -> %s\n"

# , c-format
#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr ""
"Pøeskakuji symbolický odkaz `%s', proto¾e tento systém symbolické odkazy\n"
"nepodporuje.\n"

# , c-format
#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Pøeskakuji adresáø `%s'.\n"

# , c-format
#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: neznámý/nepodporovaný typ souboru.\n"

# , c-format
#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: èasové razítko souboru je poru¹ené.\n"

# , c-format
#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr ""
"Podadresáøe nebudu pøená¹et, proto¾e jsme ji¾ v hloubce %d (maximum je %d).\n"

# , c-format
#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr ""
"Nesestupuji do adresáøe `%s', proto¾e tento adresáø se má vynechat èi\n"
"nebyl zadán k procházení.\n"

# , c-format
#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Odmítám `%s'.\n"

# , c-format
#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Vzorku `%s' nic neodpovídá.\n"

# , c-format
#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Výpis adresáøe v HTML formátu byl zapsán do `%s' [%ld].\n"

# , c-format
#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Výpis adresáøe v HTML formátu byl zapsán do `%s'.\n"

# , c-format
#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: pøepínaè `%s' není jednoznaèný\n"

# , c-format
#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: pøepínaè `--%s' nemá argument\n"

# , c-format
#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: pøepínaè `%c%s' nemá argument\n"

# , c-format
#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: pøepínaè `%s' vy¾aduje argument\n"

# , c-format
#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: neznámý pøepínaè `--%s'\n"

# , c-format
#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: neznámý pøepínaè `%c%s'\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: nepøípustný pøepínaè -- %c\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: pøepínaè vy¾aduje argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Nemohu identifikovat u¾ivatele.\n"

# , c-format
#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Varování: volání \"uname\" skonèilo chybou %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Varování: volání \"gethostname\" skonèilo chybou\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Varování: nemohu urèit lokální IP adresu.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Varování: lokální IP adresa nemá reverzní DNS záznam.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Varování: reverzní vyhledání lokální adresy nenavrátilo plnì\n"
"                kvalifikované jméno!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Poèítaè nebyl nalezen"

#: src/host.c:541
msgid "Unknown error"
msgstr "Neznámá chyba"

# , c-format
#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Obsah /%s na %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "èas neznámý        "

#: src/html.c:467
msgid "File        "
msgstr "Soubor      "

#: src/html.c:470
msgid "Directory   "
msgstr "Adresáø     "

#: src/html.c:473
msgid "Link        "
msgstr "Sym. odkaz  "

#: src/html.c:476
msgid "Not sure    "
msgstr "Neznámý typ "

# , c-format
#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bajtù)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "HTTP po¾adavek nebylo mo¾né odeslat.\n"

# , c-format
#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s po¾adavek odeslán, èekám na odpovìï ... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Hlavièka není úplná.\n"

# , c-format
#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Chyba (%s) pøi ètení hlavièek.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Nepøi¹la ¾ádná data"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Odpovìï serveru má zkomolený stavový øádek"

#: src/http.c:594
msgid "(no description)"
msgstr "(¾ádný popis)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Autorizace selhala.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Server po¾aduje neznámý zpùsob autentifikace.\n"

# , c-format
#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Pøesmìrováno na: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "neudáno"

#: src/http.c:750
msgid " [following]"
msgstr " [následuji]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Délka: "

# , c-format
#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s zbývá)"

#: src/http.c:774
msgid "ignored"
msgstr "je ignorována"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Varování: HTTP nepodporuje ¾olíkové znaky.\n"

# , c-format
#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Soubor `%s' nebudu pøená¹et, je ji¾ zde.\n"

# , c-format
#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Nemohu zapsat do `%s' (%s).\n"

# , c-format
#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "CHYBA: Pøesmìrování (%d) bez udané nové adresy.\n"

# , c-format
#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s CHYBA %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr ""
"Nebudu pou¾ívat èasová razítka (`time-stamps'), proto¾e hlavièka\n"
"\"Last-modified\" v odpovìdi serveru schází.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr ""
"Ignoruji èasové razítko souboru (`time-stamp'), proto¾e hlavièka \n"
"\"Last-modified\" obsahuje neplatné údaje.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Vzdálený soubor je novìj¹ího data, pøená¹ím.\n"

# , c-format
#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' ulo¾en [%ld/%ld]\n"
"\n"

# , c-format
#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Spojení uzavøeno na bajtu %ld. "

# , c-format
#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' ulo¾eno [%ld/%ld])\n"
"\n"

# , c-format
#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Spojení uzavøeno na bajtu %ld/%ld. "

# , c-format
#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Chyba pøi ètení dat na bajtu %ld (%s)."

# , c-format
#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Chyba pøi ètení dat na bajtu %ld/%ld (%s). "

# , c-format
#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Nemohu pøeèíst %s (%s).\n"

# , c-format
#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Chyba v %s na øádku %d.\n"

# , c-format
#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""
"%s: Varování: Globální i u¾ivatelské wgetrc jsou shodnì ulo¾eny v `%s'.\n"

# , c-format
#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Chyba: Neznámý pøíkaz `%s', hodnota `%s'.\n"

# , c-format
#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Zadejte prosím `on' nebo `off'.\n"

# , c-format
#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Neplatná specifikace `%s'\n"

# , c-format
#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Neplatná specifikace `%s'\n"

# , c-format
#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Pou¾ití: %s [PØEPÍNAÈ]... [URL]...\n"

# , c-format
#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, program pro neinteraktivní stahování souborù.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Argumenty, povinné u dlouhých pøepínaèù, jsou povinné i pro krátké verze\n"
"pøepínaèù.\n"
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
"  -V,  --version           vypi¹ informaci o verzi programu Wget a skonèi\n"
"  -h,  --help              vypi¹ tuto nápovìdu\n"
"  -b,  --background        po spu¹tìní pokraèuj v bìhu na pozadí\n"
"  -e,  --execute=PØÍKAZ    proveï `.wgetrc' pøíkaz\n"
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
"Protokolování a vstupní soubor:\n"
"  -o,  --output-file=SOUBOR   do tohoto souboru ukládej protokol\n"
"  -a,  --append-output=SOUBOR protokol pøipoj na konec tohoto souboru\n"
"  -d,  --debug                vypisuj ladicí informace\n"
"  -q,  --quiet                nevypisuj vùbec nic\n"
"  -v,  --verbose              buï upovídaný (implicitnì zapnuto)\n"
"  -nv, --non-verbose          vypisuj pouze nejdùle¾itìj¹í informace\n"
"  -i,  --input-file=SOUBOR    poèíteèní URL odkazy naèti z tohoto souboru\n"
"  -F,  --force-html           soubor s URL je v HTML formátu\n"
"\n"

# , fuzzy
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
"Stahování:\n"
"  -t,  --tries=ÈÍSLO            poèet pokusù stáhnout URL (0 donekoneèna)\n"
"  -O   --output-document=SOUBOR sta¾ené dokumenty ukládej do tohoto souboru\n"
"  -nc, --no-clobber             nepøepisuj existující soubory\n"
"  -c,  --continue               zaèni stahovat ji¾ èásteènì pøenesená data\n"
"       --dot-style=STYL         nastav zpùsob zobrazení pøi stahování dat\n"
"  -N,  --timestamping           nestahuj star¹í soubory (zapni èasová "
"razítka)\n"
"  -S,  --server-response        vypisuj odpovìdi serveru\n"
"       --spider                 nic nestahuj\n"
"  -T,  --timeout=SEKUNDY        nastav timeout pøi ètení na tuto hodnotu\n"
"  -w,  --wait=SEKUND            pøed ka¾dým stahováním poèkej SEKUND sekund\n"
"  -Y,  --proxy=on/off           zapni pøenos pøes proxy (standardnì `off')\n"
"  -Q,  --quota=NUMBER           nastav limit objemu ulo¾ených dat\n"
"\n"

# , fuzzy
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
"Adresáøe:\n"
"  -nd  --no-directories            nevytváøej adresáøe\n"
"  -x,  --force-directories         v¾dy vytváøej adresáøe\n"
"  -nH, --no-host-directories       nevytváøej adresáøe s adresou serveru\n"
"  -P,  --directory-prefix=PREFIX   ukládej data do PREFIX/...\n"
"       --cut-dirs=POÈET            nevytváøej prvních POÈET podadresáøù\n"
"\n"

# , fuzzy
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
"Pøepínaèe pro HTTP:\n"
"       --http-user=U®IVATEL  u¾ivatelské jméno pro autorizovaný http pøenos\n"
"       --http-passwd=HESLO   heslo pro autorizovaný http pøenos \n"
"  -C,  --cache=on/off        povol èi zaka¾ pou¾ití vyrovnávací pamìti na\n"
"                             stranì serveru (implicitnì `on')\n"
"       --ignore-length       ignoruj pole `Content-Length' v hlavièce\n"
"       --header=ØETÌZEC      po¹li ØETÌZEC serveru jako souèást hlavièek\n"
"       --proxy-user=U®IVATEL jméno u¾ivatele vy¾adované pro proxy pøenos\n"
"       --proxy-passwd=HESLO  heslo pro proxy pøenos\n"
"  -s,  --save-headers        do stahovaného souboru ulo¾ i HTTP hlavièky\n"
"  -U,  --user-agent=AGENT    místo identifikace `Wget/VERZE' posílej\n"
"                             v hlavièce identifikaèní øetìzec AGENT\n"

# , fuzzy
#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Pøepínaèe pro FTP protokol:\n"
"       --retr-symlinks   stahuj i symbolické odkazy\n"
"  -g,  --glob=on/off     zapni èi vypni expanzi ¾olíkù ve jménech souborù\n"
"                         (implicitnì `on')\n"
"       --passive-ftp     pou¾ij pasivní mód pøenosu dat\n"
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
"Rekurzivní stahování:\n"
"  -r,  --recursive             rekurzivní stahování -- buïte opatrní!\n"
"  -l,  --level=NUMBER          maximální hloubka rekurze (0 bez limitu)\n"
"       --delete-after          po pøenosu sma¾ sta¾ené soubory\n"
"  -k,  --convert-links         absolutní URL pøeveï na relativní\n"
"  -m,  --mirror                zapni pøepínaèe vhodné pro zrcadlení dat\n"
"  -nr, --dont-remove-listing   nema¾ soubory `.listing' s obsahy adresáøù\n"
"\n"

# , fuzzy
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
"Omezení pøi rekurzi:\n"
"  -A,  --accept=SEZNAM              seznam povolených extenzí souborù\n"
"  -R,  --reject=SEZNAM              seznam nepovolených extenzí souborù\n"
"  -D,  --domains=SEZNAM             seznam povolených domén\n"
"       --exclude-domains=SEZNAM     seznam nepovolených domén\n"
"  -L,  --relative                   následuj pouze relativní odkazy\n"
"       --follow-ftp                 následuj FTP odkazy v HTML dokumentech\n"
"  -H,  --span-hosts                 naèítej dokumenty i z ostatních serverù\n"
"  -I,  --include-directories=SEZNAM seznam povolených adresáøù\n"
"  -X,  --exclude-directories=SEZNAM seznam vylouèených adresáøù\n"
"  -nh, --no-host-lookup             nevyhledávej adresy v DNS\n"
"  -np, --no-parent                  nesestupuj do rodièovského adresáøe\n"
"\n"

# , fuzzy
#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Zprávy o chybách a návrhy na vylep¹ení programu zasílejte na adresu\n"
"<bug-wget@gnu.org> (pouze anglicky).\n"
"Komentáøe k èeskému pøekladu zasílejte na adresu <cs@li.org>. \n"

# , fuzzy
#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: program nebyl zkompilován s podporou pro ladìní.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Tento program je ¹íøen v nadìji, ¾e bude u¾iteèný, av¹ak\n"
"BEZ JAKÉKOLI ZÁRUKY; neposkytují se ani odvozené záruky PRODEJNOSTI \n"
"anebo VHODNOSTI PRO URÈITÝ ÚÈEL. Dal¹í podrobnosti hledejte \n"
"v Obecné veøejné licenci GNU.\n"

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""
"\n"
"Autorem tohto programu je Hrvoje Nik¹iæ <hniksic@srce.hr>\n"

# , c-format
#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: neplatný pøíkaz\n"

# , c-format
#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: nepøípustný pøepínaè -- `-n%c'\n"

# , c-format
#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Pøíkaz `%s --help' vypí¹e význam platných pøepínaèù.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Nedoká¾u být upovídaný a zitcha najednou.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Nedoká¾u pou¾ívat èasová razítka a nemazat pøitom staré soubory.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: postrádám URL\n"

# , c-format
#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "V souboru `%s' nebyla nalezena ¾ádná URL.\n"

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
"Celkem naèteno %s bajtù v %d souborech\n"

# , c-format
#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Pøekroèen limit objemu ulo¾ených dat (%s bajtù)!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "Zachycen signál %s , výstup pøesmìrován do `%%s'.\n"

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
"Stisknut CTRL+Break, pøesmìrovávám výstup do `%s'\n"
"Program pokraèuje v bìhu na pozadí.\n"
"Wget lze zastavit stiskem CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Pokraèuji v bìhu na pozadí.\n"

# , c-format
#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Výstup bude zapsán do `%s'.\n"

# , c-format
#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Spou¹tím WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Nemohu najít pou¾itelný ovladaè socketù.\n"

# , c-format
#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d varování: token \"%s\" je uveden je¹tì pøed jakýmkoliv\n"
"      názvem poèítaèe\n"

# , c-format
#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: neznámý token \"%s\"\n"

# , c-format
#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Pou¾ití: %s NETRC [NÁZEV POÈÍTAÈE]\n"

# , c-format
#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: volání `stat %s' skonèilo chybou: %s\n"

# , c-format
#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Ma¾u %s.\n"

# , c-format
#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Ma¾u %s, proto¾e tento soubor není po¾adován.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Naèítám `robots.txt'. Chybová hlá¹ení ignorujte, prosím.\n"

# , c-format
#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ pøeskakuji %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Nemohu najít proxy server.\n"

# , c-format
#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Musí být HTTP.\n"

# , c-format
#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Pøesmìrování na sebe sama.\n"

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Vzdávám to.\n"
"\n"

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Zkou¹ím to znovu.\n"
"\n"

# , c-format
#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Chyba (%s): K relativnímu odkazu %s nelze najít bázový odkaz.\n"

# , c-format
#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Chyba (%s): Bázový odkaz %s nesmí být relativní.\n"

# , c-format
#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konvertuji %s... "

# , c-format
#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Nedoká¾u pøevést odkazy v %s: %s\n"

# , c-format
#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Není dost pamìti.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Neznámý/nepodporovaný protokol"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Neplatná specifikace portu"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Neplatné jméno stroje"

# , c-format
#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Nebylo mo¾né odstranit symbolický odkaz `%s': %s\n"
