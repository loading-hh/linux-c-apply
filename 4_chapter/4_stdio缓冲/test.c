/*
    setvbuf中的size参数与标准库的实现，如glibc密切相关。
    如果size小于128字节，glibc可能会认为缓冲区太小，无法有效减少系统调用次数，一次忽略全缓冲模式，
    退化为行缓冲或五缓冲模式，一般为行缓冲。
    如果size大于等于128字节，会启用全缓冲模式。
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

void error_return(int fd, const char *buf, int d);
int main(void)
{
    int scr, re;
    static char buf[1024];

    re = setvbuf(stdout, buf, _IOFBF, 128);
    error_return(re, "setvbuf error", 0);
    int i = 13;
    while (i--)
        printf("asdasdasd\n");

    // fflush(stdout);
    // fclose(stdout);
    while (1)
    {
    }

    return 0;
}

void error_return(int fd, const char *buf, int d)
{
    if (fd != d)
    {
        perror(buf);
        // fclose(fd);
        exit(-1);
    }
}