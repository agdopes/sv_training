/**
 * @file hal_gpio_stm32G0B1.c
 * @brief GPIO HAL implementation for STM32G0B1RE
 * Provides hardware-specific GPIO implementation for STM32G0B1RE microcontroller.
 * Implements the gpio_hal_interface for direct register access.
 * 
 * @defgroup HAL_GPIO_STM32G0B1RE STM32G0B1RE GPIO Implementation
 * @ingroup HAL_GPIO
 * @{
 */


#define HAL_GPIO_BACKEND_STM32G0B1

#ifdef HAL_GPIO_BACKEND_STM32G0B1
#include "driver_gpio.h"
#include "hal_gpio.h"

static void enable_gpio_clock(uint32_t port_idx)
{
	//temporary gpio clock init
	volatile uint32_t *RCC_IOPENR = (volatile uint32_t*)0x40021034UL;
	*RCC_IOPENR |=  (1U<<port_idx);
}

/**
 * @brief Initialize GPIO instance (STM32G0B1RE implementation)
 * @param instance GPIO instance number
 * @param pin number
 * @param pin_config 
 * @return GPIO_OK on success, GPIO_ERROR on failure
 */
static uint8_t stm32_gpio_init(uint32_t index) {

	uint32_t pin = gpioConfig[index].pin;
	uint32_t port_ix = gpioConfig[index].port;
	uint32_t pinState = gpioConfig[index].pinState;
	uint32_t pin_config = gpioConfig[index].pinConfig;

	enable_gpio_clock(port_ix);

	uint32_t tmp = (pin_config >> MODE_SHIFT) ;
	setPinMode(port_ix,pin,tmp);

	tmp = (pin_config >> SPEED_SHIFT);
	setPinSpeed(port_ix,pin,tmp);

	tmp = (pin_config >> PULL_SHIFT);
	setPinPullDirection(port_ix,pin,tmp);

	if(pinState)
		setPin(port_ix,pin);
	else
		resetPin(port_ix,pin);

	return GPIO_OK;
}


static void stm32_gpio_deinit(uint32_t index) 
{
	uint32_t pin = gpioConfig[index].pin;
	uint32_t port_ix = gpioConfig[index].port;

	setPinMode(port_ix,pin,0U);
	setPinSpeed(port_ix,pin,0U);
	setPinPullDirection(port_ix,pin,0U);
}


static uint8_t stm32_gpio_pin_set(uint32_t index, uint32_t pin_val) {

	uint32_t pin = gpioConfig[index].pin;
	uint32_t port_ix = gpioConfig[index].port;

	if(pin_val)
		setPin(port_ix,pin);
	else
		resetPin(port_ix,pin);

	return GPIO_OK;
}


static uint8_t stm32_gpio_pin_read(uint32_t index, uint32_t *pin_val) 
{
	uint32_t pin = gpioConfig[index].pin;
	uint32_t port_ix = gpioConfig[index].port;

	//read pin
	*pin_val = readPin(port_ix,pin);
	return GPIO_OK;
}

static uint8_t stm32_gpio_pin_toggle(uint32_t index) 
{
	uint32_t pin = gpioConfig[index].pin;
	uint32_t port_ix = gpioConfig[index].port;

	if(getPinState(port_ix,pin))
		resetPin(port_ix,pin);
	else
		setPin(port_ix,pin);
		
	return GPIO_OK;
}

static const struct gpio_hal_interface stm32_gpio_interface = {
	.init 		= stm32_gpio_init,	 
	.deinit 	= stm32_gpio_deinit,
	.pin_set 	= stm32_gpio_pin_set,
	.pin_read	= stm32_gpio_pin_read,
	.pin_toggle	= stm32_gpio_pin_toggle
};

const struct gpio_hal_interface* hal_gpio_get_interface(void) {
    return &stm32_gpio_interface;
}

#endif
