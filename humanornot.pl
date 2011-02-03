#!/usr/bin/perl -w

use strict ;
my $user ;
my @util ;
my @human ;
my @inhuman ;

foreach $user (`getent passwd`)
{
	@util = split(':', $user);	
	if ( $util[-1] =~ /sh$/ )
	{
		push @human, $util[0];
	}
	else
	{
		push @inhuman, $util[0];
	}
}

$"=', ';

print "\UThese accounts use human shells: \E\n@human\n";
print "\UThese accounts use inhuman shells: \E\n@inhuman\n";
		
