# Hungarian translation of GNU wget
# Copyright (C) 2001 Free Software Foundation, Inc.
# Pal Szasz <szpal@Maria.UTCluj.Ro>, 2001.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.7\n"
"POT-Creation-Date: 2001-06-03 15:27+0200\n"
"PO-Revision-Date: 2001-10-28 10:56+0200\n"
"Last-Translator: Pal Szasz <szpal@Maria.UTCluj.Ro>\n"
"Language-Team: Hungarian <hu@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-2\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/cookies.c:588
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Hiba a Set-Cookie-ban, mezõ `%s'"

#: src/cookies.c:612
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Szintaktikai hiba a Set-Cookie-ban a `%c' karakternél.\n"

#: src/cookies.c:620
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Szintaktikai hiba a Set-Cookie-ban: korai vége a szövegnek.\n"

#: src/cookies.c:1352
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Nem tudom megnyitni a `%s' cookie állományt: %s\n"

#: src/cookies.c:1364
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Nem tudok írni `%s'-ba (%s).\n"

#: src/cookies.c:1368
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Hiba `%s' bezárásánál: %s\n"

#: src/ftp-ls.c:787
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Nemkezelt lista tipus, próbálom Unix lista értelmezõvel.\n"

#: src/ftp-ls.c:832 src/ftp-ls.c:834
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s tartalma %s:%d-n"

#: src/ftp-ls.c:856
msgid "time unknown       "
msgstr "idõ ismeretlen     "

#: src/ftp-ls.c:860
msgid "File        "
msgstr "Állomány    "

#: src/ftp-ls.c:863
msgid "Directory   "
msgstr "Könyvtár    "

#: src/ftp-ls.c:866
msgid "Link        "
msgstr "Link        "

#: src/ftp-ls.c:869
msgid "Not sure    "
msgstr "Nem biztos  "

#: src/ftp-ls.c:887
#, c-format
msgid " (%s bytes)"
msgstr " (%s bájt)"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:150 src/http.c:624
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Csatlakozás %s:%hu-hoz... "

#: src/ftp.c:172 src/ftp.c:539 src/http.c:641
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Kapcsolódás %s:%hu-hoz visszautasítva.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:193 src/http.c:652
msgid "connected!\n"
msgstr "kapcsolódva!\n"

#: src/ftp.c:194
#, c-format
msgid "Logging in as %s ... "
msgstr "Belépés mint %s ... "

#: src/ftp.c:203 src/ftp.c:256 src/ftp.c:288 src/ftp.c:336 src/ftp.c:429
#: src/ftp.c:481 src/ftp.c:575 src/ftp.c:648 src/ftp.c:709 src/ftp.c:757
msgid "Error in server response, closing control connection.\n"
msgstr "Hiba a szerver válaszában, vezérlõ kapcsolat bezárva.\n"

#: src/ftp.c:211
msgid "Error in server greeting.\n"
msgstr "Hiba a szerver üdvözlésében.\n"

#: src/ftp.c:219 src/ftp.c:345 src/ftp.c:438 src/ftp.c:490 src/ftp.c:585
#: src/ftp.c:658 src/ftp.c:719 src/ftp.c:767
msgid "Write failed, closing control connection.\n"
msgstr "Írás nem sikerült, vezérlõ kapcsolat bezárva.\n"

#: src/ftp.c:226
msgid "The server refuses login.\n"
msgstr "A szerver visszautasítja a belépést.\n"

#: src/ftp.c:233
msgid "Login incorrect.\n"
msgstr "Belépés sikertelen.\n"

#: src/ftp.c:240
msgid "Logged in!\n"
msgstr "Belépve !\n"

#: src/ftp.c:265
msgid "Server error, can't determine system type.\n"
msgstr "Szerver hiba, nem tudom meghatározni a rendszer tipusát.\n"

#: src/ftp.c:275 src/ftp.c:560 src/ftp.c:632 src/ftp.c:689
msgid "done.    "
msgstr "vége.    "

#: src/ftp.c:325 src/ftp.c:459 src/ftp.c:740 src/ftp.c:788 src/url.c:1429
msgid "done.\n"
msgstr "vége.\n"

#: src/ftp.c:353
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Ismeretlen tipus `%c', vezérlõ kapcsolat bezárva.\n"

