from misc.colour_terminal import print_red
from conf import hook
from exc.test_failed import TestFailed


@hook()
class FilesCrawled:
    def __init__(self, Request_Headers):
        self.Request_Headers = Request_Headers

    def __call__(self, test_obj):
        for i in range (0, test_obj.servers):
            headers = set(self.Request_Headers[i])
            o_headers = test_obj.Request_remaining[i]
            header_diff = headers.symmetric_difference (o_headers)
            if len(header_diff) is not 0:
                print_red(header_diff)
                raise TestFailed ("Not all files were crawled correctly")
