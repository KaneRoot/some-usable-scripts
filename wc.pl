#!/usr/bin/perl -w

use strict;

die "un argument svp ! " if !defined ($ARGV[0]);

my $i=0;
open(P,"< $ARGV[0]") || die "erreur ouverture $!";

while (<P>)
{
	$i++;
}
close(P);
print "nb de lignes = $i \n";
