#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define KILL 0
#define RAISE 1
void int_handler(int sig);
void error_return(int re, const char *buf, int judge);
int main(int argc, char *argv[])
{

#if KILL

    int pid, re;

    if (argc < 2)
    {
        printf("no input pid\r\n");
        return -1;
    }

    pid = atoi(argv[1]);
    printf("pid %d\r\n", pid);

    re = kill(pid, SIGINT);
    error_return(re, "kill error", -1);

#endif

#if RAISE

    struct sigaction sig = {0};
    int re;

    sig.sa_handler = int_handler;
    sig.sa_flags = 0;
    re = sigaction(SIGINT, &sig, NULL);
    if (re == -1)
    {
        perror("sigaction error");
        return -1;
    }

    while (1)
    {
        re = raise(SIGINT);
        if (re != 0)
        {
            printf("raise error\r\n");
            return -1;
        }
        sleep(2);
    }

#endif
    return 0;
}

void int_handler(int sig)
{
    printf("\r\n收到信号 %d\r\n", sig);
}

void error_return(int re, const char *buf, int judge)
{
    if (re == judge)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}