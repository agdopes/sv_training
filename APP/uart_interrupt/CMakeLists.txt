add_executable(uart_interrupt
    main.c
)

target_link_libraries(uart_interrupt
    PRIVATE bsp
)

target_compile_definitions(uart_interrupt
    PRIVATE USE_UART_INTERRUPT=1
)
