# Dutch messages for GNU Wget.
# Copyright © 1997, 1998 Free Software Foundation, Inc.
# André van Dijk <ady@unseen.demon.nl>, 1998
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.2-b4\n"
"POT-Creation-Date: 1998-06-13 03:12+0200\n"
"PO-Revision-Date: 1998-12-12 15:29+0200\n"
"Last-Translator: André van Dijk <ady@unseen.demon.nl>\n"
"Language-Team: Dutch <nl@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-1\n"
"Content-Transfer-Encoding: 8-bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Verbinden met %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Verbinding met %s:%hu geweigerd.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "verbonden!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Inloggen als %s ... "

# Ist das gemeint?
#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Fout in antwoord server, verbreek besturingsverbinding.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Fout in servers groet.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Schrijf fout, verbreek besturingsverbinding.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "De server weigert de login.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Login onjuist.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Ingelogt!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Onbekend type `%c', verbreek besturingsverbinding.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "gereed.  "

#: src/ftp.c:289
msgid "=> CWD not needed.\n"
msgstr "=> CWD niet nodig.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Onbekende directory `%s'.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1426
msgid "done.\n"
msgstr "gereed.\n"

#. do not CWD
#: src/ftp.c:335
msgid "=> CWD not required.\n"
msgstr "=> CWD niet noodzakelijk.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Kan PASV-overdracht niet beginnen.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Kan PASV-antwoord niet ontleden.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Tracht verbinding met %s:%hu te herstellen.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "gereed.    "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind fout (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Ongeldige POORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST gefaald, begin opnieuw.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Onbekend bestand `%s'.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Onbekend bestand of directory `%s'.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Lengte: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [nog %s]"

# Geen idee hoe dit correct te vertalen
#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (onauthoritatief)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, verbreek besturingsverbinding.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Gegevensverbinding: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Besturingsverbinding verbroken.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Gegevensoverdracht afgebroken.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Bestand `%s' reeds aanwezig, niet ophalen.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(poging:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' bewaard [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Aanroep `%s' als tijdelijk lijstbestand.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Verwijderd `%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "De recursiediepte %d overschreed de maximum diepte %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Lokaal bestand `%s' is nieuwer, niet ophalen.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Groottes komen niet overeen (lokaal %ld), ophalen.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Ongeldige naam voor een symbolische koppeling, overslaan.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Juiste symbolische koppeling bestaat reeds %s -> %s\n"

#: src/ftp.c:1143
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Maak symbolische koppeling %s -> %s\n"

#: src/ftp.c:1154
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symbolische koppelingen niet ondersteunt, symbolische koppeling overslaan `%s'.\n"

#: src/ftp.c:1166
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Directory overslaan `%s'.\n"

#: src/ftp.c:1175
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: onbekend/niet-ondersteund bestandstype.\n"

#: src/ftp.c:1191
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: beschadigd tijdstempel.\n"

#: src/ftp.c:1211
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Mappen worden niet opgehaald, omdat diepte %d is (max %d).\n"

#: src/ftp.c:1250
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Daal niet af naar `%s', omdat het uitgesloten/niet-ingesloten is.\n"

#: src/ftp.c:1295
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "`%s' afgewezen.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1342
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Geen overeenstemmingen met patroon `%s'.\n"

#: src/ftp.c:1402
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "HTML-achtige index naar `%s' [%ld] geschreven.\n"

#: src/ftp.c:1407
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "HTML-achtige index naar `%s' geschreven.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: optie `%s' is dubbelzinnig\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: optie `--%s' staat geen argument toe\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: optie `%c%s' staat geen argument toe\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: optie `%s' vereist een argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: niet herkende optie `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: nie herkende optie `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: ongeldige optie -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: optie vereist een argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Kan gebruikers-id niet bepalen.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Waarschuwing: uname gefaald: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Waarschuwing: gethostname gefaald\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Waarschuwing: kan lokaal IP-adres niet bepalen.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Waarschuwing: omgekeerd opzoeken van lokaal IP-adres onmogelijk.\n"

