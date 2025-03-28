#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>

#define DELETE_UNLINK 1
#define DELETE_REMOVE 0
#define RENAME 0
void error_return(int fd, const char *buf, int re);
int main(void)
{
    int re;

#if DELETE_UNLINK

    int fd;

    fd = open("./a.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    error_return(fd, "open error", -1);
    sleep(2);
    re = unlink("./a.txt");
    error_return(re, "unlink error", -1);
    close(fd);
#endif

#if DELETE_REMOVE

    int fd;

    fd = open("./a.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    error_return(fd, "open error", -1);
    sleep(2);
    re = remove("./a.txt");
    error_return(re, "remove error", -1);
    close(fd);
#endif

#if RENAME

    int fd;

    fd = open("./a.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    error_return(fd, "open error", -1);
    sleep(2);
    re = rename("./a.txt", "./b.txt");
    error_return(re, "rename error", -1);
    close(fd);
#endif

    return 0;
}

void error_return(int fd, const char *buf, int re)
{
    if (fd == re)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}