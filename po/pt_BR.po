# Brazilian Portuguese translation of the "wget" messages
# Copyright (C) 1998 Free Software Foundation, Inc.
# Wanderlei Antonio Cavassin <cavassin@conectiva.com.br>, 1998.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5-b9\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 1998-04-06 22:09-0300\n"
"Last-Translator: Wanderlei Antonio Cavasin <cavassin@conectiva.com.br>\n"
"Language-Team: Portuguese <pt@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-1\n"
"Content-Transfer-Encoding: 8-bit\n"

# , c-format
#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Conectando-se a %s:%hu... "

# , c-format
#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "Conexão para %s:%hu recusada.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "conectado!\n"

# , c-format
#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "Logando como %s ... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "Erro na resposta do servidor, fechando a conexão de controle.\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "Erro na saudação do servidor.\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "Falha de escrita, fechando a conexão de controle.\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "O servidor recusou o login.\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "Login incorreto.\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "Logado!\n"

# , c-format
#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tipo `%c' desconhecido, fechando a conexão de controle.\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "feito. "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD não necessário.\n"

# , c-format
#: src/ftp.c:317
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Diretório `%s' não encontrado.\n"
"\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "feito.\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD não requerido.\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "Não foi possível iniciar transferência PASV.\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "Não foi possível entender resposta do comando PASV.\n"

# , c-format
#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "Tentando conectar-se a %s:%hu.\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "feito.   "

# , c-format
#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "Erro no bind (%s).\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "PORT inválido.\n"

#: src/ftp.c:537
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST falhou, recomeçando do zero.\n"

# , c-format
#: src/ftp.c:586
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Arquivo `%s' não encontrado.\n"
"\n"

# , c-format
#: src/ftp.c:634
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Arquivo ou diretório `%s' não encontrado.\n"
"\n"

# , c-format
#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "Tamanho: %s"

# , c-format
#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [%s para terminar]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (sem autorização)\n"

# , c-format
#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, fechando conexão de controle.\n"

# , c-format
#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Conexão de dados: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "Conexão de controle fechada.\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "Transferência dos dados abortada.\n"

# , c-format
#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Arquivo `%s' já existente, não será baixado.\n"

# , c-format
#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(tentativa:%2d)"

# , c-format
#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' recebido [%ld]\n"
"\n"

# , c-format
#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Usando `%s' como arquivo temporário de listagem.\n"

# , c-format
#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "Removido `%s'.\n"

# , c-format
#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Nível de recursão %d excede nível máximo %d.\n"

# , c-format
#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid ""
"Local file `%s' is more recent, not retrieving.\n"
"\n"
msgstr ""
"Arquivo local `%s' é mais novo, não será baixado.\n"
"\n"

# , c-format
#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "Os tamanhos não são iguais (local %ld), baixando.\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Nome inválido do link simbólico, ignorando.\n"

# , c-format
#: src/ftp.c:1136
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Link simbólico já está correto %s -> %s\n"
"\n"

# , c-format
#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Criando link simbólico %s -> %s\n"

# , c-format
#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Links simbólicos não suportados, %s será ignorado.\n"

# , c-format
#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Ignorando diretório `%s'.\n"

# , c-format
#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tipo de arquivo desconhecido/não suportado.\n"

# , c-format
#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: horário (timestamp) inválido.\n"

# , c-format
#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr ""
"Não serão buscados diretórios, pois o nível de recursão é %d (max %d).\n"

# , c-format
#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Não descendo para `%s', pois está excluído/não incluído.\n"

# , c-format
#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Rejeitando `%s'.\n"

# , c-format
#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Nada encontrado com o padrão `%s'.\n"

# , c-format
#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Escrito index em formato HTML para `%s' [%ld].\n"

# , c-format
#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Escrito índice em formato HTML para `%s'.\n"

# , c-format
#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: opção `%s' é ambígua\n"

# , c-format
#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: opção `--%s' não permite argumento\n"

# , c-format
#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: opção `%c%s' não permite argumento\n"

# , c-format
#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: opção `%s' requer um argumento\n"

# , c-format
#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opção não reconhecida `--%s'\n"

# , c-format
#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opção não reconhecida `%c%s'\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opção ilegal -- %c\n"

