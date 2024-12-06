#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun(char * env[])
{
	char buffer[4096];
	memset (buffer, 0, 4096);

	char *curp = buffer;
	char *endp = buffer + 4096;

	for (size_t i = 0 ; env[i] != NULL ; i++) {
		// TODO: check for every IPC_NETWORK_* environment variable
		if (strncmp(env[i], "IPC_NETWORK", 11) == 0) {
			curp += snprintf (curp, endp - curp, "%s\n", env[i]);
		}
	}

	printf ("%s", buffer);
}

int main(int argc, char * argv[], char *env[])
{
	// fun (env);

	argc = argc;
	argv = argv;
	env = env;

	char *network_envvar = getenv("IPC_NETWORK");
	if (network_envvar == NULL)
	{
		fprintf (stderr, "no IPC_NETWORK env var\n");
		exit (1);
	}

	printf ("IPC_NETWORK: %s\n", network_envvar);

	// size_t nenvsize = strlen (network_envvar);
	// size_t i = 0;

	if (strncmp (network_envvar, "pong", 4) == 0) {
		printf ("pong found\n");
	}
	else if (strstr (network_envvar, ";pong") != NULL) {
		printf ("pong found\n");
	}
	else {
		printf ("pong not found\n");
	}

    return EXIT_SUCCESS;
}
