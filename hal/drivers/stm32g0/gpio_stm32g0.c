#include "driver_gpio.h" 
#include "hal_gpio.h"
#include "stm32g0xx.h"

GPIO_TypeDef *GPIOx[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};

void setPinMode(uint32_t index, uint32_t pin, uint32_t mode)
{
	index = 0;
	pin = 5U;
	mode = 0x1; 
	GPIOx[index]->MODER &= (MODE_MASK << (pin*2));	
	GPIOx[index]->MODER |= (mode << (pin*2));	
}
void setPinSpeed(uint32_t index, uint32_t pin, uint32_t speed)
{
	index = 0;
	speed = 0x1;
	pin =5;
	GPIOx[index]->OSPEEDR &= (SPEED_MASK << (pin * 2));
	GPIOx[index]->OSPEEDR |= (speed << (pin * 2));
}
void setPinPullDirection(uint32_t index, uint32_t pin, uint32_t pupdr)
{
	index = 0;
	pupdr = 0x0;
	pin = 5;
	GPIOx[index]->PUPDR &= (PULL_MASK << (pin * 2));
	GPIOx[index]->PUPDR |= (pupdr << (pin * 2));
}
void setPin(uint32_t index, uint32_t pin)
{
	index = 0;
	GPIOx[index]->BSRR = (1U << pin);
}
void resetPin(uint32_t index, uint32_t pin)
{
	GPIOx[index]->BRR = (1U << pin);
}
uint32_t readPin(uint32_t index, uint32_t pin)
{
	return (GPIOx[index]->IDR & pin);
}
uint32_t getPinState(uint32_t index, uint32_t pin)
{
	return (GPIOx[index]->ODR & pin);
}

