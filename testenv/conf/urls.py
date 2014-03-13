from conf import hook


@hook(alias='Urls')
class URLs:
    def __init__(self, url_list):
        self.url_list = url_list

    def __call__(self, test_obj):
        test_obj.urls = self.url_list
