# Translation of wget messages to Catalan.
# Copyright (C) 2001, 2002 Free Software Foundation, Inc.
# Jordi Valverde Sivilla <jordi@eclipsi.net>, 2001, 2002.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.8\n"
"POT-Creation-Date: 2001-12-08 23:28+0100\n"
"PO-Revision-Date: 2002-01-13 21:29+0100\n"
"Last-Translator: Jordi Valverde Sivilla <jordi@eclipsi.net>\n"
"Language-Team: Catalan <ca@dodds.net>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-1\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/connect.c:94
#, c-format
msgid "Connecting to %s[%s]:%hu... "
msgstr "Conectant a %s[%s]:%hu... "

#: src/connect.c:97
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Conectant a %s:%hu... "

#: src/connect.c:131
msgid "connected.\n"
msgstr "conectat.\n"

#: src/cookies.c:595
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Error al fixar a la secció de la cookie `%s'"

#: src/cookies.c:619
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Error de sintaxi al fixar la cookie al caracter `%c'.\n"

#: src/cookies.c:627
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Error de sintaxi al fixar la cookie: final inesperat.\n"

#: src/cookies.c:1329
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "No es pot obrir el arxiu de cookies `%s': %s\n"

#: src/cookies.c:1341
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Error d'escriptura a `%s': %s\n"

#: src/cookies.c:1345
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Error tancant `%s': %s\n"

#: src/ftp-ls.c:787
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "tipus de llistat no soportat, intentant fent servir el parsejador de Unix.\n"

#: src/ftp-ls.c:832 src/ftp-ls.c:834
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Índex de /%s a %s:%d"

#: src/ftp-ls.c:856
msgid "time unknown       "
msgstr "temps desconegut       "

#: src/ftp-ls.c:860
msgid "File        "
msgstr "Arxiu         "

#: src/ftp-ls.c:863
msgid "Directory   "
msgstr "Directori   "

#: src/ftp-ls.c:866
msgid "Link        "
msgstr "Enllaç        "

#: src/ftp-ls.c:869
msgid "Not sure    "
msgstr "No segur    "

#: src/ftp-ls.c:887
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:179
#, c-format
msgid "Logging in as %s ... "
msgstr "entrant com a %s ... "

#: src/ftp.c:188 src/ftp.c:241 src/ftp.c:272 src/ftp.c:326 src/ftp.c:419
#: src/ftp.c:470 src/ftp.c:500 src/ftp.c:564 src/ftp.c:628 src/ftp.c:689
#: src/ftp.c:737
msgid "Error in server response, closing control connection.\n"
msgstr "Error en el servidor, tancant la conexió de control.\n"

#: src/ftp.c:196
msgid "Error in server greeting.\n"
msgstr "Error en la benvinguda del servidor.\n"

#: src/ftp.c:204 src/ftp.c:335 src/ftp.c:428 src/ftp.c:509 src/ftp.c:574
#: src/ftp.c:638 src/ftp.c:699 src/ftp.c:747
msgid "Write failed, closing control connection.\n"
msgstr "Escritura fallada, tancant la conexió de control.\n"

#: src/ftp.c:211
msgid "The server refuses login.\n"
msgstr "El servidor refusa la entrada.\n"

#: src/ftp.c:218
msgid "Login incorrect.\n"
msgstr "entrada incorrecte.\n"

#: src/ftp.c:225
msgid "Logged in!\n"
msgstr "entrada aconseguida!\n"

#: src/ftp.c:250
msgid "Server error, can't determine system type.\n"
msgstr "Error de servidor, no es pot determinar el tipus de sistema.\n"

#: src/ftp.c:260 src/ftp.c:549 src/ftp.c:612 src/ftp.c:669
msgid "done.    "
msgstr "fet.    "

#: src/ftp.c:314 src/ftp.c:449 src/ftp.c:484 src/ftp.c:720 src/ftp.c:768
#: src/host.c:280
msgid "done.\n"
msgstr "fet.\n"

#: src/ftp.c:343
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tipus desconegut `%c', tancant la conexió de control.\n"

