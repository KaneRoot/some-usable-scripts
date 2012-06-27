#!/usr/bin/perl

use 5.16.0;

# Exercices tableaux
my @alphabet = ("a" .. "z");
my @cartes = ("01".."10","valet","dame","roi");
my @annee=("a1","a2","lp");
my @promo=@annee;
my @tout = (@alphabet , "trucmachin" , @cartes , 1145, "\n");

print @tout;

# Autre exercice

my @jours=("Lundi","Mardi","Mercredi");

# explicite
#foreach $jours(@jours)
#{
#	print $jours."\n";
#}

say foreach @jours ;
	
# Perl : les nombres : < > <= >= == !=
#		 Chaînes : lt gt eq ne

# !~ et =~ sont des opérateurs d'appartenance
