#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int re = 0;

    re = system("echo hello world");
    if (re == -1)
    {
        printf("system error\r\n");
        return -1;
    }
    printf("%d\r\n", WEXITSTATUS(re));
    return 0;
}