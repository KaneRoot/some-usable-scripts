#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int main( int argc, char **argv)
{
// register is a bit useless nowadays
	register int i, nflg;
	nflg = 0;
// Le flag "n" sert à rajouter un saut de ligne

	if ( argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n')
	{
		nflg++;
		argc--;
		argv++;
	}
	for(i = 1 ; i < argc ; i++)
	{
		fputs (argv[i], stdout);
		if ( i < argc - 1 )
			putchar(' ');
	}
	if ( nflg == 0 )
		putchar('\n');

	exit(0);
}