#: src/ftp.c:356
msgid "done.  "
msgstr "fet.  "

#: src/ftp.c:362
msgid "==> CWD not needed.\n"
msgstr "==> CWD no necessari.\n"

#: src/ftp.c:435
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "No existeix el directori `%s'.\n\n"

#. do not CWD
#: src/ftp.c:453
msgid "==> CWD not required.\n"
msgstr "==> CWD no requerit.\n"

#: src/ftp.c:516
msgid "Cannot initiate PASV transfer.\n"
msgstr "No es pot iniciar la transferéncia en PASV.\n"

#: src/ftp.c:520
msgid "Cannot parse PASV response.\n"
msgstr "No es pot parsejar la resposta en PASV.\n"

#: src/ftp.c:541
#, c-format
msgid "couldn't connect to %s:%hu: %s\n"
msgstr "no es pot conectar a `%s:%hu: %s\n"

#: src/ftp.c:591
#, c-format
msgid "Bind error (%s).\n"
msgstr "Error a la trucada `bind' (%s).\n"

#: src/ftp.c:598
msgid "Invalid PORT.\n"
msgstr "PORT incorrecte.\n"

#: src/ftp.c:651
#, c-format
msgid "\nREST failed; will not truncate `%s'.\n"
msgstr "\nREST fallat; no es truncarà `%s'.\n"

#: src/ftp.c:658
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST ha fallat, començant des del inici.\n"

#: src/ftp.c:707
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "No existeix el arxiu `%s'.\n\n"

#: src/ftp.c:755
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "No existeix el arxiu o directori `%s'.\n\n"

#: src/ftp.c:839 src/ftp.c:847
#, c-format
msgid "Length: %s"
msgstr "Longitut: %s"

#: src/ftp.c:841 src/ftp.c:849
#, c-format
msgid " [%s to go]"
msgstr " [%s per acabar]"

#: src/ftp.c:851
msgid " (unauthoritative)\n"
msgstr " (probablement)\n"

#: src/ftp.c:877
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, tancant la conexió de control.\n"

#: src/ftp.c:885
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s)   Conexió de dades: %s; "

#: src/ftp.c:902
msgid "Control connection closed.\n"
msgstr "Conexió de control tancada.\n"

#: src/ftp.c:920
msgid "Data transfer aborted.\n"
msgstr "Transferéncia de dades cancel·lada.\n"

#: src/ftp.c:984
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "L'arxiu `%s' ja existeix, no es descarregarà.\n"

#: src/ftp.c:1054 src/http.c:1527
#, c-format
msgid "(try:%2d)"
msgstr "(prova:%2d)"

#: src/ftp.c:1118 src/http.c:1786
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s)   `%s guardat [%ld]\n\n"

#: src/ftp.c:1160 src/main.c:822 src/recur.c:349 src/retr.c:587
#, c-format
msgid "Removing %s.\n"
msgstr "Esborrant %s.\n"

#: src/ftp.c:1202
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Utilitzant `%s' com a un arxiu de llistat temporal.\n"

#: src/ftp.c:1217
#, c-format
msgid "Removed `%s'.\n"
msgstr "Esborrat `%s'.\n"

#: src/ftp.c:1252
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "La profunditat de recursió %d excedeix el màxim permés %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1317
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "L'arxiu remot no és més nou que l'arxiu local `%s' -- no es descarrega.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1324
#, c-format
msgid "Remote file is newer than local file `%s' -- retrieving.\n\n"
msgstr "L'arxiu remot és més nou que l'arxiu local `%s' -- descarregant.\n\n"

#. Sizes do not match
#: src/ftp.c:1331
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n\n"
msgstr "Els tamanys no corresponen (local %ld) -- descarregant.\n"

#: src/ftp.c:1348
msgid "Invalid name of the symlink, skipping.\n"
msgstr "El nom del enllaç és incorrecte; omitint.\n"

