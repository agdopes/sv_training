#include "hal_gpio.h"
#include "hal_uart.h"
#include "bsp_stm32g0.h"

static void uart_print(uint32_t idx, const char *str)
{
    while (*str)
    {
        hal_uart_write_byte(idx, (uint8_t)*str++);
    }
}

int main(void)
{
    /* 1. Configure GPIO pins for USART2 TX/RX (alternate function) */
    for (int i = 0; i < NUM_GPIO_PINS; i++)
    {
        hal_gpio_init(i);
    }

    /* 2. Initialise UART (USART2, 115200, 8N1) */
    hal_uart_init(USART2_IDX);

    /* 3. Print hello world, then echo received characters */
    uart_print(USART2_IDX, "Hello, World!\r\n");

    while (1)
    {
        uint8_t ch;
        hal_uart_read_byte(USART2_IDX, &ch);
        hal_uart_write_byte(USART2_IDX, ch);   /* echo back */
    }

    return 0;
}
