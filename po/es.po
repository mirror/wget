# SOME DESCRIPTIVE TITLE.
# Copyright (C) YEAR Free Software Foundation, Inc.
# FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU Wget 1.6\n"
"POT-Creation-Date: 2001-02-26 21:18-0300\n"
"PO-Revision-Date: 2001-02-26 22:45+0300\n"
"Last-Translator: Nicolás Lichtmaier <nick@debian.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-1\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:152 src/http.c:354
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Conectándose con %s:%hu... "

#: src/ftp.c:174 src/ftp.c:416 src/http.c:371
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Conexión con %s:%hu rehusada.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:195 src/http.c:382
msgid "connected!\n"
msgstr "¡conectado!\n"

#: src/ftp.c:196
#, c-format
msgid "Logging in as %s ... "
msgstr "Entrando como %s ... "

#: src/ftp.c:205 src/ftp.c:258 src/ftp.c:306 src/ftp.c:358 src/ftp.c:452
#: src/ftp.c:525 src/ftp.c:573 src/ftp.c:621
msgid "Error in server response, closing control connection.\n"
msgstr ""

#: src/ftp.c:213
msgid "Error in server greeting.\n"
msgstr ""

#: src/ftp.c:221 src/ftp.c:267 src/ftp.c:315 src/ftp.c:367 src/ftp.c:462
#: src/ftp.c:535 src/ftp.c:583 src/ftp.c:631
msgid "Write failed, closing control connection.\n"
msgstr ""

#: src/ftp.c:228
msgid "The server refuses login.\n"
msgstr ""

#: src/ftp.c:235
msgid "Login incorrect.\n"
msgstr "Login incorrecto.\n"

#: src/ftp.c:242
msgid "Logged in!\n"
msgstr "¡Adentro!\n"

#: src/ftp.c:275
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tipo `%c' desconocido, cerrando conexión de control.\n"

#: src/ftp.c:288
msgid "done.  "
msgstr "hecho.  "

#: src/ftp.c:294
msgid "==> CWD not needed.\n"
msgstr "==> No se necesita CWD.\n"

#: src/ftp.c:322
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"No existe ningún directorio `%s'.\n"
"\n"

#: src/ftp.c:336 src/ftp.c:604 src/ftp.c:652 src/url.c:1678
msgid "done.\n"
msgstr "hecho.\n"

#. do not CWD
#: src/ftp.c:340
msgid "==> CWD not required.\n"
msgstr "==> No se requiere CWD.\n"

#: src/ftp.c:374
msgid "Cannot initiate PASV transfer.\n"
msgstr "No se puede iniciar transferencia PASV.\n"

#: src/ftp.c:378
msgid "Cannot parse PASV response.\n"
msgstr "No se pudo interpretar la respuesta de PASV.\n"

#: src/ftp.c:392
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Se intentará conectarse con %s:%hu.\n"

#: src/ftp.c:437 src/ftp.c:509 src/ftp.c:553
msgid "done.    "
msgstr "hecho.    "

#: src/ftp.c:479
#, c-format
msgid "Bind error (%s).\n"
msgstr ""

#: src/ftp.c:495
msgid "Invalid PORT.\n"
msgstr "PUERTO inválido.\n"

#: src/ftp.c:542
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"Falló REST, recomenzando de cero.\n"

#: src/ftp.c:591
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"No existe un archivo `%s'.\n"
"\n"

#: src/ftp.c:639
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"No existe el archivo o directorio `%s'.\n"
"\n"

#: src/ftp.c:715 src/ftp.c:722
#, c-format
msgid "Length: %s"
msgstr "Tamaño: %s"

#: src/ftp.c:717 src/ftp.c:724
#, c-format
msgid " [%s to go]"
msgstr " [%s para terminar]"

#: src/ftp.c:726
msgid " (unauthoritative)\n"
msgstr ""

#: src/ftp.c:752
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, cerrando conexión de control.\n"

#: src/ftp.c:760
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Conexión de datos: %s; "

#: src/ftp.c:777
msgid "Control connection closed.\n"
msgstr "Conexión de control cerrada.\n"

#: src/ftp.c:795
msgid "Data transfer aborted.\n"
msgstr "Transferencia de datos abortada.\n"

#: src/ftp.c:859
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "El archivo `%s' ya está, no se trae.\n"

