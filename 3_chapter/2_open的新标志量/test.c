#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>

void error_return(int fd, const char *buf);
int main(void)
{
    const char buf_write[] = "hollo word\r\n";
    char buf_read[30] = "\0";
    int scr, re;
    scr = open("./scr.txt", O_RDWR | O_APPEND);
    if (scr == -1)
    {
        error_return(scr, "open error");
        return -1;
    }

    re = read(scr, buf_read, 10);
    if (re == -1)
    {
        error_return(re, "read error");
        return -1;
    }

    re = lseek(scr, 2, SEEK_SET);
    if (re == -1)
    {
        error_return(re, "lseek error");
        return -1;
    }

    re = write(scr, buf_write, strlen(buf_write));
    if (re == -1)
    {
        error_return(re, "write error");
        return -1;
    }

    close(scr);
    return 0;
}

void error_return(int fd, const char *buf)
{
    perror(buf);
    close(fd);
}