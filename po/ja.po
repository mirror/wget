# Japanese messages for GNU Wget.
# Copyright (C) 1998, 2000 Free Software Foundation, Inc.
# Hiroshi Takekawa <takekawa@sr3.t.u-tokyo.ac.jp>, 2000
# Originally translated by Penguin Kun <penguin-kun@geocities.com>, 1998
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 2000-02-22 20:14+09:00\n"
"Last-Translator: Hiroshi Takekawa <takekawa@sr3.t.u-tokyo.ac.jp>\n"
"Language-Team: Japanese <ja@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=EUC-JP\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:147 src/http.c:346
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "%s:%hu に接続しています... "

#: src/ftp.c:169 src/ftp.c:411 src/http.c:363
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "%s:%hu への接続に失敗しました。\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:190 src/http.c:374
msgid "connected!\n"
msgstr "接続しました!\n"

#: src/ftp.c:191
#, c-format
msgid "Logging in as %s ... "
msgstr "%s としてログインしています... "

#: src/ftp.c:200 src/ftp.c:253 src/ftp.c:301 src/ftp.c:353 src/ftp.c:447
#: src/ftp.c:520 src/ftp.c:568 src/ftp.c:616
msgid "Error in server response, closing control connection.\n"
msgstr "サーバの応答にエラーがあるので、接続を終了します。\n"

#: src/ftp.c:208
msgid "Error in server greeting.\n"
msgstr "サーバの初期応答にエラーがあります。\n"

#: src/ftp.c:216 src/ftp.c:262 src/ftp.c:310 src/ftp.c:362 src/ftp.c:457
#: src/ftp.c:530 src/ftp.c:578 src/ftp.c:626
msgid "Write failed, closing control connection.\n"
msgstr "書き込みに失敗したので、接続を終了します。\n"

#: src/ftp.c:223
msgid "The server refuses login.\n"
msgstr "サーバがログインを拒否しました。\n"

#: src/ftp.c:230
msgid "Login incorrect.\n"
msgstr "ログインに失敗しました。\n"

#: src/ftp.c:237
msgid "Logged in!\n"
msgstr "ログインしました!\n"

#: src/ftp.c:270
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "`%c' は不明な種類なので、接続を終了します。\n"

#: src/ftp.c:283
msgid "done.  "
msgstr "完了しました。  "

#: src/ftp.c:289
msgid "==> CWD not needed.\n"
msgstr "==> CWD は必要ありません。\n"

#: src/ftp.c:317
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "`%s' というディレクトリはありません。\n\n"

#: src/ftp.c:331 src/ftp.c:599 src/ftp.c:647 src/url.c:1431
msgid "done.\n"
msgstr "完了しました。\n"

#. do not CWD
#: src/ftp.c:335
msgid "==> CWD not required.\n"
msgstr "==> CWD は必要ありません。\n"

#: src/ftp.c:369
msgid "Cannot initiate PASV transfer.\n"
msgstr "PASV転送の初期化ができません。\n"

#: src/ftp.c:373
msgid "Cannot parse PASV response.\n"
msgstr "PASVの応答を解析できません。\n"

#: src/ftp.c:387
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "%s:%hu への接続を試みています。\n"

#: src/ftp.c:432 src/ftp.c:504 src/ftp.c:548
msgid "done.    "
msgstr "完了しました。    "

#: src/ftp.c:474
#, c-format
msgid "Bind error (%s).\n"
msgstr "バインドエラーです (%s)。\n"

#: src/ftp.c:490
msgid "Invalid PORT.\n"
msgstr "無効なポート番号です。\n"

#: src/ftp.c:537
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nRESTに失敗しました、最初から始めます。\n"

#: src/ftp.c:586
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "`%s' というファイルはありません。\n\n"

#: src/ftp.c:634
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "`%s' というファイルまたはディレクトリはありません。\n\n"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid "Length: %s"
msgstr "長さ: %s"

#: src/ftp.c:694 src/ftp.c:701
#, c-format
msgid " [%s to go]"
msgstr " [のこり %s]"