#: src/host.c:506
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Waarschuwing: omgekeerd opzoeken van lokaal adres levert geen\n"
"volledige domein naam.\n"

#: src/host.c:533
msgid "Host not found"
msgstr "Host niet gevonden"

#: src/host.c:535
msgid "Unknown error"
msgstr "Onbekende fout"

#: src/html.c:435 src/html.c:437
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index van /%s op %s:%d"

#: src/html.c:459
msgid "time unknown       "
msgstr "tijd onbekend     "

#: src/html.c:463
msgid "File        "
msgstr "Bestand     "

#: src/html.c:466
msgid "Directory   "
msgstr "Map         "

#: src/html.c:469
msgid "Link        "
msgstr "Koppeling   "

#: src/html.c:472
msgid "Not sure    "
msgstr "Niet zeker  "

#: src/html.c:490
#, c-format
msgid " (%s bytes)"
msgstr " (%s Bytes)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Schrijven HTTP-verzoek gefaald.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s verzoek verzonden, wacht op antwoord... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Bestandseinde bij ontleden kopregels.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Leesfout (%s) in kopregels.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Geen gegevens ontvangen"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Onjuiste statusregel"

#: src/http.c:594
msgid "(no description)"
msgstr "(geen beschrijving)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Authorisatie gefaald.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Onbekend authenticatieschema.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Lokatie: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "ongespecificeerd"

#: src/http.c:750
msgid " [following]"
msgstr "[volgt]"

# Header
#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Lengte: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (nog %s)"

#: src/http.c:774
msgid "ignored"
msgstr "genegeerd"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Waarschuwing: jokertekens niet ondersteund in HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Bestand `%s' reeds aanwezig, niet ophalen.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Kan niet schrijven naar `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "FOUT: Omleiding (%d) zonder lokatie.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s FOUT %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Laatste-aanpassingskopregel mist -- tijdstempels uitgeschakeld.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Laatst-aanpassingskopregel ongeldig -- tijdtstempels genegeerd.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Verafgelegen bestand is nieuwer, ophalen.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' bewaard [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Verbinding verbroken bij byte %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' bewaard [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Verbinding verbroken bij byte %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Leesfout bij byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Leesfout bij byte %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Kan `%s' niet lezen (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Fout in `%s' bij regel %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Waarschuwing: Zowel systeem als gebruiker wgetrc verwijzen naar `%s'.\n"

#: src/init.c:461
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Onbekende opdracht `%s', waarde `%s'.\n"

#: src/init.c:488
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Gelieve `aan' of `uit' te specificeren.\n"

