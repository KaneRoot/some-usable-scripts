#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <curses.h>
#include <ctype.h>
#include <signal.h>
#include "constantes.h"
#include "types.h"
#include "sema.h"

#define NAMESIZE 30

char * nom_de_la_fenetre = NULL;
int mutex_data, mutex_tpa, i=0;
MEMP *memoireP; 

void quitter(int signal);
WINDOW *creation_fenetre(int n,int d,char *t);
int main( int argc, char **argv)
{
	if(argc < 2) { printf("Usage %s numIPC\n", argv[0]); exit(EXIT_FAILURE); }
	char c;
    const char CTRL_D = 4 ;
	int shmid; 
	int shm_key = atoi(argv[1]);

    WINDOW * fenetre ;

	key_t sem_key_data = MUTEX_DATA;
	key_t sem_key_tpa = MUTEX_TPA;

	shmid = shmget(shm_key, sizeof(MEMP), 0766 | IPC_CREAT); 


	// On quitte si on reçoit ces signaux
	signal(SIGHUP, quitter);
	signal(SIGINT, quitter);
	signal(SIGQUIT, quitter);

	if (shmid == -1) { perror("shmget"); exit(EXIT_FAILURE); }

	if((memoireP = (MEMP *) shmat(shmid, 0 , 0766)) ==(void *) -1)	{ perror("shmat"); exit(EXIT_FAILURE); }
	if((mutex_data = open_sem( sem_key_data)) == -1)	{ perror("open_sem"); exit(EXIT_FAILURE); }
	if((mutex_tpa = open_sem( sem_key_tpa)) == -1)		{ perror("open_sem"); exit(EXIT_FAILURE); }

	P(mutex_tpa);
		for(i = 0; i < MAX_PROD && memoireP->tpa[i] != -1 ; i++);
		if(memoireP->tpa[i] != -1) { V(mutex_tpa); exit(EXIT_FAILURE); }
		memoireP->tpa[i] = 0;
	V(mutex_tpa);

    initscr() ;			/* initialisation (obligatoire) de curses */
    noecho() ;			/* suppression de l'echo des caracteres tapes*/
    cbreak() ;			/* lecture non bufferisee */


	// Je donne un nom à ma fenêtre
	nom_de_la_fenetre = (char *) malloc(sizeof(char *) * NAMESIZE);
	snprintf(nom_de_la_fenetre, NAMESIZE, "PRODUCTEUR %d", i);
    fenetre = creation_fenetre(LINES,0,nom_de_la_fenetre);

	// On quitte le producteur en tappant CTRL_D
    while (( c = wgetch(fenetre)) != CTRL_D)
	{

		P(mutex_data);
			if(((memoireP->queue -1) % MAX_BUF) != (memoireP->tete % MAX_BUF) )
			{
				memoireP->f[memoireP->tete].c = c;
				memoireP->f[memoireP->tete].idp = i;
				memoireP->tete++;
			}
		V(mutex_data);

        waddch(fenetre,c) ;
        wrefresh(fenetre) ; 
	}
	quitter(0);
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

    endwin();
	// On remet la valeur de l'indice du processus à -1 
	// dans le tableau des producteurs
	P(mutex_tpa);
		memoireP->tpa[i] = -1;	
	V(mutex_tpa);

	// On libère la mémoire de façon propre
	free(nom_de_la_fenetre);

	exit(EXIT_SUCCESS); 

}
