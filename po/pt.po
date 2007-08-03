# Portuguese translation of the "wget" messages
# Copyright (C) 2005 Free Software Foundation, Inc.
# This file is distributed under the same license as the wget package.
# Helder Correia <helder.pereira.correia@gmail.com>, 2005.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.10.1-b1\n"
"Report-Msgid-Bugs-To: \n"
"POT-Creation-Date: 2005-07-08 08:08-0400\n"
"PO-Revision-Date: 2005-11-18 21:38+0000\n"
"Last-Translator: Helder Correia <helder.pereira.correia@gmail.com>\n"
"Language-Team: Portuguese <translation-team-pt@lists.sourceforge.net>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/connect.c:199
#, c-format
msgid "%s: unable to resolve bind address `%s'; disabling bind.\n"
msgstr "%s: incapaz de resolver o endereço de ligação '%s'; a desactivar a ligação.\n"

#: src/connect.c:271
#, c-format
msgid "Connecting to %s|%s|:%d... "
msgstr "A conectar %s|%s|:%d... "

#: src/connect.c:274
#, c-format
msgid "Connecting to %s:%d... "
msgstr "A conectar %s:%d... "

#: src/connect.c:335
msgid "connected.\n"
msgstr "conectado.\n"

#: src/connect.c:347 src/host.c:789 src/host.c:818
#, c-format
msgid "failed: %s.\n"
msgstr "falhou: %s.\n"

#: src/convert.c:176
#, c-format
msgid "Converted %d files in %.*f seconds.\n"
msgstr "%d ficheiros convertidos em %.*f segundos.\n"

#: src/convert.c:202
#, c-format
msgid "Converting %s... "
msgstr "A converter %s..."

#: src/convert.c:215
msgid "nothing to do.\n"
msgstr "nada para fazer.\n"

#: src/convert.c:223 src/convert.c:247
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Não é possível converter as ligações em %s: %s\n"

#: src/convert.c:238
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Não é possível remover '%s': %s\n"

#: src/convert.c:447
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Não é possível salvaguardar %s como %s: %s\n"

#: src/cookies.c:619
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Erro em Set-Cookie, campo '%s'"

#: src/cookies.c:643
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Erro de sintaxe em Set-Cookie: %s na posiçao %d.\n"

#: src/cookies.c:881
#, c-format
msgid "Cookie coming from %s attempted to set domain to %s\n"
msgstr "O 'cookie' vindo de %s tentou definir o domínio como %s\n"

#: src/cookies.c:1328 src/cookies.c:1477
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Não é possível abrir o ficheiro de cookies '%s': %s\n"

#: src/cookies.c:1489
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Erro ao escrever para '%s': %s\n"

#: src/cookies.c:1492
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Erro ao fechar '%s': %s\n"

#: src/ftp-ls.c:841
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Tipo de listagem não suportado, a tentar o analisador de listagem Unix.\n"

#: src/ftp-ls.c:887 src/ftp-ls.c:889
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Índice de /%s em %s:%d"

#: src/ftp-ls.c:912
#, c-format
msgid "time unknown       "
msgstr "tempo desconhecido       "

#: src/ftp-ls.c:916
#, c-format
msgid "File        "
msgstr "Ficheiro        "

#: src/ftp-ls.c:919
#, c-format
msgid "Directory   "
msgstr "Pasta   "

#: src/ftp-ls.c:922
#, c-format
msgid "Link        "
msgstr "Ligação        "

#: src/ftp-ls.c:925
#, c-format
msgid "Not sure    "
msgstr "Incerto    "

#: src/ftp-ls.c:943
#, c-format
msgid " (%s bytes)"
msgstr " (%s bytes)"

#: src/ftp.c:226
#, c-format
msgid "Length: %s"
msgstr "Tamanho: %s"

#: src/ftp.c:232 src/http.c:1861
#, c-format
msgid ", %s (%s) remaining"
msgstr ", %s (%s) em falta"

#: src/ftp.c:236 src/http.c:1865
#, c-format
msgid ", %s remaining"
msgstr ", %s em falta"

#: src/ftp.c:239
msgid " (unauthoritative)\n"
msgstr " (não autoritário)\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:314
#, c-format
msgid "Logging in as %s ... "
msgstr "A entrar como %s ... "

#: src/ftp.c:327 src/ftp.c:373 src/ftp.c:402 src/ftp.c:454 src/ftp.c:566
#: src/ftp.c:612 src/ftp.c:640 src/ftp.c:698 src/ftp.c:759 src/ftp.c:819
#: src/ftp.c:866
msgid "Error in server response, closing control connection.\n"
msgstr "Erro na resposta do servidor, a fechar a conexão de controlo.\n"

#: src/ftp.c:334
msgid "Error in server greeting.\n"
msgstr "Erro na saudação do servidor.\n"

#: src/ftp.c:341 src/ftp.c:462 src/ftp.c:574 src/ftp.c:648 src/ftp.c:708
#: src/ftp.c:769 src/ftp.c:829 src/ftp.c:876
msgid "Write failed, closing control connection.\n"
msgstr "A escrita falhou, a fechar a conexão de controlo.\n"

#: src/ftp.c:347
msgid "The server refuses login.\n"
msgstr "O servidor recusa a entrada.\n"

#: src/ftp.c:353
msgid "Login incorrect.\n"
msgstr "Entrada incorrecta.\n"

#: src/ftp.c:359
msgid "Logged in!\n"
msgstr "Entrada com sucesso!\n"

#: src/ftp.c:381
msgid "Server error, can't determine system type.\n"
msgstr "Erro do servidor, não é possível determinar o tipo de sistema.\n"

#: src/ftp.c:390 src/ftp.c:685 src/ftp.c:742 src/ftp.c:785
msgid "done.    "
msgstr "feito.    "

#: src/ftp.c:442 src/ftp.c:591 src/ftp.c:624 src/ftp.c:849 src/ftp.c:895
msgid "done.\n"
msgstr "feito.\n"

#: src/ftp.c:469
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tipo '%c' desconhecido, a feito a conexão de controlo.\n"

#: src/ftp.c:481
msgid "done.  "
msgstr "feito.  "

