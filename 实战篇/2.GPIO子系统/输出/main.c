#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gpio.h"

int main(void)
{
    int re = 0;
    char input[10] = "/0";

    re = gpio_init();
    if (re < 0)
    {
        printf("gpio init error num is %d", re);
        return -1;
    }

    while (1)
    {
        scanf("%s", input);

        switch (input[0])
        {
        case '0':
            re = gpio_low();
            if (re < 0)
            {
                printf("gpio low error num is %d", re);
                return -1;
            }
            break;

        case '1':
            re = gpio_high();
            if (re < 0)
            {
                printf("gpio high error num is %d", re);
                return -1;
            }
            break;

        case 'q':
            re = gpio_deinit();
            if (re < 0)
            {
                printf("gpio deinit error num is %d", re);
                return -1;
            }
            return 0;

        default:
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