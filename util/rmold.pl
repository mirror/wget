#! /usr/bin/perl -w

# Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


# This script is a very lame hack to remove local files, until the
# time when Wget proper will have this functionality.
# Use with utmost care!

# If the remote server supports BSD-style listings, set this to 0.
$sysvlisting = 1;

$verbose = 0;

if (@ARGV && ($ARGV[0] eq '-v')) {
    shift;
    $verbose = 1;
}

defined($dirs[0] = shift) || ($dirs[0] = '.');
while (defined($_ = shift)) {
    @dirs = (@dirs, $_);
}

foreach $_ (@dirs) {
    &procdir($_);
}

# End here

sub procdir
{
    local($dir = $_[0]);
    local(@lcfiles, @lcdirs, %files, @fl);

    print STDERR "Processing directory '$dir':\n" if $verbose;
    
    opendir(DH, $dir) || die("Cannot open $dir: $!\n");
    @lcfiles = ();
    @lcdirs = ();
    # Read local files and directories.
    foreach $_ (readdir(DH)) {
        /^(\.listing|\.\.?)$/ && next;
        if (-d "$dir/$_" || -l "$dir/$_") {
            @lcdirs = (@lcdirs, $_);
        }
        else {
            @lcfiles = (@lcfiles, $_);
        }
    }
    closedir(DH);
    # Parse .listing
    if (open(FD, "<$dir/.listing")) {
        @files = ();
        while (<FD>)
        {
            # Weed out the line beginning with 'total'
            /^total/ && next;
            # Weed out everything but plain files and symlinks.
            /^[-l]/ || next;
            @fl = split;
            $files{$fl[7 + $sysvlisting]} = 1;
        }
        close FD;
        foreach $_ (@lcfiles) {
            if (!$files{$_}) {
                print "$dir/$_\n";
            }
        }
    }
    else {
        print STDERR "Warning: $dir/.listing: $!\n";
    }
    foreach $_ (@lcdirs) {
        &procdir("$dir/$_");
    }
}