#: src/ftp.c:366
msgid "done.  "
msgstr "vége.  "

#: src/ftp.c:372
msgid "==> CWD not needed.\n"
msgstr "==> CWD nem szükséges.\n"

#: src/ftp.c:445
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Nincs ilyen könyvtár `%s'.\n\n"

#. do not CWD
#: src/ftp.c:463
msgid "==> CWD not required.\n"
msgstr "==> CWD nem szükséges.\n"

#: src/ftp.c:497
msgid "Cannot initiate PASV transfer.\n"
msgstr "Nem tudok kezdeményezni PASV átvitelt.\n"

#: src/ftp.c:501
msgid "Cannot parse PASV response.\n"
msgstr "Nem tudom értelmezni a PASV választ.\n"

#: src/ftp.c:515
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Megpróbálok csatlakozni %s:%hu-hoz.\n"

#: src/ftp.c:602
#, c-format
msgid "Bind error (%s).\n"
msgstr "Hozzárendelési hiba (%s).\n"

#: src/ftp.c:618
msgid "Invalid PORT.\n"
msgstr "Hibás PORT.\n"

#: src/ftp.c:671
#, c-format
msgid "\nREST failed; will not truncate `%s'.\n"
msgstr "\nREST nem sikerült; nem fogom tördelni `%s'-t.\n"

#: src/ftp.c:678
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST nem sikerült, kezdés elõlröl.\n"

#: src/ftp.c:727
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Nincs ilyen állomány `%s'.\n\n"

#: src/ftp.c:775
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Nincs ilyen állomány vagy könyvtár `%s'.\n\n"

#: src/ftp.c:859 src/ftp.c:867
#, c-format
msgid "Length: %s"
msgstr "Hossz: %s"

#: src/ftp.c:861 src/ftp.c:869
#, c-format
msgid " [%s to go]"
msgstr " [még %s]"

#: src/ftp.c:871
msgid " (unauthoritative)\n"
msgstr " (nem hiteles)\n"

#: src/ftp.c:898
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, vezérlõ kapcsolat bezárva.\n"

#: src/ftp.c:906
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Adat kapcsolat: %s; "

#: src/ftp.c:923
msgid "Control connection closed.\n"
msgstr "Vezérlõ kapcsolat bezárva.\n"

#: src/ftp.c:941
msgid "Data transfer aborted.\n"
msgstr "Adatátvitel megszakítva.\n"

#: src/ftp.c:1005
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Az `%s' állomány már létezik, nem töltöm le.\n"

#: src/ftp.c:1075 src/http.c:1502
#, c-format
msgid "(try:%2d)"
msgstr "(próba:%2d)"

#: src/ftp.c:1139 src/http.c:1753
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' lementve [%ld]\n\n"

#: src/ftp.c:1181 src/main.c:810 src/recur.c:483 src/retr.c:566
#, c-format
msgid "Removing %s.\n"
msgstr "Törlöm %s.\n"

#: src/ftp.c:1221
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "`%s'-t használom mint ideiglenes lista állomány.\n"

#: src/ftp.c:1233
#, c-format
msgid "Removed `%s'.\n"
msgstr "Törölve `%s'.\n"

#: src/ftp.c:1269
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Rekurziós határ %d túllépte a maximális %d mélységet.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1330
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "A szerveren lévõ `%s' állomány nem újabb mint a helyi -- nem töltöm le.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1337
#, c-format
msgid "Remote file is newer than local file `%s' -- retrieving.\n\n"
msgstr "A szerveren lévõ `%s' állomány újabb mint a helyi -- letöltöm.\n\n"

#. Sizes do not match
#: src/ftp.c:1344
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n\n"
msgstr "A méretek nem eggyeznek (helyi %ld) -- letöltöm.\n\n"

#: src/ftp.c:1361
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Hibás nevû szimbólikus link, kihagyom.\n"

#: src/ftp.c:1378
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Már létezõ helyes szimbólikus link %s -> %s\n\n"

#: src/ftp.c:1386
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Létrehozom a %s -> %s szimbólikus linket\n"

#: src/ftp.c:1397
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "A `%s' szimbólikus linket kihagyom.\n"

