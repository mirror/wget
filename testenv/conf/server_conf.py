from conf import hook


@hook()
class ServerConf:
    def __init__(self, server_settings):
        self.server_settings = server_settings

    def __call__(self, test_obj):
        for server in test_obj.servers:
            server.server_sett(self.server_settings)
