#!/usr/bin/perl

# Exercices tableaux
@alphabet = ("a" .. "z");
@cartes = ("01".."10","valet","dame","roi");
@annee=("a1","a2","lp");
@promo=@annee;
@tout = (@alphabet , "dut" , @cartes , 1145, "\n");

print @tout;

# Autre exercice

@jours=("Lundi","Mardi","Mercredi");

foreach $jours(@jours)
{
	print $jours."\n";
}

# Perl : les nombres : < > <= >= == !=
#		 Chaînes : lt gt eq ne

# !~ et =~ sont des opérateurs d'appartenance