#: src/ftp.c:703
msgid " (unauthoritative)\n"
msgstr " (必ずしも正確ではありません)\n"

#: src/ftp.c:721
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s、接続を終了します。\n"

#: src/ftp.c:729
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - データ接続: %s; "

#: src/ftp.c:746
msgid "Control connection closed.\n"
msgstr "接続を終了します。\n"

#: src/ftp.c:764
msgid "Data transfer aborted.\n"
msgstr "データ転送を中断しました。\n"

#: src/ftp.c:830
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "ファイル `%s' はすでに存在するので、転送しません。\n"

#: src/ftp.c:896 src/http.c:922
#, c-format
msgid "(try:%2d)"
msgstr "(試行:%2d)"

#: src/ftp.c:955 src/http.c:1116
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' を保存しました [%ld]\n\n"

#: src/ftp.c:1001
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "一時ファイルをリストするために `%s' を使用します。\n"

#: src/ftp.c:1013
#, c-format
msgid "Removed `%s'.\n"
msgstr "`%s' を削除しました。\n"

#: src/ftp.c:1049
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "再帰する深さ %d が最大値を超過しています。深さは %d です。\n"

#: src/ftp.c:1096 src/http.c:1054
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "ローカルファイル `%s' のほうが新しいので、転送しません。\n\n"

#: src/ftp.c:1102 src/http.c:1060
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "大きさが合わないので(ローカルは %ld)、転送します。\n"

#: src/ftp.c:1119
msgid "Invalid name of the symlink, skipping.\n"
msgstr "不正なシンボリックリンク名なので、とばします。\n"

#: src/ftp.c:1136
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "すでに %s -> %s という正しいシンボリックリンクがあります\n\n"

#: src/ftp.c:1144
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "%s -> %s というシンボリックリンクを作成しています\n"

#: src/ftp.c:1155
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "シンボリックリンクに対応していないので、シンボリックリンク `%s' をとばします。\n"

#: src/ftp.c:1167
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "ディレクトリ `%s' をとばします。\n"

#: src/ftp.c:1176
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: 不明なまたは対応していないファイルの種類です。\n"

#: src/ftp.c:1193
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: 日付が壊れています。\n"

#: src/ftp.c:1213
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "深さが %d (最大 %d)なのでディレクトリを転送しません。\n"

#: src/ftp.c:1252
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "除外されているか含まれていないので `%s' に移動しません。\n"

#: src/ftp.c:1297
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "`%s' を除外します。\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1344
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "パターン `%s' に適合するものがありません。\n"

#: src/ftp.c:1404
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "`%s' [%ld]に対するHTML化された見出し(index)を書きました。\n"

#: src/ftp.c:1409
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "`%s' に対するHTML化された見出し(index)を書きました。\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: オプション `%s' は曖昧です\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: オプション `--%s' は引数を必要としません\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: オプション `%c%s' は引数を必要としません\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: オプション `%s' は引数を必要とします\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: `--%s' は認識できないオプションです\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: `%c%s' は認識できないオプションです\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: 不正なオプションです -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: オプションは引数を必要とします -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: user-idを決定できません。\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: 警告: unameに失敗しました: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: 警告: gethostnameに失敗しました\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: 警告: ローカルIPアドレスを決定できません。\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: 警告: ローカルIPアドレスの逆引きができません。\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:511
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: 警告: ローカルアドレスの逆引き結果がFQDNではありません!\n"

#: src/host.c:539
msgid "Host not found"
msgstr "ホストが見つかりません"

#: src/host.c:541
msgid "Unknown error"
msgstr "不明なエラーです"

#: src/html.c:439 src/html.c:441
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s (%s:%d 上)の見出し(index)です"

#: src/html.c:463
msgid "time unknown       "
msgstr "時間が不明です       "

#: src/html.c:467
msgid "File        "
msgstr "ファイル        "

#: src/html.c:470
msgid "Directory   "
msgstr "ディレクトリ   "

#: src/html.c:473
msgid "Link        "
msgstr "リンク        "

#: src/html.c:476
msgid "Not sure    "
msgstr "不確実    "

