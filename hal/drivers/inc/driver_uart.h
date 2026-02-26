#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include <stdint.h>

/**
 * @brief Enable the peripheral clock for a USART instance.
 * @param instance  0-based USART index (0=USART1, 1=USART2, ...)
 */
void uart_hw_enable_clock(uint32_t instance);

/**
 * @brief Configure and enable a USART for 8N1 polling operation.
 * @param instance  0-based USART index
 * @param baudrate  Desired baud rate (e.g. 115200)
 * @param sysclk    Peripheral clock frequency in Hz
 */
void uart_hw_init(uint32_t instance, uint32_t baudrate, uint32_t sysclk);

/**
 * @brief Blocking transmit of one byte.
 * @param instance  0-based USART index
 * @param data      Byte to send
 */
void uart_hw_write_byte(uint32_t instance, uint8_t data);

/**
 * @brief Blocking receive of one byte.
 * @param instance  0-based USART index
 * @return Received byte
 */
uint8_t uart_hw_read_byte(uint32_t instance);

#endif /* DRIVER_UART_H */
