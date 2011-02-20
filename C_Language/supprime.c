// THIS DOESN'T WORK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void supprime(char *s, char c);
int main(int argc, char **argv)
{
	char * chaine = "Salut tout le monde";
	char c = 'u';
	supprime(chaine, c);
	printf("%s\t\t%c\n", chaine, c);
	exit(0);
}

void supprime(char *s, char c)
{
	char * save = s;
	while(*s)
	{
		if(*s == c)
		{
			printf("On a une correspondance\n");
			while(*s && *(s + 1) != '\0')
			{
				*s = *(s + 1);
				s++;
			}
			printf("Fin de la boucle : %s", s);
			*s = '\0';
			s = save;
		}
		else
		{
			s++;
		}
		save = s;
	}
}
