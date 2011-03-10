/* Mecanismes de communication entre processus - IPC */
/* 
/* met a zero  l' entier long de la mem par*/
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMEM_RIGHTS 0x01ff

/* droits d'accès dans la zone de mémore partgée: 1ff */


int main (int argc, char ** argv) {

	/* l'identificateur externe (key) de la zone de mémoire  partagée 
	est un nombre entier transmis en paramètre par l'utilisateur  */
 	int ipc_key ;
	
	int ipc_result ;
  	long *ptz;
  	int i;
  
  	if (argc<2) 
		exit(1);
  	
	ipc_key = atoi(argv[1]) ;
  
  	ipc_result = shmget(ipc_key, 0,0);

  	if (ipc_result != -1) 
	{
    		printf(" - Succes !! -\n");
	 	ptz = (long *) shmat(ipc_result, 0, SHMEM_RIGHTS) ;
		printf("remise a zero ( %ld ) ", *ptz);
		*ptz = 0;
	}
  	else
      		printf(" Erreur  :%d \n",ipc_result); 
  	exit(0) ; 
}
                                   
