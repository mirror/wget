from exc.test_failed import TestFailed
from conf import hook

# this file is a hook example

@hook(alias='SampleHookAlias')
class SampleHook:
    def __init__(self, sample_hook_arg):
        # do conf initialization here
        self.arg = sample_hook_arg

    def __call__(self, test_obj):
        # implement hook here
        # if you need the test case instance, refer to test_obj
        pass
