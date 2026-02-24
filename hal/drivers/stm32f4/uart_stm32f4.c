#include "driver_uart.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f411xe.h"

void driver_uart_init(uint32_t instance, uint32_t baudrate) {
    if (instance != 2) return;

    USART2->CR1 = 0;
    USART2->BRR = SystemCoreClock / baudrate;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void driver_uart_deinit(uint32_t instance) {
    if (instance != 2) return;
    USART2->CR1 = 0;
}

void driver_uart_write(uint32_t instance, const uint8_t* data, uint16_t size) {
    if (instance != 2) return;
    for (uint16_t i = 0; i < size; ++i) {
        while (!(USART2->SR & USART_SR_TXE));
        USART2->DR = data[i];
    }
}

void driver_uart_read(uint32_t instance, uint8_t* data, uint16_t size) {
    if (instance != 2) return;
    for (uint16_t i = 0; i < size; ++i) {
        while (!(USART2->SR & USART_SR_RXNE));
        data[i] = USART2->DR;
    }
}