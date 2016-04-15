#!/usr/bin/env python3
from sys import exit
from test.http_test import HTTPTest
from misc.constants import HTTP, HTTPS
from misc.wget_file import WgetFile

"""
    This is a Prototype Test File for multiple servers.
    Ideally this File should be copied and edited to write new tests.
"""
############# File Definitions ###############################################
File1 = "Would you like some Tea?"
File2 = "With lemon or cream?"
File3 = "Sure you're joking Mr. Feynman"

A_File = WgetFile ("File1", File1)
B_File = WgetFile ("File2", File2)
C_File = WgetFile ("File3", File3)

WGET_OPTIONS = ""
WGET_URLS = [["File1"], ["File2"]]

Files = [[A_File], [B_File]]
Existing_Files = [C_File]

Servers = [HTTP, HTTP]

ExpectedReturnCode = 0
ExpectedDownloadedFiles = [A_File, B_File, C_File]

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
    "ExpectedRetcode"   : ExpectedReturnCode
}

err = HTTPTest (
                pre_hook=pre_test,
                test_params=test_options,
                post_hook=post_test,
                protocols=Servers
).begin ()

exit (err)
