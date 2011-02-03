#!/usr/bin/perl -w
use strict;

my $nbsec = 0;
sub seconde
{
	alarm(1);
	$nbsec += 1;
}
sub inter
{
	print "\n".$nbsec." secondes ! PID : ".$$;
}
sub arret
{
	print "\nNombre de secondes : ".$nbsec." Arret de : ".$$." (chrono.pl)";
	exit(0);
}

$SIG{"ALRM"} = "seconde";
$SIG{"INT"} = "inter";
$SIG{"QUIT"} = "arret";

alarm(1);
print "\nDébut " . $$ . " !";
while(1){}
