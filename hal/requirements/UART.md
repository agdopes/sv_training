# UART Peripheral

## Overview
This contains the basic requirements for the UART peripheral and the high level diagram of the peripheral

## Requirements
### Must-have requirements
* **MREQ.1** - The HAL UART must be able to initialize based on the given configuration structure
* **MREQ.2** - The HAL UART must be able to de-initialize and return the registers to its reset state
* **MREQ.3** - The HAL UART must be able to use the HAL GPIO to configure the necessary pins for UART communication
* **MREQ.4** - The HAL UART must be able to use full-duplex communication
* **MREQ.5** - The HAL UART must be able to support the transmission and reception of data via polling or interrupts
    * The use of interrupts is preferred to prevent any blocking operation in the CPU
* **MREQ.6** - The HAL UART must be able to abort the transmission and reception of data
* **MREQ.7** - The HAL UART must be able to support the necessary interrupts for its functionality

### Nice-to-have requirements
* **NREQ.1** - Utilize the DMA peripheral of the MCU for a much more efficient transfer of data.

## Configuration and Status

### UART Peripheral Status

### Configuration Structure

## Public API