#: src/html.c:494
#, c-format
msgid " (%s bytes)"
msgstr " (%s バイト)"

#: src/http.c:492
msgid "Failed writing HTTP request.\n"
msgstr "HTTP による接続要求の送信に失敗しました。\n"

#: src/http.c:497
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s による接続要求を送信しました、応答を待っています... "

#: src/http.c:536
msgid "End of file while parsing headers.\n"
msgstr "ヘッダの解析中にファイルの終端になりました。\n"

#: src/http.c:547
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "ヘッダ内で読み込みエラー(%s)です\n"

#: src/http.c:587
msgid "No data received"
msgstr "データが受信されませんでした"

#: src/http.c:589
msgid "Malformed status line"
msgstr "奇妙な状態です"

#: src/http.c:594
msgid "(no description)"
msgstr "(説明なし)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:678
msgid "Authorization failed.\n"
msgstr "認証に失敗しました。\n"

#: src/http.c:685
msgid "Unknown authentication scheme.\n"
msgstr "不明な認証形式です。\n"

#: src/http.c:748
#, c-format
msgid "Location: %s%s\n"
msgstr "場所: %s%s\n"

#: src/http.c:749 src/http.c:774
msgid "unspecified"
msgstr "特定できません"

#: src/http.c:750
msgid " [following]"
msgstr " [続く]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:764
msgid "Length: "
msgstr "長さ: "

#: src/http.c:769
#, c-format
msgid " (%s to go)"
msgstr " (のこり%s)"

#: src/http.c:774
msgid "ignored"
msgstr "無視しました"

#: src/http.c:857
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "警告: HTTPはワイルドカードに対応していません。\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:872
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "ファイル `%s' はすでに存在するので、転送しません。\n"

#: src/http.c:978
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "`%s' (%s)へ書き込めません。\n"

#: src/http.c:988
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "エラー: 場所が存在しないリディレクション(%d)です。\n"

#: src/http.c:1011
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s エラー %d: %s。\n"

#: src/http.c:1023
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Last-modified ヘッダがありません -- 日付を無効にします。\n"

#: src/http.c:1031
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Last-modified ヘッダが無効です -- 日付を無視します。\n"

#: src/http.c:1064
msgid "Remote file is newer, retrieving.\n"
msgstr "リモートファイルのほうが新しいので、転送します。\n"

#: src/http.c:1098
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' を保存しました [%ld/%ld]\n\n"

#: src/http.c:1130
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - %ld バイトで接続が終了しました。 "

#: src/http.c:1138
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' を保存しました [%ld/%ld])\n\n"

#: src/http.c:1150
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - %ld/%ld バイトで接続が終了しました。 "

#: src/http.c:1161
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - %ld バイトで読み込みエラーです (%s)。"

#: src/http.c:1169
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - %ld/%ld バイトで読み込みエラーです (%s)。 "

#: src/init.c:312 src/netrc.c:250
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: %s (%s)を読み込めません。\n"

#: src/init.c:333 src/init.c:339
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: %s 内の %d 行でエラーです\n"

#: src/init.c:370
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: 警告: システムとユーザのwgetrcの両方が `%s' を指定しています。\n"

#: src/init.c:458
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: バグ: `%s' は不明な命令です、値は `%s' です。\n"

#: src/init.c:485
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: onかoffかを特定してください。\n"

