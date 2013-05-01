/* Karchnu : <kane.root@gmail.com>
 *
 * currentsong : affiche le morceau que vous écoutez dans le buffer courant
 *
 * Pour l'ajouter : make ; cp song.so ~/.weechat/plugins/
 * Puis dans weechat : /plugin load song.so
 *
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <weechat/weechat-plugin.h>

#define TAILLE_BUFFER_CURRENT_SONG 100
#define TAILLE_OPTIONS 15

WEECHAT_PLUGIN_NAME("currentsong");
WEECHAT_PLUGIN_DESCRIPTION("Affiche la musique en cours en utilisant mpc");
WEECHAT_PLUGIN_AUTHOR("Karchnu <kane.root@gmail.com>");
WEECHAT_PLUGIN_VERSION("0.1");
WEECHAT_PLUGIN_LICENSE("GPL3");

struct t_weechat_plugin *weechat_plugin = NULL;

int cb_currentsong_plugin(void *data, struct t_gui_buffer *buffer, 
		int argc, char **argv, char **argv_eol)
{
	/* pour que le compilateur C soit content */
	(void) data;
	(void) buffer;
	(void) argv;

	int i,status;
	int p[2];
	char **cmd;
	char *song;
	char *affichage;

	song = malloc(TAILLE_BUFFER_CURRENT_SONG * sizeof(char));
	affichage = malloc((TAILLE_BUFFER_CURRENT_SONG + 10) * sizeof(char));

	cmd = (char **) malloc(sizeof(char*) * argc+2);
	for(i = 0 ; i < argc +1 ; i++)
		cmd[i] = malloc(sizeof(char) * TAILLE_OPTIONS);
	cmd[i] = NULL;

	strcpy(cmd[0],"mpc"); // la commande
	strcpy(cmd[1],"current"); // la chanson courante
	if(argc >= 3) {
		if(strcmp("host", argv[1]) == 0) {
			strcpy(cmd[2], "-h");
			strcpy(cmd[3], argv[2]);
		}
	}
	if(argc >= 4) {
		if(strcmp("port", argv[3]) == 0) {
			strcpy(cmd[4], "-p");
			strcpy(cmd[5], argv[4]);
			cmd[6] = NULL;
		}
	}
	sleep(2);

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
	{
		for(i = 0 ; i < TAILLE_BUFFER_CURRENT_SONG ; i++)
			song[i] = '\0';
		snprintf(song, TAILLE_BUFFER_CURRENT_SONG, 
				"%s didn't work !!! Look at the options !",argv[0]);
		snprintf(affichage, TAILLE_BUFFER_CURRENT_SONG, "%s%s",
				weechat_prefix("error"),song);
		weechat_printf(buffer,affichage);
		return WEECHAT_RC_ERROR;
	}
	if(strcmp("",song) == 0)
		snprintf(affichage,TAILLE_BUFFER_CURRENT_SONG, "/me ! ♪");
	else
		snprintf(affichage,TAILLE_BUFFER_CURRENT_SONG, "/me ♪ %s", song);
	
	//snprintf(affichage, TAILLE_BUFFER_CURRENT_SONG, 
	//"/me ♪ %s%s", weechat_color ("_red"), song);
	//weechat_utf8_normalize(affichage, '?');

	weechat_command(buffer,affichage);

	free(song); // :')
	for(i = 0 ; i < argc + 1 ; i++)
		free(cmd[i]);
	free(cmd);
	free(affichage);

	return WEECHAT_RC_OK;
}

int weechat_plugin_init (struct t_weechat_plugin *plugin, 
		int argc, char *argv[])
{
    weechat_plugin = plugin;

    weechat_hook_command ("currentsong",
                          "Affiche le morceau que vous écoutez",
						  "[host <ip|url> [port <port>]]",
						  "si mpd n'est pas en local : [host <ip|url> [port <port>]]",
						  "host %(the_host) port %(the_port)",
                          &cb_currentsong_plugin, NULL);

    return WEECHAT_RC_OK;
}

int weechat_plugin_end (struct t_weechat_plugin *plugin)
{
    /* pour que le compilateur C soit content */
    (void) plugin;

    return WEECHAT_RC_OK;
}
