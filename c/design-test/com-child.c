#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{

    char buf[BUFSIZ];
    read (0, buf, BUFSIZ);
    buf[BUFSIZ-1] = '\0';
    printf ("%s", buf);

    return EXIT_SUCCESS;
}