#: src/ftp.c:487
msgid "==> CWD not needed.\n"
msgstr "==> CWD desnecessário.\n"

#: src/ftp.c:580
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Pasta '%s' inexistente.\n"
"\n"

#. do not CWD
#: src/ftp.c:595
msgid "==> CWD not required.\n"
msgstr "==> CWD não requerido.\n"

#: src/ftp.c:654
msgid "Cannot initiate PASV transfer.\n"
msgstr "Não é possível iniciar a transferência PASV.\n"

#: src/ftp.c:658
msgid "Cannot parse PASV response.\n"
msgstr "Não é possível analisar a resposta PASV.\n"

#: src/ftp.c:676
#, c-format
msgid "couldn't connect to %s port %d: %s\n"
msgstr "não foi possível conectar %s porto %d: %s\n"

#: src/ftp.c:724
#, c-format
msgid "Bind error (%s).\n"
msgstr "Erro de cobertura (%s).\n"

#: src/ftp.c:730
msgid "Invalid PORT.\n"
msgstr "PORT inválido.\n"

#: src/ftp.c:776
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST falhou, a reiniciar.\n"

#: src/ftp.c:837
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"O ficheiro '%s' não existe.\n"
"\n"

#: src/ftp.c:884
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Ficheiro ou pasta '%s' inexistente.\n"
"\n"

#. We cannot just invent a new name and use it (which is
#. what functions like unique_create typically do)
#. because we told the user we'd use this name.
#. Instead, return and retry the download.
#: src/ftp.c:946 src/http.c:1922
#, c-format
msgid "%s has sprung into existence.\n"
msgstr "%s formou-se de repente.\n"

#: src/ftp.c:1008
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, a fechar a conexão de controlo.\n"

#: src/ftp.c:1016
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - conexão de dados: %s; "

#: src/ftp.c:1031
msgid "Control connection closed.\n"
msgstr "Conexão de controlo fechada.\n"

#: src/ftp.c:1049
msgid "Data transfer aborted.\n"
msgstr "Transferência de dados cancelada.\n"

#: src/ftp.c:1117
#, c-format
msgid "File `%s' already there; not retrieving.\n"
msgstr "O ficheiro '%s' já existe; a não transferir.\n"

#: src/ftp.c:1185 src/http.c:2142
#, c-format
msgid "(try:%2d)"
msgstr "(tentativa:%2d)"

#: src/ftp.c:1255 src/http.c:2421
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s]\n"
"\n"
msgstr ""
"%s (%s) - '%s' gravado [%s]\n"
"\n"

#: src/ftp.c:1297 src/main.c:948 src/recur.c:376 src/retr.c:844
#, c-format
msgid "Removing %s.\n"
msgstr "A remover %s.\n"

#: src/ftp.c:1339
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "A usar '%s' como ficheiro de listagem temporário.\n"

#: src/ftp.c:1354
#, c-format
msgid "Removed `%s'.\n"
msgstr "'%s' removido.\n"

#: src/ftp.c:1389
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Profundidade de recursividade %d excedeu a profundidade máxima %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1459
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "O ficheiro remoto é mais antigo que o ficheiro local '%s' -- a não transferir.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1466
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr ""
"O ficheiro remoto é mais recente que o ficheiro local '%s' -- a transferir.\n"
"\n"

#. Sizes do not match
#: src/ftp.c:1473
#, c-format
msgid ""
"The sizes do not match (local %s) -- retrieving.\n"
"\n"
msgstr ""
"Os tamanhos não coincidem (local %s) -- a transferir.\n"
"\n"

#: src/ftp.c:1491
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Nome da ligação simbólica inválido, a ignorar.\n"

#: src/ftp.c:1508
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr "Já tem a ligação simbólica correcta %s -> %s\n"

#: src/ftp.c:1516
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "A criar a ligação simbólica %s -> %s\n"

#: src/ftp.c:1526
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Ligações simbólicas não suportadas, a ignorar ligação simbólica '%s'.\n"

#: src/ftp.c:1538
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "A ignorar a pasta '%s'.\n"

#: src/ftp.c:1547
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: tipo de ficheiro desconhecido ou não suportado.\n"

#: src/ftp.c:1574
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: selo temporal corrompido.\n"

#: src/ftp.c:1602
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "As pastas não serão transferidas, uma ves que a profundidade é %d (máximo %d).\n"

#: src/ftp.c:1652
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "A não descer para '%s', uma vez que está excluída.\n"

#: src/ftp.c:1718 src/ftp.c:1732
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "A rejeitar '%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1778
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Não há correspondências com o padrão '%s'.\n"

#: src/ftp.c:1844
#, c-format
msgid "Wrote HTML-ized index to `%s' [%s].\n"
msgstr "Índice em HTML gravado para '%s' [%s].\n"

#: src/ftp.c:1849
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Índice HTML gravado para '%s'.\n"

#: src/getopt.c:675
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: a opção '%s' é ambígua\n"

#: src/getopt.c:700
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: a opção '--%s não permite um argumento\n"

#: src/getopt.c:705
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: a opção '%c%s' não permite um argumento\n"

#: src/getopt.c:723 src/getopt.c:896
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: a opção '%s' requere um argumento\n"

#. --option
#: src/getopt.c:752
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: opção '--%s' desconhecida\n"

#. +option or -option
#: src/getopt.c:756
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: opção '%c%s' desconhecida\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:782
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: opção ilegal -- %c\n"

#: src/getopt.c:785
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: opção inválida -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:815 src/getopt.c:945
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s a opção requere um argumento -- %c\n"

#: src/getopt.c:862
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: a opção '-W %s' é ambígua\n"

#: src/getopt.c:880
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: a opção '-W %s' não permite um argumento\n"

#: src/host.c:366
msgid "Unknown host"
msgstr "Máquina desconhecida"

#. Message modeled after what gai_strerror returns in similar
#. circumstances.
#: src/host.c:370
msgid "Temporary failure in name resolution"
msgstr "Falha temporária na resolução de nome"

#: src/host.c:372
msgid "Unknown error"
msgstr "Erro desconhecido"

#: src/host.c:751
#, c-format
msgid "Resolving %s... "
msgstr "A resolver %s..."

