# traditional chinese translation for wget messages
# Copyright (C) 2000 Free Software Foundation, Inc.
# Originla author CD Chen <cdchen@linux.ntcic.edu.tw>
# Pofeng Lee <pofeng.lee@ms7.url.com.tw>, 1998.
# Jing-Jong Shyue <shyue@sonoma.com.tw>, 2000.
# Abel Cheung <maddog@linux.org.hk>, 2001.
#
msgid ""
msgstr ""
"Project-Id-Version: GNU Wget 1.7-dev\n"
"POT-Creation-Date: 2001-04-27 08:45+0200\n"
"PO-Revision-Date: 2001-04-29 04:12+0800\n"
"Last-Translator: Abel Cheung <maddog@linux.org.hk>\n"
"Language-Team: traditional chinese <zh-l10n@linux.org.tw>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=utf-8\n"
"Content-Transfer-Encoding: 8bit\n"

#: src/cookies.c:623
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Set-Cookie 在欄位 `%s' 出現錯誤"

#: src/cookies.c:647
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Set-Cookie 在字元 `%c' 出現語法錯誤。\n"

#: src/cookies.c:655
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Set-Cookie 出現語法錯誤：字串過早完結。\n"

#: src/cookies.c:1350
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "無法開啟 cookies 檔 `%s'：%s\n"

#: src/cookies.c:1362
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "寫入 `%s' 時發生錯誤：%s\n"

#: src/cookies.c:1366
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "關閉 `%s' 時發生錯誤：%s\n"

#: src/ftp-ls.c:785
msgid "Usupported listing type, trying Unix listing parser.\n"
msgstr "不支援的檔案列表類型，假設是 Unix 列表來分析.\n"

#: src/ftp-ls.c:830 src/ftp-ls.c:832
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s 的索引在 %s:%d"

#: src/ftp-ls.c:854
msgid "time unknown       "
msgstr "未知的時間         "

#: src/ftp-ls.c:858
msgid "File        "
msgstr "檔案        "

#: src/ftp-ls.c:861
msgid "Directory   "
msgstr "目錄        "

#: src/ftp-ls.c:864
msgid "Link        "
msgstr "連結        "

#: src/ftp-ls.c:867
msgid "Not sure    "
msgstr "不確定      "

#: src/ftp-ls.c:885
#, c-format
msgid " (%s bytes)"
msgstr " (%s 位元組)"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:151 src/http.c:627
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "正在連接到 %s:%hu…"

#: src/ftp.c:173 src/ftp.c:540 src/http.c:644
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "嘗試連接到 %s:%hu 但被拒絕.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:194 src/http.c:655
msgid "connected!\n"
msgstr "接上了!\n"

#: src/ftp.c:195
#, c-format
msgid "Logging in as %s ... "
msgstr "以 %s 的身份登入中…"

#: src/ftp.c:204 src/ftp.c:257 src/ftp.c:289 src/ftp.c:337 src/ftp.c:430
#: src/ftp.c:482 src/ftp.c:576 src/ftp.c:649 src/ftp.c:710 src/ftp.c:758
msgid "Error in server response, closing control connection.\n"
msgstr "伺服器回應錯誤，關閉控制連結.\n"

#: src/ftp.c:212
msgid "Error in server greeting.\n"
msgstr "伺服器問候錯誤.\n"

#: src/ftp.c:220 src/ftp.c:346 src/ftp.c:439 src/ftp.c:491 src/ftp.c:586
#: src/ftp.c:659 src/ftp.c:720 src/ftp.c:768
msgid "Write failed, closing control connection.\n"
msgstr "寫入失敗，關閉控制連結.\n"

#: src/ftp.c:227
msgid "The server refuses login.\n"
msgstr "伺服器拒絕登入.\n"

#: src/ftp.c:234
msgid "Login incorrect.\n"
msgstr "登入錯誤.\n"

#: src/ftp.c:241
msgid "Logged in!\n"
msgstr "登入完成!\n"

#: src/ftp.c:266
msgid "Server error, can't determine system type.\n"
msgstr "伺服器錯誤，不能決定作業系統的類型.\n"

