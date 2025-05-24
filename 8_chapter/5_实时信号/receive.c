#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig, siginfo_t *info, void *ptr);
void error_return(int fd, const char *buf, int re);
int main(int argc, char *argv[])
{

    struct sigaction sig = {0};
    int re, num;

    if (argc < 2)
    {
        printf("输入参数缺失\r\n");
        return -1;
    }

    // 需要接收的实时信号
    num = atoi(argv[1]);

    sig.sa_sigaction = sig_handler;
    sig.sa_flags = SA_SIGINFO;
    re = sigaction(num, &sig, NULL);
    error_return(re, "sigaction error", -1);

    // 死循环
    while (1)
        ;

    return 0;
}

void sig_handler(int sig, siginfo_t *info, void *ptr)
{
    int *a = (int *)info->si_value.sival_ptr;
    printf("伴随信息的整形数据为%d\r\n", info->si_value.sival_int);
    printf("伴随信息的指针数据为%d\r\n", *a);
}

void error_return(int fd, const char *buf, int re)
{
    if (fd == re)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}