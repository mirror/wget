#!/usr/bin/env python3
from sys import exit
from test.http_test import HTTPTest
from misc.wget_file import WgetFile
import hashlib

"""
    This is to test Metalink/XML --continue support in Wget.
"""
############# File Definitions ###############################################
bad = "Ouch!"

# partial File1 to continue
File0 = "Would you like"

File1 = "Would you like some Tea?"
File1_lowPref = "Do not take this"
File1_sha256 = hashlib.sha256 (File1.encode ('UTF-8')).hexdigest ()

File2 = "This is gonna be good"
File2_lowPref = "Not this one too"
File2_sha256 = hashlib.sha256 (File2.encode ('UTF-8')).hexdigest ()

File3 = "A little more, please"
File3_lowPref = "That's just too much"
File3_sha256 = hashlib.sha256 (File3.encode ('UTF-8')).hexdigest ()

File4 = "Maybe a biscuit?"
File4_lowPref = "No, thanks"
File4_sha256 = hashlib.sha256 (File4.encode ('UTF-8')).hexdigest ()

File5 = "More Tea...?"
File5_lowPref = "I have to go..."
File5_sha256 = hashlib.sha256 (File5.encode ('UTF-8')).hexdigest ()

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
  <identity>Wget Test Files</identity>
  <version>1.2.3</version>
  <description>Wget Test Files description</description>
  <files>
    <file name="File1">
      <verification>
        <hash type="sha256">{{FILE1_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="25">http://{{SRV_HOST}}:{{SRV_PORT}}/File1_lowPref</url>
        <url type="http" preference="30">http://{{SRV_HOST}}:{{SRV_PORT}}/File1</url>
      </resources>
    </file>
    <file name="File2"> <!-- no good resources on purpose, this file shall be kept -->
      <verification>
        <hash type="sha256">{{FILE2_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="35">http://{{SRV_HOST}}:{{SRV_PORT}}/wrong_file</url>
        <url type="http" preference="40">http://{{SRV_HOST}}:{{SRV_PORT}}/404</url>
      </resources>
    </file>
    <file name="File3">
      <verification>
        <hash type="sha256">{{FILE3_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="25">http://{{SRV_HOST}}:{{SRV_PORT}}/File3_lowPref</url>
        <url type="http" preference="30">http://{{SRV_HOST}}:{{SRV_PORT}}/File3</url>
      </resources>
    </file>
    <file name="File4"> <!-- no good resources on purpose, this file shall be kept -->
      <verification>
        <hash type="sha256">{{FILE4_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="35">http://{{SRV_HOST}}:{{SRV_PORT}}/wrong_file</url>
      </resources>
    </file>
    <file name="File5">
      <verification>
        <hash type="sha256">{{FILE5_HASH}}</hash>
      </verification>
      <resources>
        <url type="http" preference="25">http://{{SRV_HOST}}:{{SRV_PORT}}/File5_lowPref</url>
        <url type="http" preference="30">http://{{SRV_HOST}}:{{SRV_PORT}}/File5</url>
      </resources>
    </file>
  </files>
</metalink>
"""

wrong_file = WgetFile ("wrong_file", bad)

# partial File1_down to continue
File0_part = WgetFile ("File1", File0)

File1_orig = WgetFile ("File1", File1)
File1_down = WgetFile ("File1", File1)
File1_nono = WgetFile ("File1_lowPref", File1_lowPref)

# no good resources on purpose, this file shall be kept
File2_ouch = WgetFile ("File2", bad)

File3_orig = WgetFile ("File3", File3)
File3_down = WgetFile ("File3", File3)
File3_nono = WgetFile ("File3_lowPref", File3_lowPref)

# no good resources on purpose, this file shall be kept
File4_ouch = WgetFile ("File4", bad)

File5_orig = WgetFile ("File5", File5)
File5_down = WgetFile ("File5", File5)
File5_nono = WgetFile ("File5_lowPref", File5_lowPref)

MetaFile = WgetFile ("test.metalink", MetaXml)

WGET_OPTIONS = "--continue --input-metalink test.metalink"
WGET_URLS = [[]]

Files = [[
    wrong_file,
    File1_orig, File1_nono,
    File3_orig, File3_nono,
    File5_orig, File5_nono
]]
Existing_Files = [
    File0_part, # partial File1_down to continue
    File2_ouch, # wrong but fully downloaded file
    File3_down, # right and fully downloaded file
    File4_ouch, # wrong but fully downloaded file
    MetaFile
]

ExpectedReturnCode = 1
ExpectedDownloadedFiles = [
    File1_down, # continued file from File0_part
    File2_ouch, # wrong but fully downloaded file
    File3_down, # right and fully downloaded file
    File4_ouch, # wrong but fully downloaded file
    File5_down, # newly fully donwloaded file
    MetaFile
]

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
MetaXml = MetaXml.replace('{{FILE2_HASH}}', File2_sha256)
MetaXml = MetaXml.replace('{{FILE3_HASH}}', File3_sha256)
MetaXml = MetaXml.replace('{{FILE4_HASH}}', File4_sha256)
MetaXml = MetaXml.replace('{{FILE5_HASH}}', File5_sha256)
MetaXml = MetaXml.replace('{{SRV_HOST}}', srv_host)
MetaXml = MetaXml.replace('{{SRV_PORT}}', str (srv_port))
MetaFile.content = MetaXml

err = http_test.begin ()

exit (err)
