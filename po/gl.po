# Galician translation of wget
# Copyright (C) 2000 Free Software Foundation, Inc.
# Jacobo Tarrío Barreiro <jtarrio@iname.com>, 2000.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 2000-05-30 17:52+02:00\n"
"Last-Translator: Jacobo Tarrío Barreiro <jtarrio@iname.com>\n"
"Language-Team: Galician <gpul-traduccion@ceu.fi.udc.es>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=iso-8859-1\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Conectando con %s:%hu... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "A conexión a %s:%hu foi rexeitada.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "¡conectado!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Identificándome coma %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Erro na resposta do servidor, pechando a conexión de control.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Erro no saúdo do servidor.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Erro escribindo, pechando a conexión de control.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "O servidor rexeita o login.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Login incorrecto.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "¡Conectado!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tipo `%c' descoñecido, pechando a conexión de control.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "feito.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD non foi necesario.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Non existe tal ficheiro ou directorio `%s'.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "feito.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD non foi preciso.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Non puiden comeza-la transferencia PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Non se pode entende-la resposta PASV.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Tentarase conectar con %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "feito.   "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Erro facendo bind (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "PORT incorrecto.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST fallou, comezando dende o principio.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Non hai tal ficheiro `%s'.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Non hai tal ficheiro ou directorio `%s'.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Lonxitude: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s para rematar]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (dato non fidedigno)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, pechando a conexión de control.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Conexión de datos: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Conexión de control pechada.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Transferencia de datos abortada.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "O ficheiro `%s' xa está aí, non se ha descargar.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(intento:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' gardado [%ld]\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Usando `%s' coma un ficheiro temporal de listado.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Borrado `%s'.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "A profundidade de recursión %d excedeu a máxima %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "O ficheiro local `%s' é máis recente, non se ha descargar.\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Os tamaños non coinciden (local %ld), descargando.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "O nome da ligazón simbólica é incorrecto, omitindo.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Xa ten unha ligazón simbólica correcta %s -> %s\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creando a ligazón simbólica %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Ligazóns simbólicas non soportadas, omitindo `%s'.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Omitindo o directorio `%s'.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tipo de ficheiro descoñecido ou non soportado.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: data e hora corrompidas.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Non hei descargar directorios, porque a profundidade chegou a %d (máximo %d).\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Non descendo a %s' porque está excluído ou non incluído.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rexeitando `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Non encaixa no patron `%s'.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Escrito un índice en HTML en `%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Escrito un índice en HTML en `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: a opción `%s' é ambigua\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: a opción `--%s' non admite argumentos\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: a opción `%c%s' non admite argumentos\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: a opción `%s' precisa dun argumento\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opción descoñecida `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opción descoñecida `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opción incorrecta -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: a opción precisa dun argumento -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Non se pode determina-lo identificador de usuario.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Advertencia: a chamada a uname fallou: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Advertencia: a chamada a gethostname fallou\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Advertencia: non se pode determina-lo enderezo IP local.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Aviso: non se pode facer unha resolución inversa da IP local.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Aviso: a resolución inversa do enderezo local non devolveu un FQDN\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Servidor non atopado"

#: src/host.c:541
msgid "Unknown error"
msgstr "Erro descoñecido"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Índice de /%s en %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "data descoñecida   "

#: src/html.c:467
msgid "File        "
msgstr "Ficheiro    "

#: src/html.c:470
msgid "Directory   "
msgstr "Directorio  "

#: src/html.c:473
msgid "Link        "
msgstr "Ligazón     "

#: src/html.c:476
msgid "Not sure    "
msgstr "Non seguro  "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Fallo ao escribir unha petición HTTP.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "Petición %s enviada, agardando unha resposta... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Fin de ficheiro mentres se analizaban as cabeceiras.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Erro ao ler (%s) nas cabeceiras.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Non se recibiron datos"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Liña de estado mal formada"

#: src/http.c:594
msgid "(no description)"
msgstr "(sen descripción)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Fallo na autorización.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Sistema de autenticación descoñecido.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Lugar: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "non especificado"

#: src/http.c:750
msgid " [following]"
msgstr " [seguindo]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Lonxitude: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s para rematar)"

