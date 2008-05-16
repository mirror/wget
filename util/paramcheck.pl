#!/usr/bin/perl

# Copyright (C) 2008 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

use strict;
use warnings;

use FindBin qw($Bin);
use File::Spec ();

my @args = ([
    File::Spec->catfile($Bin, '..', 'src', 'main.c'),
    qr/static \s+? struct \s+? cmdline_option \s+? option_data\[\] \s+? = \s+? \{ (.*?) \}\;/sx,
    [ qw(long_name short_name type data argtype) ],
], [
    File::Spec->catfile($Bin, '..', 'src', 'init.c'),
    qr/commands\[\] \s+? = \s+? \{ (.*?) \}\;/sx,
    [ qw(name place action) ],
]);

{
    my (@lines, @opts, $source);
    foreach my $arg (@args) {
        my ($file, $regex, $names) = @$arg;
        $source = read_file($file);
        @lines = extract_opts_chunk($source, $regex);
        push @opts, extract_opts(\@lines, $names);
    }
    walk_opts(@opts);
}

sub read_file
{
    my ($file) = @_;
    open(my $fh, '<', $file) or die "Cannot open $file: $!";
    return do { local $/; <$fh> };
}

sub extract_opts_chunk
{
    my ($source, $regex) = @_;
    my ($opts) = $source =~ $regex;
    return map { /\S/ && !/^\#/ ? $_ : () } split /(?<=\})/, $opts;
}

sub extract_opts
{
    my ($lines, $names) = @_;
    my @opts;
    foreach my $line (@$lines) {
        my ($args) = $line =~ /\{ \s+? (.*?) \s+? \}/sx;
        next unless defined $args;
        my @args = map { tr/'"//d; $_ }
                   map { /\((.*?)\)/ ? $1 : $_ }
                   split /\,\s+/, $args;
        my $opt = { map { $_ => shift @args } @$names };
        ($opt->{line}) = $line =~ /.*? (\{.*)/;
        $opts[-1]->{is_deprecated} = 1 if $line =~ /deprecated/i;
        push @opts, $opt;
    }
    return \@opts;
}

sub walk_opts
{
    emit_no_corresponding_cmds(@_);
    print "\n";
    emit_no_matching_long_cmds(@_);
    print "\n";
    emit_no_corresponding_opts(@_);
    print "\n";
    emit_deprecated_opts(@_);
    print "\n";
    emit_deprecated_cmds(@_);
    print "\n";
}

sub emit_no_corresponding_cmds
{
    my ($opts) = @_;
    print <<EOT;
No corresponding commands
=========================
EOT
    foreach my $opt (@$opts) {
        unless ($opt->{type} =~ /^(?:OPT_BOOLEAN|OPT_VALUE)$/
             && $opt->{argtype} == -1)
        {
            print $opt->{line}, "\n";
        }
    }
}

sub emit_no_matching_long_cmds
{
    my ($opts) = @_;
    print <<EOT;
Non-matching commands
=====================
EOT
    foreach my $opt (@$opts) {
        my $long_name = $opt->{long_name};
        $long_name =~ tr/-//d;
        unless ($long_name eq $opt->{data}) {
            print $opt->{line}, "\n";
        }
    }
}

sub emit_no_corresponding_opts
{
    my ($opts, $cmds) = @_;
    print <<EOT;
No corresponding options
========================
EOT
    foreach my $cmd (@$cmds) {
        my $found = 0;
        foreach my $opt (@$opts) {
            my $long_name = $opt->{long_name};
            $long_name =~ tr/-//d;
            if ($cmd->{name} eq $opt->{data}
             || $cmd->{name} eq $long_name) {
                $found = 1;
                last;
            }
        }
        unless ($found) {
            print $cmd->{line}, "\n";
        }
    }
}

sub emit_deprecated_opts
{
    my ($opts) = @_;
    print <<EOT;
Deprecated options
==================
EOT
    foreach my $opt (@$opts) {
        if ($opt->{is_deprecated}) {
            print $opt->{line}, "\n";
        }
    }
}

sub emit_deprecated_cmds
{
    my ($opts, $cmds) = @_;
    print <<EOT;
Deprecated commands
===================
EOT
    foreach my $cmd (@$cmds) {
        if ($cmd->{is_deprecated}) {
            print $cmd->{line}, "\n";
        }
    }
}
