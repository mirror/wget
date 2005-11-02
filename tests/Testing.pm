#!/usr/bin/perl -w

use HTTPServer;

use strict;

package Testing;

sub Run_HTTP_Test {
    
    my ($urls, $cmdline, $expected_error_code, $expected_downloaded_files) = @_;
    
    my $pid = HTTPServer::run (%{$urls});

    print "Spawned HTTP server with pid: $pid\n"; 

    my $returned_error_code = system ($cmdline);

    kill ('TERM', $pid);

    print "Killed HTTP server\n";

    $returned_error_code == $expected_error_code 
        or die "Test failed: wrong code returned (was: $returned_error_code, expected: $expected_error_code)";

    if (my $str = verify_download (%{$expected_downloaded_files})) {
        die $str;
    }

    print "Test successful."
}


sub verify_download {
    my (%expected_downloaded_files) = @_;
       
    # use slurp mode to read file content
    my $old_input_record_separator = $/;
    undef $/;
    
    while (my ($filename, $expected_content) = each %expected_downloaded_files) {
        open (FILE, $filename) or return "Test failed: file $filename not downloaded";
        
        my $content = <FILE>;
        $content eq $expected_content or return "Test failed: wrong content for file $filename";
        
        close (FILE);
    } 
    
    $/ = $old_input_record_separator;

    return "";
}

1;

# vim: et ts=4 sw=4

