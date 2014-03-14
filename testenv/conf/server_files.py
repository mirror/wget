from conf import hook


@hook()
class ServerFiles:
    def __init__(self, server_files):
        self.server_files = server_files

    def __call__(self, test_obj):
        for server, files in zip(test_obj.servers, self.server_files):
            rules = {f.name: test_obj.get_server_rules(f)
                     for f in files}
            files = {f.name: test_obj._replace_substring(f.content)
                     for f in files}
            server.server_conf(files, rules)