#: src/ftp.c:1365
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Ja té el enllaç correcte %s --> %s\n\n"

#: src/ftp.c:1373
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creant enllaç %s --> %s\n"

#: src/ftp.c:1384
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Els enllaços no estan suportats, omitint enllaç `%s'.\n"

#: src/ftp.c:1396
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "omitint directori `%s'.\n"

#: src/ftp.c:1405
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tipus d'arxiu desconegut/no soportat.\n"

#: src/ftp.c:1432
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: marca de temps corrupte.\n"

#: src/ftp.c:1457
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "No es descarregaran els directoris perquè la profunditat es %d (màx %d).\n"

#: src/ftp.c:1507
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Es descén fins a `%s' per estar exclós/no inclós.\n"

#: src/ftp.c:1561
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rebutjant `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1608
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "No hi ha res que s'ajusti al patró `%s'.\n"

#: src/ftp.c:1673
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "S'ha escrit un índex amb HTML a `%s' [%ld].\n"

#: src/ftp.c:1678
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "S'ha escrit un índex HTML a `%s'.\n"

#: src/gen_sslfunc.c:109
msgid "Could not seed OpenSSL PRNG; disabling SSL.\n"
msgstr "No es s'ha pogut alimentar el PRNG d'OpenSSL; deshabilitant SSL.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: la opció `%s' és ambigua\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: la opció `--%s' no permet un argument\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: la opció `%c%s' no permet un argument\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: la opció `%s' requereix un argument\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opció desconeguda `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opció desconeguda `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opció no permesa -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: aquesta opció requereix un argument -- %c\n"

#: src/host.c:268
#, c-format
msgid "Resolving %s... "
msgstr "Resolent %s... "

#: src/host.c:275
#, c-format
msgid "failed: %s.\n"
msgstr "Fallat: %s.\n"

#: src/host.c:345
msgid "Host not found"
msgstr "Oste no trobat"

#: src/host.c:347
msgid "Unknown error"
msgstr "Error desconegut"

#. this is fatal
#: src/http.c:573
msgid "Failed to set up an SSL context\n"
msgstr "S'ha fallat al intentar fixar un context SSL\n"

#: src/http.c:579
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "S'ha fallat al intentar carregar els certificats des de %s\n"

#: src/http.c:583 src/http.c:591
msgid "Trying without the specified certificate\n"
msgstr "Probant sense el certificat especificat\n"

#: src/http.c:587
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "S'ha fallat al intentar conseguir la clau del certificat des de %s\n"

#: src/http.c:657 src/http.c:1620
msgid "Unable to establish SSL connection.\n"
msgstr "No es pot establir una conexió SSL.\n"

#: src/http.c:666
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "S'està reutilitzant la conexió a %s:%hu.\n"

#: src/http.c:868
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Ha fallat al escriure la petició HTTP: %s.\n"

#: src/http.c:873
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s: Petició enviada, esperant resposta... "

#: src/http.c:917
msgid "End of file while parsing headers.\n"
msgstr "Fi del arxiu al parsejar les capçaleres.\n"

#: src/http.c:927
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Error de lectura (%s) a les capçaleres.\n"

#: src/http.c:962
msgid "No data received"
msgstr "No s'han rebut dades"

#: src/http.c:964
msgid "Malformed status line"
msgstr "línia de estat mal formada"

#: src/http.c:969
msgid "(no description)"
msgstr "(sense descripció)"

#: src/http.c:1101
msgid "Authorization failed.\n"
msgstr "Autorització fallida.\n"

#: src/http.c:1108
msgid "Unknown authentication scheme.\n"
msgstr "Métode de autentificació desconeguda.\n"

#: src/http.c:1148
#, c-format
msgid "Location: %s%s\n"
msgstr "Localització: %s%s\n"

#: src/http.c:1149 src/http.c:1282
msgid "unspecified"
msgstr "no especificat"

