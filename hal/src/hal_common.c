#include "hal_common.h"
#include "hal_gpio.h"

void hal_init(void)
{
	volatile uint32_t *RCC_IOPENR = (volatile uint32_t*)0x40021034UL;
	//temporary gpio clock init
	*RCC_IOPENR |=  (1U<<0);

	//initialize GPIOA pin5 as LED output 
	hal_gpio_init(GPIOA,PIN5,OUTPUT_MODE | LOW_SPEED |NO_PULL);
}

