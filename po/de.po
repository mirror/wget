# German messages for GNU Wget.
# Copyright © 1997, 1998 Free Software Foundation, Inc.
# Karl Eichwalder <ke@suse.de>, 1998
# Karl Eichwalder <ke@ke.Central.DE>, 1997-1998
#
# 1998-06-15 19:31:58 MEST
# Kosmetische Änderungen für 1.5.2-b4. -ke-
#
# 1998-05-03 09:56:27 MEST
# Nachträge für wget-1.5.1. -ke-
#
# 1998-04-01 20:19:31 MEST
# Nachträge für wget-1.5-b14.
# getopt.c übersetzt. -ke-
#
# 1998-02-21 13:39:23 MET
# Nachträge für wget-1.5-b8. -ke-
#
# 1998-02-08 12:29:34 MET
# Abstimmungen auf wget-1.5-b5.
# Meldungen von getopt.c habe ich bewusst nicht übersetzt. -ke-
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.2-b4\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1998-06-15 19:25+02:00\n"
"Last-Translator: Karl Eichwalder <ke@suse.de>\n"
"Language-Team: German <de@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-1\n"
"Content-Transfer-Encoding: 8-bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Verbindungsaufbau zu %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Verbindung nach %s:%hu zurückgewiesen.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "verbunden!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Einloggen als %s ... "

# Ist das gemeint?
#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Fehler bei der Antwort des Servers, schließe Kontroll-Verbindung.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Fehler bei der Begrüßung des Servers.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Schreiben schlug fehl, schließe Kontroll-Verbindung.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Der Server weist Einloggen zurück.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Einloggen nicht richtig.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Eingeloggt!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Unbekannte Art »%c«, schließe Kontroll-Verbindung.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "fertig.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD nicht notwendig.\n"

#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Kein solches Verzeichnis »%s«.\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "fertig.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD nicht erforderlich.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Kann PASV-Übertragung nicht beginnen.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Kann PASV-Antwort nicht auswerten.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Versuche Verbindung zu %s:%hu herzustellen.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "fertig.    "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Verbindungsfehler (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Ungültiger PORT.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST schlug fehl, starte von Null.\n"

#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Keine solche Datei »%s«.\n"
"\n"

#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Keine solche Datei oder kein solches Verzeichnis »%s«.\n"
"\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Länge: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [noch %s]"

# wohl "unmaßgeblich", nicht "ohne Berechtigung"
#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (unmaßgeblich)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, schließe Kontroll-Verbindung.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Daten-Verbindung: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Kontroll-Verbindung geschlossen.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Daten-Übertragung abgeschlossen.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Datei »%s« ist schon vorhanden, kein Hol-Versuch.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(versuche:%2d)"

# oder "gesichert"?
#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - »%s« gespeichert [%ld]\n"
"\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Benutze »%s« als temporäre Auflistungsdatei.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Entfernt »%s«.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Die Rekursionstiefe %d übersteigt die max. Tiefe %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""
"Lokale Datei »%s« ist neuer, kein Hol-Versuch.\n"
"\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Größen stimmen nicht überein (lokal %ld), Hol-Versuch.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Ungültiger Name für einen symbolischen Verweis, überspringe.\n"

