#include "hal_uart.h"
#include <stdint.h>

int main(void) {
    hal_uart_board_init();

    const char msg[] = "Hello world!\r\n";
    hal_uart_write(2, (const uint8_t*)msg, sizeof(msg) - 1);

    while (1) {}
    return 0;
}