#: src/init.c:506 src/init.c:763 src/init.c:785 src/init.c:858
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Ongeldige specificatie `%s'\n"

#: src/init.c:619 src/init.c:641 src/init.c:663 src/init.c:689
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Ongeldige specificatie `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Aanroep: %s [OPTIE]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, een niet-interactieve netwerk ontvanger.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nVerplichte argumenten voor lange opties zijn ook verplicht voor korte opties.\n\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"Opstarten:\n"
"  -V,  --version           toon de versie van wget en stop.\n"
"  -h,  --help              deze help tonen.\n"
"  -b,  --background        draai op de achtergrond na opstarten.\n"
"  -e,  --execute=COMMANDO  voer een `.wgetrc'-opdracht uit.\n"
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
"Loggen en invoerbestand:\n"
"  -o,  --output-file¾STAND   Log meldingen in BESTAND.\n"
"  -a,  --append-output¾STAND Meldingen toevoegen aan BESTAND.\n"
"  -d,  --debug                 Debug uitvoer tonen.\n"
"  -q,  --quiet                 stil (geen uitvoer).\n"
"  -v,  --verbose               woordenrijk (dit is standaard).\n"
"  -nv, --non-verbose           beknopte uitvoer; niet geheel stil.\n"
"  -i,  --input-file¾STAND    URLs uit BESTAND lezen.\n"
"  -F,  --force-html            invoerbestand als HTML behandelen.\n"
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
"Download:\n"
"  -t,  --triesªNTAL            zet herhalingspogingen op AANTAL\n"
"                                 (0 ongelimiteerd).\n"
"  -O   --output-document¾STAND schrijf dokumenten naar BESTAND.\n"
"  -nc, --no-clobber              bestaande bestande niet overschrijven.\n"
"  -c,  --continue                begin opnieuw, een bestaand bestand\n"
"                                 op te halen.\n"
"       --dot-style=STIJL         zet ontvangst-toon-stijl op STIJL.\n"
"  -N,  --timestamping            haal geen bestanden die ouder zijn dan de\n"
"                                 lokalen.\n"
"  -S,  --server-response         toon server antwoord.\n"
"       --spider                  niets ophalen.\n"
"  -T,  --timeout=SECONDEN        zet lees-timeout op SECONDEN.\n"
"  -w,  --wait=SECONDEN           wacht SECONDEN tussen ontvangsten.\n"
"  -Y,  --proxy=on/off            proxy aan (`on') of uit (`off').\n"
"  -Q,  --quotaªNTAL            zet de ontvangstquota op AANTAL.\n"
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
"Directory's:\n"
"  -nd  --no-directories            maak geen mappen.\n"
"  -x,  --force-directories         dwing het maken van mappen af.\n"
"  -nH, --no-host-directories       geen host-mappen maken.\n"
"  -P,  --directory-prefix=PREFIX   bestanden in PREFIX/... bewaren\n"
"       --cut-dirsªNTAL           negeer AANTAL verafgelegen\n"
"                                   map componenten.\n"
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
"HTTP-opties:\n"
"       --http-user=GEBRUIKER  zet http-gebruiker op GEBRUIKER\n"
"       --http-passwd=WACHTW   zet http-wachtwoord op WACHTW\n"
"  -C,  --cache=on/off         sta toe/verbiedt server-cached data\n"
"                              (normaal toegestaan).\n"
"       --ignore-length        negeer de `Content-Length'-kopregel.\n"
"       --header=TEKENREEKS    TEKENREEKS tussen kopregels invoegen.\n"
"       --proxy-user=GEBRUIKER zet GEBRUIKER als proxy-gebruikersnaam.\n"
"       --proxy-passwd=WACHTW  zet WACHTW als proxy-wachtwoord.\n"
"  -s,  --save-headers         bewaar de HTTP-kopregels in bestand.\n"
"  -U,  --user-agent=AGENT     als AGENT identificeren i.p.v Wget/VERSION.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP-opties:\n"
"       --retr-symlinks   haal FTP symbolische koppelingen op.\n"
"  -g,  --glob=on/off     bestandsnaam-`globbing' aan (`on') of uit (`off')\n"
"                         zetten.\n"
"       --passive-ftp     gebruik \"passieve\" overdrachtsmodus.\n"
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
"Recursieve ontvangst:\n"
"  -r,  --recursive             recursief web-zuigen -- voorzichtig!\n"
"  -l,  --level=Aantal          maximale recursiediepte (0 ongelimiteerd).\n"
"       --delete-after          wis opgehaalde bestanden.\n"
"  -k,  --convert-links         niet-relatieve verwijzingen naar relatieve\n"
"                               omzetten.\n"
"  -m,  --mirror                geschikte opties voor spiegelen (mirroring)\n"
"                               inschakelen.\n"
"  -nr, --dont-remove-listing   `.listing'-bestand niet verwijderen\n"
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
"Recursief accepteren/verwerpen:\n"
"  -A,  --accept=LIJST                lijst van geaccepteerde extensies.\n"
"  -R,  --reject=LIJST                lijst van verworpen extensies.\n"
"  -D,  --domains=LIJST               lijste van geaccepteerde domeinen.\n"
"       --exclude-domains=LIJST       komma-gescheiden lijst van verworpen\n"
"                                     domeinen.\n"
"  -L,  --relative                    alleen relatieve verwijzingen volgen.\n"
"       --follow-ftp                  volg FTP-verwijzingen van HTML-\n"
"                                     dokumenten.\n"
"  -H,  --span-hosts                  bij `--recursive', ook naar vreemde hosts\n"
"                                     gaan.\n"
"  -I,  --include-directories=LIJST   lijst van geaccepteerde mappen.\n"
"  -X,  --exclude-directories=LIJST   lijst van uitgesloten mappen.\n"
"  -nh, --no-host-lookup              geen DNS-opzoeking voor hosts.\n"
"  -np, --no-parent                   negeer hoger gelegen mappen.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Email bug reports en suggesties aan <bug-wget@gnu.org>.\n"
"\n"
"Voor de Nederlandse vertaling is de mailinglist <nl@li.org> te bereiken.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: Debug-ondersteuning niet meegecompileerd.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Dit programma wordt verspreid in de hoop dat het nuttig zal zijn,\n"
"maar ZONDER ENIGE GARANTIE; zelfs zonder de geïmpliceerde garantie\n"
"van VERKOOPBAARHEID of geschiktheid voor een bepaald doel.  Zie de\n"
"GNU Algemene Openbare Licentie (GNU General Public License) voor meer\n"
"details.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nGeschreven door Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ongeldige opdracht\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: ongeldige optie -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Probeer `%s --help' voor meer opties.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Kan niet gelijktijdig \"Woordenrijk\" en \"stil\" zijn.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Tijdstempels en niet-overschrijven oude bestanden is gelijktijdig onmogelijk.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: ontbrekende URL\n"

