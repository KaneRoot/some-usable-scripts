#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// met en minuscule la chaîne
void minuscule(char *); 

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Usage : %s SenTeNCe\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char * s = malloc(sizeof(char) * strlen(argv[1]));
	s = strcpy(s,argv[1]);
	minuscule(s);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}

void minuscule(char * s)
{	
	while(*s++ && (*s = tolower(*s)));
}
