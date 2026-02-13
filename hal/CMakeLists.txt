add_library(hal STATIC)

target_sources(hal PRIVATE
    src/hal_uart.c
    src/hal_gpio.c
    src/hal_common.c
)

target_include_directories(hal
    PUBLIC inc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hal
    PRIVATE drivers
    PRIVATE bsp
)