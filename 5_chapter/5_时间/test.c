/*
 */
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

#define UTIME 1
#define UTIMES 0
#define FUTIMENS 0
#define UTIMENSAT 0

#ifndef __USE_ATFILE
#define __USE_ATFILE
#endif

void error_return(int fd, const char *buf, int re);
int main(void)
{
    int re;
    /* time_t cur_tim;
    time(&cur_tim);
    printf("%ld", cur_tim); */

#if UTIME

    time_t cur_tim1;
    struct utimbuf utm_buf;

    // 访问时间与内容修改时间都设置为现在的时间
    time(&cur_tim1);
    utm_buf.actime = cur_tim1;
    utm_buf.modtime = cur_tim1;

    re = utime("../scr.txt", &utm_buf);
    error_return(re, "utime error", -1);
#endif

#if UTIMES

    time_t cur_tim2;
    struct timeval tmval_arr[2];

    // 访问时间与内容修改时间都设置为现在的时间
    time(&cur_tim2);
    for (int i = 0; i < 2; i++)
    {
        tmval_arr[i].tv_sec = cur_tim2;
        tmval_arr[i].tv_usec = 0;
    }

    re = utimes("../scr.txt", tmval_arr);
    error_return(re, "utimes error", -1);
#endif

#if FUTIMENS
    int fd;
    struct timespec tmsp_arr[2];

    fd = open("../scr.txt", O_RDONLY);

    // 访问时间不变，内容修改时间改为现在
    tmsp_arr[0].tv_nsec = UTIME_OMIT;
    tmsp_arr[1].tv_nsec = UTIME_NOW;

    re = futimens(fd, tmsp_arr);
    error_return(re, "futimens error", -1);
#endif

#if UTIMENSAT
#define path "/home/loading/linux-c-apply/5_chapter/scr.txt"
    int fd;
    struct timespec tmsp_arr[2];

    // 访问时间改为当前时间，内容修改时间不变
    tmsp_arr[0].tv_nsec = UTIME_OMIT;
    tmsp_arr[1].tv_nsec = UTIME_NOW;

    re = utimensat(-1, path, tmsp_arr, 0);
    error_return(re, "utimensat error", -1);
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