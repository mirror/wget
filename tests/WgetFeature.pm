package WgetFeature;

use strict;
use warnings;

our $VERSION = 0.01;

use Carp;
use English qw(-no_match_vars);
use WgetTests;

our %SKIP_MESSAGES;
{
    open my $fh, '<', 'WgetFeature.cfg'
      or croak "Cannot open 'WgetFeature.cfg': $ERRNO";
    my @lines = <$fh>;
    close $fh or carp "Cannot close 'WgetFeature.cfg': $ERRNO";
    eval {
        @lines;
        1;
    } or carp "Cannot eval 'WgetFeature.cfg': $ERRNO";
}

sub import
{
    my ($class, $feature) = @_;

    my $output = `$WgetTest::WGETPATH --version`;
    my ($list) = $output =~ m/^([+-]\S+(?:\s+[+-]\S+)+)/msx;
    my %have_features;
    for my $f (split m/\s+/msx, $list)
    {
        my $feat = $f;
        $feat =~ s/^.//msx;
        $have_features{$feat} = $f =~ m/^[+]/msx ? 1 : 0;
    }
    if (!$have_features{$feature})
    {
        print "$SKIP_MESSAGES{$feature}\n";
        exit 77;    # skip
    }
}

1;