#: src/host.c:798
msgid "failed: No IPv4/IPv6 addresses for host.\n"
msgstr "falhou: Endereços IPv4/IPv6 inexistentes para a máquina.\n"

#: src/host.c:821
msgid "failed: timed out.\n"
msgstr "falhou: terminou o tempo.\n"

#: src/html-url.c:298
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Não é possível resolver a ligação incompleta %s.\n"

#: src/html-url.c:705
#, c-format
msgid "%s: Invalid URL %s: %s\n"
msgstr "%s: Endereço '%s' inválido: %s\n"

#: src/http.c:373
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Falha ao escrever o pedido HTTP: %s.\n"

#: src/http.c:687
msgid "No headers, assuming HTTP/0.9"
msgstr "Sem cabeçalhos, a assumir HTTP/0.9"

#: src/http.c:1204
msgid "Disabling SSL due to encountered errors.\n"
msgstr "A desactivar o SSL devido a erros encontrados.\n"

#: src/http.c:1374
#, c-format
msgid "POST data file `%s' missing: %s\n"
msgstr "Ficheiro de dados POST '%s' em falta: %s\n"

#: src/http.c:1423
#, c-format
msgid "Reusing existing connection to %s:%d.\n"
msgstr "A reutilizar a conexão existente com %s:%d.\n"

#: src/http.c:1492
#, c-format
msgid "Failed reading proxy response: %s\n"
msgstr "Falha ao ler a resposta do procurador ('proxy'): %s\n"

#: src/http.c:1512
#, c-format
msgid "Proxy tunneling failed: %s"
msgstr "Falhou o 'túnel' com o procurador ('proxy'): %s"

#: src/http.c:1557
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "Pedido %s enviado, a aguardar resposta..."

#: src/http.c:1568
msgid "No data received.\n"
msgstr "Nenhuns dados recebidos.\n"

#: src/http.c:1575
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Erro de leitura (%s) nos cabeçalhos.\n"

#. If the authentication header is missing or
#. unrecognized, there's no sense in retrying.
#: src/http.c:1660
msgid "Unknown authentication scheme.\n"
msgstr "Esquema de autenticação desconhecido.\n"

#: src/http.c:1684
msgid "Authorization failed.\n"
msgstr "A autorização falhou.\n"

#: src/http.c:1698
msgid "Malformed status line"
msgstr "Linha de estado mal-formada"

#: src/http.c:1700
msgid "(no description)"
msgstr "(sem descrição)"

#: src/http.c:1763
#, c-format
msgid "Location: %s%s\n"
msgstr "Localização: %s%s\n"

#: src/http.c:1764 src/http.c:1871
msgid "unspecified"
msgstr "não especificado"

#: src/http.c:1765
msgid " [following]"
msgstr " [a seguir]"

#. If `-c' is in use and the file has been fully downloaded (or
#. the remote file has shrunk), Wget effectively requests bytes
#. after the end of file and the server response with 416.
#: src/http.c:1821
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"     O ficheiro já está todo transferido; nada para fazer.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1851
msgid "Length: "
msgstr "Tamanho: "

#: src/http.c:1871
msgid "ignored"
msgstr "ignorado"

#: src/http.c:2019
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Aviso: carácteres de expansão ('wildcards') não suportados no HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:2054
#, c-format
msgid ""
"File `%s' already there; not retrieving.\n"
"\n"
msgstr ""
"O ficheiro '%s' já existe, a não transferir.\n"
"\n"

#: src/http.c:2244
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Não é possível escrever para '%s' (%s).\n"

#. Another fatal error.
#: src/http.c:2251
msgid "Unable to establish SSL connection.\n"
msgstr "Incapaz de estabelecer a conexão SSL.\n"

#: src/http.c:2260
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "ERRO: Redireccionamento (%d) sem localização.\n"

#: src/http.c:2290
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s ERRO %d: %s.\n"

#: src/http.c:2303
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Falta o último cabeçalho modificado -- selos temporais desactivados.\n"

#: src/http.c:2311
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Último cabeçalho modificado inválido -- selo temporal ignorado.\n"

#: src/http.c:2334
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"O ficheiro do servidor não é mais recente que o ficheiro local '%s' -- a não transferir.\n"
"\n"

#: src/http.c:2342
#, c-format
msgid "The sizes do not match (local %s) -- retrieving.\n"
msgstr "Os tamanhos não coincidem (local %s) -- a transferir.\n"

#: src/http.c:2347
msgid "Remote file is newer, retrieving.\n"
msgstr "O ficheiro remoto é mais recente, a transferir.\n"

#: src/http.c:2389 src/http.c:2455
#, c-format
msgid ""
"%s (%s) - `%s' saved [%s/%s]\n"
"\n"
msgstr ""
"%s (%s) - '%s' gravado [%s/%s]\n"
"\n"

#: src/http.c:2446
#, c-format
msgid "%s (%s) - Connection closed at byte %s. "
msgstr "%s (%s) - Conexão fechada ao byte %s. "

#: src/http.c:2481
#, c-format
msgid "%s (%s) - Connection closed at byte %s/%s. "
msgstr "%s (%s) - Conexão fechada ao byte %s/%s. "

#: src/http.c:2495
#, c-format
msgid "%s (%s) - Read error at byte %s (%s)."
msgstr "%s (%s) - Erro de leitura no byte %s (%s)."

#: src/http.c:2505
#, c-format
msgid "%s (%s) - Read error at byte %s/%s (%s). "
msgstr "%s (%s) - Erro de leitura no byte %s/%s (%s). "

#: src/init.c:369
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC aponta para %s, o qual não existe.\n"

#: src/init.c:433 src/netrc.c:277
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Não é possível ler %s (%s).\n"

#: src/init.c:451
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Erro em %s na linha %d.\n"

#: src/init.c:457
#, c-format
msgid "%s: Syntax error in %s at line %d.\n"
msgstr "%s: Erro de sintaxe em %s na linha %d.\n"

#: src/init.c:462
#, c-format
msgid "%s: Unknown command `%s' in %s at line %d.\n"
msgstr "%s: Comando desconhecido '%s' em %s na linha %d.\n"

#: src/init.c:507
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Aviso: Ambos o ficheiro de sistema e de utilizador wgetrc apontam para '%s'.\n"

