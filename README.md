# STM32F411RE Bare-Metal Training Project

A minimal bare-metal firmware project for the STM32F411RE microcontroller, designed for embedded systems training. This project demonstrates fundamental embedded programming concepts including GPIO control, hardware abstraction, and bare-metal development without an RTOS.

## 🎯 Project Overview

This project implements a simple LED blink application using:
- **Direct register manipulation** through a hardware abstraction layer
- **Bare-metal C** without any operating system
- **CMake build system** for cross-compilation
- **Complete interrupt vector table** for production-ready code
- **Modular BSP architecture** for code reusability

## 🔧 Hardware Requirements

### Target Board
- **STM32F411RE Nucleo Board** (or compatible)
  - Cortex-M4F core @ 100 MHz
  - 512 KB Flash memory
  - 128 KB SRAM
  - Hardware FPU (Floating Point Unit)

### LED Configuration
- **LED Pin**: PA5 (GPIO Port A, Pin 5)
- Most STM32 Nucleo boards have an onboard LED on PA5
- If using a custom board, connect an LED with appropriate resistor to PA5

### Programmer/Debugger
- **ST-Link V2** (integrated on Nucleo boards)
- Or compatible JTAG/SWD debugger

### Connections
```
STM32F411RE Nucleo Board
├── USB Mini/Micro-B → PC (for ST-Link programming)
├── PA5 → LED (onboard or external with 220Ω resistor)
└── Power: 5V via USB or external 7-12V
```

## 📁 Project Structure

```
sv_training/
├── APP/                    # Application layer
│   ├── main.c             # Main application code
│   └── README.md          # APP layer documentation
├── BSP/                    # Board Support Package
│   ├── bsp_gpio.c         # GPIO hardware abstraction
│   ├── bsp_gpio.h         # GPIO API definitions
│   └── README.md          # BSP layer documentation
├── PHY/                    # Physical layer drivers
│   └── drivers/           # Network PHY drivers (placeholder)
├── Scripts/                # Build configuration
│   └── CMakeLists.txt     # CMake build script
├── Startup/                # Startup and system files
│   ├── stm32f411re_startup.s         # Assembly startup code
│   ├── stm32f411re_linker_script.ld  # Linker script
│   └── README.md                      # Startup documentation
├── UTILS/                  # Utility functions (placeholder)
├── build.sh               # Linux/macOS build script
├── build.bat              # Windows build script
├── BUILD.md               # Detailed build instructions
└── README.md              # This file
```

## 🚀 Quick Start

### Prerequisites
1. ARM GCC Toolchain (`arm-none-eabi-gcc`)
2. CMake (version 3.15+)
3. Make or MinGW Make
4. ST-Link tools or OpenOCD (for flashing)

See [BUILD.md](BUILD.md) for detailed installation instructions.

### Build

**Linux/macOS:**
```bash
chmod +x build.sh
./build.sh
```

**Windows:**
```cmd
build.bat
```

### Flash

**Using st-flash:**
```bash
st-flash write build/app.bin 0x8000000
```

**Using OpenOCD:**
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
        -c "program build/app.elf verify reset exit"
```

For detailed flashing instructions, see [BUILD.md](BUILD.md).

## 💡 Features

### Current Implementation
- ✅ GPIO hardware abstraction layer (BSP)
- ✅ LED blink application on PA5
- ✅ Complete Cortex-M4 interrupt vector table
- ✅ Proper data/BSS initialization
- ✅ CMake-based build system
- ✅ Support for hardware FPU
- ✅ Memory-mapped register access

### What You'll Learn
- Bare-metal embedded programming
- Direct hardware register manipulation
- Interrupt vector table configuration
- Linker scripts and memory layout
- ARM Cortex-M4 architecture
- Build system configuration
- Hardware abstraction layers

## 📚 Documentation

- [BUILD.md](BUILD.md) - Comprehensive build and flash instructions
- [APP/README.md](APP/README.md) - Application layer details
- [BSP/README.md](BSP/README.md) - Board Support Package documentation
- [Startup/README.md](Startup/README.md) - Startup code explanation

## 🛠️ Development

### Modifying the Blink Rate

Edit [APP/main.c](APP/main.c) and change the delay value:

```c
delay(500000);  // Increase for slower, decrease for faster
```

### Adding New GPIO Operations

The BSP provides these functions:

```c
BSP_GPIO_ClockEnable(port);              // Enable clock
BSP_GPIO_ConfigurePin(port, pin, mode);  // Configure pin
BSP_GPIO_WritePin(port, pin, state);     // Write HIGH/LOW
BSP_GPIO_TogglePin(port, pin);           // Toggle state
BSP_GPIO_ReadPin(port, pin);             // Read pin state
```

### Example: Control Multiple LEDs

```c
#include "../BSP/bsp_gpio.h"

int main(void) {
    BSP_GPIO_ClockEnable(GPIO_PORT_A);
    BSP_GPIO_ConfigurePin(GPIO_PORT_A, GPIO_PIN_5, GPIO_MODE_OUTPUT);
    BSP_GPIO_ConfigurePin(GPIO_PORT_A, GPIO_PIN_6, GPIO_MODE_OUTPUT);
    
    while(1) {
        BSP_GPIO_TogglePin(GPIO_PORT_A, GPIO_PIN_5);
        delay(250000);
        BSP_GPIO_TogglePin(GPIO_PORT_A, GPIO_PIN_6);
        delay(250000);
    }
}
```

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| LED not blinking | Check PA5 connection, verify power, press reset |
| Build errors | Ensure ARM toolchain is installed and in PATH |
| Flash errors | Update ST-Link drivers, try different USB port |
| Wrong blink rate | Adjust delay value or check clock configuration |

## 📖 References

- [STM32F411RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f411re.pdf)
- [STM32F411 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00119316.pdf)
- [ARM Cortex-M4 Generic User Guide](https://developer.arm.com/documentation/dui0553/latest/)
- [CMake Documentation](https://cmake.org/documentation/)

## 🤝 Contributing

This is a training project. Feel free to:
- Add new BSP modules (UART, SPI, I2C)
- Implement utility functions
- Add more example applications
- Improve documentation

## 📄 License

This project is provided for educational purposes. Refer to individual component licenses where applicable.

## 🎓 Training Modules

**Completed:**
- ✅ Basic GPIO control
- ✅ Build system setup
- ✅ Hardware abstraction

**Future Topics:**
- ⏳ UART communication
- ⏳ Timer/PWM configuration
- ⏳ Interrupt handling
- ⏳ ADC/DAC operations
- ⏳ DMA transfers
- ⏳ RTOS integration

---

**Questions?** Review the documentation in each module's README file or consult the STM32F411RE reference manual.

