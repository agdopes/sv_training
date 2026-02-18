add_executable(gpio_toggle
    main.c
)

target_link_libraries(gpio_toggle
    PRIVATE bsp
)

# target_compile_definitions(uart_interrupt
    # PRIVATE USE_UART_INTERRUPT=1
# )
