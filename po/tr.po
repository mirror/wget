# Turkish translations for wget messages.
# Copyright (C) 2001 Free Software Foundation, Inc.
# Nilgün Belma Bugüner <nilgun@fide.org>, 2001.
#
msgid ""
msgstr ""
"Project-Id-Version: wget 1.7-pre1\n"
"POT-Creation-Date: 2001-05-26 11:07+0200\n"
"PO-Revision-Date: 2001-06-01 00:19+300\n"
"Last-Translator: Nilgün Belma Bugüner <nilgun@fide.org>\n"
"Language-Team: Turkish <tr@li.org>\n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=ISO-8859-9\n"
"Content-Transfer-Encoding: 8bit\n"
"X-Generator: KBabel 0.9.2alpha\n"

#: src/cookies.c:588
#, c-format
msgid "Error in Set-Cookie, field `%s'"
msgstr "Set-Cookie, `%s' alanýnda hata"

#: src/cookies.c:612
#, c-format
msgid "Syntax error in Set-Cookie at character `%c'.\n"
msgstr "Set-Cookie `%c' karakterinde sözdizimi hatasý.\n"

#: src/cookies.c:620
msgid "Syntax error in Set-Cookie: premature end of string.\n"
msgstr "Set-Cookie'de sözdizimi hatasý: dizge sonu eksik.\n"

#: src/cookies.c:1352
#, c-format
msgid "Cannot open cookies file `%s': %s\n"
msgstr "Çerezler dosyasý %s açýlamýyor: %s\n"

#: src/cookies.c:1364
#, c-format
msgid "Error writing to `%s': %s\n"
msgstr "`%s'e yazýlýrken hata: %s\n"

#: src/cookies.c:1368
#, c-format
msgid "Error closing `%s': %s\n"
msgstr "`%s' kapatýlýrken hata: %s\n"

#: src/ftp-ls.c:787
msgid "Usupported listing type, trying Unix listing parser.\n"
msgstr "Desteklenmeyen listeleme türü, Unix liste çözümleyici deneniyor.\n"

#: src/ftp-ls.c:832 src/ftp-ls.c:834
#, c-format
msgid "Index of /%s on %s:%d"
msgstr "/%s indeksi (%s de):%d"

#: src/ftp-ls.c:856
msgid "time unknown       "
msgstr "zaman bilinmiyor    "

#: src/ftp-ls.c:860
msgid "File        "
msgstr "Dosya       "

#: src/ftp-ls.c:863
msgid "Directory   "
msgstr "Dizin       "

#: src/ftp-ls.c:866
msgid "Link        "
msgstr "Bað         "

#: src/ftp-ls.c:869
msgid "Not sure    "
msgstr "Kesin deðil "

#: src/ftp-ls.c:887
#, c-format
msgid " (%s bytes)"
msgstr "  (%s bayt)"

#. Login to the server:
#. First: Establish the control connection.
#: src/ftp.c:149 src/http.c:623
#, c-format
msgid "Connecting to %s:%hu... "
msgstr "%s e baðlanýlýyor:%hu..."

#: src/ftp.c:171 src/ftp.c:538 src/http.c:640
#, c-format
msgid "Connection to %s:%hu refused.\n"
msgstr "%s e baðlanýlýyor:%hu reddedildi.\n"

#. Second: Login with proper USER/PASS sequence.
#: src/ftp.c:192 src/http.c:651
msgid "connected!\n"
msgstr "baðlantý kuruldu!\n"

#: src/ftp.c:193
#, c-format
msgid "Logging in as %s ... "
msgstr "%s olarak oturuma giriliyor ... "

#: src/ftp.c:202 src/ftp.c:255 src/ftp.c:287 src/ftp.c:335 src/ftp.c:428
#: src/ftp.c:480 src/ftp.c:574 src/ftp.c:647 src/ftp.c:708 src/ftp.c:756
msgid "Error in server response, closing control connection.\n"
msgstr "Sunucu cevabýnda hata, kontrol baðlantýsý kapatýlýyor.\n"

#: src/ftp.c:210
msgid "Error in server greeting.\n"
msgstr "Sunucu karþýlama iletisinde hata.\n"

#: src/ftp.c:218 src/ftp.c:344 src/ftp.c:437 src/ftp.c:489 src/ftp.c:584
#: src/ftp.c:657 src/ftp.c:718 src/ftp.c:766
msgid "Write failed, closing control connection.\n"
msgstr "Yazma baþarýsýz, kontrol baðlantýsý kapatýlýyor.\n"

#: src/ftp.c:225
msgid "The server refuses login.\n"
msgstr "Sunucu oturum açmayý reddetti.\n"

#: src/ftp.c:232
msgid "Login incorrect.\n"
msgstr "Oturum açma baþarýsýz.\n"

#: src/ftp.c:239
msgid "Logged in!\n"
msgstr "Oturum açýldý!\n"

#: src/ftp.c:264
msgid "Server error, can't determine system type.\n"
msgstr "Sunucu hatasý, sistem türü saptanamadý.\n"

#: src/ftp.c:274 src/ftp.c:559 src/ftp.c:631 src/ftp.c:688
msgid "done.    "
msgstr "tamam.   "

