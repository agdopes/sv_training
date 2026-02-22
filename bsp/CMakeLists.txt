add_library(bsp INTERFACE)

if(NOT DEFINED BOARD_NAME)
    message(FATAL_ERROR "BOARD_NAME must be defined")
endif()

set(BSP_BOARD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD_NAME}")

if(NOT EXISTS ${BSP_BOARD_DIR})
    message(FATAL_ERROR "Board directory not found: ${BSP_BOARD_DIR}")
endif()

message(STATUS "BSP Board: ${BOARD_NAME}")

target_include_directories(bsp INTERFACE
    ${BSP_BOARD_DIR}
)

set(STARTUP_FILE "${BSP_BOARD_DIR}/startup.s" PARENT_SCOPE)
set(LINKER_SCRIPT "${BSP_BOARD_DIR}/linker.ld" PARENT_SCOPE)