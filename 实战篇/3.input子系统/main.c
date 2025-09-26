#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define EVENT_PATH "/dev/input/event1"
int main(void)
{
    int fd = 0, re = 0;
    struct input_event events = {0};

    fd = open(EVENT_PATH, O_RDONLY);
    if (fd < 0)
    {
        printf("open event file error\r\n");
        return -1;
    }

    printf("start read events\r\n");
    while (1)
    {
        re = read(fd, &events, sizeof(struct input_event));
        if (re < 0)
        {
            printf("read file error\r\n");
            return -2;
        }
        printf("type=%d code=%d value=%d\r\n", events.type, events.code, events.value);
    }
}