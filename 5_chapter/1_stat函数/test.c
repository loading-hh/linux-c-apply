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

void error_return(int fd, const char *buf, int d);
int main(void)
{
    int re;
    struct stat st;
    re = stat("../scr.txt", &st);
    error_return(re, "stat error", -1);

    printf("文件节点编号为：%ld\r\n", st.st_ino);
    printf("文件大小为：%ld字节\r\n", st.st_size);

    if (S_ISSOCK(st.st_mode))
        printf("文件为套接字文件\r\n");
    else if (S_ISREG(st.st_mode))
        printf("文件为普通文件\r\n");
    else if (S_ISDIR(st.st_mode))
        printf("文件为目录\r\n");
    else if (S_ISCHR(st.st_mode))
        printf("文件为字符设备文件\r\n");
    else if (S_ISBLK(st.st_mode))
        printf("文件为块设备文件\r\n");
    else if (S_ISFIFO(st.st_mode))
        printf("文件为管道文件\r\n");
    else if (S_ISLNK(st.st_mode))
        printf("文件为链接文件\r\n");

    if ((st.st_mode & S_IROTH) && (st.st_mode & S_IWOTH))
        printf("此文件其他用户有可读可写权限\r\n");
    else
        printf("文件类型与权限编码为0x%x\r\n", st.st_mode);

    return 0;
}

void error_return(int fd, const char *buf, int d)
{
    if (fd == d)
    {
        perror(buf);
        close(fd);
        exit(-1);
    }
}