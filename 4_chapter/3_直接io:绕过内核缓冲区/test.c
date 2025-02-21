/*

 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

#define _GNU_SOURCE

void error_return(int fd, const char *buf);
int main(void)
{
    const char buf_write[4096] __attribute((aligned(4096)));
    int scr, re, i = 100000;

    scr = open("./scr.txt", O_WRONLY | O_TRUNC | __O_DIRECT);
    if (scr == -1)
    {
        error_return(scr, "open error");
        return -1;
    }

    lseek(scr, 4096, SEEK_SET);
    // 写入10000 * 4kB的数据
    while (i--)
    {
        re = write(scr, buf_write, strlen(buf_write));
        error_return(re, "write error");
    }

    close(scr);

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