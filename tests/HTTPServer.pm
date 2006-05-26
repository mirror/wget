#!/usr/bin/perl -w

package HTTPServer;

use strict;

use HTTP::Daemon;
use HTTP::Status;
use HTTP::Headers;
use HTTP::Response;

our @ISA=qw(HTTP::Daemon);
my $VERSION = 0.01;

my $CRLF = "\015\012"; # "\r\n" is not portable
my $log = undef;

sub run {
    my ($self, $urls) = @_;
                                
    while (my $con = $self->accept) {
        print STDERR "Accepted a new connection\n" if $log;
        while (my $req = $con->get_request) {
            my $url_path = $req->url->path;
            if ($url_path =~ m{/$}) {
                $url_path .= 'index.html';
            }
            if ($log) {
                print STDERR "Method: ", $req->method, "\n";
                print STDERR "Path: ", $url_path, "\n";
                print STDERR "Available URLs: ", "\n";
                foreach my $key (keys %$urls) {
                    print STDERR $key, "\n";
                }
            }
            if (exists($urls->{$url_path})) {
                print STDERR "Serving requested URL: ", $url_path, "\n" if $log;
                next unless ($req->method eq "HEAD" || $req->method eq "GET");
                
                # create response
                my $tmp = $urls->{$url_path};
                my $resp = HTTP::Response->new ($tmp->{code}, $tmp->{msg});
                print STDERR "HTTP::Response: \n", $resp->as_string if $log;
                
                #if (is_dynamic_url) { # dynamic resource
                #} else { # static resource
                    # fill in headers
                    while (my ($name, $value) = each %{$tmp->{headers}}) {
                        # print STDERR "setting header: $name = $value\n";
                        $resp->header($name => $value);
                    }
                    print STDERR "HTTP::Response with headers: \n", $resp->as_string if $log;
                    
                    if ($req->method eq "GET") {
                        if (exists($tmp->{headers}{"Content-Length"})) {
                            # Content-Length and length($tmp->{content}) don't match
                            # manually prepare the HTTP response
                            $con->send_basic_header($tmp->{code}, $resp->message, $resp->protocol);
                            print $con $resp->headers_as_string($CRLF);
                            print $con $CRLF;
                            print $con $tmp->{content};                                
                            next;
                        }
                        # fill in content
                        $resp->content($tmp->{content});
                        print STDERR "HTTP::Response with content: \n", $resp->as_string if $log;
                    }
                #}
                
                $con->send_response($resp);
                print STDERR "HTTP::Response sent: \n", $resp->as_string if $log;
            } else {
                print STDERR "Requested wrong URL: ", $url_path, "\n" if $log;
                $con->send_error($HTTP::Status::RC_FORBIDDEN);
                last;
            }            
        }
        print STDERR "Closing connection\n" if $log;
        $con->close;
        undef($con);
    }
}

1;

# vim: et ts=4 sw=4