#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr "Der richtige symbolische Verweis %s -> %s ist schon vorhanden\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Lege symbolischen Verweis %s -> %s an\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr ""
"Symbolische Verweise nicht unterstützt, überspringe symbolischen Verweis "
"»%s«.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Überspringe Verzeichnis »%s«.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: unbekannter/nicht unterstüzter Dateityp.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: beschädigter Zeitstempel.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Hole Verzeichnisse nicht, da die Tiefe %d ist (max %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr ""
"Steige nicht zu »%s« hinab, da es ausgeschlossen/nicht eingeschlossen ist.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Weise zurück »%s«.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Keine Übereinstimmungen bei dem Muster »%s«.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Schreibe HTML-artigen Index nach »%s« [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "HTML-artiger Index nach »%s« geschrieben.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: Option `%s' ist zweideutig\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: Option `--%s' erlaubt kein Argument\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: Option `%c%s' erlaubt kein Argument\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: Option `%s' benötigt kein Argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: nicht erkannte Option `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: nicht erkannte Option `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: ungültige Option -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: Option verlangt ein Argument -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Kann Benutzer-Kennung (User-ID) nicht bestimmen.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Warnung: uname fehlgeschlagen: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Warnung: gethostname fehlgeschlagen\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Warnung: lokale IP-Adresse nicht bestimmbar.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Warnung: kein \"reverse-lookup\" für lokale IP-Adresse möglich.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr ""
"%s: Warnung: \"reverse-lookup\" für lokale Adresse ergibt keinen FQDN!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Host nicht gefunden"

#: src/host.c:541
msgid "Unknown error"
msgstr "Unbekannter Fehler"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index von /%s auf %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "Zeit unbekannt     "

#: src/html.c:467
msgid "File        "
msgstr "Datei       "

#: src/html.c:470
msgid "Directory   "
msgstr "Verzeichnis "

#: src/html.c:473
msgid "Link        "
msgstr "Verweis     "

#: src/html.c:476
msgid "Not sure    "
msgstr "Nicht sicher"

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s Bytes)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "HTTP-Anforderung zu schreiben schlug fehl.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s Anforderung gesendet, warte auf Antwort... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Dateiende beim auswerten der Kopfzeilen.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Lesefehler (%s) bei den Kopfzeilen.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Keine Daten empfangen"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Nicht korrekte Statuszeile"

#: src/http.c:594
msgid "(no description)"
msgstr "(keine Beschreibung)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Authorisierung fehlgeschlagen.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Unbekannten Authentifizierungsablauf.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Platz: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "nicht spezifiziert"

#: src/http.c:750
msgid " [following]"
msgstr "[folge]"

# Header
#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Länge: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (noch %s)"

#: src/http.c:774
msgid "ignored"
msgstr "übergangen"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Warnung: Joker-Zeichen werden bei HTTP nicht unterstützt.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Datei »%s« schon vorhanden, kein Hol-Versuch.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Kann nicht nach »%s« schreiben (%s).\n"

# Was meint hier location?
#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "FEHLER: Redirektion (%d) ohne Ziel(?).\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s FEHLER %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "»Last-modified«-Kopfzeile fehlt -- Zeitstempel abgeschaltet.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "»Last-modified«-Kopfzeile ungültig -- Zeitstempeln übergangen.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Entfernte Datei ist neuer, Hol-Versuch.\n"

#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - »%s« gesichert [%ld/%ld]\n"
"\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Verbindung bei Byte %ld geschlossen. "

#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - »%s« gesichert [%ld/%ld])\n"
"\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Verbindung bei Byte %ld/%ld geschlossen. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Lesefehler bei Byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Lesefehler bei Byte %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Kann »%s« nicht lesen (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Fehler in »%s« bei Zeile %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Warnung: wgetrc des Systems und des Benutzers zeigen nach »%s«.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Unbekannter Befehl »%s«, Wert »%s«.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Bitte »on« oder »off« angeben.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Ungültige Angabe »%s«\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Ungültige Angabe »%s«\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Syntax: %s [OPTION]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, ein nicht-interaktives Netzwerk-Tool zum Holen.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Zwingende Argumente zu langen Optionen sind auch zwingend bei kurzen "
"Optionen.\n"
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
"Beim Start:\n"
"  -V,  --version          Programmversion anzeigen\n"
"  -h,  --help             diese Hilfe anzeigen\n"
"  -b,  --background       nach dem Starten in den Hintergrund gehen\n"
"  -e,  --execute=BEFEHL   einen ».wgetrc«-Befehl ausführen\n"
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
"Log-Datei schreiben und Eingabe-Datei:\n"
"  -o,  --output-file=DATEI    Log-Meldungen in DATEI schreiben\n"
"  -a,  --append-output=DATEI  Meldungen der DATEI anhängen\n"
"  -d,  --debug                Debug-Ausgabe anzeigen\n"
"  -q,  --quiet                still (keine Ausgabe von Meldungen)\n"
"  -v,  --verbose              mitteilsam (dies ist Standard)\n"
"  -nv, --non-verbose          Mitteilsamkeit reduzieren; nicht ganz still\n"
"  -i,  --input-file=DATEI     URLs aus DATEI lesen\n"
"  -F,  --force-html           Eingabe-Datei als HTML behandeln\n"
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
"Holen (download):\n"
"  -t,  --tries=ZAHL             setze Anzahl der Wiederholversuch auf ZAHL\n"
"                                  (0 ohne Beschränkung)\n"
"  -O   --output-document=DATEI  schreibe Dokumente in DATEI\n"
"  -nc, --no-clobber             bestehende Dateien nicht überschreiben\n"
"  -c,  --continue               beginne erneut, eine existierende Datei\n"
"                                  zu holen\n"
"       --dot-style=STYLE        Hol-Anzeige auf STYLE setzen\n"
"  -N,  --timestamping           hole keine Dateien, die älter als die "
"lokalen\n"
"                                  sind\n"
"  -S,  --server-response        Antwort des Servers anzeigen\n"
"       --spider                 nichts holen (don't download anything)\n"
"  -T,  --timeout=SEKUNDEN       den Lese-Timeout auf SEKUNDEN setzen\n"
"  -w,  --wait=SEKUNDEN          SEKUNDEN zwischen den Hol-Versuchen warten\n"
"  -Y,  --proxy=on/off           Proxy ein (»on«) oder aus (»off«) stellen\n"
"  -Q,  --quota=ZAHL             setze die Hol-Vorgänge auf ZAHL\n"
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
"Verzeichnisse:\n"
"  -nd  --no-directories            keine Verzeichnisse anlegen\n"
"  -x,  --force-directories         Anlegen von Verzeichnissen erwingen\n"
"  -nH, --no-host-directories       keine Host-Verzeichnisse anlegen\n"
"  -P,  --directory-prefix=PREFIX   Dateien nach PREFIX/... sichern\n"
"       --cut-dirs=ZAHL             ignoriere die ZAHL der entfernten\n"
"                                     Verzeichnisbestandteile\n"
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
"HTTP-Optionen:\n"
"       --http-user=USER       setze http-Benutzer auf USER\n"
"       --http-passwd=PASS     setse http-Passwort auf PASS\n"
"  -C,  --cache=on/off         erlaube/verbiete server-gepufferte Daten\n"
"                                (server-cached data) (normalerweise "
"erlaubt)\n"
"       --ignore-length        ignoriere das »Content-Length«-Kopffeld\n"
"       --header=ZEICHENKETTE  ZEICHENKETTE zwischen die Kopfzeilen einfügen\n"
"       --proxy-user=USER      setze USER als Proxy-Benutzername\n"
"       --proxy-passwd=PASS    setze PASS als Proxy-Passwort\n"
"  -s,  --save-headers         sichere die HTTP-Kopfzeilen in Datei\n"
"  -U,  --user-agent=AGENT     als AGENT anstelle of Wget/VERSION "
"identifizieren\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP-Optionen:\n"
"       --retr-symlinks   hole symbolische Verweise (FTP)\n"
"  -g,  --glob=on/off     Dateinamen-»Globbing« ein (»on«) oder aus (»off«)\n"
"                           stellen\n"
"       --passive-ftp     den \"passiven\" Übertragungsmodus verwenden\n"
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
"Rekursives Holen:\n"
"  -r,  --recursive             rekursives Web-Saugen -- mit Umsicht "
"verwenden!\n"
"  -l,  --level=Zahl            maximale Rekursionstiefe (0 ohne Begrenzung)\n"
"       --delete-after          geholte Dateien löschen\n"
"  -k,  --convert-links         nicht-relative Verweise in relative "
"umwandeln\n"
"  -m,  --mirror                geeignete Optionen fürs Spiegeln (mirroring)\n"
"                                 einschalten\n"
"  -nr, --dont-remove-listing   ».listing«-Dateien nicht entfernen\n"
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
"Recursiv erlauben/zurückweisen:\n"
"  -A,  --accept=LISTE                Liste der erlaubten Erweiterungen\n"
"  -R,  --reject=LISTE                Liste der zurückzuweisenden "
"Erweiterungen\n"
"  -D,  --domains=LISTE               Liste der erlaubten Domains\n"
"       --exclude-domains=LISTE       komma-unterteilte Liste der\n"
"                                       zurückzuweisen Domains\n"
"  -L,  --relative                    nur relativen Verweisen folgen\n"
"       --follow-ftp                  FTP-Verweisen von HTML-Dokumenten aus\n"
"                                       folgen\n"
"  -H,  --span-hosts                  wenn »--recursive«, auch zu fremden "
"Hosts\n"
"                                       gehen\n"
"  -I,  --include-directories=LISTE   Liste der erlaubten Verzeichnisse\n"
"  -X,  --exclude-directories=LISTE   Liste der auszuschließenden "
"Verzeichnisse\n"
"  -nh, --no-host-lookup              kein DNS-lookup für Hosts durchführen\n"
"  -np, --no-parent                   nicht zum übergeordneten Verzeichnis\n"
"                                       hinaufsteigen\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr ""
"Fehlerberichte und Verbesserungsvorschläge bitte an <bug-wget@gnu.org>\n"
"schicken.\n"
"\n"
"Für die deutsche Übersetzung ist die Mailingliste <de@li.org> zuständig.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: Debug-Unterstützung nicht hineinkompiliert.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright © 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Es gibt KEINERLEI Garantie, nicht einmal für die TAUGLICHKEIT oder die,\n"
"VERWENDBARKEIT ZU EINEM ANGEGEBENEN ZWECK.  In den Quellen befindet sich "
"die\n"
"Lizenz- und Kopierbedingung; die Einzelheiten sind in der Datei COPYING\n"
"(GNU General Public License) beschrieben.\n"

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""
"\n"
"Geschrieben von Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ungültiger Befehl\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: ungültige Option -- »-n%c«\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "»%s --help« gibt weitere Informationen.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "\"Mitteilsam\" und \"still\" ist gleichzeitig unmöglich.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""
"Zeitstempeln und nicht Überschreiben alter Dateien ist gleichzeitig "
"unmöglich.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL fehlt\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Keine URLs in %s gefunden.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"BEENDET --%s--\n"
"Geholt: %s Bytes in %d Dateien\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Hol-Kontingent (%s Bytes) ERSCHÖPFT!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s erhalten, weise Ausgabe nach »%%s« zurück.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break (= Strg+Abbruch) empfangen, Ausgabe wird nach »%s« umgeleitet.\n"
"Ausführung wird im Hintergrund fortgeführt.\n"
"Wget kann durch das Drücken von CTRL+ALT+DELETE (= Strg+Alt+Entf)\n"
"gestopt werden.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Im Hintergrund geht's weiter.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Ausgabe wird nach »%s« geschrieben.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "WinHelp %s wird gestartet\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Kann keinen benutzbaren \"socket driver\" finden.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: Warnung: »%s«-Wortteil erscheint vor einem Maschinennamen\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: unbekannter Wortteil »%s«\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Syntax: %s NETRC [HOSTNAME]\n"

# stat
#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: kann nicht finden %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Entferne »%s«.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Entferne »%s«, da dies zurückgewiesen werden soll.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Lade »robots.txt«; bitte Fehler ignorieren.\n"

#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ überspringe %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Kann Proxy-Host nicht finden.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Muss HTTP sein.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Redirektion auf sich selber.\n"

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Gebe auf.\n"
"\n"

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Versuche erneut.\n"
"\n"

# ???
#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Fehler (%s): Verweis »%s« ohne »base« versucht.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Fehler (%s): »Base« %s relativ, ohne Bezugs-URL.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Wandle um %s... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Kann Verweise nicht umwandeln zu %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Nicht genügend Speicher.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Unbekanntes/nicht unterstütztes Protokoll"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Ungültige Port-Angabe"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Ungültiger Hostname"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Entfernen des symbolischen Verweises »%s« schlug fehlt: %s\n"