#: src/ftp.c:324 src/ftp.c:458 src/ftp.c:739 src/ftp.c:787 src/url.c:1429
msgid "done.\n"
msgstr "tamam.\n"

#: src/ftp.c:352
#, c-format
msgid "Unknown type `%c', closing control connection.\n"
msgstr "Tür `%c' bilinmiyor, kontrol baðlantýsý kapatýlýyor.\n"

#: src/ftp.c:365
msgid "done.  "
msgstr "tamam.  "

#: src/ftp.c:371
msgid "==> CWD not needed.\n"
msgstr "==> CWD kullanýlmadý.\n"

#: src/ftp.c:444
#, c-format
msgid "No such directory `%s'.\n\n"
msgstr "`%s' diye bir dizin yok.\n\n"

#. do not CWD
#: src/ftp.c:462
msgid "==> CWD not required.\n"
msgstr "==> CWD gerekli deðil.\n"

#: src/ftp.c:496
msgid "Cannot initiate PASV transfer.\n"
msgstr "PASV aktarýmý baþlatýlamadý.\n"

#: src/ftp.c:500
msgid "Cannot parse PASV response.\n"
msgstr "PASV cevabý çözümlenemedi.\n"

#: src/ftp.c:514
#, c-format
msgid "Will try connecting to %s:%hu.\n"
msgstr "%s e baðlantý denenecek:%hu.\n"

#: src/ftp.c:601
#, c-format
msgid "Bind error (%s).\n"
msgstr "Baðlanma hatasý (%s).\n"

#: src/ftp.c:617
msgid "Invalid PORT.\n"
msgstr "PORT geçersiz.\n"

#: src/ftp.c:670
#, c-format
msgid "\nREST failed; will not truncate `%s'.\n"
msgstr "\nREST baþarýsýz; `%s' devam etmeyecek.\n"

#: src/ftp.c:677
msgid "\nREST failed, starting from scratch.\n"
msgstr "\nREST baþarýsýz, baþtan baþlanýyor.\n"

#: src/ftp.c:726
#, c-format
msgid "No such file `%s'.\n\n"
msgstr "`%s' diye bir dosya yok.\n\n"

#: src/ftp.c:774
#, c-format
msgid "No such file or directory `%s'.\n\n"
msgstr "`%s' diye bir dosya ya da dizin yok.\n\n"

#: src/ftp.c:858 src/ftp.c:866
#, c-format
msgid "Length: %s"
msgstr "Uzunluk: %s"

#: src/ftp.c:860 src/ftp.c:868
#, c-format
msgid " [%s to go]"
msgstr " [%s gider]"

#: src/ftp.c:870
msgid " (unauthoritative)\n"
msgstr " (yetkin deðil)\n"

#: src/ftp.c:897
#, c-format
msgid "%s: %s, closing control connection.\n"
msgstr "%s: %s, kontrol baðlantýsý kapatýlýyor.\n"

#: src/ftp.c:905
#, c-format
msgid "%s (%s) - Data connection: %s; "
msgstr "%s (%s) - Veri baðlantýsý: %s; "

#: src/ftp.c:922
msgid "Control connection closed.\n"
msgstr "Kontrol baðlantýsý kapatýldý.\n"

#: src/ftp.c:940
msgid "Data transfer aborted.\n"
msgstr "Veri aktarýmý kesildi.\n"

#: src/ftp.c:1004
#, c-format
msgid "File `%s' already there, not retrieving.\n"
msgstr "`%s' dosyasý zaten var, alýnmayacak.\n"

#: src/ftp.c:1074 src/http.c:1501
#, c-format
msgid "(try:%2d)"
msgstr "(deneme:%2d)"

#: src/ftp.c:1138 src/http.c:1752
#, c-format
msgid "%s (%s) - `%s' saved [%ld]\n\n"
msgstr "%s (%s) - `%s' kaydedildi [%ld]\n\n"

#: src/ftp.c:1180 src/main.c:809 src/recur.c:483 src/retr.c:566
#, c-format
msgid "Removing %s.\n"
msgstr "%s kaldýrýlýyor.\n"

#: src/ftp.c:1220
#, c-format
msgid "Using `%s' as listing tmp file.\n"
msgstr "Listeleme geçici dosyasý olarak `%s' kullanýlýyor.\n"

#: src/ftp.c:1232
#, c-format
msgid "Removed `%s'.\n"
msgstr "`%s' kaldýrýldý.\n"

#: src/ftp.c:1268
#, c-format
msgid "Recursion depth %d exceeded max. depth %d.\n"
msgstr "Yineleme derinliði %d aþýldý. En fazla derinlik %d.\n"

#. Remote file is older, file sizes can be compared and
#. are both equal.
#: src/ftp.c:1329
#, c-format
msgid "Remote file no newer than local file `%s' -- not retrieving.\n"
msgstr "Uzak dosya yerel dosya %s'den daha yeni deðil -- alýnmayacak.\n\n"

#. Remote file is newer or sizes cannot be matched
#: src/ftp.c:1336
#, c-format
msgid "Remote file is newer than local file `%s' -- retrieving.\n\n"
msgstr "Uzak dosya yerel dosya %s'den daha yeni  -- alýnýyor.\n\n"

