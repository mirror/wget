# translation of wget-1.9.1.po to Vietnamese
# Copyright (C) 2005 Free Software Foundation, Inc.
# This file is distributed under the same license as the PACKAGE package.
# Phan Vinh Thinh <teppi82@gmail.com>, 2005.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.9.1\n"
"POT-Creation-Date: 2003-10-11 16:21+0200\n"
"PO-Revision-Date: 2005-04-17 21:34+0400\n"
"Last-Translator: Phan Vinh Thinh <teppi82@gmail.com>\n"
"Language-Team: Vietnamese <gnomevi-list@lists.sourceforge.net>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
"X-Generator: KBabel 1.9.1\n"

#: src/connect.c:88
#, c-format
msgid "Unable to convert `%s' to a bind address.  Reverting to ANY.\n"
msgstr "Không chuyển đổi được `%s' thành địa chỉ tên.  Chuyển thành ANY.\n"

#: src/connect.c:165
#, c-format
msgid "Connecting to %s[%s]:%hu... "
msgstr "Đang kết nối tới %s[%s]:%hu... "

#: src/connect.c:168
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "Đang kết nối tới %s:%hu... "

#: src/connect.c:222
msgid "connected.\n"
msgstr "đã kết nối.\n"

#: src/convert.c:171
#, c-format
msgid "Converted %d files in %.2f seconds.\n"
msgstr "Đã chuyển đổi %d tập tin trong %.2f giây.\n"

#: src/convert.c:197
#, c-format
msgid "Converting %s... "
msgstr "Đang chuyển đổi %s... "

#: src/convert.c:210
msgid "nothing to do.\n"
msgstr "không thực hiện gì.\n"

#: src/convert.c:218 src/convert.c:242
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "Không thể chuyển đổi liên kết trong %s: %s\n"

#: src/convert.c:233
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "Không xóa được `%s': %s\n"

#: src/convert.c:439
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "Không sao lưu được %s thành %s: %s\n"

#: src/cookies.c:606
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Lỗi trong Set-Cookie, vùng `%s'"

#: src/cookies.c:629
#, c-format
msgid "Syntax error in Set-Cookie: %s at position %d.\n"
msgstr "Lỗi cú pháp trong Set-Cookie: %s tại vị trí %d.\n"

#: src/cookies.c:1426
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Không mở được tập tin cookie `%s': %s\n"

#: src/cookies.c:1438
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "Lỗi ghi nhớ tới `%s': %s\n"

#: src/cookies.c:1442
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "Lỗi đóng `%s': %s\n"

#: src/ftp-ls.c:812
msgid "Unsupported listing type, trying Unix listing parser.\n"
msgstr "Dạng danh sách không hỗ trợ, đang thử phân tích dạng danh sách Unix.\n"

#: src/ftp-ls.c:857 src/ftp-ls.c:859
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "Chỉ mục của /%s trên %s: %d"

#: src/ftp-ls.c:882
msgid "time unknown       "
msgstr "thời gian không rõ      "

#: src/ftp-ls.c:886
msgid "File        "
msgstr "Tập tin        "

#: src/ftp-ls.c:889
msgid "Directory   "
msgstr "Thư mục   "

#: src/ftp-ls.c:892
msgid "Link        "
msgstr "Liên kết        "

#: src/ftp-ls.c:895
msgid "Not sure    "
msgstr "Không chắc    "

#: src/ftp-ls.c:913
#, c-format
msgid " (%s bytes)"
msgstr " (%s byte)"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:202
#, c-format
msgid "Logging in as %s ... "
msgstr "Đăng nhập với tên %s... "

#: src/ftp.c:215 src/ftp.c:268 src/ftp.c:299 src/ftp.c:353 src/ftp.c:468
#: src/ftp.c:519 src/ftp.c:551 src/ftp.c:611 src/ftp.c:675 src/ftp.c:748
#: src/ftp.c:796
msgid "Error in server response, closing control connection.\n"
msgstr "Lỗi trong câu trả lời của máy chủ, đang đóng liên kết điều khiển.\n"

#: src/ftp.c:223
msgid "Error in server greeting.\n"
msgstr "Lỗi trong lời chào mừng của máy chủ.\n"

#: src/ftp.c:231 src/ftp.c:362 src/ftp.c:477 src/ftp.c:560 src/ftp.c:621
#: src/ftp.c:685 src/ftp.c:758 src/ftp.c:806
msgid "Write failed, closing control connection.\n"
msgstr "Ghi nhớ không thành công, đang đóng liên kết điều khiển.\n"

#: src/ftp.c:238
msgid "The server refuses login.\n"
msgstr "Máy chủ từ chối đăng nhập.\n"

#: src/ftp.c:245
msgid "Login incorrect.\n"
msgstr "Đăng nhập không đúng.\n"

#: src/ftp.c:252
msgid "Logged in!\n"
msgstr "Đã đăng nhập!\n"

#: src/ftp.c:277
msgid "Server error, can't determine system type.\n"
msgstr "Lỗi máy chủ, không xác định được dạng hệ thống.\n"

