package SSLTest;

use strict;
use warnings;

use SSLServer;
use WgetTests;
use HTTPTest;

our @ISA = qw(WgetTest HTTPTest);
my $VERSION = 0.01;

my %ssl_defaults = (
    _certfile  => "certs/server.crt",
    _keyfile   => "certs/server.key",
    _cafile    => "certs/test-ca-cert.pem",
    _ciphers   => 'ALL',
    _lhostname => 'wgettestingserver',
);

{
    my %_attr_data = %ssl_defaults;

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

sub _setup_server
{
    my $self = shift;
    my %ssl_config = %ssl_defaults;

    $self->{_server} = SSLServer->new()
        or die "Cannot create SSL server!!!";

    for my $attrname ($self->_standard_keys())
    {
        my ($argname) = ($attrname =~ m/^_(.*)/msx);
        $ssl_config{$argname} = $self->{$attrname};
    }
    for my $attrname (keys %ssl_config)
    {
        if ($attrname =~ m/file$/)
        {
            my $cwd = $self->SUPER::_default_for('_workdir');
            my $cfile = $ssl_config{$attrname};
            $ssl_config{$attrname} = "$cwd/$cfile";
        }
    }
    $self->{_server}->init(%ssl_config);
}

1;

# vim: et ts=4 sw=4
