#include <stdio.h>
#include <string.h>

int lirechl(char *s, int n);
void squeeze( char *s , char *t, char c);

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

int main()
{
	char string[10];
	printf("Écrivez puis appuyez sur 'Entrée' : ");
	int nb = lirechl(&string[0], 7);
	printf("Nombre de caracteres jusqu'à saut de ligne : %d \n",nb);
}

// This is for another exercise.
void squeeze( char *s , char *t, char c)
{	
	int i = 0;
	int k = 0;
	while( s[i] != '\n' && s[i] != '\0' )
	{
		if (s[i] != c && k < strlen(t))
		{
			t[k] = s[i];
			k++;
		}
		i++;
	}
	t[k]='\0';
}
