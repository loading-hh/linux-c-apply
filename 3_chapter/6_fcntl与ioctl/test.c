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
    int scr, fd1, fd2, flag, re;

    scr = open("./scr.txt", O_RDONLY);
    error_return(scr, "open error");

    fd1 = fcntl(scr, F_DUPFD, 1025);
    error_return(scr, "fcntl F_DUPFD error");
    printf("%d\r\n", fd1);

    fd2 = fcntl(scr, F_DUPFD, 0);
    error_return(scr, "fcntl F_DUPFD error");
    printf("%d\r\n", fd2);

    flag = fcntl(fd1, F_GETFL);
    error_return(flag, "fcntl F_GETFL error");
    printf("0x%x\r\n", flag);

    // 此标志F_SETFL时，成功返回值为0，失败为-1
    re = fcntl(fd1, F_SETFL, O_APPEND);
    error_return(re, "fcntl F_SETFL error");
    printf("0x%x\r\n", re);

    flag = fcntl(fd1, F_GETFL);
    error_return(flag, "fcntl F_GETFL error");
    printf("0x%x\r\n", flag);

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