#: src/ftp.c:287 src/ftp.c:596 src/ftp.c:659 src/ftp.c:716
msgid "done.    "
msgstr "đã xong.    "

#: src/ftp.c:341 src/ftp.c:498 src/ftp.c:533 src/ftp.c:779 src/ftp.c:827
msgid "done.\n"
msgstr "đã xong.\n"

#: src/ftp.c:370
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Không rõ loại `%c', đang đóng liên kết điều khiển.\n"

#: src/ftp.c:383
msgid "done.  "
msgstr "đã xong.  "

#: src/ftp.c:389
msgid "==> CWD not needed.\n"
msgstr "==> không cần thiết CWD.\n"

#: src/ftp.c:484
#, c-format
msgid ""
"No such directory `%s'.\n"
"\n"
msgstr ""
"Không có thư mục `%s'.\n"
"\n"

#. do not CWD
#: src/ftp.c:502
msgid "==> CWD not required.\n"
msgstr "==> không yêu cầu CWD.\n"

#: src/ftp.c:567
msgid "Cannot initiate PASV transfer.\n"
msgstr "Không khởi đầu được sự truyền tải THỤĐỘNG.\n"

#: src/ftp.c:571
msgid "Cannot parse PASV response.\n"
msgstr "Không phân tích được câu trả lời THỤĐỘNG.\n"

#: src/ftp.c:588
#, c-format
msgid "couldn't connect to %s:%hu: %s\n"
msgstr "không kết nối được tới %s:%hu: %s\n"

#: src/ftp.c:638
#, c-format
msgid "Bind error (%s).\n"
msgstr "Lỗi bind (%s).\n"

#: src/ftp.c:645
msgid "Invalid PORT.\n"
msgstr "CỔNG không đúng.\n"

#: src/ftp.c:698
#, c-format
msgid ""
"\n"
"REST failed; will not truncate `%s'.\n"
msgstr ""
"\n"
"REST không thành công; sẽ không cắt bớt `%s'.\n"

#: src/ftp.c:705
msgid ""
"\n"
"REST failed, starting from scratch.\n"
msgstr ""
"\n"
"REST không thành công; bắt đầu lại từ đầu.\n"

#: src/ftp.c:766
#, c-format
msgid ""
"No such file `%s'.\n"
"\n"
msgstr ""
"Không có tập tin `%s'.\n"
"\n"

#: src/ftp.c:814
#, c-format
msgid ""
"No such file or directory `%s'.\n"
"\n"
msgstr ""
"Không có tập tin hay thư mục `%s'.\n"
"\n"

#: src/ftp.c:898 src/ftp.c:906
#, c-format
msgid "Length: %s"
msgstr "Chiều dài: %s"

#: src/ftp.c:900 src/ftp.c:908
#, c-format
msgid " [%s to go]"
msgstr " [%s để tới]"

#: src/ftp.c:910
msgid " (unauthoritative)\n"
msgstr " (chưa xác thực)\n"

#: src/ftp.c:936
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, đang đóng kết nối điều khiển.\n"

#: src/ftp.c:944
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Kết nối dữ liệu: %s; "

#: src/ftp.c:961
msgid "Control connection closed.\n"
msgstr "Đã đóng kết nối điều khiển.\n"

#: src/ftp.c:979
msgid "Data transfer aborted.\n"
msgstr "Dừng truyền tải dữ liệu.\n"

#: src/ftp.c:1044
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "Tập tin `%s' đã có ở đó, không nhận nữa.\n"

#: src/ftp.c:1114 src/http.c:1716
#, c-format
msgid "(try:%2d)"
msgstr "(thử:%2d)"

#: src/ftp.c:1180 src/http.c:1975
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' đã ghi [%ld]\n"
"\n"

#: src/ftp.c:1222 src/main.c:890 src/recur.c:377 src/retr.c:596
#, c-format
msgid "Removing %s.\n"
msgstr "Đang xóa bỏ %s.\n"

#: src/ftp.c:1264
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Đang dùng `%s' làm tập tin danh sách tmp.\n"

#: src/ftp.c:1279
#, c-format
msgid "Removed `%s'.\n"
msgstr "Đã xóa `%s'.\n"

#: src/ftp.c:1314
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Độ sâu đệ quy %d vượt quá độ sâu lớn nhất %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1384
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Tập tin ở xa không mới hơn tập tin nội bộ `%s' -- không tải xuống.\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1391
#, c-format
msgid ""
"Remote file is newer than local file `%s' -- retrieving.\n"
"\n"
msgstr ""
"Tập tin ở xa mới hơn tập tin nội bộ `%s' -- đang tải xuống.\n"
"\n"

#. Sizes do not match
#: src/ftp.c:1398
#, c-format
msgid ""
"The sizes do not match (local %ld) -- retrieving.\n"
"\n"
msgstr ""
"Kích thước không tương ứng (nội bộ %ld) -- đang tải xuống.\n"
"\n"

#: src/ftp.c:1415
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Sai tên của liên kết mềm, bỏ qua.\n"

#: src/ftp.c:1432
#, c-format
msgid ""
"Already have correct symlink %s -> %s\n"
"\n"
msgstr ""
"Đã có liên kết mềm đúng %s -> %s\n"
"\n"

