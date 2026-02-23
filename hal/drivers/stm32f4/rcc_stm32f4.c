#include "driver_rcc.h"
#include "stm32f4xx.h"
#include "stm32f411xe.h"

void drivers_rcc_enable_gpio(uint32_t port) {
    // Example: port = 0 for GPIOA, 1 for GPIOB, etc.
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void drivers_rcc_enable_uart(uint32_t instance) {
    // Example: instance = 1 for USART2
    if (instance == 2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
}