#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <weechat/weechat-plugin.h>

#define TAILLE_BUFFER_CURRENT_SONG 100
WEECHAT_PLUGIN_NAME("currentsong");
WEECHAT_PLUGIN_DESCRIPTION("Affiche la musique en cours en utilisant mpc");
WEECHAT_PLUGIN_AUTHOR("Karchnu <kane.root@gmail.com>");
WEECHAT_PLUGIN_VERSION("0.1");
WEECHAT_PLUGIN_LICENSE("GPL3");

struct t_weechat_plugin *weechat_plugin = NULL;

int cb_currentsong_plugin(void *data, struct t_gui_buffer *buffer, int argc, char **argv, char **argv_eol)
{
	/* pour que le compilateur C soit content */
	(void) data;
	(void) buffer;
	(void) argv;

	int p[2];
	//char local_buffer[100];
	char * song;
	char affichage[TAILLE_BUFFER_CURRENT_SONG + 10];
	int i;
	char * cmd[] = { "mpc", "-h" , "192.168.0.100","current", (char *)0 };
	song = malloc(TAILLE_BUFFER_CURRENT_SONG*sizeof(char));
	if(song == NULL) return WEECHAT_RC_ERROR;

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
	sprintf(affichage,"/me ♪ %s", song);
	//sprintf(affichage,"/me ♪ %s%s", weechat_color ("_red"), song); // Ne s'affiche pas correctement chez les autres
	weechat_utf8_normalize(affichage, '?'); // Pour ne pas avoir de caractères non-lisibles
	weechat_command(buffer,affichage);
	free(song);

	return WEECHAT_RC_OK;
}

int weechat_plugin_init (struct t_weechat_plugin *plugin, int argc, char *argv[])
{
    weechat_plugin = plugin;

    weechat_hook_command ("currentsong",
                          "Affiche la chanson que vous écoutez",
						  "noargs",
						  "no arguments",
						  NULL,
                          &cb_currentsong_plugin, NULL);

    return WEECHAT_RC_OK;
}

int weechat_plugin_end (struct t_weechat_plugin *plugin)
{
    /* pour que le compilateur C soit content */
    (void) plugin;

    return WEECHAT_RC_OK;
}
