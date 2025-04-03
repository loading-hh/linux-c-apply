#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define ALARM 1
#define PAUSE 1
void alarm_handler(int sig);
void error_return(int re, const char *buf, int judge);
int main(int argc, char *argv[])
{

    int re;
    struct sigaction sig = {0};

    if (argc < 2)
    {
        printf("no input secound variable\r\n");
        return -1;
    }

    sig.sa_flags = 0;
    sig.sa_handler = alarm_handler;
    re = sigaction(SIGALRM, &sig, NULL);
    error_return(re, "sigaction error", -1);

#if ALARM

    int second = 0;

    second = atoi(argv[1]);
    alarm(second);
    printf("定时时长 %d\r\n", second);

#if PAUSE

    printf("进入pause休眠状态\r\n");
    pause();
    printf("pause休眠状态结束\r\n");
#else

    while (1)
        sleep(1);
#endif

#endif
    return 0;
}

void alarm_handler(int sig)
{
    printf("\r\n收到SIGARM信号 %d\r\n", sig);
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