#: src/ftp.c:276 src/ftp.c:561 src/ftp.c:633 src/ftp.c:690
msgid "done.    "
msgstr "完成."

#: src/ftp.c:326 src/ftp.c:460 src/ftp.c:741 src/ftp.c:789 src/url.c:1429
msgid "done.\n"
msgstr "完成.\n"

#: src/ftp.c:354
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "未知的類別 '%c'，關閉控制連結.\n"

#: src/ftp.c:367
msgid "done.  "
msgstr "完成."

#: src/ftp.c:373
msgid "==> CWD not needed.\n"
msgstr "==> 不需要 CWD (切換路徑).\n"

#: src/ftp.c:446
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"目錄 '%s' 不存在.\n"
"\n"

#. do not CWD
#: src/ftp.c:464
msgid "==> CWD not required.\n"
msgstr "==> 不需要 CWD (切換路徑).\n"

#: src/ftp.c:498
msgid "Cannot initiate PASV transfer.\n"
msgstr "無法初始化 PASV 傳輸.\n"

#: src/ftp.c:502
msgid "Cannot parse PASV response.\n"
msgstr "無法分析 PASV 回應.\n"

#: src/ftp.c:516
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "會嘗試連接到 %s:%hu.\n"

#: src/ftp.c:603
#, c-format
msgid "Bind error (%s).\n"
msgstr "結合(Bind)錯誤 (%s).\n"

#: src/ftp.c:619
msgid "Invalid PORT.\n"
msgstr "錯誤的通訊埠.\n"

#: src/ftp.c:672
#, c-format
msgid ""
"\n"
"REST failed; will not truncate `%s'.\n"
msgstr ""
"\n"
"重設(REST) 失敗；不會截短 `%s'。\n"

#: src/ftp.c:679
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"重設(REST) 失敗，要重頭開始。\n"

#: src/ftp.c:728
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"檔案 '%s' 不存在.\n"
"\n"

#: src/ftp.c:776
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"檔案或目錄 '%s' 不存在.\n"
"\n"

#: src/ftp.c:860 src/ftp.c:868
#, c-format
msgid "Length: %s"
msgstr "長度: %s"

#: src/ftp.c:862 src/ftp.c:870
#, c-format
msgid " [%s to go]"
msgstr " [尚有 %s]"

#: src/ftp.c:872
msgid " (unauthoritative)\n"
msgstr " (不可靠)\n"

#: src/ftp.c:899
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s 關閉控制連結.\n"

#: src/ftp.c:907
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - 資料連結: %s; "

#: src/ftp.c:924
msgid "Control connection closed.\n"
msgstr "已關閉控制連結.\n"

#: src/ftp.c:942
msgid "Data transfer aborted.\n"
msgstr "已中止資料傳輸.\n"

#: src/ftp.c:1006
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "檔案 '%s' 已存在，不會接收.\n"

#: src/ftp.c:1076 src/http.c:1501
#, c-format
msgid "(try:%2d)"
msgstr "(嘗試次數:%2d)"

#: src/ftp.c:1140 src/http.c:1754
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - '%s' 已儲存 [%ld]\n"
"\n"

#: src/ftp.c:1182 src/main.c:814 src/recur.c:483 src/retr.c:566
#, c-format
msgid "Removing %s.\n"
msgstr "正在刪除 %s.\n"

#: src/ftp.c:1222
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "使用 '%s' 作為列表暫存檔.\n"

#: src/ftp.c:1234
#, c-format
msgid "Removed `%s'.\n"
msgstr "刪除了 '%s'.\n"

#: src/ftp.c:1270
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "遞迴深度 %d 超過最大值 %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1331
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "伺服器端檔案不比本機檔案 `%s' 新 -- 不會傳輸.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1338
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr "伺服器端檔案較本機檔案 `%s' 新 -- 接收中.\n"

#. Sizes do not match
#: src/ftp.c:1345
#, c-format
msgid ""
"The sizes do not match (local %ld) -- retrieving.\n"
"\n"
msgstr ""
"檔案大小不符合 (本地檔案 %ld) -- 接收中.\n"
"\n"

