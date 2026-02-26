#ifndef BSP_STM32G0_H
#define BSP_STM32G0_H

#include "hal_gpio.h"
#include "hal_uart.h"

/* ── GPIO pin index table ─────────────────────────────────────────── */

typedef enum
{
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF
} gpio_port_t;

typedef enum
{
    PIN_RESET = 0,
    PIN_SET
} pin_state_t;

typedef enum
{
    UART_TX_PIN = 0,
    UART_RX_PIN,
    NUM_GPIO_PINS
} gpio_index_t;

/* PA2 = USART2_TX (AF1), PA3 = USART2_RX (AF1) */
gpio_config gpioConfig[] = {
    [UART_TX_PIN] = { .pin = PIN2, .port = GPIO_PORTA, .pinState = 0,
                      .alternate_mode = AF1,
                      .pinConfig = (ALTERNATE_MODE | LOW_SPEED | NO_PULL) },
    [UART_RX_PIN] = { .pin = PIN3, .port = GPIO_PORTA, .pinState = 0,
                      .alternate_mode = AF1,
                      .pinConfig = (ALTERNATE_MODE | LOW_SPEED | NO_PULL) },
};

/* ── UART index ───────────────────────────────────────────────────── */
#define USART2_IDX   0   /* index into uartConfig[] */

#endif /* BSP_STM32G0_H */
