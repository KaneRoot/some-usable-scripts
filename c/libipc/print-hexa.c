#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ipc.h>
#include <utils.h>


int main(int argc, char * argv[])
{
	argc = argc; // warnings
	argv = argv; // warnings


	SECURE_BUFFER_DECLARATION (uint8_t, buffer, 100);

	buffer[0] = 1;
	buffer[1] = 16;
	buffer[2] = 17;
	buffer[3] = 18;
	buffer[4] = 1;
	buffer[5] = 2;

	print_hexa ("coucou", buffer, 50);

    return EXIT_SUCCESS;
}
