#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define CANCEL_STATE 0
#define CANCEL_TYPE 0
void *new_pthread(void *arg);
int main(void)
{
    int re = 0;
    pthread_t pt = 0;
    void *retval = NULL;

    // 创建新线程
    re = pthread_create(&pt, NULL, new_pthread, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }
    sleep(1);
    // 取消新线程
    re = pthread_cancel(pt);
    if (re)
    {
        fprintf(stderr, "cancel pthread error %s\r\n", strerror(re));
        exit(-1);
    }
    // 等待新线程终止，并回收新线程资源
    re = pthread_join(pt, &retval);
    if (re)
    {
        fprintf(stderr, "pthread join error %s\r\n", strerror(re));
        exit(-1);
    }
    printf("新线程结束, code=%ld\r\n", (long)retval);
    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
#if CANCEL_STATE
    int re;

    printf("修改新线程的取消状态\r\n");
    re = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    if (re)
    {
        fprintf(stderr, "pthread cancel state error %s\r\n", strerror(re));
        pthread_exit((void *)-1);
    }
#endif

#if CANCEL_TYPE
    int re;

    printf("修改新线程的取消类型\r\n");
    re = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    if (re)
    {
        fprintf(stderr, "pthread cancel type error %s\r\n", strerror(re));
        pthread_exit((void *)-1);
    }
#endif
    printf("新线程开始\r\n");
    while (1)
    {
        sleep(1);
        printf("新线程正在运行\r\n");
    }
    pthread_exit((void *)10);
}
