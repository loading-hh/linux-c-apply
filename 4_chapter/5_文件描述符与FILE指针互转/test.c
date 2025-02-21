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

// #define __USE_POSIX

void error_return(int fd, const char *buf, int d);
int main(void)
{

    // fdopen测试历程
    int scr, re;
    FILE *file1;
    scr = open("./scr1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    error_return(scr, "open error", -1);

    file1 = fdopen(scr, "w");
    if (file1 == NULL)
    {
        perror("fdopen error");
        close(scr);
        return -1;
    }

    re = fwrite("Hello world\r\n", 1, 13, file1);
    if (re < 12)
    {
        printf("fwrite error\r\n");
        fclose(file1);
        return -1;
    }

    fclose(file1);

    // fileno测试历程
    int r;
    FILE *file2 = NULL;
    file2 = fopen("./scr2.txt", "w");
    if (file2 == NULL)
    {
        perror("fopen error\r\n");
        fclose(file2);
        return -1;
    }

    r = fileno(file2);
    error_return(r, "fileno error", -1);

    r = write(r, "Hello world\r\n", 13);
    error_return(r, "write error", -1);

    close(r);

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