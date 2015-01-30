from misc.colour_terminal import print_green, print_red
from conf import hook
from exc.test_failed import TestFailed

""" Post-Test Hook: FilesCrawled
This is a post test hook that is invoked in tests that check wget's behaviour
in recursive mode. It expects an ordered list of the request lines that Wget
must send to the server. If the requests received by the server do not match
the provided list, IN THE GIVEN ORDER, then it raises a TestFailed exception.
Such a test can be used to check the implementation of the recursion algorithm
in Wget too.
"""


@hook()
class FilesCrawled:
    def __init__(self, request_headers):
        self.request_headers = request_headers

    def __call__(self, test_obj):
        if self.request_headers != test_obj.request_remaining():
            print_green ('Expected: %s' % self.request_headers)
            print_red ('Got: %s' % test_obj.request_remaining())

            raise TestFailed('Not all files were crawled correctly.')
