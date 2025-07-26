#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

void *new_pthread(void *arg);
int main(void)
{
    int re = 0;
    pthread_t pt = 0;

    re = pthread_create(&pt, NULL, new_pthread, NULL);
    if (re)
    {
        printf("create pthread error\r\n");
        exit(-1);
    }
    sleep(2);
    printf("%ld\r\n", pt);
    // 没有下面的sleep时，只输出主进程的printf，这是因为main函数中return语句会使编译器调用进程推出代码_exit()
    // 故进程就终止了,所以进程里面的所有线程都终止了.所以新线程还没运行整个进程就终止了.但是不是main函数调用return就不会
    // 使进程终止，如新建线程的启动函数中调用return就不会使进程终止，只是会终止调用return的线程。
    // sleep(1);
    printf("主线程：进程ID=%d，线程ID=%lu\r\n", getpid(), pthread_self());
    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
    printf("子线程：进程ID=%d，线程ID=%lu\r\n", getpid(), pthread_self());
    return 0;
}
