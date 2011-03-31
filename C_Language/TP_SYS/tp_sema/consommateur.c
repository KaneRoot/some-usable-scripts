#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <curses.h>
#include <ctype.h>

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "consommateur.h"
#include "types.h"
#include "sema.h"
#include "constantes.h"


// Déclaration en global de certaines variables
// Utilisées par plusieurs fonctions du programme
int shmid, shm_key;
int mutex_data, mutex_tpa;

int main( int argc, char **argv)
{
	int i = 0;
	// Si on n'indique pas le numéro d'IPC
	// On quitte le programme
	if(argc < 2) 
	{ 
		printf("Usage : %s nSHM \n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	shm_key = (key_t) atoi(argv[1]);
	MEMP * memoireP;
	MEMP temp;
	MSG msgtemp;
	WINDOW *tWindow[MAX_PROD];

    WINDOW *w ;
    char c ;

	signal(SIGHUP, quitter);
	signal(SIGINT, quitter);
	signal(SIGQUIT, quitter);

	if((shmid = shmget(shm_key, sizeof(MEMP), IPC_CREAT|IPC_EXCL|0766)) == -1) 
	{ 
		perror("shmget"); 
		exit(EXIT_FAILURE);
	}
	
	if((memoireP = (MEMP *) shmat(shmid, 0 , 0766)) == (void *) -1)
	{ 
		perror("shmat"); 
		exit(EXIT_FAILURE); 
	}
		
	if((mutex_data = creat_sem( MUTEX_DATA, 1)) == -1)
	{ 
		perror("creat_sem"); exit(EXIT_FAILURE); 
	}

	if((mutex_tpa = creat_sem( MUTEX_TPA, 1)) == -1)
	{ 
		perror("creat_sem"); 
		exit(EXIT_FAILURE); 
	}

	temp.tete = 0;
	temp.queue = 0;

	for( i = 0; i < MAX_PROD ; i++)
		temp.tpa[i] = -1;

	P(mutex_data);
		*memoireP = temp;
	V(mutex_data);
		
	// nbDeProd => est-ce qu'il y a des producteur (si 0 on quitte)
	int nbDeProd;

	// numTete est un entier qui détermine la "tête" courante. Si elle a changé, c'est qu'on a ajouté un caractère
	int numTete = 0;
	int vartemp;

	// Variable temporaire qui indique le premier lancement du consommateur.c
	// Si = 0 alors aucun producteur ne s'est connecté, on ne quitte pas le programme
	// Si != 0 et si nbDeProd = 0 alors on quitte
	int premier_lancement = 0;

    initscr() ;			/* initialisation (obligatoire) de curses */
    noecho() ;			/* suppression de l'echo des caracteres tapes*/
    cbreak() ;			/* lecture non bufferisee */

	// Création des fenêtres statiquement
	for( i = 0; i < MAX_PROD; i++)
	{
		tWindow[i] = creation_fenetre(LINES / MAX_PROD, i*(LINES/MAX_PROD), "En attente");
	}

    while (1)
    {
		// On (re)met nbDeProd à 0 
		nbDeProd = 0;

		// On vérifie qu'il y ait toujours des producteurs
		P(mutex_tpa);
		for(i = 0 ; i < MAX_PROD && nbDeProd == 0 ; i++ )
		{
			if(memoireP->tpa[i] != -1)
			{
				nbDeProd++;

				// On change la valeur de la variable
				// un producteur au moins s'est déjà connecté
				premier_lancement = 1; 
			}
		}
		V(mutex_tpa);

		// On récupère la tête courante
		// Et le message courant
		P(mutex_data);
			vartemp = (int) memoireP->tete;
			msgtemp = (MSG) memoireP->f[( vartemp -1 + MAX_BUF) % MAX_BUF ];
		V(mutex_data);

		// Si le numéro de tête a changé
		// Alors on a écrit un message
		if(numTete != vartemp)
		{
			numTete = vartemp;
			c = msgtemp.c;
			w = tWindow[msgtemp.idp];

			waddch(w,c) ;
			wrefresh(w) ; 
		}

		// On incrémente la queue
		P(mutex_data);
			memoireP->queue = (memoireP->tete -1 + MAX_BUF) % MAX_BUF;
		V(mutex_data);

		// S'il n'y a plus de producteurs, on quitte
		if(nbDeProd == 0 && premier_lancement != 0)
		{
			quitter(PLUSDEPROD);
		}
		// Ralentissement volontaire du programme
		// Pour cause d'utilisation excessive de CPU
		usleep(2); 
    }
	// le programme n'est pas supposé pouvoir sortir de la boucle
	exit(EXIT_FAILURE);
}

WINDOW *creation_fenetre(int n,int d,char *t)
{
    WINDOW *cadre ;			/* la fenetre pour le cadre */
    WINDOW *w ;			/* la fenetre de dialogue */
    
    /* creation du cadre */

    cadre= newwin(n,COLS,d,0) ;
    box(cadre,0,0) ;
    mvwprintw(cadre,0,COLS/2-strlen(t)/2,t) ;
    wrefresh(cadre) ;
    
    /* creation de la fenetre de dialogue */

    w= newwin(n-2,COLS-2,d+1,1) ;
    idlok(w,TRUE) ;
    scrollok(w,TRUE) ;	   /* mise en place du defilement (scrolling) */
    wclear(w) ;
    wrefresh(w) ;
    return w ;
}

void quitter(int signal)
{
	// Fermeture de la fenêtre
	endwin() ;

	// Suppression de la mémoire partagée
	if(shmctl(shmid, IPC_RMID, 0) < 0)
	{ 
		perror("shmctl"); 
		exit(EXIT_FAILURE); 
	}

	// Suppression des sémaphores
	if(mutex_data >= 0) 
	{ 
		del_sem(MUTEX_DATA); 
	}
	if(mutex_tpa >= 0) 
	{ 
		del_sem(MUTEX_TPA); 
	}

	// Si on quitte avec le signal PLUSDEPROD on l'indique
	if(signal == PLUSDEPROD)
		printf("Plus de producteurs.\n");

	printf("FIN.\n");
	exit(EXIT_SUCCESS);
}
