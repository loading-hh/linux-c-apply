#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

void error_return(int fd, const char *buf);
int main(void)
{
    const char buf_write1[] = "hello word1\r\n";
    const char buf_write2[] = "hello word2\r\n";
    int scr1, scr2, re;

    scr1 = open("./scr.txt", O_WRONLY | O_APPEND);
    error_return(scr1, "open1 error");

    scr2 = open("./scr.txt", O_WRONLY | O_APPEND);
    error_return(scr2, "open2 error");

    re = write(scr1, buf_write1, strlen(buf_write1));
    error_return(re, "write1 error");

    re = write(scr1, buf_write2, strlen(buf_write2));
    error_return(re, "write2 error");

    close(scr1);
    close(scr2);
    return 0;
}

void error_return(int fd, const char *buf)
{
    if (fd == -1)
    {
        perror(buf);
        close(fd);
        exit(-1);
    }
}