#: src/ftp.c:1440
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Đang tạo liên kết mềm %s -> %s\n"

#: src/ftp.c:1451
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Không hỗ trợ liên kết mềm, nhảy qua liên kết mềm `%s'.\n"

#: src/ftp.c:1463
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "Nhảy qua thư mục `%s'.\n"

#: src/ftp.c:1472
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: loại tập tin không biết/không hỗ trợ.\n"

#: src/ftp.c:1499
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: tem đánh dấu thời gian bị lỗi.\n"

#: src/ftp.c:1524
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "Sẽ không nhận thư mục vì độ sâu là %d (max %d).\n"

#: src/ftp.c:1574
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Không giảm xuống thành `%s' vì nó bị loại bỏ/không được thêm.\n"

#: src/ftp.c:1639 src/ftp.c:1652
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "Đang nhả ra `%s'.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1698
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "Không có tương ứng với mẫu `%s'.\n"

#: src/ftp.c:1764
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "Đã viết chỉ mục ở dạng HTML tới `%s' [%ld].\n"

#: src/ftp.c:1769
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "Đã viết chỉ mục ở dạng HTML tới `%s'.\n"

#: src/gen_sslfunc.c:117
msgid "Could not seed OpenSSL PRNG; disabling SSL.\n"
msgstr "Không tìm thấy OpenSSL PRNG, đang tắt bỏ SSL.\n"

#: src/getopt.c:675
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: tùy chọn `%s' không rõ ràng\n"

#: src/getopt.c:700
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: tùy chọn `--%s' không cho phép một tham số\n"

#: src/getopt.c:705
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: tùy chọn `%c%s' không cho phép một tham số\n"

#: src/getopt.c:723 src/getopt.c:896
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: tùy chọn `%s' yêu cầu một tham số\n"

#. --option
#: src/getopt.c:752
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: tùy chọn không nhận ra `--%s'\n"

#. +option or -option
#: src/getopt.c:756
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: tùy chọn không nhận ra `%c%s'\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:782
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: tùy chọn không hợp lệ -- %c\n"

#: src/getopt.c:785
#, c-format
msgid "%s: invalid option -- %c\n"
msgstr "%s: tùy chọn sai -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:815 src/getopt.c:945
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: tùy chọn yêu cầu một tham số -- %c\n"

#: src/getopt.c:862
#, c-format
msgid "%s: option `-W %s' is ambiguous\n"
msgstr "%s: tùy chọn `-W %s' không rõ ràng\n"

#: src/getopt.c:880
#, c-format
msgid "%s: option `-W %s' doesn't allow an argument\n"
msgstr "%s: tùy chọn `-W %s' không cho phép một tham số\n"

#: src/host.c:636
#, c-format
msgid "Resolving %s... "
msgstr "Đang tìm %s... "

#: src/host.c:656 src/host.c:672
#, c-format
msgid "failed: %s.\n"
msgstr "không thành công: %s.\n"

#: src/host.c:674
msgid "failed: timed out.\n"
msgstr "không thành công: vượt quá thời gian chờ.\n"

#: src/host.c:762
msgid "Host not found"
msgstr "Không tìm thấy máy"

#: src/host.c:764
msgid "Unknown error"
msgstr "Lỗi không rõ nguyên nhân"

#: src/html-url.c:293
#, c-format
msgid "%s: Cannot resolve incomplete link %s.\n"
msgstr "%s: Không tìm thấy được liên kết không hoàn chỉnh %s.\n"

#. this is fatal
#: src/http.c:674
msgid "Failed to set up an SSL context\n"
msgstr "Đặt một khung cảnh SSL không thành công\n"

#: src/http.c:680
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "Nạp chứng thực từ %s không thành công\n"

#: src/http.c:684 src/http.c:692
msgid "Trying without the specified certificate\n"
msgstr "Đang thử không dùng chứng thực chỉ ra\n"

#: src/http.c:688
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Lấy chìa khóa chứng thực từ %s không thành công\n"

#: src/http.c:761 src/http.c:1809
msgid "Unable to establish SSL connection.\n"
msgstr "Không thiết lập được kết nối SSL.\n"

#: src/http.c:770
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Đang dùng lại kết nối tới %s: %hu.\n"

#: src/http.c:1034
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "Yêu cầu ghi HTTP không thành công: %s.\n"

#: src/http.c:1039
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s yêu cầu đã gửi, đang đợi câu trả lời... "

#: src/http.c:1083
msgid "End of file while parsing headers.\n"
msgstr "Kết thúc tập tin khi phân tích phần đầu.\n"

#: src/http.c:1093
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Lỗi đọc (%s) trong phần đầu.\n"

#: src/http.c:1128
msgid "No data received"
msgstr "Không nhận được dữ liệu"

#: src/http.c:1130
msgid "Malformed status line"
msgstr "Dòng trạng thái bị lỗi"

#: src/http.c:1135
msgid "(no description)"
msgstr "(không mô tả)"

