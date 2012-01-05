/* Mecanismes de communication entre processus - IPC */
/* Ecriture dans une zone de mémoire partajée (shared memory - shm ) */

//         VERSION AVEC SEMAPHORE 

#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMEM_SIZE 0xff
#define SHMEM_RIGHTS 0x01ff

void erreur(char *mess);

int main (int argc, char ** argv) {
  	long i , k  , temp;
  	long * ptz ;
  	int p1 , p2, p3, p4;
  	int ipc_key, ipc_result ;
  
	int mutex;    // id du semaphore


  	if (argc<2) 
		exit(1) ;
  	ipc_key = atoi(argv[1]) ;
  
  
  	ipc_result = shmget(ipc_key, 0 , 0) ; 	// ouverture mémoire partagée
  	ptz = (long *) shmat(ipc_result, 0, SHMEM_RIGHTS) ; // attachement mémoire partagée

	// creation du semaphore mutex
	
	if((mutex = creat_sem(ipc_key+1,1)) == -1)
		erreur("erreur creation semaphore");
	
  	if ((p1 = fork()) == 0) {
		for(i=0;i<10;i++) { 

			P(mutex); //__________________________

    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp; ; 

			V(mutex); //________________________________
			
    			//(*ptz) ++ ;
		}
		exit(0) ;
	}	

  	if ((p2 = fork()) == 0) {
		for(i=0;i<10;i++) { 

		  	P(mutex); //__________________________

    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;
			 
			V(mutex); //________________________________
			 
		}
		exit(0) ;
	}	

  	if ((p3 = fork()) == 0) {
		for(i=0;i<10;i++) { 

		 	P(mutex); //__________________________
			 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp;
    		
		 	V(mutex); //________________________________

			//(*ptz) ++ ;
		}
		exit(0) ;
	}	

  	if ((p4 = fork()) == 0) {
		for(i=0;i<10;i++) { 

		 	P(mutex); //__________________________
			 
    			temp = * ptz;
			temp++;
			sleep( rand() % 2 );	// attente aléatoire
			*ptz = temp; ; 
    			//(*ptz) ++ ;
			
			V(mutex); //________________________________
		}
		exit(0) ;
	}	

	// while(wait(0) != -1);  si le père attend que tous ses fils soient terminés

	// suppression du semaphore
	
	//del_sem(mutex);

 	printf("\n Arret processus pid = %d  compteur ( %d ) \n\n", getpid(), *ptz) ;
 
 	exit(0) ;
}
