/**
 * @file main.c
 * @brief LED Toggle with Button Application
 * 
 * This application demonstrates:
 * - Toggling an LED when a button is pressed
 * - Using only HAL APIs (board-agnostic)
 */

#include "hal_common.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "board_config.h"

// Simple strlen implementation
static uint16_t str_len(const char* str) {
    uint16_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

int main(void) {
    // Initialize HAL (system clocks)
    hal_init();
    
    // Initialize UART for debug output
    hal_uart_init();
    
    const char* welcome = "LED Toggle Application Started\r\n";
    hal_uart_write((const uint8_t*)welcome, str_len(welcome));
    
    // Initialize LED as output
    hal_gpio_init_output(BOARD_PIN_LED);
    hal_gpio_write(BOARD_PIN_LED, HAL_GPIO_LOW);
    
    // Initialize button as input with pull-up
    hal_gpio_init_input(BOARD_PIN_BUTTON, HAL_GPIO_PULL_UP);
    
    uint8_t last_button_state = HAL_GPIO_HIGH;
    
    while(1) {
        // Read button state (active low - pressed = 0)
        uint8_t button_state = hal_gpio_read(BOARD_PIN_BUTTON);
        
        // Detect button press (falling edge)
        if (button_state == HAL_GPIO_LOW && last_button_state == HAL_GPIO_HIGH) {
            // Toggle LED
            hal_gpio_toggle(BOARD_PIN_LED);
            
            // Send debug message
            const char* msg = "LED Toggled!\r\n";
            hal_uart_write((const uint8_t*)msg, str_len(msg));
            
            // Simple debounce delay
            hal_delay_ms(200);
        }
        
        last_button_state = button_state;
    }
    
    return 0;
}
