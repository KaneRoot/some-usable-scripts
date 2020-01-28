#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <syslog.h>

int main(int argc, char * argv[])
{
	argc = argc; // warnings
	argv = argv; // warnings

	setlogmask (LOG_UPTO (LOG_NOTICE));

	openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	syslog (LOG_NOTICE, "Program started by User %d",  1000);
	syslog (LOG_INFO, "A tree falls in a forest");

	closelog ();

	return EXIT_SUCCESS;
}
