# Application subdirectories

add_subdirectory(led_toggle)

target_link_libraries(${PROJECT_NAME}.elf 
    PRIVATE bsp
)