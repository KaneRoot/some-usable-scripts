#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include "constantes.h"
#include "sema.h"

int main( int argc, char **argv)
{
	if(argc < 3) { printf("Usage %s numIPC message\n", argv[0]); exit(EXIT_FAILURE); }
	int *zone; 
	int memid; 
	int clef = atoi(argv[1]);
	if(clef == -1) { printf("Usage %s numIPC message\n", argv[0]); exit(EXIT_FAILURE); }

/* création ou lien avec une zone partagée */
	memid = shmget(clef, 100, 0700 | IPC_CREAT); 
	if (memid == -1) { perror("shmget"); return (EXIT_FAILURE); }

/* montage en mémoire */
	zone = shmat(memid, NULL, 0);

/* utilisation */
	printf("zone[0] = %d\n", zone[0]++ );

	return (EXIT_SUCCESS); 

}
