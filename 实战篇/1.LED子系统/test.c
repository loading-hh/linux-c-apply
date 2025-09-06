#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PWR_LDE_PATH "/home/jetson/sys/class/leds/pwr/brightness"
int main(void)
{
    FILE *pwr_fd;

    printf("This is the led demo\r\n");
    pwr_fd = fopen(PWR_LDE_PATH, "w");
    if (pwr_fd == NULL)
    {
        printf("fopen error\r\n");
        return -1;
    }

    while (1)
    {
        // 电源灯亮
        fwrite("1", 1, 1, pwr_fd);
        fflush(pwr_fd);
        // 延时1秒
        sleep(1);
        // 电源灯灭
        fwrite("0", 1, 1, pwr_fd);
        fflush(pwr_fd);
        // 延时1秒
        sleep(1);
    }
    // 电源灯亮
    fwrite("1", 1, 1, pwr_fd);
    fflush(pwr_fd);
    // 关闭文件
    fclose(pwr_fd);

    return 0;
}