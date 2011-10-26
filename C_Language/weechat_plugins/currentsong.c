#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <weechat/weechat-plugin.h>

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
	char * cmd[] = { "mpc", "-h" , "192.168.0.100",(char *)0 };
	song = malloc(200*sizeof(char));
	if(song == NULL) return WEECHAT_RC_ERROR;

	pipe(p);
	if(fork() == 0)
	{
		close(p[0]);
		close(0); close(2);
		dup2(p[1],1);
		execvp("mpc", cmd);
	}

	close(p[1]);
	read(p[0], song, 200);
	close(p[0]);

	if(buffer)
		weechat_printf (buffer, "J'écoute : %s %s",
				weechat_color ("yellow,red"),
				song);
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
