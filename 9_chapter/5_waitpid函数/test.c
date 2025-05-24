#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define USE_0 0
#define USE_1 0
#define USE_2 1
void use_0(void);
void use_1(void);
void use_2(void);
int main(void)
{
#if USE_0
    use_0();
#endif
#if USE_1
    use_1();
#endif
#if USE_2
    use_2();
#endif
    return 0;
}

void use_0(void)
{
    int pid = 0;
    int re = 0, status = 0;

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("fork error\r\n");
        exit(-1);
    case 0:
        printf("child process pid is %d\r\n", getpid());
        exit(0);
    default:
        sleep(1);
        printf("I am father process\r\n");
        re = waitpid(pid, &status, 0);
        if (re == -1)
        {
            printf("waitpid error\r\n");
            exit(-1);
        }
        printf("child process is %d, %d\r\n", re, WEXITSTATUS(status));
        exit(0);
    }
}
void use_1(void)
{
    int pid = 0;
    int re = 0, status = 0;

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("fork error\r\n");
        exit(-1);
    case 0:
        printf("child process pid is %d\r\n", getpid());
        exit(0);
    default:
        printf("I am father process\r\n");
        re = waitpid(-1, &status, WNOHANG);
        if (re == -1)
        {
            printf("waitpid error\r\n");
            exit(-1);
        }
        else if (re == 0)
        {
            printf("No\r\n");
            exit(-1);
        }
        printf("child process is %d, %d\r\n", re, WEXITSTATUS(status));
        exit(0);
    }
}
void use_2(void)
{
    int pid = 0;
    int re = 0, status = 0;

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("fork error\r\n");
        exit(-1);
    case 0:
        printf("I am child process, pid is %d\r\n", getpid());
        while (1)
        {
        }
    default:
        printf("I am father process\r\n");
        while (1)
        {
            re = waitpid(-1, &status, WUNTRACED | WCONTINUED);
            printf("%d", re);
            if (re == -1)
            {
                printf("waitpid error\r\n");
                exit(-1);
            }
            else if (re == 0)
            {
                printf("No\r\n");
                exit(-1);
            }
            else
                printf("child process is %d, %d\r\n", re, WEXITSTATUS(status));
        }
        exit(0);
    }
}