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
#include "consommateur.h"
#include "types.h"
#include "sema.h"
#include "constantes.h"

int main( int argc, char **argv)
{

	int shmid, shm_key;
	int mutex_data, mutex_tpa;
	key_t sem_key_data;
	key_t sem_key_tpa;

	if(argc < 2) { printf("Usage : %s nSHM \n", argv[0]); exit(EXIT_FAILURE); }

	shm_key = (key_t) atoi(argv[1]);
	sem_key_tpa = MUTEX_TPA;
	sem_key_data = MUTEX_DATA;

	MEMP * memoireP;

	if((shmid = shmget(shm_key, sizeof(MEMP), IPC_CREAT|IPC_EXCL|0766)) == -1) 
	{ perror("shmget"); exit(EXIT_FAILURE);}
	
	if((memoireP = (MEMP *) shmat(shmid, 0 , 0766)) == (void *) -1)
	{ perror("shmat"); exit(EXIT_FAILURE); }
		
	if((mutex_data = creat_sem( sem_key_data, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }

	if((mutex_tpa = creat_sem( sem_key_tpa, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }

	P(mutex_data);
	
		memoireP->tete = 0;
		memoireP->queue = 0;
	V(mutex_data);
		
	P(mutex_tpa);
		for(int i = 0; i < MAX_PROD ; i++)
			memoireP->tpa[i] = -1;
	V(mutex_tpa);


	sleep(10);

	if(shmctl(shmid, IPC_RMID, 0) < 0)
	{ perror("shmctl"); exit(EXIT_FAILURE); }
		
	if(mutex_data >= 0) { del_sem(sem_key_data); }
	if(mutex_tpa >= 0) { del_sem(sem_key_tpa); }

	exit(EXIT_SUCCESS);
}

