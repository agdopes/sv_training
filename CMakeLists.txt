cmake_minimum_required(VERSION 3.15)

project(training_app C ASM)

add_executable(training_app
    ${CMAKE_SOURCE_DIR}/hal/test_app/gpio/main.c
    ${STARTUP_FILE}
)

target_include_directories(training_app PRIVATE
    ${CMAKE_SOURCE_DIR}/hal/inc
)

target_link_libraries(training_app
    PRIVATE hal        # App only links against HAL
)

add_subdirectory(bsp)      # BSP first (provides config)
add_subdirectory(hal)      # HAL last (uses drivers + bsp)


add_custom_command(TARGET training_app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary training_app training_app.bin)
