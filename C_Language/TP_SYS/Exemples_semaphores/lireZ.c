/* Mecanismes de communication entre processus - IPC */
/* Lecture d'une zone de mémoire partagée */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMEM_SIZE 256
#define SHMEM_RIGHTS 0x01ff

int main(int argc, char ** argv){
  	long * ptz ;
  	int ipc_result, ipc_key ;
  	
	if (argc<2) 
		exit(1) ;
  	ipc_key = atoi(argv[1]) ;
  	ipc_result = shmget(ipc_key, 0 , 0) ;
  	ptz = (long *) shmat(ipc_result,0,SHMEM_RIGHTS) ;
  
  	printf("\n Valeur dans la zone partagee : %d \n\n", *ptz) ;
  	exit(0) ;
 } 





