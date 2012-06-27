#!/usr/bin/perl -w 
$motif = shift(@ARGV);
# $motif=$ARGV[0]
#Shift

# Manière non explicite
while(<>)
{
	print if(/$motif/);
};

# Manière explicite
#while($ligne = <>)
#{
#	if($ligne =~ /$motif/)
#	{
#		print $ligne;
#	}
#};
