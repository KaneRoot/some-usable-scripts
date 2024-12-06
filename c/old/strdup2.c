// strdupAvecBug !!

#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *strdup2(char *) ; // prototype

main()
{
   char *t1 = "hello how are you ?" ;
   char t2[20] ;
   char *r ;
   
   strcpy(t2, "TORTUE") ;
   
   r = (char *) strdup(t1) ; // appel à la fonction existante
   printf( "%s\n ", r );
   printf( "%d\n ", strlen(r) );
   
   r = ( char *) strdup(t2) ;
   printf( "%s\n ", r );
   printf( "%d\n ", strlen(r) );
   
   // =========================
   // and now the same thing with personal function strdup2 !!
   
   printf( "%s\n ", "Resultats avec STRDUP2" );
   r = strdup2(t1) ; 
   printf( "%s\n ", r );
   printf( "%d\n ", strlen(r) );
   
   r = strdup2(t2) ;
   printf( "%s\n ", r );
   printf( "%d\n ", strlen(r) );
   
}

char *strdup2(char *s)
{
    char *r ;
	int n = strlen(s);
    r = (char* )malloc( (n + 1) * sizeof(char) );
	while(*s)
	{
		*r = *s ;
		r++;
		s++;
	}		
	*r='\0';
	return r-n;
}