#: src/ftp.c:1362
msgid "Invalid name of the symlink, skipping.\n"
msgstr "跳過有名稱錯誤的符號連結.\n"

#: src/ftp.c:1379
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"已有正確符號連結 %s -> %s\n"
"\n"

#: src/ftp.c:1387
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "建立符號連結 %s -> %s\n"

#: src/ftp.c:1398
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "不支援符號連結，跳過符號連結 '%s'.\n"

#: src/ftp.c:1410
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "跳過目錄 '%s'.\n"

#: src/ftp.c:1419
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: 未知或不支援的檔案類別.\n"

#: src/ftp.c:1446
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: 錯誤的時間標記.\n"

#: src/ftp.c:1467
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "因為深度為 %d (最大值為 %d)，所以不接收.\n"

#: src/ftp.c:1513
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "不進入 '%s' 目錄因為已被排除或不被列入表中.\n"

#: src/ftp.c:1560
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "拒絕 '%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1607
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "不符合樣式 '%s'.\n"

#: src/ftp.c:1672
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "寫入 HTML 化的索引到 '%s' [%ld].\n"

#: src/ftp.c:1677
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "寫入 HTML 化的索引到 '%s'.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: 選項 '%s' 是含混不清的\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: 選項 '--%s' 不接受參數\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: 選項 '%c%s' 不接受參數\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: 選項 '%s' 需要參數\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: 不明的選項 '--%s'\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: 不明的選項 '%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: 不合法的選項 -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: 選項需要參數 -- %c\n"

#: src/host.c:391
#, c-format
msgid "%s: Cannot determine user-id.\n"
msgstr "%s: 無法決定使用者帳號.\n"

#: src/host.c:403
#, c-format
msgid "%s: Warning: uname failed: %s\n"
msgstr "%s: 警告: uname() 失敗: %s\n"

#: src/host.c:415
#, c-format
msgid "%s: Warning: gethostname failed\n"
msgstr "%s: 警告: gethostname() 失敗\n"

#: src/host.c:443
#, c-format
msgid "%s: Warning: cannot determine local IP address.\n"
msgstr "%s: 警告: 無法確定本地端 IP 地址.\n"

#: src/host.c:457
#, c-format
msgid "%s: Warning: cannot reverse-lookup local IP address.\n"
msgstr "%s: 警告: 無法反查本地端 IP 地址.\n"

#. This gets ticked pretty often.  Karl Berry reports
#. that there can be valid reasons for the local host
#. name not to be an FQDN, so I've decided to remove the
#. annoying warning.
#: src/host.c:470
#, c-format
msgid "%s: Warning: reverse-lookup of local address did not yield FQDN!\n"
msgstr "%s: 警告: 反查後的本地端地址不是有效的 FQDN!\n"

#: src/host.c:498
msgid "Host not found"
msgstr "找不到主機"

#: src/host.c:500
msgid "Unknown error"
msgstr "未知的錯誤"

#. this is fatal
#: src/http.c:554
msgid "Failed to set up an SSL context\n"
msgstr "無法建立 SSL context\n"

#: src/http.c:560
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "無法由 %s 載入認證\n"

#: src/http.c:564 src/http.c:572
msgid "Trying without the specified certificate\n"
msgstr "嘗試不載入指定的認證\n"

#: src/http.c:568
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "無法由 %s 載入相關認證的 key\n"

#: src/http.c:666 src/http.c:1592
msgid "Unable to establish SSL connection.\n"
msgstr "不能建立 SSL 連線.\n"

#: src/http.c:674
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "再使用到 %s:%hu 的連線.\n"

#: src/http.c:860
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "無法寫入 HTTP 要求: %s.\n"

#: src/http.c:865
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "已送出 %s 要求，等候回應中…"

#: src/http.c:909
msgid "End of file while parsing headers.\n"
msgstr "分析標頭時檔案結束。\n"

#: src/http.c:920
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "讀取標頭時發生錯誤(%s)。\n"

#: src/http.c:960
msgid "No data received"
msgstr "沒收到資料"

