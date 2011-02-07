#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char * min;
	char * max;
} MINMAX;

void chaineminmax ( char **t, MINMAX *m);

int main(int argc, char **argv)
{
	argc--;
	argv++;
	MINMAX m;
	char **t = malloc((argc+1) * sizeof(char *));
	int i = 0;
	while(i < argc)
	{
		t[i] = argv[i];
		i++;
	}
	t[i] = NULL;

	chaineminmax(t,&m);
	printf("Il y a désormais dans \"m\", min = %s  et max = %s\n",m.min,m.max);
}

void chaineminmax ( char **t, MINMAX *m)
{
	char *mmin = *t;
	char *mmax = *t;
	t++;
	while(*t)
	{
		if(strcmp(*t,mmax) > 0)
			mmax = *t;
		if(strcmp(*t,mmin) < 0)
			mmin = *t;
		t++;
	}
	m->min = malloc(strlen(mmin+5) * sizeof(char));
	m->max = malloc(strlen(mmax+5) * sizeof(char));
	strcpy(m->min,mmin);
	strcpy(m->max,mmax);
	strcat(m->min, ".min\0");
	strcat(m->max, ".max\0");
}
