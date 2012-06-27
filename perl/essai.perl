#!/usr/bin/perl
while(<>)
{
	if($_ =~ "Salut")
	{
		print "OK\n";
	}
};

while(<>)
{
	print if $_=~/"Bonjour"/;
};
# Encore plus simple !!
while(<>)
{
	print if /"Bonjour"/;
};
