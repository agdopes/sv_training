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

#include "driver_gpio.h"
#include "../inc/hal_gpio.h"

#ifdef HAL_GPIO_BACKEND_STM32G0B1


static void enable_gpio_clock(GPIO_TypeDef *GPIOx)
{
	//Call RCC clock enable IOPORT
}

/**
 * @brief Initialize GPIO instance (STM32G0B1RE implementation)
 * @param instance GPIO instance number
 * @param pin number
 * @param pin_config 
 * @return GPIO_OK on success, GPIO_ERROR on failure
 */
static uint8_t stm32_gpio_init(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t pin_config) {

	enable_gpio_clock(GPIOx);

	uint32_t tmp = (pin_config >> MODE_SHIFT) ;
	setPinMode(GPIOA,pin,tmp);

	tmp = (pin_config >> SPEED_SHIFT);
	setPinSpeed(GPIOA,pin,tmp);

	tmp = (pin_config >> PULL_SHIFT);
	setPinPullDirection(GPIOA,pin,tmp);

	return GPIO_OK;
}


static void stm32_gpio_deinit(GPIO_TypeDef *GPIOx,uint32_t pin) 
{
	setPinMode(GPIOx,pin,0U);

	setPinSpeed(GPIOx,pin,0U);

	setPinPullDirection(GPIOx,pin,0U);
}


static uint8_t stm32_gpio_pin_set(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t pin_val) {

	if(pin_val)
		setPin(GPIOx,pin);
	else
		resetPin(GPIOx,pin);

	return GPIO_OK;
}


static uint8_t stm32_gpio_pin_read(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t *pin_val) 
{
	//read pin
	*pin_val = readPin(GPIOx,pin);
	return GPIO_OK;
}

static uint8_t stm32_gpio_pin_toggle(GPIO_TypeDef *GPIOx, uint32_t pin) 
{
	if(getPinState(GPIOx,pin))
		resetPin(GPIOx,pin);
	else
		setPin(GPIOx,pin);
		
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
