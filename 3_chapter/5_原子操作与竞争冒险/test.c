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
    char buf_read[20] = "\0";
    int scr, re;

    scr = open("./scr.txt", O_RDONLY);
    error_return(scr, "open error");

    re = pread(scr, buf_read, 20, 10);
    error_return(re, "pread error");
    printf("%s\r\n", buf_read);

    re = lseek(scr, 0, SEEK_CUR);
    error_return(re, "lseek error");

    printf("lseek count:%d\r\n", re);

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
