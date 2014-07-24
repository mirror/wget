from exc.test_failed import TestFailed
from conf import hook


@hook(alias='ExpectedRetcode')
class ExpectedRetCode:
    def __init__(self, expected_ret_code):
        self.expected_ret_code = expected_ret_code

    def __call__(self, test_obj):
        if test_obj.ret_code != self.expected_ret_code:
            failure = "Return codes do not match.\n" \
                      "Expected: %s\n" \
                      "Actual: %s" % (self.expected_ret_code,
                                      test_obj.ret_code)
            raise TestFailed(failure)
