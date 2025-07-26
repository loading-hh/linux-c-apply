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

    re = pthread_create(&pt, NULL, new_pthread, NULL);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }

    re = pthread_join(pt, &retval);
    if (re)
    {
        fprintf(stderr, "create pthread error %s\r\n", strerror(re));
        exit(-1);
    }
    printf("新线程结束, code=%ld\r\n", (long)retval);
    pthread_exit(NULL);
}

void *new_pthread(void *arg)
{
    printf("新线程开始\r\n");
    printf("新线程结束\r\n");
    pthread_exit((void *)10);
}
