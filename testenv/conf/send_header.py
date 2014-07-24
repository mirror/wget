from conf import rule


@rule()
class SendHeader:
    def __init__(self, header_obj):
        self.headers = header_obj
