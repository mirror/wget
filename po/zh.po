# Chinese translation of GNU wget messages.
# Copyright (C) 1998 Free Software Foundation, Inc.
# Pofeng Lee <pofeng.lee@ms7.url.com.tw>, 1998.
# Originla author CD Chen <cdchen@linux.ntcic.edu.tw>
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.5.3\n"
"POT-Creation-Date: 1998-09-21 19:08+0200\n"
"PO-Revision-Date: 2000-01-14 21:49:32+0800\n"
"Last-Translator: Pofeng Lee <pofeng.lee@ms7.url.com.tw>\n"
"Language-Team: Chinese <zh@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=big5\n"
"Content-Transfer-Encoding: 8bit\n"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:146 src/http.c:337
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "正連往 %s: %hu... "

#: src/ftp.c:168 src/ftp.c:409 src/http.c:354
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "連線到 %s: %hu 被拒絕. \n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:189 src/http.c:365
msgid "connected!\n"
msgstr "連上了!\n"

#: src/ftp.c:190
#, c-format
msgid "Logging in as %s ... "
msgstr "使用 %s 簽入... "

#: src/ftp.c:199 src/ftp.c:251 src/ftp.c:299 src/ftp.c:351 src/ftp.c:445
#: src/ftp.c:518 src/ftp.c:566 src/ftp.c:614
msgid "Error in server response, closing control connection.\n"
msgstr "伺服器端回應時發生錯誤，正在關閉連線控制.\n"

#: src/ftp.c:207
msgid "Error in server greeting.\n"
msgstr "與伺服器連線時發生錯誤.\n"

#: src/ftp.c:214 src/ftp.c:260 src/ftp.c:308 src/ftp.c:360 src/ftp.c:455
#: src/ftp.c:528 src/ftp.c:576 src/ftp.c:624
msgid "Write failed, closing control connection.\n"
msgstr "寫入失敗, 正在關閉連線控制.\n"

#: src/ftp.c:221
msgid "The server refuses login.\n"
msgstr "伺服器拒絕簽入.\n"

#: src/ftp.c:228
msgid "Login incorrect.\n"
msgstr "簽入不正確.\n"

#: src/ftp.c:235
msgid "Logged in!\n"
msgstr "已經簽入了!\n"

#: src/ftp.c:268
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "不明的形式 `%c', 正在關閉連線控制.\n"

#: src/ftp.c:281
msgid "done.  "
msgstr "完成.  "

#: src/ftp.c:287
msgid "==> CWD not needed.\n"
msgstr "==> 不需要 CWD.\n"

#: src/ftp.c:315
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "沒有 `%s' 這個目錄.\n\n"

#: src/ftp.c:329 src/ftp.c:597 src/ftp.c:645 src/url.c:1421
msgid "done.\n"
msgstr "完成.\n"

#. do not CWD
#: src/ftp.c:333
msgid "==> CWD not required.\n"
msgstr "==> 不需要 CWD.\n"

#: src/ftp.c:367
msgid "Cannot initiate PASV transfer.\n"
msgstr "無法啟動 PASV 傳輸.\n"

#: src/ftp.c:371
msgid "Cannot parse PASV response.\n"
msgstr "無法分析 PASV 回應內容.\n"

#: src/ftp.c:385
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "將會繼續嘗試與 %s 連線: %hu.\n"

#: src/ftp.c:472
#, c-format
msgid "Bind error (%s).\n"
msgstr "BIND 錯誤 (%s).\n"

#: src/ftp.c:488
msgid "Invalid PORT.\n"
msgstr "無效的 PORT.\n"

#: src/ftp.c:502 src/ftp.c:546
msgid "done.    "
msgstr "完成.    "

#: src/ftp.c:535
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nRSET 失敗，正由錯亂中開始中.\n"

#: src/ftp.c:584
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "沒有 `%s' 這個檔案.\n\n"

#: src/ftp.c:632
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "沒有 `%s' 這個檔案或目錄.\n\n"

#: src/ftp.c:690 src/ftp.c:697
#, c-format
msgid "Length: %s"
msgstr "長度: %s"

#: src/ftp.c:692 src/ftp.c:699
#, c-format
msgid " [%s to go]"
msgstr " [%s 開始]"

#: src/ftp.c:701
msgid " (unauthoritative)\n"
msgstr " (未獲認可的)\n"

#: src/ftp.c:719
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, 正在關閉連線控制.\n"

#: src/ftp.c:727
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - 資料連線: %s; "