#: src/http.c:1150
msgid " [following]"
msgstr " [el següent]"

#: src/http.c:1213
msgid "\n    The file is already fully retrieved; nothing to do.\n\n"
msgstr "\n    L'arxiu següent està descarregat totalment; res a fer.\n\n"

#: src/http.c:1229
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"La descàrrega continuada ha fallat en aquest arxiu, que dóna conflictes amb `-c'.\n"
"No es truncarà l'arxiu existent `%s'.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1272
msgid "Length: "
msgstr "Longitud:"

#: src/http.c:1277
#, c-format
msgid " (%s to go)"
msgstr " (%s per acabar)"

#: src/http.c:1282
msgid "ignored"
msgstr "ignorat"

#: src/http.c:1413
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Perill: Les wildcards no estan suportades en HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1443
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "L'arxiu `%s' ja esta aquí, no es descarregarà.\n"

#: src/http.c:1611
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "No es pot escriure a '%s' (%s).\n"

#: src/http.c:1630
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERROR: La redirecció (%d) sense localització.\n"

#: src/http.c:1662
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERROR %d %s.\n"

#: src/http.c:1675
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "La capçalera d'arxiu modificat no hi es --- Timestamp parada.\n"

#: src/http.c:1683
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "L'últim modificador és incorrecte -- time stamp ignorada.\n"

#: src/http.c:1706
#, c-format
msgid "Server file no newer than local file `%s' -- not retrieving.\n\n"
msgstr "L'arxiu remot no és més nou que el local `%s' -- no es descarregarà.\n"

#: src/http.c:1714
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Els tamanys no són iguals (local %ld) -- descarregant.\n"

#: src/http.c:1718
msgid "Remote file is newer, retrieving.\n"
msgstr "L'arxiu remot és més nou, descarregant.\n"

#: src/http.c:1759
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' guardat [%ld/%ld]\n"

#: src/http.c:1809
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) -- Conexió tancada al byte %ld. "

#: src/http.c:1818
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' guardat [%ld/%ld]\n\n"

#: src/http.c:1839
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Conexió tancada al byte %ld/%ld. "

#: src/http.c:1851
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Error de lectura al byte %ld (%s)."

#: src/http.c:1860
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Error de lectura al byte %ld/%ld (%s)."

#: src/init.c:354 src/netrc.c:265
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: No s'ha pogut llegi %s (%s).\n"

#: src/init.c:372 src/init.c:378
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Error de %s a la linia %d.\n"

#: src/init.c:410
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Perill: El wgetrc del sistema i del usuari apunten a `%s'.\n"

#: src/init.c:502
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: ordre desconeguda `%s', valor `%s'.\n"

#: src/init.c:536
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: No es pot convertir `%s' a una adreça IP.\n"

#: src/init.c:569
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Sius-plau especifica on o off.\n"

#: src/init.c:613
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Sius-plau especifica sempre, on, off o nerver.\n"

#: src/init.c:632 src/init.c:899 src/init.c:978
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Especificació incorrecte `%s'.\n"

#: src/init.c:788 src/init.c:810 src/init.c:832 src/init.c:858
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Especificació incorrecte `%s'\n"

#: src/init.c:949
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Tipus de progrés incorrecte `%s'.\n"

#: src/main.c:116
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Ús: %s [OPTION]... [URL]...\n"

#: src/main.c:124
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, un descarregador de la xarxa no interactiu.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:129
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nEls arguments obligatoris de les opcions més llargues són obligatoris per les opcions curtes també.\n\n"

#: src/main.c:133
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Inici:\n"
" -V, --version            Mostra la versió del Wget i surt.\n"
" -h, --help                 Mostra aquesta ajuda.\n"
" -b, --background      va al fons després del inici.\n"
" -e, --execute=ORDRE  executa una ordre del estil del `wgetrc'.\n"
"\n"

