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

void error_return(int fd, const char *buf, int re);
int main(void)
{
    int re;
    struct stat st;

    // access是检查执行进程的用户对文件有何权限。
    // 可以先用stat来看看文件属于哪个用户和文件属于哪个用户组。
    // re = access("../scr.txt", F_OK | X_OK | R_OK | W_OK);
    // error_return(re, "access error", -1);

    // chmod是改变文件权限，但是要么执行进程的用户是超级用户， 要么是
    // 执行进程的用户与文件所属用户一样，而不是用户组一样。
    // re = chmod("../scr.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    // error_return(re, "chmod error", -1);

    re = umask(S_IWOTH | S_IXOTH);
    printf("之前的umask是%o\r\n", re);
    printf("现在的umask是%o\r\n", S_IWOTH | S_IXOTH);

    return 0;
}

void error_return(int fd, const char *buf, int re)
{
    if (fd == re)
    {
        perror(buf);
        close(fd);
        exit(-1);
    }
}