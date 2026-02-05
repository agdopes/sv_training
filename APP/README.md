# APP Layer

## Overview

The APP (Application) layer contains the high-level application logic and user-facing functionality of the system. This is where your main program resides.

## Purpose

This layer serves as the entry point for application execution and implements the business logic using the BSP (Board Support Package) layer.

## Architecture

```
APP Layer (Application Logic) ← You are here
    ↓
BSP Layer (Board-Specific)
    ↓
HAL Layer (Peripheral Drivers)
    ↓
Hardware Registers
```

## Current Implementation

### main.c
The current application implements a simple LED blink program:

```c
#include "../BSP/bsp.h"

int main(void) {
    // Initialize board support package
    BSP_Init();
    
    // Main loop - blink the LED
    while(1) {
        BSP_LED_Toggle();
        BSP_Delay(500000);
    }
}
```

## Key Principles

### 1. Use BSP, Not HAL Directly
Application code should only interact with BSP functions:

❌ **Wrong** - Don't use HAL in APP:
```c
#include "../PHY/drivers/hal_gpio.h"
HAL_GPIO_TogglePin(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5);
```

✅ **Correct** - Use BSP in APP:
```c
#include "../BSP/bsp.h"
BSP_LED_Toggle();
```

### 2. Focus on Application Logic
The APP layer should focus on:
- User interface logic
- Application state management
- Business logic
- Algorithm implementation
- Data processing

### 3. Avoid Hardware Details
Don't reference specific pins, ports, or registers in application code.

## Example Applications

### Example 1: Button-Controlled LED
```c
#include "../BSP/bsp.h"

int main(void) {
    BSP_Init();
    
    while(1) {
        if (BSP_Button_IsPressed()) {
            BSP_LED_On();
        } else {
            BSP_LED_Off();
        }
    }
}
```

### Example 2: LED Pattern Generator
```c
#include "../BSP/bsp.h"

int main(void) {
    BSP_Init();
    
    while(1) {
        // Fast blink 3 times
        for(int i = 0; i < 6; i++) {
            BSP_LED_Toggle();
            BSP_Delay(100000);
        }
        
        // Pause
        BSP_Delay(1000000);
        
        // Slow blink 2 times
        for(int i = 0; i < 4; i++) {
            BSP_LED_Toggle();
            BSP_Delay(500000);
        }
        
        // Long pause
        BSP_Delay(2000000);
    }
}
```

### Example 3: State Machine
```c
#include "../BSP/bsp.h"

typedef enum {
    STATE_IDLE,
    STATE_BLINK_FAST,
    STATE_BLINK_SLOW,
    STATE_OFF
} AppState_t;

int main(void) {
    BSP_Init();
    AppState_t state = STATE_IDLE;
    uint32_t counter = 0;
    
    while(1) {
        switch(state) {
            case STATE_IDLE:
                BSP_LED_Off();
                if (counter++ > 1000000) {
                    state = STATE_BLINK_FAST;
                    counter = 0;
                }
                break;
                
            case STATE_BLINK_FAST:
                BSP_LED_Toggle();
                BSP_Delay(100000);
                if (counter++ > 10) {
                    state = STATE_BLINK_SLOW;
                    counter = 0;
                }
                break;
                
            case STATE_BLINK_SLOW:
                BSP_LED_Toggle();
                BSP_Delay(500000);
                if (counter++ > 5) {
                    state = STATE_OFF;
                    counter = 0;
                }
                break;
                
            case STATE_OFF:
                BSP_LED_Off();
                BSP_Delay(1000000);
                state = STATE_IDLE;
                counter = 0;
                break;
        }
    }
}
```

## Best Practices

1. **Keep main.c focused** - One clear purpose per application
2. **Use meaningful variable names** - `ledBlinkCount` not `x`
3. **Comment complex logic** - Explain "why", not "what"
4. **Modularize large applications** - Split into multiple files if needed
5. **Handle initialization errors** - Check BSP_Init() return value
6. **Use proper types** - `uint32_t` for counts, `bool` for flags

## Future Enhancements

Potential application features to implement:
- [ ] UART command interface
- [ ] Temperature monitoring
- [ ] PWM-based LED dimming
- [ ] Data logging
- [ ] Sensor fusion algorithms
- [ ] Communication protocols

## Debugging Tips

1. **LED as debug indicator** - Use LED patterns to indicate state
2. **UART printf** - Add debug output when UART BSP is available
3. **Breakpoints** - Use GDB to step through code
4. **Logic analyzer** - Monitor GPIO pins during development

## Structure for Larger Applications

For complex applications, organize code as:

```
APP/
├── main.c              # Entry point and main loop
├── app_state.c/h       # State machine logic
├── app_sensors.c/h     # Sensor data handling
├── app_comms.c/h       # Communication handling
└── README.md           # This file
```

## Testing

Test your application by:
1. Verifying expected behavior (LED patterns, timing)
2. Edge case testing (button debouncing, rapid state changes)
3. Long-term stability testing (run for hours/days)
4. Power cycle testing (ensure proper initialization)

## Notes

- Always call `BSP_Init()` before using any board features
- Keep application code portable by using only BSP interfaces
- Follow the single responsibility principle for functions
- Document state machines and complex logic flows
