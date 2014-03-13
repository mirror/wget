from exc.test_failed import TestFailed
from conf import hook


@hook(alias='ExpectedRetcode')
class ExpectedRetCode:
    def __init__(self, retcode):
        self.retcode = retcode

    def __call__(self, test_obj):
        if test_obj.act_retcode != self.retcode:
            pr = "Return codes do not match.\nExpected: " + str(self.retcode) + "\nActual: " + str(test_obj.act_retcode)
            raise TestFailed (pr)
