from conf import hook


@hook()
class ServerFiles:
    def __init__(self, server_files):
        self.server_files = server_files

    def __call__(self, test_obj):
        for i in range (0, test_obj.servers):
            file_list = dict ()
            server_rules = dict ()
            for file_obj in self.server_files[i]:
                content = test_obj._replace_substring (file_obj.content)
                file_list[file_obj.name] = content
                rule_obj = test_obj.get_server_rules (file_obj)
                server_rules[file_obj.name] = rule_obj
            test_obj.server_list[i].server_conf (file_list, server_rules)
