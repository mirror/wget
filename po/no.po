# Norwegian messages for GNU wget (bokmål dialect)
# Copyright (C) 1998 Free Software Foundation, Inc.
# Robert Schmidt <rsc@vingmed.no>, 1998.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.2-b1\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1998-05-22 09:00+0100\n"
"Last-Translator: Robert Schmidt <rsc@vingmed.no>\n"
"Language-Team: Norwegian <no@li.org>\n"
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
msgstr "Kontakt med %s:%hu nektet.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "kontakt!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Logger inn som %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Feil i svar fra tjener, lukker kontrollforbindelsen.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Feil i melding fra tjener.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Feil ved skriving, lukker kontrollforbindelsen.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Tjeneren tillater ikke innlogging.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Feil ved innlogging.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Logget inn!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Ukjent type «%c», lukker kontrollforbindelsen.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "OK.    "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD ikke nødvendig.\n"

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Ingen katalog ved navn «%s».\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "OK.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD ikke nødvendig.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Kan ikke sette opp PASV-overføring.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Kan ikke tolke PASV-tilbakemelding.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Vil prøve å kontakte %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "OK.      "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind-feil (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Ugyldig PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"Feil ved REST, starter fra begynnelsen.\n"

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Ingen fil ved navn «%s».\n"
"\n"

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Ingen fil eller katalog ved navn «%s».\n"
"\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Lengde: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s igjen]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (ubekreftet)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, lukker kontrollforbindelsen.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - dataforbindelse: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Forbindelsen brutt.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Dataoverføring brutt.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "File «%s» eksisterer allerede, ignoreres.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(forsøk:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - «%s» lagret [%ld]\n"
"\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Bruker «%s» som temporær katalogliste.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Slettet «%s».\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekursjonsdybde %d overskred maksimal dybde %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""
"Lokal fil «%s» er samme/nyere, ignoreres.\n"
"\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Filstørrelsene er forskjellige (local %ld), hentes.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Ugyldig navn for symbolsk link, ignoreres.\n"

#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Har allerede gyldig symbolsk link %s -> %s\n"
"\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Lager symbolsk link %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symbolske linker ikke støttet, ignorerer «%s».\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Ignorerer katalog «%s».\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: filtypen er ukjent/ikke støttet.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: ugyldig tidsstempel.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Henter ikke kataloger på dybde %d (max %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Behandler ikke «%s» da det er ekskludert/ikke inkludert.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Ignorerer «%s».\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Ingenting passer med mønsteret «%s».\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Skrev HTML-formattert indeks til «%s» [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Skrev HTML-formattert indeks til «%s».\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: flagget «%s» er tvetydig\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: flagget «--%s» tillater ikke argumenter\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: flagget «%c%s» tillater ikke argumenter\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: flagget «%s» krever et argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: ukjent flagg «--%s»\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: ukjent flagg «%c%s»\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: ugyldig flagg -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: flagget krever et argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Fant ikke bruker-ID.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Advarsel: feil fra «uname»:  %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Advarsel: feil fra «gethostname»\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Advarsel: fant ikke lokal IP-adresse.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Advarsel: feil fra tilbake-oppslag for lokal IP-adresse.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Advarsel: fikk ikke FQDN fra tilbake-oppslag for lokal IP-adresse!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Tjener ikke funnet"

#: src/host.c:541
msgid "Unknown error"
msgstr "Ukjent feil"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Indeks for /%s på %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "ukjent tid         "

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
msgstr " (%s bytes)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Feil ved sending av HTTP-forespørsel.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s forespørsel sendt, mottar topptekster... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Filslutt funnet ved lesing av topptekster.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Lesefeil (%s) i topptekster.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Ingen data mottatt"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Feil i statuslinje"

#: src/http.c:594
msgid "(no description)"
msgstr "(ingen beskrivelse)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Autorisasjon mislyktes\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Ukjent autorisasjons-protokoll.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Sted: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "uspesifisert"

#: src/http.c:750
msgid " [following]"
msgstr " [omdirigert]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Lengde: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s igjen)"

#: src/http.c:774
msgid "ignored"
msgstr "ignoreres"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Advarsel: jokertegn ikke støttet i HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Filen «%s» hentes ikke, fordi den allerede eksisterer.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Kan ikke skrive til «%s» (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "FEIL: Omdirigering (%d) uten nytt sted.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s FEIL %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified topptekst mangler -- tidsstempling slås av.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified topptekst ugyldig -- tidsstempel ignoreres.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Fil på tjener er nyere - hentes.\n"

#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - «%s» lagret [%ld/%ld]\n"
"\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Forbindelse brutt ved byte %ld. "

#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - «%s» lagret [%ld/%ld]\n"
"\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Forbindelse brutt ved byte %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Lesefeil ved byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Lesefeil ved byte %ld/%ld (%s)."

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Kan ikke lese %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Feil i %s på linje %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Advarsel: Både systemets og brukerens wgetrc peker til «%s».\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Ukjent kommando «%s», verdi «%s».\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Vennligst spesifiser «on» eller «off».\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Ugyldig spesifikasjon «%s»\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Ugyldig spesifikasjon «%s»\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Bruk: %s [FLAGG]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, en ikke-interaktiv informasjonsagent.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Obligatoriske argumenter til lange flagg er obligatoriske også \n"
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
"Oppstart:\n"
"  -V,  --version           viser Wget's versjonsnummer og avslutter.\n"
"  -h,  --help              skriver ut denne hjelpeteksten.\n"
"  -b,  --background        kjører i bakgrunnen etter oppstart.\n"
"  -e,  --execute=KOMMANDO  utfør en «.wgetrc»-kommando.\n"
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
"Utskrifter og innlesing:\n"
"  -o,  --output-file=FIL      skriv meldinger til ny FIL.\n"
"  -a,  --append-output=FIL    skriv meldinger på slutten av FIL.\n"
"  -d,  --debug                skriv avlusingsinformasjon.\n"
"  -q,  --quiet                stille (ingen utskrifter).\n"
"  -v,  --verbose              vær utførlig (standard).\n"
"  -nv, --non-verbose          mindre utførlig, men ikke stille.\n"
"  -i,  --input-file=FIL       les URLer fra FIL.\n"
"  -F,  --force-html           les inn filer som HTML.\n"
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
"Nedlasting:\n"
"  -t,  --tries=ANTALL           maksimalt antall forsøk (0 for uendelig).\n"
"  -O   --output-document=FIL    skriv nedlastede filer til FIL.\n"
"  -nc, --no-clobber             ikke berør eksisterende filer.\n"
"  -c,  --continue               fortsett nedlasting av en eksisterende fil.\n"
"       --dot-style=TYPE         velg format for nedlastings-status.\n"
"  -N,  --timestamping           ikke hent filer som er eldre enn "
"eksisterende.\n"
"  -S,  --server-response        vis svar fra tjeneren.\n"
"       --spider                 ikke hent filer.\n"
"  -T,  --timeout=SEKUNDER       sett ventetid ved lesing til SEKUNDER.\n"
"  -w,  --wait=SEKUNDER          sett ventetid mellom filer til SEKUNDER.\n"
"  -Y,  --proxy=on/off           sett bruk av proxy på eller av.\n"
"  -Q,  --quota=ANTALL           sett nedlastingskvote til ANTALL.\n"
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
"Kataloger:\n"
"  -nd  --no-directories             ikke lag kataloger.\n"
"  -x,  --force-directories          lag kataloger.\n"
"  -nH, --no-host-directories        ikke lag ovenstående kataloger.\n"
"  -P,  --directory-prefix=PREFIKS   skriv filer til PREFIKS/...\n"
"       --cut-dirs=ANTALL            ignorer ANTALL komponenter av tjenerens\n"
"                                    katalognavn.\n"
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
"HTTP-flagg:\n"
"       --http-user=BRUKER      sett HTTP-bruker til BRUKER.\n"
"       --http-passwd=PASSORD   sett HTTP-passord til PASSORD.\n"
"  -C,  --cache=on/off          (ikke) tillat bruk av hurtiglager på tjener.\n"
"       --ignore-length         ignorer «Content-Length» felt i topptekst.\n"
"       --header=TEKST          sett TEKST inn som en topptekst.\n"
"       --proxy-user=BRUKER     sett proxy-bruker til BRUKER.\n"
"       --proxy-passwd=PASSORD  sett proxy-passord til PASSORD.\n"
"  -s,  --save-headers          skriv HTTP-topptekster til fil.\n"
"  -U,  --user-agent=AGENT      identifiser som AGENT i stedet for \n"
"                               «Wget/VERSJON».\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP-flagg:\n"
"       --retr-symlinks   hent symbolske linker via FTP.\n"
"  -g,  --glob=on/off     (ikke) tolk bruk av jokertegn i filnavn.\n"
"       --passive-ftp     bruk passiv overføringsmodus.\n"
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
"  -r,  --recursive             tillat rekursiv nedlasting -- bruk med "
"omtanke!\n"
"  -l,  --level=ANTALL          maksimalt antall rekursjonsnivåer "
"(0=uendelig).\n"
"       --delete-after          slett nedlastede filer.\n"
"  -k,  --convert-links         konverter absolutte linker til relative.\n"
"  -m,  --mirror                sett passende flagg for speiling av tjenere.\n"
"  -nr, --dont-remove-listing   ikke slett «.listing»-filer.\n"
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
"Hva er tillatt ved rekursjon:\n"
"  -A,  --accept=LISTE               liste med tillatte filtyper.\n"
"  -R,  --reject=LISTE               liste med ikke tillatte filtyper.\n"
"  -D,  --domains=LISTE              liste med tillatte domener.\n"
"       --exclude-domains=LISTE      liste med ikke tillatte domener.\n"
"  -L,  --relative                   følg kun relative linker.\n"
"       --follow-ftp                 følg FTP-linker fra HTML-dokumenter.\n"
"  -H,  --span-hosts                 følg linker til andre tjenere.\n"
"  -I,  --include-directories=LISTE  liste med tillatte katalognavn.\n"
"  -X,  --exclude-directories=LISTE  liste med ikke tillatte katalognavn.\n"
"  -nh, --no-host-lookup             ikke let etter tjenernavn via DNS.\n"
"  -np, --no-parent                  ikke følg linker til ovenstående "
"katalog.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Rapportér feil og send forslag til <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: støtte for avlusing ikke inkludert ved kompilering.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Dette programmet distribueres i håp om at det blir funnet nyttig,\n"
"men UTEN NOEN GARANTIER; ikke en gang for SALGBARHET eller\n"
"EGNETHET TIL NOEN SPESIELL OPPGAVE.\n"
"Se «GNU General Public License» for detaljer.\n"

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""
"\n"
"Skrevet av Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ugyldig kommando\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: ugyldig flagg -- «-n%c»\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Prøv «%s --help» for flere flagg.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Kan ikke være utførlig og stille på samme tid.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""
"Kan ikke tidsstemple og la være å berøre eksisterende filer på samme tid.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL mangler.\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Fant ingen URLer i %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"FERDIG --%s--\n"
"Lastet ned %s bytes i %d filer\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Nedlastingskvote (%s bytes) overskredet!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s mottatt, omdirigerer utskrifter til «%%s».\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break mottatt, omdirigerer utskrifter til `%s'.\n"
"Kjøring fortsetter i bakgrunnen.\n"
"Du kan stoppe Wget ved å trykke CTRL+ALT+DELETE.\n"
"\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Fortsetter i bakgrunnen.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Utskrifter vil bli skrevet til «%s».\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Starter WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Fant ingen brukbar socket-driver.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: Advarsel: symbolet «%s» funnet før tjener-navn\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: ukjent symbol «%s»\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Bruk: %s NETRC [TJENERNAVN]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: «stat» feilet for %s: %s\n"

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
msgstr "Henter robots.txt; ignorer eventuelle feilmeldinger.\n"

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ hopper over %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Fant ikke proxy-tjener.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Må støtte HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Omdirigerer til seg selv.\n"

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Gir opp.\n"
"\n"

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Prøver igjen.\n"
"\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Feil (%s): Link %s gitt uten utgangspunkt.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Feil (%s): Utgangspunktet %s er relativt, ukjent URL som referent.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konverterer %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Kan ikke konvertere linker i %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Ikke nok minne.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Protokollen er ukjent/ikke støttet"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Port-spesifikasjonen er ugyldig"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Tjenernavnet er ugyldig"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Kan ikke slette den symbolske linken «%s»: %s\n"
