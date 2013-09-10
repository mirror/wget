from http.server import HTTPServer, BaseHTTPRequestHandler
from base64 import b64encode
from random import random
from hashlib import md5
import threading
import re


class InvalidRangeHeader (Exception):

    """ Create an Exception for handling of invalid Range Headers. """
    # TODO: Eliminate this exception and use only ServerError

    def __init__ (self, err_message):
        self.err_message = err_message

class ServerError (Exception):
    def __init__ (self, err_message):
        self.err_message = err_message


class StoppableHTTPServer (HTTPServer):

    """ Define methods for configuring the Server. """

    def server_conf (self, filelist, conf_dict):
        """ Set Server Rules and File System for this instance. """
        self.server_configs = conf_dict
        self.fileSys = filelist


class WgetHTTPRequestHandler (BaseHTTPRequestHandler):

    """ Define methods for handling Test Checks. """

    def get_rule_list (self, name):
        r_list = self.rules.get (name) if name in self.rules else None
        return r_list


class _Handler (WgetHTTPRequestHandler):

    """ Define Handler Methods for different Requests. """

    InvalidRangeHeader = InvalidRangeHeader
    protocol_version = 'HTTP/1.1'

    """ Define functions for various HTTP Requests. """

    def do_HEAD (self):
        self.send_head ()

    def do_GET (self):
        content, start = self.send_head ()
        if content:
            if start is None:
                self.wfile.write (content.encode ('utf-8'))
            else:
                self.wfile.write (content.encode ('utf-8')[start:])

    def do_POST (self):
        path = self.path[1:]
        self.rules = self.server.server_configs.get (path)
        if not self.custom_response ():
            return (None, None)
        if path in self.server.fileSys:
            body_data = self.get_body_data ()
            self.send_response (200)
            self.send_header ("Content-type", "text/plain")
            content = self.server.fileSys.pop (path) + "\n" + body_data
            total_length = len (content)
            self.server.fileSys[path] = content
            self.send_header ("Content-Length", total_length)
            self.finish_headers ()
            try:
                self.wfile.write (content.encode ('utf-8'))
            except Exception:
                pass
        else:
            self.send_put (path)

    def do_PUT (self):
        path = self.path[1:]
        self.rules = self.server.server_configs.get (path)
        if not self.custom_response ():
            return (None, None)
        self.server.fileSys.pop (path, None)
        self.send_put (path)

    """ End of HTTP Request Method Handlers. """

    """ Helper functions for the Handlers. """

    def parse_range_header (self, header_line, length):
        if header_line is None:
            return None
        if not header_line.startswith ("bytes="):
            raise InvalidRangeHeader ("Cannot parse header Range: %s" %
                                     (header_line))
        regex = re.match (r"^bytes=(\d*)\-$", header_line)
        range_start = int (regex.group (1))
        if range_start >= length:
            raise InvalidRangeHeader ("Range Overflow")
        return range_start

    def get_body_data (self):
        cLength_header = self.headers.get ("Content-Length")
        cLength = int (cLength_header) if cLength_header is not None else 0
        body_data = self.rfile.read (cLength).decode ('utf-8')
        return body_data

    def send_put (self, path):
        body_data = self.get_body_data ()
        self.send_response (201)
        self.server.fileSys[path] = body_data
        self.send_header ("Content-type", "text/plain")
        self.send_header ("Content-Length", len (body_data))
        self.finish_headers ()
        try:
            self.wfile.write (body_data.encode ('utf-8'))
        except Exception:
            pass

    def SendHeader (self, header_obj):
        pass