#. Sizes do not match
#: src/ftp.c:1343
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n\n"
msgstr "Uzunluklarý ayný deðil (yerel %ld), -- alýnýyor.\n"

#: src/ftp.c:1360
msgid "Invalid name of the symlink, skipping.\n"
msgstr "Sembolik baðýn ismi geçersiz, atlanýyor.\n"

#: src/ftp.c:1377
#, c-format
msgid "Already have correct symlink %s -> %s\n\n"
msgstr "Zaten doðru sembolik bað var: %s -> %s\n\n"

#: src/ftp.c:1385
#, c-format
msgid "Creating symlink %s -> %s\n"
msgstr "Sembolik bað oluþturuluyor: %s -> %s\n"

#: src/ftp.c:1396
#, c-format
msgid "Symlinks not supported, skipping symlink `%s'.\n"
msgstr "Sembolik bað desteklenmiyor. `%s' sembolik baðý atlanýyor.\n"

#: src/ftp.c:1408
#, c-format
msgid "Skipping directory `%s'.\n"
msgstr "`%s' dizini atlanýyor.\n"

#: src/ftp.c:1417
#, c-format
msgid "%s: unknown/unsupported file type.\n"
msgstr "%s: bilinmeyen/desteklenmeyen dosya türü.\n"

#: src/ftp.c:1444
#, c-format
msgid "%s: corrupt time-stamp.\n"
msgstr "%s: zaman damgasý bozuk.\n"

#: src/ftp.c:1465
#, c-format
msgid "Will not retrieve dirs since depth is %d (max %d).\n"
msgstr "%d derinliðindeki dizinler alýnamayacak (en çok %d)\n"

#: src/ftp.c:1511
#, c-format
msgid "Not descending to `%s' as it is excluded/not-included.\n"
msgstr "Dýþlanan/içerilmeyen olduðundan dolayý `%s' e inilmiyor.\n"

#: src/ftp.c:1558
#, c-format
msgid "Rejecting `%s'.\n"
msgstr "`%s' reddediliyor.\n"

#. No luck.
#. #### This message SUCKS.  We should see what was the
#. reason that nothing was retrieved.
#: src/ftp.c:1605
#, c-format
msgid "No matches on pattern `%s'.\n"
msgstr "`%s' kalýbýna uygun sonuç gelmedi.\n"

#: src/ftp.c:1670
#, c-format
msgid "Wrote HTML-ized index to `%s' [%ld].\n"
msgstr "HTMLeþtirilmiþ indeks `%s' e yazýldý [%ld].\n"

#: src/ftp.c:1675
#, c-format
msgid "Wrote HTML-ized index to `%s'.\n"
msgstr "HTMLeþtirilmiþ indeks `%s' e yazýldý.\n"

#: src/getopt.c:454
#, c-format
msgid "%s: option `%s' is ambiguous\n"
msgstr "%s: seçenek `%s' belirsiz\n"

#: src/getopt.c:478
#, c-format
msgid "%s: option `--%s' doesn't allow an argument\n"
msgstr "%s: seçenek `--%s' argümansýz kullanýlýr\n"

#: src/getopt.c:483
#, c-format
msgid "%s: option `%c%s' doesn't allow an argument\n"
msgstr "%s: seçenek `%c%s' argümansýz kullanýlýr\n"

#: src/getopt.c:498
#, c-format
msgid "%s: option `%s' requires an argument\n"
msgstr "%s: seçenek `%s' bir argümanla kullanýlýr\n"

#. --option
#: src/getopt.c:528
#, c-format
msgid "%s: unrecognized option `--%s'\n"
msgstr "%s: `--%s' seçeneði bilinmiyor\n"

#. +option or -option
#: src/getopt.c:532
#, c-format
msgid "%s: unrecognized option `%c%s'\n"
msgstr "%s: `%c%s' seçeneði bilinmiyor\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:563
#, c-format
msgid "%s: illegal option -- %c\n"
msgstr "%s: kuraldýþý seçenek -- %c\n"

#. 1003.2 specifies the format of this message.
#: src/getopt.c:602
#, c-format
msgid "%s: option requires an argument -- %c\n"
msgstr "%s: seçenek bir argümanla kullanýlýr -- %c\n"

#: src/host.c:374
msgid "Host not found"
msgstr "Makina bulunamadý"

#: src/host.c:376
msgid "Unknown error"
msgstr "Hata anlaþýlamadý"

#. this is fatal
#: src/http.c:554
msgid "Failed to set up an SSL context\n"
msgstr "Bir SSL baðlamý belirlenemedi\n"

#: src/http.c:560
#, c-format
msgid "Failed to load certificates from %s\n"
msgstr "Sertifikalar %s'den yüklenemedi\n"

#: src/http.c:564 src/http.c:572
msgid "Trying without the specified certificate\n"
msgstr "Belirtilen setifikasýz deneniyor\n"

#: src/http.c:568
#, c-format
msgid "Failed to get certificate key from %s\n"
msgstr "Sertifika anahtarý %s'den alýnamadý\n"

