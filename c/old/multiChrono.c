#!/usr/bin/perl -w

# creation d'un programme  "multiChrono.pl"  qui va creer un nouveau processus chrono
# à chaque fois qu'il recoit le signal SIGTERM
# sur le signal SIGINT le processus "multiChrono" envoie ce signal à tous ses fils qui
# affichent à leur tour la valeur du compteur
# sur le signal SIGQUIT le processus renvoie ce signal à tous ses fils qui
# affichent la valeur de leur compteur et quittent.
#

@tab;   # liste des fils crées

sub nouveau
{
	# creation d'un processus
	$pid=fork();
	
	if($pid == 0 )
	{
		exec "chrono.pl";
		exit(255);
	}
	else
	{
		$tab[$#tab + 1] = $pid;  # on ajoute le nouveau fils
	 	print "nouveau chrono cree ( $pid)\n ";
		print "liste des fils @tab \n";
	}
}
		

sub  inter
{
#    affiche la valeur du compteur
#  on transmet ce signal à tous les fils

	print "\n on transmet le signal SIGINT a tous les chronometres  fils \n";
	kill 2, @tab;
}

sub arret
{
	print "\n on transmet le signal SIGQUIT a tous les chronometres  fils \n";
	kill 3, @tab;
	$tab=();  # on vide le tableau + wait à faire
	exit(0);
}


# debut du programme
# print "\ndebut \n"

$SIG {"TERM"} = "nouveau";	#on cree un nouveau chrono
$SIG {"INT"}    = "inter";		# signal SIGINT (2)
$SIG{"QUIT"} = "arret";		# SIGQUIT  (3)

print "\nInitialisation - programme principal = $$ \n";  # on affiche le pid et on boucle

while (1) {
    getc
}
