/*
    磁盘中最小存储单位是"扇区(sector)",每个扇区存储512个字节(0.5KB).
    而操作系统读取硬盘的时候不会一个扇区这样读,是一次读取多个扇区,即一次读取一个"块(block)".
    这种由多个扇区组成的"块",是文件存储的最小单位."块"的通常是连续的八个扇区组成一个块,故一个块一般是4KB.
    du -h命令是返回的文件最小存储大小,以块大小为单位,返回的是文件大小不包括空洞大小,就算剩下的文件大小不足一块,还是返回块的大小.
    而ls命令返回的是文件包括空洞所占字节数.
*/
#include <stdio.h>
#include <error.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    char buf[4096];
    int scr, re;
    // 打开scr文件
    scr = open("./scr.txt", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (scr == -1)
    {
        perror("error");
        close(scr);
        return -1;
    }
    // 调整文件的位置偏移量，从而可以制造空洞文件。
    re = lseek(scr, 4096, SEEK_SET);
    if (re == -1)
    {
        perror("lseek error");
        close(scr);
        return -1;
    }
    // 往scr文件中随便写入东西，以造成空洞文件。
    re = write(scr, buf, 4096);
    if (re == -1)
    {
        perror("write error");
        close(scr);
        return -1;
    }

    close(scr);
    return 0;
}
