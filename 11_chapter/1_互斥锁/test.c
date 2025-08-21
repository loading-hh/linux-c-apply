#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define LOCK 0
#define TRY_LOCK 1

pthread_mutex_t mutex;
int num = 0, loop = 100000;
void *new_pthread(void *arg);
int main(void)
{
    int re = 0;
    pthread_t pt1 = 0, pt2 = 0;

    // 初始化互斥锁
    re = pthread_mutex_init(&mutex, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 创建第一个线程
    re = pthread_create(&pt1, NULL, new_pthread, &loop);
    if (re)
    {
        fprintf(stderr, "first pthread create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 创建第二个线程
    re = pthread_create(&pt2, NULL, new_pthread, &loop);
    if (re)
    {
        fprintf(stderr, "secound pthread create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    // 等待第一个线程结束
    re = pthread_join(pt1, NULL);
    if (re)
    {
        fprintf(stderr, "first pthread create pthread error %s\r\n", strerror(re));
        exit(-1);
    }
    // 等待第二个线程结束
    re = pthread_join(pt2, NULL);
    if (re)
    {
        fprintf(stderr, "secound pthread create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    pthread_mutex_destroy(&mutex);
    printf("%d\r\n", num);
    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
    // 当把互斥锁注销后会发现num的值不是二倍的loop(前提是loop足够大,否则是二倍)
    int all_loop = *(int *)arg;
    for (int i = 0; i < all_loop; i++)
    {
#if LOCK
        pthread_mutex_lock(&mutex);
        num++;
        pthread_mutex_unlock(&mutex);
#endif

#if TRY_LOCK
        while (pthread_mutex_trylock(&mutex))
            ;
        num++;
        pthread_mutex_unlock(&mutex);
#endif // DEBUG
    }
    pthread_exit((void *)0);
}
