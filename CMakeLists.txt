cmake_minimum_required(VERSION 3.25)

project(gpio_hal)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/bsp/boards/nucleo_g0b1re/linker.ld -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/app.map"
)
set(CMAKE_SIZE arm-none-eabi-size)
	

add_executable(${PROJECT_NAME}
	hal/test_app/gpio/main.c
	bsp/boards/nucleo_g0b1re/startup.c
	hal/src/hal_gpio.c
	hal/drivers/stm32g0/gpio_stm32g0.c
)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	hal/inc/
	hal/drivers/CMSIS/Device/ST/STM32G0xx/Include/
	hal/drivers/CMSIS/Include/
	hal/drivers/inc/
	hal/test_app/gpio/
)
target_link_options(${PROJECT_NAME}
 PRIVATE
	-Wl,--start-group
	-Wl,--end-group
	-mcpu=cortex-m0
	-mthumb
	-static
	-nostartfiles
)
	
target_compile_options(${PROJECT_NAME}
 PRIVATE
 	-mcpu=cortex-m0
	-mthumb
	-Os
	-ffunction-sections # Place functions in separate sections
	-fdata-sections # Place data in separate sections
	-fno-exceptions # Disable exceptions for bare-metal code
	-DHAL_GPIO_STM32G0B1RE

)

# # Convert .elf firmware to .bin after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}
)
