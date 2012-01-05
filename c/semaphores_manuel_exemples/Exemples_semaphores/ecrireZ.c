/* Mecanismes de communication entre processus - IPC */
/* Ecriture dans une zone de mémoire partajée  */


#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMEM_SIZE 0xff
#define SHMEM_RIGHTS 0x01ff

int main (int argc, char ** argv) {
  	long i , k  , temp;
  	long * ptz ;
  	int p1 , p2, p3, p4;
  	int ipc_key, ipc_result ;
  
  	if (argc<2) 
		exit(1) ;

  	ipc_key = atoi(argv[1]) ;

	srand ( time(0) );  // initialisation générateur 
  
  	ipc_result = shmget(ipc_key, 0 , 0) ;   // ouverture mémoire partagée

  	ptz = (long *) shmat(ipc_result, 0, SHMEM_RIGHTS) ; // attachement

  	if ((p1 = fork()) == 0) {
		for(i=0;i<10;i++) { 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;
		}
		exit(0) ;
	}	

//	while(wait(0) != p1);

  	if ((p2 = fork()) == 0) {
		for(i=0;i<10;i++) { 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;		
		}
		exit(0) ;
	}	

//	while(wait(0) != p2);

  	if ((p3 = fork()) == 0) {
		for(i=0;i<10;i++) { 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;
		}
		exit(0) ;
	}	
  	
//	 while(wait(0) != p3);

  	if ((p4 = fork()) == 0) {
		for(i=0;i<10;i++) { 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;
		}
		exit(0) ;
	}	
	
 
 	printf("\n Arret processus pid = %d   compteur = ( %d )\n\n", getpid(), *ptz) ;

 
 	exit(0) ;
}
