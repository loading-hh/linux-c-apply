#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    int cnt = 1;
    pid_t re = 0;

    switch (fork())
    {
    case -1:
        printf("fork error\r\n");
        return -1;
    case 0:
        printf("I am child process, pid=%d pgid=%d\r\n", getpid(), getpgid(getpid()));
        if (setpgid(getpid(), getpid()))
        {
            printf("setpgid error\r\n");
            return -1;
        }
        printf("new gpid\r\n");
        printf("I am child process, pid=%d new pgid=%d\r\n", getpid(), getpgid(getpid()));
        exit(0);
    default:
        sleep(1);
        printf("I am father process, pid=%d pgid=%d\r\n", getpid(), getpgid(getpid()));
        break;
    }

    return 0;
}