#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main( int argc, char **argv, char **env)
{
	if(argc < 3) { fprintf(stdout, "Usage : %s NBSEC COMMANDE\n", argv[0]); exit(EXIT_FAILURE); }

	int NBSEC;
	NBSEC = atoi(argv[1]);
	int pid,status;
	int fd0;
	int i;

	while(1)
	{
		if((pid = fork()) == 0)
		{
			// + 1 pour stocker NULL à la fin
			char ** options = (char **) malloc(sizeof(char **)*(argc-2 +1));
	
			for(i = 0; i < (argc -2) ; i++)
				options[i] = argv[i+2];
			options[i] = NULL;
	
			if((fd0 = open("/dev/null", O_RDONLY)) == -1)
			{
				printf("Ouverture /dev/null");
				exit(EXIT_FAILURE);
			}
			close(0); dup(fd0);

			execvpe(argv[2],options,env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid,&status,0);
			sleep(NBSEC);
		}
	}
	exit(EXIT_SUCCESS);
}

