#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * strdup2(char *);
int main(int argc, char **argv)
{
	char * chaine1 = "Coucou c'est moi";
	char * copie = strdup2(chaine1);
	printf("Chaîne originale : %s \nChaîne copie : %s\n", chaine1, copie);
	exit(0);
}
char * strdup2(char * t)
{
	char *s, *save;
	save = s = malloc((strlen(t) + 1)* sizeof(char));
	while(*s++ = *t++);

	return save;
}
