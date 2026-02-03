# Startup

This folder contains the startup and linker configuration files for the embedded system project.

## Contents

- **startup.s** - Assembly startup code that initializes the system before main() execution
- **Linker scripts** - Memory layout and section placement configuration for the build process

## Purpose

The startup code handles:
- Stack pointer initialization
- Interrupt vector table setup
- System initialization before C/C++ runtime
- Branch to main()

The linker scripts define:
- Memory regions (Flash, RAM, etc.)
- Section placement (.text, .data, .bss)
- Stack and heap sizes
- Symbol definitions for runtime use

## Usage

These files are automatically included in the build process through the toolchain configuration.