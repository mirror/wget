# Swedish messages for wget
# Copyright (C) 1999 Free Software Foundation, Inc.
# Christian Rose <menthos@menthos.com>, 1999.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1999-11-22 22:21+01:00\n"
"Last-Translator: Christian Rose <menthos@menthos.com>\n"
"Language-Team: Swedish <sv@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-1\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Ansluter till %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Anslutning till %s:%hu vägras.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "ansluten!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Loggar in som %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Fel i serversvar, stänger styrförbindelse.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Fel i serverhälsning.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Skrivning misslyckades, stänger styrförbindelse.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Inloggning nekas av servern.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Felaktig inloggning.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Inloggad!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Okänd typ \"%c\", stänger styrförbindelse.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "färdig.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD behövs inte.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Katalogen \"%s\" finns inte.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "färdig.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD krävs inte.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Kan inte initiera PASV-överföring.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Kan inte tolka PASV-svar.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Försöker ansluta till %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "färdig.  "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bindningsfel (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Felaktig PORT.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST misslyckades, startar om från början.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Filen \"%s\" finns inte.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Filen eller katalogen \"%s\" finns inte.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Längd: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s kvar]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (ej auktoritativt)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, stänger styrförbindelse.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Dataförbindelse: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Styrförbindelse stängd.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Dataöverföring avbruten.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Filen \"%s\" finns redan, hämtar inte.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(försök:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - \"%s\" sparad [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Använder \"%s\" som temporär listningsfil.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Raderade \"%s\".\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekursionsdjupet %d överskred det maximala djupet %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Lokala filen \"%s\" är nyare, hämtar inte.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Storlekarna stämmer inte överens (lokal %ld), hämtar.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Ogiltig symbolisk länk, hoppar över.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "En korrekt symbolisk länk %s -> %s existerar redan.\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Skapar symbolisk länk %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Symboliska länkar stöds inte, hoppar över symbolisk länk \"%s\".\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Hoppar över katalogen \"%s\".\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: okänd/ej understödd filtyp.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: felaktig tidsstämpel.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Hämtar inte kataloger eftersom djupet är %d (max %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Går inte ner till \"%s\" eftersom det är undantaget/inte ingår.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Förkastar \"%s\".\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Inga träffar med mönster \"%s\".\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Skrev HTML-iserat index till \"%s\" [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Skrev HTML-iserat index till \"%s\".\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: flaggan \"%s\" är tvetydig\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: flaggan \"--%s\" tar inget argument\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: flaggan \"%c%s\" tar inget argument\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: flaggan \"%s\" behöver ett argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: okänd flagga \"--%s\"\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: okänd flagga \"%c%s\"\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: otillåten flagga -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: flaggan behöver ett argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Kan inte avgöra användar-id.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Varning: uname misslyckades: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Varning: gethostname misslyckades\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Varning: kan inte avgöra lokal IP-adress.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Varning: kan inte utföra omvänd uppslagning av lokal IP-adress.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Varning: omvänd uppslagning av den lokala adressen gav inget\n"
"fullständigt domännamn!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Servern kunde inte hittas"

#: src/host.c:541
msgid "Unknown error"
msgstr "Okänt fel"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Innehåll i /%s på %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "okänd tid          "

#: src/html.c:467
msgid "File        "
msgstr "Fil         "

#: src/html.c:470
msgid "Directory   "
msgstr "Katalog     "

#: src/html.c:473
msgid "Link        "
msgstr "Länk        "

#: src/html.c:476
msgid "Not sure    "
msgstr "Osäker      "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s byte)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Misslyckades med att skriva HTTP-begäran.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s begäran skickad, väntar på svar... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Filslut vid genomsökning av huvuden.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Läsfel (%s) i huvuden.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Ingen data mottagen"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Missbildad statusrad"

#: src/http.c:594
msgid "(no description)"
msgstr "(ingen beskrivning)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Auktorisering misslyckades.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Okänd auktoriseringsmetod.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Adress: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "ospecificerat"

#: src/http.c:750
msgid " [following]"
msgstr " [följande]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Längd: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s kvar)"

