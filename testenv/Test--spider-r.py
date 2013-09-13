#!/usr/bin/env python3
from sys import exit
from WgetTest import HTTPTest, WgetFile

"""
    This test executed Wget in Spider mode with recursive retrieval.
"""
TEST_NAME = "Recursive Spider"
############# File Definitions ###############################################
mainpage = """
<html>
<head>
  <title>Main Page</title>
</head>
<body>
  <p>
    Some text and a link to a <a href="http://127.0.0.1:{{port}}/secondpage.html">second page</a>.
    Also, a <a href="http://127.0.0.1:{{port}}/nonexistent">broken link</a>.
  </p>
</body>
</html>
"""


secondpage = """
<html>
<head>
  <title>Second Page</title>
</head>
<body>
  <p>
    Some text and a link to a <a href="http://127.0.0.1:{{port}}/thirdpage.html">third page</a>.
    Also, a <a href="http://127.0.0.1:{{port}}/nonexistent">broken link</a>.
  </p>
</body>
</html>
"""

thirdpage = """
<html>
<head>
  <title>Third Page</title>
</head>
<body>
  <p>
    Some text and a link to a <a href="http://127.0.0.1:{{port}}/dummy.txt">text file</a>.
    Also, another <a href="http://127.0.0.1:{{port}}/againnonexistent">broken link</a>.
  </p>
</body>
</html>
"""

dummyfile = "Don't care."


index_html = WgetFile ("index.html", mainpage)
secondpage_html = WgetFile ("secondpage.html", secondpage)
thirdpage_html = WgetFile ("thirdpage.html", thirdpage)
dummy_txt = WgetFile ("dummy.txt", dummyfile)

WGET_OPTIONS = "-d --spider -r"
WGET_URLS = [[""]]

Files = [[index_html, secondpage_html, thirdpage_html, dummy_txt]]

ExpectedReturnCode = 8
ExpectedDownloadedFiles = []

################ Pre and Post Test Hooks #####################################
pre_test = {
    "ServerFiles"       : Files
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
