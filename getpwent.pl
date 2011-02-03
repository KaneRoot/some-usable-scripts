#!/usr/bin/perl -w

use strict;
my $user;
my @util;
my @human;
my @inhuman;

setpwent();

while(@util=getpwent())
{
	push @human, $util[0] if ($util[-1] =~ /sh$/);
	push @inhuman, $util[0] if ! ($util[-1] =~ /sh$/);
}

endpwent();

print "\U\nThese accounts use human shells: \E\n@human\n";
print "\U\nThese accounts use human shells: \E\n@inhuman\n";