#: src/main.c:670
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Geen URLs gevonden in %s.\n"

#: src/main.c:679
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"KLAAR --%s--\n"
"Opgehaald: %s bytes in %d bestanden\n"

#: src/main.c:684
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Download quota (%s Bytes) OVERSCHREDEN!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:711
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s ontvangen, leid uitvoer om naar `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break ontvangen, leid uitvoer om naar `%s'.\n"
"Uitvoering voortgezet in de achtergrond.\n"
"Wget kan worden gestopt door op CTRL+ALT+DELETE te drukken.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:265
msgid "Continuing in background.\n"
msgstr "Voortzetting in de achtergrond.\n"

#: src/mswindows.c:137 src/utils.c:267
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Uitvoer wordt naar `%s' geschreven.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "WinHelp %s wordt gestart\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Kan geen bruikbare \"socket driver\" vinden.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: Waarschuwing: `%s'-teken verschijnt voor een machinenaam\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: onbekend teken `%s'\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Aanroep: %s NETRC [HOSTNAME]\n"

# stat
#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: kan de status van bestand %s niet opvragen: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Verwijder `%s'.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Verwijder `%s' omdat het verworpen zal worden.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Laad `robots.txt'; gelieve fouten te negeren.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ overslaan %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Kan proxy-host niet vinden.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Moet HTTP zijn.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Omleiding naar zichzelf.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Geef op.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Opnieuw proberen.\n\n"

# ???
#: src/url.c:935
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Fout (%s): Verwijzing `%s' zonder basis aangeboden.\n"

#: src/url.c:950
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Fout (%s): Basis %s relatief, zonder verwijzings-URL.\n"

#: src/url.c:1368
#, c-format
msgid "Converting %s... "
msgstr "Omzetten %s... "

#: src/url.c:1373 src/url.c:1384
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Kan verwijzingen niet omzetten naar %s: %s\n"

#: src/utils.c:68
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Onvoldoende geheugen.\n"

#: src/utils.c:200
msgid "Unknown/unsupported protocol"
msgstr "Onbekend/niet-ondersteund protocol"

#: src/utils.c:203
msgid "Invalid port specification"
msgstr "Ongeldige poort-specificatie"

#: src/utils.c:206
msgid "Invalid host name"
msgstr "Ongeldige computernaam"

#: src/utils.c:427
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Verwijderen symbolische koppeling `%s' gefaald: %s\n"
