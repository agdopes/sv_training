# ARM GCC Toolchain for Cortex-M processors
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Specify the cross compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CPU configuration (can be overridden via -DARM_CPU, -DARM_FPU, -DARM_FLOAT_ABI)
if(NOT DEFINED ARM_CPU)
    set(ARM_CPU "cortex-m4")
endif()

if(NOT DEFINED ARM_FPU)
    set(ARM_FPU "fpv4-sp-d16")
endif()

if(NOT DEFINED ARM_FLOAT_ABI)
    set(ARM_FLOAT_ABI "hard")
endif()

# Build CPU flags based on configuration
set(CPU_FLAGS "-mcpu=${ARM_CPU} -mthumb")
if(ARM_FPU)
    set(CPU_FLAGS "${CPU_FLAGS} -mfpu=${ARM_FPU} -mfloat-abi=${ARM_FLOAT_ABI}")
endif()

set(CMAKE_C_FLAGS_INIT "${CPU_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS_INIT "${CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs")

# Debug and release flags
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")

# Skip compiler tests (cross-compiling)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
