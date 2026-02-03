# BSP (Board Support Package)

## Overview

This directory contains the Board Support Package for the project. The BSP provides hardware abstraction and drivers for the target board.

## Structure

```
BSP/
├── inc/          # Header files
├── src/          # Source files
└── README.md     # This file
```

## Purpose

The BSP layer provides:
- Hardware initialization
- Low-level driver interfaces
- Pin configuration
- Peripheral setup
- Board-specific constants

## Usage

Include the necessary BSP headers in your application code:

```c
#include "bsp.h"
```

Initialize the board at startup:

```c
BSP_Init();
```

## Configuration

Board-specific settings can be modified in the configuration files located in the `inc/` directory.

## Dependencies

- Target toolchain
- Hardware abstraction layer (HAL)

## Notes

Ensure the BSP is properly initialized before accessing any hardware peripherals.