#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// 信号处理函数
void signal_handler(int signum, siginfo_t *info, void *context)
{
    if (signum == SIGUSR1)
    {
        int *ptr = (int *)info->si_value.sival_ptr;
        printf("Received pointer value: %d\n", *ptr);
        // printf("int value %d\r\n", info->si_value.sival_int);
        // free(ptr); // 释放动态分配的内存
    }
}

int main()
{
    pid_t target_pid;
    int *data;
    union sigval sv;
    int a = 10;

    // 注册信号处理函数
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    // 获取目标进程ID（这里假设是当前进程）
    target_pid = getpid();

    // 动态分配内存并赋值
    data = (int *)malloc(sizeof(int));
    if (data == NULL)
    {
        perror("malloc");
        return 1;
    }
    *data = 42;

    // 设置要发送的数据
    sv.sival_ptr = &a;
    // sv.sival_int = *data;

    // 发送信号和数据
    if (sigqueue(target_pid, SIGUSR1, sv) == -1)
    {
        perror("sigqueue");
        free(data);
        return 1;
    }

    // 等待信号处理
    pause();

    return 0;
}
