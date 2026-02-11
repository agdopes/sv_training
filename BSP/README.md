# BSP (Board Support Package)

## Overview

This directory contains the Board Support Package for the STM32F411RE Nucleo board. The BSP provides board-specific abstractions built on top of the HAL (Hardware Abstraction Layer) drivers.

## Purpose

The BSP layer provides:
- Board-specific hardware initialization
- High-level API for board features (LED, buttons, etc.)
- Pin mapping and board configuration
- Integration of multiple HAL drivers for board functionality
- Application-friendly interfaces

## Architecture

```
APP Layer (Application Logic)
    ↓
BSP Layer (Board-Specific) ← You are here
    ↓
HAL Layer (Peripheral Drivers)
    ↓
Hardware Registers
```

## Key Concepts

- **HAL** = Low-level peripheral drivers (generic, reusable)
- **BSP** = Board-specific implementations using HAL (specific to STM32F411RE Nucleo)

## Available BSP Modules

### Core BSP (`bsp.c/h`)
Main board initialization and control:

**Functions:**
- `BSP_Init()` - Initialize all board components
- `BSP_LED_Init()` - Initialize onboard LED
- `BSP_LED_On()` - Turn LED on
- `BSP_LED_Off()` - Turn LED off
- `BSP_LED_Toggle()` - Toggle LED state
- `BSP_Delay()` - Simple blocking delay

**Example Usage:**
```c
#include "bsp.h"

int main(void) {
    // Initialize board
    BSP_Init();
    
    // Use board features
    while(1) {
        BSP_LED_Toggle();
        BSP_Delay(500000);
    }
}
```

## Board Configuration

### STM32F411RE Nucleo Pin Mapping

| Feature | Port | Pin | Description |
|---------|------|-----|-------------|
| LED (LD2) | PA | 5 | Green LED |
| User Button | PC | 13 | Blue pushbutton (B1) |
| USART2 TX | PA | 2 | ST-Link Virtual COM |
| USART2 RX | PA | 3 | ST-Link Virtual COM |

### Defined in `bsp.h`:
```c
#define BSP_LED_PORT    HAL_GPIO_PORT_A
#define BSP_LED_PIN     HAL_GPIO_PIN_5
```

## Adding New BSP Features

### Example: Add User Button Support

1. **Update `bsp.h`:**
```c
#define BSP_BUTTON_PORT    HAL_GPIO_PORT_C
#define BSP_BUTTON_PIN     HAL_GPIO_PIN_13

BSP_Status_t BSP_Button_Init(void);
uint8_t BSP_Button_IsPressed(void);
```

2. **Update `bsp.c`:**
```c
BSP_Status_t BSP_Button_Init(void) {
    HAL_GPIO_ClockEnable(BSP_BUTTON_PORT);
    HAL_GPIO_ConfigurePin(BSP_BUTTON_PORT, BSP_BUTTON_PIN, HAL_GPIO_MODE_INPUT);
    return BSP_OK;
}

uint8_t BSP_Button_IsPressed(void) {
    return (HAL_GPIO_ReadPin(BSP_BUTTON_PORT, BSP_BUTTON_PIN) == HAL_GPIO_STATE_LOW);
}
```

3. **Call in `BSP_Init()`:**
```c
BSP_Button_Init();
```

## Design Principles

### 1. Abstract Board Details
Application code should never know specific pin numbers or ports. BSP provides this abstraction:

❌ **Bad** (in APP):
```c
HAL_GPIO_WritePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5, HAL_GPIO_STATE_HIGH);
```

✅ **Good** (in APP):
```c
BSP_LED_On();
```

### 2. Use HAL for Hardware Access
BSP should always use HAL functions, never direct register access:

❌ **Bad** (in BSP):
```c
*((volatile uint32_t*)0x40020014) ^= (1 << 5);
```

✅ **Good** (in BSP):
```c
HAL_GPIO_TogglePin(BSP_LED_PORT, BSP_LED_PIN);
```

### 3. Board-Specific Only
Keep BSP specific to the physical board. If code could work on any STM32F4, it belongs in HAL.

## Future BSP Features

- [ ] User button support with debouncing
- [ ] Debug UART (USART2) for printf support
- [ ] System clock configuration
- [ ] Power management functions
- [ ] Board identification and version info

## Testing

To test BSP functions:
1. Flash a test application
2. Verify LED behavior
3. Test with oscilloscope/multimeter if needed
4. Ensure proper initialization sequence

## Migration from Direct HAL

If your application currently uses HAL directly:

```c
// Old way (APP using HAL directly)
HAL_GPIO_ClockEnable(HAL_GPIO_PORT_A);
HAL_GPIO_ConfigurePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5, HAL_GPIO_MODE_OUTPUT);
HAL_GPIO_TogglePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5);

// New way (APP using BSP)
BSP_Init();
BSP_LED_Toggle();
```

## References

- See [PHY/drivers/README.md](../PHY/drivers/README.md) for HAL documentation
- [STM32 Nucleo-64 User Manual](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)

## Notes

- BSP is board-specific and may need modification for different boards
- Keep BSP simple and focused on board features
- Complex application logic belongs in the APP layer, not BSP
