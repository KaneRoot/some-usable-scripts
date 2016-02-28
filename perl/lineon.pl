#!/usr/bin/perl -w
use v5.20;

sub usage {
    say "usage : $0 [pattern [replacement]]";
}

do { usage ; exit 1} if @ARGV > 2;
do { usage ; exit 0} if @ARGV == 1 && $ARGV[0] =~ /-h/i;

my ($pattern, $repl) = @ARGV;
#say "pattern: $pattern, replacement: $repl";

@ARGV = ();
my $lines = '';

$lines .= $_ while (<>);
$lines =~ s/\n/ /g;

my @l = split /$pattern/, $lines;
map { $_ .= $repl } @l;
say for @l;