#: src/http.c:1267
msgid "Authorization failed.\n"
msgstr "Xác thực không thành công.\n"

#: src/http.c:1274
msgid "Unknown authentication scheme.\n"
msgstr "Hệ thống xác thực không rõ.\n"

#: src/http.c:1314
#, c-format
msgid "Location: %s%s\n"
msgstr "Vị trí: %s%s\n"

#: src/http.c:1315 src/http.c:1454
msgid "unspecified"
msgstr "chưa chỉ ra"

#: src/http.c:1316
msgid " [following]"
msgstr " [theo sau]"

#: src/http.c:1383
msgid ""
"\n"
"    The file is already fully retrieved; nothing to do.\n"
"\n"
msgstr ""
"\n"
"    Đã nhận tập tin đầy đủ; không cần làm gì.\n"
"\n"

#: src/http.c:1401
#, c-format
msgid ""
"\n"
"Continued download failed on this file, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Tiếp tục tải tập tin không thành công, có mâu thuẫn với '-c'.\n"
"Đang từ chối cắt bớt tập tin đã có `%s'.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1444
msgid "Length: "
msgstr "Dài: "

#: src/http.c:1449
#, c-format
msgid " (%s to go)"
msgstr " (còn %s)"

#: src/http.c:1454
msgid "ignored"
msgstr "lờ đi"

#: src/http.c:1598
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Cảnh báo: không hỗ trợ wildcard trong HTTP.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1628
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "Tập tin `%s' đã có ở đó, sẽ không nhận.\n"

#: src/http.c:1800
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "Không ghi nhớ được tới `%s' (%s).\n"

#: src/http.c:1819
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "LỖI: Chuyển hướng (%d) mà không có vị trí.\n"

#: src/http.c:1851
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s LỖI %d: %s.\n"

#: src/http.c:1864
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Thiếu phần đầu \"Lần-sửa-cuối-cùng\" -- tắt tem đánh dấu thời gian.\n"

#: src/http.c:1872
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Sai phần đầu \"Lần-sửa-cuối-cùng\" -- lờ đi tem đánh dấu thời gian.\n"

#: src/http.c:1895
#, c-format
msgid ""
"Server file no newer than local file `%s' -- not retrieving.\n"
"\n"
msgstr ""
"Tập tin trên máy chủ không mới hơn tập tin nội bộ `%s' -- không nhận.\n"
"\n"

#: src/http.c:1903
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Kích thước tập tin không tương ứng (nội bộ %ld) - đang nhận.\n"

#: src/http.c:1907
msgid "Remote file is newer, retrieving.\n"
msgstr "Tập tin ở xa mới hơn, đang nhận.\n"

#: src/http.c:1948
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld]\n"
"\n"
msgstr ""
"%s (%s) - `%s' đã ghi [%ld/%ld]\n"
"\n"

#: src/http.c:1998
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - Đóng kết nối tại byte %ld. "

#: src/http.c:2007
#, c-format
msgid ""
"%s (%s) - `%s' saved [%ld/%ld])\n"
"\n"
msgstr ""
"%s (%s) - `%s' đã ghi [%ld/%ld])\n"
"\n"

#: src/http.c:2028
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) - Đóng kết nối tại byte %ld/%ld. "

#: src/http.c:2040
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - Lỗi đọc tại byte %ld (%s)."

#: src/http.c:2049
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - Lỗi đọc tại byte %ld/%ld (%s). "

#: src/init.c:342
#, c-format
msgid "%s: WGETRC points to %s, which doesn't exist.\n"
msgstr "%s: WGETRC chỉ tới %s không tồn tại.\n"

#: src/init.c:398 src/netrc.c:276
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: Không đọc được %s (%s).\n"

#: src/init.c:416 src/init.c:422
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: Lỗi trong %s trên dòng %d.\n"

#: src/init.c:454
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Cảnh báo: Cả wgetrc của hệ thống và người dùng đều chỉ tới `%s'.\n"

#: src/init.c:594
#, c-format
msgid "%s: Invalid --execute command `%s'\n"
msgstr "%s: Câu lệnh --execute không đúng `%s'\n"

#: src/init.c:630
#, c-format
msgid "%s: %s: Invalid boolean `%s', use `on' or `off'.\n"
msgstr "%s: %s: Giá trị boolean sai `%s', hãy dùng `on' hoặc 'off'.\n"

#: src/init.c:673
#, c-format
msgid "%s: %s: Invalid boolean `%s', use always, on, off, or never.\n"
msgstr "%s: %s: Giá trị boolean sai `%s', hãy dùng always, on, off, hoặc never.\n"

#: src/init.c:691
#, c-format
msgid "%s: %s: Invalid number `%s'.\n"
msgstr "%s: %s: Số sai `%s'.\n"

#: src/init.c:930 src/init.c:949
#, c-format
msgid "%s: %s: Invalid byte value `%s'\n"
msgstr "%s: %s: Giá trị byte sai `%s'.\n"

#: src/init.c:974
#, c-format
msgid "%s: %s: Invalid time period `%s'\n"
msgstr "%s: %s: Khoảng thời gian sai `%s'.\n"