#: src/http.c:662 src/http.c:1592
msgid "Unable to establish SSL connection.\n"
msgstr "SSL baðlantýsý kurulamýyor.\n"

#: src/http.c:670
#, c-format
msgid "Reusing connection to %s:%hu.\n"
msgstr "Baðlantý tekrar kullanýlýyor: %s:%hu.\n"

#: src/http.c:860
#, c-format
msgid "Failed writing HTTP request: %s.\n"
msgstr "HTTP isteðini yazma baþarýsýz: %s.\n"

#: src/http.c:865
#, c-format
msgid "%s request sent, awaiting response... "
msgstr "%s isteði gönderildi, cevap bekleniyor... "

#: src/http.c:909
msgid "End of file while parsing headers.\n"
msgstr "Baþlýklar çözümlenirken dosya sonuyla karþýlaþýldý.\n"

#: src/http.c:919
#, c-format
msgid "Read error (%s) in headers.\n"
msgstr "Baþlýklar okunurken hata (%s).\n"

#: src/http.c:958
msgid "No data received"
msgstr "Alýnan veri yok"

#: src/http.c:960
msgid "Malformed status line"
msgstr "Durum satýrý bozuk"

#: src/http.c:965
msgid "(no description)"
msgstr "(açýklama yok)"

#: src/http.c:1088
msgid "Authorization failed.\n"
msgstr "Yetkilendirme baþarýsýz.\n"

#: src/http.c:1095
msgid "Unknown authentication scheme.\n"
msgstr "Kimlik tanýmlama þemasý bilinmiyor.\n"

#: src/http.c:1135
#, c-format
msgid "Location: %s%s\n"
msgstr "Yer: %s%s\n"

#: src/http.c:1136 src/http.c:1268
msgid "unspecified"
msgstr "belirtilmeyen"

#: src/http.c:1137
msgid " [following]"
msgstr " [izleyen]"

#: src/http.c:1199
msgid "\n    The file is already fully retrieved; nothing to do.\n\n"
msgstr "\n    Dosya zaten alýnmýþtý; birþey yapýlmadý.\n\n"

#: src/http.c:1215
#, c-format
msgid ""
"\n"
"The server does not support continued downloads, which conflicts with `-c'.\n"
"Refusing to truncate existing file `%s'.\n"
"\n"
msgstr ""
"\n"
"Sunucu kesilen indirme iþlemine devam etmeyi desteklemiyor,\n"
"bu da `-c' ile çeliþiyor. `%s' dosyasý alýnamýyor.\n"
"\n"

#. No need to print this output if the body won't be
#. downloaded at all, or if the original server response is
#. printed.
#: src/http.c:1258
msgid "Length: "
msgstr "Uzunluk: "

#: src/http.c:1263
#, c-format
msgid " (%s to go)"
msgstr " (%s gider)"

#: src/http.c:1268
msgid "ignored"
msgstr "yoksayýldý"

#: src/http.c:1398
msgid "Warning: wildcards not supported in HTTP.\n"
msgstr "Uyarý: HTTP ile genel arama karakterleri kullanýlamaz.\n"

#. If opt.noclobber is turned on and file already exists, do not
#. retrieve the file
#: src/http.c:1416
#, c-format
msgid "File `%s' already there, will not retrieve.\n"
msgstr "`%s' dosyasý zaten var, alýnmayacak.\n"

#: src/http.c:1584
#, c-format
msgid "Cannot write to `%s' (%s).\n"
msgstr "`%s'e yazýlamadý (%s).\n"

#: src/http.c:1601
#, c-format
msgid "ERROR: Redirection (%d) without location.\n"
msgstr "HATA: Yönlendirmede (%d) yer belirtilmemiþ.\n"

#: src/http.c:1629
#, c-format
msgid "%s ERROR %d: %s.\n"
msgstr "%s HATA %d: %s.\n"

#: src/http.c:1641
msgid "Last-modified header missing -- time-stamps turned off.\n"
msgstr "Son deðiþiklik yapýlan baþlýk kayýp -- zaman damgasý kapatýldý.\n"

#: src/http.c:1649
msgid "Last-modified header invalid -- time-stamp ignored.\n"
msgstr "Son deðiþiklik yapýlan baþlýk geçersiz -- zaman damgasý yoksayýldý.\n"

#: src/http.c:1672
#, c-format
msgid "Server file no newer than local file `%s' -- not retrieving.\n\n"
msgstr "Sunucudaki dosya yerel dosya %s'den daha yeni deðil -- alýnmayacak.\n\n"

#: src/http.c:1679
#, c-format
msgid "The sizes do not match (local %ld) -- retrieving.\n"
msgstr "Uzunluklarý ayný deðil (yerel %ld), -- alýnýyor.\n"

#: src/http.c:1683
msgid "Remote file is newer, retrieving.\n"
msgstr "Uzak dosya daha yeni, alýnýyor.\n"

#: src/http.c:1727
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld]\n\n"
msgstr "%s (%s) - `%s' kaydedildi [%ld/%ld]\n\n"

#: src/http.c:1773
#, c-format
msgid "%s (%s) - Connection closed at byte %ld. "
msgstr "%s (%s) - %ld baytta baðlantý kapandý. "

