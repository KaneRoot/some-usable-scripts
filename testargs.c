#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main( int argc, char **argv, char ** envp)
{
	while(*envp != NULL)
	{
		if(strstr(*envp, "GDMSESSION") != NULL)
			printf("%s\n", *envp);
		*envp++;
	}
}

