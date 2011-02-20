#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

// utilise tube, fork, redirection E/S

//   commande  :  voir  enchainant l'execution d'une cde avec more
//   exemple :  ./voir ls -lR $HOME

int  main(int argc, char **argv)
{
int p[2],pid;

if(argc < 2)
{
    perror("erreur argument");
    exit(-1);
}

if(pipe(p) == -1)
{
    perror("erreur creation tube ");
    exit(-2);
}

pid=fork();     // creation du proc. fils 

switch(pid )
{
    case -1: 
	    perror("fork1");
        exit(-3);
	    break;

    case 0 : 	// le  fils traite la commande

	    close(1);
	    dup(p[1]); // on recupere forcement le desc. 1 (+ petit possible)	
	    close(p[0]);
	    close(p[1]);
	    execvp(argv[1],argv+1);
 	    printf("\n*** erreur exec. impossible!");
	    exit(-4);
   
    default:	//  le pere  fait le "more"
	
   	    close(0);       	// on ferme entree standard
	    dup(p[0]);     // on connecte l'entree standard au tube 
	    close(p[0]);    // pour blocage en lecture
            close(p[1]);
  	    execlp("more","more",0);   // si on saisit More par exemple  -> message erreur
            printf("\nerreur execution more \n");
	    exit(-5);
}
exit(0);  // on ne vient jamais ici
}

