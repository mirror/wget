import traceback
import conf
from exc.test_failed import TestFailed
from misc.colour_terminal import print_red, print_green, print_blue
from server.http import http_server
from test.base_test import CommonMethods, HTTP


class HTTPTest (CommonMethods):

    """ Class for HTTP Tests. """

# Temp Notes: It is expected that when pre-hook functions are executed, only an empty test-dir exists.
# pre-hook functions are executed just prior to the call to Wget is made.
# post-hook functions will be executed immediately after the call to Wget returns.

    def __init__ (
        self,
        name="Unnamed Test",
        pre_hook=dict(),
        test_params=dict(),
        post_hook=dict(),
        servers=[HTTP]
    ):
        try:
            self.Server_setup (name, pre_hook, test_params, post_hook, servers)
        except TestFailed as tf:
            print_red("Error: " + tf.error)
            self.tests_passed = False
        except Exception as ae:
            print_red("Unhandled Exception Caught.")
            print ( ae.__str__ ())
            traceback.print_exc ()
            self.tests_passed = False
        else:
            print_green("Test Passed")
        finally:
            self._exit_test ()

    def Server_setup (self, name, pre_hook, test_params, post_hook, servers):
        self.name = name
        self.server_types = servers
        self.servers = len (servers)
        print_blue("Running Test " + self.name)
        self.init_test_env (name)
        self.server_list = list()
        self.domain_list = list()
        for server_type in servers:
            server_inst = getattr (self, "init_" + server_type + "_Server") ()
            self.server_list.append (server_inst)
            domain = self.get_domain_addr (server_inst.server_address)
            self.domain_list.append (domain)
        #self.server = self.init_HTTP_Server ()
        #self.domain = self.get_domain_addr (self.server.server_address)

        self.pre_hook_call (pre_hook)
        self.call_test (test_params)
        self.post_hook_call (post_hook)


    def hook_call(self, configs, name):
        for conf_name, conf_arg in configs.items():
            try:
                # conf.find_conf(conf_name) returns the required conf class,
                # then the class is instantiated with conf_arg, then the
                # conf instance is called with this test instance itself to
                # invoke the desired hook
                conf.find_conf(conf_name)(conf_arg)(self)
            except AttributeError as e:
                print(e)
                self.stop_HTTP_Server()
                raise TestFailed("%s %s not defined." %
                                 (name, conf_name))


    def pre_hook_call (self, pre_hook):
        self.hook_call(pre_hook, 'Pre Test Function')

    def call_test (self, test_params):
        self.hook_call(test_params, 'Test Option')

        try:
            self.act_retcode = self.exec_wget (self.options, self.urls, self.domain_list)
        except TestFailed as tf:
            self.stop_HTTP_Server ()
            raise TestFailed (tf.__str__ ())
        self.stop_HTTP_Server ()

    def post_hook_call (self, post_hook):
        self.hook_call(post_hook, 'Post Test Function')

    def init_HTTP_Server (self):
        server = http_server.HTTPd ()
        server.start ()
        return server

    def init_HTTPS_Server (self):
        server = http_server.HTTPSd ()
        server.start ()
        return server

    def stop_HTTP_Server (self):
        self.Request_remaining = list ()
        for server in self.server_list:
            server_req = server.server_inst.get_req_headers ()
            self.Request_remaining.append (server_req)
            server.server_inst.shutdown ()
