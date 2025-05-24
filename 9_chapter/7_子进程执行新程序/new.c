#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main(int argc, char *argv[])
{
    int i = 0;
    char **ep = NULL;

    for (i = 0; i < argc; i++)
        printf("argv[%d] = %s\r\n", i, argv[i]);

    printf("env\r\n");
    for (ep = environ; *ep != NULL; ep++)
        printf("    %s\r\n", *ep);

    return 0;
}