from conf import rule


@rule()
class Authentication:
    def __init__ (self, auth_obj):
        self.auth_type = auth_obj['Type']
        self.auth_user = auth_obj['User']
        self.auth_pass = auth_obj['Pass']