#: src/init.c:661
#, c-format
msgid "%s: Invalid --execute command `%s'\n"
msgstr "%s: Comando --execute '%s' inválido\n"

#: src/init.c:707
#, c-format
msgid "%s: %s: Invalid boolean `%s'; use `on' or `off'.\n"
msgstr "%s: %s: Valor lógico '%s' inválido; use 'on' ou 'off'.\n"

#: src/init.c:759
#, c-format
msgid ""
"%s: %s: Invalid extended boolean `%s';\n"
"use one of `on', `off', `always', or `never'.\n"
msgstr ""
"%s: %s: Valor lógico extendido '%s' inválido;\n"
"use 'always', 'on', 'off' ou 'never'.\n"

#: src/init.c:777
#, c-format
msgid "%s: %s: Invalid number `%s'.\n"
msgstr "%s: %s: Número '%s' inválido.\n"

#: src/init.c:1008 src/init.c:1027
#, c-format
msgid "%s: %s: Invalid byte value `%s'\n"
msgstr "%s: %s: Valor de byte '%s' inválido\n"

#: src/init.c:1052
#, c-format
msgid "%s: %s: Invalid time period `%s'\n"
msgstr "%s: %s Período de tempo '%s' inválido\n"

#: src/init.c:1106 src/init.c:1196 src/init.c:1291 src/init.c:1316
#, c-format
msgid "%s: %s: Invalid value `%s'.\n"
msgstr "%s: %s: Valor '%s' inválido.\n"

#: src/init.c:1143
#, c-format
msgid "%s: %s: Invalid header `%s'.\n"
msgstr "%s: %s: Cabeçãlho '%s' inválido.\n"

#: src/init.c:1208
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Tipo de progresso '%s' inválido.\n"

#: src/init.c:1259
#, c-format
msgid "%s: %s: Invalid restriction `%s', use `unix' or `windows'.\n"
msgstr "%s: %s: Restrição '%s' inválida, use 'unix' ou 'windows'.\n"

#: src/log.c:806
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""
"\n"
"%s recebido, a redireccionar saída para '%s'.\n"

#. Eek!  Opening the alternate log file has failed.  Nothing we
#. can do but disable printing completely.
#: src/log.c:816
#, c-format
msgid ""
"\n"
"%s received.\n"
msgstr ""
"\n"
"%s recebido.\n"

#: src/log.c:817
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; a desactivar registo.\n"

#: src/main.c:375
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Utilização: %s [OPÇÃO]... [ENDEREÇO]...\n"

#: src/main.c:387
msgid ""
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"Argumentos mandatórios para opções longas são também mandatórios para opções curtas.\n"
"\n"

#: src/main.c:389
msgid "Startup:\n"
msgstr "Arranque:\n"

#: src/main.c:391
msgid "  -V,  --version           display the version of Wget and exit.\n"
msgstr "  -V,  --version           exibir a versão do Wget e terminar.\n"

#: src/main.c:393
msgid "  -h,  --help              print this help.\n"
msgstr "  -h,  --help              exibir esta ajuda.\n"

#: src/main.c:395
msgid "  -b,  --background        go to background after startup.\n"
msgstr "  -b,  --background        executar em segundo plano após o arranque.\n"

#: src/main.c:397
msgid "  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
msgstr "  -e,  --execute=COMANDO   executar um comando do estilo '.wgetrc'.\n"

#: src/main.c:401
msgid "Logging and input file:\n"
msgstr "Registo e ficheiro de entrada:\n"

#: src/main.c:403
msgid "  -o,  --output-file=FILE    log messages to FILE.\n"
msgstr "  -o,  --output-file=FICH    registar mensagens em FICH.\n"

#: src/main.c:405
msgid "  -a,  --append-output=FILE  append messages to FILE.\n"
msgstr "  -a,  --append-output=FICH  acrescentar mensagens a FICH.\n"

#: src/main.c:408
msgid "  -d,  --debug               print lots of debugging information.\n"
msgstr "  -d,  --debug               exibir informação de depuração.\n"

#: src/main.c:411
msgid "  -q,  --quiet               quiet (no output).\n"
msgstr "  -q,  --quiet               modo silencioso.\n"

#: src/main.c:413
msgid "  -v,  --verbose             be verbose (this is the default).\n"
msgstr "  -v,  --verbose             modo verboso (activado por omissão).\n"

#: src/main.c:415
msgid "  -nv, --no-verbose          turn off verboseness, without being quiet.\n"
msgstr "  -nv, --no-verbose          desactivar a verbosidade, sem silenciar.\n"

#: src/main.c:417
msgid "  -i,  --input-file=FILE     download URLs found in FILE.\n"
msgstr "  -i,  --input-file=FICH     transferir endereços contidos em FICH.\n"

#: src/main.c:419
msgid "  -F,  --force-html          treat input file as HTML.\n"
msgstr "  -F,  --force-html          tratar o ficheiro de entrada como HTML.\n"

#: src/main.c:421
msgid "  -B,  --base=URL            prepends URL to relative links in -F -i file.\n"
msgstr "  -B,  --base=URL            acrescenta URL a ligações relativas no ficheiro -F -i.\n"

#: src/main.c:425
msgid "Download:\n"
msgstr "Transferência:\n"

#: src/main.c:427
msgid "  -t,  --tries=NUMBER            set number of retries to NUMBER (0 unlimits).\n"
msgstr "  -t,  --tries=NÚMERO            definir NÚMERO de tentativas (0 para ilimitado).\n"

#: src/main.c:429
msgid "       --retry-connrefused       retry even if connection is refused.\n"
msgstr "       --retry-connrefused       tentar de novo se a conexão for recusada.\n"

#: src/main.c:431
msgid "  -O,  --output-document=FILE    write documents to FILE.\n"
msgstr "  -O,  --output-document=FICH    escrever documentos para FICH.\n"

#: src/main.c:433
msgid ""
"  -nc, --no-clobber              skip downloads that would download to\n"
"                                 existing files.\n"
msgstr ""
"  -nc, --no-clobber              saltar transferências que sobreporiam\n"
"                                 ficheiros existentes.\n"

