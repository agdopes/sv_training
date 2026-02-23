#include "hal_gpio.h"
#include "driver_gpio.h"

void hal_gpio_init(void* port, uint32_t pin, uint32_t mode, uint32_t alternate) {
    drivers_gpio_init(port, pin, mode, alternate);
}