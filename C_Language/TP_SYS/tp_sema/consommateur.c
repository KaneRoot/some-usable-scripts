#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <curses.h>
#include <ctype.h>
#include "consommateur.h"
#include "types.h"
#include "sema.h"
#include "constantes.h"

WINDOW *creation_fenetre(int n,int d,char *t);
typedef struct prod_s
{
	int idp;
	WINDOW w;
} PROD;

int main( int argc, char **argv)
{
	if(argc < 2) { printf("Usage : %s nSHM \n", argv[0]); exit(EXIT_FAILURE); }

	int shmid, shm_key, i = 0;
	int mutex_data, mutex_tpa;
	key_t sem_key_data = MUTEX_DATA;
	key_t sem_key_tpa = MUTEX_TPA;

	shm_key = (key_t) atoi(argv[1]);
	MEMP * memoireP;
	MEMP temp;
	MSG msgtemp;
	WINDOW *tWindow[MAX_PROD];

    WINDOW *w ;
    char c ;

    initscr() ;			/* initialisation (obligatoire) de curses */
    noecho() ;			/* suppression de l'echo des caracteres tapes*/
    cbreak() ;			/* lecture non bufferisee */

	if((shmid = shmget(shm_key, sizeof(MEMP), IPC_CREAT|IPC_EXCL|0766)) == -1) 
	{ perror("shmget"); exit(EXIT_FAILURE);}
	
	if((memoireP = (MEMP *) shmat(shmid, 0 , 0766)) == (void *) -1)
	{ perror("shmat"); exit(EXIT_FAILURE); }
		
	if((mutex_data = creat_sem( sem_key_data, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }

	if((mutex_tpa = creat_sem( sem_key_tpa, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }

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
				premier_lancement++;
			}
		}
		V(mutex_tpa);

		P(mutex_data);
			vartemp = (int) memoireP->tete;
			msgtemp = (MSG) memoireP->f[(vartemp -1 + MAX_BUF) % MAX_BUF ];
		V(mutex_data);

		if(numTete != vartemp)
		{
			numTete = vartemp;
			c = msgtemp.c;
			w = tWindow[msgtemp.idp];

			waddch(w,c) ;
			wrefresh(w) ; 
		}

		P(mutex_data);
			vartemp = (int) memoireP->queue;
			vartemp = (vartemp +1) % MAX_BUF;
			memoireP->queue = vartemp;
		V(mutex_data);

		// S'il n'y a plus de producteurs, on quitte
		if(nbDeProd == 0 && premier_lancement != 0)
		{
			if(shmctl(shmid, IPC_RMID, 0) < 0)
			{ perror("shmctl"); exit(EXIT_FAILURE); }
		
			if(mutex_data >= 0) { del_sem(sem_key_data); }
			if(mutex_tpa >= 0) { del_sem(sem_key_tpa); }

			endwin() ;
			exit(EXIT_SUCCESS);
		}
		// Ralentissement volontaire du programme
		// Pour cause d'utilisation excessive de CPU
		usleep(2); 
    }
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
