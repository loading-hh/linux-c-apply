#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int num = 0;
void *new_pthread(void *arg);
int main(void)
{
    int re = 0;
    pthread_t pt1 = 0;

    // 初始化条件变量
    re = pthread_cond_init(&cond, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 初始化互斥锁
    re = pthread_mutex_init(&mutex, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 创建第一个线程
    re = pthread_create(&pt1, NULL, new_pthread, NULL);
    if (re)
    {
        fprintf(stderr, "first pthread create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    while (1)
    {
        pthread_mutex_lock(&mutex);
        // 共享变量值增大
        num++;
        printf("进货\r\n");
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }

    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (num <= 0)
            pthread_cond_wait(&cond, &mutex);
        // 共享变量值减小，这里再判断一次num是为了保险。
        while (num > 0)
        {
            num--;
            printf("出货\r\n");
        }

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit((void *)0);
}
