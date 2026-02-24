#include "hal_gpio.h"


typedef enum
{
	GPIO_PORTA = 0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF
}gpio_port;

typedef enum
{
	PIN_RESET = 0,
	PIN_SET

}pin_state;

typedef enum
{
	LED_PIN = 0,
	BUTTON_PIN,
	UART_TX,
	UART_RX,
	NUM_PINS
}gpio_index_t;

gpio_config gpioConfig[] = {
	[LED_PIN]={ .pin = PIN5, .port = GPIO_PORTA, .pinState = PIN_RESET,.pinConfig =	(OUTPUT_MODE | LOW_SPEED | NO_PULL)},
	[BUTTON_PIN]={ .pin = PIN13, .port = GPIO_PORTC, .pinState = PIN_RESET,.pinConfig =	(INPUT_MODE | LOW_SPEED | NO_PULL)},
	[UART_TX]={ .pin = PIN2, .port = GPIO_PORTA, .pinState = PIN_RESET, .alternate_mode = AF1, .pinConfig =	(ALTERNATE_MODE | LOW_SPEED | NO_PULL)},
	[UART_RX]={ .pin = PIN3, .port = GPIO_PORTA, .pinState = PIN_RESET, .alternate_mode = AF1,  .pinConfig = (ALTERNATE_MODE | LOW_SPEED | NO_PULL)}
};

