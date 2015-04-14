
class ServerError (Exception):
    """ A custom exception which is raised by the test servers. Often used to
    handle control flow. """

    def __init__(self, err_message):
        self.err_message = err_message


class AuthError (ServerError):
    """ A custom exception raised byt he servers when authentication of the
    request fails. """
    pass