#: src/http.c:774
msgid "ignored"
msgstr "ignorerad"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Varning: jokertecken understöds inte i HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Filen \"%s\" finns redan där, hämtar inte.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Kan inte skriva till \"%s\" (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "FEL: Omdirigering (%d) utan adress.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s FEL %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "\"Last-modified\"-huvud saknas -- tidsstämplar avstängda.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "\"Last-modified\"-huvudet ogiltigt -- tidsstämpel ignorerad.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Filen på fjärrsystemet är nyare, hämtar.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - \"%s\" sparad [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Förbindelse stängd vid byte %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - \"%s\" sparad [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Förbindelse stängd vid byte %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Läsfel vid byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Läsfel vid byte %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Kan inte läsa %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Fel i %s vid rad %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Varning: Både systemets och användarens wgetrc pekar till \"%s\".\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUGG: okänt kommando \"%s\", värde \"%s\".\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Vänligen ange \"on\" eller \"off\".\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Ogiltig specifikation \"%s\".\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Ogiltig specifikation \"%s\"\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Användning: %s [FLAGGA]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, en icke-interaktiv nätverkshämtare.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nObligatoriska argument till långa flaggor är obligatoriska även för de korta.\n\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"Uppstart:\n"
"  -V,  --version           visa versionsinformation och avsluta.\n"
"  -h,  --help              visa denna hjälptext och avsluta.\n"
"  -b,  --background        gå till bakgrunden efter uppstart.\n"
"  -e,  --execute=KOMMANDO  utför ett \".wgetrc\"-kommando.\n"
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
"Loggning och infil:\n"
"  -o,  --output-file=FIL      logga meddelanden till FIL.\n"
"  -a,  --append-output=FIL    lägg till meddelanden till FIL.\n"
"  -d,  --debug                skriv ut avlusningsmeddelanden.\n"
"  -q,  --quiet                tyst (inga utskrifter).\n"
"  -v,  --verbose              var utförlig (detta är standard).\n"
"  -nv, --non-verbose          stäng av utförlighet, utan att vara tyst.\n"
"  -i,  --input-file=FIL       läs URLer från fil.\n"
"  -F,  --force-html           behandla indatafil som HTML.\n"
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
"Nerladdning:\n"
"  -t,  --tries=ANTAL            sätt antal försök till ANTAL (0=obegränsat).\n"
"  -O   --output-document=FIL    skriv dokument till FIL.\n"
"  -nc, --no-clobber             skriv inte över existerande filer.\n"
"  -c,  --continue               fortsätt nerladdningen av en existerande fil.\n"
"       --dot-style=STIL         ställ in visning för nerladdningen.\n"
"  -N,  --timestamping           hämta inte filer om de är äldre än de lokala.\n"
"  -S,  --server-response        visa serversvar.\n"
"       --spider                 ladda inte ner något.\n"
"  -T,  --timeout=SEKUNDER       sätt tidsgräns för läsning till SEKUNDER.\n"
"  -w,  --wait=SEKUNDER          vänta SEKUNDER mellan hämtningar.\n"
"  -Y,  --proxy=on/off           sätt proxy till på (on) eller av (off).\n"
"  -Q,  --quota=ANTAL            sätt gräns för hämtning till ANTAL.\n"
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
"  -nd  --no-directories            skapa inte kataloger.\n"
"  -x,  --force-directories         påtvinga skapande av kataloger.\n"
"  -nH, --no-host-directories       skapa inte värddatorkataloger.\n"
"  -P,  --directory-prefix=PREFIX   spara filer till PREFIX/...\n"
"       --cut-dirs=ANTAL            ignorera ANTAL fjärrkatalogkomponenter.\n"
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
"HTTP-flaggor:\n"
"       --http-user=ANVÄNDARE     sätt http-användare till ANVÄNDARE.\n"
"       --http-passwd=LÖSENORD    sätt http-lösenord till LÖSENORD.\n"
"  -C,  --cache=on/off            tillåt/tillåt inte server-cachad data\n"
"                                 (normalt tillåtet).\n"
"       --ignore-length           ignorera \"Content-Length\"-fält i huvuden.\n"
"       --header=STRÄNG           sätt in STRÄNG bland huvudena.\n"
"       --proxy-user=ANVÄNDARE    sätt ANVÄNDARE som användarnamn för ombud\n"
"                                 (proxy).\n"
"       --proxy-passwd=LÖSENORD   sätt LÖSENORD som lösenord för ombud (proxy).\n"
"  -s,  --save-headers            spara HTTP-huvudena till fil.\n"
"  -U,  --user-agent=AGENT        identifiera som AGENT istället för\n"
"                                 Wget/VERSION.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP-flaggor:\n"
"       --retr-symlinks   hämta symboliska länkar över FTP.\n"
"  -g,  --glob=on/off     sätt på/stäng av filnamnsmatchning.\n"
"       --passive-ftp     använd \"passiv\" överföring.\n"
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
"Rekursiv hämtning:\n"
"  -r,  --recursive             rekursiv webbhämtning -- används varsamt!.\n"
"  -l,  --level=ANTAL           maximalt rekursionsdjup (0 för obegränsat).\n"
"       --delete-after          radera nerladdade filer.\n"
"  -k,  --convert-links         konvertera absoluta länkar till relativa.\n"
"  -m,  --mirror                sätt på flaggor lämpliga för spegling.\n"
"  -nr, --dont-remove-listing   ta inte bort \".listing\"-filer.\n"
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
"Tillåtelser vid rekursiv hämtning:\n"
"  -A,  --accept=LISTA                lista med tillåtna ändelser.\n"
"  -R,  --reject=LISTA                lista med otillåtna ändelser.\n"
"  -D,  --domains=LISTA               lista med tillåtna domäner.\n"
"       --exclude-domains=LISTA       kommaseparerad lista med otillåtna\n"
"                                     domäner.\n"
"  -L,  --relative                    följ endast relativa länkar.\n"
"       --follow-ftp                  följ FTP-länkar från HTML-dokument.\n"
"  -H,  --span-hosts                  gå till främmande värdar i rekursivt läge.\n"
"  -I,  --include-directories=LISTA   lista med tillåtna kataloger.\n"
"  -X,  --exclude-directories=LISTA   lista med uteslutna kataloger.\n"
"  -nh, --no-host-lookup              utför ingen DNS-uppslagning av värdar.\n"
"  -np, --no-parent                   gå inte upp till förälderkatalog.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Skicka felrapporter och förslag till <bug-wget@gnu.org>.\n"
"Skicka anmärkningar på översättningar till <sv@li.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: stöd för felsökningsinformation är inte inkompilerat.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998, 1999 Free Software Foundation, Inc.\n"
"Följande text är en informell översättning som enbart tillhandahålls\n"
"i informativt syfte. För alla juridiska tolkningar gäller den\n"
"engelska originaltexten.\n"
"Detta program distribueras i hopp om att det ska vara användbart,\n"
"men UTAN NÅGON SOM HELST GARANTI, även utan underförstådd garanti\n"
"om SÄLJBARHET eller LÄMPLIGHET FÖR NÅGOT SPECIELLT ÄNDAMÅL. Se GNU\n"
"General Public License för ytterligare information.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nSkrivet av Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ogiltigt kommando\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: ogiltig flagga -- \"-n%c\"\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Prova \"%s --help\" för fler alternativ.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Kan inte vara utförlig och tyst på samma gång.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Kan inte tidsstämpla och inte skriva över gamla filer på samma gång.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL saknas\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Inga URLer hittade i %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"FÄRDIG --%s--\n"
"Laddade ner: %s byte i %d filer\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Nerladdningsgräns (%s byte) ÖVERSKRIDEN!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s mottagna, omdirigerar utdata till \"%%s\".\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break mottaget, omdirigerar utdata till \"%s\".\n"
"Programkörningen fortsätter i bakgrunden.\n"
"Du kan stoppa Wget genom att trycka CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Fortsätter i bakgrunden.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Utdata skrivs till \"%s\".\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Startar WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Kunde inte hitta användbar uttagsdrivrutin (socket driver).\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: varning: \"%s\"-märke förekommer framför alla maskinnamn\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: okänt märke \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Användning: %s NETRC [VÄRDDATORNAMN]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: kan inte ta status på %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Tar bort %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Tar bort %s eftersom den skulle ha avvisats.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Laddar robots.txt; vänligen ignorera fel.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ hoppar över %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Kunde inte hitta proxy-värden.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Måste vara HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Omdirigering till sig själv.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Ger upp.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Försöker igen.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Fel (%s): Länk %s given utan en bas.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Fel (%s): Basen %s relativ utan hänvisar-URL.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Konverterar %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Kan inte konvertera länkar i %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Ej tillräckligt med minne.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Okänt/ej understött protokoll"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Ogiltig portspecifikation"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Ogiltigt värddatornamn"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Misslyckades med att ta bort symboliska länken \"%s\": %s\n"
