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

    // 1000是loading这个用户的的id与用户所属组的id
    re = chown("../scr.txt", 0, 0);
    error_return(re, "chown error", -1);

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