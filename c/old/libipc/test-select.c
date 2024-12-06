#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int setup_tcp_socket(short int port)
{
	/* server address */
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	socklen_t addrlen = sizeof(struct sockaddr_in);

    /* for setsockopt() SO_REUSEADDR, below */
    int yes = 1;
	int listener = -1;

	if((listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		perror("Server-socket()");
		exit(1);
	}
	printf("Server-socket() is OK... fd %d\n", listener);

	/*"address already in use" error message */
	if(setsockopt(listener
		, SOL_SOCKET
		, SO_REUSEADDR
		, &yes
		, sizeof(int)) == -1) {
		perror("Server-setsockopt()");
		exit(1);
	}
	printf("Server-setsockopt() is OK...\n");

	/* bind */
	serveraddr.sin_family      = AF_INET;
	serveraddr.sin_port        = htons(port);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	// memset(&(serveraddr.sin_zero), '\0', 8);

	if(bind(listener, (struct sockaddr *)&serveraddr, addrlen) == -1) {
		perror("Server-bind()");
		exit(1);
	}
	printf("Server-bind() is OK...\n");

	/* listen */
	if(listen(listener, 10) == -1)
	{
		perror("Server-listen()");
		exit(1);
	}
	printf("Server-listen() is OK...\n");

	return listener;
}

int main(int argc, char * argv[])
{
	if (argc < 2) {
		fprintf (stderr, "usage: %s port\n", argv[0]);
		exit(1);
	}

	short int port = atoi(argv[1]);

	printf ("port : %d\n", port);

	/* client address */
	struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));

    /* master file descriptor list */
    fd_set master;
    /* temp file descriptor list for select() */
    fd_set read_fds;

    /* maximum file descriptor number */
    int fdmax;
    /* listening socket descriptor */
    // int listener = open ("/tmp/bla", O_RDONLY);
    int listener;
    int newfd;
    /* buffer for client data */
    char buf[6];
    int nbytes;

    socklen_t addrlen;
    int i, j;


	/* Now we set variables */

	listener = setup_tcp_socket (port);

    /* clear the master and temp sets */
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    /* add the listener to the master set */
    FD_SET(listener, &master);

    /* keep track of the biggest file descriptor */
    fdmax = listener; /* so far, it's this one*/

	int times_going_in_select = 0;

    /* loop */
    for(;;) {
        /* copy it */
        read_fds = master;
        if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("Server-select() error lol!");
            exit(1);
        }
        times_going_in_select++;

        // printf("Server-select() is OK... message received\n");

        /*run through the existing connections looking for data to be read*/
        for(i = 0; i <= fdmax; i++) {
            if(FD_ISSET(i, &read_fds)) {
                /* we got one... */
                if(i == listener) {
                    printf("new connection");

					/* handle new connections */
					addrlen = sizeof(clientaddr);
					if((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1) {
						perror("Server-accept()");
					}
					else
					{
						printf("Server-accept() is OK...\n");
						FD_SET(newfd, &master); /* add to master set */
						if(newfd > fdmax)
						{ /* keep track of the maximum */
							fdmax = newfd;
						}

						printf("%s: New connection from %s on socket %d\n"
								, argv[0], inet_ntoa(clientaddr.sin_addr), newfd);
					}
                }
                else {
                    /* handle data from a client */
                    if((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        /* got error or connection closed by client */
                        if(nbytes == 0)
                            /* connection closed */
                            printf("%s: socket %d hung up\n", argv[0], i);

                        else
                            perror("recv() error lol!");

                        /* close it... */
                        close(i);
                        /* remove from master set */
                        FD_CLR(i, &master);
                    }
                    else {
                    	printf("received message: %s  (%d going in select function)\n", buf, times_going_in_select);

                        /* we got some data from a client*/
                        for(j = 0; j <= fdmax; j++) {
                            /* send to everyone! */
                            if(FD_ISSET(j, &master)) {
#if 0
                                /* except the listener and ourselves */
                                if(j != listener && j != i)
#endif
                                /* except the listener */
                                if(j != listener) {
                                    if(send(j, buf, nbytes, 0) == -1)
                                        perror("send() error lol!");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
