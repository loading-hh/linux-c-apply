/*
    同一时间只取消注释一个，通过time ./test来看看将数据从内核缓冲区移到硬件
    中与只将数据移到内核缓冲区程序运行时间会有什么不同.
    要注意__O_DSYNC与__O_SYNC是在每一个write只有调用fdatasync或fsync,而不是在所有
    write之后调用fdatasync或fsync.
 */
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
    int scr, re, i = 4096;
    const char buf_write[4096];

    // scr = open("./scr.txt", O_WRONLY | O_TRUNC | __O_DSYNC);
    scr = open("./scr.txt", O_WRONLY | O_TRUNC);
    error_return(scr, "open error");

    // 写入4096 * 4kB的数据
    while (i--)
    {
        re = write(scr, buf_write, strlen(buf_write));
        error_return(re, "write error");
        // fsync(scr);
        // fdatasync(scr);
        // sync();
    }

    // fsync(scr);
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