#: src/main.c:140
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
"       --egd-file=FILE        file name of the EGD socket.\n"
"\n"
msgstr ""
"Log i arxius d'entrada:\n"
"  -o,  --output-file=ARXIU                        logueja els missatges a un ARXIU.\n"
"  -a,  --append-output=ARXIU                 afegeix els missatges a un ARXIU.\n"
"  -d,  --debug                                           escriu a pantalla el depurat.\n"
"  -q,  --quiet                                              mode silenciós (no mostra cap sortida).\n"
"  -v,  --verbose                                        mode informatiu (això és per defecte).\n"
"  -nv, --non-verbose                                apaga l'informació que surt a pantalla.\n"
"   -i,  --input-file=ARXIU                          descarrega les URL trobades a un ARXIU.\n"
"  -F,  --force-html                                    tracta l'arxiu com a HTML.\n"
"  -B,  --base=URL                                   afegeix un URL davant dels enllaços relatius en l'arxiu -F -i.\n"
"        --ssicertfile=ARXIU                        certificat del client opcional.\n"
"        --ssicertkey=ARXIUCLAU              Arxiu-clau per aquest certificat.\n"
"        --egd-file=ARXIU                            nom del arxiu del socket EGD.\n"
"\n"

#: src/main.c:155
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --progress=TYPE          select progress gauge type.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"       --random-wait            wait from 0...2*WAIT secs between retrievals.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"       --limit-rate=RATE        limit download rate to RATE.\n"
"\n"
msgstr ""
"Descàrrega:\n"
"               --bind-address=ADREÇA      fa un bind a l'adreça (oste o IP) en l'oste local.\n"
"  -t,     --tries=NÚMERO                        fixa el número de reintents (0=sense limit).\n"
"  -O,   --output-document=ARXIU          escriu els documents a un ARXIU.\n"
"  -nc,  --no-clobber                                 no sobreescriu els arxius existents. O no utilitzar sufixos.\n"
"  -c,   -­continue                                    Continua una descàrrega interrompuda.\n"
"        --progress=TIPUS                       Selecciona el tipus de mesura de descàrrega.\n"
"  -N,  --timestamping                             No descarrega de nou els arxius fins que no són més nous que\n"
"                                                            els locals.\n"
"  -S,  --server-response                         Escriu a pantalla les respostes del servidor.\n"
"        --spider                                         No descarrega res.\n"
"   -T,  --timeout=SEGONS                      fixa la lectura de temps en SEGONS.\n"
"  -w,  --wait=SEGONS                           espera SEGONS entre les descàrregues.\n"
"           --waitrery=SEGONS                  espra 1...SEGONS entre els intents de descàrrega.\n"
"  -Y,  --proxy=on/off                              Apaga o engega el proxy.\n"
"  -Q,  --quota=NÚMERO                       fixa la quota de descàrrega a un NÚMERO.\n"
"         --limit-rate=PERCENTATGE       limita el percentatge de descàrrega a un PERCENTATGE.\n"
"\n"

#: src/main.c:174
msgid ""
"Directories:\n"
"  -nd  --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Directoris:\n"
"  -nd,     --no-directories                     no crea els directoris.\n"
"  -x,     --force-directories                   força la creació dels directoris.\n"
"  -nH,  --no-host-directories                no crea directoris al oste.\n"
"  -P,    --directory-prefix=PREFIX        guarda els arxius a un PREFIX/...\n"
"          --cut-dirs=NÚMERO                 talla els directoris a guardar.\n"
"\n"

