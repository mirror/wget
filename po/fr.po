# Messages français pour GNU concernant enscript.
# Copyright (C) 1996 Free Software Foundation, Inc.
# Michel Robitaille <robitail@IRO.UMontreal.CA>, 1999.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1999-06-25 11:00 -0500\n"
"Last-Translator: Michel Robitaille <robitail@IRO.UMontreal.CA>\n"
"Language-Team: French <traduc@traduc.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-1\n"
"Content-Transfer-Encoding: 8-bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Connexion vers %s:%hu..."

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Connexion vers %s:%hu refusée.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "Connecté!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Session débutant sous %s..."

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "ERREUR dans la réponse du serveur, fermeture de connexion de contrôle.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "ERREUR dans le message de salutation du serveur.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "ÉCHEC d'écriture, fermeture de connexion de contrôle.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "Le serveur refuse l'établissement de session.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Établissement de session erroné.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Session établie!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Type %c inconnu, fermeture de connexion de contrôle.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "complété.  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD n'est pas nécessaire.\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "Répertoire `%s' inexistant.\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "complété.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD n'est pas requis.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Ne peut initier le transfert PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Ne peut analyser la réponse PASV.\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Tentative de connexion vers %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "complété.    "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "ERREUR de `bind' (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "Port non valable.\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nÉCHEC sur le reste, reprise depuis le début.\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "Fichier `%s' inexistant.\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "Fichier ou répertoire `%s' inexistant.\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Longueur: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s restant]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (non autorisée)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, fermeture de connexion de contrôle.\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Connexion de tranfert de données: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Connexion de contrôle fermée.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Transfert des données arrêté.\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Fichier `%s' est déjà là, pas de récupération.\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(essai:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' sauvegardé [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Utilisation de `%s' comme fichier temporaire de listage.\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "`%s' détruit.\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Le niveau %d de récursivité dépasse le niveau maximum %d.\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "Fichier local `%s' est plus récent, pas de récupération.\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "La taille des fichiers ne concorde pas (local %ld), récupération.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Nom erroné d'un lien symbolique, escamoté.\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Lien symbolique est déjà correct %s -> %s\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Création du lien symbolique %s -> %s\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Lien symbolique non supporté, escamotage du lien `%s'.\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Répertoire `%s' escamoté.\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: type de fichier inconnu ou non supporté.\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: tampon date-heure corrompu.\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Les répertoires ne seront pas récupérés, la profondeur %d dépasse le maximum %d.\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "%s n'a pas été parcouru puisqu'il est exclu ou non inclu.\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rejet de `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Pas de pairage sur le patron `%s'.\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Écriture de l'index HTML-isé vers `%s' [%ld].\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Écriture de l'index HTML-isé vers `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: l'option `%s' est ambigü.\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: l'option `--%s' ne permet pas un paramètre.\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: l'option `%c%s' ne permet pas un paramètre.\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: l'option `%s' requiert un paramètre.\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: l'option `--%s' n'est pas reconnue.\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: l'option `%c%s' n'est pas reconnue.\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: l'option -- %c est illégale.\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: l'option requiert le paramètre -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: ne peut déterminer le UID de l'usager.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: AVERTISSEMENT: échec de `uname': %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: AVERTISSEMENT: échec de la fonction gethostname()\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: AVERTISSEMENT: ne peut déterminer l'adresse IP locale.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: AVERTISSEMENT: ne peut repérer l'adresse IP locale par requête inverse.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: AVERTISSEMENT: requête inverse de l'adresse IP locale n'est pas complétée par FQDN!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Hôte non repéré"

#: src/host.c:541
msgid "Unknown error"
msgstr "ERREUR inconnue"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Index de /%s sur %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "heure inconnue     "

#: src/html.c:467
msgid "File        "
msgstr "Fichier     "

#: src/html.c:470
msgid "Directory   "
msgstr "Répertoire  "

#: src/html.c:473
msgid "Link        "
msgstr "Lien        "

#: src/html.c:476
msgid "Not sure    "
msgstr "Incertain   "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s octets)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Échec d'écriture de la requête HTTP.\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "requête %s transmise, en attente de la réponse..."

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Fin de fichier lors de l'analyse du l'en-tête.\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "ERREUR de lecture (%s) de l'en-tête.\n"

#: src/http.c:587
msgid "No data received"
msgstr "Aucune donnée reçue"

#: src/http.c:589
msgid "Malformed status line"
msgstr "Ligne d'état mal composée"

#: src/http.c:594
msgid "(no description)"
msgstr "(pas de description)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "Échec d'autorisation.\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "Schème inconnu d'authentification.\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Location: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "non spécifié"

#: src/http.c:750
msgid " [following]"
msgstr " [suivant]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Longueur: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s restant)"

#: src/http.c:774
msgid "ignored"
msgstr "ignoré"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "AVERTISSEMENT: les métacaractères ne sont pas supportés en HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Fichier `%s' est déjà là, pas de récupération.\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Ne peut écrire dans `%s' (%s).\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERREUR: redirection (%d) sans destination.\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERREUR %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "En-tête manquante de la dernière modification -- tampon date-heure ignoré.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "En-tête erronée de la dernière modification -- tampon date-heure ignoré.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Fichier éloigné est plus récent, récupération.\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' sauvegardé [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Fermeture de la connexion à l'octet %ld. "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' sauvegardé [%ld/%ld]\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Fermeture de la connexion à l'octet %ld/%ld. "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - ERREUR de lecture à l'octet %ld (%s)."

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - ERREUR de lecture à l'octet %ld/%ld (%s)."

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: ne peut lire %s (%s).\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: ERREUR dans %s à la ligne %d.\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: AVERTISSEMENT wgetrc tant du système que de l'usager pointe vers `%s'.\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: ERREUR: commande inconnue `%s', valeur `%s'.\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: SVP spécifier `on' ou `off'.\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: spécification erronnée `%s'.\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: spécification erronnée `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Usage: %s [OPTION]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, un récupérateur réseau non intéractif.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr ""
"\n"
"Les paramètres obligatoires pour les options de formes longues le sont\n"
"aussi pour les options de formes courtes.\n"
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
"Démarrage:\n"
"  -V,  --version               afficher le nom et la version du logiciel\n"
"  -h,  --help                  afficher l'aide-mémoire\n"
"  -b,  --background            travailler à l'arrière plan après le démarrage.\n"
"  -e,  --execute=COMMAND       exécuter une commande `.wgetrc'.\n"
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
"Journalisation et fichier d'entrée:\n"
"  -o,  --output-file=FICHIER   journaliser les messages dans le FICHIER.\n"
"  -a,  --append-output=FICHIER concaténer les messages au FICHIER.\n"
"  -d,  --debug                 afficher les informations de mise au point.\n"
"  -q,  --quiet                 travailler silencieusement (sans sortie).\n"
"  -v,  --verbose               travailler en mode bavard (par défaut).\n"
"  -nv, --non-verbose           ne pas travailler en mode bavard, sans être silencieux.\n"
"  -i,  --input-file=FICHIER    lire les URL du FICHIER.\n"
"  -F,  --force-html            traiter le fichier d'entrée comme du code HTML.\n"
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
"Téléchargement:\n"
"  -t,  --tries=NOMBRE            initialiser le NOMBRE d'essais (0 sans limite).\n"
"  -O   --output-document=FICHIER écrire les documents dans le FICHIER.\n"
"  -nc, --no-clobber              ne écraser les fichiers existants.\n"
"  -c,  --continue                redémarrer la récupération d'un fichier existant.\n"
"       --dot-style=STYLE         utiliser le STYLE d'affichage de récupération.\n"
"  -N,  --timestamping            ne pas récupérer un fichier plus vieux qu'un fichier local.\n"
"  -S,  --server-response         afficher la réponse du serveur.\n"
"       --spider                  ne pas télécharger n'importe quoi.\n"
"  -T,  --timeout=SECONDS         set the read timeout to SECONDS.\n"
"  -w,  --wait=N                  attendre N secondes entre chaque essai.\n"
"  -Y,  --proxy=on/off            activer (`on') ou désactiver (`off') le proxy.\n"
"  -Q,  --quota=N                 initialiser le quota de récupération à N.\n"
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
"Répertoires:\n"
"  -nd  --no-directories            na pas créer les répertoires.\n"
"  -x,  --force-directories         forcer la création des répertoires.\n"
"  -nH, --no-host-directories       ne pas créer les répertoires de l'hôte.\n"
"  -P,  --directory-prefix=PRÉFIXE  sauvegarder les fichiers avec le PRÉFIXE/...\n"
"       --cut-dirs=N                ignorer les N composants des répertoires de l'hôte.\n"
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
"Options HTTP:\n"
"       --http-user=USAGER      utiliser le nom de l'USAGER http.\n"
"       --http-passwd=MOT_DE_PASSE\n"
"                               utiliser le MOT_DE_PASSE http.\n"
"  -C,  --cache=on/off          activer (`on') ou désactiver (`off') la cache\n"
"                               de données du serveur (activé par défaut)\n"
"       --ignore-length         ignorer le champ `Content-Length' de l'en-tête.\n"
"       --header=CHAÎNE         insérer la CHAÎNE à travers les en-têtes.\n"
"       --proxy-user=USAGER     utiliser le nom de l'USAGER pour le proxy.\n"
"       --proxy-passwd=MOT_DE_PASSE\n"
"                               utiliser le MOT_DE_PASSE pour le proxy.\n"
"  -s,  --save-headers          sauvegarder les en-têtes HTTP dans le fichier.\n"
"  -U,  --user-agent=AGENT      identifier l'AGENT plutôt que Wget/VERSION.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Option FTP:\n"
"       --retr-symlinks   récupérer les lien symbolique via FTP.\n"
"  -g,  --glob=on/off     écraser (`on') ou ne pas écraser (`off') les noms de fichiers\n"
"       --passive-ftp     utiliser un mode de transfert passif.\n"
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
"Récupération récursive:\n"
"  -r,  --recursive             récupération récursive -- utiliser avec précaution!.\n"
"  -l,  --level=N               fixer le niveau maximal récursif à N (0 sans limite).\n"
"       --delete-after          détruire les fichiers téléchargés.\n"
"  -k,  --convert-links         convertir les liens non relatifs en liens relatifs.\n"
"  -m,  --mirror                activer l'option de récupération en mode mirroir.\n"
"  -nr, --dont-remove-listing   ne pas détruire les fichiers `.listing'.\n"
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
"Acception ou rejet récursif:\n"
"  -A,  --accept=LISTE               lister les extensions acceptées.\n"
"  -R,  --reject=LISTE               lister les extensions rejetées.\n"
"  -D,  --domains=LISTE              lister les domaines acceptés.\n"
"       --exclude-domains=LISTE      lister les domaines rejetés.\n"
"  -L,  --relative                   suivre les liens relatifs seulement.\n"
"       --follow-ftp                 suivre les liens FTP à partir de documents HTML.\n"
"  -H,  --span-hosts                 visiter les hôtes en mode récursif.\n"
"  -I,  --include-directories=LISTE  lister les répertoires permis.\n"
"  -X,  --exclude-directories=LISTE  lister les répertoire exclus.\n"
"  -nh, --no-host-lookup             ne pas repérer l'hôte par une requête au DNS.\n"
"  -np, --no-parent                  ne psa remonter dans le répertoire parent.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Transmettre toutes anomalies ou suggestions à <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: support de mise au point non compilé.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright © 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Ce logiciel est distribué en espérant qu'il soit utile,\n"
"mais sans AUCUNE garantie; sans la garantie liée à des raisons\n"
"COMMERÇIALES ou pour RÉPONDRE À UN BESOIN PARTICULIER.\n"
"selon les termes de la «GNU General Public License».\n"
"Pour plus d'informations à ce sujet, consulter la «GNU General Public License».\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nÉcrit par Hrvoje Niksic <hniksic@srce.hr>.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: commande invalide\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: option illégale -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Essayez `%s --help' pour plus d'informations.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Ne peut être en mode bavard et silencieux en même temps.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Ne peut dater et ne pas écraser les vieux fichiers en même temps.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL manquant\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Aucun URL repéré dans %s.\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"Terminé --%s--\n"
"Téléchargement: %s octets dans %d fichiers\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Quota de téléchargement (%s octets) DÉPASSÉ!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s reçu, redirection de la sortie vers `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break reçu, redirection de la sortie vers `%s'.\n"
"L'exécution de poursuit en arrière plan.\n"
"Vous pouvez arrêter l'exécution de `wget' en appuyant CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Poursuite à l'arrière plan.\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "La sortie sera écrite vers `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Démarrage de WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: ne repérer un pilote de socket utilisable.\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: AVERTISSEMENT: \"%s\" le jeton apparaît avant le nom d'une machine\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: jeton inconnu \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Usage: %s NETRC [HÔTE]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: ne peut évaluer par `stat' le fichier %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Destruction de %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Destruction de %s puiqu'il doit être rejeté.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Chargement de robots.txt; svp ignorer les erreurs.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ escamoté %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Ne peut repérer un hôte proxy.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: doit être de type HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: redirection vers lui-même.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "Abandon.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "Nouvel essai.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "ERREUR (%s): lien %s sans base fournie.\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "ERREUR (%s): base %s relative, sans URL référent.\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Converstion de %s..."

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Ne peut convertir les liens dans %s: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: mémoire épuisée.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Protocole inconnu ou non supporté"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Spécification du port erronée"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Nom de l'hôte erroné"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Échec de `unlink' sur le lien symbolique `%s': %s\n"
