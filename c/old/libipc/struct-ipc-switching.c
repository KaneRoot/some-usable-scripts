#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ipc.h>

#define NTAB(t)     ((int) (sizeof (t) / sizeof (t)[0]))

struct ipc_connection_info *srv = NULL;
struct ipc_connection_infos *clients = NULL;

struct ipc_switching * TCP_TO_IPC;
struct ipc_switching * IPC_TO_TCP;

// void ipc_switching_add (struct ipc_switchings *is, int orig, int dest);
// int ipc_switching_del (struct ipc_switchings *is, int orig);
// int ipc_switching_get (struct ipc_switchings *is, int orig);
// void ipc_switching_print (struct ipc_switchings *is);

int main(int argc, char * argv[])
{
	argc = argc;
	argv = argv;
	
	struct ipc_switchings TCP_TO_IPC;
	memset (&TCP_TO_IPC, 0, sizeof(struct ipc_switchings));
	TCP_TO_IPC.collection = malloc(sizeof(struct ipc_switching));

	ipc_switching_add (&TCP_TO_IPC, 1, 2);
	ipc_switching_add (&TCP_TO_IPC, 5, 6);
	ipc_switching_print(&TCP_TO_IPC);

	int ret;

	ret = ipc_switching_get (&TCP_TO_IPC, 1);
	printf ("ret ipc_switching_get 1 : %d\n", ret);
	ret = ipc_switching_get (&TCP_TO_IPC, 5);
	printf ("ret ipc_switching_get 5 : %d\n", ret);
	ret = ipc_switching_get (&TCP_TO_IPC, 2);
	printf ("ret ipc_switching_get 2 : %d\n", ret);



	ipc_switching_del (&TCP_TO_IPC, 5);
	ipc_switching_print(&TCP_TO_IPC);
	ipc_switching_del (&TCP_TO_IPC, 5);
	ipc_switching_print(&TCP_TO_IPC);
	ipc_switching_del (&TCP_TO_IPC, 1);
	ipc_switching_print(&TCP_TO_IPC);

	free (TCP_TO_IPC.collection);
	// free (IPC_TO_TCP);

    return EXIT_SUCCESS;
}