#: src/ftp.c:920 src/http.c:1021
#, c-format
msgid "(try:%2d)"
msgstr "(intento:%2d)"

#: src/ftp.c:984 src/http.c:1251
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - %s' guardado [%ld]\n"
"\n"

#: src/ftp.c:1026 src/main.c:754 src/recur.c:472 src/retr.c:564
#, c-format
msgid "Removing %s.\n"
msgstr "Borrando %s.\n"

#: src/ftp.c:1067
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Usando `%s' como archivo temporario para el listado.\n"

#: src/ftp.c:1079
#, c-format
msgid "Removed `%s'.\n"
msgstr "Se borra `%s'.\n"

#: src/ftp.c:1115
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr ""

#: src/ftp.c:1167 src/http.c:1168
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"El archivo en el servidor no es más reciente que el local `%s' -- no se trae.\n"
"\n"

#: src/ftp.c:1173 src/http.c:1176
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Los tamaños no coinciden (el local es %ld) -- se trae.\n"

#: src/ftp.c:1190
msgid "Invalid name of the symlink, skipping.\n"
msgstr "El nombre del enlace simbólico no es válido. Se saltea.\n"

#: src/ftp.c:1207
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Ya se tiene el enlace %s -> %s correcto\n"
"\n"

#: src/ftp.c:1215
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Creando enlace simbólico %s -> %s\n"

#: src/ftp.c:1226
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "No se soportan enlaces simbólicos, se saltéa `%s'.\n"

#: src/ftp.c:1238
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Ignorando directorio `%s'.\n"

#: src/ftp.c:1247
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tipo de archivo desconocido/no soportado.\n"

#: src/ftp.c:1274
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: datado corrupto.\n"

#: src/ftp.c:1295
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "No se traen directorios ya que la profundidad es %d (máx: %d).\n"

#: src/ftp.c:1334
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "No se desciende a `%s' ya que está excluido o no incluido.\n"

#: src/ftp.c:1379
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rechazando `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1426
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "No hay coincidencias con `%s'.\n"

#: src/ftp.c:1486
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Índice en formato HTML escrito en `%s' [%ld].\n"

#: src/ftp.c:1491
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Índice en formato HTML escrito en `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: la opción `%s' es ambigua\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: la opción `--%s' no admite argumentos\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: la opción `%c%s' no admite argumentos\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: la opción `%s' requiere un argumento\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opción `--%s' desconocida\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opción `%c%s' desconocida\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opción ilegal -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: la opción requiere un argumento -- %c\n"

#: src/host.c:430
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: No se puede determinar el usuario.\n"

#: src/host.c:442
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Aviso: falló uname: %s\n"

#: src/host.c:454
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Aviso: falló gethostname\n"

#: src/host.c:482
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Aviso: no se puede determinar la dirección IP local.\n"

#: src/host.c:496
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr ""
"%s: Aviso: no se puede hacer la búsqueda inversa de la dirección IP local.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:509
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Aviso: ¡La búsqueda reversa de la dirección local no dio un FQDN!\n"

#: src/host.c:537
msgid "Host not found"
msgstr "Nombre de máquina no encontrado"

#: src/host.c:539
msgid "Unknown error"
msgstr "Error desconocido"

#: src/html.c:615 src/html.c:617
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Índice de /%s en %s:%d"

#: src/html.c:639
msgid "time unknown       "
msgstr "tiempo desconocido "

#: src/html.c:643
msgid "File        "
msgstr "Archivo     "

#: src/html.c:646
msgid "Directory   "
msgstr "Directorio  "

#: src/html.c:649
msgid "Link        "
msgstr "Enlace      "

#: src/html.c:652
msgid "Not sure    "
msgstr "No es seguro"

#: src/html.c:670
#, c-format
msgid " (%s bytes)"
msgstr ""

#: src/http.c:515
msgid "Failed writing HTTP request.\n"
msgstr "Falló la escritura del requerimiento HTTP.\n"

#: src/http.c:519
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "Requerimiento %s enviado, esperando respuesta... "

#: src/http.c:558
msgid "End of file while parsing headers.\n"
msgstr "Final de archivo mientras se analizaban las cabeceras.\n"

#: src/http.c:569
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Error de lectura (%s) en las cabeceras.\n"

