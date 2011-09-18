#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	// Options simples
	char * liste_options = "s:e:ol";
	int option;

	opterr = 0; // Pas de message d'erreur
	
	while((option = getopt(argc,argv,liste_options)) != -1)
	{
		switch(option)
		{
			case 's':
				fprintf(stdout,"option s %s\n",optarg);
				break;
			case 'e':
				fprintf(stdout,"option e %s\n",optarg);
				break;
			case 'o':
			case 'l':
				fprintf(stdout,"option %c",option);
				break;
			case '?':
				fprintf(stdout,"erreur : %s\n",optopt);
				break;
		}
	}
	// s'il reste des options
	if(argc != optind)
	{
		fprintf(stdout, "Arguments restants : \n");
		while(optind != argc)
			fprintf(stdout, " %s \n", argv[optind++]);
	}
	return EXIT_SUCCESS;
}

