#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


/*void erreurMes(char * format, ...)
{
char texte[200];
va_list liste_arguments;

va_start(liste_arguments,format);

vsnprintf(texte,200,format,liste_arguments);

va_end(liste_arguments);

if(errno)
      perror(texte);
else
       fprintf(stderr,texte);
  exit(1);
}
*/

/*-----------------------------------------------------------*/

int creat_sem(key_t cle,int val)

/* creation du semaphore cle ayant comme valeur initiale val
   retourne un identificateur de semaphore >=0 ou -1 si erreur
*/

{
int semid;

union semun{
    int val;
    struct semid_ds *buf;
    ushort *array;
    } arg;

    if((semid=semget(cle,1,0666+IPC_CREAT+IPC_EXCL))>= 0)
    {
	arg.val=val;
	if(semctl(semid,0,SETVAL,arg)< 0)
		semid = -1;
    }
    return(semid);
}

/*--------------------------------------------------------------*/

int del_sem(key_t cle)

/* destruction du semaphore cle 
   retourne:
	0 si la destruction du semaphore s est effectuee correctement
       -1 si erreur
*/
{

    return(semctl((semget(cle,0,0)),0,IPC_RMID,0));

}

/*---------------------------------------------------------------*/

int open_sem(key_t cle)

/* recherche le semaphore cle
   retourne l'identificateur du semaphore >=0 ou -1 si erreur
*/
{

return(semget(cle,0,0));

}

/*----------------------------------------------------------------*/

void P(int semid)

{
struct sembuf psembuf;

psembuf.sem_op = -1;
psembuf.sem_flg = 0;
psembuf.sem_num = 0;
semop(semid,&psembuf,1);
}

/*------------------------------------------------------------------*/

void V(int semid)

{
struct sembuf vsembuf;

vsembuf.sem_op = 1;
vsembuf.sem_flg = 0;
vsembuf.sem_num = 0;
semop(semid,&vsembuf,1);
}

/*--------------------------------------------------------------*/