#: src/http.c:609
msgid "No data received"
msgstr "No se recibieron datos"

#: src/http.c:611
msgid "Malformed status line"
msgstr "Línea de status mal formada"

#: src/http.c:616
msgid "(no description)"
msgstr "(sin descripción)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:700
msgid "Authorization failed.\n"
msgstr "Falló autorización.\n"

#: src/http.c:707
msgid "Unknown authentication scheme.\n"
msgstr "Esquema de autentificación desconocido.\n"

#: src/http.c:790
#, c-format
msgid "Location: %s%s\n"
msgstr "Ubicación: %s%s\n"

#: src/http.c:791 src/http.c:816
msgid "unspecified"
msgstr "no especificado"

#: src/http.c:792
msgid " [following]"
msgstr " [siguiendo]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:806
msgid "Length: "
msgstr "Tamaño: "

#: src/http.c:811
#, c-format
msgid " (%s to go)"
msgstr " (faltan %s)"

#: src/http.c:816
msgid "ignored"
msgstr "se ignora"

#: src/http.c:917
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Aviso: no se soportan comodines en HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:938
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "El archivo `%s' ya está, no se trae.\n"

#: src/http.c:1088
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "No se pudo escribir a `%s' (%s).\n"

#: src/http.c:1099
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERROR: Redirección (%d) sin `location'.\n"

#: src/http.c:1124
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr ""

#: src/http.c:1137
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Falta cabecera Last-modified -- no se usará time-stamps.\n"

#: src/http.c:1145
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Cabecera Last-modified inválido -- se ignora el time-stamp.\n"

#: src/http.c:1180
msgid "Remote file is newer, retrieving.\n"
msgstr "El archivo remoto es más nuevo, se lo trae.\n"

#: src/http.c:1225
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' guardado [%ld/%ld]\n"
"\n"

#: src/http.c:1273
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - La conexión se cerró en el byte %ld. "

#: src/http.c:1281
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - %s' guardado [%ld/%ld])\n"
"\n"

#: src/http.c:1301
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - La conexión se cerró en el byte %ld/%ld. "

#: src/http.c:1312
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Error de lectura en el byte %ld (%s)."

#: src/http.c:1320
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Error de lectura en el byte %ld/%ld (%s). "

#: src/init.c:329 src/netrc.c:260
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: No se puede leer %s (%s).\n"

#: src/init.c:347 src/init.c:353
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Error en %s, línea %d.\n"

#: src/init.c:384
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Aviso: El wgetrc de usuario y el de sistema apuntan a `%s'.\n"

#: src/init.c:476
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: comando desconocido `%s', valor `%s'.\n"

#: src/init.c:497
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: No se puede convertir `%s' a una dirección IP.\n"

#: src/init.c:525
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Especifique `on' u `off'.\n"

#: src/init.c:569
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Por favor especifique `always', `on', `off' o `never'.\n"

#: src/init.c:588 src/init.c:845 src/init.c:867 src/init.c:931
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Especificación `%s' inválida.\n"

#: src/init.c:701 src/init.c:723 src/init.c:745 src/init.c:771
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Especificación `%s' inválida.\n"

#: src/main.c:107
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Uso: %s [OPCIÓN]... [URL]...\n"

#: src/main.c:115
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, un recuperador de datos de red no interactivo.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:120
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Los argumentos obligatorios para las opciones largas también lo son para\n"
"las cortas.\n"
"\n"

#: src/main.c:123
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Comienzo:\n"
"  -V,  --version           muestra la versión de Wget y termina.\n"
"  -h,  --help              muestra esta ayuda.\n"
"  -b,  --background        pasa a segundo plano luego del inicio.\n"
"  -e,  --execute=COMANDO   ejectuta un comando `.wgetrc'.\n"
"\n"

#: src/main.c:129
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
"Archivos de registro y entrada:\n"
"  -o,  --output-file=ARCHIVO   registra los mensajes en ARCHIVO.\n"
"  -a,  --append-output=ARCHIVO agrega los mensajes a ARCHIVO.\n"
"  -d,  --debug                 imprime mensajes de debug.\n"
"  -q,  --quiet                 silencioso (no imprime mensajes).\n"
"  -v,  --verbose               locuaz (esta es la opción por omisión).\n"
"  -nv, --non-verbose           ni locuaz ni silencioso, punto medio.\n"
"  -i,  --input-file=ARCHIVO    lee las URL de ARCHIVO.\n"
"  -F,  --force-html            trata al archivo de entrada como HTML.\n"
"  -B,  --base=URL              prefija con URL los enlaces relativos\n"
"                               de -F -i archivo.\n"

