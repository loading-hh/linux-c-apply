#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int re;
    int create;
    char a[20] = "\0";
    create = open("./scr.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (create == -1)
    {
        printf("文件打开失败\r\n");
        close(create);
        return -1;
    }

    re = write(create, "Hollow word\r\n", 13);
    if (re == -1)
    {
        printf("写文件失败\r\n");
        close(create);
        return -1;
    }
    printf("write %d bytes OK!\r\n", re);

    // 在用完write函数后，已打开文件的位置偏移量不在起始处
    // 所以要用lseek函数来将位置偏移量移到文件起始处。若文件没有东西那么会报错。
    re = lseek(create, 0, SEEK_SET);
    if (re == -1)
    {
        printf("lseek失败\r\n");
        close(create);
        return -1;
    }

    re = read(create, a, 13);
    if (re == -1)
    {
        printf("读文件失败\r\n");
        close(create);
        return -1;
    }
    printf("read %d bytes OK!\r\n", re);
    printf("%s", a);
    close(create);

    return 0;
}