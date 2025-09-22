#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gpio.h"

extern int value_fd;
int main(void)
{
    int re = 0;
    char input[10] = "/0";
    char input_value = '/0';

    re = gpio_init();
    if (re < 0)
    {
        printf("gpio init error num is %d", re);
        return -1;
    }

    re = gpio_input();
    if (re < 0)
    {
        printf("gpio input error num is %d", re);
        return -1;
    }

    while (1)
    {
        scanf("%s", input);

        switch (input[0])
        {
        case 'r':
            re = read(value_fd, input_value, 1);
            if (re < 0)
            {
                printf("gpio read error\r\n");
                return -1;
            }
            printf("input value is %c\r\n", input_value);

            // 移动文件位置偏移量
            re = lseek(value_fd, 0, SEEK_SET);
            if (re < 0)
            {
                printf("lseek error\r\n");
                return -1;
            }
            printf("input value is %c\r\n", input_value);
            break;

        case 'q':
            close(value_fd);
            re = gpio_deinit();
            if (re < 0)
            {
                printf("gpio deinit error num is %d", re);
                return -1;
            }
            return 0;

        default:
            close(value_fd);
            re = gpio_deinit();
            if (re < 0)
            {
                printf("gpio deinit error num is %d", re);
                return -1;
            }
            return 0;
        }
    }

    return 0;
}