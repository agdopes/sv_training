#include "driver_gpio.h" 

GPIO_TypeDef *GPIOx[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};

void setPinMode(uint32_t index, uint32_t pin, uint32_t mode)
{
	GPIOx[index]->MODER |= (mode << (pin*2));	
}
void setPinSpeed(uint32_t index, uint32_t pin, uint32_t speed)
{
	GPIOx[index]->OSPEEDR |= (speed << (pin * 2));
}
void setPinPullDirection(uint32_t index, uint32_t pin, uint32_t pupdr)
{
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
	return (GPIOx[index]->IDR & pin);
}
uint32_t getPinState(uint32_t index, uint32_t pin)
{
	return (GPIOx[index]->ODR & pin);
}

