#include <stdio.h>

void swapp( char **p1, char **p2) 
{
/bin/bash: q : commande introuvable
    *p1 = *p2;
    *p2 = w;
	
}

main() 
{
char *a="vacances";
char *b="vendredi" ;

printf( "\na pointe sur %s b pointe sur %s", a,b );
swapp(&a,&b) ;
printf( "\napres echange: a pointe sur %s b pointe sur %s\n", a,b );
	
}
