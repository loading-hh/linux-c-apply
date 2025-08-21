#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

pthread_rwlock_t rwlock;
int nums[2] = {0, 1};
int g_count = 0;
void *read_pthread(void *arg);
void *write_pthread(void *arg);
int main(void)
{
    int re = 0, i = 0;
    // 包括两个读线程和写线程
    pthread_t pt1[4] = {0};

    // 初始化读写锁
    re = pthread_rwlock_init(&rwlock, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 创建读模型锁的线程
    for (i = 0; i < 2; i++)
    {
        re = pthread_create(&pt1[i], NULL, read_pthread, &nums[i]);
        if (re)
        {
            fprintf(stderr, "read[%d] pthread create pthread error %s\r\n", i, strerror(re));
            exit(-1);
        }
    }

    // 创建读写模型锁的线程
    for (i = 0; i < 2; i++)
    {
        re = pthread_create(&pt1[i + 2], NULL, write_pthread, &nums[i]);
        if (re)
        {
            fprintf(stderr, "write[%d] pthread create pthread error %s\r\n", i, strerror(re));
            exit(-1);
        }
    }

    // 回收线程
    for (i = 0; i < 4; i++)
    {
        re = pthread_join(pt1[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

void *read_pthread(void *arg)
{
    int number = *(int *)arg;

    for (int i = 0; i < 10; i++)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("读线程<%d>, gt_count=%d\r\n", number + 1, g_count);
        pthread_rwlock_unlock(&rwlock);
    }

    pthread_exit((void *)0);
}

void *write_pthread(void *arg)
{
    int number = *(int *)arg;
    for (int i = 0; i < 10; i++)
    {
        pthread_rwlock_wrlock(&rwlock);
        printf("写线程<%d>, gt_count=%d\r\n", number + 1, g_count += 20);
        pthread_rwlock_unlock(&rwlock);
    }

    pthread_exit((void *)0);
}