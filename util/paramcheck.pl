#!/usr/bin/perl

# Copyright (C) 2008, 2009 Free Software Foundation, Inc.

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
use constant true  => 1;
use constant false => 0;

use FindBin qw($Bin);
use File::Spec ();

my @args = ([
    File::Spec->catfile($Bin, File::Spec->updir, 'src', 'main.c'),
    qr/static \s+? struct \s+? cmdline_option \s+? option_data\[\] \s+? = \s+? \{ (.*?) \}\;/sx,
    [ qw(long_name short_name type data argtype) ],
], [
    File::Spec->catfile($Bin, File::Spec->updir, 'src', 'init.c'),
    qr/commands\[\] \s+? = \s+? \{ (.*?) \}\;/sx,
    [ qw(name place action) ],
]);
my $tex_file = File::Spec->catfile($Bin, File::Spec->updir, 'doc', 'wget.texi');

{
    my @data;

    foreach my $arg (@args) {
        my ($file, $regex, $names) = @$arg;
        my $source = read_file($file);
        my @chunks = extract_chunks($source, $regex);
        push @data, extract_entries(\@chunks, $names);
    }

    output_results(@data);
}

sub read_file
{
    my ($file) = @_;

    open(my $fh, '<', $file) or die "Cannot open $file: $!";

    return do { local $/; <$fh> };
}

sub extract_chunks
{
    my ($source, $regex) = @_;

    my ($raw_data) = $source =~ $regex;

    return map { /\S/ && !/^\#/ ? $_ : () } split /(?<=\})/, $raw_data;
}

sub extract_entries
{
    my ($chunks, $names) = @_;

    my (@entries, %index, $i);

    foreach my $chunk (@$chunks) {
        my ($args) = $chunk =~ /\{ \s+? (.*?) \s+? \}/sx;
        next unless defined $args;

        my @args = map {
          tr/'"//d; $_
        } map {
          /\((.*?)\)/ ? $1 : $_
        } split /\,\s+/, $args;

        my $entry = { map { $_ => shift @args } @$names };

        ($entry->{line}) = $chunk =~ /^ \s+? (\{.*)/mx;
        if ($chunk =~ /deprecated/i) {
            $entries[-1]->{deprecated} = true;
        }

        my $index_name = exists $entry->{data}
          ? $entry->{data}
          : $entry->{name};

        $index{$index_name} = $i++;

        push @entries, $entry;
    }

    push @entries, \%index;

    return \@entries;
}

sub output_results
{
    my ($opts, $cmds) = @_;

    my %index = (
        opts => pop @$opts,
        cmds => pop @$cmds,
    );

    emit_no_corresponding_cmds($opts);
    print "\n";
    emit_no_matching_long_cmds($opts);
    print "\n";
    emit_no_corresponding_opts($opts, $cmds);
    print "\n";
    emit_deprecated_opts($opts);
    print "\n";
    emit_deprecated_cmds($cmds);
    print "\n";

    my $tex = read_file($tex_file);

    emit_undocumented_opts($tex, $opts);
    print "\n";
    emit_undocumented_cmds($tex, $opts, $cmds, \%index);
    print "\n";
}

sub emit_no_corresponding_cmds
{
    my ($opts) = @_;

    my @options;
    foreach my $opt (@$opts) {
        unless ($opt->{type} =~ /^(?:OPT_BOOLEAN|OPT_VALUE)$/
             && $opt->{argtype} == -1)
        {
            push @options, $opt->{line};
        }
    }

    local $" = "\n";
    print <<EOT;
No corresponding commands
=========================
@options
EOT
}

sub emit_no_matching_long_cmds
{
    my ($opts) = @_;

    my @options;
    foreach my $opt (@$opts) {
        my $long_name = $opt->{long_name};
        $long_name =~ tr/-//d;
        unless ($long_name eq $opt->{data}) {
            push @options, $opt->{line};
        }
    }

    local $" = "\n";
    print <<EOT;
Non-matching commands
=====================
@options
EOT
}

sub emit_no_corresponding_opts
{
    my ($opts, $cmds) = @_;

    my @commands;
    foreach my $cmd (@$cmds) {
        my $found = false;
        foreach my $opt (@$opts) {
            my $long_name = $opt->{long_name};
            $long_name =~ tr/-//d;
            if ($cmd->{name} eq $opt->{data}
             || $cmd->{name} eq $long_name) {
                $found = true;
                last;
            }
        }
        unless ($found) {
            push @commands, $cmd->{line};
        }
    }

    local $" = "\n";
    print <<EOT;
No corresponding options
========================
@commands
EOT
}

sub emit_deprecated_opts
{
    my ($opts) = @_;

    my @options;
    foreach my $opt (@$opts) {
        if ($opt->{deprecated}) {
            push @options, $opt->{line};
        }
    }

    local $" = "\n";
    print <<EOT;
Deprecated options
==================
@options
EOT
}

sub emit_deprecated_cmds
{
    my ($cmds) = @_;

    my @commands;
    foreach my $cmd (@$cmds) {
        if ($cmd->{deprecated}) {
            push @commands, $cmd->{line};
        }
    }

    local $" = "\n";
    print <<EOT;
Deprecated commands
===================
@commands
EOT
}

sub emit_undocumented_opts
{
    my ($tex, $opts) = @_;

    my %items;
    while ($tex =~ /^\@item\w*? \s+? --([\w\-]+)/gmx) {
        my $opt = $1;
        $items{$opt} = true;
    }
    my @options;
    foreach my $opt (@$opts) {
        my $opt_name = $opt->{long_name};
        if (not $items{$opt_name}
          || ($opt_name !~ /^no/
            ? $items{"no-$opt_name"}
            : false)
          || $opt->{deprecated})
        {
            push @options, $opt_name;
        }
    }

    local $" = "\n";
    print <<EOT;
Undocumented options
====================
@options
EOT
}

sub emit_undocumented_cmds
{
    my ($tex, $opts, $cmds, $index) = @_;

    my %items;
    while ($tex =~ /^\@item\w*? \s+? ([\w\_]+) \s+? = \s+? \S+?/gmx) {
        my $cmd = $1;
        $cmd =~ tr/_//d;
        $items{$cmd} = true;
    }
    my @commands;
    foreach my $cmd (@$cmds) {
        my $cmd_name = do {
            local $_ = exists $index->{opts}->{$cmd->{name}}
              ? $opts->[$index->{opts}->{$cmd->{name}}]->{long_name}
              : $cmd->{name};
            tr/-/_/;
            $_;
        };
        if (not $items{$cmd->{name}} || $cmd->{deprecated}) {
            push @commands, $cmd_name;
        }
    }

    local $" = "\n";
    print <<EOT;
Undocumented commands
=====================
@commands
EOT
}
