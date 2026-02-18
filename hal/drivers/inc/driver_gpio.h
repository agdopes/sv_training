#ifndef STM32G0xx_LLD_GPIO_H
#define STM32G0xx_LLD_GPIO_H


#include "stm32g0xx.h"

void setPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t mode);

void setPinSpeed(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t speed);

void setPinPullDirection(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t pupdr);

void setPin(GPIO_TypeDef *GPIOx, uint32_t pin);

void resetPin(GPIO_TypeDef *GPIOx, uint32_t pin);

uint32_t readPin(GPIO_TypeDef *GPIOx, uint32_t pin);

uint32_t getPinState(GPIO_TypeDef *GPIOx, uint32_t pin);


#endif
