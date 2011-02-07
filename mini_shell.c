#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
}
void lire(char** arg1, char** arg2, char** arg3) 
{
	char *s;

	s = lireChaine3();

	*arg1 = strtok(s," ");
	*arg2 = strtok((char *)0," ");
	*arg3 = strtok((char *)0," ");
}
