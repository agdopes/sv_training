#include "hal_rcc.h"
#include "driver_rcc.h"

void hal_rcc_enable_gpio(uint32_t port) {
    drivers_rcc_enable_gpio(port);
}

void hal_rcc_enable_uart(uint32_t instance) {
    drivers_rcc_enable_uart(instance);
}