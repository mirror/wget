from conf import rule

""" Rule: RejectHeaderField
This is a server side rule which expects a string list of Header Fields
which should be blacklisted by the server for a particular file's requests.
"""


@rule()
class RejectHeaderField:
    def __init__(self, header_fields):
        self.header_fields = header_fields
