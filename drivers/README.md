# HAL (Hardware Abstraction Layer) Drivers

## Overview

This directory contains the Hardware Abstraction Layer (HAL) drivers for STM32F411RE peripheral access. The HAL provides low-level, hardware-specific functions that abstract register-level operations.

## Purpose

The HAL layer provides:
- Direct peripheral register access abstraction
- Reusable, microcontroller-specific drivers
- Standard APIs for peripheral operations
- Hardware configuration functions
- Status and error handling

## Architecture

```
APP Layer (Application Logic)
    ↓
BSP Layer (Board-Specific)
    ↓
HAL Layer (Peripheral Drivers) ← You are here
    ↓
Hardware Registers
```

## Available Drivers

### GPIO Driver (`hal_gpio.c/h`)
Provides low-level GPIO peripheral control:
- Clock enable/disable
- Pin mode configuration (input, output, alternate, analog)
- Pin state read/write operations
- Pin toggle operations

**Example Usage:**
```c
#include "hal_gpio.h"

// Enable GPIO port clock
HAL_GPIO_ClockEnable(HAL_GPIO_PORT_A);

// Configure pin as output
HAL_GPIO_ConfigurePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5, HAL_GPIO_MODE_OUTPUT);

// Set pin high
HAL_GPIO_WritePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5, HAL_GPIO_STATE_HIGH);

// Toggle pin
HAL_GPIO_TogglePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5);

// Read pin state
HAL_GPIO_State_t state = HAL_GPIO_ReadPin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_0);
```

## Adding New HAL Drivers

To add a new peripheral driver:

1. **Create header file** (`hal_<peripheral>.h`):
   ```c
   #ifndef HAL_<PERIPHERAL>_H
   #define HAL_<PERIPHERAL>_H
   
   // Type definitions
   // Function prototypes
   
   #endif
   ```

2. **Create source file** (`hal_<peripheral>.c`):
   ```c
   #include "hal_<peripheral>.h"
   
   // Register definitions
   // Implementation
   ```

3. **Update CMakeLists.txt** to include the new driver

4. **Document the driver** in this README

## Planned Drivers

- [ ] UART (Serial communication)
- [ ] SPI (Serial Peripheral Interface)
- [ ] I2C (Inter-Integrated Circuit)
- [ ] Timer (PWM, delays, counting)
- [ ] ADC (Analog-to-Digital Converter)
- [ ] DMA (Direct Memory Access)
- [ ] EXTI (External Interrupts)

## Design Guidelines

### Naming Convention
- Prefix all functions with `HAL_`
- Use descriptive names: `HAL_<Peripheral>_<Action>`
- Example: `HAL_UART_Transmit()`, `HAL_SPI_ReadByte()`

### Function Categories
1. **Initialization**: Configure peripheral hardware
2. **Read/Write**: Data transfer operations
3. **Control**: Enable/disable, mode changes
4. **Status**: Query peripheral state

### Error Handling
Return status codes where appropriate:
```c
typedef enum {
    HAL_OK = 0,
    HAL_ERROR,
    HAL_BUSY,
    HAL_TIMEOUT
} HAL_Status_t;
```

## Integration with BSP

The BSP layer uses HAL drivers to implement board-specific functionality:
- BSP calls HAL functions
- BSP defines board-specific pin mappings
- BSP handles multi-peripheral coordination

**Do NOT** call HAL functions directly from APP layer - use BSP instead.

## Testing

Each HAL driver should be testable independently by:
1. Creating a simple test application
2. Verifying register configurations with a debugger
3. Measuring outputs with oscilloscope/logic analyzer

## References

- [STM32F411xC/xE Reference Manual](https://www.st.com/resource/en/reference_manual/dm00119316.pdf)
- [STM32F411RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f411re.pdf)
- [Cortex-M4 Generic User Guide](https://developer.arm.com/documentation/dui0553/latest/)

## Contributing

When adding new drivers:
1. Follow the existing code style
2. Document all public APIs
3. Update this README
4. Test thoroughly before committing