#: src/http.c:1781
#, c-format
msgid "%s (%s) - `%s' saved [%ld/%ld])\n\n"
msgstr "%s (%s) - `%s' kaydedildi [%ld/%ld])\n\n"

#: src/http.c:1800
#, c-format
msgid "%s (%s) - Connection closed at byte %ld/%ld. "
msgstr "%s (%s) -  %ld/%ld baytta baðlantý kapandý. "

#: src/http.c:1811
#, c-format
msgid "%s (%s) - Read error at byte %ld (%s)."
msgstr "%s (%s) - %ld baytta okuma hatasý (%s)."

#: src/http.c:1819
#, c-format
msgid "%s (%s) - Read error at byte %ld/%ld (%s). "
msgstr "%s (%s) - %ld/%ld baytta okuma hatasý (%s). "

#: src/init.c:348 src/netrc.c:267
#, c-format
msgid "%s: Cannot read %s (%s).\n"
msgstr "%s: %s okunamadý (%s).\n"

#: src/init.c:366 src/init.c:372
#, c-format
msgid "%s: Error in %s at line %d.\n"
msgstr "%s: %s de hata (%d satýrýnda).\n"

#: src/init.c:404
#, c-format
msgid "%s: Warning: Both system and user wgetrc point to `%s'.\n"
msgstr "%s: Uyarý: Sistem ve kullanýcý wgetrc dosyalarýnýn her ikisi de %s gösteriyor.\n"

#: src/init.c:496
#, c-format
msgid "%s: BUG: unknown command `%s', value `%s'.\n"
msgstr "%s: Yazýlým HATAsý: `%s' komutu, `%s' deðeriyle anlaþýlamadý.\n"

#: src/init.c:528
#, c-format
msgid "%s: %s: Cannot convert `%s' to an IP address.\n"
msgstr "%s: %s: `%s' bir IP adresine dönüþtürülemez.\n"

#: src/init.c:558
#, c-format
msgid "%s: %s: Please specify on or off.\n"
msgstr "%s: %s: Lütfen on ya da off olarak belirtin.\n"

#: src/init.c:602
#, c-format
msgid "%s: %s: Please specify always, on, off, or never.\n"
msgstr "%s: %s: Lütfen always (her zaman), on, off veya never (asla) olarak belirtin.\n"

#: src/init.c:621 src/init.c:918 src/init.c:940 src/init.c:1004
#, c-format
msgid "%s: %s: Invalid specification `%s'.\n"
msgstr "%s: %s: `%s' özelliði geçersiz.\n"

#: src/init.c:774 src/init.c:796 src/init.c:818 src/init.c:844
#, c-format
msgid "%s: Invalid specification `%s'\n"
msgstr "%s: `%s' özelliði geçersiz.\n"

#: src/main.c:119
#, c-format
msgid "Usage: %s [OPTION]... [URL]...\n"
msgstr "Kullanýmý: %s [SEÇENEK]... [URL]...\n"

#: src/main.c:127
#, c-format
msgid "GNU Wget %s, a non-interactive network retriever.\n"
msgstr "GNU Wget %s, bir etkileþimsiz að eriþimci.\n"

#. Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
#. don't bitch.  Also, it makes translation much easier.
#: src/main.c:132
msgid "\nMandatory arguments to long options are mandatory for short options too.\n\n"
msgstr "\nUzun seçeneklerdeki zorunlu argümanlar kýsa seçeneklerde de zorunludur.\n\n"

#: src/main.c:136
msgid ""
"Startup:\n"
"  -V,  --version           display the version of Wget and exit.\n"
"  -h,  --help              print this help.\n"
"  -b,  --background        go to background after startup.\n"
"  -e,  --execute=COMMAND   execute a `.wgetrc'-style command.\n"
"\n"
msgstr ""
"Baþlatma:\n"
"  -V,  --version           Wget sürümünü gösterir ve çýkar.\n"
"  -h,  --help              bu iletiyi gösterir.\n"
"  -b,  --background        baþlatýldýktan sonra ardalana gider.\n"
"  -e,  --execute=KOMUT     bir `.wgetrc' KOMUTunu çalýþtýrýr.\n"
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
"Oturum açma ve girdi dosyasý:\n"
"  -o,  --output-file=DOSYA    iletileri DOSYA ya yazar.\n"
"  -a,  --append-output=DOSYA  iletileri DOSYAya ekler.\n"
"  -d,  --debug                hata ayýklama iletileri gösterir.\n"
"  -q,  --quiet                sessiz (çýktý verilmez).\n"
"  -v,  --verbose              çýktý daha ayrýntýlý olur (öntanýmlý).\n"
"  -nv, --non-verbose          çýktý ayrýntýlý olmaz.\n"
"  -i,  --input-file=DOSYA     DOSYAda bulunan URLleri indirir.\n"
"  -F,  --force-html           girdi dosyasý HTML olarak iþlenir.\n"
"  -B,  --base=URL             -F -i DOSYA içindeki göreceli baðlara\n"
"                              önhazýrlýk olarak URL atar.\n"
"  --sslcertfile=DOSYA         istemci sertifikasý (isteðe baðlý).\n"
"  --sslcertkey=ANAHTARDOSYASI istemci sertifikasý için ANAHTAR DOSYASI.\n"
"\n"

