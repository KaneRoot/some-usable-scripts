#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void lire(char **, char **, char **);
char * lireChaine3();
void changeDirectory(char * path);
int subString (const char *chaine, int debut, int fin, char *result);
void erreur(char *s);
void executionArrierePlan(char *arg1);
void execution(char *arg1, char *arg2, char *arg3);

int main(int argc, char **argv)
{
	int commandeInterne;
	char *arg1, *arg2, *arg3;
	// Boucle principale qui attend les commandes
	while(1)
	{
		printf("[ %s ] %s $ ",(char *) getenv("USER"), (char *) getenv("PWD"));
		arg1 = arg2 = arg3 = NULL;
		commandeInterne = 0;
		lire(&arg1, &arg2, &arg3);

		if(strcmp(arg1, "cd") == 0)
		{
			commandeInterne = 1;
			// On change de répertoire
			changeDirectory(arg2);
		}
		if(strcmp(arg1, "exit") == 0)
		{
			commandeInterne = 1;
			exit(0);
		}
		if(commandeInterne == 0)
		{
			execution(arg1, arg2, arg3);
		}
	}

}
void execution(char *arg1, char *arg2, char *arg3)
{
	int pid;
	if(arg2 != NULL)
	{
		if(strcmp(arg2, "&") == 0)
			executionArrierePlan(arg1);
		if(strcmp(arg2, "<") == 0)
		{
			printf("Commande avec <\n");
		}
				
	}
	else // exécution basique
	{
		if((pid = fork()) == 0)
		{
			execv(arg1, NULL);
			erreur("Soucis au niveau du exec");
			exit(-2);
		}
		else
			waitpid(pid);
	}
}
void changeDirectory(char * path)
{
	if(path == NULL || strcmp(path, "") == 0)
	{
		chdir(getenv("HOME"));
		setenv("PWD", (char *) getenv("HOME"), 1);
	}
	else
	{
		if(chdir(path) != 0) 
			erreur("Impossible de changer de répertoire");
		else
			setenv("PWD", path, 1);
	}
}
void lire(char** arg1, char** arg2, char** arg3) 
{
	char *s;

	s = lireChaine3();

	*arg1 = strtok(s," ");
	*arg2 = strtok((char *)0," ");
	*arg3 = strtok((char *)0," ");
}
char *lireChaine3() 
{
	char *ptr, *ptr1;
	int c;
	int i=0;
	int nb=10;

	ptr=malloc(nb);
	assert(ptr);

	while((c=getchar()) !=  '\n' && c != EOF) 
	{
		if (i==nb-1) 
		{
			ptr1=malloc(nb=nb*2);
			assert(ptr1);
			ptr[i]='\0';
			strcpy(ptr1,ptr);
			free(ptr);
			ptr=ptr1;
		}
		ptr[i]=c;
		i++;
    }
    ptr[i]='\0';

    if(c == EOF && i == 0) 
        ptr = NULL; 
    else
		if (i+1 != nb) 
		{
			ptr1=malloc(i+1);
			assert(ptr1);
			strcpy(ptr1,ptr);
			free(ptr);
			ptr=ptr1;
        }
    return ptr;
}
void erreur(char *s)
{
	perror(s);
}
int subString (const char *chaine, int debut, int fin, char *result)
{
	result[fin+1-debut] = '\0';
	memcpy (result, (char *)chaine+debut, fin+1-debut);
	return (fin+1-debut);
} 
void executionArrierePlan(char *arg1)
{
	int pid;
	int pipefd[2];
	pipe(pipefd);
	if((pid = fork()) == 0)
	{
		if((pid = fork()) == 0)
		{
			close(pipefd[1]);
			int temp, fd0, fd1, fd2, pid;
			if((fd0 = open("/dev/null", O_RDONLY)) == -1) 
			{
				erreur("Ouverture fichier null");
				exit(-2);
			}
			exit(0);
		}
		else
		{
			close(pipefd[0]);
		}
	}
	else
	{
	}
}
