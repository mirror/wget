# Finnish messages for wget.
# Copyright (C) 2002 Free Software Foundation, Inc.
# Petri Koistinen <petri.koistinen@iki.fi>, 2002.
# Proofreading by Tero Jänkä and others.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.9.1\n"
"POT-Creation-Date: 2003-10-11 16:21+0200\n"
"PO-Revision-Date: 2003-11-21 16:50+0200\n"
"Last-Translator: Petri Koistinen <petri.koistinen@iki.fi>\n"
"Language-Team: Finnish <translation-team-fi@lists.sourceforge.net>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-15\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/connect.c:88
#, c-format
msgid "Unable to convert `%s' to a bind address.  Reverting to ANY.\n"
msgstr "Ei voi muuttaa \"%s\":ta bind-osoitteeksi. Valitaan ANY.\n"

#: src/connect.c:165
#, c-format
msgid "Connecting to %s[%s]:%hu... "
msgstr "Yhdistetään %s[%s]:%hu... "

#: src/connect.c:168
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Yhdistetään %s:%hu... "

#: src/connect.c:222
msgid "connected.\n"
msgstr "yhdistetty.\n"

#: src/convert.c:171
#, c-format
msgid "Converted %d files in %.2f seconds.\n"
msgstr "Muutettu %d tiedostoa %.2f sekunnissa.\n"

#: src/convert.c:197
#, c-format
msgid "Converting %s... "
msgstr "Muunnetaan %s... "

#: src/convert.c:210
msgid "nothing to do.\n"
msgstr "ei ole mitään tehtävää.\n"

#: src/convert.c:218 src/convert.c:242
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Ei voi muuttaa linkkejä %s: %s\n"

#: src/convert.c:233
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Ei voi poistaa \"%s\": %s\n"

#: src/convert.c:439
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Tiedostoa %s ei voi varmuuskopioida tiedostoon %s: %s\n"

#: src/cookies.c:606
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Virhe Set-Cookiessa, kenttä \"%s\""

#: src/cookies.c:629
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Syntaksivirhe Set-Cookiessa: %s kohdassa %d.\n"

#: src/cookies.c:1426
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Ei voi avata evästetiedostoa \"%s\": %s\n"

#: src/cookies.c:1438
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Virhe kirjoitettaessa tiedostoon \"%s\": %s\n"

#: src/cookies.c:1442
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Virhe suljettaessa \"%s\": %s\n"

#: src/ftp-ls.c:812
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Listaustyyppiä ei tueta, yritetään jäsentää unix-listauksena.\n"

#: src/ftp-ls.c:857 src/ftp-ls.c:859
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s indeksi kohteessa %s:%d"

#: src/ftp-ls.c:882
msgid "time unknown       "
msgstr "tuntematon aika    "

#: src/ftp-ls.c:886
msgid "File        "
msgstr "Tiedosto    "

#: src/ftp-ls.c:889
msgid "Directory   "
msgstr "Hakemisto   "

#: src/ftp-ls.c:892
msgid "Link        "
msgstr "Linkki      "

#: src/ftp-ls.c:895
msgid "Not sure    "
msgstr "Epävarma    "

#: src/ftp-ls.c:913
#, c-format
msgid " (%s bytes)"
msgstr " (%s tavua)"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:202
#, c-format
msgid "Logging in as %s ... "
msgstr "Kirjaudutaan nimellä %s ... "

#: src/ftp.c:215 src/ftp.c:268 src/ftp.c:299 src/ftp.c:353 src/ftp.c:468
#: src/ftp.c:519 src/ftp.c:551 src/ftp.c:611 src/ftp.c:675 src/ftp.c:748
#: src/ftp.c:796
msgid "Error in server response, closing control connection.\n"
msgstr "Virhe palvelimen vastauksessa, suljetaan hallintayhteys.\n"

#: src/ftp.c:223
msgid "Error in server greeting.\n"
msgstr "Virhe palvelimen tervehdyksessä.\n"

#: src/ftp.c:231 src/ftp.c:362 src/ftp.c:477 src/ftp.c:560 src/ftp.c:621
#: src/ftp.c:685 src/ftp.c:758 src/ftp.c:806
msgid "Write failed, closing control connection.\n"
msgstr "Kirjoitus epäonnistui, suljetaan hallintayhteys.\n"

#: src/ftp.c:238
msgid "The server refuses login.\n"
msgstr "Palvelin hylkäsi kirjautumisen.\n"

#: src/ftp.c:245
msgid "Login incorrect.\n"
msgstr "Kirjautuminen epäonnistui.\n"

#: src/ftp.c:252
msgid "Logged in!\n"
msgstr "Kirjauduttu!\n"

