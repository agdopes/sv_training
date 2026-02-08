/**
 * @file main.c
 * @brief Main application entry point
 * 
 * Simple demonstration application that prints "Hello World" via UART.
 */

#include "../bsp/bsp.h"

/**
 * @brief Main application entry point
 * 
 * Initializes board hardware and prints "Hello World" message via UART.
 * 
 * @return Never returns (embedded system)
 */
int main(void) {
    // Initialize board hardware
    bsp_init();
    
    // Print message via UART
    const char* message = "Hello World\r\n";
    bsp_uart_write((const uint8_t*)message, 13);
    
    // Keep program running
    while(1) {
        // Application idle loop
    }
    
    return 0;
}