#: src/init.c:1051
#, c-format
msgid "%s: %s: Invalid header `%s'.\n"
msgstr "%s: %s: Phần đầu sai `%s'.\n"

#: src/init.c:1106
#, c-format
msgid "%s: %s: Invalid progress type `%s'.\n"
msgstr "%s: %s: Dạng minh họa tiến trình sai `%s'.\n"

#: src/init.c:1157
#, c-format
msgid "%s: %s: Invalid restriction `%s', use `unix' or `windows'.\n"
msgstr "%s: %s: Giới hạn sai `%s', hãy dùng `unix' hoặc `windows'.\n"

#: src/init.c:1198
#, c-format
msgid "%s: %s: Invalid value `%s'.\n"
msgstr "%s: %s: Giá trị sai `%s'.\n"

#: src/log.c:636
#, c-format
msgid ""
"\n"
"%s received, redirecting output to `%s'.\n"
msgstr ""
"\n"
"đã nhận %s, đang chuyển hướng kết quả tới `%s'.\n"

#. Eek!  Opening the alternate log file has failed.  Nothing we
#. can do but disable printing completely.
#: src/log.c:643
#, c-format
msgid "%s: %s; disabling logging.\n"
msgstr "%s: %s; đang tắt bỏ việc ghi sự kiện.\n"

#: src/main.c:127
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Sử dụng: %s [TÙY CHỌN]... [URL]...\n"

#: src/main.c:135
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, một chương trình truyền tải mạng có thể chạy ở dạng daemon.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:140
msgid ""
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"\n"
msgstr ""
"\n"
"Tham số cho các tùy chọn dài cũng là tham số cho các tùy chọn ngắn.\n"
"\n"

#: src/main.c:144
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Bắt đầu:\n"
"  -V,  --version           Hiển thị phiên bản của Wget và thoát.\n"
"  -h,  --help              in trợ giúp này.\n"
"  -b,  --background        chuyển vào nền sau, sau khi bẳt đầu chạy.\n"
"  -e,  --execute=COMMAND   chạy một câu lệnh \"kiểu\" .wgetrc.\n"
"\n"

#: src/main.c:151
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
"Tập tin Ghi sự kiện và đầu vào:\n"
"  -o,  --output-file=FILE     ghi thông báo vào FILE.\n"
"  -a,  --append-output=FILE   thêm thông báo vào FILE.\n"
"  -d,  --debug                in ra thông tin dùng để tìm & sửa lỗi.\n"
"  -q,  --quiet                im lặng (không hiển thị gì).\n"
"  -v,  --verbose              chi tiết (là mặc định).\n"
"  -nv, --non-verbose          tắt bỏ chế độ chi tiết, mà cũng không im lặng.\n"
"  -i,  --input-file=FILE      tải xuống các URL tìm thấy trong FILE.\n"
"  -F,  --force-html           coi tập tin đầu vào có dạng HTML.\n"
"  -B,  --base=URL             thêm URL vào đầu liên kết tương đối trong -F -i file.\n"
"\n"

#: src/main.c:163
msgid ""
"Download:\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"       --retry-connrefused      retry even if connection is refused.\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --progress=TYPE          select progress gauge type.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set all timeout values to SECONDS.\n"
"       --dns-timeout=SECS       set the DNS lookup timeout to SECS.\n"
"       --connect-timeout=SECS   set the connect timeout to SECS.\n"
"       --read-timeout=SECS      set the read timeout to SECS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"       --random-wait            wait from 0...2*WAIT secs between retrievals.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"       --limit-rate=RATE        limit download rate to RATE.\n"
"       --dns-cache=off          disable caching DNS lookups.\n"
"       --restrict-file-names=OS restrict chars in file names to ones OS allows.\n"
"\n"
msgstr ""
"Tải xuống:\n"
"  -t,  --tries=NUMBER           đặt số lần thử thành NUMBER (0 là không giới hạn).\n"
"       --retry-connrefused      cố tải dù kết nối bị từ chối.\n"
"  -O   --output-document=FILE   ghi nhớ tài liệu thành FILE.\n"
"  -nc, --no-clobber             không ghi đè lên tập tin đã có hoặc sử dụng hậu tố .#.\n"
"  -c,  --continue               tải phần còn lại của tập tin đã tải.\n"
"       --progress=TYPE          chọn dạng đo tiến trình.\n"
"  -N,  --timestamping           đừng tải lại tập tin trừ khi mới hơn nội bộ.\n"
"  -S,  --server-response        in ra câu trả lời của máy chủ.\n"
"       --spider                 đừng tải gì cả.\n"
"  -T,  --timeout=SECONDS        đặt tất cả thời gian chờ thành SECONDS.\n"
"       --dns-timeout=SECS       đặt thời gian chờ tìm kiếm DNS thành SECS.\n"
"       --connect-timeout=SECS   đặt thời gian chờ kết nối thành SECS.\n"
"       --read-timeout=SECS      đặt thời gian đọc thành SECS.\n"
"  -w,  --wait=SECONDS           chờ SECONDS giữa các lần tải.\n"
"       --waitretry=SECONDS      chờ 1...SECONDS giữa những lần thử tải một tập tin.\n"
"       --random-wait            chờ từ 0...2*WAIT giây giữa các lần tải.\n"
"  -Y,  --proxy=on/off           bật hay tắt proxy.\n"
"  -Q,  --quota=NUMBER           đặt giới hạn số tải thành NUMBER.\n"
"       --bind-address=ADDRESS   bind tới ADDRESS (tên máy hoặc IP) trên máy nội bộ.\n"
"       --limit-rate=RATE        giới hạn tốc độ thành RATE.\n"
"       --dns-cache=off          tắt bỏ bộ nhớ tạm cho tìm kiếm DNS.\n"
"       --restrict-file-names=OS giới hạn ký tự trong tên tập tin thành những ký tự hệ điều hành OS cho phép.\n"
"\n"