# , c-format
#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: opção requer um argumento -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: Não foi possível determinar user-id.\n"

# , c-format
#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: Aviso: falha em uname: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: Aviso: falha em gethostname\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: Aviso: não foi possível determinar endereço IP local.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: Aviso: não foi possível resolver endereço IP local.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: Aviso: resolução do endereço local não resultou em FQDN!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "Host não encontrado"

#: src/host.c:541
msgid "Unknown error"
msgstr "Erro desconhecido"

# , c-format
#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Índice de /%s em %s:%d"

#: src/html.c:463
msgid "time unknown       "
msgstr "horário desconhecido "

#: src/html.c:467
msgid "File        "
msgstr "Arquivo     "

#: src/html.c:470
msgid "Directory   "
msgstr "Diretório   "

#: src/html.c:473
msgid "Link        "
msgstr "Link        "

#: src/html.c:476
msgid "Not sure    "
msgstr "Sem certeza "

# , c-format
#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "Falha na requisição HTTP.\n"

# , c-format
#: src/http.c:497
#, fuzzy, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s requisição enviada, buscando headers... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "Fim de arquivo durante a leitura dos headers.\n"

# , c-format
#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Erro de leitura (%s) nos headers.\n"

#: src/http.c:587
msgid "No data received"
msgstr ""

#: src/http.c:589
msgid "Malformed status line"
msgstr ""

#: src/http.c:594
msgid "(no description)"
msgstr "(sem descrição)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr ""

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr ""

# , c-format
#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "Localização: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "nao especificado"

#: src/http.c:750
msgid " [following]"
msgstr " [seguinte]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "Tamanho: "

# , c-format
#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (%s para o fim)"

#: src/http.c:774
msgid "ignored"
msgstr "ignorado"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Aviso: wildcards não suportados para HTTP.\n"

# , c-format
#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Arquivo `%s' já presente, não será baixado.\n"

# , c-format
#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Não foi possível escrever em `%s' (%s).\n"

# , c-format
#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERRO: Redireção (%d) sem Location.\n"

# , c-format
#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERRO %d: %s.\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Header Last-modified não recebido -- time-stamps desligados.\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Header Last-modified inválido -- time-stamp ignorado.\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "Arquivo remoto é mais novo, buscando.\n"

# , c-format
#: src/http.c:1098
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' recebido [%ld/%ld]\n"
"\n"

# , c-format
#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Conexão fechada no byte %ld. "

# , c-format
#: src/http.c:1138
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' recebido [%ld/%ld])\n"
"\n"

# , c-format
#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Conexão fechada no byte %ld/%ld. "

# , c-format
#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Erro de leitura no byte %ld (%s)."

# , c-format
#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Erro de leitura no byte %ld/%ld (%s)."

# , c-format
#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Não foi possível ler %s (%s).\n"

# , c-format
#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Erro em %s na linha %d.\n"

# , c-format
#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr ""
"%s: Aviso: os arquivos wgetrc do sistema e do usuário apontam para `%s'.\n"

# , c-format
#: src/init.c:458
#, fuzzy, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Comando desconhecido `%s', valor `%s'.\n"

# , c-format
#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Por favor especifique on ou off.\n"

# , c-format
#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: Especificação inválida `%s'\n"

# , c-format
#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: Especificação inválida `%s'\n"

# , c-format
#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Uso: %s [OPÇÃO]... [URL]...\n"

# , c-format
#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr ""
"GNU Wget %s, um programa não interativo para buscar arquivos da rede.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Argumentos obrigatórios para opções longas são também\n"
"obrigatórios para opções curtas.\n"
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
"Início:\n"
"  -V,  --version           mostra a versão do Wget e sai.\n"
"  -h,  --help              mostra esta ajuda.\n"
"  -b,  --background        executa em background.\n"
"  -e,  --execute=COMANDO   executa um comando `.wgetrc'.\n"
"\n"

