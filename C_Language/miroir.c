#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// on donne s et t sera le miroir
void miroir ( char *s, char *t); 

int main(int argc, char * argv[])
{
	if ( argc != 2  )
	{
		printf("Usage: %s sentence \n", *argv);
		exit(EXIT_FAILURE);
	}
	char t[strlen(argv[1])];
	miroir(argv[1],t);
	printf("%s :: %s\n",argv[1],t);
	return EXIT_SUCCESS;
}

void miroir ( char *s, char *t)
{
	int i=0, taille = strlen(s);
	t[taille] = '\0';
	taille--;
	while((taille - i) >= 0)
	{
		t[taille-i]=s[i];
		i++;
	}
}
