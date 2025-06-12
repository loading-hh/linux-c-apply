#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    int cnt = 1;
    pid_t re = 0;

    switch (vfork())
    {
    case -1:
        printf("vfork error\r\n");
        return -1;
    case 0:
        cnt++;
        printf("%d\r\n", cnt);
        printf("I am child process %d\r\n", getpid());
        _exit(0);

    default:
        printf("%d\r\n", cnt);
        printf("I am father process %d\r\n", getpid());
        break;
    }

    return 0;
}