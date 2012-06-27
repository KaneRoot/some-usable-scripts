#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv, char **envp)
{
	// I will display all the environment variables
	while(*envp != NULL)
	{
		printf("%s\n", *envp);
		*envp++;
	}
}