#: src/ftp.c:1409
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "A `%s' könyvtárat kihagyom.\n"

#: src/ftp.c:1418
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: nem ismert/nem kezelhetõ állomány tipus.\n"

#: src/ftp.c:1445
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: hibás idö-bejegyzés.\n"

#: src/ftp.c:1466
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Könyvtárakat nem töltöm le, mivel a mélység %d (max %d).\n"

#: src/ftp.c:1512
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Nem lépek be `%s'-be mert ki van zárva/nincs kijelölve.\n"

#: src/ftp.c:1559
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Visszautasítom `%s'-t.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1606
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Nincs találat a `%s' mintához .\n"

#: src/ftp.c:1671
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "A HTML-esített indexet a `%s' [%ld] állományba írtam.\n"

#: src/ftp.c:1676
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "A HTML-esített indexet a `%s' állományba írtam.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: a `%s' opció kétes értelmû\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: a `--%s' opcióhoz nem kell argumentum\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: a `%c%s' opcióhoz nem kell argumentum\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: a `%s' opcióhoz kell argumentum\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: ismeretlen opció `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: ismeretlen opció `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: helytelen opció -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: az opcióhoz szükség van argumentumra -- %c\n"

#: src/host.c:374
msgid "Host not found"
msgstr "Host-ot nem találom"

#: src/host.c:376
msgid "Unknown error"
msgstr "Ismeretlen hiba"

#. this is fatal
#: src/http.c:555
msgid "Failed to set up an SSL context\n"
msgstr "Nem sikerült SSL-t beállítsak\n"

#: src/http.c:561
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "Nem sikerült betöltsem az igazolásokat %s-ról\n"

#: src/http.c:565 src/http.c:573
msgid "Trying without the specified certificate\n"
msgstr "Megpróbálom a megadott igazolás nélkül\n"

#: src/http.c:569
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Nemsikerült megszerezni az igazoló kulcsot %s-ról\n"

#: src/http.c:663 src/http.c:1593
msgid "Unable to establish SSL connection.\n"
msgstr "Nem sikerült SSL kapcsolatot létrehozni.\n"

#: src/http.c:671
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Újrahasználom a kapcsolatot %s:%hu-hoz.\n"

#: src/http.c:861
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "A HTTP kérés írása sikertelen: %s.\n"

#: src/http.c:866
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s kérés elküldve, várom a választ... "

#: src/http.c:910
msgid "End of file while parsing headers.\n"
msgstr "Állomány vége miközben a fejlécet olvasom.\n"

#: src/http.c:920
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Olvasási hiba (%s) a fejlécben.\n"

#: src/http.c:959
msgid "No data received"
msgstr "Nem érkezett adat"

#: src/http.c:961
msgid "Malformed status line"
msgstr "Rosszul formázott állapot vonal"

#: src/http.c:966
msgid "(no description)"
msgstr "(nincs leírás)"

#: src/http.c:1089
msgid "Authorization failed.\n"
msgstr "Azonosítás sikertelen.\n"

#: src/http.c:1096
msgid "Unknown authentication scheme.\n"
msgstr "Ismeretlen azonosítási módszer.\n"

#: src/http.c:1136
#, c-format
msgid "Location: %s%s\n"
msgstr "Hely: %s%s\n"

#: src/http.c:1137 src/http.c:1269
msgid "unspecified"
msgstr "nem megadott"

#: src/http.c:1138
msgid " [following]"
msgstr " [következik]"

#: src/http.c:1200
msgid "\n    The file is already fully retrieved; nothing to do.\n\n"
msgstr "\n    Az állomány már teljesen le van töltve; nincs mit csinájak.\n\n"

#: src/http.c:1216
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Folytatott letöltés nem sikerült ennél az állománynál, ami ellentmond `-c'-val.\n"
"Nem tördelem a létezõ `%s' állományt.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1259
msgid "Length: "
msgstr "Hossz: "

#: src/http.c:1264
#, c-format
msgid " (%s to go)"
msgstr " (még %s)"

#: src/http.c:1269
msgid "ignored"
msgstr "figyelmen kivül hagyva"

#: src/http.c:1399
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Figyelem: * és ? nem használható HTTP-nél.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1417
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "A `%s' állomány már létezik, nem töltöm le.\n"