# , fuzzy
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
"Geração de log e arquivo de entrada:\n"
"  -o,  --output-file=ARQUIVO   mensagens de log para ARQUIVO.\n"
"  -a,  --append-output=ARQUIVO apenda mensagens em ARQUIVO.\n"
"  -d,  --debug                 mostra saídas de debug.\n"
"  -q,  --quiet                 quieto (sem saídas).\n"
"  -nv, --non-verbose           desliga modo verboso, sem ser quieto.\n"
"  -i,  --input-file=ARQUIVO    lê URL-s de ARQUIVO.\n"
"  -F,  --force-html            trata arquivo de entrada como HTML.\n"
"\n"

# , fuzzy
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
"Download:\n"
"  -t,  --tries=NÚMERO            configura número de tentativas "
"(0=infinitas).\n"
"  -O   --output-document=ARQUIVO escreve os documentos no ARQUIVO.\n"
"  -nc, --no-clobber              não sobrescreve arquivos existentes.\n"
"       --dot-style=ESTILO        configura estilo do display de download.\n"
"  -N,  --timestamping            não busca arquivos mais antigos que os "
"locais.\n"
"  -S,  --server-response         mostra respostas do servidor.\n"
"       --spider                  não baixa nenhum arquivo.\n"
"  -T,  --timeout=SEGUNDOS        configura o timeout de leitura.\n"
"  -w,  --wait=SEGUNDOS           espera SEGUNDOS entre buscas de arquivos.\n"
"  -Y,  --proxy=on/off            liga ou desliga proxy.\n"
"  -Q,  --quota=NÚMERO            configura quota de recepção.\n"
"\n"

# , fuzzy
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
"Diretórios:\n"
"  -nd  --no-directories            não cria diretórios.\n"
"  -x,  --force-directories         força a criação de diretórios.\n"
"  -nH, --no-host-directories       não cria diretórios com nome do host.\n"
"  -P,  --directory-prefix=PREFIXO  salva arquivos em PREFIXO/...\n"
"\n"

# , fuzzy
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
"Opções HTTP:\n"
"       --http-user=USUÁRIO   configura usuário http.\n"
"       --http-passwd=SENHA   configura senha http.\n"
"  -C,  --cache=on/off        liga/desliga busca de dados do cache\n"
"                             (normalmente ligada).\n"
"       --ignore-length       ignora o header `Content-Length'.\n"
"       --header=STRING       insere STRING entre os headers.\n"
"       --proxy-user=USUÁRIO  configura nome do usuário do proxy.\n"
"       --proxy-passwd=SENHA  configura a senha do usuário do proxy.\n"
"  -s,  --save-headers        salva os headers HTTP no arquivo.\n"
"\n"

# , fuzzy
#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"Opções FTP:\n"
"       --retr-symlinks   busca links simbólicos FTP.\n"
"  -c,  --continue-ftp    recomeça a busca ftp aproveitando arquivos.\n"
"                         existentes e já recebidos em parte.\n"
"  -g,  --glob=on/off     liga/desliga expansão de nomes de arquivos.\n"
"       --passive-ftp     usa modo de transferência \"passivo\".\n"
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
"Busca recursiva:\n"
"  -r,  --recursive             busca recursiva -- use com cuidado!.\n"
"  -l,  --level=NÚMERO          nível máximo de recursão (0 para ilimitado).\n"
"       --delete-after          deleta arquivos baixados.\n"
"  -k,  --convert-links         converte links não relativos para relativos.\n"
"  -m,  --mirror                liga opções para espelhamento (mirror).\n"
"  -nr, --dont-remove-listing   não remove arquivos `.listing'.\n"
"\n"

# , fuzzy
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
"Aceitação/rejeição recursiva:\n"
"  -A,  --accept=LISTA              lista de extensões aceitas.\n"
"  -D,  --domains=LISTA             lista de domínios aceitos.\n"
"  -R,  --reject=LISTA              lista de extensões rejeitadas.\n"
"  -L,  --relative                  segue somente links relativos.\n"
"       --exclude-domains=LISTA     lista de domínios rejeitados.\n"
"       --follow-ftp                segue links FTP em documentos HTML.\n"
"  -H,  --span-hosts                segue hosts externos quando recursivo.\n"
"  -I,  --include-directories=LISTA lista de diretórios permitidos.\n"
"  -X,  --exclude-directories=LISTA lista de diretórios excluídos.\n"
"  -nh, --no-host-lookup            não faz DNS-lookup dos hosts.\n"
"  -np, --no-parent                 não sobe para o diretório pai.\n"
"\n"