#: src/ftp.c:744
msgid "Control connection closed.\n"
msgstr "連線控制已經被關閉了.\n"

#: src/ftp.c:762
msgid "Data transfer aborted.\n"
msgstr "資料傳輸已經被中斷了.\n"

#: src/ftp.c:828
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "檔案 `%s' 已經存在，不會接收.\n"

#: src/ftp.c:894 src/http.c:913
#, c-format
msgid "(try:%2d)"
msgstr "(嘗試:%2d)"

#: src/ftp.c:953 src/http.c:1099
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' 被儲存 [%ld]\n\n"

#: src/ftp.c:999
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "使用 `%s' 作為列表之暫存檔.\n"

#: src/ftp.c:1011
#, c-format
msgid "Removed `%s'.\n"
msgstr "移除 `%s'.\n"

#: src/ftp.c:1047
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "遞迴層次 %d 已經超過最大的 %d 層次值. \n"

#: src/ftp.c:1094 src/http.c:1037
#, c-format
msgid "Local file `%s' is more recent, not retrieving.\n\n"
msgstr "本地的 `%s' 檔案比較新，所以將不取回.\n\n"

#: src/ftp.c:1100 src/http.c:1043
#, c-format
msgid "The sizes do not match (local %ld), retrieving.\n"
msgstr "檔案大小並不相符合 (本地的為 %ld)，正在取回中.\n"

#: src/ftp.c:1117
msgid "Invalid name of the symlink, skipping.\n"
msgstr "無效的連結裝置名稱，正在跳過中.\n"

#: src/ftp.c:1134
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "已經存在正確的 %s -> %s 象徵連結\n\n"

#: src/ftp.c:1141
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "正在建立 %s -> %s 的象徵連結\n"

#: src/ftp.c:1152
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "不支援連結裝置，正在跳過 `%s' 這個象徵連結.\n"

#: src/ftp.c:1164
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "正跳過 `%s' 目錄.\n"

#: src/ftp.c:1173
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: 不明的/不支援的檔案格式.\n"

#: src/ftp.c:1189
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: 錯誤的時間戳記.\n"

#: src/ftp.c:1209
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "將不取回從 %d (最大值為 %d) 層後的目錄.\n"

#: src/ftp.c:1248
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "不下行到 `%s' 因為他是被排除的或是非包含進來的.\n"

#: src/ftp.c:1293
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "正放棄 `%s' 中.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1340
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "沒有與 `%s' 格式相符合的.\n"

#: src/ftp.c:1400
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "已經寫入 HTML 格式的索引檔到 `%s' [%ld].\n"

#: src/ftp.c:1405
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "寫妥 HTML 格式的索引檔到 `%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: 選項 `%s' 是不明確的\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: 選項 `--%s' 未提供一個引數值\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: 選項 `%c%s' 未提供一個引數值\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: 選項 `%s' 需要一個引數\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: 未被認定的選項 `--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: 未被認定的選項 `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: 不合規定的選項 -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: 選項需要一個引數 -- %c\n"

#: src/host.c:432
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: 無法偵測使用者識別碼.\n"

#: src/host.c:444
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: 警告: uname 失敗: %s\n"

#: src/host.c:456
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: 警告: gethostname 失敗\n"

#: src/host.c:484
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: 警告: 無法偵測本地 IP 位址.\n"

#: src/host.c:498
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: 警告: 無法反查本地 IP 位址.\n"

#: src/host.c:506
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: 警告: 本地位址的反查不符合 FQDN 規格!\n"

#: src/host.c:533
msgid "Host not found"
msgstr "找不到主機"

#: src/host.c:535
msgid "Unknown error"
msgstr "不明的錯誤"

#: src/html.c:433 src/html.c:435
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s 的索引在 %s:%d"

#: src/html.c:457
msgid "time unknown       "
msgstr "時間不明           "

#: src/html.c:461
msgid "File        "
msgstr "檔案        "

#: src/html.c:464
msgid "Directory   "
msgstr "目錄        "

#: src/html.c:467
msgid "Link        "
msgstr "連結        "

#: src/html.c:470
msgid "Not sure    "
msgstr "沒有確定    "

#: src/html.c:488
#, c-format
msgid " (%s bytes)"
msgstr " (%s 位元組)"

#: src/http.c:483
msgid "Failed writing HTTP request.\n"
msgstr "失敗於寫入 HTTP 請求時.\n"

#: src/http.c:488
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "已經送出 %s 請求封包，正在等待回應中... "

