/**
 * @file main.c
 * @brief UART Polling Mode Application
 * 
 * UART demonstration using polling-based communication.
 */

#include "../../bsp/bsp.h"

/**
 * @brief Main application entry point
 * 
 * Initializes board hardware and prints message via UART.
 * 
 * @return Never returns (embedded system)
 */
int main(void) {
    // Initialize board hardware
    bsp_init();
    
    // Print message via UART
    const char* message = "Hello World from UART Polling Mode\r\n";
    
    // Write message (using polling mode)
    bsp_uart_write((const uint8_t*)message, 
                   (uint16_t)__builtin_strlen(message));
    
    // Keep program running
    while(1) {
        // Application idle loop
    }
    
    return 0;
}