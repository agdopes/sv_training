add_library(drivers STATIC)

target_sources(drivers PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_uart_stm32f411.c
)

target_include_directories(drivers 
    PRIVATE 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/config
)