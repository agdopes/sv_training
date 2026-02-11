/**
 * @file bsp.c
 * @brief Board Support Package implementation for STM32F411RE Nucleo
 * 
 * @addtogroup BSP
 * @{
 */

#include "bsp.h"
#include "../drivers/inc/hal_uart.h"

/**
 * @brief Board UART instance (USART2 on STM32F411RE Nucleo)
 */
#define UART_INSTANCE   1  // USART2

/**
 * @brief Configure GPIO pins for UART
 * 
 * Configures PA2 (TX) and PA3 (RX) as alternate function 7 (USART2)
 * for STM32F411RE Nucleo board.
 */
static void configure_uart_gpio(void) {
    // Enable GPIOA clock
    volatile uint32_t* RCC_AHB1ENR = (volatile uint32_t*)0x40023830;
    *RCC_AHB1ENR |= (1 << 0);  // GPIOA
    
    // Configure PA2 (TX) and PA3 (RX) as alternate function
    volatile uint32_t* GPIOA_MODER = (volatile uint32_t*)0x40020000;
    volatile uint32_t* GPIOA_AFRL = (volatile uint32_t*)0x40020020;
    
    // Set PA2 and PA3 to alternate function mode (10)
    *GPIOA_MODER &= ~((3 << 4) | (3 << 6));
    *GPIOA_MODER |= ((2 << 4) | (2 << 6));
    
    // Set alternate function 7 (USART2)
    *GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12));
    *GPIOA_AFRL |= ((7 << 8) | (7 << 12));
}

/**
 * @brief Initialize board hardware
 * 
 * Configures GPIO and initializes UART for board operation.
 */
void bsp_init(void) {
    // Configure GPIO for UART
    configure_uart_gpio();
    
    // Configure UART: 115200 baud, 8N1
    struct uart_config uart_config = {
        .baudrate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0  // None
    };
    
    // Initialize UART HAL
    hal_uart_init(UART_INSTANCE, &uart_config);
}

/**
 * @brief Write data to UART
 * @param data Pointer to data buffer
 * @param size Number of bytes to write
 * @return UART_OK on success, error code otherwise
 */
uint8_t bsp_uart_write(const uint8_t* data, uint16_t size) {
    return hal_uart_write(UART_INSTANCE, data, size);
}

/** @} */ // end of BSP group
