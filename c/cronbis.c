#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main( int argc, char **argv)
{
	if(argc < 3) { fprintf(stdout, "Usage : %s NBSEC COMMANDE\n", argv[0]); exit(EXIT_FAILURE); }

	int NBSEC;
	NBSEC = atoi(argv[1]);
	int pid;
	int fd0;

	while(1)
	{
		if((pid = fork()) == 0)
		{
			char ** options = malloc(sizeof(char *)*(argc-2));
	
			for(int i = 0; i < (argc -2) ; i++)
				options[i] = *argv[i+2];
	
	
			if((fd0 = open("/dev/null", O_RDONLY)) == -1)
			{
				erreur("Ouverture /dev/null");
				exit(EXIT_FAILURE);
			}
			close(0); dup(fd0);

			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid);
			sleep(NBSEC);
		}
	}
	exit(EXIT_SUCCESS);
}