#: src/main.c:157
msgid ""
"Download:\n"
"       --bind-address=ADDRESS   bind to ADDRESS (hostname or IP) on local host.\n"
"  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\n"
"  -O   --output-document=FILE   write documents to FILE.\n"
"  -nc, --no-clobber             don't clobber existing files or use .# suffixes.\n"
"  -c,  --continue               resume getting a partially-downloaded file.\n"
"       --dot-style=STYLE        set retrieval display style.\n"
"  -N,  --timestamping           don't re-retrieve files unless newer than local.\n"
"  -S,  --server-response        print server response.\n"
"       --spider                 don't download anything.\n"
"  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\n"
"  -w,  --wait=SECONDS           wait SECONDS between retrievals.\n"
"       --waitretry=SECONDS      wait 1...SECONDS between retries of a retrieval.\n"
"  -Y,  --proxy=on/off           turn proxy on or off.\n"
"  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\n"
"\n"
msgstr ""
"Ýndirme:\n"
"       --bind-address=ADRES     ADRESe (makina adý ya da IP) baðlanýr.\n"
"  -t,  --tries=SAYI             tekrar SAYIsý (0 sýnýrsýz).\n"
"  -O   --output-document=DOSYA  belgeleri DOSYAya yazar.\n"
"  -nc, --no-clobber             .# önekli veya mevcut dosyalarýn üstüne yazýlmaz.\n"
"  -c,  --continue               yarým kalan bir dosyanýn alýmýný yeniden baþlatýr.\n"
"       --dot-style=TiP          iþlemin göstergesini belirtir.\n"
"  -N,  --timestamping           yerel dosyadan daha eskiyse iþleme baþlamaz.\n"
"  -S,  --server-response        sunucu cevabýný gösterir.\n"
"       --spider                 hiçbir þey indirilmez.\n"
"  -T,  --timeout=SANÝYE         okuma SANÝYE sonra zamanaþýmýna uðrar.\n"
"  -w,  --wait=SANÝYE            iþlemler arasýnda SANÝYE kadar bekler.\n"
"       --waitretry=SANÝYE       iþlem tekrarlarý arasýnda SANÝYE bekler\n"
"  -Y,  --proxy=on/off           vekil baðlantýsýný açar ya da kapatýr.\n"
"  -Q,  --quota=SAYI             iþlem kotasýný SAYIya ayarlar.\n"
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
"Dizinler:\n"
"  -nd  --no-directories            dizinleri oluþturmaz.\n"
"  -x,  --force-directories         dizin oluþturmaya zorlar.\n"
"  -nH, --no-host-directories       makina dizinlerini oluþturmaz.\n"
"  -P,  --directory-prefix=DiZiN    dosyalar DiZiN/...e kaydedilir.\n"
"       --cut-dirs=ADET             ADET karþý dizini yoksayar.\n"
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
"HTTP seçenekleri:\n"
"       --http-user=KULLANICI  http ile KULLANICI belirtir.\n"
"       --http-passwd=ÞiFRE    http ile ÞiFRE belirtir.\n"
"  -C,  --cache=on/off         sunucu-önbellekli veriyi engel-ler/lemez.\n"
"       --ignore-length        `Content-Length' baþlýk alanýný yoksayar.\n"
"       --header=DiZGE          baþlýklarýn arasýna DiZGEyi yerleþtirir.\n"
"       --proxy-user=KULLANICI Vekil makina için KULLANICI.\n"
"       --proxy-passwd=ÞiFRE   Vekil makina için ÞiFRE.\n"
"       --referer=URL          http isteðinde `Referer: URL' baþlýðýný içerir.\n"
"  -s,  --save-headers         HTTP baþlýklarýný dosyaya kaydeder.\n"
"  -U,  --user-agent=VEKiL     Wget/SÜRÜM yerine VEKiL olarak tanýtýlýr.\n"
"       --no-http-keep-alive   HTTP sürekli baðlantýsý etkisizleþtirilir.\n"
"       --cookies=off          çerezler kabul edilmez.\n"
"       --load-cookies=DOSYA   çerezler oturum öncesi DOSYAdan yüklenir.\n"
"       --save-cookies=DOSYA   çerezler oturum sonrasý DOSYAya yazýlýr.\n"
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
"FTP seçenekleri:\n"
"  -nr, --dont-remove-listing   `.listing' dosyalarý silinmez.\n"
"  -g,  --glob=on/off           dosya ismi genellemelerini  açar ya da kapar.\n"
"       --passive-ftp           \"pasif\" aktarým kipi kullanýlýr.\n"
"       --retr-symlinks         özyineleme sýrasýnda, dizinlere deðil,\n"
"                               dosyalara baðý olanlar alýnýr.\n"
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
"Özyinelemeli iþlemler:\n"
"  -r,  --recursive             özyinelemeli web-emme -- dikkatli kullanýn!.\n"
"  -l,  --level=SAYI            en çok özyineleme derinliði (0 sýnýrsýz).\n"
"       --delete-after          indirdikten sonra dosyalarý siler.\n"
"  -k,  --convert-links         göreceli olmayan baðlarý göreceli yapar.\n"
"  -K,  --backup-converted      X dosyasýný çevirmeden önce X.orig olarak\n"
"                               kopyalar\n"
"  -m,  --mirror                -r -N -l inf -nr seçenekleri için kýsaltma.\n"
"  -p,  --page-requisites       HTML sayfasýnýn gösterilebilmesi için gerekli\n"
"                               tüm resim dosyalarýný alýr.\n"
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
"  -nh, --no-host-lookup             don't DNS-lookup hosts.\n"
"  -np, --no-parent                  don't ascend to the parent directory.\n"
"\n"
msgstr ""
"Özyinelemeli kabul/red:\n"
"  -A,  --accept=LÝSTE               kabul edilen uzantýlarýn virgüllü LÝSTEsi\n"
"  -R,  --reject=LÝSTE               reddedilen uzantýlarýn virgüllü LÝSTEsi.\n"
"  -D,  --domains=LÝSTE              kabul edilen alanlarýn virgüllü LÝSTEsi.\n"
"       --exclude-domains=LÝSTE      reddedilen alanlarýn virgüllü LÝSTEsi.\n"
"       --follow-ftp                 HTML belgelerdeki FTP baðlarý izler.\n"
"       --follow-tags=LÝSTE          izlenecek HTML adreslerinin virgüllü\n"
"                                    LÝSTEsi\n"
"  -G,  --ignore-tags=LÝSTE          izlenmeyecek HTML adreslerinin virgüllü\n"
"                                    LÝSTEsi\n"
"  -H,  --span-hosts                 özyinelerken diðer makinalara da gider.\n"
"  -L,  --relative                   sadece göreceli baðlarý izler.\n"
"  -i,  --include-directories=LÝSTE  izin verilen dizinlerin LÝSTEsi.\n"
"  -X,  --exclude-directories=LÝSTE  dýþlanan dizinlerin LÝSTEsi.\n"
"  -nh, --no-host-lookup             makina DNS-okumasý yapmaz.\n"
"  -np, --no-parent                  Üst dizine çýkmaz.\n"
"\n"