#: src/main.c:140
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local "
"host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 "
"unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# "
"suffixes.\n"
"  -c,  --continue               restart getting an existing file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't retrieve files if older than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a "
"retrieval.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""
"Descarga:\n"
"       --bind-address=DIR       usa DIR como dirección local (con bind()).\n"
"  -t,  --tries=NÚMERO           establece el número de reintentos en NÚMERO\n"
"                                (0: sin límite)\n"
"  -O,  --output-document=ARCHIVO escribe los documentos en ARCHIVO.\n"
"  -nc, --no-clobber             no sobreescribe archivos existentes\n"
"                                ni usa sufijos numerados.\n"
"  -c,  --continue               intenta terminar de traer un archivo "
"existente.\n"
"       --dot-style=ESTILO       set retrieval display style.\n"
"  -N,  --timestamping           no trae archivos más viejos que los "
"locales.\n"
"  -S,  --server-response        imprime la respuesta del servidor.\n"
"       --spider                 no trae nada.\n"
"  -T,  --timeout=SEGUNDOS       el tiempo máximo en una lectura será SEGUNDOS.\n"
"  -w,  --wait=SEGUNDOS          espera SEGUNDOS entre descargas.\n"
"       --waitretry=SEGUNDOS     espera 1...SEGUNDOS entre reintentos.\n"
"  -Y,  --proxy=on/off           activa o desactiva el uso de proxy.\n"
"  -Q,  --quota=NÚMERO           establece la cuota de descarga en número.\n"
"\n"

#: src/main.c:156
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
"Directorios:\n"
"  -nd, --no-directories            no crea directorios.\n"
"  -x,  --force-directories         fuerza la creación de directorios.\n"
"  -nH, --no-host-directories       no crea directorios según estén en\n"
"                                   el servidor.\n"
"  -P,  --directory-prefix=PREFIJO  guarda archivos en PREFIJO/...\n"
"       --cut-dirs=NÚMERO           ignora NÚMERO componentes del directorio\n"
"                                   remoto.\n"
"\n"

#: src/main.c:163
msgid ""
"HTTP options:\n"
"       --http-user=USER      set http user to USER.\n"
"       --http-passwd=PASS    set http password to PASS.\n"
"  -C,  --cache=on/off        (dis)allow server-cached data (normally "
"allowed).\n"
"  -E,  --html-extension      save all text/html documents with .html "
"extension.\n"
"       --ignore-length       ignore `Content-Length' header field.\n"
"       --header=STRING       insert STRING among the headers.\n"
"       --proxy-user=USER     set USER as proxy username.\n"
"       --proxy-passwd=PASS   set PASS as proxy password.\n"
"       --referer=URL         include `Referer: URL' header in HTTP request.\n"
"  -s,  --save-headers        save the HTTP headers to file.\n"
"  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\n"
"\n"
msgstr ""
"Opciones de HTTP:\n"
"       --http-user=USUARIO   utiliza USUARIO como usuario http.\n"
"       --http-passwd=CLAVE   utiliza la clave CLAVE.\n"
"  -C,  --cache=on/off        admite (on) o no (off) datos cacheados en el\n"
"                             servidor (normalmente sí).\n"
"  -E,  --html-extension      graba todo documento de tipo text/html con\n"
"                             una extensión acorde.\n"
"       --ignore-length       ignora la cabecera `Content-length'.\n"
"       --header=CABECERA     inserta CABECERA en el encabezado.\n"
"       --proxy-user=USUARIO  utiliza USUARIO para conectarse al proxy.\n"
"       --proxy-passwd=CLAVE  utiliza la clave CLAVE con el proxy.\n"
"       --referer             incluye `Referer: URL' en el requerimiento.\n"
"  -s,  --save-headers        guarda las cabeceras HTTP en un archivo.\n"
"  -U,  --user-agent=AGENTE   se identifica como AGENTE en vez de "
"Wget/VERSIÓN.\n"
"\n"

