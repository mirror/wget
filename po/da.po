# Danish messages for GNU wget
# Copyright (C) 1998 Free Software Foundation, Inc.
# Keld Jørn Simonsen <keld@dkuug.dk>, 2000.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 2000-10-23 00:53-0200\n"
"Last-Translator: Keld Jørn Simonsen <keld@dkuug.dk>\n"
"Language-Team: Danish <dansk@klid.dk>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Kontakter %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Kontakt med %s:%hu nægtet.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "kontakt!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Logger ind som %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Fejl i svar fra tjener, lukker kontrolforbindelsen.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Fejl i besked fra tjener.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Fejl ved skrivning, lukker kontrolforbindelsen.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Tjeneren tillader ikke indlogging.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Fejl ved indlogging.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Logget ind!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Ukendt type '%c', lukker kontrolforbindelsen.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "OK.    "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD ikke nødvendig.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Intet katalog ved navn '%s'.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "Ok.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD ikke nødvendig.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Kan ikke opsætte PASV-overføring.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Kan ikke tolke PASV-tilbagemelding.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Vil prøve at kontakte %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "færdig.      "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind-fejl (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Ugyldig PORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nFejl ved REST, starter forfra.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Ingen fil ved navn '%s'.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Ingen fil eller katalog ved navn '%s'.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Længde: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s tilbage]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (ubekræftet)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, lukker kontrolforbindelsen.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - dataforbindelse: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Forbindelsen brudt.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Dataoverførsel brudt.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "File '%s' eksisterer allerede, ignoreres.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(forsøg:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - '%s' gemt [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Bruger '%s' som temporær katalogliste.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Slettet '%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekursionsdybde %d overskred maksimal dybde %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Lokal fil '%s' er samme/nyere, ignoreres.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Filstørrelserne er forskellige (local %ld), hentes.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Ugyldig navn for symbolsk lænke, ignoreres.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Har allerede gyldig symbolsk lænke %s -> %s\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Laver symbolsk lænke %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symbolske lænker ikke understøttet, ignorerer '%s'.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Ignorerer katalog '%s'.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: filtypen er ukendt/ikke understøttet.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: ugyldigt tidsstempel.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Henter ikke kataloger, da dybde er %d (max %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Behandler ikke '%s' da det er ekskluderet/ikke inkluderet.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Ignorerer '%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Ingenting passer med mønstret '%s'.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Skrev HTML-formatteret indeks til '%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Skrev HTML-formatteret indeks til '%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: flaget '%s' er flertydig\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: flaget '--%s' tillader ikke argumenter\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: flaget '%c%s' tillader ikke argumenter\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: flaget '%s' kræver et argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: ukendt flag '--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: ukendt flag '%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: ugyldig flag -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: flaget kræver et argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Fandt ikke bruger-ID.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Advarsel: fejl fra 'uname':  %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Advarsel: fejl fra 'gethostname'\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Advarsel: fandt ikke lokal IP-adresse.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Advarsel: fejl fra tilbage-opslag for lokal IP-adresse.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Advarsel: fik ikke FQDN fra tilbage-opslag for lokal IP-adresse!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Tjener ikke fundet"

#: src/host.c:541
msgid "Unknown error"
msgstr "Ukendt fejl"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Indeks for /%s på %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "ukendt tid         "

#: src/html.c:467
msgid "File        "
msgstr "Fil         "

#: src/html.c:470
msgid "Directory   "
msgstr "Katalog     "

#: src/html.c:473
msgid "Link        "
msgstr "Link        "

#: src/html.c:476
msgid "Not sure    "
msgstr "Usikker     "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s byte)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Fejl ved sending af HTTP-forespørgsel.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s forespørgsel sendt, modtager toptekster... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Filafslutning fundet ved læsning af toptekster.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Læsefejl (%s) i toptekster.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Ingen data modtaget"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Fejl i statuslinje"

#: src/http.c:594
msgid "(no description)"
msgstr "(ingen beskrivelse)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Autorisation mislykkedes\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Ukendt autorisations-protokol.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Sted: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "uangivet"

#: src/http.c:750
msgid " [following]"
msgstr " [omdirigeret]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Længde: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s tilbage)"

#: src/http.c:774
msgid "ignored"
msgstr "ignoreret"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Advarsel: jokertegn ikke understøttet i HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Filen '%s' hentes ikke, fordi den allerede eksisterer.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Kan ikke skrive til '%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "FEJL: Omdirigering (%d) uden nyt sted.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s FEJL %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified toptekst mangler -- tidsstempling slås fra.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified toptekst ugyldig -- tidsstempel ignoreret.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Fil på tjener er nyere - hentes.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - '%s' gemt [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Forbindelse brudt ved byte %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - '%s' gemt [%ld/%ld]\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Forbindelse brudt ved byte %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Læsefejl ved byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Læsefejl ved byte %ld/%ld (%s)."

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Kan ikke læse %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Fejl i %s på linje %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Advarsel: Både systemets og brugerens wgetrc peger på '%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Ukendt kommando '%s', værdi '%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Venligst angiv 'on' eller 'off'.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Ugyldig specifikation '%s'\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Ugyldig specifikation '%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Brug: %s [FLAG]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, en ikke-interaktiv informationsagent.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr ""
"\n"
"Obligatoriske argumenter til lange flag er obligatoriske også \n"
"for korte.\n"
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
"Opstart:\n"
"  -V,  --version           viser Wget's versionsnummer og afslutter.\n"
"  -h,  --help              udskriver denne hjælpetekst.\n"
"  -b,  --background        kører i baggrunden efter opstart.\n"
"  -e,  --execute=KOMMANDO  udfør en '.wgetrc'-kommando.\n"
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
"Udskrifter og indlæsning:\n"
"  -o,  --output-file=FIL      skriv beskeder til ny FIL.\n"
"  -a,  --append-output=FIL    skriv beskeder på slutningen af FIL.\n"
"  -d,  --debug                skriv aflusingsinformation.\n"
"  -q,  --quiet                stille (ingen udskrifter).\n"
"  -v,  --verbose              vær udførlig (standard).\n"
"  -nv, --non-verbose          mindre udførlig, men ikke stille.\n"
"  -i,  --input-file=FIL       læs URLer fra FIL.\n"
"  -F,  --force-html           læs ind filer som HTML.\n"
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
"Nedlasting:\n"
"  -t,  --tries=ANTAL            maksimalt antal forsøg (0 for uendelig).\n"
"  -O   --output-document=FIL    skriv nedlastede filer til FIL.\n"
"  -nc, --no-clobber             berør ikke eksisterende filer.\n"
"  -c,  --continue               fortsæt nedlasting af en eksisterende fil.\n"
"       --dot-style=TYPE         vælg format for nedlastings-status.\n"
"  -N,  --timestamping           hent ikke filer som er ældre end eksisterende.\n"
"  -S,  --server-response        vis svar fra tjeneren.\n"
"       --spider                 hent ikke filer.\n"
"  -T,  --timeout=SEKUNDER       sæt ventetid ved læsning til SEKUNDER.\n"
"  -w,  --wait=SEKUNDER          sæt ventetid mellem filer til SEKUNDER.\n"
"  -Y,  --proxy=on/off           slå brug af proxy til eller fra.\n"
"  -Q,  --quota=ANTAL            sæt nedlastingskvote til ANTAL.\n"
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
"Kataloger:\n"
"  -nd  --no-directories             lav ikke kataloger.\n"
"  -x,  --force-directories          lav kataloger.\n"
"  -nH, --no-host-directories        lav ikke ovenstående kataloger.\n"
"  -P,  --directory-prefix=PRÆFIKS   skriv filer til PRÆFIKS/...\n"
"       --cut-dirs=ANTAL             ignorér ANTAL komponenter af tjenerens\n"
"                                    katalognavn.\n"
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
"HTTP-flag:\n"
"       --http-user=BRUGER      sæt HTTP-bruger til BRUGER.\n"
"       --http-passwd=PASSORD   sæt HTTP-adgangskode til PASSORD.\n"
"  -C,  --cache=on/off          tillad (ikke) brug af hurtiglager på tjener.\n"
"       --ignore-length         ignorer 'Content-Length' felt i toptekst.\n"
"       --header=TEKST          sæt TEKST ind som en toptekst.\n"
"       --proxy-user=BRUGER     sæt proxy-bruger til BRUGER.\n"
"       --proxy-passwd=PASSORD  sæt proxy-adgangskode til PASSORD.\n"
"  -s,  --save-headers          skriv HTTP-toptekster til fil.\n"
"  -U,  --user-agent=AGENT      identificer som AGENT i stedet for \n"
"                               'Wget/VERSION'.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP-flag:\n"
"       --retr-symlinks   hent symbolske lænker via FTP.\n"
"  -g,  --glob=on/off     tolk (ikke) brug af jokertegn i filnavn.\n"
"       --passive-ftp     brug passiv overføringsmodus.\n"
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
"Rekursiv nedlasting:\n"
"  -r,  --recursive             tillad rekursiv nedlasting -- brug med omtanke!\n"
"  -l,  --level=ANTAL           maksimalt antal rekursionsniveauer (0=uendelig).\n"
"       --delete-after          slet nedlastede filer.\n"
"  -k,  --convert-links         konverter absolutte lænker til relative.\n"
"  -m,  --mirror                sæt passende flag for spejling af tjenere.\n"
"  -nr, --dont-remove-listing   slet ikke '.listing'-filer.\n"
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
"Hvad er tilladt ved rekursion:\n"
"  -A,  --accept=LISTE               liste med tilladte filtyper.\n"
"  -R,  --reject=LISTE               liste med ikke-tilladte filtyper.\n"
"  -D,  --domains=LISTE              liste med tilladte domæner.\n"
"       --exclude-domains=LISTE      liste med ikke-tilladte domæner.\n"
"  -L,  --relative                   følg kun relative linker.\n"
"       --follow-ftp                 følg FTP-lænker fra HTML-dokumenter.\n"
"  -H,  --span-hosts                 følg lænker til andre tjenere.\n"
"  -I,  --include-directories=LISTE  liste med tilladte katalognavn.\n"
"  -X,  --exclude-directories=LISTE  liste med ikke-tilladte katalognavn.\n"
"  -nh, --no-host-lookup             led ikke efter tjenernavn via DNS.\n"
"  -np, --no-parent                  følg ikke lænker til ovenstående katalog.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Rapportér fejl og send forslag til <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: støtte for aflusing ikke inkluderet ved kompilering.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Dette program distribueres i håb om at det bliver fundet nyttigt,\n"
"men UDEN NOGEN GARANTIER; ikke engang for SALGBARHED eller\n"
"EGNETHED TIL NOGEN SPECIEL OPGAVE.\n"
"Se 'GNU General Public License' for detaljer.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nSkrevet af Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ugyldig kommando\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: ugyldigt flag -- '-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Prøv '%s --help' for flere flag.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Kan ikke være udførlig og stille på samme tid.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Kan ikke tidsstemple og lade være at berøre eksisterende filer på samme tid.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL mangler.\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Fandt ingen URLer i %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"FÆRDIG --%s--\n"
"Lastet ned %s byte i %d filer\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Nedlastingskvote (%s bytes) overskredet!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s modtaget, omdirigerer udskrifter til '%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break modtaget, omdirigerer udskrifter til `%s'.\n"
"Kørsel fortsætter i baggrunden.\n"
"Du kan stoppe Wget ved at trykke CTRL+ALT+DELETE.\n"
"\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Fortsætter i baggrunden.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Udskrifter vil blive skrevet til '%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Starter WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Fandt ingen brugbar sokkel-driver.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: Advarsel: symbolet '%s' fundet før tjener-navn\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: ukendt symbol '%s'\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Brug: %s NETRC [TJENERNAVN]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: 'stat' fejlede for %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Fjerner %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Fjerner %s fordi den skal forkastes.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Henter robots.txt; ignorer eventuelle fejlmeldinger.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ hopper over %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Fandt ikke proxy-tjener.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Skal understøtte HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Omdirigerer til sig selv.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Giver op.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Prøver igen.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Fejl (%s): Lænke %s givet uden udgangspunkt.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Fejl (%s): Udgangspunktet %s er relativt, ukendt URL som referent.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konverterer %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Kan ikke konvertere lænker i %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Ikke nok hovedlager.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Protokollen er ukendt/ikke understøttet"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Port-specifikationen er ugyldig"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Tjenernavnet er ugyldigt"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Kan ikke slette den symbolske lænke '%s': %s\n"
