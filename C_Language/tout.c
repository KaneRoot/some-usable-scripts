#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void miroir ( char *s, char *t); // on donne s et t sera le miroir
void squeeze( char *s , char *t, char c); // on donne s et t sera la chaine sans le caractère c
int lirechl(char *s, int n); // lire un nombre de caractères donné par n
int palindrome(char *); // 1 si vrai 0 sinon
void minuscule(char *); // met en minuscule la chaîne
int main(int argc, char **argv)
{
	if ( argc != 2  )
	{
		printf("Usage: %s sentence \n", *argv);
		exit(2);
	}
	char *s = argv[1];
	char t[strlen(s)];
	miroir(s,t);
	printf("%s :: %s\n",s,t);

	int rep = palindrome(s);
	if(rep==1)
		printf("Cette phrase est un palindrome\n");
	else
		printf("Cette phrase n'est pas un palindrome\n");
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
int palindrome(char *s)
{
	int i=0,res = 1;
	char t[strlen(s)];
	squeeze(s,t,' ');
	minuscule(t);
	while(i<strlen(t))
	{
		if(t[i]!=t[strlen(t)-i-1])
			res=0;
		i++;
	}
	return res;
}
void squeeze( char *s , char *t, char c)
{	
	while(*s)
	{
		if( *s != c)
		{
			*t = *s;
			t++;
		}
		s++;
	}
	*t = '\0';
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
void minuscule(char * s)
{	
	while(*s++ && (*s = tolower(*s)));
}