#: src/init.c:503 src/init.c:760 src/init.c:782 src/init.c:855
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: 無効な指定 `%s' です。\n"

#: src/init.c:616 src/init.c:638 src/init.c:660 src/init.c:686
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: 無効な指定 `%s' です。\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "使い方: %s [オプション]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, 非対話的ネットワーク転送ソフト\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\n長いオプションで不可欠な引数は短いオプションでも不可欠です。\n\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"起動:\n"
"  -V,  --version           Wgetのバージョン番号を表示し、終了します。\n"
"  -h,  --help              このヘルプを表示します。\n"
"  -b,  --background        起動後バックグラウンドで動作します。\n"
"  -e,  --execute=COMMAND   `.wgetrc' コマンドを実行します。\n"
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
"ログインと入力ファイル:\n"
"  -o,  --output-file=FILE     FILE にログメッセージを書き込みます。\n"
"  -a,  --append-output=FILE   FILE にメッセージを追加します。\n"
"  -d,  --debug                デバッグ情報を表示します。\n"
"  -q,  --quiet                出力しません。\n"
"  -v,  --verbose              詳しい出力をします(標準)。\n"
"  -nv, --non-verbose          抑制された出力をします。\n"
"  -i,  --input-file=FILE      URLをファイルから読み込みます。\n"
"  -F,  --force-html           入力ファイルをHTMLとして扱います。\n"
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
"ダウンロード:\n"
"  -t,  --tries=NUMBER           再試行する回数を指定します (0は無制限)。\n"
"  -O   --output-document=FILE   FILE に文書を出力します。\n"
"  -nc, --no-clobber             既存のファイルを消去しません。\n"
"  -c,  --continue               既にあるファイルの続きから転送を行います。\n"
"       --dot-style=STYLE        ディスプレー形式を指定します。\n"
"  -N,  --timestamping           ローカルより古いファイルは転送しません。\n"
"  -S,  --server-response        サーバの応答を表示します。\n"
"       --spider                 何もダウンロードしません。\n"
"  -T,  --timeout=SECONDS        読み込みタイムアウト時間をSECONDSにします。\n"
"  -w,  --wait=SECONDS           転送ごとに SECONDS 間待ちます。\n"
"  -Y,  --proxy=on/off           代理サーバ(proxy)をon/offにします。\n"
"  -Q,  --quota=NUMBER           容量制限(quota)を NUMBER にします。\n"
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
"ディレクトリ:\n"
"  -nd  --no-directories            ディレクトリを作成しません。\n"
"  -x,  --force-directories         強制的にディレクトリを作成します。\n"
"  -nH, --no-host-directories       ホストディレクトリを作成しません。\n"
"  -P,  --directory-prefix=PREFIX   PREFIXにファイルを保存します。\n"
"       --cut-dirs=NUMBER           NUMBERのリモートディレクトリ\n"
"                                   コンポーネントを無視します。\n"
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
"HTTPオプション:\n"
"       --http-user=USER      httpユーザを USER にします。\n"
"       --http-passwd=PASS    httpパスワードを PASS にします。\n"
"  -C,  --cache=on/off        サーバのキャッシュデータを on/off にします\n"
"                             (通常はonにします)。\n"
"       --ignore-length       ヘッダファイルの `Content-Length' を無視します。\n"
"       --header=STRING       ヘッダに STRING を挿入します。\n"
"       --proxy-user=USER     USER を代理サーバ(proxy)のユーザ名にします。\n"
"       --proxy-passwd=PASS   PASS を代理サーバ(proxy)のパスワードにします。\n"
"  -s,  --save-headers        HTTPヘッダをファイルに保存します。\n"
"  -U,  --user-agent=AGENT    User Agentとして、`Wget/バージョン番号'の代りに\n"
"                             AGENT を使用します。\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTPオプション:\n"
"       --retr-symlinks   FTPのシンボリックリンクを転送します。\n"
"  -g,  --glob=on/off     ファイル名のglobbingをオンまたはオフにします。\n"
"       --passive-ftp     \"passive\" 転送モードを使用します。\n"
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
"再帰的転送:\n"
"  -r,  --recursive             ウェブを再帰的に転送します\n"
"                               -- 注意して使用してください!\n"
"  -l,  --level=NUMBER          再帰する深さを指定します(0は無制限)。\n"
"       --delete-after          ダウンロードしたファイルを削除します。\n"
"  -k,  --convert-links         非相対リンクを相対リンクに変換します。\n"
"  -m,  --mirror                ミラーに適したオプションで動作します。\n"
"  -nr, --dont-remove-listing   `.listing' ファイルを削除しません。\n"
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
"再帰転送時に転送するファイルの許可・不許可\n"
"  -A,  --accept=LIST                許可するファイルのリストを指定します。\n"
"  -R,  --reject=LIST                除外するファイルのリストを指定します。\n"
"  -D,  --domains=LIST               許可するドメインのリストを指定します。\n"
"       --exclude-domains=LIST       除外するドメインのリストをコンマ(,)\n"
"                                    で区切って指定します。\n"
"  -L,  --relative                   相対リンクのみ対応します。\n"
"       --follow-ftp                 HTML文書からのFTPリンクに対応します。\n"
"  -H,  --span-hosts                 再帰時に他のホストへ移動します。\n"
"  -I,  --include-directories=LIST   許可するディレクトリのリストです。\n"
"  -X,  --exclude-directories=LIST   除外するディレクトリのリストです。\n"
"  -nh, --no-host-lookup             ホストに対してDNSを見ません。\n"
"  -np, --no-parent                  親ディレクトリに移動しません。\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "バグ報告や提案は<bug-wget@gnu.org>へ\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: デバックに対応するようにコンパイルされていません。\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
"\n"
"以下は参考訳です。法的には上の英文に従います。\n"
"\n"
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"このプログラムは有用と思われますが無保証です。\n"
"商業性や特定の目的に合致するかの暗黙の保証もありません。\n"
"詳細はGNU一般公用使用許諾をご覧下さい。\n"

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\nHrvoje Niksic <hniksic@srce.hr>によって書かれました。\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: 無効なコマンドです\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: `-n%c' は不正なオプション指定です\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "詳しいオプションは `%s --help' を実行してください。\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "出力を詳細するオプションと出力を抑制されるオプションを同時には指定できません\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "古いファイルに日付を付けなおすことと古いファイルを消去しないことを同時には行えません。\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URLがありません\n"

