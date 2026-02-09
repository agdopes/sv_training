add_library(drivers STATIC
    src/hal_uart_stm32f411.c
)

target_include_directories(drivers 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/config
)