#: src/ftp.c:277
msgid "Server error, can't determine system type.\n"
msgstr "Palvelimen virhe, järjestelmän tyyppiä ei voi päätellä.\n"

#: src/ftp.c:287 src/ftp.c:596 src/ftp.c:659 src/ftp.c:716
msgid "done.    "
msgstr "valmis.  "

#: src/ftp.c:341 src/ftp.c:498 src/ftp.c:533 src/ftp.c:779 src/ftp.c:827
msgid "done.\n"
msgstr "valmis.\n"

#: src/ftp.c:370
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tuntematon tyyppi \"%c\", suljetaan hallintayhteys.\n"

#: src/ftp.c:383
msgid "done.  "
msgstr "valmis."

#: src/ftp.c:389
msgid "==> CWD not needed.\n"
msgstr "==> CWD:tä ei tarvita.\n"

#: src/ftp.c:484
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Hakemistoa \"%s\" ei ole.\n"
"\n"

#. do not CWD
#: src/ftp.c:502
msgid "==> CWD not required.\n"
msgstr "==> CWD:tä ei tarvita.\n"

#: src/ftp.c:567
msgid "Cannot initiate PASV transfer.\n"
msgstr "PASV-siirtoa ei voi alustaa.\n"

#: src/ftp.c:571
msgid "Cannot parse PASV response.\n"
msgstr "PASV-vastausta ei voi jäsentää.\n"

#: src/ftp.c:588
#, c-format
msgid "couldn't connect to %s:%hu: %s\n"
msgstr "ei voi yhdistää %s:%hu: %s\n"

#: src/ftp.c:638
#, c-format
msgid "Bind error (%s).\n"
msgstr "Bind-virhe (%s).\n"

#: src/ftp.c:645
msgid "Invalid PORT.\n"
msgstr "PORTTI ei kelpaa.\n"

#: src/ftp.c:698
#, c-format
msgid ""
"\n"
"REST failed; will not truncate `%s'.\n"
msgstr ""
"\n"
"REST epäonnistui; en lyhennä \"%s\".\n"

#: src/ftp.c:705
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST epäonnistui, aloitetaan alusta.\n"

#: src/ftp.c:766
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Tiedostoa \"%s\" ei ole.\n"
"\n"

#: src/ftp.c:814
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Tiedostoa tai hakemistoa \"%s\" ei ole.\n"
"\n"

#: src/ftp.c:898 src/ftp.c:906
#, c-format
msgid "Length: %s"
msgstr "Pituus: %s"

#: src/ftp.c:900 src/ftp.c:908
#, c-format
msgid " [%s to go]"
msgstr " [%s jäljellä]"

#: src/ftp.c:910
msgid " (unauthoritative)\n"
msgstr " (epävarma)\n"

#: src/ftp.c:936
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, suljetaan hallintayhteys.\n"

#: src/ftp.c:944
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - tiedonsiirtoyhteys: %s; "

#: src/ftp.c:961
msgid "Control connection closed.\n"
msgstr "Hallintayhteys suljettu.\n"

#: src/ftp.c:979
msgid "Data transfer aborted.\n"
msgstr "Tiedonsiirto keskeytetty.\n"

#: src/ftp.c:1044
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Tiedosto \"%s\" on jo olemassa, ei noudeta.\n"

#: src/ftp.c:1114 src/http.c:1716
#, c-format
msgid "(try:%2d)"
msgstr "(yritys:%2d)"

#: src/ftp.c:1180 src/http.c:1975
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - \"%s\" tallennettu [%ld]\n"
"\n"

#: src/ftp.c:1222 src/main.c:890 src/recur.c:377 src/retr.c:596
#, c-format
msgid "Removing %s.\n"
msgstr "Poistetaan %s.\n"

#: src/ftp.c:1264
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Käytetään \"%s\" listauksen väliaikaistiedostona.\n"

#: src/ftp.c:1279
#, c-format
msgid "Removed `%s'.\n"
msgstr "\"%s\" poistettu.\n"

#: src/ftp.c:1314
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekursiosyvyys %d saavutettu, suurin syvyys %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1384
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Etätiedosto \"%s\" ei ole paikallista uudempi -- ei noudeta.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1391
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr ""
"Etätiedosto \"%s\" on uudempi kuin paikallinen -- noudetaan.\n"
"\n"

#. Sizes do not match
#: src/ftp.c:1398
#, c-format
msgid ""
"The sizes do not match (local %ld) -- retrieving.\n"
"\n"
msgstr ""
"Koot eivät täsmää (paikallinen %ld) -- noudetaan.\n"
"\n"

#: src/ftp.c:1415
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Symbolisen linkin nimi ei kelpaa, ohitetaan.\n"

