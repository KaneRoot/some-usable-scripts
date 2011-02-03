#!/usr/bin/perl -w

use strict;
my $nb=0;
open(LS,"ls -l |") || die "$!";

while (<LS>)
{
	print ;
	$nb++;
}
close(LS);
$nb--; # à cause de la première ligne qui indique le total
print "nb d'objets : $nb\n";
