#!/usr/bin/perl -w
use strict;

my $pid = fork();

if($pid == 0)
{
	while (1)
	{
		print "On se détache\n" ;
		sleep(1);
	}
}
else
{
	exit;
}
