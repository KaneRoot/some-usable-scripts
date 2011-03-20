#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include "constantes.h"
#include "types.h"
#include "sema.h"

int main( int argc, char **argv)
{
	if(argc < 2) { printf("Usage %s numIPC\n", argv[0]); exit(EXIT_FAILURE); }
	MEMP *memoireP; 
	int mutex_data, mutex_tpa;
	key_t sem_key_data;
	key_t sem_key_tpa;
	int shmid; 
	int shm_key = atoi(argv[1]);

/* création ou lien avec une memoireP partagée */
	shmid = shmget(shm_key, sizeof(MEMP), 0766 | IPC_CREAT); 
	if (shmid == -1) { perror("shmget"); return (EXIT_FAILURE); }

	if((memoireP = (MEMP *) shmat(shmid, 0 , 0766)) == (void *) -1)
	{ perror("shmat"); exit(EXIT_FAILURE); }
		
	if((mutex_data = creat_sem( sem_key_data, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }

	if((mutex_tpa = creat_sem( sem_key_tpa, 1)) == -1)
	{ perror("creat_sem"); exit(EXIT_FAILURE); }


		P(mutex_data);
		
		V(mutex_data);
	
/* utilisation */
//	printf("memoireP[0] = %d\n", memoireP[0]++ );

	return (EXIT_SUCCESS); 

}
