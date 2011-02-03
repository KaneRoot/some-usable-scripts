#!/usr/bin/perl -w
use strict;

my @fils;
print "Mon PID :". $$ ."\n ";

sub nouveau
{
	my $pid = fork();
	if($pid==0)
	{
		exec("perl chrono.pl");
	}
	else
	{
		push(@fils,$pid);
		print "nouveau chrono : $pid \n";
		print "liste des fils : @fils \n";
	}
}
sub demandeTemps
{
	print "On transmet SIGINT à tous les chronos";
	kill 2, @fils;
}
sub arret
{
	print "On transmet SIGQUIT à tous les chronos";
	kill 3, @fils;
	exit(0);
}

$SIG{"TERM"} = "nouveau";  
$SIG{"INT"} = "demandeTemps"; # INT = kill 2 = CTRL C
$SIG{"QUIT"} = "arret"; # QUIT = kill 3
while(1){}
