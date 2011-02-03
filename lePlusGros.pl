#!/usr/bin/perl -w
# leplusGros.pl <rep>
# donne le nom du fichier ordinaire localisé ds <rep>
# (& directement subordonné) le plus GROS (en taille)
# on se base sur le champ size (pas le nbre de
#blocs alloués !)
use strict;
use File::stat;
# déclaration des variables
my $rep ;
# répertoire en argument
my $size ;
my $max_size = 0 ;
# initialisation du max
my $heavy_file_name ;
# nom du fichier le + lourd
my @files ; # liste des objets du répertoire
my $file ;
my $count_file = 0 ;

if ( @ARGV != 1) {
	print "usage : $0 <repertoire >\n" ; exit (-1) ;
}
$rep = $ARGV[0] ;

die "repertoire inconnu ou pas en droit de lecture !" unless -d $rep and -r $rep ;


# récupérer la liste des objets du répertoire
# (fichiers "cachés" compris)
@files = glob "$rep/* $rep/.*" ;
foreach $file(@files)
{
	my $sb=stat($file);
	$size=$sb->size;
	print $file," fait ", $size, " octets\n";
	if($size > $max_size)
	{
		print "C'est lui le plus gros !\n";
		$heavy_file_name=$file;
		$max_size=$size;
	}
	$count_file++;
}
print "Le fichier le plus gros est $heavy_file_name et fait $max_size octets\n";