#: src/main.c:436
msgid "  -c,  --continue                resume getting a partially-downloaded file.\n"
msgstr "  -c,  --continue                continuar transferência parcial de ficheiro.\n"

#: src/main.c:438
msgid "       --progress=TYPE           select progress gauge type.\n"
msgstr "       --progress=TIPO           definir o TIPO de escala de progresso.\n"

#: src/main.c:440
msgid ""
"  -N,  --timestamping            don't re-retrieve files unless newer than\n"
"                                 local.\n"
msgstr ""
"  -N,  --timestamping            não transferir ficheiros de novo mais antigos\n"
"                                 que o local.\n"

#: src/main.c:443
msgid "  -S,  --server-response         print server response.\n"
msgstr "  -S,  --server-response         exibir a resposta do servidor.\n"

#: src/main.c:445
msgid "       --spider                  don't download anything.\n"
msgstr "       --spider                  não transferir os ficheiros.\n"

#: src/main.c:447
msgid "  -T,  --timeout=SECONDS         set all timeout values to SECONDS.\n"
msgstr "  -T,  --timeout=SEGUNDOS        definir tempo máximo de todas as tentativas.\n"

#: src/main.c:449
msgid "       --dns-timeout=SECS        set the DNS lookup timeout to SECS.\n"
msgstr "       --dns-timeout=SEGS        definir o tempo máximo de pesquisa.\n"

#: src/main.c:451
msgid "       --connect-timeout=SECS    set the connect timeout to SECS.\n"
msgstr "       --connect-timeout=SEGS    definir o tempo máximo de conexão.\n"

#: src/main.c:453
msgid "       --read-timeout=SECS       set the read timeout to SECS.\n"
msgstr "       --read-timeout=SEGS       definir o tempo máximo de leitura.\n"

#: src/main.c:455
msgid "  -w,  --wait=SECONDS            wait SECONDS between retrievals.\n"
msgstr "  -w,  --wait=SEGUNDOS           esperar SEGUNDOS entre transferências.\n"

#: src/main.c:457
msgid "       --waitretry=SECONDS       wait 1..SECONDS between retries of a retrieval.\n"
msgstr "       --waitretry=SEGUNDOS      esperar 1..SEGUNDOS entre tentativas.\n"

#: src/main.c:459
msgid "       --random-wait             wait from 0...2*WAIT secs between retrievals.\n"
msgstr "       --random-wait             esperar de 0...2*N segundos entre transf.\n"

#: src/main.c:461
msgid "  -Y,  --proxy                   explicitly turn on proxy.\n"
msgstr "  -Y,  --proxy                   activar procurador ('proxy') implicitamente.\n"

#: src/main.c:463
msgid "       --no-proxy                explicitly turn off proxy.\n"
msgstr "       --no-proxy                desativar procurador ('proxy') implicitamente.\n"

#: src/main.c:465
msgid "  -Q,  --quota=NUMBER            set retrieval quota to NUMBER.\n"
msgstr "  -Q,  --quota=NUMERO            definir quota de transferência NÚMERO.\n"

#: src/main.c:467
msgid "       --bind-address=ADDRESS    bind to ADDRESS (hostname or IP) on local host.\n"
msgstr "       --bind-address=ENDEREÇO   ligar a ENDEREÇO (nome ou IP) na máquina local.\n"

#: src/main.c:469
msgid "       --limit-rate=RATE         limit download rate to RATE.\n"
msgstr "       --limit-rate=TAXA         limitar TAXA de transferência.\n"

#: src/main.c:471
msgid "       --no-dns-cache            disable caching DNS lookups.\n"
msgstr "       --no-dns-cache            desactivar esconderijo ('cache') de pesquisas DNS.\n"

#: src/main.c:473
msgid "       --restrict-file-names=OS  restrict chars in file names to ones OS allows.\n"
msgstr "       --restrict-file-names=OS  restringir a caracteres do sistema para nomes de ficheiros.\n"

#: src/main.c:476
msgid "  -4,  --inet4-only              connect only to IPv4 addresses.\n"
msgstr "  -4,  --inet4-only              conectar apenas a endereços IPv4.\n"

#: src/main.c:478
msgid "  -6,  --inet6-only              connect only to IPv6 addresses.\n"
msgstr "  -6,  --inet6-only              conectar apenas a endereços IPv6.\n"

#: src/main.c:480
msgid ""
"       --prefer-family=FAMILY    connect first to addresses of specified family,\n"
"                                 one of IPv6, IPv4, or none.\n"
msgstr ""
"       --prefer-family=FAMÍLIA   conectar primeiro a endereços da família especificada,\n"
"                                 um de IPv6, IPv4 ou nenhum.\n"

#: src/main.c:484
msgid "       --user=USER               set both ftp and http user to USER.\n"
msgstr "       --user=UTILIZADOR         definir UTILIZADOR FTP e HTTP.\n"

#: src/main.c:486
msgid "       --password=PASS           set both ftp and http password to PASS.\n"
msgstr "       --password=SENHA          definir a SENHA FTP e HTTP.\n"

#: src/main.c:490
msgid "Directories:\n"
msgstr "Pastas:\n"

#: src/main.c:492
msgid "  -nd, --no-directories           don't create directories.\n"
msgstr "  -nd, --no-directories           não criar pastas.\n"

#: src/main.c:494
msgid "  -x,  --force-directories        force creation of directories.\n"
msgstr "  -x,  --force-directories        forçar a criação de pastas.\n"

#: src/main.c:496
msgid "  -nH, --no-host-directories      don't create host directories.\n"
msgstr "  -nH, --no-host-directories      não criar pastas do servidor.\n"

#: src/main.c:498
msgid "       --protocol-directories     use protocol name in directories.\n"
msgstr "       --protocol-directories     usar o nome do protocolo nas pastas.\n"

#: src/main.c:500
msgid "  -P,  --directory-prefix=PREFIX  save files to PREFIX/...\n"
msgstr "  -P,  --directory-prefix=PREFIX  gravar ficheiros para PREFIX/...\n"

#: src/main.c:502
msgid "       --cut-dirs=NUMBER          ignore NUMBER remote directory components.\n"
msgstr "       --cut-dirs=NÚMERO          ignorar NÚMERO componentes de pasta remotos.\n"

