#ifndef DRIVERS_RCC_H
#define DRIVERS_RCC_H

#include <stdint.h>

void drivers_rcc_enable_gpio(uint32_t port);
void drivers_rcc_enable_uart(uint32_t instance);

#endif // DRIVERS_RCC_H