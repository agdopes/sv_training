# LED Toggle Application

add_executable(led_toggle 
    main.c
    ${STARTUP_FILE}
)

target_link_libraries(led_toggle PRIVATE hal)

target_include_directories(led_toggle PRIVATE
    ${CMAKE_SOURCE_DIR}/hal/inc
)

# Set linker script
set_target_properties(led_toggle PROPERTIES
    LINK_DEPENDS ${LINKER_SCRIPT}
)

target_link_options(led_toggle PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=led_toggle.map
    --specs=nano.specs
    --specs=nosys.specs
)

# Generate binary file
add_custom_command(TARGET led_toggle POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary led_toggle led_toggle.bin
    COMMAND ${CMAKE_SIZE} led_toggle
    COMMENT "Generating binary and printing size information"
)
