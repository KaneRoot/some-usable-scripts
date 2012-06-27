#!/usr/bin/perl -w 
# -w pour les erreurs

$motif = shift(@ARGV);
# $motif=$ARGV[0]
#Shift

# Manière non explicite
while(<>)
{
	if(/$motif/) { print ; };
};

# Manière explicite
while($ligne = <>)
{
	if($ligne =~ /$motif/)
	{
		print $ligne;
	}
};
