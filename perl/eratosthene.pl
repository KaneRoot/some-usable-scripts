#!/usr/bin/perl -w
use strict;


sub Crible
{
	my ($n) = @_;
# Liste initiale :
	my @nombres = (2..$n);
# Liste des nombres premiers trouvés :
	my @premiers = ();
# Tant qu'il y a des éléments (un tableau
# en contexte booléen vaut faux s'il est vide) :
	while( @nombres )
	{
# On extrait le premier nombre
		my $prem = shift @nombres;
# On indique qu'il est premier
		push @premiers, $prem;
# On supprime ses multiples
		@nombres = grep { ($_ % $prem) != 0} @nombres;
	}
# On renvoie la liste des nombres premiers
	return @premiers;
}
my @t;
@t = Crible(10000) unless defined($ARGV[0]);
@t = Crible($ARGV[0]) if defined($ARGV[0]);
my $t = join(':',@t);
printf "$t\n";