#: src/http.c:527
msgid "End of file while parsing headers.\n"
msgstr "正在分析標頭內容時，檔案已經未端.\n"

#: src/http.c:538
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "讀取的標頭有錯誤 (%s).\n"

#: src/http.c:578
msgid "No data received"
msgstr "沒有接收到任何資料"

#: src/http.c:580
msgid "Malformed status line"
msgstr "畸形的狀態行"

#: src/http.c:585
msgid "(no description)"
msgstr "(沒有相關說明)"

#. If we have tried it already, then there is not point
#. retrying it.
#: src/http.c:669
msgid "Authorization failed.\n"
msgstr "認證失敗.\n"

#: src/http.c:676
msgid "Unknown authentication scheme.\n"
msgstr "不明的認證方案.\n"

#: src/http.c:739
#, c-format
msgid "Location: %s%s\n"
msgstr "位置: %s%s\n"

#: src/http.c:740 src/http.c:765
msgid "unspecified"
msgstr "沒有指定"

#: src/http.c:741
msgid " [following]"
msgstr " [下列各項]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:755
msgid "Length: "
msgstr "長度: "

#: src/http.c:760
#, c-format
msgid " (%s to go)"
msgstr " (%s 要開始)"

#: src/http.c:765
msgid "ignored"
msgstr "忽略"

#: src/http.c:848
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "警告: 在 HTTP 裡面並支援萬用字元符號 (wildcards).\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:863
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "檔案 `%s' 已經存在，將不取回.\n"

#: src/http.c:969
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "無法寫到 `%s' (%s).\n"

#: src/http.c:979
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "錯誤: 要求重新定向 (%d) 卻沒有位置.\n"

#: src/http.c:995
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s 錯誤 %d: %s.\n"

#: src/http.c:1007
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "遺失 \"Last-modified\" 的檔頭 -- 時間戳記被關閉.\n"

#: src/http.c:1015
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "無效的 \"Last-modified\" 檔頭 -- 時間戳記被忽略.\n"

#: src/http.c:1047
msgid "Remote file is newer, retrieving.\n"
msgstr "遠端的檔案比較新，取回中.\n"

#: src/http.c:1081
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' 被存為 [%ld/%ld]\n\n"

#: src/http.c:1113
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - 連線被關閉在 %ld 位元組. "

#: src/http.c:1121
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' 被存為 [%ld/%ld])\n\n"

#: src/http.c:1133
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - 連線關閉於 %ld/%ld byte."

#: src/http.c:1144
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - 於 %ld (%s) 位元組處發生讀取錯誤."

#: src/http.c:1152
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - 於 %ld/%ld (%s) 位元組處發生讀取錯誤."

#: src/init.c:311 src/netrc.c:249
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: 無法讀取 %s (%s).\n"

#: src/init.c:332 src/init.c:338
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: 失敗於 %s 在第 %d 行.\n"

#: src/init.c:369
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: 警告: 系統與使用者的 wgetrc 都指向 `%s'.\n"

#: src/init.c:460
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: BUG: 不明的命令 `%s', 數值 `%s'.\n"

#: src/init.c:487
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: 請特別指定開啟或關閉.\n"

#: src/init.c:505 src/init.c:762 src/init.c:784 src/init.c:857
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: 無效的指定項目 `%s'.\n"

#: src/init.c:618 src/init.c:640 src/init.c:662 src/init.c:688
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: 無效的指定項目 `%s'\n"

#: src/main.c:101
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "用法: %s [選項]... [URL]...\n"

#: src/main.c:109
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNY Wget %s, 一個非交談式的網路抓檔工具.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:114
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\n命令的引數使用長項目與短項目相同.\n"

