#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void int_handler(int sig);
void error_return(int re, const char *buf, int judge);
int main(int argc, char *argv[])
{
    int re = 0;
    struct sigaction sig = {0};

    // 定义信号处理函数
    sig.sa_flags = 0;
    sig.sa_handler = int_handler;
    re = sigaction(SIGINT, &sig, NULL);
    error_return(re, "sigaction error", -1);

    // 定义空信号集
    sigset_t set;
    re = sigemptyset(&set);
    error_return(re, "sigemptyset error", -1);
    // 往信号集中添加信号
    re = sigaddset(&set, SIGINT);
    error_return(re, "sigaddset error", -1);

    re = sigprocmask(SIG_BLOCK, &set, NULL);
    error_return(re, "sigprocmask error", -1);

    while (1)
    {
        sleep(2);
        raise(SIGINT);
    }

    return 0;
}

void int_handler(int sig)
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