/**
 * @file bsp.h
 * @brief Board Support Package for STM32F411RE Nucleo
 * 
 * Provides board-specific abstractions and configurations.
 * Wraps hardware HAL with board-specific knowledge (pin assignments, etc).
 * 
 * @defgroup BSP Board Support Package
 * @{
 */

#ifndef BSP_H
#define BSP_H

#include <stdint.h>

/**
 * @brief Initialize board hardware
 * 
 * Configures GPIO pins and initializes peripherals for the board.
 * Must be called before using any other BSP functions.
 */
void bsp_init(void);

/**
 * @brief Write data to UART
 * @param data Pointer to data buffer
 * @param size Number of bytes to write
 * @return UART_OK on success, error code otherwise
 */
uint8_t bsp_uart_write(const uint8_t* data, uint16_t size);

/** @} */ // end of BSP group

#endif // BSP_H