#: src/main.c:506
msgid "HTTP options:\n"
msgstr "Opções HTTP:\n"

#: src/main.c:508
msgid "       --http-user=USER        set http user to USER.\n"
msgstr "       --http-user=UTILIZADOR  definir o UTILIZADOR HTTP.\n"

#: src/main.c:510
msgid "       --http-password=PASS    set http password to PASS.\n"
msgstr "       --http-password=SENHA   definir a SENHA HTTP.\n"

#: src/main.c:512
msgid "       --no-cache              disallow server-cached data.\n"
msgstr "       --no-cache              não permitir dados em esconderijo ('cache') no servidor.\n"

#: src/main.c:514
msgid "  -E,  --html-extension        save HTML documents with `.html' extension.\n"
msgstr "  -E,  --html-extension        gravar documentos HTML com extensão '.html'.\n"

#: src/main.c:516
msgid "       --ignore-length         ignore `Content-Length' header field.\n"
msgstr "       --ignore-length         ignorar campo de cabeçalho `Content-Length'.\n"

#: src/main.c:518
msgid "       --header=STRING         insert STRING among the headers.\n"
msgstr "       --header=EXPRESSÃO      inserir EXPRESSÃO entre os cabeçalhos.\n"

#: src/main.c:520
msgid "       --proxy-user=USER       set USER as proxy username.\n"
msgstr "       --proxy-user=UTILIZAD   definir UTILIZADor do procurador ('proxy').\n"

#: src/main.c:522
msgid "       --proxy-password=PASS   set PASS as proxy password.\n"
msgstr "       --proxy-password=SENHA  definir SENHA do procurador ('proxy').\n"

#: src/main.c:524
msgid "       --referer=URL           include `Referer: URL' header in HTTP request.\n"
msgstr "       --referer=ENDEREÇO      incluir o cabeçalho 'Referer: ENDEREÇO' no pedido.\n"

#: src/main.c:526
msgid "       --save-headers          save the HTTP headers to file.\n"
msgstr "       --save-headers          gravar os cabeçalhos HTTP no ficheiro.\n"

#: src/main.c:528
msgid "  -U,  --user-agent=AGENT      identify as AGENT instead of Wget/VERSION.\n"
msgstr "  -U,  --user-agent=AGENTE     identificar como AGENTE ao invés de Wget/VERSÃO.\n"

#: src/main.c:530
msgid "       --no-http-keep-alive    disable HTTP keep-alive (persistent connections).\n"
msgstr "       --no-http-keep-alive    desactivar 'HTTP keep-alive' (conexões persistentes).\n"

#: src/main.c:532
msgid "       --no-cookies            don't use cookies.\n"
msgstr "       --no-cookies            não usar 'cookies'.\n"

#: src/main.c:534
msgid "       --load-cookies=FILE     load cookies from FILE before session.\n"
msgstr "       --load-cookies=FICH     carregar 'cookies' de FICHeiro antes da sessão.\n"

#: src/main.c:536
msgid "       --save-cookies=FILE     save cookies to FILE after session.\n"
msgstr "       --save-cookies=FICH     gravar 'cookies' para FICHeiro após a sessão.\n"

#: src/main.c:538
msgid "       --keep-session-cookies  load and save session (non-permanent) cookies.\n"
msgstr "       --keep-session-cookies  carregar e gravar os 'cookies' da sessão (não permanentes).\n"

#: src/main.c:540
msgid "       --post-data=STRING      use the POST method; send STRING as the data.\n"
msgstr "       --post-data=EXPRESSÃO   usar o método POST; enviar EXPRESSÃO como dados.\n"

#: src/main.c:542
msgid "       --post-file=FILE        use the POST method; send contents of FILE.\n"
msgstr "       --post-file=FICHEIRO    usar o método POST; enviar conteúdo de FICHEIRO.\n"

#: src/main.c:547
msgid "HTTPS (SSL/TLS) options:\n"
msgstr "Opções HTTPS (SSL/TLS):\n"

#: src/main.c:549
msgid ""
"       --secure-protocol=PR     choose secure protocol, one of auto, SSLv2,\n"
"                                SSLv3, and TLSv1.\n"
msgstr ""
"       --secure-protocol=PR     escolher protocolo de segurança, auto, SSLv2,\n"
"                                SSLv3 ou TLSv1.\n"

#: src/main.c:552
msgid "       --no-check-certificate   don't validate the server's certificate.\n"
msgstr "       --no-check-certificate   não validar o certificado do servidor.\n"

#: src/main.c:554
msgid "       --certificate=FILE       client certificate file.\n"
msgstr "       --certificate=FICH       FICHeiro do certificado do cliente.\n"

#: src/main.c:556
msgid "       --certificate-type=TYPE  client certificate type, PEM or DER.\n"
msgstr "       --certificate-type=TIPO  TIPO do certificado do cliente, PEM ou DER.\n"

#: src/main.c:558
msgid "       --private-key=FILE       private key file.\n"
msgstr "       --private-key=FICHEIRO   FICHEIRO da chave privada.\n"

#: src/main.c:560
msgid "       --private-key-type=TYPE  private key type, PEM or DER.\n"
msgstr "       --private-key-type=TIPO  TIPO da chave privada, PEM ou DER.\n"

#: src/main.c:562
msgid "       --ca-certificate=FILE    file with the bundle of CA's.\n"
msgstr "       --ca-certificate=FICH    FICHeiro com CAs.\n"

#: src/main.c:564
msgid "       --ca-directory=DIR       directory where hash list of CA's is stored.\n"
msgstr "       --ca-directory=PASTA     PASTA da lista de chaves de CAs.\n"

#: src/main.c:566
msgid "       --random-file=FILE       file with random data for seeding the SSL PRNG.\n"
msgstr "       --random-file=FICH       FICHeiro com dados aleatórios para SSL PRNG.\n"

#: src/main.c:568
msgid "       --egd-file=FILE          file naming the EGD socket with random data.\n"
msgstr "       --egd-file=FICHEIRO      FICHEIRO EGD com dados aleatórios.\n"

#: src/main.c:573
msgid "FTP options:\n"
msgstr "Opções FTP:\n"

