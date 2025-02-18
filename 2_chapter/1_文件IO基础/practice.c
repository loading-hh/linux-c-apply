/*
实现一个文件拷贝功能，给定一个源文件，读取源文件中的所有数据，将其写入到另一个目标文件中。
给定一个文件，计算它的大小并打印出来。
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int re, scr, target, num1, num2;
    char a[20] = "\0";
    char scr_path[20] = "\0";
    char target_path[20] = "\0";

    sprintf(scr_path, "./%s", argv[1]);
    sprintf(target_path, "./%s", argv[2]);
    printf("%s\r\n%s\r\n", scr_path, target_path);

    // 打开scr文件
    scr = open(scr_path, O_RDONLY);
    if (scr == -1)
    {
        printf("文件1打开失败\r\n");
        close(scr);
        return -1;
    }
    // 打开target文件
    target = open(target_path, O_WRONLY);
    if (re == -1)
    {
        printf("文件2打开失败\r\n");
        close(scr);
        close(target);
        return -1;
    }
    // 得到scr文件大小
    num1 = lseek(scr, 0, SEEK_END);
    if (num1 == -1)
    {
        printf("得到文件scr大小失败\r\n");
        close(scr);
        close(target);
        return -1;
    }
    printf("文件大小为%d\r\n", num1);
    // 将scr文件的位置偏移量移到文件起始处
    num2 = lseek(scr, -num1, SEEK_END);
    if (num2 == -1)
    {
        printf("lssek失败\r\n");
        close(scr);
        close(target);
        return -1;
    }
    // 从scr文件中读num1个字节的数据
    re = read(scr, a, num1);
    if (re == -1)
    {
        printf("读文件失败\r\n");
        close(scr);
        close(target);
        return -1;
    }
    printf("写入的字符串为：%s\r\n", a);
    // 对target文件中写入num1个数据
    re = write(target, a, num1);
    if (re == -1)
    {
        printf("写文件失败\r\n");
        close(scr);
        close(target);
        return -1;
    }
    close(scr);
    close(target);
    return 0;
}
