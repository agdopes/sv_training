#include "driver_gpio.h" 

void setPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t mode)
{
	GPIOx->MODER |= (mode << (pin*2));	
}
void setPinSpeed(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t speed)
{
	GPIOx->OSPEEDR |= (speed << (pin * 2));
}
void setPinPullDirection(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t pupdr)
{
	GPIOx->PUPDR |= (pupdr << (pin * 2));
}
void setPin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	GPIOx->BSRR = (1U << pin);
}
void resetPin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	GPIOx->BRR = (1U << pin);
}
uint32_t readPin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	return (GPIOx->IDR & pin);
}
uint32_t getPinState(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	return (GPIOx->ODR & pin);
}