#: src/main.c:117
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc' command.\n"
"\n"
msgstr ""
"啟動:\n"
"  -V,  --version           顯示 Wget 的版本並且離開.\n"
"  -h,  --help              顯示這個說明檔.\n"
"  -b,  -background         在啟動之後跳到背景去.\n"
"  -e,  -execute=COMMAND    執行一個 `.wgetrc' 裡面的 COMMAND 指令.\n"
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
"紀錄檔與輸入的檔案:\n"
"  -o,  --output-file=FILE     紀錄訊息到 FILE 去.\n"
"  -a,  -append-output=FILE    增加訊息到 FILE 去.\n"
"  -d,  --debug                顯示除錯的輸出.\n"
"  -q,  --quiet                安靜模式 (不輸入任何訊息).\n"
"  -v,  --verbose              冗長模式 (這是內定值).\n"
"  -nv, --non-verbose          關閉 verboseness, 但不是安靜模式.\n"
"  -i,  --input-file=FILE      從 FILE 讀取 URL .\n"
"  -F,  --force-html           把輸入的檔案當作 HTML.\n"
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
"下載:\n"
"  -t,  --tries=NUMBER           設定重複嘗試 NUMBER 次 (0 是無限制).\n"
"  -O   --output-document=FILE   把文件寫到 FILE 裡.\n"
"  -nc, --no-clobber             不破壞已經存在的檔案.\n"
"  -c,  --continue               重新取得一個已經存在的檔案.\n"
"       --dot-style=STYLE        設定取回狀況的顯示風格.\n"
"  -N,  --timestamping           不取回比本地舊的檔案.\n"
"  -S,  --server-response        顯示伺服器回應狀況.\n"
"       --spider                 不下載任何東西.\n"
"  -T,  --timeout=SECONDS        設定讀取時超過的時間為 SECONDS 秒.\n"
"  -w,  --wait=SECONDS           在取回檔案時等待 SECONDS 秒.\n"
"  -Y,  --proxy=on/off           開啟或關閉 Proxy.\n"
"  -Q,  --quota=NUMBER           設定取回檔案的定額限制為 NUMBER 個.\n"
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
"目錄:\n"
"  -nd  --no-directories            不建立目錄.\n"
"  -x,  --force-directories         強制進行目錄建立的工作.\n"
"  -nH, --no-host-directories       不建立主機的目錄.\n"
"  -P,  --directory-prefix=PREFIX   把檔案存到 PREFIX/...\n"
"       --cut-dirs=NUMBER           忽略 NUMBER 個遠端的目錄元件.\n"
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
"HTTP 選項:\n"
"       --http-user=USER       設 http 使用者為 USER.\n"
"       --http0passwd=PASS     設 http 使用者的密碼為 PASS.\n"
"  -C,  --cache=on/off         提供/關閉快取伺服器資料 (正常情況為提供).\n"
"       --ignore-length        忽略 `Content-Length' 標頭欄位.\n"
"       --proxy-user=USER      設 USER 為 Proxy 使用者名稱.\n"
"       --proxy-passwd=PASS    設 PASS 為 Proxy 密碼.\n"
"  -s,  --save-headers         儲存 HTTP 標頭成為檔案.\n"
"  -U,  --user-agent=AGENT     使用 AGENT 取代 Wget/VERSION 作為識別代號.\n"
"\n"

#: src/main.c:165
msgid ""
"FTP options:\n"
"       --retr-symlinks   retrieve FTP symbolic links.\n"
"  -g,  --glob=on/off     turn file name globbing on or off.\n"
"       --passive-ftp     use the \"passive\" transfer mode.\n"
"\n"
msgstr ""
"FTP 選項:\n"
"       --retr-symlinks   取回 FTP 的象徵連結.\n"
"  -g,  --glob=on/off     turn file name globbing on ot off.\n"
"       --passive-ftp     使用 \"passive\" 傳輸模式.\n"
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
"使用遞迴方式的取回:\n"
"  -r,  --recursive             像是吸入 web 的取回 -- 請小心使用!.\n"
"  -l,  --level=NUMBER          遞迴層次的最大值 (0 不限制).\n"
"       --delete-after          刪除下載完畢的檔案.\n"
"  -k,  --convert-links         改變沒有關連的連結成為有關連.\n"
"  -m,  --mirror                開啟適合用來映射的選項.\n"
"  -nr, --dont-remove-listing   不要移除 `.listing' 檔.\n"
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
"遞迴式作業的允許\與拒絕選項:\n"
"  -A,  --accept=LIST                允許\的擴充項目的列表.\n"
"  -R,  --reject=LIST                拒絕的擴充項目的列表.\n"
"  -D,  --domains=LIST               允許\的網域列表.\n"
"       --exclude-domains=LIST       拒絕的網域列表 (使用逗號來分隔).\n"
"  -L,  --relative                   只跟隨關聯連結前進.\n"
"       --follow-ftp                 跟隨 HTML 文件裡面的 FTP 連結.\n"
"  -H,  --span-hosts                 當開始遞迴時便到外面的主機.\n"
"  -I,  --include-directories=LIST   允許\的目錄列表.\n"
"  -X,  --exclude-directories=LIST   排除的目錄列表.\n"
"  -nh, --no-host-lookup             不透過 DNS 查尋主機.\n"
"  -np, --no-parent                  不追朔到起源目錄.\n"
"\n"

