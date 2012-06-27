#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void changeDirectory(char * path);
void erreur(char *s);

int main(int argc, char **argv)
{
	changeDirectory("");
	char * wd = (char *) get_current_dir_name();
	printf("Répertoire courant : %s\n", wd);
}

void changeDirectory(char * path)
{
	if(strcmp(path, "") == 0)
		chdir(getenv("HOME"));
	else if(chdir(path) != 0 )
		erreur("Impossible de changer de répertoire");
}
void erreur(char *s)
{
	perror(s);
	exit(-2);
}
