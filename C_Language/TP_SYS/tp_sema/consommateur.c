#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constantes.h"
#include "types.h"

int main( int argc, char **argv)
{

	if(argc < 2) { printf("Usage : %s numIPC\n"); exit(EXIT_FAILURE); }

	int clef = atoi(argv[1]);

	exit(EXIT_SUCCESS);
}

