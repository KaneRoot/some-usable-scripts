#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
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
void executionArrierePlan(char *arg1, char **env);
void execution(char *arg1, char *arg2, char *arg3, char **env);
void quitter(int signal);

int main(int argc, char **argv, char **env)
{
	int commandeInterne;
	char *arg1, *arg2, *arg3;

	signal(SIGHUP, quitter);
	signal(SIGINT, quitter);
	signal(SIGQUIT, quitter);

	// Boucle principale qui attend les commandes
	while(1)
	{
		printf("[ %s ] %s $ ",(char *) getenv("USER"), (char *) getenv("PWD"));
		arg1 = arg2 = arg3 = NULL;
		commandeInterne = 0;
		lire(&arg1, &arg2, &arg3);

		if(arg1 != NULL)
		{
			if(strcmp(arg1, "cd") == 0)
			{
				commandeInterne = 1;
				// On change de répertoire
				changeDirectory(arg2);
			}
			if(strcmp(arg1, "exit") == 0)
			{
				commandeInterne = 1;
				exit(EXIT_SUCCESS);
			}
			if(commandeInterne == 0)
			{
				execution(arg1, arg2, arg3, env);
			}
		}
	}

}
void execution(char *arg1, char *arg2, char *arg3, char **env)
{
	int pid;
	char ** options = malloc(sizeof(char *)*3);
	options[0] = arg1;
	options[1] = NULL;
	int status;

	if(arg2 != NULL)
	{
		if(strcmp(arg2, "&") == 0)
			executionArrierePlan(arg1, env);
		else
		{
			if((pid = fork()) == 0)
			{
				int fd0,fd1;
				if(strcmp(arg2, "<") == 0)
				{
					if((fd0 = open(arg3, O_RDONLY)) == -1) 
					{
						erreur("Ouverture fichier");
						exit(EXIT_FAILURE);
					}
					close(0); dup(fd0); // Redirection de l'entrée standard
				}
				if(strcmp(arg2, ">") == 0)
				{
					if((fd1 = open(arg3, O_WRONLY | O_CREAT | O_TRUNC , 0666)) == -1)
					{
						erreur("Redirection sortie standard vers fichier");
						exit(EXIT_FAILURE);
					}
					close(1); dup(fd1);
				}
				execvpe(arg1, options, env);
				erreur("execvpe n'a pas fonctionné");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0 );
				if(status != 0)
					erreur("Soucis avec le fils");
			}
		}

	}
				
	else // exécution basique
	{
		if((pid = fork()) == 0)
		{
			execvpe(arg1, options, env);
			erreur("Soucis au niveau du exec");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
	free(options);
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
		DIR * repertoire = opendir(path); // A REPRENDRE
		struct dirent * rep = readdir(repertoire);
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
void executionArrierePlan(char *arg1, char **env)
{
	int pid;
	if((pid = fork()) == 0)
	{
		int pipefd[2];
		pipe(pipefd);
		int fd0, fd2;

		if((fd0 = open("/dev/null", O_RDONLY)) == -1) 
		{
			erreur("Ouverture fichier null");
			exit(EXIT_FAILURE);
		}
		if((fd2 = open("nohup.err", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1 ) 
		{
			erreur("Ouverture fichier nohup.err");
			exit(EXIT_FAILURE);
		}
		
		close(0); dup(fd0);
		close(2); dup(fd2);

		if((pid = fork()) == 0)
		{
			close(pipefd[1]);
			int temp, fd00, fd01, fd02, pid;
			if((fd00 = open("/dev/null", O_RDONLY)) == -1) 
			{
				erreur("Ouverture fichier null");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
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
void quitter(int signal)
{
	printf("\nVous avez indiqué le signal avec le numéro : %d\n", signal);
	exit(EXIT_SUCCESS);
}
