#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// creation d'un processus chrono qui compte les secondes
// sur le signal SIGINT le processus affiche la valeur du compteur
// sur le signal SIGQUIT le processus affiche le compteur et quitte.
//
// lancer le programme dans une fenetre et tester depuis une autre
// kill -2 pid   display the timer
// kill -3 pid   display the timer and stop the process


int nsec = 0 ; // Nombre de secondes


void seconde()
{
		print "coucou\n";
    	alarm(1);	// on repositionne l'evenement SIGALRM
    	$nsec = $nsec + 1;
}

void inter()
{
//	affiche la valeur du compteur
    print "\n" , $nsec, " secondes ecoulees \n";
}

void arret()
{
//    affiche la valeur du compteur et quitte
	print "\n" , $nsec, " secondes ecoulees \n";
	print "Fin du chronometre!";
	exit(0);
}


// debut du programme

$SIG {"ALRM"} = "seconde";	//#on associe la fct handler au signal SIGALRM(14)
$SIG {"INT"}    = "inter";		//# idem pour le signal SIGINT (2)
$SIG{"QUIT"} = "arret";		//# idem pour le signal SIGQUIT  (3)

alarm(1) ;	// on initialise le processus

print("\ndebut (%d) \n", );  // on affiche le pid et on boucle

while (1) {
    getc()
}
