from conf import hook


@hook()
class LocalFiles:
    def __init__(self, local_files):
        self.local_files = local_files

    def __call__(self, _):
        for f in self.local_files:
            with open(f.name, 'w') as fp:
                fp.write(f.content)
