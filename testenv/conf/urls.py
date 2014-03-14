from conf import hook


@hook(alias='Urls')
class URLs:
    def __init__(self, urls):
        self.urls = urls

    def __call__(self, test_obj):
        test_obj.urls = self.urls
