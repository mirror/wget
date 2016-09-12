#!/usr/bin/env python3
from sys import exit
from test.http_test import HTTPTest
from misc.wget_file import WgetFile
import hashlib

"""
    This is to test if Metalink XML file escapes current directory.
"""
############# File Definitions ###############################################
File1 = "Would you like some Tea?"
File1_lowPref = "Do not take this"
File1_sha256 = hashlib.sha256 (File1.encode ('UTF-8')).hexdigest ()
MetaXml = \
"""<?xml version="1.0" encoding="utf-8"?>
<metalink version="3.0" xmlns="http://www.metalinker.org/">
  <publisher>
    <name>GNU Wget</name>
  </publisher>
  <license>
    <name>GNU GPL</name>
    <url>http://www.gnu.org/licenses/gpl.html</url>
  </license>
  <identity>Wget Test File 1</identity>
  <version>1.2.3</version>
  <description>Wget Test File 1 description</description>
  <files>
    <file name="/File1">
      <verification>
        <hash type="sha256">{{FILE1_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="40">http://broken.example/File1</url>
        <url type="http" preference="25">http://{{SRV_HOST}}:{{SRV_PORT}}/File1_lowPref</url>
        <url type="http" preference="30">http://{{SRV_HOST}}:{{SRV_PORT}}/File1</url>
      </resources>
    </file>
  </files>
</metalink>
"""

A_File = WgetFile ("File1", File1)
B_File = WgetFile ("File1_lowPref", File1_lowPref)
MetaFile = WgetFile ("test.metalink", MetaXml)

WGET_OPTIONS = "--input-metalink test.metalink"
WGET_URLS = [[]]

Files = [[A_File, B_File]]
Existing_Files = [MetaFile]

ExpectedReturnCode = 0
ExpectedDownloadedFiles = [MetaFile]

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

http_test = HTTPTest (
                pre_hook=pre_test,
                test_params=test_options,
                post_hook=post_test,
)

http_test.server_setup()
### Get and use dynamic server sockname
srv_host, srv_port = http_test.servers[0].server_inst.socket.getsockname ()

MetaXml = MetaXml.replace('{{FILE1_HASH}}', File1_sha256)
MetaXml = MetaXml.replace('{{SRV_HOST}}', srv_host)
MetaXml = MetaXml.replace('{{SRV_PORT}}', str (srv_port))
MetaFile.content = MetaXml

err = http_test.begin ()

exit (err)
