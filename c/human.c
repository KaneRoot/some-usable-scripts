#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARGUMENTS "d:f:"

struct fields
{
    int nbfields;
    unsigned int *fields;
};

void
chomp (const char *s)
{
    char *p;
    while (NULL != s && NULL != (p = strrchr(s, '\n'))) {
        *p = '\0';
    }
} /* chomp */

int
human (const char *s, char *stmp, ssize_t bufsize)
{
    unsigned long long int val = strtoull(s, NULL, 10);

    char suf = ' ';
    if(val > 1000) {
        val /= 1000;
        suf = 'k';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'M';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'M';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'G';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'T';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'P';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'E';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'Z';
    }

    if(val > 1000) {
        val /= 1000;
        suf = 'Y';
    }

    snprintf(stmp, bufsize, "%llu %co", val, suf);
    return EXIT_SUCCESS;
}

void
print_token_to_human (const char *token)
{
    char *stmp = malloc(BUFSIZ);
    if(stmp != 0) {
        int ret = human(token, stmp, BUFSIZ);
        printf("%s ", stmp);
        free(stmp);
    }
}

void
print_delim (char *s, const char *delim, const struct fields *f)
{
    char *token, *saveptr;
    char *str;
    int i, j;

    // printf("%d fields :: ", f->nbfields);
    // for( i = 0 ; i < f->nbfields ; i++) {
    //     printf("%u, ", f->fields[i]);
    // }
    // printf("\n");

    for (str = s, i = 1; ; str = NULL, i++) {
        token = strtok_r(str, delim, &saveptr);
        if (token == NULL)
            break;

        // check if we need to print the current token humanized
        int found = 0;

        for (j = 0 ; j < f->nbfields ; j++ ) {
            if( i == f->fields[j] ) {
                print_token_to_human(token);
                found = 1;
                break;
            }
        }

        // print the current token not humanized
        if (found == 0) {
            printf("%s ", token);
        }
    }
}

/*
 * print every line, with the first token humanized
 * there is a split in the line by the space character to get tokens
 */

void
print_human (char *s)
{
    struct fields f;
    f.nbfields = 1;
    f.fields = malloc(sizeof(unsigned int) * 1);
    f.fields[0] = 1;
    print_delim (s, " ", &f);
}

// get the index of every token to humanize
int
get_tok_to_humanize (char *s, struct fields *f)
{
    if(f == NULL || s == NULL) {
        return 1;
    }

    char *str = NULL;
    char *token = NULL, *saveptr = NULL;
    f->nbfields = 0;

    // counts the number of fields
    char * strtmp = s;
    while(*strtmp++ != '\0') {
        if (*strtmp == ',')
            f->nbfields++;
    }
    f->nbfields++;

    f->fields = (unsigned int *) malloc(sizeof(unsigned int) * f->nbfields);

    int i;
    for (str = s, i = 0; ; str = NULL, i++) {
        token = strtok_r(str, ",", &saveptr);
        if (token == NULL)
            break;

        f->fields[i] = atoi(token);
    }

    return 0;
}

int
main (int argc, char *argv[])
{
    char *strtmp = malloc(BUFSIZ);
    char *delim = NULL;   // options
    struct fields fields;

    if(argc < 1 || argc > 3) {
        fprintf(stderr, "Usage: %s [fields [delim]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int ret ;
    switch (argc) {
        case 3 :
            ret = get_tok_to_humanize(argv[1], &fields);
            delim = argv[2];
            break;
        case 2 :
            ret = get_tok_to_humanize(argv[1], &fields);
            delim = (char *) malloc(1);
            *delim = ' ';
            break;
    }

    while(fgets(strtmp, BUFSIZ, stdin)) {

        chomp(strtmp);

        if(delim) {
            print_delim (strtmp, delim, &fields);
        }
        else {
            print_human (strtmp);
        }

        printf("\n");
    }

    free(strtmp);

    exit(EXIT_SUCCESS);
}