#: src/main.c:188
msgid ""
"Directories:\n"
"  -nd, --no-directories            don't create directories.\n"
"  -x,  --force-directories         force creation of directories.\n"
"  -nH, --no-host-directories       don't create host directories.\n"
"  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\n"
"       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\n"
"\n"
msgstr ""
"Thư mục:\n"
"  -nd, --no-directories            không tạo thư mục.\n"
"  -x,  --force-directories         bắt buộc tạo thư mục.\n"
"  -nH, --no-host-directories       không tạo thư mục cho các máy.\n"
"  -P,  --directory-prefix=PREFIX   ghi tập tin vào PREFIX/...\n"
"       --cut-dirs=NUMBER           bỏ qua NUMBER thành phần của thư mục ở xa.\n"
"\n"

#: src/main.c:196
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
"       --post-data=STRING    use the POST method; send STRING as the data.\n"
"       --post-file=FILE      use the POST method; send contents of FILE.\n"
"\n"
msgstr ""
"Tùy chọn HTTP:\n"
"       --http-user=USER      đặt người dùng http thành USER.\n"
"       --http-passwd=PASS    đặt mật khẩu http thành PASS.\n"
"  -C,  --cache=on/off        (không) cho phép dữ liệu cache của máy chủ (thông thường cho phép).\n"
"  -E,  --html-extension      ghi nhớ mọi tài liệu text/html với \"đuôi\" .html.\n"
"       --ignore-length       lờ đi `Content-Length' trong phần đầu.\n"
"       --header=STRING       chèn chuỗi STRING vào giữa các phần đầu.\n"
"       --proxy-user=USER     dùng USER làm tên người dùng proxy.\n"
"       --proxy-passwd=PASS   dùng PASS làm mật khẩu proxy.\n"
"       --referer=URL         thêm phần đầu `Referer: URL' vào yêu cầu HTTP.\n"
"  -s,  --save-headers        ghi nhớ phần đầu HTTP vào tập tin.\n"
"  -U,  --user-agent=AGENT    lấy AGENT làm tên đại diện thay cho Wget/VERSION.\n"
"       --no-http-keep-alive  không dùng tính năng giữ kết nối HTTP (kết nối cố định).\n"
"       --cookies=off         không dùng cookies.\n"
"       --load-cookies=FILE   nạp cookies từ FILE trước buổi làm việc.\n"
"       --save-cookies=FILE   ghi cookies vào FILE sau buổi làm việc.\n"
"       --post-data=STRING    dùng phương pháp POST; gửi STRING như dữ liệu.\n"
"       --post-file=FILE      dùng phương pháp POST; gửi nội dung của FILE.\n"
"\n"

#: src/main.c:217
msgid ""
"HTTPS (SSL) options:\n"
"       --sslcertfile=FILE     optional client certificate.\n"
"       --sslcertkey=KEYFILE   optional keyfile for this certificate.\n"
"       --egd-file=FILE        file name of the EGD socket.\n"
"       --sslcadir=DIR         dir where hash list of CA's are stored.\n"
"       --sslcafile=FILE       file with bundle of CA's\n"
"       --sslcerttype=0/1      Client-Cert type 0=PEM (default) / 1=ASN1 (DER)\n"
"       --sslcheckcert=0/1     Check the server cert agenst given CA\n"
"       --sslprotocol=0-3      choose SSL protocol; 0=automatic,\n"
"                              1=SSLv2 2=SSLv3 3=TLSv1\n"
"\n"
msgstr ""
"Tùy chọn HTTPS (SSL):\n"
"       --sslcertfile=FILE     chứng thực không bắt buộc của client.\n"
"       --sslcertkey=KEYFILE   tập tin chìa khóa không bắt buộc cho chứng thực này.\n"
"       --egd-file=FILE        tên tập tin của socket EGD.\n"
"       --sslcadir=DIR         thư mục chứa danh sách hash của CA.\n"
"       --sslcafile=FILE       tập tin với các gói CA\n"
"       --sslcerttype=0/1      Dạng Client-Cert 0=PEM (mặc định) / 1=ASN1 (DER)\n"
"       --sslcheckcert=0/1     Kiểm tra chứng thực của máy chủ đưa ra CA này\n"
"       --sslprotocol=0-3      Chọn giao thức SSL; 0=tự động,\n"
"                              1=SSLv2 2=SSLv3 3=TLSv1\n"
"\n"

