#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/sem.h>
#include "consommateur.h"
#include "types.h"
#include "sema.h"
#include "constantes.h"

int main( int argc, char **argv)
{

	if(argc < 2) { printf("Usage : %s numIPC\n", argv[0]); exit(EXIT_FAILURE); }

	key_t clef = (key_t) atoi(argv[1]);

	MEMP memoireP;
	memoireP.tete = 0;
	memoireP.queue = 0;

	int semid;
	semid = creat_sem( clef, MAX_PROD);
	if(semid >= 0)
	{

		sleep(10);
		del_sem(clef);
	}

	exit(EXIT_SUCCESS);
}

