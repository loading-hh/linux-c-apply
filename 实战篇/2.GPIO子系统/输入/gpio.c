#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gpio.h"

int gpio_init(void)
{
    int fd = 0;
    char gpio_path[100] = "/0";

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
        return -1;

    write(fd, GPIO_INDEX, strlen(GPIO_INDEX));
    close(fd);

    sprintf(gpio_path, "/sys/class/gpio/gpio%s/direction", GPIO_INDEX);
    fd = open(gpio_path, O_WRONLY);
    if (fd < 0)
        return -2;

    write(fd, "out", strlen("out"));
    close(fd);

    return 0;
}

int gpio_deinit(void)
{
    int fd = 0;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
        return -1;

    write(fd, GPIO_INDEX, strlen(GPIO_INDEX));
    close(fd);

    return 0;
}

int gpio_low(void)
{
    int fd = 0;
    char gpio_path[100] = "\0";

    sprintf(gpio_path, "/sys/class/gpio/gpio%s/value", GPIO_INDEX);
    fd = open(gpio_path, O_WRONLY);
    if (fd < 0)
        return -1;

    write(fd, "0", strlen("0"));
    close(fd);

    return 0;
}

int gpio_high(void)
{
    int fd = 0;
    char gpio_path[100] = "\0";

    sprintf(gpio_path, "/sys/class/gpio/gpio%s/value", GPIO_INDEX);
    fd = open(gpio_path, O_WRONLY);
    if (fd < 0)
        return -1;

    write(fd, "1", strlen("1"));
    close(fd);

    return 0;
}