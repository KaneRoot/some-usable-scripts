#!/usr/bin/perl -w

use strict;
my $user;
my @util;
my @human;
my @inhuman;

open(USERS,"getent passwd |") || die "$!";

while(<USERS>)
{
	@util = split(':', $_);
	push @human, $util[0] if (/sh$/);
	push @inhuman, $util[0] if ! (/sh$/);
}

close USERS;

print "\U\nThese accounts use human shells: \E\n@human\n";
print "\U\nThese accounts use human shells: \E\n@inhuman\n";
