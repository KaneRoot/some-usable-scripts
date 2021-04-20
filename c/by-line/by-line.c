#include <stdio.h> // printf
#include <fcntl.h>
#include <string.h> // memchr
#include <unistd.h> // read write
#include <stdint.h> // uint32_t
#include <stdlib.h> // exit
#include <poll.h> // poll

// OUTPUT: line-by-line strings

#define line_size_exceeded "line exeeded max buffer size\n"
#define  MAXBUFFER 64000

char buf[MAXBUFFER];

void err(int error, const char *str) {
	fprintf (stderr, "%s\n", str);
	exit(error);
}

int main(int argc, const char **argv)
{
	if (argc > 1) {
		printf ("usage: %s\n", argv[0]);
		return 0;
	}

	// fcntl(0, F_SETFL, O_SYNC);

	uint32_t tot_read = 0;
	uint32_t n_read = 0;
	struct pollfd pfd[1];
	int nready;

	pfd[0].fd = 0;

	while (1) {
		pfd[0].events = POLLIN;
		nready = poll(pfd, 1, 60 * 1000);

		if (nready == -1)
			err (1, "poll");

		if (nready == 0) {
			fprintf (stderr, "time out\n");
		}

		if ((pfd[0].revents & (POLLERR|POLLNVAL))) {
			fprintf (stderr, "bad fd %d", pfd[0].fd);
			err (1, "bad fd");
		}

		if ((pfd[0].revents & (POLLIN|POLLHUP))) {
			n_read = read(0, buf, sizeof(buf));
			if (n_read > 0) {
				// fprintf (stderr, "read %u characters\n", n_read);

				tot_read += n_read;
				// fprintf(stderr, "total read %u\n", tot_read);
				// fprintf(stderr, "could still read %u\n", MAXBUFFER - tot_read);
				if (tot_read == MAXBUFFER) {
					// print anyway
					write (1, buf, tot_read);
					write (2, line_size_exceeded, strlen(line_size_exceeded));
					printf(buf);
					n_read = 0;
					tot_read = 0;
					continue;
				}

				// print line by line (if any)
				char * p = NULL;
				while ((p = memchr(buf, '\n', tot_read)) != NULL) {
					uint32_t remaining = tot_read - (p - buf) - 1;
					write (1, buf, tot_read - remaining);
					// fprintf (stderr, "found retline, %u remaining chars\n", remaining);

					for (uint32_t i = 0; i < remaining ; i++) {
						buf[i] = buf[i + tot_read - remaining];
					}
					tot_read = remaining;
					n_read = 0;
				}

			}
			else if (n_read == 0) {
				// fprintf (stderr, "EOF\n");
				break;
			}
			else {
				err (1, "read");
			}
		}
	}

	if (tot_read > 0) {
		// fprintf(stderr, "print the %u characters remaining in the buffer\n", tot_read);
		write (1, buf, tot_read);
	}

	// fprintf (stderr, "end of the loop\n");

	return 0;
}