#: src/http.c:1585
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Nem tudok írni `%s'-ba (%s).\n"

#: src/http.c:1602
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "HIBA: Átirányítás (%d) helyzet nélkül.\n"

#: src/http.c:1630
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s HIBA %d: %s.\n"

#: src/http.c:1642
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Utolsó módosított fejléc hiányzik -- idõbejegyzés kikapcsolva.\n"

#: src/http.c:1650
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Utolsó módosított fejléc helytelen -- idõbejegyzés figyelmen kivûl hagyva.\n"

#: src/http.c:1673
#, c-format
msgid "Server file no newer than local file `%s' -- not retrieving.\n\n"
msgstr "A szerveren lévõ `%s' állomány nem újabb mint a helyi -- nem töltöm le.\n\n"

#: src/http.c:1680
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "A méretek nem eggyeznek (helyi %ld) -- letöltöm.\n"

#: src/http.c:1684
msgid "Remote file is newer, retrieving.\n"
msgstr "Távoli állomány újabb, letöltöm.\n"

#: src/http.c:1728
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' lementve [%ld/%ld]\n\n"

#: src/http.c:1774
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Kapcsolat bezárva a %ld-ik bájtnál. "

#: src/http.c:1782
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' lementve [%ld/%ld])\n\n"

#: src/http.c:1801
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Kapcsolat bezárva a %ld/%ld-ik bájtnál. "

#: src/http.c:1812
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Olvasási hiba a %ld-ik bájtnál (%s). "

#: src/http.c:1820
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Olvasási hiba a %ld/%ld-ik bájtnál (%s). "

#: src/init.c:349 src/netrc.c:267
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Nem tudom olvasni %s-t (%s).\n"

#: src/init.c:367 src/init.c:373
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Hiba %s-ban a %d-ik sornál.\n"

#: src/init.c:405
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Figyelem: Mind a rendszer és a felhasználói wgetrc `%s'-re mutat.\n"

#: src/init.c:497
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: ismeretlen parancs `%s', érték `%s'.\n"

#: src/init.c:529
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: Nem tudom átalakítani `%s'-t IP címmé.\n"

#: src/init.c:559
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Kérem adja meg, hogy ki vagy bekapcsolva.\n"

#: src/init.c:603
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Kérem adja meg, hogy mindig, kikapcsolva, bekapcsolva vagy soha.\n"

#: src/init.c:622 src/init.c:919 src/init.c:941 src/init.c:1005
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Helytelen megadás `%s'.\n"

#: src/init.c:775 src/init.c:797 src/init.c:819 src/init.c:845
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Helytelen megadás `%s'\n"

#: src/main.c:120
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Használat: %s [OPCIÓK]... [URL]...\n"

#: src/main.c:128
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, egy nem-interaktív hálózati letöltõ.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:133
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nA hosszú opciók kötelezõ argumentumai kötelezõek a rövid opcióknak is.\n\n"

#: src/main.c:137
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Indítás:\n"
"  -V,  --version           kiírja a Wget verzióját és kilép.\n"
"  -h,  --help              kiírja ezt a segítséget.\n"
"  -b,  --background        indítás után háttérben fut.\n"
"  -e,  --execute=COMMAND   végrehajt egy `.wgetrc'-tipusú parancsot.\n"
"\n"

#: src/main.c:144
#,
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
"       --sslcertfile=FILE     optional client certificate.\n"
"       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n"
"\n"
msgstr ""
"Belépés és bemeneti állomány:\n"
"  -o,  --output-file=FILE     üzenetek rögzítése a FILE-ban.\n"
"  -a,  --append-output=FILE   üzenetek hozzáadása a FILE-hoz.\n"
"  -d,  --debug                hibakeresési kiírás.\n"
"  -q,  --quiet                csendes (nincs kimenet).\n"
"  -v,  --verbose              legyen részletes (alapértelmezett).\n"
"  -nv, --non-verbose          nem részletes anélkül, hogy csendes legyen.\n"
"  -i,  --input-file=FILE      az állományban talált címek letöltése.\n"
"  -F,  --force-html           a bemenetet kezelje HTML-ként.\n"
"  -B,  --base=URL             URL hozzáadása relatív linkeknél -F -i fájlban.\n"
"       --sslcertfile=FILE     opcionális kliens igazolás.\n"
"       --sslcertkey=KEYFILE   opcionális kulcs az igazoláshoz.\n"
"\n"

