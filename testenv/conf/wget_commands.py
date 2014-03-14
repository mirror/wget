from conf import hook


@hook()
class WgetCommands:
    def __init__(self, commands):
        self.commands = commands

    def __call__(self, test_obj):
        test_obj.wget_options = test_obj._replace_substring(self.commands)
