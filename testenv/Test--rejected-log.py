#!/usr/bin/env python3
from sys import exit
from test.http_test import HTTPTest
from misc.wget_file import WgetFile

"""
    This test executed Wget in recursive mode with a rejected log outputted.
"""
TEST_NAME = "Rejected Log"
############# File Definitions ###############################################
mainpage = """
<html>
<head>
  <title>Main Page</title>
</head>
<body>
  <p>
    Recurse to a <a href="http://127.0.0.1:{{port}}/secondpage.html">second page</a>.
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
    Recurse to a <a href="http://127.0.0.1:{{port}}/thirdpage.html">third page</a>.
    Try the blacklisted <a href="http://127.0.0.1:{{port}}/index.html">main page</a>.
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
    Try a hidden <a href="http://127.0.0.1:{{port}}/dummy.txt">dummy file</a>.
    Try to leave to <a href="http://no.such.domain/">another domain</a>.
  </p>
</body>
</html>
"""

robots = """
User-agent: *
Disallow: /dummy.txt
"""

log = """\
REASON	U_URL	U_SCHEME	U_HOST	U_PORT	U_PATH	U_PARAMS	U_QUERY	U_FRAGMENT	P_URL	P_SCHEME	P_HOST	P_PORT	P_PATH	P_PARAMS	P_QUERY	P_FRAGMENT
BLACKLIST	http%3A//127.0.0.1%3A{{port}}/index.html	SCHEME_HTTP	127.0.0.1	{{port}}	index.html				http%3A//127.0.0.1%3A{{port}}/secondpage.html	SCHEME_HTTP	127.0.0.1	{{port}}	secondpage.html
ROBOTS	http%3A//127.0.0.1%3A{{port}}/dummy.txt	SCHEME_HTTP	127.0.0.1	{{port}}	dummy.txt				http%3A//127.0.0.1%3A{{port}}/thirdpage.html	SCHEME_HTTP	127.0.0.1	{{port}}	thirdpage.html
SPANNEDHOST	http%3A//no.such.domain/	SCHEME_HTTP	no.such.domain	80					http%3A//127.0.0.1%3A{{port}}/thirdpage.html	SCHEME_HTTP	127.0.0.1	{{port}}	thirdpage.html
"""

dummyfile = "Don't care."


index_html = WgetFile ("index.html", mainpage)
secondpage_html = WgetFile ("secondpage.html", secondpage)
thirdpage_html = WgetFile ("thirdpage.html", thirdpage)
robots_txt = WgetFile ("robots.txt", robots)
dummy_txt = WgetFile ("dummy.txt", dummyfile)
log_csv = WgetFile ("log.csv", log)

WGET_OPTIONS = "-nd -r --rejected-log log.csv"
WGET_URLS = [["index.html"]]

Files = [[index_html, secondpage_html, thirdpage_html, robots_txt, dummy_txt]]

ExpectedReturnCode = 0
ExpectedDownloadedFiles = [index_html, secondpage_html, thirdpage_html, robots_txt, log_csv]

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