#: src/main.c:158
#,
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""
"Letöltés:\n"
"       --bind-address=ADDRESS   hozzárendelés ADDRESS címhez (hostnév vagy IP).\n"
"  -t,  --tries=NUMBER           a próbálkozások száma NUMBER (0 végtelen).\n"
"  -O   --output-document=FILE   dokumentum írása FILE-ba.\n"
"  -nc, --no-clobber             ne változtassa meg a létezõ állományokat vagy\n"
"                                használjon .# végzõdést.\n"
"  -c,  --continue               folytassa egy létezõ állomány letöltését.\n"
"       --dot-style=STYLE        letöltési kiírás stílusának beállítása.\n"
"  -N,  --timestamping           ne töltse az álloményokat ha régebbiek mint a\n"
"                                helyiek.\n"
"  -S,  --server-response        szerver válaszának kiírása.\n"
"       --spider                 ne töltsön le semmit.\n"
"  -T,  --timeout=SECONDS        olvasási idõhatár beállítása SECONDS másodperce.\n"
"  -w,  --wait=SECONDS           várjon SECONDS másodpercet a letöltések között.\n"
"       --waitretry=SECONDS      várjon 1...SECONDS másodpercet a próbálkozások\n"
"                                között.\n"
"  -Y,  --proxy=on/off           proxy ki- vagy bekapcsolása.\n"
"  -Q,  --quota=NUMBER           a probálkozások számát NUMBER-re állítja.\n"
"\n"

#: src/main.c:175
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Könyvtárak:\n"
"  -nd  --no-directories            ne hozzon létre könyvtárakat.\n"
"  -x,  --force-directories         eröltesse a könyvtárak létrehozását.\n"
"  -nH, --no-host-directories       ne hozzon létre könyvtárakat a host-oknak.\n"
"  -P,  --directory-prefix=PREFIX   mentse le az állományokat PREFIX/...-be\n"
"       --cut-dirsóNUMBER           figyelmen kívül hagyjon NUMBER db távoli\n"
"                                   könyvtár elemet.\n"
"\n"

#: src/main.c:183
#,
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
"\n"
msgstr ""
"HTTP opcók:\n"
"       --http-user=USER      http felhasználó USER.\n"
"       --http-passwd=PASS    http kód PASS.\n"
"  -C,  --cache=on/off        (nem)engedi a szerver cache-elt adatokat.\n"
"  -E,  --html-extension      minden text/html álloményt .html kiterjesztéssel\n"
"                             ment le.\n"
"       --ignore-length       figyelmen kívül hagyja a `Content-Length'-t.\n"
"       --header=STRING       beszúrja a STRING-t a fejlécbe.\n"
"       --proxy-user=USER     USER a felhasználói név a proxyhoz.\n"
"       --proxy-passwd=PASS   PASS a kód a proxyhoz.\n"
"       --referer=URL         beszúrja a `Referer: URL' fejlécet a HTTP kérésbe.\n"
"  -s,  --save-headers        a HTTP fejlécek mentése állományba.\n"
"  -U,  --user-agent=AGENT    azonosítsa magát AGENT-ként Wget/VERSION helyett.\n"
"       --no-http-keep-alive  HTTP keep-alive (maradandó kapcsolat) kikapcsolása.\n"
"       --cookies=off         ne használjon cookie-kat.\n"
"       --load-cookies=FILE   cookie-k betöltése FILE-ból munka elõtt.\n"
"       --save-cookies=FILE   cookie-k elmentése FILEüba munka után.\n"
"\n"

#: src/main.c:201
#,
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"FTP opciók:\n"
"  -nr, --dont-remove-listing   ne törölje le a `.listing' állományokat.\n"
"  -g,  --glob=on/off     állományok maszkolhatása ki/be..\n"
"       --passive-ftp     \"passive\" adatátviteli mód használata.\n"
"       --retr-symlinks   ha rekurzív, akkor töltse le a szimlinkelt\n"
"                         állományokat (nem könyvtárakat).\n"
"\n"