#: src/ftp.c:1432
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Symbolinen linkki %s -> %s on jo olemassa.\n"
"\n"

#: src/ftp.c:1440
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Luodaan symbolinen linkki %s -> %s\n"

#: src/ftp.c:1451
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Ei tukea symbolisille linkeille, ohitetaan \"%s\".\n"

#: src/ftp.c:1463
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Ohitetaan hakemisto \"%s\".\n"

#: src/ftp.c:1472
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tuntematon/tukematon tiedostotyyppi.\n"

#: src/ftp.c:1499
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: vääristynyt aikaleima.\n"

#: src/ftp.c:1524
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "En nouda hakemistoja, koska syvyys on %d (yläraja %d).\n"

#: src/ftp.c:1574
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Hakemisto \"%s\" on poissuljettu, sisältöä ei noudeta.\n"

#: src/ftp.c:1639 src/ftp.c:1652
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Hylätään \"%s\".\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1698
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Ei täsmää malliin \"%s\".\n"

#: src/ftp.c:1764
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Kirjoitettu HTML-indeksi tiedostoon \"%s\" [%ld].\n"

#: src/ftp.c:1769
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Kirjoitettu HTML-indeksi tiedostoon \"%s\".\n"

#: src/gen_sslfunc.c:117
msgid "Could not seed OpenSSL PRNG; disabling SSL.\n"
msgstr "OpenSSL PRNG:tä ei voi alustaa; estetään SSL.\n"

#: src/getopt.c:675
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: valinta \"%s\" on moniselkoinen\n"

#: src/getopt.c:700
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: valinta \"--%s\" ei hyväksy parametrejä\n"

#: src/getopt.c:705
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: valinta \"%c%s\" ei hyväksy parametrejä\n"

#: src/getopt.c:723 src/getopt.c:896
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: valinta \"%s\" vaatii parametrin\n"

#. --option
#: src/getopt.c:752
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: tuntematon valinta \"--%s\"\n"

#. +option or -option
#: src/getopt.c:756
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: tuntematon valinta \"%c%s\"\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:782
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: valinta ei kelpaa -- %c\n"

#: src/getopt.c:785
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: valinta ei kelpaa -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:815 src/getopt.c:945
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: valinta vaatii parametrin -- %c\n"

#: src/getopt.c:862
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: valinta \"-W %s\" on moniselkoinen\n"

#: src/getopt.c:880
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: valinta \"-W %s\" ei hyväksy parametrejä\n"

#: src/host.c:636
#, c-format
msgid "Resolving %s... "
msgstr "Selvitetään osoitetta %s... "

#: src/host.c:656 src/host.c:672
#, c-format
msgid "failed: %s.\n"
msgstr "epäonnistui: %s.\n"

#: src/host.c:674
msgid "failed: timed out.\n"
msgstr "epäonnistui: aikaraja ylittyi.\n"

#: src/host.c:762
msgid "Host not found"
msgstr "Palvelinta ei löytynyt"

#: src/host.c:764
msgid "Unknown error"
msgstr "Tuntematon virhe"

#: src/html-url.c:293
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Epätäydellistä linkkiä %s ei voi selvittää.\n"

#. this is fatal
#: src/http.c:674
msgid "Failed to set up an SSL context\n"
msgstr "SSL-kontekstin asettaminen epäonnistui\n"

#: src/http.c:680
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "Varmenteen lataaminen epäonnistui kohteesta %s\n"

#: src/http.c:684 src/http.c:692
msgid "Trying without the specified certificate\n"
msgstr "Yritetään ilman määriteltyä varmennetta\n"

#: src/http.c:688
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Varmenteen haku ei onnistunut kohteesta %s\n"

#: src/http.c:761 src/http.c:1809
msgid "Unable to establish SSL connection.\n"
msgstr "SSL-yhteyden muodostaminen ei onnistu.\n"

#: src/http.c:770
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Uudelleenkäytetään yhteyttä %s:%hu.\n"

#: src/http.c:1034
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "HTTP-pyynnön kirjoitus epäonnistui: %s.\n"

#: src/http.c:1039
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s-pyyntö lähetetty, odotetaan vastausta... "

#: src/http.c:1083
msgid "End of file while parsing headers.\n"
msgstr "Tiedoston loppu otsakkeita jäsennettäessä.\n"

#: src/http.c:1093
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Lukuvirhe (%s) otsakkeissa.\n"

#: src/http.c:1128
msgid "No data received"
msgstr "Dataa ei ole vastaanotettu"

#: src/http.c:1130
msgid "Malformed status line"
msgstr "Väärin muotoiltu tilarivi"

#: src/http.c:1135
msgid "(no description)"
msgstr "(ei kuvausta)"

