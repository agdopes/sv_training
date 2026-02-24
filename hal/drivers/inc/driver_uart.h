#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include <stdint.h>

void driver_uart_init(uint32_t instance, uint32_t baudrate);
void driver_uart_deinit(uint32_t instance);
void driver_uart_write(uint32_t instance, const uint8_t* data, uint16_t size);
void driver_uart_read(uint32_t instance, uint8_t* data, uint16_t size);

#endif // DRIVER_UART_H