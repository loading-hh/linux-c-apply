#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

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
    sleep(2);
    // 等待新线程终止，并回收新线程资源
    re = pthread_join(pt, &retval);
    if (re)
    {
        fprintf(stderr, "pthread join error %s\r\n", strerror(re));
    }
    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
    int re;
    re = pthread_detach(pthread_self());
    if (re)
    {
        printf("pthread error %s\r\n", strerror(re));
        pthread_exit((void *)-1);
    }
    printf("新线程开始\r\n");
    sleep(1);
    printf("新线程结束\r\n");
    pthread_exit((void *)10);
}