#: src/main.c:674
#, c-format
msgid "No URLs found in %s.\n"
msgstr "%s にはURLがありません。\n"

#: src/main.c:683
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"終了しました --%s--\n"
"ダウンロード: %s バイト(ファイル数 %d)\n"

#: src/main.c:688
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "容量制限(%s バイトのquota)を超過します!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:715
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s を受信しました、`%%s' に出力をリディレクトします。\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Breakが押されました、`%s' に出力をリディレクションします。\n"
"実行はバックグラウンドで継続します。\n"
"CTRL+ALT+DELETE を押せば、Wget を停止できます。\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:268
msgid "Continuing in background.\n"
msgstr "バックグラウンドで継続します。\n"

#: src/mswindows.c:137 src/utils.c:270
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "出力を `%s' に書き込みます。\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "WinHelp %s を開始します。\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: 使用可能なソケットドライバを見つけられません。\n"

#: src/netrc.c:334
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: 警告: 区切り記号(token) \"%s\" はすべてのマシン名の前に現われます\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: \"%s\" は不明な区切り記号(token)です\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "使い方: %s NETRC [ホスト名]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: %sの情報を取得できません: %s \n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "%s を削除しました。\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "拒否すべきなので、%s を削除しました。\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "robots.txtを読み込んでいます、エラーは無視してください。\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ %dK とばします ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "代理ホスト(proxy host)が見つかりません。\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "代理サーバ(proxy) %s: HTTPである必要があります。\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s は自分自身へのリディレクションです。\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "中止しました。\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "再試行しています。\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "エラー (%s): %s というリンクに対するベースが与えられていません。\n"

#: src/url.c:955
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "エラー(%s): Base URL %s が相対指定で、参照するURL(Referer)が存在しません。\n"

#: src/url.c:1373
#, c-format
msgid "Converting %s... "
msgstr "%s を変換しています... "

#: src/url.c:1378 src/url.c:1389
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "%s 内のリンクを変換できません: %s\n"

#: src/utils.c:71
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: 十分なメモリがありません。\n"

#: src/utils.c:203
msgid "Unknown/unsupported protocol"
msgstr "不明な、または対応していないプロトコルです"

#: src/utils.c:206
msgid "Invalid port specification"
msgstr "無効なポート番号です"

#: src/utils.c:209
msgid "Invalid host name"
msgstr "無効なホスト名です"

#: src/utils.c:430
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "シンボリックリンク `%s' の削除に失敗しました: %s\n"
