#!/usr/bin/perl

$motif=$ARGV[0];
shift;
foreach $f (@ARGV)
{
	open(F,"<$f") || die "Impossible de lire le fichier $f : $!";
	
	while(<F>)
	{
		if(/$motif/)
		{	print "Motif trouvé dans $f : $_ \n";}
	};
}
