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
	int shmid; 
	int shm_key = atoi(argv[1]);
	if(shm_key == -1) { printf("Usage %s numIPC message\n", argv[0]); exit(EXIT_FAILURE); }

/* création ou lien avec une memoireP partagée */
	shmid = shmget(shm_key, 100, 0700 | IPC_CREAT); 
	if (shmid == -1) { perror("shmget"); return (EXIT_FAILURE); }

/* montage en mémoire */
	memoireP = shmat(shmid, NULL, 0);

/* utilisation */
//	printf("memoireP[0] = %d\n", memoireP[0]++ );

	return (EXIT_SUCCESS); 

}
