#!/usr/bin/perl -w

$nbmots = 0 ;

while (<>)
{
	@tab_mots = split (/\W+/);
	$nbmots += $#tab_mots + 1 ; # $nbmots += @tab_mots
}

print "nb de mots : $nbmots \n";
