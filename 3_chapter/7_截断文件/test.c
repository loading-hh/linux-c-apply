#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include <sys/types.h>

void error_return(int fd, const char *buf);
int main(void)
{
    int scr, re;

    scr = open("./scr1.txt", O_WRONLY);
    error_return(scr, "open error");

    // 只有当open有写操作时才能正确截断，但当open没有写操作时truncate也不会运行错误，没有错误返回的都是0.
    re = truncate("./scr2.txt", 10);
    error_return(re, "truncate error");

    re = ftruncate(scr, 2);
    error_return(re, "ftruncate error");

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
