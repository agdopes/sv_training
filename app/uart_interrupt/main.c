/**
 * @file main.c
 * @brief UART Interrupt Mode Application
 * 
 * UART demonstration using interrupt-driven communication.
 */

#include "../../bsp/bsp.h"

/**
 * @brief Main application entry point
 * 
 * Initializes board hardware and prints message via UART using interrupts.
 * 
 * @return Never returns (embedded system)
 */
int main(void) {
    // Initialize board hardware
    bsp_init();
    
    // Print message via UART
    const char* message = "Hello World from UART Interrupt Mode\r\n";
    
    // Write message (using interrupt mode when HAL supports it)
    bsp_uart_write((const uint8_t*)message, 
                   (uint16_t)__builtin_strlen(message));
    
    // Keep program running
    while(1) {
        // Application idle loop
        // TODO: Implement interrupt-driven functionality
    }
    
    return 0;
}
