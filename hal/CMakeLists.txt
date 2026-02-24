add_subdirectory(drivers)

set(HAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_timer.c
)

add_library(hal STATIC ${HAL_SOURCES})

target_include_directories(hal 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(hal 
    PUBLIC drivers
    PUBLIC bsp
)