#: src/main.c:191
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "錯誤回報與建議請寄到 <bug-wget@gnu.org>.\n"

#: src/main.c:347
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: 除錯支援功\能被沒有被編譯進來.\n"

#: src/main.c:395
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""

#: src/main.c:401
msgid "\nWritten by Hrvoje Niksic <hniksic@srce.hr>.\n"
msgstr "\n由 Hrvoje Niksic <hniksic@srce.hr> 撰寫.\n"

#: src/main.c:465
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: 無效的命令\n"

#: src/main.c:515
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: 違法的選項 -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:518 src/main.c:560 src/main.c:591
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "試著使用 `%s --help' 取得更多的選項.\n"

#: src/main.c:571
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "無法同時使用冗長模式和安靜模式.\n"

#: src/main.c:577
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "無法同時修改時間戳記和覆蓋\舊檔.\n"

#. No URL specified.
#: src/main.c:586
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: 遺失 URL \n"

#: src/main.c:670
#, c-format
msgid "No URLs found in %s.\n"
msgstr "在 %s 裡面找不到任何 URL.\n"

#: src/main.c:679
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"已經完成 --%s--\n"
"下載: %s 位元組在 %d 檔案裡\n"

#: src/main.c:684
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "下載的定額 (%s 位元組) 已經超過!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:711
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s: 已經接收過，將輸出重新指向 `%%s'.\n"

#: src/mswindows.c:118
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"已經接收到 CTRL+Break 訊號，將輸出重新指向 `%s'.\n"
"已經在背景裡繼續執行了.\n"
"您可以藉由按下 CTRL+ALT+DELETE 來停止 Wget.\n"

#. parent, no error
#: src/mswindows.c:135 src/utils.c:265
msgid "Continuing in background.\n"
msgstr "在背景繼續執行.\n"

#: src/mswindows.c:137 src/utils.c:267
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "輸出的內容將被寫到 `%s'.\n"

#: src/mswindows.c:227
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "啟動 WinHelp %s 中\n"

#: src/mswindows.c:254 src/mswindows.c:262
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: 無法找到可以使用的 socket 驅動程式.\n"

#: src/netrc.c:333
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: 警告 \"%s\" 記號在任何機器名稱之前出現\n"

#: src/netrc.c:365
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: 不明的記號 \"%s\"\n"

#: src/netrc.c:429
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "用法: %s NETRC [主機名稱]\n"

#: src/netrc.c:439
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: 無法開始 %s: %s\n"

#: src/recur.c:449 src/retr.c:462
#, c-format
msgid "Removing %s.\n"
msgstr "正在移除 %s.\n"

#: src/recur.c:450
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "自從 %s 應被拒絕掉起便開始移除它.\n"

#: src/recur.c:609
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "載入 robots.txt; 請忽略錯誤.\n"

#: src/retr.c:193
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ 在跳過 %dk ]"

#: src/retr.c:344
msgid "Could not find proxy host.\n"
msgstr "無法找到 Proxy 主機.\n"

#: src/retr.c:355
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Proxy %s: 必須是 HTTP.\n"

#: src/retr.c:398
#, c-format
msgid "%s: Redirection to itself.\n"
msgstr "%s: 重新指向到它自己.\n"

#: src/retr.c:483
msgid "Giving up.\n\n"
msgstr "放棄中.\n\n"

#: src/retr.c:483
msgid "Retrying.\n\n"
msgstr "重新嘗試中.\n\n"

#: src/url.c:940
#, c-format
msgid "Error (%s): Link %s without a base provided.\n"
msgstr "錯誤 (%s): %s 這個連結不需要一個基準供應點.\n"

#: src/url.c:954
#, c-format
msgid "Error (%s): Base %s relative, without referer URL.\n"
msgstr "錯誤 (%s): 基於 %s 關連的緣故，不需要指示 URL.\n"

#: src/url.c:1363
#, c-format
msgid "Converting %s... "
msgstr "轉換中 %s... "

#: src/url.c:1368 src/url.c:1379
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "無法轉換在 %s: %s 的連結\n"

#: src/utils.c:68
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: 沒有足夠的記憶體.\n"

#: src/utils.c:200
msgid "Unknown/unsupported protocol"
msgstr "不明的/未支援的通訊協定"

#: src/utils.c:203
msgid "Invalid port specification"
msgstr "無效的埠號規格"

#: src/utils.c:206
msgid "Invalid host name"
msgstr "無效的主機名稱"

#: src/utils.c:427
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "失敗於脫離 `%s': %s 的象徵連結\n"
