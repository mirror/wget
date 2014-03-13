from conf import rule


@rule()
class Response:
    def __init__(self, ret_code):
        self.response_code = ret_code