#: src/main.c:233
msgid "Mail bug reports and suggestions to <bug-wget@gnu.org>.\n"
msgstr "Yazýlým hatalarýný ve önerilerinizi <bug-wget@gnu.org> adresine bildirin.\n"

#: src/main.c:419
#, c-format
msgid "%s: debug support not compiled in.\n"
msgstr "%s: hata ayýklayýcý desteðiyle derlenmedi.\n"

#: src/main.c:471
msgid ""
"Copyright (C) 1995, 1996, 1997, 1998, 2000 Free Software Foundation, Inc.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
msgstr ""
"TelifHakký (C) 1995, 1996, 1997, 1998,2000 Free Software Foundation, inc.\n"
"Bu program faydalý olacaðý umularak daðýtýlmaktadýr.\n"
"Hiçbir GARANTÝSÝ YOKTUR; hatta SATILABÝLÝRLÝÐÝ veya ÞAHSÝ KULLANIMINIZA\n"
"UYGUNLUÐU için bile garanti verilmez. Detaylar için GNU Genel Kamu\n"
"Lisansýna bakýnýz.\n"

#: src/main.c:477
msgid "\nOriginally written by Hrvoje Niksic <hniksic@arsdigita.com>.\n"
msgstr "\nÖzgün olarak Hrvoje Niksic <hniksic@arsdigita.com> tarafýndan yazýldý.\n"

#: src/main.c:568
#, c-format
msgid "%s: %s: invalid command\n"
msgstr "%s: %s: komut geçersiz\n"

#: src/main.c:624
#, c-format
msgid "%s: illegal option -- `-n%c'\n"
msgstr "%s: seçenek uygun deðil -- `-n%c'\n"

#. #### Something nicer should be printed here -- similar to the
#. pre-1.5 `--help' page.
#: src/main.c:627 src/main.c:669 src/main.c:727
#, c-format
msgid "Try `%s --help' for more options.\n"
msgstr "Daha fazla seçenek için `%s --help' yazýn.\n"

#: src/main.c:707
msgid "Can't be verbose and quiet at the same time.\n"
msgstr "Hem çok detaylý hem de sessiz olmaz.\n"

#: src/main.c:713
msgid "Can't timestamp and not clobber old files at the same time.\n"
msgstr "Eski dosyalarý hem zaman damgalamak hem de dokunmamak olmaz.\n"

#. No URL specified.
#: src/main.c:722
#, c-format
msgid "%s: missing URL\n"
msgstr "%s: URL kayýp\n"

#: src/main.c:824
#, c-format
msgid "No URLs found in %s.\n"
msgstr "%s de URL yok.\n"

#: src/main.c:833
#, c-format
msgid ""
"\n"
"FINISHED --%s--\n"
"Downloaded: %s bytes in %d files\n"
msgstr ""
"\n"
"BÝTTÝ --%s--\n"
"Ýndirilen: %s bayt, %d dosya\n"