#: src/http.c:962
msgid "Malformed status line"
msgstr "畸形的狀態行"

#: src/http.c:967
msgid "(no description)"
msgstr "(沒有描述)"

#: src/http.c:1090
msgid "Authorization failed.\n"
msgstr "認證失敗!\n"

#: src/http.c:1097
msgid "Unknown authentication scheme.\n"
msgstr "未知的認證方式.\n"

#: src/http.c:1173
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    檔案早已下載完成；不會再有任何動作。\n"
"\n"

#: src/http.c:1190
#, c-format
msgid ""
"\n"
"    The server does not support continued download;\n"
"    refusing to truncate `%s'.\n"
"\n"
msgstr ""
"\n"
"    伺服器不支援續傳檔案；\n"
"    不會截短 `%s'。\n"
"\n"

#: src/http.c:1238
#, c-format
msgid "Location: %s%s\n"
msgstr "位置: %s%s\n"

#: src/http.c:1239 src/http.c:1265
msgid "unspecified"
msgstr "沒有指定"

#: src/http.c:1240
msgid " [following]"
msgstr " [跟隨中]"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1255
msgid "Length: "
msgstr "長度: "

#: src/http.c:1260
#, c-format
msgid " (%s to go)"
msgstr " (尚有 %s)"

#: src/http.c:1265
msgid "ignored"
msgstr "已忽略"

#: src/http.c:1395
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "警告: HTTP 不支援萬用字元.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1416
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "檔案 '%s' 已存在，將不接收.\n"

#: src/http.c:1584
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "無法寫入 '%s' (%s).\n"

#: src/http.c:1602
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "錯誤: 嘗試重導向 (%d) 但沒有指定位置.\n"

#: src/http.c:1627
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s 錯誤 %d: %s.\n"

#: src/http.c:1640
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "缺少了最後修改時間標頭 -- 關閉時間標記.\n"

#: src/http.c:1648
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "不合法的最後修改時間標頭 -- 忽略時間標記.\n"

#: src/http.c:1671
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"伺服器端檔案不比本機檔案 `%s' 新 -- 不會傳輸.\n"
"\n"

#: src/http.c:1679
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "檔案大小不符合 (本地檔案 %ld) -- 接收中.\n"

#: src/http.c:1683
msgid "Remote file is newer, retrieving.\n"
msgstr "遠端檔案較新，接收中.\n"

#: src/http.c:1728
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - '%s' 已儲存 [%ld/%ld]\n"
"\n"

#: src/http.c:1776
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - 在 %ld 位元組時關閉連結. "

#: src/http.c:1784
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - '%s' 已儲存 [%ld/%ld])\n"
"\n"

#: src/http.c:1804
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - 在 %ld/%ld 位元組時關閉連結. "

#: src/http.c:1815
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - 在 %ld 位元組時讀取發生錯誤 (%s)."

#: src/http.c:1823
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - 在 %ld/%ld 位元組時讀取錯誤 (%s)."

#: src/init.c:348 src/netrc.c:260
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: 無法讀取 %s (%s).\n"

#: src/init.c:366 src/init.c:372
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: 錯誤發生於 %s，第 %d 行.\n"

#: src/init.c:404
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: 警告: 系統與使用者的 wgetrc 都指向 '%s'.\n"

#: src/init.c:496
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: 臭蟲: 未知的指令 '%s'，變數值 '%s'.\n"

#: src/init.c:526
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: 無法將 `%s' 轉換為 IP 地址.\n"

#: src/init.c:557
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: 請指定 on 或 off.\n"

#: src/init.c:601
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: 請指定 always、on、off 或 never.\n"

#: src/init.c:620 src/init.c:917 src/init.c:939 src/init.c:1003
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: 不合法的指定值 '%s'.\n"

#: src/init.c:773 src/init.c:795 src/init.c:817 src/init.c:843
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: 不合法的指定值 '%s'\n"

#: src/main.c:119
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "用法: %s [選項]… [URL]…\n"

#: src/main.c:127
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s，非互動式檔案接收工具.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:132
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"長選項必須用的參數在使用短選項時也是必須的.\n"
"\n"

#: src/main.c:136
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"啟動:\n"
"  -V,  --version           顯示 Wget 版本後離開.\n"
"  -h,  --help              印出此輔助說明.\n"
"  -b,  --background        啟動後進入背景作業.\n"
"  -e,  --execute=COMMAND   執行 `.wgetrc' 形式的指令.\n"
"\n"

