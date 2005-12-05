#!/usr/bin/perl -w

package Test;
$VERSION = 0.01;

use strict;


{
    my %_attr_data = ( # DEFAULT
    );
    
	sub _default_for
	{
		my ($self, $attr) = @_;
		$_attr_data{$attr};
	}

	sub _standard_keys 
	{
		keys %_attr_data;
	}
}

sub new {
    my ($caller, %args) = @_;
    my $caller_is_obj = ref($caller);
    my $class = $caller_is_obj || $caller;
    my $self = bless {}, $class;
    foreach my $attrname ($self->_standard_keys()) {
        my ($argname) = ($attrname =~ /^_(.*)/);
        if (exists $args{$argname}) {
            #printf STDERR "Setting up $attrname\n";
            $self->{$attrname} = $args{$argname};
        } elsif ($caller_is_obj) {
            #printf STDERR "Copying $attrname\n";
            $self->{$attrname} = $caller->{$argname};
        } else {
            #printf STDERR "Using default for $attrname\n";
            $self->{$attrname} = $self->_default_for($argname);
        }
    }
    return $self;
}

1;

# vim: et ts=4 sw=4

