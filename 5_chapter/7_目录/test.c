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

#define CREAT 0
#define DELETE 0
#define READ 0
#define CURRENT_WORK_DIR 1
void error_return(int fd, const char *buf, int re);
int main(void)
{
    int re;
#if CREAT

    re = mkdir("./dir", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    error_return(re, "mkdir error", -1);
#endif

#if DELETE

    re = rmdir("./dir");
    error_return(re, "rmdir error", -1);
#endif

#if READ
    DIR *drip = NULL;
    struct dirent *rent;

    drip = opendir("../7_目录");
    if (drip == NULL)
    {
        printf("opendir error\r\n");
        exit(-1);
    }

    errno = 0;
    while (rent = readdir(drip))
        printf("%s %ld\r\n", rent->d_name, rent->d_ino);
    if (errno != 0)
    {
        perror("readdir error");
        re = closedir(drip);
        exit(-1);
    }
    else
        printf("End of directory\r\n");
#endif

#if CURRENT_WORK_DIR
    char buf[100];
    char *ptr = NULL;

    memset(buf, 0, sizeof(buf));
    ptr = getcwd(buf, sizeof(buf));
    if (ptr == NULL)
    {
        perror("getcwd error\r\n");
        exit(-1);
    }
    printf("当前工作目录:%s\r\n", ptr);

    re = chdir("../6_链接文件");
    error_return(re, "chdir error", -1);

    memset(buf, 0, sizeof(buf));
    ptr = getcwd(buf, sizeof(buf));
    if (ptr == NULL)
    {
        perror("getcwd error\r\n");
        exit(-1);
    }
    printf("当前工作目录:%s\r\n", buf);
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