#: src/http.c:1267
msgid "Authorization failed.\n"
msgstr "Todentaminen epäonnistui.\n"

#: src/http.c:1274
msgid "Unknown authentication scheme.\n"
msgstr "Tuntematon varmennusjärjestelmä.\n"

#: src/http.c:1314
#, c-format
msgid "Location: %s%s\n"
msgstr "Sijainti: %s%s\n"

#: src/http.c:1315 src/http.c:1454
msgid "unspecified"
msgstr "määrittelemätön"

#: src/http.c:1316
msgid " [following]"
msgstr " [seurataan]"

#: src/http.c:1383
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    Tiedosto on jo kokonaan noudettu; ei ole mitään tehtävää.\n"
"\n"

#: src/http.c:1401
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Tiedoston noutamisen jatkaminen epäonnistui, mikä on ristiriidassa \"-c\" vastaan.\n"
"Ei lyhennetä alkuperäistä tiedostoa \"%s\".\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1444
msgid "Length: "
msgstr "Pituus: "

#: src/http.c:1449
#, c-format
msgid " (%s to go)"
msgstr " (%s jäljellä)"

#: src/http.c:1454
msgid "ignored"
msgstr "jätetty huomiotta"

#: src/http.c:1598
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Varoitus: jokerimerkkejä ei tueta HTTP:ssä.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1628
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Tiedosto \"%s\" on jo olemassa, ei noudeta.\n"

#: src/http.c:1800
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Tiedostoon \"%s\" ei voi kirjoittaa (%s).\n"

#: src/http.c:1819
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "VIRHE: Edelleenohjaus (%d) ilman sijaintia.\n"

#: src/http.c:1851
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s VIRHE %d: %s.\n"

#: src/http.c:1864
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Viimeksi muutettu -otsake puuttuu -- aikaleimat poistettu käytöstä.\n"

#: src/http.c:1872
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Viimeksi muutettu -otsake kelvoton -- aikaleima jätetty huomiotta.\n"

#: src/http.c:1895
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"Palvelimen tiedosto \"%s\" ei ole paikallista uudempi -- ei noudeta.\n"
"\n"

#: src/http.c:1903
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Koot eivät täsmää (paikallinen %ld) -- noudetaan.\n"

#: src/http.c:1907
msgid "Remote file is newer, retrieving.\n"
msgstr "Etätiedosto on uudempi, noudetaan.\n"

#: src/http.c:1948
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - \"%s\" tallennettu [%ld/%ld]\n"
"\n"

#: src/http.c:1998
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Yhteys suljettu tavun %ld kohdalla. "

#: src/http.c:2007
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - \"%s\" tallennettu [%ld/%ld])\n"
"\n"

#: src/http.c:2028
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Yhteys suljettu tavun %ld/%ld kohdalla. "

#: src/http.c:2040
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Lukuvirhe tavun %ld kohdalla (%s)."

#: src/http.c:2049
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Lukuvirhe tavun %ld/%ld kohdalla (%s). "

#: src/init.c:342
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC osoittaa kohteeseen %s, jota ei ole olemassa.\n"

#: src/init.c:398 src/netrc.c:276
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Ei voi lukea %s (%s).\n"

#: src/init.c:416 src/init.c:422
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Virhe kohdassa %s rivillä %d.\n"

#: src/init.c:454
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Varoitus: Sekä järjestelmän että käyttäjän wgetrc osoittaa \"%s\".\n"

#: src/init.c:594
#, c-format
msgid "%s: Invalid --execute command `%s'\n"
msgstr "%s: Kelvoton --execute komento \"%s\"\n"

#: src/init.c:630
#, c-format
msgid "%s: %s: Invalid boolean `%s', use `on' or `off'.\n"
msgstr "%s: %s: Kelvoton valinta \"%s\", valitse on (päällä) tai off (pois päältä).\n"

#: src/init.c:673
#, c-format
msgid "%s: %s: Invalid boolean `%s', use always, on, off, or never.\n"
msgstr "%s: %s: Kelvoton valinta \"%s\", valitse always, on, off tai never.\n"

#: src/init.c:691
#, c-format
msgid "%s: %s: Invalid number `%s'.\n"
msgstr "%s: %s: Numero \"%s\" ei kelpaa.\n"

#: src/init.c:930 src/init.c:949
#, c-format
msgid "%s: %s: Invalid byte value `%s'\n"
msgstr "%s: %s: Tavun arvo \"%s\" ei kelpaa.\n"

#: src/init.c:974
#, c-format
msgid "%s: %s: Invalid time period `%s'\n"
msgstr "%s: %s: Aikaväli \"%s\" ei kelpaa.\n"

#: src/init.c:1051
#, c-format
msgid "%s: %s: Invalid header `%s'.\n"
msgstr "%s: %s: Otsake \"%s\" ei kelpaa.\n"

