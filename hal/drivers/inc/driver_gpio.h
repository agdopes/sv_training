#ifndef LLD_GPIO_H
#define LLD_GPIO_H

#include <stdint.h>

void setPinMode(uint32_t index, uint32_t pin, uint32_t mode);

void setPinSpeed(uint32_t index, uint32_t pin, uint32_t speed);

void setPinPullDirection(uint32_t index, uint32_t pin, uint32_t pupdr);

void setPin(uint32_t index, uint32_t pin);

void resetPin(uint32_t index, uint32_t pin);

uint32_t readPin(uint32_t index, uint32_t pin);

uint32_t getPinState(uint32_t index, uint32_t pin);

uint32_t setAlternateMode(uint32_t index, uint32_t pin, uint32_t altMode);


#endif