#: src/main.c:143
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
"紀錄與輸入檔案:\n"
"  -o,  --output-file=FILE     將訊息紀錄到 FILE 中.\n"
"  -a,  --append-output=FILE   累加紀錄訊息到 FILE 中.\n"
"  -d,  --debug                印出除錯輸出.\n"
"  -q,  --quiet                安靜模式 (不輸出訊息).\n"
"  -v,  --verbose              冗長模式 (預設值).\n"
"  -nv, --non-verbose          關閉冗長模式，但不進入安靜模式.\n"
"  -i,  --input-file=FILE      下載從 FILE 中找到的 URL.\n"
"  -F,  --force-html           把輸入檔案當作 HTML 處理.\n"
"  -B,  --base=URL             使用 -F -i file 選項時，在相對連結前加入 URL.\n"
"       --sslcertfile=FILE     可選用的請求端認證.\n"
"       --sslcertkey=KEYFILE   可選用的對應此認證的\"鑰匙\".\n"
"\n"

#: src/main.c:157
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local "
"host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 "
"unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# "
"suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than "
"local.\n"
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
"下載:\n"
"       --bind-address=ADDRESS   與本機的 ADDRESS (主機名稱或 IP) 聯繫上.\n"
"  -t,  --tries=NUMBER           設定重試次數為 NUMBER (0 表示無限).\n"
"  -O   --output-document=FILE   將文件寫入 FILE 中.\n"
"  -nc, --no-clobber             不要動已經存在的檔案，也不使用在檔案名稱後加"
"入 .<數字> 旳方法寫入新的檔案.\n"
"  -c,  --continue               繼續接收已下載了一部份的檔案.\n"
"       --dot-style=STYLE        設定接收顯示的樣式.\n"
"  -N,  --timestamping           除非較本地端的檔案新，否則不再接收遠端檔案.\n"
"  -S,  --server-response        顯示伺服器回應.\n"
"       --spider                 不要下載任何東西.\n"
"  -T,  --timeout=SECONDS        設定讀取逾時為 SECONDS.\n"
"  -w,  --wait=SECONDS           在接收之間等待 SECONDS.\n"
"       --waitretry=SECONDS      在每次重覆嘗試之間等待 1 至 SECONDS.\n"
"  -Y,  --proxy=on/off           開啟/關閉 代理伺服器.\n"
"  -Q,  --quota=NUMBER           設定接收限額為 NUMBER.\n"
"\n"

#: src/main.c:174
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
"目錄:\n"
"  -nd  --no-directories            不建立目錄.\n"
"  -x,  --force-directories         強制建立目錄.\n"
"  -nH, --no-host-directories       不建立主機目錄.\n"
"  -P,  --directory-prefix=PREFIX   將檔案存到 PREFIX/…\n"
"       --cut-dirs=NUMBER           忽略遠端目錄的前 NUMBER 個目錄層.\n"
"\n"

#: src/main.c:182
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
"       --cookies=no\t     don't use cookies.\n"
"       --load-cookies=FILE   load cookies from FILE before session.\n"
"       --save-cookies=FILE   save cookies to FILE after session.\n"
"\n"
msgstr ""
"HTTP 選項:\n"
"       --http-user=USER      設定 http 使用者名稱為 USER.\n"
"       --http-passwd=PASS    設定 http 使用者密碼為 PASS.\n"
"  -C,  --cache=on/off        (不)允許伺服器使用快取資料 (正常是允許的).\n"
"  -E,  --html-extension      將所有 MIME 類型為 text/html 的文件都加上 .html "
"延伸檔名.\n"
"       --ignore-length       忽略 `Content-Length' 標頭欄位.\n"
"       --header=STRING       插入 STRING 到標頭中.\n"
"       --proxy-user=USER     設定代理伺服器使用者名稱為 USER.\n"
"       --proxy-passwd=PASS   設定代理伺服器使用者密碼為 PASS.\n"
"       --referer=URL         在 HTTP 要求中包括 `Referer: URL' 標頭.\n"
"  -s,  --save-headers        將 HTTP 標頭存檔.\n"
"  -U,  --user-agent=AGENT    宣稱為 AGENT 而不是 Wget/VERSION.\n"
"       --cookies=no\t     不使用 cookies.\n"
"       --load-cookies=FILE   作業階段開始前由 FILE 載入 cookies.\n"
"       --save-cookies=FILE   作業階段結束後將 cookies 儲存入 FILE.\n"
"\n"

