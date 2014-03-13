from conf import hook


@hook()
class ServerConf:
    def __init__(self, server_settings):
        self.server_settings = server_settings

    def __call__(self, test_obj):
        for i in range (0, test_obj.servers):
            test_obj.server_list[i].server_sett (self.server_settings)