#: src/main.c:230
msgid ""
"FTP options:\n"
"  -nr, --dont-remove-listing   don't remove `.listing' files.\n"
"  -g,  --glob=on/off           turn file name globbing on or off.\n"
"       --passive-ftp           use the \"passive\" transfer mode.\n"
"       --retr-symlinks         when recursing, get linked-to files (not dirs).\n"
"\n"
msgstr ""
"Tùy chọn FTP:\n"
"  -nr, --dont-remove-listing   không xóa bỏ các tập tin `.listing'.\n"
"  -g,  --glob=on/off           sử dụng hay không wildcard trong tên tập tin.\n"
"       --passive-ftp           sử dụng chế độ truyền tải \"passive\".\n"
"       --retr-symlinks         khi đệ quy, lấy cả tập tin được liên kết chỉ đến (không tải thư mục).\n"
"\n"

#: src/main.c:237
msgid ""
"Recursive retrieval:\n"
"  -r,  --recursive          recursive download.\n"
"  -l,  --level=NUMBER       maximum recursion depth (inf or 0 for infinite).\n"
"       --delete-after       delete files locally after downloading them.\n"
"  -k,  --convert-links      convert non-relative links to relative.\n"
"  -K,  --backup-converted   before converting file X, back up as X.orig.\n"
"  -m,  --mirror             shortcut option equivalent to -r -N -l inf -nr.\n"
"  -p,  --page-requisites    get all images, etc. needed to display HTML page.\n"
"       --strict-comments    turn on strict (SGML) handling of HTML comments.\n"
"\n"
msgstr ""
"Truyền tải đệ quy:\n"
"  -r,  --recursive          tải xuống đệ quy.\n"
"  -l,  --level=NUMBER       độ sâu lớn nhất của đệ quy (inf hoặc 0 để không giới hạn).\n"
"       --delete-after       xóa các tập tin nội bộ sau khi tải chúng.\n"
"  -k,  --convert-links      chuyển các liên kết không tương đối thành tương đối.\n"
"  -K,  --backup-converted   trước khi chuyển đổi tập tin A, sao lưu thành A.orig.\n"
"  -m,  --mirror             tùy chọn rút gọn tương đương với -r -N -l inf -nr.\n"
"  -p,  --page-requisites    lấy tất cả hình ảnh, v.v... cần để hiển thị trang HTML.\n"
"       --strict-comments    bật điều khiển chính xác (SGML) của chú thích HTML.\n"
"\n"

#: src/main.c:248
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
"Chấp nhận/nhả ra đệ quy:\n"
"  -A,  --accept=LIST                danh sách những phần mở rộng (phân cách nhau                                    bởi dấu \":\") được chấp nhận.\n"
"  -R,  --reject=LIST                danh sách những phần mở rộng (phân cách nhau\t\t\t\t\t\t\t\t\t \t\t\t\t    bởi dấu \":\") bị nhả ra.\n"
"  -D,  --domains=LIST               danh sách những miền (phân cách nhau bởi dấu\t\t\t\t\t\t\t\t\t \t\t\t\t    \":\") được chấp nhận.\n"
"       --exclude-domains=LIST       danh sách những miền (phân cách nhau bởi dấu\t\t\t\t\t\t\t\t\t \t\t\t\t    \":\") bị nhả ra.\n"
"       --follow-ftp                 đi theo liên kết FTP từ tài liệu HTML.\n"
"       --follow-tags=LIST           danh sách những thẻ HTML (phân cách nhau bởi\t\t\t \t    \t\t\t    dấu \":\") đi theo.\n"
"  -G,  --ignore-tags=LIST           danh sách những thẻ HTML (phân cách nhau bởi\t\t\t \t    \t\t\t    dấu \":\") lờ đi.\n"
"  -H,  --span-hosts                 đi tới các máy ngoại quốc khi đệ quy.\n"
"  -L,  --relative                   chỉ đi theo các liên kết tương đối.\n"
"  -I,  --include-directories=LIST   danh sách những thư mục cho phép.\n"
"  -X,  --exclude-directories=LIST   danh sách những thư mục không cho phép.\n"
"  -np, --no-parent                  không đi ngược lên thư mục mẹ.\n"
"\n"

#: src/main.c:263
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Gửi báo cáo lỗi (bug) và đề nghị tới <bug-wget@gnu.org>.\n"

#: src/main.c:465
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: không biên dịch với hỗ trợ báo lỗi (debug).\n"

#: src/main.c:517
msgid "Copyright (C) 2003 Free Software Foundation, Inc.\n"
msgstr "Đăng ký bản quyền (C) 2003 Free Software Foundation, Inc.\n"

#: src/main.c:519
msgid ""
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"Chương trình này được phát hành với hy vọng rằng nó sẽ trở nên hữu ích,\n"
"nhưng nó KHÔNG KÈM THEO BẤT KỲ SỰ BẢO ĐẢM NÀO, ngay cả những đảm\n"
"bảo ngầm hiểu về việc THƯƠNG MẠI HÓA hay PHẢI PHÙ HỢP VỚI MỘT MỤC ĐÍCH\n"
"CỤ THỂ NÀO. Hãy tham khảo giấy phép GNU General Public License để biết thêm chi tiết.\n"

