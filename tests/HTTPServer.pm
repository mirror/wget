#!/usr/bin/perl -w

package HTTPServer;

use strict;

use HTTP::Daemon;
use HTTP::Status;
use HTTP::Headers;
use HTTP::Response;

our @ISA=qw(HTTP::Daemon);

my $CRLF = "\015\012"; # "\r\n" is not portable

sub run {
    my ($self, $urls) = @_;
                                
    while (my $con = $self->accept) {
        while (my $req = $con->get_request) {
            # print STDERR "method: ", $req->method, "\n";
            if (exists($urls->{$req->url->path})) {
                next unless ($req->method eq "HEAD" || $req->method eq "GET");
                # print STDERR "requested URL: ", $req->url->path, "\n";
                    
                # create response
                my $tmp = $urls->{$req->url->path};
                my $resp = HTTP::Response->new ($tmp->{code},
                                                $tmp->{msg});
                # print STDERR "HTTP::Response: \n", $resp->as_string;
                
                # fill in headers
                while (my ($name, $value) = each %{$tmp->{headers}}) {
                    # print STDERR "setting header: $name = $value\n";
                    $resp->header($name => $value);
                }
                # print STDERR "HTTP::Response with headers: \n", $resp->as_string;
                
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
                    # print STDERR "HTTP::Response with content: \n", $resp->as_string;
                }
                
                $con->send_response($resp);
                # print STDERR "HTTP::Response sent: \n", $resp->as_string;
            } else {
                # print STDERR "requested wrong URL: ", $req->url->path, "\n";
                $con->send_error($HTTP::Status::RC_FORBIDDEN);
            }
        }
        $con->close;
        undef($con);
    }
}

1;

# vim: et ts=4 sw=4