#: src/main.c:182
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
"Opcions de HTTP:\n"
"          --http-user=USUARI            fixa el usuari de HTTP.\n"
"          --http-passwd=PASS           fixa la contrassenya d'usuari.\n"
"  -C,   --cache=on/off                     apaga o engega la caché d'arxius   -E,   --html-extension                   guarda tots els documents sota una extensió .html.\n"
"         --ignore-length                     ignora la longitut de la capçalera.\n"
"         --header=STRING               inserta una cadena entre les capçaleres.\n"
"         --proxy-user=USUARI          fixa el usuari de proxy.\n"
"         --proxy-passwd=pass           fixa la contrasenya del proxy.\n"
"         --referer=URL                      inclou la capçalera 'referer' a la petició HTTP.\n"
"  -s,   --save-headers                     guarda les capçaleres HTTP a un arxiu.\n"
"  -U,  --user-agent=AGENT            identifica com un AGENT en lloc de Wget/VERSION.\n"
"        --no-http-keep-alive               desactiva les conexions permanents de HTTP.\n"
"        --cookies=off                         desactiva les cookies.\n"
"        --load cookies=ARXIU           carrega les cookies d'un ARXIU abans de començar la sessió.\n"
"        --save-cookies=ARXIU           guarda les cookies a un ARXIU després de la sessió.\n"
"\n"

#: src/main.c:200
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"Opcions FTP:\n"
"   --nr,  --dont-remove-listing          no elimina els arxius 'listing'.\n"
"   -g,   --glob=on/off                       habilita o activa el us de comodins als arxius.\n"
"         --passive-ftp                         activa el ftp passiu.\n"
"        --retr-symlinks                       quan hi ha recursio recupera els arxius que apunten als directoris\n"
"                                                     (no els directoris).\n"
"\n"

#: src/main.c:207
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
"Descarrega recursiva:\n"
"  -r,    --recursive                descàrrega recursiva de la web -- usar amb compte!\n"
"  -l,     --level=NUMBER      màxim nivell de recursió (inf o 0 per infinit).\n"
"         --delete-after             borrar els arxius després d'haver-los descarregat.\n"
"  -k,   --convert-links            converteix els enllaços no relatius a enllaços relatius.\n"
"  -K,  --backup-converted    abans de convertir un arxiu X, fa un backup que es dirà X.orig.\n"
"  -m,  --mirror                      opció equivalent a -r -N -l inf -nr.\n"
"  -p,  --page-requisites        descarrega totes les imatges, etc, necessàries per veure el\n"
"                                          HTML correctament.\n"
"\n"

#: src/main.c:217
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
"Recuperació recursiva accept/reject:\n"
"  -A,  --accept=LLISTA                            llista separada per comes de lo que s'accepta.\n"
"  -R,   --reject=LLISTA                              llista separada per comes de lo que no s'accepta.\n"
"  -D,   --domains=LLISTA                          llista dels dominis separada per comes que s'accepta.\n"
"         --exclude-domains=LLISTA             llista dels dominis separada per comes que no s'accepta.\n"
"         --follow-ftp                                      segueix els enllaços FTP dels documents HTML.\n"
"        --follow-tags=LLISTA                       llista de tags que s'accepten per seguir.\n"
"  -G,  --ignore-tags=LLISTA                     llista de tags separat per coma que s'ignoren.\n"
"  -H,  --span-hosts                                    anar a hosts diferents a la hora de la recursió.\n"
"  --L,  --relative                                         segueix només els enllaços relatius.\n"
"  -I,   --include-directories=LLISTA           llista dels directoris permesos.\n"
"  -X,  --exclude-directories=LLISTA          llista de directoris a excloure.\n"
"  -np,  --no-parent                                    no puja al directori pare.\n"
"\n"

#: src/main.c:232
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Envia els teus reports de bugs a <bug-wget@gnu.org>.\n"

#: src/main.c:420
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: informació de depurat no compilada.\n"

#: src/main.c:472
msgid "Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.\n"
msgstr "Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001 Free Software Foundation, inc.\n"

#: src/main.c:474
msgid ""
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Aquest programa es distribueix amb l'esperança de que serà útil,\n"
"però SENSE CAP TIPUS DE GARANTIA; fins i tot sense la garantia implicita\n"
"de Comercialitat o idoneitat per el fi determinat. Veure la llicència publica de GNU per més detalls.\n"

#: src/main.c:479
msgid "\nOriginally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr "\nOriginàriament escrit per Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:578
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: ordre incorrecte\n"

