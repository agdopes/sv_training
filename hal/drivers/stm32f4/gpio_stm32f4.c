#include "driver_gpio.h"
#include "stm32f4xx.h"
#include "stm32f411xe.h"

void drivers_gpio_init(void* port, uint32_t pin, uint32_t mode, uint32_t alternate) {
    GPIO_TypeDef* gpio = (GPIO_TypeDef*)port;
    // Set mode
    gpio->MODER &= ~(0x3 << (pin * 2));
    gpio->MODER |= (mode << (pin * 2));
    // Set alternate function if needed
    if (mode == 0x02U) {
        if (pin < 8) {
            gpio->AFR[0] &= ~(0xF << (pin * 4));
            gpio->AFR[0] |= (alternate << (pin * 4));
        } else {
            gpio->AFR[1] &= ~(0xF << ((pin - 8) * 4));
            gpio->AFR[1] |= (alternate << ((pin - 8) * 4));
        }
    }
}