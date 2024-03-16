#!/usr/bin/env python3

import random
import string
import os
from sys import exit
from test.http_test import HTTPTest
from test.base_test import HTTP
from misc.wget_file import WgetFile

"""
    Basic test of --recursive.
"""
############# File Definitions ###############################################

max_path_len = os.pathconf(os.getcwd(), 'PC_PATH_MAX')
max_name_len = os.pathconf(os.getcwd(), 'PC_NAME_MAX')

# 19 is a magic number. See CHOMP_BUFFER in url.c to have an understanding of where it comes from
long_filename = 'deeper/than/' + ''.join(random.choices(string.ascii_lowercase, k=(max_name_len - 19)))

# Since this filename is one larger than the CHOMP_BUFFER, it should cause Wget to truncate the filename when saving it
# to disk.
very_long_filename = 'deeper/than/' + ''.join(random.choices(string.ascii_lowercase, k=(max_name_len - 18)))

File1 = f"""<html><body>
<a href=\"/a/File2.html\">text</a>
<a href=\"/{long_filename}\">text</a>
<a href=\"/{very_long_filename}\">text</a>
</body></html>"""
File2 = "With lemon or cream?"
File3 = "Surely you're joking Mr. Feynman"
File4 = "This filename will be truncated"

File1_File = WgetFile("index.html", File1)
File2_File = WgetFile("a/File2.html", File2)
File3_File = WgetFile(long_filename, File3)
File4_File = WgetFile(very_long_filename, File4)
File4saved_File = WgetFile(very_long_filename[:-1], File4)

WGET_OPTIONS = "--recursive --no-host-directories"
WGET_URLS = [[""]]

Servers = [HTTP]

Files = [[File1_File, File2_File, File3_File, File4_File]]
Existing_Files = []

ExpectedReturnCode = 0
ExpectedDownloadedFiles = [File1_File, File2_File, File3_File, File4saved_File]
Request_List = [["GET /",
                 "GET /robots.txt",
                 "GET /a/File2.html",
                 f"GET /{long_filename}",
                 f"GET /{very_long_filename}"]]

################ Pre and Post Test Hooks #####################################
pre_test = {
    "ServerFiles"       : Files,
    "LocalFiles"        : Existing_Files
}
test_options = {
    "WgetCommands"      : WGET_OPTIONS,
    "Urls"              : WGET_URLS
}
post_test = {
    "ExpectedFiles"     : ExpectedDownloadedFiles,
    "ExpectedRetcode"   : ExpectedReturnCode,
    "FilesCrawled"      : Request_List
}

err = HTTPTest (
                pre_hook=pre_test,
                test_params=test_options,
                post_hook=post_test,
                protocols=Servers
).begin ()

exit (err)
