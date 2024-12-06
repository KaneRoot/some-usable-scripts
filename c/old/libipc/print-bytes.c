#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <ipc.h>

int main(int argc, char * argv[])
{
	SECURE_BUFFER_DECLARATION (char, buffer, 4096);
	uint32_t msize = 0;
	char *message = "coucou";

	if (argc == 2) {
		message = argv[1];
	}

	msize = ipc_message_raw_serialize (buffer, 2, 42, message, strlen(message));
	write (1, buffer, msize);
	fflush (stdout);

	// to wait for a response
	sleep (1);

    return EXIT_SUCCESS;
}