#: src/main.c:524
msgid ""
"\n"
"Originally written by Hrvoje Niksic <hniksic@xemacs.org>.\n"
msgstr ""
"\n"
"Được viết bởi Hrvoje Niksic <hniksic@xemacs.org>.\n"

#: src/main.c:703
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: tùy chọn không cho phép -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:706 src/main.c:748 src/main.c:794
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Hãy thử `%s --help' để biết thêm tùy chọn.\n"

#: src/main.c:774
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Không thể cùng một lúc thông báo chi tiết và im lặng.\n"

#: src/main.c:780
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Không thể cùng một lúc đánh dấu thời gian và không ghi đè tập tin cũ.\n"

#. No URL specified.
#: src/main.c:789
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: thiếu URL\n"

#: src/main.c:905
#, c-format
msgid "No URLs found in %s.\n"
msgstr "Không tìm thấy URL trong %s.\n"

#: src/main.c:914
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"KẾT THÚC --%s--\n"
"Đã tải: %s byte trong %d tập tin\n"

#: src/main.c:920
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Đã VƯỢT QUÁ giới hạn truyền tải (%s byte)!\n"

#: src/mswindows.c:147
msgid "Continuing in background.\n"
msgstr "Tiếp tục trong nền sau.\n"

#: src/mswindows.c:149 src/utils.c:487
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Kết quả sẽ được ghi vào `%s'.\n"

#: src/mswindows.c:245
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "Đang chạy WinHelp %s\n"

#: src/mswindows.c:272 src/mswindows.c:279
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Không tìm thấy driver socket có thể sử dụng.\n"

#: src/netrc.c:380
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: cảnh báo: \"%s\" dấu hiệu xuất hiện trước bất kỳ tên máy nào\n"

#: src/netrc.c:411
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: không rõ dấu hiệu \"%s\"\n"

#: src/netrc.c:475
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Sử dụng: %s NETRC [TÊN MÁY]\n"

#: src/netrc.c:485
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: không thể stat %s: %s\n"

#. Align the [ skipping ... ] line with the dots.  To do
#. that, insert the number of spaces equal to the number of
#. digits in the skipped amount in K.
#: src/progress.c:234
#, c-format
msgid ""
"\n"
"%*s[ skipping %dK ]"
msgstr ""
"\n"
"%*s[ nhảy qua %dK ]"

#: src/progress.c:401
#, c-format
msgid "Invalid dot style specification `%s'; leaving unchanged.\n"
msgstr "Lỗi trong định dạng dấu chấm `%s', để nguyên.\n"

#: src/recur.c:378
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Đang xóa bỏ %s vì nó sẽ bị nhả ra.\n"

#: src/res.c:549
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "Đang nạp robots.txt; xin hãy lờ đi các thông báo lỗi.\n"

#: src/retr.c:400
#, c-format
msgid "Error parsing proxy URL %s: %s.\n"
msgstr "Lỗi phân tích URL của proxy %s: %s.\n"

#: src/retr.c:408
#, c-format
msgid "Error in proxy URL %s: Must be HTTP.\n"
msgstr "Lỗi trong URL của proxy %s: Phải là HTTP.\n"

#: src/retr.c:493
#, c-format
msgid "%d redirections exceeded.\n"
msgstr "Vượt quá giới hạn %d lần chuyển hướng.\n"

#: src/retr.c:617
msgid ""
"Giving up.\n"
"\n"
msgstr ""
"Đầu hàng.\n"
"\n"

#: src/retr.c:617
msgid ""
"Retrying.\n"
"\n"
msgstr ""
"Đang thử lại.\n"
"\n"

#: src/url.c:621
msgid "No error"
msgstr "Không có lỗi"

#: src/url.c:623
msgid "Unsupported scheme"
msgstr "Sơ đồ không hỗ trợ"

#: src/url.c:625
msgid "Empty host"
msgstr "Máy rỗng"

#: src/url.c:627
msgid "Bad port number"
msgstr "Số thứ tự cổng xấu"

#: src/url.c:629
msgid "Invalid user name"
msgstr "Sai tên người dùng"

#: src/url.c:631
msgid "Unterminated IPv6 numeric address"
msgstr "Địa chỉ số IPv6 không có giới hạn"

#: src/url.c:633
msgid "IPv6 addresses not supported"
msgstr "Không hỗ trợ địa chỉ IPv6"

#: src/url.c:635
msgid "Invalid IPv6 numeric address"
msgstr "Địa chỉ IPv6 không đúng"

#: src/utils.c:120
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Không đủ bộ nhớ.\n"

#. parent, no error
#: src/utils.c:485
#, c-format
msgid "Continuing in background, pid %d.\n"
msgstr "Tiếp tục trong nền sau, pid %d.\n"

#: src/utils.c:529
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "Bỏ liên kết mềm `%s' không thành công: %s\n"
