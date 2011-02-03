#!/usr/bin/perl -w
use strict;

exit(1) unless @ARGV==2;

my $f1 = shift @ARGV;
my $f2 = shift;
my $buffer1;
my $buffer2;
my $SIZE = 8;
my $lec1;
my $lec2;

exit(2) unless -f $f1 and -r $f1 and -f $f2 and -r $f2;

open(f1,"<$f1") || exit(2);
open(f2,"<$f2") || exit(2);

do
{
	$lec1 = sysread(f1,$buffer1,$SIZE);
	$lec2 = sysread(f2,$buffer2,$SIZE);

	exit(1) unless $buffer1 eq $buffer2;	
}while( $lec1 == $lec2 and $lec1 > 0 );
exit(1) unless $lec1 == $lec2;

close f1;
close f2;