# , fuzzy
#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Relatos de bugs e sugestões para <bug-wget@prep.ai.mit.edu>.\n"

# , fuzzy
#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: compilado sem debug.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"Este programa é distribuído com o objetivo de que seja útil,\n"
"mas SEM QUALQUER GARANTIA; nem mesmo a garantia ímplicita de\n"
"COMERCIABILIDADE ou de UTILIDADE PARA UM PROPÓSITO PARTICULAR.\n"
"Veja a Licença Pública Geral GNU (GNU GPL) para mais detalhes.\n"

#: src/main.c:401
msgid ""
"\n"
"Written by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr ""
"\n"
"Escrito por Hrvoje Niksic <hniksic@srce.hr>.\n"

# , c-format
#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: comando inválido\n"

# , c-format
#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opção ilegal -- `-n%c'\n"

# , c-format
#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Tente `%s --help' para mais opções.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Não pode ser verboso e quieto ao mesmo tempo.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr ""
"Não é possível usar as opções \"timestamp\" e \"no clobber\" ao mesmo "
"tempo.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL faltando\n"

# , c-format
#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Nenhuma URL encontrada em %s.\n"

# , c-format
#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"FINALIZADO --%s--\n"
"Baixados: %s bytes em %d arquivos\n"

# , c-format
#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "EXCEDIDA a quota (%s bytes) de recepção!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s recebido, redirecionando saída para `%%s'.\n"

# , c-format
#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break recebido, redirecionando saída para `%s'.\n"
"Execução continuará em background.\n"
"Você pode parar o Wget pressionando CTRL+ALT+DELETE.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "Continuando em background.\n"

# , c-format
#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Saída será escrita em `%s'.\n"

# , c-format
#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Disparando WinHelp %s\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Não foi possivel encontrar um driver de sockets usável.\n"

# , c-format
#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr ""
"%s: %s:%d: aviso: token \"%s\" aparece antes de qualquer nome de máquina\n"

# , c-format
#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: token desconhecido \"%s\"\n"

# , c-format
#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Uso: %s NETRC [NOME DO HOST]\n"

# , c-format
#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: não foi possível acessar %s: %s\n"

# , c-format
#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "Removendo %s.\n"

# , c-format
#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Removendo %s pois ele deve ser rejeitado.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Buscando robots.txt; por favor ignore qualquer erro.\n"

# , c-format
#: src/retr.c:193
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ ignorando %dK ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "Não foi possível encontrar o proxy.\n"

# , c-format
#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: Deve ser HTTP.\n"

# , c-format
#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: Redireção para si mesmo.\n"

#: src/retr.c:483
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Desistindo.\n"
"\n"

#: src/retr.c:483
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Tentando novamente.\n"
"\n"

# , c-format
#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "Erro (%s): Link %s sem uma base fornecida.\n"

# , c-format
#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "Erro (%s): Base %s relativa, sem URL referenciadora.\n"

# , c-format
#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "Convertendo %s... "

# , c-format
#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Não foi possível converter links em %s: %s\n"

# , c-format
#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Memória insuficiente.\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "Protocolo desconhecido/não suportado"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "Especificação de porta inválida"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "Nome do host inválido"

# , c-format
#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Falha na remoção do link simbólico `%s': %s\n"

# , c-format
#~ msgid "%s: unrecognized option, character code 0%o\n"
#~ msgstr "%s: opção não reconhecida, caractere código 0%o\n"

# , c-format
#~ msgid "%s: unrecognized option `-%c'\n"
#~ msgstr "%s: opção não reconhecida `-%c'\n"

# , c-format
#~ msgid "%s: option `-%c' requires an argument\n"
#~ msgstr "%s: opção `-%c' requer um argumento\n"

# , c-format
#~ msgid "wget: %s: Invalid specification `%s'.\n"
#~ msgstr "wget: %s: Especificação inválida `%s'.\n"

# , c-format
#~ msgid "wget: illegal option -- `-n%c'\n"
#~ msgstr "wget: opção ilegal -- `-n%c'\n"

#~ msgid "done."
#~ msgstr "feito."

#~ msgid "UNKNOWN"
#~ msgstr "DESCONHECIDO"
