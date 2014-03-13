from conf import hook


@hook()
class LocalFiles:
    def __init__(self, local_files):
        self.local_files = local_files

    def __call__(self, _):
        for file_obj in self.local_files:
            file_handler = open (file_obj.name, "w")
            file_handler.write (file_obj.content)
            file_handler.close ()
