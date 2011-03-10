/* Mecanismes de communication entre processus - IPC */
/* Creation d'une zone de m�moire interne partaj�e (shared memory - shm ) */
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMEM_SIZE 256		
#define SHMEM_RIGHTS 0x01ff

/* dimension de la zone : 255 octets */
/* droits d'acc�s dans la zone de m�more partag�e: 1ff */
/* on nn'utilisera que le premier entier long pour l'exemple */


int main (int argc, char ** argv) {

	/* l'identificateur externe (key) de la zone de m�moire  partag�e 
	est un nombre entier transmis en param�tre par l'utilisateur  */

 	int ipc_key ;
	
	int ipc_result ;
  	char * pnl ;
  	int i;
  
  	if (argc<2) 
		exit(1);
  	
	ipc_key = atoi(argv[1]) ;
  
	/* creation de la zone commune : primitive shmget (....) */
  
  	ipc_result = shmget(ipc_key, SHMEM_SIZE, IPC_CREAT|IPC_EXCL|SHMEM_RIGHTS) ;

  	if (ipc_result != -1) {
    		printf(" - Succes !! -\n");
       
		/* attachement � la zone de m�moire partag�e : shmat (....) */ 

		pnl = (char*)shmat(ipc_result, 0, SHMEM_RIGHTS) ;
      
		/* initialisation avec 0 de la zone de m�moire partag�e */
		for (i=0;i<SHMEM_SIZE;i++)
       			pnl[i]='\0' ; 
  	}
  	else
      		printf(" Erreur  :%d \n",ipc_result); 

  	exit(0) ; 
}
                                   
