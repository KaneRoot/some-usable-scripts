#!/usr/bin/perl -w

sub max{
	my $max_actuel = shift @_;

	foreach (@_)
	{
		if ($_ > $max_actuel)
		{
			$max_actuel = $_;
		}
	}
$max_actuel;
}

