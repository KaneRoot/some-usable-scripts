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

#define TAILLE_BUFFER 200
char * path2;

void lire(char **, char **, char **);
char * lireChaine3();
void changeDirectory(char * path);
int subString (const char *chaine, int debut, int fin, char *result);
void erreur(char *s);
void executionPipe(char *arg1, char * arg3, char **env);
void execution(char *arg1, char *arg2, char *arg3, char **env);
void quitter(int signal);

int main(int argc, char **argv, char **env)
{
	int commandeInterne;
	char *arg1, *arg2, *arg3;

	signal(SIGHUP, quitter);
	signal(SIGINT, quitter);
	signal(SIGQUIT, quitter);

	int UUID;
	UUID = geteuid();
	// Boucle principale qui attend les commandes
	while(1)
	{
		if(UUID == 0) // Si l'utilisateur est root alors il a droit à son prompt personnalisé
			printf("[ root ] %s # ", (char *) getenv("PWD"));
		else
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
				commandeInterne = 1; // Écrit simplement pour rester cohérent, mais un peu inutile :)
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
		if(strcmp(arg2, "|") == 0)
			executionPipe(arg1, arg3, env);
		else
		{
			if((pid = fork()) == 0)
			{
				int fd0,fd1;
				if(strcmp(arg2, "<") == 0) // On prend arg3 en entrée standard
				{
					if((fd0 = open(arg3, O_RDONLY)) == -1) 
					{
						erreur("Ouverture fichier");
						exit(EXIT_FAILURE);
					}
					close(0); dup(fd0); // Redirection de l'entrée standard
				}
				else if(strcmp(arg2, ">") == 0) // On redirige la sortie vers un fichier (arg3)
				{
					if((fd1 = open(arg3, O_WRONLY | O_CREAT | O_TRUNC , 0666)) == -1)
					{
						erreur("Redirection sortie standard vers fichier");
						exit(EXIT_FAILURE);
					}
					close(1); dup(fd1); // Redirection de la sortie standard
				}
				else if(strcmp(arg2, "&") == 0) // Exécution en arrière plan, on a rien en entrée
				{
					if((fd0 = open("/dev/null", O_RDONLY)) == -1)
					{
						erreur("Ouverture /dev/null");
						exit(EXIT_FAILURE);
					}
					close(0); dup(fd0);
				}
				else // Exécution simple (avec arguments)
				{
					free(options);
					options = malloc(4 * sizeof(char *));
					options[0] = arg1;
					options[1] = arg2;
					options[2] = arg3;
					options[3] = NULL;
				}
				execvpe(arg1, options, env);
				erreur("execvpe n'a pas fonctionné");
				exit(EXIT_FAILURE);
			}
			else
			{
				if(strcmp(arg2, "&") == 0) // Si exécution en arrière plan
				{
					signal(SIGCHLD, SIG_IGN);
				}
				else // Sinon on attend la fin d'exécution du fils
				{
					signal(SIGINT, SIG_IGN);
					waitpid(pid, &status, 0 );
					signal(SIGINT, quitter);

					if(status == EXIT_FAILURE )
						erreur("Soucis avec le fils");
				}
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
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			signal(SIGINT, quitter);
		}
	}
	if(options != NULL) free(options);
	if(arg1 != NULL) free(arg1);
	
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
		{
			erreur("Impossible de changer de répertoire");
		}
		else
		{
			if(path2 == NULL)
				path2 = (char *) malloc(TAILLE_BUFFER * sizeof(char *));

			getcwd(path2, TAILLE_BUFFER);
			setenv("PWD",path2, 1);
		}
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
	char *ptr, *ptr1 = NULL;
	int c;
	int i=0;
	int nb=10;

	ptr = malloc(nb);
	assert(ptr);

	while((c=getchar()) !=  '\n' )
	{
		// Si on envoit EOF (^D) alors on quitte le shell (comme sur les shells qu'on utilise habituellement)
		if(c == EOF)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
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
	ptr1 = NULL;
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
void executionPipe(char *arg1, char *arg3, char **env)
{
	int pid, status;
	if((pid = fork()) == 0)
	{
		int pipefd[2];
		pipe(pipefd);
		int pid2;
		
		char ** options = malloc(sizeof(char *)*3);
		options[0] = arg1;
		options[1] = NULL;

		if((pid2 = fork()) == 0) // Dans le fils : exécution de la première commande
		{
			close(pipefd[0]);
			close(1); dup(pipefd[1]);

			execvpe(arg1, options, env);
			erreur("Soucis avec le exec, option 'PIPE'");
			exit(EXIT_FAILURE);
		}
		else // Le père récupère en entrée la sortie du fils
		{
			close(pipefd[1]);
			close(0); dup(pipefd[0]);

			execvpe(arg3, options, env);
			erreur("Soucis avec le exec, option 'PIPE'");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, quitter);
	}
}
void quitter(int signal)
{
	printf("\nVous avez indiqué le signal avec le numéro : %d\n", signal);
	exit(EXIT_SUCCESS);
}
