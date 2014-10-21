#!/usr/bin/perl -w
use strict;
use warnings;
use v5.14;

die "usage : ./$0 website_list.txt" if @ARGV != 1;

say "<html><body><p>";

my @tab;

while(<>) {
    chomp;
	last if $_ eq "";

	if(m#/#) {
		$_ =~ s#https?://##;
		@tab = split '/', $_;
		$_ = $tab[0];
	}

    my $ret = `/usr/bin/dig +short AAAA $_`;

    if(length $ret != 0) {
        say "$_ is ok<br />";
    }
    else {
        say "<b>WARNING: $_ NOT OK</b><br />";
    }
}

say "</p></body></html>";

