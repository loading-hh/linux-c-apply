#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void error_return(int fd, const char *buf, int re);
int main(int argc, char *argv[])
{

    union sigval sig_val;
    int re, pid, sig;

    if (argc < 3)
    {
        printf("输入参数缺失\r\n");
        return -1;
    }

    // 需要接收实时信号的进程的pid
    pid = atoi(argv[1]);
    // 指定需要发送的信号
    sig = atoi(argv[2]);

    sig_val.sival_int = 10;
    // 不能跨进程传递地址，因为不同进程有独立的地址空间。
    // sig_val.sival_ptr = &pid;
    re = sigqueue(pid, sig, sig_val);
    error_return(re, "sigqueue error", -1);

    printf("信号发送成功\r\n");

    return 0;
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