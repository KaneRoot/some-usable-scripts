/*  manipulation de pointeurs */

#include <stdio.h>

main()
{
    char *c[] = { "ENTER","NEW","POINT","FIRST" };
    char **cp[] = { c+3, c+2, c+1, c };
    char ***cpp = cp;

    printf("\n%s", **++cpp );
    printf("%s ", *--*++cpp + 3 );
    printf("%s\n", *cpp[-2] + 3 );
}