#: src/main.c:176
msgid ""
"FTP options:\n"
"       --retr-symlinks   when recursing, retrieve linked-to files (not "
"dirs).\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Opciones de FTP:\n"
"       --retr-symlinks   al deambular traer los archivos referidos"
"                         mediante enlaces simbólicos (que no sean dirs).\n"
"  -g,  --glob=on/off     activar o desactivar la expansión de patrones\n"
"                         para archivos.\n"
"       --passive-ftp     usa el modo de transferencia \"pasivo\".\n"
"\n"

#: src/main.c:181
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive             recursive web-suck -- use with care!.\n"
"  -l,  --level=NUMBER          maximum recursion depth (inf or 0 for "
"infinite).\n"
"       --delete-after          delete files locally after downloading them.\n"
"  -k,  --convert-links         convert non-relative links to relative.\n"
"  -K,  --backup-converted      before converting file X, back up as X.orig.\n"
"  -m,  --mirror                shortcut option equivalent to -r -N -l inf "
"-nr.\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -p,  --page-requisites       get all images, etc. needed to display HTML "
"page.\n"
"\n"
msgstr ""
"Descarga recursiva:\n"
"  -r,  --recursive            aspira la web recursivamente--¡use con cuidado!\n"
"  -l,  --level=NUMBER         profundidad máxima de recursión\n"
"                              (inf o 0 para infinito).\n"
"       --delete-after         borra los archivos locales después de traerlos.\n"
"  -k,  --convert-links        convierte enlaces absolutos en relativos.\n"
"  -K,  --backup-converted     antes de convertir X, se lo guarda como X.orig.\n"
"  -m,  --mirror               equivalente a -r -N -l inf -nr.\n"
"  -nr, --dont-remove-listing  no elimina archivos `.listing'.\n"
"  -p,  --page-requisites      trae lo necesario para mostrar la página HTML.\n"
"\n"

#: src/main.c:191
msgid ""
"Recursive accept/reject:\n"
"  -A,  --accept=LIST                comma-separated list of accepted "
"extensions.\n"
"  -R,  --reject=LIST                comma-separated list of rejected "
"extensions.\n"
"  -D,  --domains=LIST               comma-separated list of accepted "
"domains.\n"
"       --exclude-domains=LIST       comma-separated list of rejected "
"domains.\n"
"       --follow-ftp                 follow FTP links from HTML documents.\n"
"       --follow-tags=LIST           comma-separated list of followed HTML "
"tags.\n"
"  -G,  --ignore-tags=LIST           comma-separated list of ignored HTML "
"tags.\n"
"  -H,  --span-hosts                 go to foreign hosts when recursive.\n"
"  -L,  --relative                   follow relative links only.\n"
"  -I,  --include-directories=LIST   list of allowed directories.\n"
"  -X,  --exclude-directories=LIST   list of excluded directories.\n"
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Selección de URLs en la recursión:\n"
"  -A,  --accept=LISTA               lista delimitada con comas de\n"
"                                    extensiones aceptadas.\n"
"  -R,  --reject=LISTA               lista delimitada con comas de\n"
"                                    extensiones rechazadas.\n"
"  -D,  --domains=LISTA              lista delimitada con comas de\n"
"                                    dominios aceptados.\n"
"       --exclude-domains=LISTA      lista delimitada con comas de\n"
"                                    dominios rechazados.\n"
"       --follow-ftp                 seguir enlaces FTP desde documentos HTML.\n"
"       --follow-tags=LISTA          lista delimitada con comas de\n"
"                                    tags HTML seguidos.\n"
"  -G,  --ignore-tags=LISTA          lista delimitada con comas de\n"
"                                    tags HTML ignorados.\n"
"  -H,  --span-hosts                 seguir hacia sitios externos.\n"
"  -L,  --relative                   seguir sólo enlaces relativos.\n"
"  -I,  --include-directories=LISTA  lista de directorios permitidos.\n"
"  -X,  --exclude-directories=LISTA  lista de directorios excluidos.\n"
"  -nh, --no-host-lookup             no buscar nombres de máquinas en DNS.\n"
"  -np, --no-parent                  no ascender al directorio padre.\n"
"\n"

#: src/main.c:206
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Envíe reportes de errores y sugerencias a <bug-wget@gnu.org>.\n"

