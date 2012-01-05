#!/usr/bin/perl -w

# Utilisation : wc.pl fichier

open(F, "<$ARGV[0]") || die "Problème d'ouverture de fichier ! ";

$i = 0 ;
$i++ while(<F>);

close(F);

print "Nombre de lignes : $i \n";
