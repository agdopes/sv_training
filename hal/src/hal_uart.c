#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "driver_uart.h"
#include "board_config.h"

void hal_uart_board_init(void) {
    hal_rcc_enable_gpio(BOARD_UART_TX_PORT);
    hal_rcc_enable_gpio(BOARD_UART_RX_PORT);
    hal_rcc_enable_uart(BOARD_UART_INSTANCE);

    hal_gpio_init((void*)(0x40020000U + 0x400 * BOARD_UART_TX_PORT), BOARD_UART_TX_PIN, GPIO_MODE_AF, 7);
    hal_gpio_init((void*)(0x40020000U + 0x400 * BOARD_UART_RX_PORT), BOARD_UART_RX_PIN, GPIO_MODE_AF, 7);

    hal_uart_config_t cfg = {
        .baudrate = BOARD_UART_BAUDRATE,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0
    };
    hal_uart_init(BOARD_UART_INSTANCE, &cfg);
}

void hal_uart_init(uint32_t instance, const hal_uart_config_t* config) {
    driver_uart_init(instance, config->baudrate);
}

void hal_uart_deinit(uint32_t instance) {
    driver_uart_deinit(instance);
}

void hal_uart_write(uint32_t instance, const uint8_t* data, uint16_t size) {
    driver_uart_write(instance, data, size);
}

void hal_uart_read(uint32_t instance, uint8_t* data, uint16_t size) {
    driver_uart_read(instance, data, size);
}