#: src/main.c:385
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: soporte para depuración no compilado.\n"

#: src/main.c:437
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"Este programa se distribuye con la esperanza de que sea útil,\n"
"pero SIN NINGUNA GARANTÍA; no siquiera una garantía implícita de\n"
"MERCANTIBILIDAD o APLICABILIDAD PARA ALGÚN PROPÓSITO EN PARTICULAR.\n"
"Vea la GNU General Public License para más detalles.\n"

#: src/main.c:443
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr ""
"\n"
"Originalmente escrito por Hrvoje Niksic <hniksic@arsdigita.com>.\n"

#: src/main.c:517
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s; comando inválido\n"

#: src/main.c:570
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opción ilegal -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:573 src/main.c:615 src/main.c:673
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Para más opciones pruebe con `%s --help'.\n"

#: src/main.c:653
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "No se puede ser locuaz (--verbose) y silencioso (--quiet) a la vez.\n"

#: src/main.c:659
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "No se puede datar y evitar sobreescribir viejos archivos a la vez.\n"

#. No URL specified.
#: src/main.c:668
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: falta URL\n"

#: src/main.c:769
#, c-format
msgid "No URLs found in %s.\n"
msgstr "No se encontraron URLs en %s.\n"

#: src/main.c:778
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"TERMINADO --%s--\n"
"Se bajó: %s bytes en %d archivos\n"

#: src/main.c:786
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "¡Cuota de bajado (%s bytes) EXCEDIDA!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:813
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "se recibió %s, redirigiendo salida hacia `%%s'.\n"

#: src/mswindows.c:123
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""

#. parent, no error
#: src/mswindows.c:140 src/utils.c:269
msgid "Continuing in background.\n"
msgstr "Continuando en segundo plano.\n"

#: src/mswindows.c:142 src/utils.c:271
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "La salida será escrita en `%s'.\n"

#: src/mswindows.c:232
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Ejecutando WinHelp %s\n"

#: src/mswindows.c:259 src/mswindows.c:267
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr ""

#: src/netrc.c:359
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""

#: src/netrc.c:390
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr ""

#: src/netrc.c:454
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Uso: %s NETRC [MÁQUINA]\n"

#: src/netrc.c:464
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: no se pudo acceder a %s con stat(): %s\n"

#: src/recur.c:473
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Borrando %s, ya que debería ser rechazado.\n"

#: src/recur.c:634
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Cargando robots.txt, por favor ignore errores.\n"

#: src/retr.c:201
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ %dK salteados ]"

#: src/retr.c:384
msgid "Could not find proxy host.\n"
msgstr "No se pudo encontrar al servidor proxy.\n"

#: src/retr.c:397
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Debe ser HTTP.\n"

#: src/retr.c:476
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Redirección a sí mismo.\n"

#: src/retr.c:490
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Se detectó un anillo de redirecciones.\n"

#: src/retr.c:585
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Me rindo.\n"
"\n"

#: src/retr.c:585
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Reintentando.\n"
"\n"

#: src/url.c:983
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Error (%s): Enlace %s sin que se haya provisto una base.\n"

#: src/url.c:999
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Error (%s): La base %s es relativa, sin un URL de `referer'.\n"

#: src/url.c:1540
#, c-format
msgid "Converting %s... "
msgstr "Convirtiendo %s... "

#: src/url.c:1545 src/url.c:1632
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "No se pueden convertir enlaces en %s: %s\n"

#: src/url.c:1608
#, fuzzy, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "No se pueden convertir enlaces en %s: %s\n"

#: src/utils.c:72
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: No hay memoria suficiente.\n"

#: src/utils.c:204
msgid "Unknown/unsupported protocol"
msgstr "Protocolo desconocido/no-soportado"

#: src/utils.c:207
msgid "Invalid port specification"
msgstr "Especificación de puerto inválida"

#: src/utils.c:210
msgid "Invalid host name"
msgstr "Nombre de host inválido"

#: src/utils.c:431
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "No se pudo borrar el enlace simbólico `%s': %s\n"

#~ msgid ""
#~ "Local file `%s' is more recent, not retrieving.\n"
#~ "\n"
#~ msgstr ""
#~ "El archivo local `%s' es más reciente, no se trae.\n"
#~ "\n"
