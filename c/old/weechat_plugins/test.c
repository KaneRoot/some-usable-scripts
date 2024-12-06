#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 5
#define TAILLE_CHAINE 20
#define TAILLE_BUFFER_CURRENT_SONG 200
#define TAILLE_OPTIONS 20

int main(int argc, char * argv[])
{
	int i,status;
	int p[2];
	char ** cmd;
	char * song;
	char * affichage;
	cmd = (char **) malloc(sizeof(char*) * argc+1);
	if(argc > 3) argc = 3;
	for(i = 0 ; i < argc + 2 ; i++)
		cmd[i] = malloc(sizeof(char*) * TAILLE_OPTIONS);
	free(cmd[i-1]);
	cmd[i-1] = (char *)0;
	strcpy(cmd[0],"mpc");
	strcpy(cmd[i-2],"current");
	if(argc == 3)
	{
		strcpy(cmd[1],"-h");
		strcpy(cmd[2],argv[2]);
	}

	song = malloc(TAILLE_BUFFER_CURRENT_SONG*sizeof(char));
	affichage = malloc((TAILLE_BUFFER_CURRENT_SONG + 10) * sizeof(char));

	for(i = 0 ; i < TAILLE_BUFFER_CURRENT_SONG ; i++)
		song[i] = '\0';
	for(i = 0 ; i < TAILLE_BUFFER_CURRENT_SONG + 10 ; i++)
		affichage[i] = '\0';

	pipe(p);
	if(fork() == 0)
	{
		close(p[0]);
		close(0); close(2);
		dup2(p[1],1);
		execvp("mpc", cmd);
	}
	close(p[1]);
	read(p[0], song, TAILLE_BUFFER_CURRENT_SONG);
	close(p[0]);
	wait(&status);
	if(WEXITSTATUS(status) != 0)
		sprintf(song,"didn't worked !!!");
	sprintf(affichage,"/me ♪ %s", song);
	
	//sprintf(affichage,"/me ♪ %s%s", weechat_color ("_red"), song); // Ne s'affiche pas correctement chez les autres
	//weechat_utf8_normalize(affichage, '?'); // Pour ne pas avoir de caractères non-lisibles

	printf("AFFICHAGE : %s\n",affichage);
	free(song); // :')
	for(i = 0 ; i < argc ; i++)
		free(cmd[i]);
	free(cmd);

	return EXIT_SUCCESS;
}