#: src/main.c:199
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not "
"dirs).\n"
"\n"
msgstr ""
"FTP 選項:\n"
"  -nr, --dont-remove-listing   不要刪除 '.listing' 檔案.\n"
"  -g,  --glob=on/off           設定是否展開有萬用字元的檔名.\n"
"       --passive-ftp           使用 \"被動\" 傳輸模式.\n"
"       --retr-symlinks         在遞迴模式中，下傳連結所連到的檔案(而不是目"
"錄).\n"
"\n"

#: src/main.c:206
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive          recursive web-suck -- use with care!\n"
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for "
"infinite).\n"
"       --delete-after       delete files locally after downloading them.\n"
"  -k,  --convert-links      convert non-relative links to relative.\n"
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
"  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n"
"  -p,  --page-requisites    get all images, etc. needed to display HTML "
"page.\n"
"\n"
msgstr ""
"遞迴接收:\n"
"  -r,  --recursive             遞迴下載整個網站 -- 小心使用!!\n"
"  -l,  --level=NUMBER          最大遞迴深度 (inf 或 0 表示無限).\n"
"       --delete-after          刪除下載後的檔案.\n"
"  -k,  --convert-links         將絕對連結轉換為相對連結.\n"
"  -K,  --backup-converted      將 X 轉換前先備份為 X.orig .\n"
"  -m,  --mirror                相等於 -r -N -l inf -nr 選項.\n"
"  -p,  --page-requisites       下載所有顯示完整網頁所需要的檔案，例如圖像.\n"
"\n"

#: src/main.c:216
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
"遞迴 接受/拒絕:\n"
"  -A,  --accept=LIST                接受的延伸檔名列表，以逗號分隔.\n"
"  -R,  --reject=LIST                排除的延伸檔名列表，以逗號分隔.\n"
"  -D,  --domains=LIST               接受的網域列表，以逗號分隔.\n"
"       --exclude-domains=LIST       排除的網域列表，以逗號分隔.\n"
"       --follow-ftp                 跟隨 HTML 文件中的 FTP 連結.\n"
"       --follow-tags=LIST           會跟隨的 HTML 標籤，以逗號分隔.\n"
"  -G,  --ignore-tags=LIST           會忽略的 HTML 標籤，以逗號分隔.\n"
"  -H,  --span-hosts                 遞迴時到其它主機.\n"
"  -L,  --relative                   只跟隨相對連結.\n"
"  -I,  --include-directories=LIST   允許的目錄列表.\n"
"  -X,  --exclude-directories=LIST   排除的目錄列表.\n"
"  -nh, --no-host-lookup             不對主機作 DNS 查詢.\n"
"  -np, --no-parent                  不回到上層的目錄.\n"
"\n"

#: src/main.c:232
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "請將臭蟲報告或建議寄給 <bug-wget@gnu.org>.\n"

#: src/main.c:424
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: 未將除錯支援編譯到程式中.\n"

#: src/main.c:476
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"版權所有 (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"這個程式散佈的目的是為了它會對人有用，\n"
"但是沒有任何保証；甚至沒有可售性或適合於特定目的的保証。\n"
"詳情請查閱 GNU General Public License。\n"

#: src/main.c:482
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr ""
"\n"
"本來由 Hrvoje Niksic <hniksic@arsdigita.com> 編寫.\n"