#: src/init.c:1106
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Edistymistyyppi \"%s\" ei kelpaa.\n"

#: src/init.c:1157
#, c-format
msgid "%s: %s: Invalid restriction `%s', use `unix' or `windows'.\n"
msgstr "%s: %s: Kelvoton rajoitus \"%s\", valitse \"unix\" tai \"windows\".\n"

#: src/init.c:1198
#, c-format
msgid "%s: %s: Invalid value `%s'.\n"
msgstr "%s: %s: Arvo \"%s\" ei kelpaa.\n"

#: src/log.c:636
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""
"\n"
"%s vastaanotettu, ohjataan tulostus tiedostoon \"%s\".\n"

#. Eek!  Opening the alternate log file has failed.  Nothing we
#. can do but disable printing completely.
#: src/log.c:643
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; loki poistettu käytöstä.\n"

#: src/main.c:127
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Käyttö: %s [VALINTA]... [URL]...\n"

#: src/main.c:135
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, tiedostojen noutaja.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:140
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Pitkien valintojen parametrit ovat pakollisia myös lyhyille.\n"
"\n"

#: src/main.c:144
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Käynnistys:\n"
"  -V,  --version                   näyttää Wget:in version ja lopettaa.\n"
"  -h,  --help                      näyttää tämän ohjeen.\n"
"  -b,  --background                siirtyy taustalle käynnistyksen jälkeen.\n"
"  -e,  --execute=KOMENTO           suorittaa \".wgetrc\"-tyylisen komennon.\n"
"\n"

#: src/main.c:151
msgid ""
"Logging and input file:\n"
"  -o,  --output-file=FILE     log messages to FILE.\n"
"  -a,  --append-output=FILE   append messages to FILE.\n"
"  -d,  --debug                print debug output.\n"
"  -q,  --quiet                quiet (no output).\n"
"  -v,  --verbose              be verbose (this is the default).\n"
"  -nv, --non-verbose          turn off verboseness, without being quiet.\n"
"  -i,  --input-file=FILE      download URLs found in FILE.\n"
"  -F,  --force-html           treat input file as HTML.\n"
"  -B,  --base=URL             prepends URL to relative links in -F -i file.\n"
"\n"
msgstr ""
"Loki ja syöttötiedostot:\n"
"  -o,  --output-file=TIEDOSTO      kirjoita viestit TIEDOSTOON.\n"
"  -a,  --append-output=TIEDOSTO    lisää viestit TIEDOSTOON.\n"
"  -d,  --debug                     tulosta vianetsintätiedot.\n"
"  -q,  --quiet                     hiljainen (ei tulostusta).\n"
"  -v,  --verbose                   ole monisanainen (tämä on oletus).\n"
"  -nv, --non-verbose               monisanaisuus pois, muttei hiljainen.\n"
"  -i,  --input-file=TIEDOSTO       lataa URLit TIEDOSTOSTA.\n"
"  -F,  --force-html                käsittele syöttötiedostoa HTML:nä.\n"
"  -B,  --base=URL                  lisää URLin suht. linkkien alkuun -F -i tiedostoon.\n"
"\n"

#: src/main.c:163
msgid ""
"Download:\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"       --retry-connrefused      retry even if connection is refused.\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --progress=TYPE          select progress gauge type.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set all timeout values to SECONDS.\n"
"       --dns-timeout=SECS       set the DNS lookup timeout to SECS.\n"
"       --connect-timeout=SECS   set the connect timeout to SECS.\n"
"       --read-timeout=SECS      set the read timeout to SECS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"       --random-wait            wait from 0...2*WAIT secs between retrievals.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"       --limit-rate=RATE        limit download rate to RATE.\n"
"       --dns-cache=off          disable caching DNS lookups.\n"
"       --restrict-file-names=OS restrict chars in file names to ones OS allows.\n"
"\n"
msgstr ""
"Noutaminen:\n"
"       --bind-address=OSOITE       sido OSOITE (konenimi tai IP) paikalliseen koneeseen.\n"
"  -t,  --tries=MÄÄRÄ               asettaa yrityskertojen MÄÄRÄn (0 on rajaton).\n"
"  -O   --output-document=TIEDOSTO  kirjoita asiakirjat TIEDOSTOON.\n"
"  -nc, --no-clobber                älä ylikirjoita tiedostoja, äläkä käytä .#-liitteitä.\n"
"  -c,  --continue                  jatka osittain noudetun tiedoston hakemista.\n"
"       --progress=TYYPPI           valitse edistymismittarin tyyppi.\n"
"  -N,  --timestamping              nouda vain paikallista uudemmat tiedostot.\n"
"  -S,  --server-response           tulosta palvelimen vastaus.\n"
"       --spider                    älä nouda mitään tiedostoja.\n"
"  -T,  --timeout=SEKUNTIA          aseta lukemisen katkaisuviive.\n"
"  -w,  --wait=SEKUNTIA             odota SEKUNTIA noutojen välillä.\n"
"       --waitretry=SEKUNTIA        odota 1...SEKUNTIA noutojen uudelleenyritysten välillä.\n"
"       --random-wait               odota 0...2*WAIT sekuntia noutojen välillä.\n"
"  -Y,  --proxy=on/off              välityspalvelin päälle tai pois.\n"
"  -Q,  --quota=LUKU                aseta noutokiintiö LUVUN kokoiseksi.\n"
"       --limit-rate=NOPEUS         rajoita noutonopeus NOPEUTEEN.\n"
"       --dns-cache=off             älä pidä nimipalveluhakuja välimuistissa.\n"
"       --restrict-file-names=OS    rajoita tiedostonimet käyttöjärjestelmän sallimiin.\n"
"\n"