#: src/main.c:208
#,
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive          recursive web-suck -- use with care!\n"
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
"       --delete-after       delete files locally after downloading them.\n"
"  -k,  --convert-links      convert non-relative links to relative.\n"
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
"  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n"
"  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
"\n"
msgstr ""
"Rekurzív letöltés:\n"
"  -r,  --recursive             rekurz1v letöltés --  óvatosan használd!.\n"
"  -l,  --level=NUMBER          maximális rekurziós mélység (inf|0 végtelenért).\n"
"       --delete-after          törölje le az állományokat letöltés után.\n"
"  -k,  --convert-links         nem-relatív linkeket relatív linkekké alakítsa.\n"
"  -K,  --backup-converted      mielõtt az X állományt módosítja, mentse le\n"
"                               mint X.orig.\n"
"  -m,  --mirror                rövidítés a -r -N -l inf -nr opciókhoz.\n"
"  -p,  --page-requisites       töltse le az összes képet ami HTML állományok\n"
"                               megjelenítéséhez kell.\n"
"\n"

#: src/main.c:218
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
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                vesszõvel elválasztott lista az elfogatott\n"
"                                    kiterjesztésekrõl.\n"
"  -R,  --reject=LIST                vesszõvel elválasztott lista a \n"
"                                    visszautasított kiterjesztésekrõl.\n"
"  -D,  --domains=LIST               vesszõvel elválasztott lista az elfogadott\n"
"                                    domain-ekrõl.\n"
"       --exclude-domains=LIST       vesszõvel elválasztott lista a kizárt\n"
"                                    domain-ekrõl.\n"
"       --follow-ftp                 kövesse az FTP linkeket HTML dokumentumból.\n"
"       --follow-tags=LIST           vesszõvel elválasztott lista a követendõ\n"
"                                    HTML elemkrõl.\n"
"  -G,  --ignore-tags=LIST           vesszõvel elválasztott lista a nem\n"
"                                    követendõ HTML elemkrõl.\n"
"  -H,  --span-hosts                 menjen más szerverre mikor rekurzív.\n"
"  -L,  --relative                   relatív linkeket kövesse csak.\n"
"  -I,  --include-directories=LIST   lista a megengedett könyvtárakról.\n"
"  -X,  --exclude-directories=LIST   lista a megengedett könyvtárakról.\n"
"  -nh, --no-host-lookup             ne csináljon DNS-keresést a hosztokra.\n"
"  -np, --no-parent                  ne mélyedjen bele a szülõ könyvtárba.\n"
"\n"

#: src/main.c:234
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Küldjön BUG jelentést és ötleteket a <bug-wget@gnu.org> címre.\n"

#: src/main.c:420
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: debug kezelése nincs belefordítva.\n"

#: src/main.c:472
#,
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"Ez a program abban a reményben van terjesztve, hogy hasznos legyen,\n"
"de BÁRMIFÉLE GARANCIA NÉLKÜL; még az ÉRTÉKESÍTHETÕSÉG vagy MEGFELELÉS\n"
"EGY BIZONYOS CÉLNAK a garanciája nélkül. Nézd meg a \n"
"GNU General Public License-t bõvebb információért.\n"

#: src/main.c:478
msgid "\nOriginally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr "\nEredetileg írta Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:569
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: hibás parancs\n"

#: src/main.c:625
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: hibás opció -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:628 src/main.c:670 src/main.c:728
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Próbálja meg a `%s --help'-t több opcióért.\n"

#: src/main.c:708
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Nem lehetek részletes és csendes egyszerre.\n"

#: src/main.c:714
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Nem tudok idõbejegyzést is tenni egy fáljra és békén is hagyni.\n"

#. No URL specified.
#: src/main.c:723
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: hiányzó URL\n"

#: src/main.c:825
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Nem találtam URL-t %s-ban.\n"

#: src/main.c:834
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"BEFEJEZTEM --%s--\n"
"Letöltve: %s byte %d állományban\n"

#: src/main.c:842
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Letöltési határ (%s byte) TÚLLÉPVE!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:876
#, c-format
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s-t kaptam, kimenet átirányítása `%%s'-ba.\n"

