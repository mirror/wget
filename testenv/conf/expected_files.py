from conf import hook


@hook()
class ExpectedFiles:
    def __init__(self, exp_filesys):
        self.exp_filesys = exp_filesys

    def __call__(self, test_obj):
        test_obj._check_downloaded_files (self.exp_filesys)
