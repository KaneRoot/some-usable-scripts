#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int main( int argc, char **argv)
{
// register ne sert plus de nos jours
	register nflg;
	nflg = 0;
// Le flag "n" sert à rajouter un saut de ligne
	argv++;
	if ( argc > 1 && **argv == '-' && argv[0][1] == 'n')
	{
		nflg++;
		argv++;
	}
	while(argv[0] != NULL)
	{
		fputs (*(argv), stdout);
		putchar(' ');
		argv++;
	}
	if ( nflg == 0 )
		putchar('\n');

	exit(0);
}
