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
    const char buf_write3[] = "hello word3\r\n";
    int scr, fd1, fd2, re;

    scr = open("./scr.txt", O_WRONLY | O_APPEND);
    error_return(scr, "open1 error");
    // 复制的文件描述符的位置偏移量与原文件描述符的位置偏移量是一样的，也会随着write，read的使用而改变。
    fd1 = dup(scr);
    error_return(fd1, "dup error");

    fd2 = dup2(scr, 6);
    error_return(fd2, "dup2 error");
    printf("%d\r\n", fd2);

    re = write(scr, buf_write1, strlen(buf_write1));
    error_return(re, "write1 error");
    re = write(fd1, buf_write2, strlen(buf_write2));
    error_return(re, "write2 error");
    re = write(fd2, buf_write3, strlen(buf_write3));
    error_return(re, "write3 error");

    close(scr);
    close(fd1);
    close(fd2);
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
