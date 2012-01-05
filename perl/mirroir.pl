#!/usr/bin/perl -w
use strict;
use warnings;
use 5.010;

sub mirroir
{
	my $chaine = join(' ',@_);
	my $mirroir; 
	my $i = 0;
	my $taille = length($chaine);
	until($i == $taille)
	{
		$mirroir .= chop($chaine);
		$i++;
	}
	return $mirroir;
}	
say mirroir(@ARGV);
