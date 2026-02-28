/**
 * @file uart_stm32g0.c
 * @brief Low-level USART driver for STM32G0B1 (polling, 8N1)
 */

#include "driver_uart.h"
#include "stm32g0xx.h"

static USART_TypeDef *UARTx[] = { USART1, USART2, USART3, USART4 };

void uart_hw_enable_clock(uint32_t instance)
{
	switch (instance)
	{
		case 0: /* USART1*/
			RCC->APBENR2 |= (1U << 14);
			break;
		case 1: /* USART2*/
			RCC->APBENR1 |= (1U << 17);
			break;
		case 2: /* USART3*/
			RCC->APBENR1 |= (1U << 18);
			break;
		case 3: /* USART4*/
			RCC->APBENR1 |= (1U << 19);
			break;
		default:
			break;
	}
}

void uart_hw_init(uint32_t instance, uint32_t baudrate, uint32_t sysclk)
{
	USART_TypeDef *uart = UARTx[instance];

	uart_hw_enable_clock(instance);

	/* Disable USART before configuration */
	uart->CR1 &= ~USART_CR1_UE;

	/* Set baud rate: BRR = FCLK / baud (OVER8=0, 16x oversampling) */
	uart->BRR = (uint32_t)(sysclk / baudrate);

	/* Enable TX + RX + USART */
	uart->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void uart_hw_write_byte(uint32_t instance, uint8_t data)
{
	USART_TypeDef *uart = UARTx[instance];

	/* Wait until TXE (transmit data register empty) */
	while (!(uart->ISR & USART_ISR_TXE_TXFNF))
		;
	uart->TDR = data;
}

uint8_t uart_hw_read_byte(uint32_t instance)
{
	USART_TypeDef *uart = UARTx[instance];

	/* Wait until RXNE (read data register not empty) */
	while (!(uart->ISR & USART_ISR_RXNE_RXFNE))
		;
	return (uint8_t)(uart->RDR & 0xFFU);
}