#: src/main.c:575
msgid "       --ftp-user=USER         set ftp user to USER.\n"
msgstr "       --ftp-user=UTILIZADOR   definir UTILIZADOR FTP.\n"

#: src/main.c:577
msgid "       --ftp-password=PASS     set ftp password to PASS.\n"
msgstr "       --ftp-password=SENHA    definir a SENHA FTP.\n"

#: src/main.c:579
msgid "       --no-remove-listing     don't remove `.listing' files.\n"
msgstr "       --no-remove-listing     não remover ficheiros '.listing'.\n"

#: src/main.c:581
msgid "       --no-glob               turn off FTP file name globbing.\n"
msgstr "       --no-glob               desactivar alterações de nome de ficheiros FTP.\n"

#: src/main.c:583
msgid "       --no-passive-ftp        disable the \"passive\" transfer mode.\n"
msgstr "       --no-passive-ftp        desactivar o modo passivo de transferência.\n"

#: src/main.c:585
msgid "       --retr-symlinks         when recursing, get linked-to files (not dir).\n"
msgstr "       --retr-symlinks         em recursividade, obter ficheiros ligados (não pastas).\n"

#: src/main.c:587
msgid "       --preserve-permissions  preserve remote file permissions.\n"
msgstr "       --preserve-permissions  preservar as permissões dos ficheiros remotos.\n"

#: src/main.c:591
msgid "Recursive download:\n"
msgstr "Transferência recursiva:\n"

#: src/main.c:593
msgid "  -r,  --recursive          specify recursive download.\n"
msgstr "  -r,  --recursive          especificar transferência recursiva.\n"

#: src/main.c:595
msgid "  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
msgstr "  -l,  --level=NÚMERO       profundidade máxima (inf ou 0 para infinito).\n"

#: src/main.c:597
msgid "       --delete-after       delete files locally after downloading them.\n"
msgstr "       --delete-after       remover os ficheiros localmente após transferência.\n"

#: src/main.c:599
msgid "  -k,  --convert-links      make links in downloaded HTML point to local files.\n"
msgstr "  -k,  --convert-links      apontar as ligações em HTML para ficheiros locais.\n"

#: src/main.c:601
msgid "  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
msgstr "  -K,  --backup-converted   salvaguardar com extensão '.orig' antes de converter.\n"

#: src/main.c:603
msgid "  -m,  --mirror             shortcut for -N -r -l inf --no-remove-listing.\n"
msgstr "  -m,  --mirror             atalho para -N -r -l inf --no-remove-listing.\n"

#: src/main.c:605
msgid "  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
msgstr "  -p,  --page-requisites    obter todas as imagens, etc. para exibir a página HTML.\n"

#: src/main.c:607
msgid "       --strict-comments    turn on strict (SGML) handling of HTML comments.\n"
msgstr "       --strict-comments    activar tratamento severo (SGML) de comentários HTML.\n"

#: src/main.c:611
msgid "Recursive accept/reject:\n"
msgstr "Aceitação/Rejeitação recursiva:\n"

#: src/main.c:613
msgid "  -A,  --accept=LIST               comma-separated list of accepted extensions.\n"
msgstr "  -A,  --accept=LISTA              LISTA de extensões aceites separadas por vírgula.\n"

#: src/main.c:615
msgid "  -R,  --reject=LIST               comma-separated list of rejected extensions.\n"
msgstr "  -R,  --reject=LISTA              LISTA de extensões rejeitadas.\n"

#: src/main.c:617
msgid "  -D,  --domains=LIST              comma-separated list of accepted domains.\n"
msgstr "  -D,  --domains=LISTA             LISTA de domínios aceites.\n"

#: src/main.c:619
msgid "       --exclude-domains=LIST      comma-separated list of rejected domains.\n"
msgstr "       --exclude-domains=LISTA     LISTA de domínios rejeitados.\n"

#: src/main.c:621
msgid "       --follow-ftp                follow FTP links from HTML documents.\n"
msgstr "       --follow-ftp                seguir ligações FTP de documentos HTML.\n"

#: src/main.c:623
msgid "       --follow-tags=LIST          comma-separated list of followed HTML tags.\n"
msgstr "       --follow-tags=LISTA         LISTA de elementos HTML para seguir.\n"

#: src/main.c:625
msgid "       --ignore-tags=LIST          comma-separated list of ignored HTML tags.\n"
msgstr "       --ignore-tags=LISTA         LISTA de elementos HTML para ignorar.\n"

#: src/main.c:627
msgid "  -H,  --span-hosts                go to foreign hosts when recursive.\n"
msgstr "  -H,  --span-hosts                ir para outros servidores quando recursivo.\n"

#: src/main.c:629
msgid "  -L,  --relative                  follow relative links only.\n"
msgstr "  -L,  --relative                  seguir apenas ligações relativas.\n"

#: src/main.c:631
msgid "  -I,  --include-directories=LIST  list of allowed directories.\n"
msgstr "  -I,  --include-directories=LISTA LISTA de pastas permitidas.\n"

#: src/main.c:633
msgid "  -X,  --exclude-directories=LIST  list of excluded directories.\n"
msgstr "  -X,  --exclude-directories=LISTA LISTA de pastas excluídas.\n"

#: src/main.c:635
msgid "  -np, --no-parent                 don't ascend to the parent directory.\n"
msgstr "  -np, --no-parent                 não ascender à pasta anterior.\n"

#: src/main.c:639
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Envie erros e sugestões para <bug-wget@gnu.org>.\n"

#: src/main.c:644
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, um transferidor de rede não interactivo.\n"

#: src/main.c:658
msgid "Copyright (C) 2005 Free Software Foundation, Inc.\n"
msgstr "Copyright (C) 2005 Free Software Foundation Inc.\n"

#: src/main.c:660
msgid ""
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Este programa é distribuído na esperança que seja útil,\n"
"mas SEM QUALQUER GARANTIA; sem sequer a garantia implícita de\n"
"COMERCIALIZAÇÃO ou SERVIÇO DE PROPÓSITO PARTICULAR. Veja a\n"
"Licença Pública Geral GNU para mais detalhes.\n"