#: src/main.c:188
msgid ""
"Directories:\n"
"  -nd, --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Hakemistot:\n"
"  -nd  --no-directories            älä luo hakemistoja.\n"
"  -x,  --force-directories         pakotettu hakemistojen luonti.\n"
"  -nH, --no-host-directories       älä luo konekohtaisia hakemistoja.\n"
"  -P,  --directory-prefix=ETULIITE tallenna tiedostot hakemistoon ETULIITE/...\n"
"       --cut-dirs=LUKU             ohita alusta LUKU kpl hakemistoja.\n"
"\n"

#: src/main.c:196
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\n"
"  -E,  --html-extension      save all text/html documents with .html extension.\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"       --referer=URL         include `Referer: URL' header in HTTP request.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"       --no-http-keep-alive  disable HTTP keep-alive (persistent connections).\n"
"       --cookies=off         don't use cookies.\n"
"       --load-cookies=FILE   load cookies from FILE before session.\n"
"       --save-cookies=FILE   save cookies to FILE after session.\n"
"       --post-data=STRING    use the POST method; send STRING as the data.\n"
"       --post-file=FILE      use the POST method; send contents of FILE.\n"
"\n"
msgstr ""
"HTTP-valinnat:\n"
"       --http-user=KÄYTTÄJÄ        aseta http-käyttäjäksi KÄYTTÄJÄ.\n"
"       --http-passwd=SALASANA      aseta http-salasanaksi SALASANA.\n"
"  -C,  --cache=on/off              salli välivarastoidun datan käyttö (oletus).\n"
"  -E,  --html-extension            tallenna text/html dokumentit .html päätteisinä.\n"
"       --ignore-length             älä välitä \"Content-Length\"-otsakekentästä.\n"
"       --header=MERKKIJONO         lisää MERKKIJONO otsakkeiden sekaan.\n"
"       --proxy-user=KÄYTTÄJÄ       aseta välityspalvelimen käyttäjänimeksi KÄYTTÄJÄ.\n"
"       --proxy-passwd=SALASANA     aseta välityspalvelimen salasanaksi SALASANA.\n"
"       --referer=URL               liitä \"Referer: URL\"-otsake http-pyyntöön.\n"
"  -s,  --save-headers              tallenna http-otsakkeet tiedostoon.\n"
"  -U,  --user-agent=AGENTTI        tunnnistaudu Wget/versio sijasta AGENTIKSI.\n"
"       --no-http-keep-alive        älä salli jatkuvia yhteyksiä (http keep-alive).\n"
"       --cookies=off               älä käytä evästeitä.\n"
"       --load-cookies=TIEDOSTO     lue evästeet ennen istuntoa TIEDOSTOSTA.\n"
"       --save-cookies=TIEDOSTO     tallenna evästeet istunnon jälkeen TIEDOSTOON.\n"
"       --post-data=MERKKIJONO      käytä POST methodia; lähetä MERKKIJONO datana.\n"
"       --post-file=TIEDOSTO        käytä POST methodia; lähetä TIEDOSTON sisältö.\n"
"\n"

#: src/main.c:217
msgid ""
"HTTPS (SSL) options:\n"
"       --sslcertfile=FILE     optional client certificate.\n"
"       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n"
"       --egd-file=FILE        file name of the EGD socket.\n"
"       --sslcadir=DIR         dir where hash list of CA's are stored.\n"
"       --sslcafile=FILE       file with bundle of CA's\n"
"       --sslcerttype=0/1      Client-Cert type 0=PEM (default) / 1=ASN1 (DER)\n"
"       --sslcheckcert=0/1     Check the server cert agenst given CA\n"
"       --sslprotocol=0-3      choose SSL protocol; 0=automatic,\n"
"                              1=SSLv2 2=SSLv3 3=TLSv1\n"
"\n"
msgstr ""
"HTTPS (SSL) -valinnat:\n"
"       --sslcertfile=TIEDOSTO      vapaaehtoinen asiakassertifikaatti.\n"
"       --sslcertkey=AVAINTIEDOSTO  vapaaehtoinen avaintiedosto tälle sertifikaatille.\n"
"       --egd-file=TIEDOSTO         EGD-pistokkeen tiedostonimi.\n"
"       --sslcadir=DIR              hakemisto minne CA:den tiivistelista on tallennettu.\n"
"       --sslcafile=FILE            tiedosto, jossa on CA kokoelma\n"
"       --sslcerttype=0/1           asiakkaan sertifikaatin tyyppi 0=PEM (oletus) / 1=ASN1 (DER)\n"
"       --sslcheckcert=0/1          tarkista palvelimen sertifikaatti annettua CA:ta vasten\n"
"       --sslprotocol=0-3           valitse SSL-protokolla; 0=automaattinen,\n"
"                                   1=SSLv2 2=SSLv3 3=TLSv1\n"
"\n"

#: src/main.c:230
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"FTP-valinnat:\n"
"  -nr, --dont-remove-listing       älä poista \".listing\"-tiedostoja.\n"
"  -g,  --glob=on/off               aseta tiedostonimentäydennys päälle tai pois.\n"
"       --passive-ftp               käytä \"passiivista\" siirtotapaa.\n"
"       --retr-symlinks             rekursiossa: nouda linkitetyt tiedostot (ei hakemistoja).\n"
"\n"

#: src/main.c:237
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive          recursive download.\n"
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
"       --delete-after       delete files locally after downloading them.\n"
"  -k,  --convert-links      convert non-relative links to relative.\n"
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
"  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n"
"  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
"       --strict-comments    turn on strict (SGML) handling of HTML comments.\n"
"\n"
msgstr ""
"Rekursiivinen nouto:\n"
"  -r,  --recursive                 rekursiivinen verkkoimu -- käytä varoen!\n"
"  -l,  --level=LUKU                rekursiosyvyyden yläraja (inf tai 0 on ääretön).\n"
"       --delete-after              poista tiedostot haun jälkeen.\n"
"  -k,  --convert-links             muuta ei-suhteelliset linkit suhteellisiksi.\n"
"  -K,  --backup-converted          ennen tiedoston X muuttamista, varmuuskopioi X.orig nimellä.\n"
"  -m,  --mirror                    oikopolkuvalinta, yhtäkuin -r -N -l inf -nr.\n"
"  -p,  --page-requisites           nouda kaikki kuvat yms. html-sivun näyttämiseen tarvittava.\n"
"       --strict-comments           käytä HTML-kommenttien tiukkaa (SGML) käsittelyä.\n"
"\n"

#: src/main.c:248
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                comma-separated list of accepted extensions.\n"
"  -R,  --reject=LIST                comma-separated list of rejected extensions.\n"
"  -D,  --domains=LIST               comma-separated list of accepted domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected domains.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"       --follow-tags=LIST           comma-separated list of followed HTML tags.\n"
"  -G,  --ignore-tags=LIST           comma-separated list of ignored HTML tags.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -L,  --relative                   follow relative links only.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Rekursiivinen hyväksyntä/hylkäys:\n"
"  -A,  --accept=LISTA              lista hyväksytyistä päätteistä.\n"
"  -R,  --reject=LISTA              lista hylätyistä päätteistä.\n"
"  -D,  --domains=LISTA             lista hyväksytyistä verkkotunnuksista.\n"
"       --exclude-domains=LISTA     lista hylätyistä verkkotunnuksista.\n"
"       --follow-ftp                seuraa ftp-linkkejä html-dokumenteista.\n"
"       --follow-tags=LISTA         lista seurattavista html-tageista.\n"
"  -G,  --ignore-tags=LISTA         lista ohitettavista html-tageista.\n"
"  -H,  --span-hosts                mene eri palvelimille rekursiossa.\n"
"  -L,  --relative                  seuraa vain suhteellisia linkkejä.\n"
"  -I,  --include-directories=LISTA lista hyväksytyistä hakemistoista.\n"
"  -X,  --exclude-directories=LISTA lista poissuljetuista hakemistoista.\n"
"  -np, --no-parent                 älä nouse hakemistorakenteessa.\n"
"\n"

#: src/main.c:263
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Lähetä virheraportit ja ehdotukset osoitteeseen <bug-wget@gnu.org>.\n"

#: src/main.c:465
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: vianetsintätukea ei ole käännetty mukaan.\n"

#: src/main.c:517
msgid "Copyright (C) 2003 Free Software Foundation, Inc.\n"
msgstr "Tekijänoikeus (C) 2003 Free Software Foundation, Inc.\n"

#: src/main.c:519
msgid ""
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Tätä ohjelmaa levitetään siinä toivossa, että se olisi hyödyllinen,\n"
"mutta ilman mitään takuuta; ilman edes hiljaista takuuta kaupallisesti\n"
"hyväksyttävästä laadusta tai soveltuvuudesta tiettyyn tarkoitukseen.\n"
"Katso GPL-lisenssistä lisää yksityiskohtia.\n"

#: src/main.c:524
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Alunperin kirjoittanut Hrvoje Niksic <hniksic@xemacs.org>.\n"

#: src/main.c:703
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: virheellinen valinta -- \"-n%c\"\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:706 src/main.c:748 src/main.c:794
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Kirjoita \"%s --help\" saadaksesi lisää ohjeita.\n"

#: src/main.c:774
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Ei voi olla monisanainen ja hiljainen yhtäaikaa.\n"

#: src/main.c:780
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Ei voi aikaleimata ja olla koskematta vanhoihin tiedostoihin yhtäaikaa.\n"

#. No URL specified.
#: src/main.c:789
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL puuttuu\n"

#: src/main.c:905
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Tiedostosta %s ei löytynyt URLeja.\n"

#: src/main.c:914
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"VALMIS --%s--\n"
"Noudettu: %s tavua ja %d tiedostoa\n"

#: src/main.c:920
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Hakukiintiö (%s tavua) YLITETTY!\n"

#: src/mswindows.c:147
msgid "Continuing in background.\n"
msgstr "Ohjelman suoritus jatkuu taustalla.\n"

#: src/mswindows.c:149 src/utils.c:487
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Tulostus kirjoitetaan tiedostoon \"%s\".\n"

#: src/mswindows.c:245
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Käynnistetään WinHelp %s\n"

#: src/mswindows.c:272 src/mswindows.c:279
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Ei löytynyt käyttökelpoista socket-ajuria.\n"

#: src/netrc.c:380
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: varoitus: \"%s\" merkintä esiintyy kaikkien koneiden nimien edessä\n"

#: src/netrc.c:411
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: tuntematon merkki \"%s\"\n"

#: src/netrc.c:475
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Käyttö: %s NETRC [KOHDENIMI]\n"

#: src/netrc.c:485
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: tiedostoa ei voi käsitellä %s: %s\n"

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:234
#, c-format
msgid ""
"\n"
"%*s[ skipping %dK ]"
msgstr ""
"\n"
"%*s[ ohitetaan %d kB ]"

#: src/progress.c:401
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Pistetyylin määrittely \"%s\" ei kelpaa; ei muuteta.\n"

#: src/recur.c:378
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Poistetaan %s koska se pitäisi olla hylätty.\n"

#: src/res.c:549
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Ladataan robots.txt; älä välitä virheistä.\n"

#: src/retr.c:400
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Virhe jäsennettäessä välityspalvelimen URLia %s: %s.\n"

#: src/retr.c:408
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Virhe välityspalvelimen URLissa %s: Täytyy olla HTTP.\n"

#: src/retr.c:493
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d edelleenohjaukset ylitetty.\n"

#: src/retr.c:617
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Luovutetaan.\n"
"\n"

#: src/retr.c:617
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Yritetään uudelleen.\n"
"\n"

#: src/url.c:621
msgid "No error"
msgstr "Ei virhettä"

#: src/url.c:623
msgid "Unsupported scheme"
msgstr "Kaavaa ei tueta"

#: src/url.c:625
msgid "Empty host"
msgstr "Ei koneen nimeä"

#: src/url.c:627
msgid "Bad port number"
msgstr "Portin numero ei kelpaa"

#: src/url.c:629
msgid "Invalid user name"
msgstr "Epäkelpo käyttäjätunnus"

#: src/url.c:631
msgid "Unterminated IPv6 numeric address"
msgstr "Päättämätön numeerinen IPv6-osoite"

#: src/url.c:633
msgid "IPv6 addresses not supported"
msgstr "IPv6 osoitteita ei tueta"

#: src/url.c:635
msgid "Invalid IPv6 numeric address"
msgstr "Epäkelpo numeerinen IPv6-osoite"

#: src/utils.c:120
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Ei ole tarpeeksi muistia.\n"

#. parent, no error
#: src/utils.c:485
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Ohjelman suoritus jatkuu taustalla, pid %d.\n"

#: src/utils.c:529
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Symbolisen linkin \"%s\" poistaminen epäonnistui: %s\n"
