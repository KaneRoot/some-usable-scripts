#!/usr/bin/perl -w

sub max{
my $max_actuel = shift @_ ;

foreach my $e (@_)
{
	if ($e > $max_actuel)
	{
		$max_actuel = $e;
	}
}
return $max_actuel;

}

