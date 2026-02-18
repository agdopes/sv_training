cmake_minimum_required(VERSION 3.15)

project(training_app C ASM)

add_executable(training_app
    ${CMAKE_SOURCE_DIR}/app/main.c
    ${STARTUP_FILE}
)

target_include_directories(training_app PRIVATE
    ${CMAKE_SOURCE_DIR}/hal/inc
)

target_link_libraries(training_app
    PRIVATE hal
)

add_subdirectory(bsp)
add_subdirectory(hal)
add_subdirectory(app)

add_custom_command(TARGET training_app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary training_app training_app.bin)