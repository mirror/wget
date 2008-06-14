#!/usr/bin/perl -w

package FTPTest;

use strict;

use FTPServer;
use WgetTest;

our @ISA = qw(WgetTest);
my $VERSION = 0.01;


{
    my %_attr_data = ( # DEFAULT
    );
    
    sub _default_for
    {
        my ($self, $attr) = @_;
        return $_attr_data{$attr} if exists $_attr_data{$attr};
        return $self->SUPER::_default_for($attr);
    }

    sub _standard_keys 
    {
        my ($self) = @_;
        ($self->SUPER::_standard_keys(), keys %_attr_data);
    }
}
    

sub _setup_server {
    my $self = shift;

    foreach my $url (keys %{$self->{_input}}) {
        my $filename = $url;
        $filename =~ s/^\///;
        open (FILE, ">$filename")
            or return "Test failed: cannot open input file $filename\n";

        print FILE $self->{_input}->{$url}->{content}
            or return "Test failed: cannot write input file $filename\n";

        close (FILE);
    }

    $self->{_server} = FTPServer->new (LocalAddr => 'localhost',
                                       ReuseAddr => 1,
                                       rootDir => "$self->{_workdir}/$self->{_name}/input") or die "Cannot create server!!!";
}


sub _launch_server {
    my $self = shift;
    my $synch_func = shift;
    $self->{_server}->run ($synch_func);
}

sub _substitute_port {
    my $self = shift;
    my $ret = shift;
    $ret =~ s/{{port}}/$self->{_server}->sockport/eg;
    return $ret;
}

1;

# vim: et ts=4 sw=4

