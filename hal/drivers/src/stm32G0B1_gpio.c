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

#include "../inc/hal_gpio.h"
#include "../config/hal_gpio_config.h"

#ifdef HAL_GPIO_BACKEND_STM32G0B1

#define IOPORT_BASE           (0x50000000UL)
// #define GPIOA            IOPORT_BASE
// #define GPIOB            (GPIOA + GPIO_OFFSET)
// #define GPIOC            (GPIOB + GPIO_OFFSET)
// #define GPIOD            (GPIOC + GPIO_OFFSET)
// #define GPIOE            (GPIOD + GPIO_OFFSET)
// #define GPIOF            (GPIOE + GPIO_OFFSET)
#define GPIO_OFFSET			 (0x00000400UL)

#define GPIO_MODER			0x00
#define GPIO_OTYPER			0x04
#define GPIO_OSPEEDR		0x08
#define GPIO_PUPDR			0x0C
#define	GPIO_IDR			0x10
#define GPIO_ODR			0x14
#define	GPIO_BSRR			0x18
#define GPIO_LCKR			0x1C
#define	GPIO_AFRL			0x20
#define	GPIO_AFRH			0x24
#define GPIO_BRR			0x28



/**
* @brief Get GPIO base address
* @param instance GPIO (GPIOA-GPIOF)
*/
static volatile uint32_t* get_gpio_base(uint32_t instance)
{
	 return (volatile uint32_t*)(IOPORT_BASE+(instance * GPIO_OFFSET));
}

static void enable_gpio_clock(uint32_t instance)
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
static uint8_t stm32_gpio_init(uint32_t instance, uint32_t pin, uint32_t pin_config) {
	if (instance >= HAL_GPIO_MAX_INSTANCES) {
        return GPIO_ERROR;
    }

	volatile uint32_t* base = get_gpio_base(instance);
	volatile uint32_t* moder = (volatile uint32_t*)((uint32_t)base + GPIO_MODER);
	volatile uint32_t* ospeedr = (volatile uint32_t*)((uint32_t)base + GPIO_OSPEEDR);
	volatile uint32_t* pupdr = (volatile uint32_t*)((uint32_t)base + GPIO_PUPDR);

	uint32_t tmp = (pin_config >> MODE_SHIFT) ;
	*moder &= ~(MODE_MASK << (pin*2));	
	*moder |= (tmp << (pin*2));	

	tmp = (pin_config >> SPEED_SHIFT);
	*ospeedr &= ~(SPEED_MASK << (pin*2));	
	*ospeedr |= (tmp << (pin*2));	

	tmp = (pin_config >> PULL_SHIFT);
	*pupdr &= ~(PULL_MASK << (pin*2));	
	*pupdr |= (tmp << (pin*2));	

	return GPIO_OK;
}


static void stm32_gpio_deinit(uint32_t instance,uint32_t pin) 
{
	//unlock register and reset
}


static uint8_t stm32_gpio_pin_set(uint32_t instance, uint32_t pin, uint32_t pin_val) {

	if (instance >= HAL_GPIO_MAX_INSTANCES) {
        return GPIO_ERROR;
    }

	volatile uint32_t* base = get_gpio_base(instance);
	volatile uint32_t* bsrr = (volatile uint32_t*)((uint32_t)base + GPIO_BSRR);
	volatile uint32_t* brr = (volatile uint32_t*)((uint32_t)base + GPIO_BRR);
	
	if(pin_val)
		*bsrr = (1U << pin);
	else
		*brr = (1U << pin);

	return GPIO_OK;
}


static uint8_t stm32_gpio_pin_read(uint32_t instance, uint32_t pin, uint32_t *pin_val) 
{
	//read pin
	return GPIO_OK;
}

static const struct gpio_hal_interface stm32_gpio_interface = {
	.init 		= stm32_gpio_init,	 
	.deinit 	= stm32_gpio_deinit,
	.pin_set 	= stm32_gpio_pin_set,
	.pin_read	= stm32_gpio_pin_read
};

const struct gpio_hal_interface* hal_gpio_get_interface(void) {
    return &stm32_gpio_interface;
}

#endif
