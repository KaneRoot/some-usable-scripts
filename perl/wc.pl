#!/usr/bin/perl -w

# Utilisation : wc.pl fichier

open(F, "<$ARGV[0]") || die "Problème d'ouverture de fichier ! ";

$i = 0 ;
while(<F>)
{
	$i++;
};

close(F);

print "Nombre de lignes : $i \n";
