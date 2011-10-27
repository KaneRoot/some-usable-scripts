#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// lire un nombre de caractères donné par n
int lirechl(char *s, int n); 
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s number\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	int n = atoi(argv[1]);
	char * s = malloc(sizeof(char) * n + 1);
	int i = 0;
	i = lirechl(s,n);
	printf("read : %d char, sentence : %s \n",i , s);

	return EXIT_SUCCESS;
}

int lirechl(char *s, int n)
{
	int i, c;
	i=0;
	while( i < n && ( c = getchar() ) != '\n' )
		s[i++] = c ;

	s[i] = '\0';

	if ( c != '\n' )
		while ( getchar() != '\n' );

	return i;
}
