#include "hal_gpio.h"
#include "bsp_stm32g0.h"

int main(void) {

	//uint32_t pin_state = 0;
	//initialize GPIOA pin5 as LED output 
	for(int i = 0; i < NUM_PINS;i++)
	{
		hal_gpio_init(i);
	}

	while(1)
	{
		hal_gpio_pin_set(LED_PIN,1);
		//hal_gpio_pin_toggle(LED_PIN);
		for (int i=0; i<1000000;i++)
		{
			//delay
		}
		//hal_gpio_pin_read(BUTTON_PIN, &pin_state);
	}
    return 0;
}



