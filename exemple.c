#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int multiple(int, int);

int main( int argc, char **argv)
{
	if(argc < 3)
	{	perror("Usage : ./truc.out nombre nombre\n"); return 1;	}

	int var1 = atoi(argv[1]);
	int var2 = atoi(argv[2]);

	int truc = multiple(var1,var2);

	printf("Mon multiple : %d %s \n", truc, "Salut !");
	return 0;
}

int multiple(int a, int b)
{
	return a * b;
}