#: src/main.c:631
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opció desconeguda  -- `n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:634 src/main.c:676 src/main.c:727
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Prova `%s --help' per més opcions.\n"

#: src/main.c:707
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "No es pot oferir informació i estar silenciós al mateix temps.\n"

#: src/main.c:713
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "No es poden utilitzar marques de temps i no sobreescriure arxius al mateix temps.\n"

#. No URL specified.
#: src/main.c:722
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL perduda\n"

#: src/main.c:837
#, c-format
msgid "No URLs found in %s.\n"
msgstr "No s'han trobat URLs a %s.\n"

#: src/main.c:846
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"ACABAT  --%s--\n"
"S'han descarregat: %s bytes en %d arxius\n"

#: src/main.c:854
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "La quota de descàrrega de (%s bytes) HA SIGUT EXCEDIDA!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:896
#, c-format
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s s'ha rebut, redireccionant sortida a `%%s'.\n"

#: src/mswindows.c:106
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break rebut, redireccionant sortida a `%s'.\n"
"Execució continuada en segón pla.\n"
"Pot apagar la execució de Wget apretant CTRL+ALT+SUPR.\n"

#. parent, no error
#: src/mswindows.c:123 src/utils.c:467
msgid "Continuing in background.\n"
msgstr "Continuant en segón pla.\n"

#: src/mswindows.c:125 src/utils.c:469
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "La sortida serà escrita a `%s'.\n"

#: src/mswindows.c:205
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Engegant WinHelp %s\n"

#: src/mswindows.c:232 src/mswindows.c:239
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: No s'ha trobat un controlador de socket.\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d perill: no apareix cap nom de màquina després de \"%s\".\n"

#: src/netrc.c:396
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s%d: Símbol desconegut \"%s\"\n"

#: src/netrc.c:460
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Ús: %s NETRC [HOSTNAME]\n"

#: src/netrc.c:470
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: no s'ha pogut executar `stat' en aquesta ordre %s: %s\n"

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:224
#, c-format
msgid "\n%*s[ skipping %dK ]"
msgstr "\n%*s [ ignorant %dK ]"

#: src/progress.c:391
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Especificació incorrecte del estil de dot `%s'; deixant-ho sense canviar.\n"

#: src/recur.c:350
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Borrant %s fins que sigui rebutjat.\n"

#: src/recur.c:916
#, c-format
msgid "Converted %d files in %.2f seconds.\n"
msgstr "Convertits %d arxius en %.2f segons.\n"

#: src/res.c:541
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Carregant robots.txt; sius-plau ignoreu els errors.\n"

#: src/retr.c:363
msgid "Could not find proxy host.\n"
msgstr "No s'ha trobat l'oste del proxy.\n"

#: src/retr.c:375
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Error parsejant la URL %s:%s.\n"

#: src/retr.c:384
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Error en la URL del proxy %s: ha de ser HTTP.\n"

#: src/retr.c:476
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d redireccions excedides.\n"

#: src/retr.c:491
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Cicle de redireccions detectada.\n"

#: src/retr.c:608
msgid "Giving up.\n\n"
msgstr "Donant per vençut.\n\n"

#: src/retr.c:608
msgid "Retrying.\n\n"
msgstr "Descarregant.\n\n"

#: src/url.c:1748
#, c-format
msgid "Converting %s... "
msgstr "Convertint %s... "

#: src/url.c:1761
msgid "nothing to do.\n"
msgstr "Res a fer.\n"

#: src/url.c:1769 src/url.c:1793
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "No es poden convertir els enllaços a %s: %s\n"

#: src/url.c:1784
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "No es pot borrar `%s': %s\n"

#: src/url.c:1990
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "No es pot guardar cópia de seguretat %s com %s: %s\n"

#: src/utils.c:102
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: No hi ha memória suficient.\n"

#: src/utils.c:667
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "S'ha fallat a la hora de trencar el enllaç simbolic `%s': %s\n"