#: src/main.c:841
#, c-format
msgid "Download quota (%s bytes) EXCEEDED!\n"
msgstr "Ýndirme kotasý (%s bayt) AÞILDI! \n"

#. Please note that the double `%' in `%%s' is intentional, because
#. redirect_output passes tmp through printf.
#: src/main.c:875
#, c-format
msgid "%s received, redirecting output to `%%s'.\n"
msgstr "%s alýndý, çýktý `%%s'e yönlendirildi. \n"

#: src/mswindows.c:89
#, c-format
msgid ""
"\n"
"CTRL+Break received, redirecting output to `%s'.\n"
"Execution continued in background.\n"
"You may stop Wget by pressing CTRL+ALT+DELETE.\n"
msgstr ""
"\n"
"CTRL+Break alýndý, çýktý `%s'e yönlendiriliyor.\n"
"Ýþlem ardalanda sürecek.\n"
"CTRL+ALT+DELETE tuþlayarak Wget'i durdurabilirsiniz.\n"

#. parent, no error
#: src/mswindows.c:106 src/utils.c:457
msgid "Continuing in background.\n"
msgstr "Ardalanda sürüyor.\n"

#: src/mswindows.c:108 src/utils.c:459
#, c-format
msgid "Output will be written to `%s'.\n"
msgstr "Çýktý `%s'e yazýlmýþ olacak.\n"

#: src/mswindows.c:188
#, c-format
msgid "Starting WinHelp %s\n"
msgstr "WinHelp %s Baþlatýlýyor\n"

#: src/mswindows.c:215 src/mswindows.c:222
#, c-format
msgid "%s: Couldn't find usable socket driver.\n"
msgstr "%s: Kullanýlabilir soket sürücü bulunamadý.\n"

#: src/netrc.c:367
#, c-format
msgid "%s: %s:%d: warning: \"%s\" token appears before any machine name\n"
msgstr "%s: %s:%d: uyarý: herhangi bir makina isminden önce \"%s\" dizgeciði görünüyor\n"

#: src/netrc.c:398
#, c-format
msgid "%s: %s:%d: unknown token \"%s\"\n"
msgstr "%s: %s:%d: bilinmeyen dizgecik \"%s\"\n"

#: src/netrc.c:462
#, c-format
msgid "Usage: %s NETRC [HOSTNAME]\n"
msgstr "Kullaným: %s NETRC [MAKÝNA-ADI]\n"

#: src/netrc.c:472
#, c-format
msgid "%s: cannot stat %s: %s\n"
msgstr "%s: %s durumlanamadý: %s\n"

#: src/recur.c:484
#, c-format
msgid "Removing %s since it should be rejected.\n"
msgstr "Reddedileceðinden %s kaldýrýlýyor.\n"

#: src/recur.c:679
msgid "Loading robots.txt; please ignore errors.\n"
msgstr "robots.txt yükleniyor; lütfen hatalarý yoksayýn.\n"

#: src/retr.c:227
#, c-format
msgid "\n          [ skipping %dK ]"
msgstr "\n          [ %dK atlanýyor ]"

#: src/retr.c:373
msgid "Could not find proxy host.\n"
msgstr "Vekil makina bulunamadý.\n"

#: src/retr.c:387
#, c-format
msgid "Proxy %s: Must be HTTP.\n"
msgstr "Vekil makina %s: HTTP olmalý.\n"

#: src/retr.c:481
#, c-format
msgid "%s: Redirection cycle detected.\n"
msgstr "%s: Yönlendirme çevrimi saptandý.\n"

#: src/retr.c:587
msgid "Giving up.\n\n"
msgstr "Vazgeçiliyor.\n\n"

#: src/retr.c:587
msgid "Retrying.\n\n"
msgstr "Tekrarlanýyor.\n\n"

#: src/url.c:1329
#, c-format
msgid "Converting %s... "
msgstr "%s dönüþtürülüyor..."

#: src/url.c:1342
msgid "nothing to do.\n"
msgstr "birþey yapýlmadý.\n"

#: src/url.c:1350 src/url.c:1374
#, c-format
msgid "Cannot convert links in %s: %s\n"
msgstr "%s deki baðlar dönüþtürülemiyor: %s\n"

#: src/url.c:1365
#, c-format
msgid "Unable to delete `%s': %s\n"
msgstr "`%s' silinemiyor: %s\n"

#: src/url.c:1555
#, c-format
msgid "Cannot back up %s as %s: %s\n"
msgstr "%s, %s olarak yedeklenemiyor: %s\n"

#: src/utils.c:93
#, c-format
msgid "%s: %s: Not enough memory.\n"
msgstr "%s: %s: Bellek yetersiz.\n"

#: src/utils.c:416
msgid "Unknown/unsupported protocol"
msgstr "Bilinmeyen/desteklenmeyen protokol"

#: src/utils.c:419
msgid "Invalid port specification"
msgstr "Port özellikleri geçersiz"

#: src/utils.c:422
msgid "Invalid host name"
msgstr "Makina ismi geçersiz"

#: src/utils.c:619
#, c-format
msgid "Failed to unlink symlink `%s': %s\n"
msgstr "`%s' sembolik bað asýl dosyaya dönüþtürülürken baþarýsýz: %s\n"
