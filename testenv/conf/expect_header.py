from conf import rule


@rule()
class ExpectHeader:
    def __init__(self, header_obj):
        self.headers = header_obj
