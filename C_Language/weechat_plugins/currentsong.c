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

	weechat_printf (buffer, "TEST DE PLUGIN LAWWWWWWWWWWWWWL");

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
