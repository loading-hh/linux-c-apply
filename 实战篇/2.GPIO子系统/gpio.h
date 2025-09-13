#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO_INDEX '216'
int gpio_init(void);
int gpio_deinit(void);
int gpio_low(void);
int gpio_high(void);

#endif