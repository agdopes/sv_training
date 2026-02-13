# Hardware Abstraction Layer

## Overview
This folder contains the public API for the hardware abstraction layer, and the target implementation for the STM32G0xx and STM32F4xx MCUs that will be used for this training

## Supported Peripherals
The following are the current supported peripherals for the training.
* [RCC](requirements/RCC.md)
* [TIMER](requirements/TIMER.md)
* [GPIO](requirements/GPIO.md)
* [UART](requirements/UART.md)

## Folder Structure
````
├── public_inc                      - Contains the generic public API interface for the HAL
│   ├── rcc.h
│   ├── timer.h
│   ├── gpio.h
│   └── uart.h
├── requirements                    - Contains the necessary requirements on how to implement the HAL
│   ├── GPIO.md
│   ├── RCC.md
│   ├── TIMER.md
│   └── UART.md
└── src                             - Contains the implementation for the target MCU
    ├── stm32f4xx
    │   ├── stm32f4xx_rcc.c
    │   ├── stm32f4xx_timer.c
    │   ├── stm32f4xx_gpio.c
    │   └── stm32f4xx_uart.c
    ├── stm32g0xx
    │   ├── stm32g0xx_rcc.c
    │   ├── stm32g0xx_timer.c
    │   ├── stm32g0xx_gpio.c
    │   └── stm32g0xx_uart.c
````