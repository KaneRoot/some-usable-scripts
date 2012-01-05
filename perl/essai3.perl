#!/usr/bin/perl

# Exercices tableaux
@alphabet = ("a" .. "z");
@cartes = ("01".."10","valet","dame","roi");
@annee=("a1","a2","lp");
@promo=@annee;
@tout = (@alphabet , "trucmachin" , @cartes , 1145, "\n");

print @tout;

# Autre exercice

@jours=("Lundi","Mardi","Mercredi");

print $_."\n" foreach @jours ;
	
# Perl : les nombres : < > <= >= == !=
#		 Chaînes : lt gt eq ne

# !~ et =~ sont des opérateurs d'appartenance
