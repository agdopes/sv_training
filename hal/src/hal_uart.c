/**
 * @file hal_uart.c
 * @brief UART HAL implementation for STM32G0B1 (polling, 8N1)
 */

#include "hal_uart.h"
#include "driver_uart.h"
#include "board_config.h"

/* ── Board UART configuration table ─────────────────────────────────── */
uart_config_t uartConfig[] = {
    [0] = {
        .instance = BOARD_UART_INSTANCE - 1U,  /* 0-based index */
        .baudrate = BOARD_UART_BAUDRATE,
        .sysclk   = BOARD_SYSCLK_HZ,
    },
};

/* ── Driver implementations ──────────────────────────────────────────── */

static uint8_t stm32_uart_init(uint32_t index)
{
    uart_hw_init(uartConfig[index].instance,
                 uartConfig[index].baudrate,
                 uartConfig[index].sysclk);
    return UART_OK;
}

static uint8_t stm32_uart_write_byte(uint32_t index, uint8_t data)
{
    uart_hw_write_byte(uartConfig[index].instance, data);
    return UART_OK;
}

static uint8_t stm32_uart_read_byte(uint32_t index, uint8_t *data)
{
    *data = uart_hw_read_byte(uartConfig[index].instance);
    return UART_OK;
}

static uint8_t stm32_uart_write_buf(uint32_t index, const uint8_t *buf, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        uart_hw_write_byte(uartConfig[index].instance, buf[i]);
    }
    return UART_OK;
}

/* ── Interface table ─────────────────────────────────────────────────── */

static const struct uart_hal_interface stm32_uart_interface = {
    .init       = stm32_uart_init,
    .write_byte = stm32_uart_write_byte,
    .read_byte  = stm32_uart_read_byte,
    .write_buf  = stm32_uart_write_buf,
};

const struct uart_hal_interface *hal_uart_get_interface(void)
{
    return &stm32_uart_interface;
}
