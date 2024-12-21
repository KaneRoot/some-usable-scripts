#include <stdio.h>
#include <fcntl.h> // open
#include <unistd.h> // read write
#include <stdlib.h>

#include <netdb.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#define BUFFER_SIZE 1000

/*	The purpose of this application is to test AppArmor profiles.
	Thus, this application can perform a few (limited) operations regarding files and network access.
*/

void read_file(char *filename) {
	printf("read_file: %s\n", filename);
	int fd = open(filename, O_RDONLY, NULL);
	if (fd > 0) {
		char buffer[BUFFER_SIZE];
		size_t bytes = read(fd, buffer, BUFFER_SIZE);
		printf("read %zu bytes\n", bytes);
		close(fd);
	}
	else {
		printf("impossible to read %s\n", filename);
	}
}

void write_file(char *filename) {
	printf("write_file: %s\n", filename);
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd > 0) {
		char buffer[] = "hello that's meeeeee";
		size_t bytes = write(fd, buffer, sizeof buffer);
		printf("wrote %zu bytes\n", bytes);
		close(fd);
	}
	else {
		printf("impossible to write %s\n", filename);
	}
}

void unixsock_server(char *address) {
	printf("unixsock_server: %s\n", address);
	int      ret;
	int      connection_socket;
	int      data_socket;
	ssize_t  r, w;
	struct sockaddr_un  name;
	char buffer[BUFFER_SIZE];

	/* Create local socket. */
	connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (connection_socket == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&name, 0, sizeof(name));

	/* Bind socket to socket name. */
	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, address, sizeof(name.sun_path) - 1);
	ret = bind(connection_socket, (const struct sockaddr *) &name, sizeof(name));
	if (ret == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	ret = listen(connection_socket, 20);
	if (ret == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* Wait for incoming connection. */
	data_socket = accept(connection_socket, NULL, NULL);
	if (data_socket == -1) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* Wait for a data packet. */
	r = read(data_socket, buffer, sizeof(buffer));
	if (r == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	/* Ensure buffer is 0-terminated. */
	buffer[sizeof(buffer) - 1] = 0;

	printf("received: %s\n", buffer);

	/* Send result. */
	sprintf(buffer, "hello back");
	printf("sending: %s\n", buffer);
	w = write(data_socket, buffer, sizeof(buffer));
	if (w == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	/* Close socket. */
	printf("closing\n");
	close(data_socket);
	close(connection_socket);

	/* Unlink the socket. */
	printf("unlink: %s\n", address);
	unlink(address);
}

void unixsock_client(char *address) {
	printf("unixsock_client: %s\n", address);

	int ret;
	int data_socket;
	ssize_t r, w;
	struct sockaddr_un addr;
	char buffer[BUFFER_SIZE];

	/* Create local socket. */
	data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (data_socket == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&addr, 0, sizeof(addr));

	/* Connect socket to socket address. */
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, address, sizeof(addr.sun_path) - 1);
	printf("address is: %s\n", addr.sun_path);

	ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));
	if (ret == -1) {
		fprintf(stderr, "server is down\n");
		exit(EXIT_FAILURE);
	}

	/* Send data. */
	w = write(data_socket, "hello", 6);
	if (w == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	/* Receive data. */
	r = read(data_socket, buffer, sizeof(buffer));
	if (r == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	/* Ensure buffer is 0-terminated. */
	buffer[sizeof(buffer) - 1] = 0;

	printf("received: %s\n", buffer);

	/* Close socket. */
	printf("closing\n");
	close(data_socket);
}

void network_client(char *address, char *port) {
	printf("network_client: @%s port %s\n", address, port);
	int              sfd, s;
	char             buffer[BUFFER_SIZE];
	ssize_t          nread;
	struct addrinfo  hints;
	struct addrinfo  *result, *rp;

	/* Obtain address(es) matching host/port. */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0; /* Any protocol */

	s = getaddrinfo(address, port, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully connect(2).
	   If socket(2) (or connect(2)) fails, we (close the socket and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1) continue;
		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) break;
		close(sfd);
	}
	freeaddrinfo(result); /* No longer needed */

	if (rp == NULL) { /* No address succeeded */
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	snprintf(buffer, 6, "hello");
	if (write(sfd, buffer, 6) != 6) {
		fprintf(stderr, "partial/failed write\n");
		exit(EXIT_FAILURE);
	}

	nread = read(sfd, buffer, BUFFER_SIZE);
	if (nread == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	printf("received %zd bytes: %s\n", nread, buffer);
}

void network_server(char *port) {
	printf("network_server: %s\n", port);
	int                     sfd, s;
	char                    buffer[BUFFER_SIZE];
	ssize_t                 nread;
	socklen_t               peer_addrlen;
	struct addrinfo         hints;
	struct addrinfo         *result, *rp;
	struct sockaddr_storage peer_addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM;  /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;     /* For wildcard IP address */
	hints.ai_protocol = 0;           /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully bind(2).
	   If socket(2) (or bind(2)) fails, we (close the socket and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1) continue;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
		close(sfd);
	}
	freeaddrinfo(result); /* No longer needed */

	if (rp == NULL) { /* No address succeeded */
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	/* Read a single datagram and echo it back to sender. */
	char host[NI_MAXHOST], service[NI_MAXSERV];

	peer_addrlen = sizeof(peer_addr);
	nread = recvfrom(sfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addrlen);
	if (nread == -1) {
		fprintf(stderr, "nread == -1\n");
		exit(EXIT_FAILURE);
	}

	s = getnameinfo((struct sockaddr *) &peer_addr, peer_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
	if (s == 0) printf("Received %zd bytes from %s:%s\n", nread, host, service);
	else        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

	printf("sending it back to sender\n");
	if (sendto(sfd, buffer, nread, 0, (struct sockaddr *) &peer_addr, peer_addrlen) != nread) {
		fprintf(stderr, "Error sending response\n");
	}
}

void usage(void) {
	printf("usage: paintest r /path/to/file w /path/to/file n example.com:8080 u /unix/socket/path\n");
}

int main(int argc, char **argv)
{
	int i = 1;
	if(argc < 2) {
		usage();
		exit (EXIT_SUCCESS);
	}

	while (i != argc) {
		if      (memcmp(argv[i], "r", 1) == 0) { read_file(argv[i+1]);                      }
		else if (memcmp(argv[i], "w", 1) == 0) { write_file(argv[i+1]);                     }
		else if (memcmp(argv[i], "n", 1) == 0) { network_client(argv[i+1], argv[i+2]); i++; }
		else if (memcmp(argv[i], "N", 1) == 0) { network_server(argv[i+1]);                 }
		else if (memcmp(argv[i], "u", 1) == 0) { unixsock_client(argv[i+1]);                }
		else if (memcmp(argv[i], "U", 1) == 0) { unixsock_server(argv[i+1]);                }
		else if (memcmp(argv[i], "h", 1) == 0) { usage();                                   }
		i += 2;
	}

	return 0;
}
