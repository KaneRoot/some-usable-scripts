#include <stdio.h>
//#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

// For poll-related stuff.
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <unistd.h>

#define err(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define BILLION  1000000000L
#define MILLION  1000000L
#define THOUSAND 1000L

void get_time_ts(struct timespec *t0) {
	if (clock_gettime(CLOCK_REALTIME, t0) == -1) {
		perror("clock_gettime");
		exit(1);
	}
}

long long duration_ns(struct timespec t0, struct timespec t1) {
	return ((t1.tv_sec - t0.tv_sec)*BILLION) + (t1.tv_nsec - t0.tv_nsec);
}

void print_time_ns(long long time) {
	printf("%llds %lldms %lldµ %lldns\n"
		, time/BILLION
		, (time/MILLION)%THOUSAND
		, (time/THOUSAND)%THOUSAND
		, time%THOUSAND
	);
}

int main(int argc, char *argv[])
{
	// Time-related structures.
	struct timespec t0, t1;

	int ready;
	char buf[10];
	nfds_t num_open_fds, nfds;
	ssize_t s;
	struct pollfd *pfds;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num_open_fds = nfds = argc - 1;
	pfds = calloc(nfds, sizeof(struct pollfd));
	if (pfds == NULL)
		err("malloc");

	/* Open each file on command line, and add it to 'pfds' array. */

	for (nfds_t j = 0; j < nfds; j++) {
		pfds[j].fd = open(argv[j + 1], O_RDONLY);
		if (pfds[j].fd == -1)
			err("open");

		printf("Opened \"%s\" on fd %d\n", argv[j + 1], pfds[j].fd);

		pfds[j].events = POLLIN;
	}

	/* Keep calling poll() as long as at least one file descriptor is
	   open. */

	while (num_open_fds > 0) {
		printf("About to poll()\n");

		get_time_ts(&t0);
		ready = poll(pfds, nfds, -1);
		get_time_ts(&t1);
		if (ready == -1)
			err("poll");

		printf("polling duration: ");
		print_time_ns(duration_ns(t0, t1));

		printf("Ready: %d\n", ready);

		/* Deal with array returned by poll(). */

		for (nfds_t j = 0; j < nfds; j++) {
			if (pfds[j].revents != 0) {
				printf("  fd=%d; events: %s%s%s\n", pfds[j].fd,
				       (pfds[j].
					revents & POLLIN) ? "POLLIN " : "",
				       (pfds[j].
					revents & POLLHUP) ? "POLLHUP " : "",
				       (pfds[j].
					revents & POLLERR) ? "POLLERR " : "");

				if (pfds[j].revents & POLLIN) {
					s = read(pfds[j].fd, buf, sizeof(buf));
					if (s == -1)
						err("read");
					printf("    read %zd bytes: %.*s\n",
					       s, (int)s, buf);
				} else {	/* POLLERR | POLLHUP */
					printf("    closing fd %d\n",
					       pfds[j].fd);
					if (close(pfds[j].fd) == -1)
						err("close");
					num_open_fds--;
				}
			}
		}
	}

	printf("All file descriptors closed; bye\n");
	exit(EXIT_SUCCESS);
}
