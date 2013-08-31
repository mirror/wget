#!/usr/bin/env python3
from sys import exit
from WgetTest import HTTPTest, WgetFile

"""
    This is a Prototype Test File.
    Ideally this File should be copied and edited to write new tests.
"""
TEST_NAME = "Prototype"
############# File Definitions ###############################################
File1 = "Would you like some Tea?"
File2 = "With lemon or cream?"
File3 = "Sure you're joking Mr. Feynman"

File1_rules = {
    "Authentication"    : {
        "Type"          : "Both",
        "User"          : "Sauron",
        "Pass"          : "TheEye"
    },
    "RejectHeader"      : {
        "Authorization" : "Basic U2F1cm9uOlRoZUV5ZQ=="
    }
}
File2_rules = {
    "Authentication"    : {
        "Type"          : "Both_inline",
        "User"          : "Sauron",
        "Pass"          : "TheEye"
    },
    "SendHeader"        : {
        "Content-Disposition"  : "Attachment; filename=newfile"
    }
}

A_File = WgetFile ("File1", File1, rules=File1_rules)
B_File = WgetFile ("File2", File2, rules=File2_rules)
C_File = WgetFile ("File3", File3)

WGET_OPTIONS = "-d --content-disposition --user=Sauron --password=TheEye"
WGET_URLS = ["File1", "File2"]

Files = [A_File, B_File]
Existing_Files = [C_File]

ExpectedReturnCode = 0
ExpectedDownloadedFiles = [A_File, WgetFile ("newfile", File2), C_File]

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
                name=TEST_NAME,
                pre_hook=pre_test,
                test_params=test_options,
                post_hook=post_test
).begin ()

exit (err)
