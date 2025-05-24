#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    int i = 0, re = 0, state = 0;
    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            printf("fork error\r\n");
            return -2;
        case 0:
            printf("子进程 %d 被创建\r\n", getpid());
            sleep(i);
            return i;
        default:
            break;
        }
    }
    sleep(1); // 这个不加下面这个printf就会打印在最前面
    printf("-----------\r\n");
    for (i = 0; i < 3; i++)
    {
        re = wait(&state);
        if (re == -1)
        {
            if (ECHILD == errno)
            {
                printf("Don't have child process\r\n");
                return -1;
            }
            else
            {
                printf("wait error\r\n");
                return -2;
            }
        }
        else
            printf("回收子进程 %d, 终止状态是%d\r\n", re, WEXITSTATUS(state));
    }

    return 0;
}