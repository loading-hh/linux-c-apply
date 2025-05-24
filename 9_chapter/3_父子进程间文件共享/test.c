#include <stdio.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIRST_OPEN 0
#define NO_OPEN 1
void error_return(int re, const char *buf, int judge);
int main(void)
{

    char child_process[] = "child process";
    char father_process[] = "father process";
    int fd, re = 0;
#if FIRST_OPEN

    fd = open("./test.txt", O_RDWR | O_TRUNC);
    error_return(fd, "open file error", -1);

    re = fork();
    switch (re)
    {
    case -1:
        perror("fork error");
        close(fd);
        return -1;

    case 0: // 子进程
        for (int i = 0; i < 4; i++)
            write(fd, child_process, strlen(child_process));
        close(fd);
        return 0;
    default:
        for (int j = 0; j < 4; j++)
            write(fd, father_process, strlen(father_process));
        close(fd);
        return 0;
    }
#endif

#if NO_OPEN
    re = fork();
    switch (re)
    {
    case -1:
        perror("fork error");
        close(fd);
        return -1;

    case 0: // 子进程
        fd = open("./test.txt", O_RDWR);
        error_return(fd, "open file error", -1);
        for (int i = 0; i < 4; i++)
            write(fd, child_process, strlen(child_process));
        close(fd);
        return 0;
    default:
        fd = open("./test.txt", O_RDWR);
        error_return(fd, "open file error", -1);
        for (int j = 0; j < 5; j++)
            write(fd, father_process, strlen(father_process));
        close(fd);
        return 0;
    }
#endif
}

void error_return(int re, const char *buf, int judge)
{
    if (re == judge)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}