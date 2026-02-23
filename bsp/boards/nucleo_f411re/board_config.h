/**
 * @file board_config.h
 * @brief Board-specific configuration for STM32F411RE Nucleo
 */
#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// Clock Config
#define BOARD_SYSCLK_HZ         84000000
#define BOARD_AHB_PRESCALER     1
#define BOARD_APB1_PRESCALER    2
#define BOARD_APB2_PRESCALER    1

// Pin Mapping - Application Level Pin IDs
#define BOARD_PIN_LED           0
#define BOARD_PIN_BUTTON        1

// GPIO Config
#define GPIOA                   0
#define ALTERNATE_MODE           0x02U
#define VERY_HIGH_SPEED          0x03U
#define NO_PULL                  0x00U

// LED Config
#define BOARD_LED_PORT          0       // GPIOA
#define BOARD_LED_PIN           5       // PA5

// Button Config
#define BOARD_BUTTON_PORT       2       // GPIOC
#define BOARD_BUTTON_PIN        13      // PC13

// UART Config
#define BOARD_UART_INSTANCE     2       // USART2
#define BOARD_UART_BAUDRATE     115200
#define BOARD_UART_TX_PORT      0       // GPIOA
#define BOARD_UART_TX_PIN       2       // PA2
#define BOARD_UART_RX_PORT      0       // GPIOA
#define BOARD_UART_RX_PIN       3       // PA3

#endif // BOARD_CONFIG_H