#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILDBIN "./com-child"

int main(int argc, char * argv[])
{

    if (argc < 2) {
        fprintf (stderr, "usage : %s string\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    int in[2], out[2];
    FILE *in_fp, *out_fp;

    pipe(in);
    pipe(out);

    if (fork()) { // PARENT

        close(in[0]);
        close(out[1]);

        write (in[1], argv[1], strlen(argv[1]));

        char buf[BUFSIZ];
        read (out[0], buf, BUFSIZ);
        buf[BUFSIZ-1] = '\0';

        printf ("response : %s\n", buf);

    } else { // CHILD

        close(0);
        close(1);

        dup2(in[0], 0);
        dup2(out[1], 1);

        execv(CHILDBIN, NULL);
    }

    int status;
    wait(&status);
    // do something with the status

    return EXIT_SUCCESS;
}