#: src/main.c:573
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: 錯誤的指令\n"

#: src/main.c:629
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: 不合法的選項 -- '-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:632 src/main.c:674 src/main.c:732
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "使用 '%s --help' 以取得選項.\n"

#: src/main.c:712
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "無法同時使用冗長與安靜模式.\n"

#: src/main.c:718
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "無法同時使用時間標記而不動本地端檔案.\n"

#. No URL specified.
#: src/main.c:727
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: 沒有指明 URL\n"

#: src/main.c:829
#, c-format
msgid "No URLs found in %s.\n"
msgstr "在 %s 中找不到 URL.\n"

#: src/main.c:838
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"完成 --%s--\n"
"下載了: %s 位元組，共 %d 個檔案\n"

#: src/main.c:846
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "超過下載配額 (%s 位元組)!\n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:880
#, c-format
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "接收 %s 完畢，重導向輸出到 '%%s'.\n"

#: src/mswindows.c:115
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"收到 CTRL+Break，重導向輸出到 '%s' 中.\n"
"將在背景繼續執行.\n"
"你可以按下 CTRL+ALT+DELETE 以停止 Wget.\n"

#. parent, no error
#: src/mswindows.c:132 src/utils.c:481
msgid "Continuing in background.\n"
msgstr "繼續在背景中執行.\n"

#: src/mswindows.c:134 src/utils.c:483
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "將輸出寫入 '%s' 中.\n"

#: src/mswindows.c:214
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "啟動 WinHelp %s\n"

#: src/mswindows.c:241 src/mswindows.c:248
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: 找不到可用的插座驅動程式.\n"

#: src/netrc.c:360
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: 警告: \"%s\" 標記出現在機器名稱前\n"

#: src/netrc.c:391
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: 未知的標記 \"%s\"\n"

#: src/netrc.c:455
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "用法: %s NETRC [主機名稱]\n"

#: src/netrc.c:465
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: 無法 stat() %s: %s\n"

#: src/recur.c:484
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "刪除 %s 因為它應該被指定了拒絕下載.\n"

#: src/recur.c:679
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "載入 robots.txt; 請忽略錯誤訊息.\n"

#: src/retr.c:227
#, c-format
msgid ""
"\n"
"          [ skipping %dK ]"
msgstr ""
"\n"
"          [ 跳過 %dK ]"

#: src/retr.c:373
msgid "Could not find proxy host.\n"
msgstr "找不到代理伺服主機.\n"

#: src/retr.c:387
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "代理伺服主機 %s: 必須是 HTTP.\n"

#: src/retr.c:481
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: 重導向到自己.\n"

#: src/retr.c:587
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"放棄中.\n"
"\n"

#: src/retr.c:587
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"重試中.\n"
"\n"

#: src/url.c:1329
#, c-format
msgid "Converting %s... "
msgstr "轉換 %s 中…"

#: src/url.c:1342
msgid "nothing to do.\n"
msgstr "不需進行任何動作.\n"

#: src/url.c:1350 src/url.c:1374
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "無法轉換 %s 中的連結: %s\n"

#: src/url.c:1365
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "無法刪除 '%s': %s\n"

#: src/url.c:1555
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "不能將 %s 備份成 %s: %s\n"

#: src/utils.c:93
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: 記憶體不足.\n"

#: src/utils.c:416
msgid "Unknown/unsupported protocol"
msgstr "未知/不支援的通訊協定"

#: src/utils.c:419
msgid "Invalid port specification"
msgstr "不合法的通訊埠"

#: src/utils.c:422
msgid "Invalid host name"
msgstr "不合法的主機名稱"

#: src/utils.c:643
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "無法解除符號連結 '%s': %s\n"

#, fuzzy
#~ msgid "Error (%s): Link %s without a base provided.\n"
#~ msgstr "錯誤 (%s): 連結 %s 沒有基礎提供者.\n"

#, fuzzy
#~ msgid "Error (%s): Base %s relative, without referer URL.\n"
#~ msgstr "錯誤 (%s): 接收基礎 %s, 沒有對應的 URL.\n"
