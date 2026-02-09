add_executable(uart_poll
    main.c
)

target_link_libraries(uart_poll
    PRIVATE bsp
)

target_compile_definitions(uart_poll
    PRIVATE USE_UART_POLLING=1
)