#: src/http.c:774
msgid "ignored"
msgstr "ignorado"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Aviso: comodíns non soportados en HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "O ficheiro `%s' xa está aí, non ha ser descargado.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Non se pode escribir en `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERROR: Redirección (%d) sen destino.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERRO %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Falta a cabeceira Last-modified -- marcas de data e hora desactivadas.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Cabeceira Last-modified incorrecta -- a marca de data e hora foi ignorada.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "O ficheiro remoto é máis novo, descargando.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' gardado [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Conexión pechada no byte %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' gardado [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Conexión pechada no byte %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Erro de lectura no byte %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Erro de lectura no byte %ld/%ld (%s). "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Non se pode ler %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Erro en %s na liña %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Aviso: Os ficheiros wgetrc do sistema e do usuario apuntan a `%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: comando descoñecido `%s', valor `%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Por favor, especifique `on' ou `off'.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Especificación `%s' non válida.\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Especificación `%s' non válida\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Uso: %s [OPCIÓN]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, un descargador de ficheiros de rede non interactivo.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nOs argumentos obrigatorios nas opcións largas sono tamén nas curtas.\n\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"Comezo:\n"
"  -V,  --version           amosa a versión de Wget e sae.\n"
"  -h,  --help              amosa esta axuda.\n"
"  -b,  --background        deixa o proceso en segundo plano.\n"
"  -e,  --execute=COMANDO   executa un comando de `.wgetrc'.\n"
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
"Rexistro e ficheiro de entrada:\n"
"  -o,  --output-file=FICHEIRO   garda-lo rexistro de mensaxes no FICHEIRO.\n"
"  -a,  --append-output=FICHEIRO engadir mensaxes ao FICHEIRO.\n"
"  -d,  --debug                  amosar información de depuración.\n"
"  -q,  --quiet                  en silencio (sen mensaxes).\n"
"  -v,  --verbose                moi falador (esta é a opción por defecto).\n"
"  -nv, --non-verbose            non moi falador, sen estar en silencio.\n"
"  -i,  --input-file=FICHEIRO    le-las URLs dende o FICHEIRO.\n"
"  -F,  --force-html             trata-lo ficheiro de entrada coma HTML.\n"
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
"Baixar ficheiros:\n"
"  -t,  --tries=NÚMERO             estabrece-lo número de intentos a NÚMERO\n"
"                                        (0 é sen límite).\n"
"  -O   --output-document=FICHEIRO escribi-los documentos ao FICHEIRO.\n"
"  -nc, --no-clobber               non esmaga-los ficheiros que xa existan.\n"
"  -c,  --continue                 seguir descargando un ficheiro que xa exista.\n"
"       --dot-style=ESTILO         establece-lo xeito de representa-la\n"
"                                        descarga dos ficheiros.\n"
"  -N,  --timestamping             non descarga-los ficheiros se son máis\n"
"                                        vellos que os locais.\n"
"  -S,  --server-response          amosa-las respostas do servidor.\n"
"       --spider                   non baixar nada.\n"
"  -T,  --timeout=SEGUNDOS         establece-lo tempo de vencemento de lectura\n"
"                                        en SEGUNDOS.\n"
"  -w,  --wait=SEGUNDOS            agardar SEGUNDOS entre descargas.\n"
"  -Y,  --proxy=on/off             activar ou desactiva-lo proxy.\n"
"  -Q,  --quota=NÚMERO             establece-lo límite de descarga a NÚMERO.\n"
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
"Directorios:\n"
"  -nd, --no-directories            non crear directorios.\n"
"  -x,  --force-directories         forza-la creación de directorios.\n"
"  -nH, --no-host-directories       non crea-los directorios do servidor.\n"
"  -P,  --directory-prefix=PREFIXO  garda-los ficheiros a PREFIXO/...\n"
"       --cut-dirs=NÚMERO           ignorar NUMERO compoñentes dos directorios\n"
"                                        remotos.\n"
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
"Opcións HTTP:\n"
"       --http-user=USUARIO   establece-lo USUARIO coma o usuario de http.\n"
"       --http-passwd=CLAVE   establece-la CLAVE coma a clave de http.\n"
"  -C,  --cache=on/off        (non) admitir datos da caché do servidor\n"
"                                (normalmente admítense).\n"
"       --ignore-length       ignora-lo campo da cabeceira `Content-Length'.\n"
"       --header=CADEA        inserta-la CADEA entre as cabeceiras.\n"
"       --proxy-user=USUARIO  establece-lo USUARIO coma o usuario do proxy.\n"
"       --proxy-passwd=CLAVE  establece-la CLAVE coma a clave do proxy.\n"
"  -s,  --save-headers        garda-las cabeceiras HTTP ao ficheiro.\n"
"  -U,  --user-agent=AXENTE   identificar coma AXENTE no canto de Wget/VERSION.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Opcións FTP:\n"
"       --retr-symlinks   descarga-las ligazóns simbólicas de FTP.\n"
"  -g,  --glob=on/off     usar ou non comparación de nomes de ficheiros\n"
"                                con patróns.\n"
"       --passive-ftp     usa-lo modo de transferencia \"passive\".\n"
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
"Recuperación recursiva:\n"
"  -r,  --recursive             acceso recursivo a web -- ¡úsese con coidado!.\n"
"  -l,  --level=NUMERO          máximo nivel de recursión (0 é sen límite).\n"
"       --delete-after          borra-los ficheiros descargados.\n"
"  -k,  --convert-links         converti-los enlaces non relativos a relativos.\n"
"  -m,  --mirror                activar opcións axeitadas para facer mirrors.\n"
"  -nr, --dont-remove-listing   non borra-los ficheiros `.listing'.\n"
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
"Aceptar/rexeitar en recepcións recursivas:\n"
"  -A,  --accept=LISTA               lista de extensións aceptadas.\n"
"  -R,  --reject=LISTA               lista de extensións rexeitadas.\n"
"  -D,  --domains=LISTA              lista de dominios aceptados.\n"
"       --exclude-domains=LISTA      lista de dominios rexeitados separados\n"
"                                        por comas.\n"
"  -L,  --relative                   seguir só os enlaces relativos.\n"
"       --follow-ftp                 seguir enlaces FTP dende ficheiros HTML.\n"
"  -H,  --span-hosts                 ir a servidores estraños durante a\n"
"                                        recursión.\n"
"  -I,  --include-directories=LISTA  lista de directorios admitidos.\n"
"  -X,  --exclude-directories=LISTA  lista de directorios excluídos.\n"
"  -nh, --no-host-lookup             non busca-los servidores no DNS.\n"
"  -np, --no-parent                  non ascender ao directorio pai.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Envíe os seus informes sobre erros e suxerencias a <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: non se compilou con soporte de depuración.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Este programa distribúese coa intención de que sexa útil, pero SEN\n"
"NINGUNHA GARANTIA; nin sequera a garantía implícita de MERCABILIDADE\n"
"ou VALIDEZ PARA UN FIN PARTICULAR.  Vexa a Licencia Pública Xeral de\n"
"GNU para obter máis detalles.\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nEscrito por Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: comando non válido\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opción incorrecta -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Escriba `%s --help' para ver máis opcións.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Non se pode ser moi falador e estar en silencio ao mesmo tempo.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Non se pode poñer unha marca de data e hora e non machaca-los ficheiros antigos ao mesmo tempo.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: falta a URL\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Non se atoparon URLs en %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"REMATADO --%s--\n"
"Descargados: %s bytes en %d ficheiros\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "¡O límite de descarga (%s bytes) foi SUPERADO!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s recibido, redireccionando a saída a `%%s'\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"Recibiuse un CTRL+Break, redireccionando a saida a `%s'.\n"
"A execución segue en segundo plano.\n"
"Pode deter Wget premendo CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Seguindo en segundo plano.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Vaise escribi-la saida a `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Comezando WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Non se puido atopar un controlador de sockets utilizable.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: aviso: o elemento \"%s\" aparece antes dun nome de máquina\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: elemento \"%s\" descoñecido\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Uso: %s NETRC [SERVIDOR]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: non se pode obter información de %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Borrando %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Borrando %s porque debería ser rexeitado.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Cargando robots.txt; por favor, ignore os erros.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ saltando %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Non se puido atopar un servidor proxy.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Debe ser HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Redirección a si mesmo.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Abandonando.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Intentándoo de novo.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Error (%s): Proporcionouse a ligazón %s sen unha base.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Error (%s): A base %s é relativa, sen unha URL á que se referir.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Convertindo %s..."

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Non se poden converte-las ligazóns en %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Non hai memoria dabondo.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Protocolo descoñecido ou non soportado"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Especificación de porto incorrecta"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "O nome do servidor non é válido"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Fallo ao desligar `%s': %s\n"
