#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

union semun
    {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };

void erreur(char *s)
{
    if(errno)
        perror(s);
    else
        fprintf(stderr,"%s\n",s);
    exit(1);
}

/*-----------------------------------------------------------*/

int creat_sem(key_t cle,int val)

/* creation du semaphore cle ayant comme valeur initiale val
   retourne un identificateur de semaphore >=0 ou -1 si erreur
*/

{
int semid ;

union semun arg;

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
    int semid;

    if((semid = semget(cle,0,0)) >= 0)
        semid =  semctl(semid,0,IPC_RMID,0);
    
    if(semid != -1)
        semid = 0;
    return semid;

}

/*---------------------------------------------------------------*/

int chuid_sem(int semid, uid_t uid)

/* change le owner's user id du semaphore semid en lui donnant la valeur
   uid
   retourne 0 si ok
           -1 si erreur
*/
{
    int ret;
    union semun arg;

    struct semid_ds str_sema;

    arg.buf = &str_sema;
    
    if((ret = semctl(semid,0,IPC_STAT,arg)) != -1)
    {
        str_sema.sem_perm.uid = uid;
        ret = semctl(semid,0,IPC_SET,arg);
    }
    if(ret != -1)
        ret = 0;
    
    return ret;        
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

