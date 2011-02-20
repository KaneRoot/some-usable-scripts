#include <stdio.h>

int lirech1( char* s, int n )
{
	int i, c;
	
	i = 0;
	
	while ( i < n && ( c = getchar() ) != '\n' )
		s[i++] = c;
	
	s[i] = '\0';
	
	if ( c != '\n' )
		while ( getchar() != '\n' );
		
	return i;
}

void miroir( char *s, char *t) 
{

/* A VOUS !
regardez la version miroir2 MAIS ...
obligation d'employer les notations POINTEURS (t++,s++ ou s--, *t, *s)


*/
}

/* miroir, avec notation "classique" t[i]
void miroir2( char *s, char *t) 
{
    int l,i;
    l= strlen(t);
    for (i=0; i<l; i++)
        s[i] = t[l-i-1] ;
    s[l] = '\0' ;
}
*/

main()
{
	char a[21], b[21];
	lirech1( a, 20 );
	printf( "\nchaine originale : %s\n", a );
	miroir( b, a );
	printf( "\nchaine miroir    : %s\n", b );
}
