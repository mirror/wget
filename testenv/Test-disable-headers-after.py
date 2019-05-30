#!/usr/bin/env python3
from sys import exit
from test.http_test import HTTPTest
from test.base_test import HTTP, HTTPS
from misc.wget_file import WgetFile

"""
    This is test ensures that the --disable-header option removes user headers
    from the HTTP request when it's placed after --header="header: value".
"""
############# File Definitions ###############################################
file_content = """Les paroles de la bouche d'un homme sont des eaux profondes;
La source de la sagesse est un torrent qui jaillit."""

Headers = {
    'Authorization',
    'User-Agent',
    'Referer',
    'Cache-Control',
    'Pragma',
    'If-Modified-Since',
    'Range',
    'Accept',
    'Accept-Encoding',
    'Host',
    'Connection',
    'Proxy-Connection',
    'Content-Type',
    'Content-Length',
    'Proxy-Authorization',
    'Cookie',
    'MyHeader',
}

WGET_OPTIONS = ''
WGET_URLS = [[]]
Files = [[]]

# Define user defined headers
for header in Headers:
    WGET_OPTIONS += ' --header="' + header + ': any"'

WGET_OPTIONS += ' --disable-header="'
headers_len = len(Headers)

for index, header in enumerate(Headers, start=1):
    File_rules = {
        "RejectHeader"    : {
            header : 'any'
        }
    }
    file_name = "File" + str(index)
    Files[0].append(WgetFile(file_name, file_content, rules=File_rules))
    WGET_OPTIONS += header  + (',' if index < headers_len else '"')
    WGET_URLS[0].append(file_name)

Servers = [HTTP]

ExpectedReturnCode = 0

################ Pre and Post Test Hooks #####################################
pre_test = {
    "ServerFiles"       : Files
}
test_options = {
    "WgetCommands"      : WGET_OPTIONS,
    "Urls"              : WGET_URLS
}
post_test = {
    "ExpectedRetcode"   : ExpectedReturnCode
}

err = HTTPTest (
                pre_hook=pre_test,
                test_params=test_options,
                post_hook=post_test,
                protocols=Servers
).begin ()

exit (err)
