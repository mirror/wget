#!/usr/bin/perl -w

use Test;

package HTTPTest;
our @ISA = qw(Test);
$VERSION = 0.01;

use strict;

use HTTPServer;


{
    my %_attr_data = ( # DEFAULT
        _urls         => {},
        _cmdline      => "",
        _errcode      => 0,
        _downloads    => {},
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
    

sub run {
    my $self = shift;

    my $pid = fork();

    if($pid == 0) {
        my $server = HTTPServer->new (LocalAddr => 'localhost',
                                      LocalPort => '8080',
                                      ReuseAddr => 1) or die "Cannot create server!!!";
        $server->run ($self->{_urls});
    }

    # print "Spawned HTTP server with pid: $pid\n"; 

    # print "Calling $self->{_cmdline}\n";
    my $errcode = system ($self->{_cmdline});

    kill ('TERM', $pid);

    # print "Killed HTTP server\n";

    $errcode == $self->{_errcode}
        or die "Test failed: wrong code returned (was: $errcode, expected: $self->{_errcode})";

    if (my $error_str = $self->_verify_download()) {
        die $error_str;
    }

    print "Test successful.\n"
}


sub _verify_download {    
    my $self = shift;

    # use slurp mode to read file content
    my $old_input_record_separator = $/;
    undef $/;
    
    while (my ($filename, $filedata) = each %{$self->{_downloads}}) {
        open (FILE, $filename) 
            or return "Test failed: file $filename not downloaded";
        
        my $content = <FILE>;
        $content eq $filedata->{'content'} 
            or return "Test failed: wrong content for file $filename";

        if (exists($filedata->{'timestamp'})) {
            my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
                $atime,$mtime,$ctime,$blksize,$blocks) = stat FILE;

            $mtime == $filedata->{'timestamp'} 
                or return "Test failed: wrong timestamp for file $filename";
        }
        
        close (FILE);
    } 
    
    $/ = $old_input_record_separator;

    return "";
}

1;

# vim: et ts=4 sw=4

