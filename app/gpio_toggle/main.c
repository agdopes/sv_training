#include "hal_common.h"
#include "hal_gpio.h"

int main(void) {

	hal_init();
	while(1)
	{
		hal_gpio_pin_toggle(GPIOA,PIN5);
		for (int i=0; i<1000000;i++)
		{
			//delay
		}

	}
    return 0;
}



