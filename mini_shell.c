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

int main(int argc, char **argv)
{
	char **arg1, **arg2, **arg3;
	lire(arg1, arg2, arg3);

	if(strcmp(*arg1, "cd") == 0)
	{
		// On change de répertoire
		changeDirectory(*arg2);
	}
	

}
void changeDirectory(char * path)
{
	if(strcmp(path, "") == 0)
		chdir(getenv("HOME"));
	else if(chdir(path) != 0 )
		erreur("Impossible de changer de répertoire");
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
	exit(-2);
}
int subString (const char *chaine, int debut, int fin, char *result)
{
	result[fin+1-debut] = '\0';
	memcpy (result, (char *)chaine+debut, fin+1-debut);
	return (fin+1-debut);
} 
