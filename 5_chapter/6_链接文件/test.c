#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>

#define HARD_LINK 0
#define SYM_LINK 0
#define READ_SYM_LINK 1
void error_return(int fd, const char *buf, int re);
int main(void)
{
    int re;

#if HARD_LINK

    re = link("./test.c", "./hard_link");
    error_return(re, "link error", -1);
#endif

#if SYM_LINK

    re = symlink("./test.c", "./sym_link");
    error_return(re, "symlink error", -1);
#endif

#if READ_SYM_LINK

    char buf[30];

    memset(buf, 0, sizeof(buf));
    re = readlink("./sym_link", buf, 30);
    error_return(re, "read symlink error", -1);
    printf("软链接文件中的存储的源文件路径长度为%d个字节\r\n", re);
    printf("%s\r\n", buf);
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