from misc.colour_terminal import print_red
from conf import hook
from exc.test_failed import TestFailed


@hook()
class FilesCrawled:
    def __init__(self, request_headers):
        self.request_headers = request_headers

    def __call__(self, test_obj):
        for headers, remaining in zip(map(set, self.request_headers),
                                      test_obj.request_remaining()):
            diff = headers.symmetric_difference(remaining)

            if diff:
                print_red(diff)
                raise TestFailed('Not all files were crawled correctly.')
