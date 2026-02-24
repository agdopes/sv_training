#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

#define GPIO_MODE_INPUT      0x00U
#define GPIO_MODE_OUTPUT     0x01U
#define GPIO_MODE_AF         0x02U
#define GPIO_MODE_ANALOG     0x03U

void hal_gpio_init(void* port, uint32_t pin, uint32_t mode, uint32_t alternate);

#endif // HAL_GPIO_H