#: src/main.c:665
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Originalmente escrito por Hrvoje Niksic <hniksic@xemacs.org>.\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:711 src/main.c:780 src/main.c:859
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Tente '%s --help' para mais opções.\n"

#: src/main.c:777
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: opção ilegal -- '-n%c'\n"

#: src/main.c:830
#, c-format
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Não é possível ser simultaneamente verboso e silencioso.\n"

#: src/main.c:836
#, c-format
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Não é possível marcar com selo temporal e sobrepor ficheiros antigos, simultaneamente.\n"

#: src/main.c:844
#, c-format
msgid "Cannot specify both --inet4-only and --inet6-only.\n"
msgstr "Não é possível especificar simultaneamente --inet4-only e --inet6-only.\n"

#. No URL specified.
#: src/main.c:854
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL em falta\n"

#: src/main.c:963
#, c-format
msgid "No URLs found in %s.\n"
msgstr "URLs não encontrados em %s.\n"

#: src/main.c:972
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"TERMINADO --%s--\n"
"Transferência: %s bytes em %d ficheiros\n"

#: src/main.c:979
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Quota de transferência (%s bytes) EXCEDIDA!\n"

#: src/mswindows.c:235
#, c-format
msgid "Continuing in background.\n"
msgstr "A continuar em segundo plano (fundo).\n"

#: src/mswindows.c:427
#, c-format
msgid "Continuing in background, pid %lu.\n"
msgstr "A continuar em segundo plano, pid %lu.\n"

#: src/mswindows.c:429 src/utils.c:351
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Resultados serão gravados em '%s'.\n"

#: src/mswindows.c:597 src/mswindows.c:604
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: 'socket driver' utilizável não encontrado.\n"

#: src/netrc.c:385
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: aviso: \"%s\" expressão aparece antes de qualquer nome de máquina\n"

#: src/netrc.c:416
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: expressão desconhecida \"%s\"\n"

#: src/netrc.c:480
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Utilização: %s NETRC [NOME-DA-MÁQUINA]\n"

#: src/netrc.c:490
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: não é possível analisar %s: %s\n"

#. Still not random enough, presumably because neither /dev/random
#. nor EGD were available.  Try to seed OpenSSL's PRNG with libc
#. PRNG.  This is cryptographically weak and defeats the purpose
#. of using OpenSSL, which is why it is highly discouraged.
#: src/openssl.c:121
msgid "WARNING: using a weak random seed.\n"
msgstr "AVISO: a usar uma semente aleatória fraca.\n"

#: src/openssl.c:181
msgid "Could not seed PRNG; consider using --random-file.\n"
msgstr "Não foi possível gerar PRNG; considere usar --random-file.\n"

#. If the user has specified --no-check-cert, we still want to warn
#. him about problems with the server's certificate.
#: src/openssl.c:419
msgid "ERROR"
msgstr "ERRO"

#: src/openssl.c:419
msgid "WARNING"
msgstr "AVISO"

#: src/openssl.c:427
#, c-format
msgid "%s: No certificate presented by %s.\n"
msgstr "%s: Certificado não apresentado por %s.\n"

#: src/openssl.c:458
#, c-format
msgid "%s: Certificate verification error for %s: %s\n"
msgstr "%s: Erro de verificação de certificado para %s: %s\n"

#: src/openssl.c:485
#, c-format
msgid "%s: certificate common name `%s' doesn't match requested host name `%s'.\n"
msgstr "%s: o nome do certificado '%s' não corresponde ao nome da máquina requerida '%s'.\n"

#: src/openssl.c:498
#, c-format
msgid "To connect to %s insecurely, use `--no-check-certificate'.\n"
msgstr "Para conectar a %s de forma insegura, use '--no-check-certificate'.\n"

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:243
#, c-format
msgid ""
"\n"
"%*s[ skipping %dK ]"
msgstr ""
"\n"
"%*s[ a saltar %dK ]"

#: src/progress.c:410
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Especificação de estilo de ponto '%s' inválida; a não alterar.\n"

#. If no clock was found, it means that clock_getres failed for
#. the realtime clock.
#: src/ptimer.c:176
#, c-format
msgid "Cannot get REALTIME clock frequency: %s\n"
msgstr "Não é possível obter a frequência de relógio de tempo real: %s\n"

#: src/recur.c:377
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "A remover %s, uma vez que deveria ser rejeitado.\n"

#: src/res.c:394
#, c-format
msgid "Cannot open %s: %s"
msgstr "Não é possível abrir %s: %s"

#: src/res.c:544
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "A carregar robots.txt; por favor, ignore erros.\n"

#: src/retr.c:645
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Erro ao analisar URL %s do 'proxy': %s.\n"

#: src/retr.c:653
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Erro no URL %s do 'proxy': Necessita ser HTTP.\n"

#: src/retr.c:740
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "%d redireccionamentos excedidos.\n"

#: src/retr.c:865
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"A desistir.\n"
"\n"

#: src/retr.c:865
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"A tentar novamente.\n"
"\n"

#: src/url.c:626
msgid "No error"
msgstr "Sem erros"

#: src/url.c:628
msgid "Unsupported scheme"
msgstr "Esquema não suportado"

#: src/url.c:630
msgid "Invalid host name"
msgstr "Nome de máquina inválido"

#: src/url.c:632
msgid "Bad port number"
msgstr "Mau número de porto"

#: src/url.c:634
msgid "Invalid user name"
msgstr "Nome de utilizador inválido"

#: src/url.c:636
msgid "Unterminated IPv6 numeric address"
msgstr "Endereço numérico IPv6 não concluído"

#: src/url.c:638
msgid "IPv6 addresses not supported"
msgstr "Endereços IPv6 não suportados"

#: src/url.c:640
msgid "Invalid IPv6 numeric address"
msgstr "Endereço numérico IPv6 inválido"

#. parent, no error
#: src/utils.c:349
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "A continuar em segundo plano (fundo), pid %d.\n"

#: src/utils.c:397
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Erro ao remover ligação simbólica '%s': %s\n"

#: src/xmalloc.c:72
#, c-format
msgid "%s: %s: Failed to allocate %ld bytes; memory exhausted.\n"
msgstr "%s: %s: Falha ao reservar %ld bytes; memória insuficiente.\n"
