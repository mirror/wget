#!/usr/bin/perl -w

use HTTP::Daemon;
use HTTP::Status;
use HTTP::Headers;
use HTTP::Response;

use strict;

package HTTPServer;

sub run_daemon {
    my %urls = @_;
    my $server = HTTP::Daemon->new (LocalAddr => 'localhost', 
                                    LocalPort => '8080',
                                    ReuseAddr => 1) or die "Cannot create server!!!";
                                
    while (my $con = $server->accept) {
        while (my $req = $con->get_request) {
            # print STDERR "method: ", $req->method, "\n";
            if ($req->method eq "GET" and $urls{$req->url->path}) {
                # print STDERR "requested URL: ", $req->url->path, "\n";
                
                # create response
                my $tmp = $urls{$req->url->path};
                my $resp = HTTP::Response->new ($tmp->{'code'},
                                                $tmp->{'msg'});
                # print STDERR "HTTP::Response: \n", $resp->as_string;
                
                # fill in headers
                while (my ($name, $value) = each %{$tmp->{headers}}) {
                    # print STDERR "setting header: $name = $value\n";
                    $resp->header($name => $value);
                }
                # print STDERR "HTTP::Response with headers: \n", $resp->as_string;

                # fill in content
                $resp->content($tmp->{content});
                # print STDERR "HTTP::Response with content: \n", $resp->as_string;
                
                $con->send_response($resp);
                # print STDERR "HTTP::Response sent: \n", $resp->as_string;
            } else {
                print STDERR "requested wrong URL: ", $req->url->path, "\n";
                $con->send_error($HTTP::Status::RC_FORBIDDEN);
            }
        }
        $con->close;
        undef($con);
    }
}

sub run {
    my $pid = fork();

    if($pid == 0) {
        run_daemon(@_);
    }

    return $pid;
}

1;

# vim: et ts=4 sw=4