#        headers_list = header_obj.headers
#        for header_line in headers_list:
#            print (header_line + " : " + headers_list[header_line])
#            self.send_header (header_line, headers_list[header_line])

    def send_cust_headers (self):
        header_obj = self.get_rule_list ('SendHeader')
        if header_obj:
            for header in header_obj.headers:
                self.send_header (header, header_obj.headers[header])

    def finish_headers (self):
        self.send_cust_headers ()
        self.end_headers ()

    def Response (self, resp_obj):
        self.send_response (resp_obj.response_code)
        self.finish_headers ()
        raise ServerError ("Custom Response code sent.")

    def custom_response (self):
        codes = self.get_rule_list ('Response')
        if codes:
            self.send_response (codes.response_code)
            self.finish_headers ()
            return False
        else:
            return True

    def base64 (self, data):
        string = b64encode (data.encode ('utf-8'))
        return string.decode ('utf-8')

    def send_challenge (self, auth_type):
        if auth_type == "Both":
            self.send_challenge ("Digest")
            self.send_challenge ("Basic")
            return
        if auth_type == "Basic":
            challenge_str = 'Basic realm="Wget-Test"'
        elif auth_type == "Digest" or auth_type == "Both_inline":
            self.nonce = md5 (str (random ()).encode ('utf-8')).hexdigest ()
            self.opaque = md5 (str (random ()).encode ('utf-8')).hexdigest ()
            challenge_str = 'Digest realm="Test", nonce="%s", opaque="%s"' %(
                                                                   self.nonce,
                                                                   self.opaque)
            challenge_str += ', qop="auth"'
            if auth_type == "Both_inline":
                challenge_str = 'Basic realm="Wget-Test", ' + challenge_str
        self.send_header ("WWW-Authenticate", challenge_str)

    def authorize_Basic (self, auth_header, auth_rule):
        if auth_header is None or auth_header.split(' ')[0] != 'Basic':
            return False
        else:
            self.user = auth_rule.auth_user
            self.passw = auth_rule.auth_pass
            auth_str = "Basic " + self.base64 (self.user + ":" + self.passw)
            return True if auth_str == auth_header else False

    def parse_auth_header (self, auth_header):
        n = len("Digest ")
        auth_header = auth_header[n:].strip()
        items = auth_header.split(", ")
        key_values = [i.split("=", 1) for i in items]
        key_values = [(k.strip(), v.strip().replace('"', '')) for k, v in key_values]
        return dict(key_values)

    def KD (self, secret, data):
        return self.H (secret + ":" + data)

    def H (self, data):
        return md5 (data.encode ('utf-8')).hexdigest ()

    def A1 (self):
        return "%s:%s:%s" % (self.user, "Test", self.passw)

    def A2 (self, params):
        return "%s:%s" % (self.command, params["uri"])

    def check_response (self, params):
        if "qop" in params:
            data_str = params['nonce'] \
                        + ":" + params['nc'] \
                        + ":" + params['cnonce'] \
                        + ":" + params['qop'] \
                        + ":" + self.H (self.A2 (params))
        else:
            data_str = params['nonce'] + ":" + self.H (self.A2 (params))
        resp = self.KD (self.H (self.A1 ()), data_str)

        return True if resp == params['response'] else False

    def authorize_Digest (self, auth_header, auth_rule):
        if auth_header is None or auth_header.split(' ')[0] != 'Digest':
            return False
        else:
            self.user = auth_rule.auth_user
            self.passw = auth_rule.auth_pass
            params = self.parse_auth_header (auth_header)
            pass_auth = True
            if self.user != params['username'] or \
              self.nonce != params['nonce'] or self.opaque != params['opaque']:
                pass_auth = False
            req_attribs = ['username', 'realm', 'nonce', 'uri', 'response']
            for attrib in req_attribs:
                if not attrib in params:
                    pass_auth = False
            if not self.check_response (params):
                pass_auth = False
            return pass_auth

    def authorize_Both (self, auth_header, auth_rule):
        return False

    def authorize_Both_inline (self, auth_header, auth_rule):
        return False

    def Authentication (self, auth_rule):
        try:
            self.handle_auth (auth_rule)
        except ServerError as se:
            self.send_response (401, "Authorization Required")
            self.send_challenge (auth_rule.auth_type)
            self.finish_headers ()
            raise ServerError (se.__str__())

    def handle_auth (self, auth_rule):
        is_auth = True
        auth_header = self.headers.get ("Authorization")
        required_auth = auth_rule.auth_type
        if required_auth == "Both" or required_auth == "Both_inline":
            auth_type = auth_header.split(' ')[0] if auth_header else required_auth
        else:
            auth_type = required_auth
        assert hasattr (self, "authorize_" + auth_type)
        is_auth = getattr (self, "authorize_" + auth_type) (auth_header, auth_rule)
        if is_auth is False:
            raise ServerError ("Unable to Authenticate")

    def is_authorized (self):
        is_auth = True
        auth_rule = self.get_rule_list ('Authentication')
        if auth_rule:
            auth_header = self.headers.get ("Authorization")
            req_auth = auth_rule.auth_type
            if req_auth == "Both" or req_auth == "Both_inline":
                auth_type = auth_header.split(' ')[0] if auth_header else req_auth
            else:
                auth_type = req_auth
            assert hasattr (self, "authorize_" + auth_type)
            is_auth = getattr (self, "authorize_" + auth_type) (auth_header, auth_rule)
            if is_auth is False:
                self.send_response (401)
                self.send_challenge (auth_type)
                self.finish_headers ()
        return is_auth

    def ExpectHeader (self, header_obj):
        exp_headers = header_obj.headers
        for header_line in exp_headers:
            header_recd = self.headers.get (header_line)
            if header_recd is None or header_recd != exp_headers[header_line]:
                self.send_error (400, "Expected Header " + header_line + " not found")
                self.finish_headers ()
                raise ServerError ("Header " + header_line + " not found")

    def expect_headers (self):
        """ This is modified code to handle a few changes. Should be removed ASAP """
        exp_headers_obj = self.get_rule_list ('ExpectHeader')
        if exp_headers_obj:
            exp_headers = exp_headers_obj.headers
            for header_line in exp_headers:
                header_re = self.headers.get (header_line)
                if header_re is None or header_re != exp_headers[header_line]:
                    self.send_error (400, 'Expected Header not Found')
                    self.end_headers ()
                    return False
        return True

    def RejectHeader (self, header_obj):
        rej_headers = header_obj.headers
        for header_line in rej_headers:
            header_recd = self.headers.get (header_line)
            if header_recd is not None and header_recd == rej_headers[header_line]:
                self.send_error (400, 'Blackisted Header ' + header_line + ' received')
                self.finish_headers ()
                raise ServerError ("Header " + header_line + ' received')

    def reject_headers (self):
        rej_headers = self.get_rule_list ("RejectHeader")
        if rej_headers:
            rej_headers = rej_headers.headers
            for header_line in rej_headers:
                header_re = self.headers.get (header_line)
                if header_re is not None and header_re == rej_headers[header_line]:
                    self.send_error (400, 'Blacklisted Header was Sent')
                    self.end_headers ()
                    return False
        return True

    def send_head (self):
        """ Common code for GET and HEAD Commands.
        This method is overriden to use the fileSys dict.
        """
        path = self.path[1:]

        if path in self.server.fileSys:
            self.rules = self.server.server_configs.get (path)

            for rule_name in self.rules:
                try:
                    assert hasattr (self, rule_name)
                    getattr (self, rule_name) (self.rules [rule_name])
                except AssertionError as ae:
                    msg = "Method " + rule_name + " not defined"
                    self.send_error (500, msg)
                    return (None, None)
                except ServerError as se:
                    print (se.__str__())
                    return (None, None)

            content = self.server.fileSys.get (path)
            content_length = len (content)
            try:
                self.range_begin = self.parse_range_header (
                    self.headers.get ("Range"), content_length)
            except InvalidRangeHeader as ae:
                # self.log_error("%s", ae.err_message)
                if ae.err_message == "Range Overflow":
                    self.send_response (416)
                    self.finish_headers ()
                    return (None, None)
                else:
                    self.range_begin = None
            if self.range_begin is None:
                self.send_response (200)
            else:
                self.send_response (206)
                self.send_header ("Accept-Ranges", "bytes")
                self.send_header ("Content-Range",
                                  "bytes %d-%d/%d" % (self.range_begin,
                                                      content_length - 1,
                                                      content_length))
                content_length -= self.range_begin
            self.send_header ("Content-type", "text/plain")
            self.send_header ("Content-Length", content_length)
            self.finish_headers ()
            return (content, self.range_begin)
        else:
            self.send_error (404, "Not Found")
            return (None, None)

class HTTPd (threading.Thread):
    server_class = StoppableHTTPServer
    handler = _Handler
    def __init__ (self, addr=None):
        threading.Thread.__init__ (self)
        if addr is None:
            addr = ('localhost', 0)
        self.server_inst = self.server_class (addr, self.handler)
        self.server_address = self.server_inst.socket.getsockname()[:2]

    def run (self):
       self.server_inst.serve_forever ()

    def server_conf (self, file_list, server_rules):
        self.server_inst.server_conf (file_list, server_rules)

# vim: set ts=8 sts=4 sw=3 tw=0 et :
