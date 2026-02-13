# TIMER Peripheral

## Overview
This contains the basic requirements for the TIMER peripheral and the high level diagram of the peripheral

## Requirements
### Must-have requirements
* **MREQ.1** - The HAL TIMER must be able to initialize based on the given configuration structure
* **MREQ.2** - The HAL TIMER must be able to de-initialize and return to its reset state
* **MREQ.3** - The HAL TIMER must support the output compare feature
    * This will be use to trigger the 1ms interrupt for toggling the GPIO pin
* **MREQ.4** - The HAL TIMER must be able to start and stop the timer during runtime
* **MREQ.5** - The HAL TIMER must be able to get the current count of the timer

### Nice-to-have requirements
* **NREQ.1** - Support the use of the input capture feature
    * Can be used as a de-bounce for button press
* **NREQ.2** - Support the PWM feature
    * Can be use the dim the LED connected to the GPIO

## Configuration and Status

### GPIO Peripheral Status

### Configuration Structure

## Public API
