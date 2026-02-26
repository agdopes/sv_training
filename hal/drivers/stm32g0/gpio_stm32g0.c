#include "driver_gpio.h" 
#include "hal_gpio.h"
#include "stm32g0xx.h"

GPIO_TypeDef *GPIOx[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};

void setPinMode(uint32_t index, uint32_t pin, uint32_t mode)
{
	GPIOx[index]->MODER &= ~(MODE_MASK << (pin*2));	
	GPIOx[index]->MODER |= (mode << (pin*2));	
}
void setPinSpeed(uint32_t index, uint32_t pin, uint32_t speed)
{
	GPIOx[index]->OSPEEDR &= ~(SPEED_MASK << (pin * 2));
	GPIOx[index]->OSPEEDR |= (speed << (pin * 2));
}
void setPinPullDirection(uint32_t index, uint32_t pin, uint32_t pupdr)
{
	GPIOx[index]->PUPDR &= ~(PULL_MASK << (pin * 2));
	GPIOx[index]->PUPDR |= (pupdr << (pin * 2));
}
void setPin(uint32_t index, uint32_t pin)
{
	GPIOx[index]->BSRR = (1U << pin);
}
void resetPin(uint32_t index, uint32_t pin)
{
	GPIOx[index]->BRR = (1U << pin);
}
uint32_t readPin(uint32_t index, uint32_t pin)
{
	return (GPIOx[index]->IDR >> pin) & 1U;
}
uint32_t getPinState(uint32_t index, uint32_t pin)
{
	return (GPIOx[index]->ODR >> pin) & 1U;
}

void setAlternateMode(uint32_t index, uint32_t pin, uint32_t altMode)
{
	if(pin < 8U)
	{
		GPIOx[index]->AFR[0] &= ~(0xFU << ((pin % 8) * 4));
		GPIOx[index]->AFR[0] |=  (altMode << ((pin % 8) * 4));
	}
	else
	{
		GPIOx[index]->AFR[1] &= ~(0xFU << ((pin % 8) * 4));
		GPIOx[index]->AFR[1] |=  (altMode << ((pin % 8) * 4));
	}
}
