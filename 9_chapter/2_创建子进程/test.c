#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void error_return(pid_t re, const char *buf, pid_t judge);
int main(void)
{
    pid_t re;

    re = fork();
    error_return(re, "fork error", -1);

    if (re == 0)
    {
        printf("I am child process\r\n");
        printf("My pid is %d, my father pid is %d\r\n", getpid(), getppid());
        return 0;
    }
    if (re != 0)
    {
        printf("I am father process\r\n");
        printf("My pid is %d, my child pid is %d\r\n", getpid(), re);
        return 0;
    }

    return 0;
}

void error_return(pid_t re, const char *buf, pid_t judge)
{
    if (re == judge)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}