#: src/mswindows.c:89
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break-t, kimenet átirányítása `%s'-ba.\n"
"A futás a háttérben folytatódik.\n"
"Leállíthatod a Wget-et lenyomva a CTRL+ALT+DELETE-t.\n"

#. parent, no error
#: src/mswindows.c:106 src/utils.c:458
msgid "Continuing in background.\n"
msgstr "Folytatás a háttérben.\n"

#: src/mswindows.c:108 src/utils.c:460
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "A kimenet a `%s' állományba írom.\n"

#: src/mswindows.c:188
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "WinHelp %s indítása\n"

#: src/mswindows.c:215 src/mswindows.c:222
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Nem találtam használható csatlakozó eszközkezelõt.\n"

#: src/netrc.c:367
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: figyelem: \"%s\" tokent találtam a gép neve elõtt\n"

#: src/netrc.c:398
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: ismeretlen token \"%s\"\n"

#: src/netrc.c:462
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Használat: %s NETRC [HOSTNAME]\n"

#: src/netrc.c:472
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: nem tudom megvizsgálni %s: %s\n"

#: src/recur.c:484
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Letörlöm %s-t mivel vissza kéne utasítani.\n"

#: src/recur.c:679
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "robots.txt letöltése; hagyja figyelmen kívül a hibákat.\n"

#: src/retr.c:227
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ kihagyva %dK ]"

#: src/retr.c:373
msgid "Could not find proxy host.\n"
msgstr "Nem találom a proxy címét.\n"

#: src/retr.c:387
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: HTTP kell legyen.\n"

#: src/retr.c:481
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Ciklikus átirányítás.\n"

#: src/retr.c:587
msgid "Giving up.\n\n"
msgstr "Feladom.\n\n"

#: src/retr.c:587
msgid "Retrying.\n\n"
msgstr "Újrapróbálom.\n\n"

#: src/url.c:1329
#, c-format
msgid "Converting %s... "
msgstr "%s átalakítása... "

#: src/url.c:1342
msgid "nothing to do.\n"
msgstr "nincs mit csinálni.\n"

#: src/url.c:1350 src/url.c:1374
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Nem tudom átalakítani a linket %s-ben: %s\n"

#: src/url.c:1365
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Sikertelen a `%s' törlése: %s\n"

#: src/url.c:1555
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Nem tudom lementeni %s-t mint %s: %s\n"

#: src/utils.c:94
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Nincs elég memória.\n"

#: src/utils.c:417
msgid "Unknown/unsupported protocol"
msgstr "Ismeretlen/nemkezelt protokoll"

#: src/utils.c:420
msgid "Invalid port specification"
msgstr "Helytelen port megadás"

#: src/utils.c:423
msgid "Invalid host name"
msgstr "Helytelen hoszt név"

#: src/utils.c:620
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Sikertelen a `%s' szimlink törlése: %s\n"

#~ msgid "%s: Cannot determine user-id.\n"
#~ msgstr "%s: Nem tudom meghatározni a felhasználó azonosítóját.\n"

#~ msgid "%s: Warning: uname failed: %s\n"
#~ msgstr "%s: Figyelem: uname sikertelen: %s\n"

#~ msgid "%s: Warning: gethostname failed\n"
#~ msgstr "%s: Figyelem: gethostname sikertelen\n"

#~ msgid "%s: Warning: cannot determine local IP address.\n"
#~ msgstr "%s: Figyelem: nem tudom meghatározni a helyi IP címet.\n"

#~ msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
#~ msgstr "%s: Figyelem: nem tudom visszakeresni a helyi IP címet.\n"

#~ msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
#~ msgstr "%s: Figyelem: a helyi cím visszakeresése nem vezetett FQDN-re!\n"

#~ msgid "%s: Out of memory.\n"
#~ msgstr "%s: Nincs memória.\n"

#~ msgid "%s: Redirection to itself.\n"
#~ msgstr "%s: Önmagába átirányítás.\n"

#~ msgid "Error (%s): Link %s without a base provided.\n"
#~ msgstr "Hiba (%s): Link %s alapcím nálkül.\n"

#~ msgid "Error (%s): Base %s relative, without referer URL.\n"
#~ msgstr "Hiba (%s): Alap %s relatív, utaló URL nélkül.\n"
