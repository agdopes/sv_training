#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

typedef struct {
    uint32_t baudrate;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t parity;
} hal_uart_config_t;

void hal_uart_init(uint32_t instance, const hal_uart_config_t* config);
void hal_uart_deinit(uint32_t instance);
void hal_uart_write(uint32_t instance, const uint8_t* data, uint16_t size);
void hal_uart_read(uint32_t instance, uint8_t* data, uint16_t size);


void hal_uart_board_init(void);

#endif // HAL_UART_H