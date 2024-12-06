#!/usr/bin/perl -w
use v5.14;

while(<>) {
	chomp;
	my @wl = split "_\+";
	my @wl2 = map { ucfirst lc } @wl;
	say join "", @wl2;
}
