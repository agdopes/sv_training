#ifndef HAL_RCC_H
#define HAL_RCC_H

#include <stdint.h>

void hal_rcc_enable_gpio(uint32_t port);
void hal_rcc_enable_uart(uint32_t instance);

#endif // HAL_RCC_H