#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int supprimer(char *s, char c);
int main( int argc, char **argv)
{
	int retour;
	char *s = NULL;
	s = (char *) malloc(sizeof(char *) * 30);
	scanf("%29s",s);
	
	retour = supprimer(s,'C');
	printf("%s\n",s);

	free(s);

	exit(EXIT_SUCCESS);
}

int supprimer(char *s, char c)
{
	if(s == NULL) return -1;

	int i = 0;
	int k = 0;
	int taille = strlen(s);
	int taille2 = taille;
	while(i < taille)
	{
		if( *(s+i) == c)
		{
			k = i;
			while(k < taille) 
			{
				s[k] = s[k+1];
				k++;
			}

			if( i == taille -1)
				*(s + i) = '\0';
			i--; taille--;
		}
		i++;
	}

	while(taille < taille2)
	{
		s[taille] = '\0';
		taille++;
	}
	return(EXIT_SUCCESS);
}
