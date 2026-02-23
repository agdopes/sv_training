cmake_minimum_required(VERSION 3.15)

project(training_app C ASM)

add_subdirectory(bsp) 
add_subdirectory(hal)
add_subdirectory(app)

add_executable(training_app.elf
    ${CMAKE_SOURCE_DIR}/app/uart_hello.c
    ${STARTUP_FILE}
)

target_include_directories(training_app.elf PRIVATE
    ${CMAKE_SOURCE_DIR}/hal/inc
)

target_link_libraries(training_app.elf
    PRIVATE hal
)

add_custom_command(TARGET training_app.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary training_app.elf training_app.bin)