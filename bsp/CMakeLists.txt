add_library(bsp STATIC
    bsp.c
)

target_include_directories(bsp 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bsp
    PUBLIC drivers
)