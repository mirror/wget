from conf import hook


@hook()
class WgetCommands:
    def __init__(self, command_list):
        self.command_list = command_list

    def __call__(self, test_obj):
        test_obj.options = test_obj._replace_substring (self.command_list)
