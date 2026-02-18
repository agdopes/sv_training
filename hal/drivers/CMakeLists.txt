# Drivers CMakeLists.txt

if(NOT DEFINED MCU_FAMILY)
    message(FATAL_ERROR "MCU_FAMILY must be defined")
endif()

if(NOT DEFINED MCU_SERIES)
    message(FATAL_ERROR "MCU_SERIES must be defined")
endif()

if(NOT DEFINED MCU_DEVICE)
    message(FATAL_ERROR "MCU_DEVICE must be defined (e.g., STM32F411xE, STM32G0B1xx)")
endif()

string(TOLOWER ${MCU_FAMILY} MCU_FAMILY_LOWER)
string(TOLOWER ${MCU_SERIES} MCU_SERIES_LOWER)

set(DRIVER_MCU_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_FAMILY_LOWER}${MCU_SERIES_LOWER}")

if(NOT EXISTS ${DRIVER_MCU_DIR})
    message(FATAL_ERROR "Driver directory not found: ${DRIVER_MCU_DIR}\n"
                        "Expected structure: drivers/${MCU_FAMILY_LOWER}${MCU_SERIES_LOWER}/")
endif()

include(${DRIVER_MCU_DIR}/CMakeLists.txt)

if(NOT DEFINED DRIVER_SOURCES)
    message(FATAL_ERROR "DRIVER_SOURCES not defined in ${DRIVER_MCU_DIR}/CMakeLists.txt")
endif()

# Set CMSIS device paths
set(CMSIS_DEVICE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/${MCU_FAMILY}${MCU_SERIES}xx/Include")
set(CMSIS_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include")

if(NOT EXISTS ${CMSIS_DEVICE_PATH})
    message(FATAL_ERROR "CMSIS device path not found: ${CMSIS_DEVICE_PATH}")
endif()

if(NOT EXISTS ${CMSIS_CORE_PATH})
    message(FATAL_ERROR "CMSIS core path not found: ${CMSIS_CORE_PATH}")
endif()

message(STATUS "MCU Family: ${MCU_FAMILY}")
message(STATUS "MCU Series: ${MCU_SERIES}")
message(STATUS "MCU Device: ${MCU_DEVICE}")
message(STATUS "Using drivers from: ${DRIVER_MCU_DIR}")
message(STATUS "CMSIS Device: ${CMSIS_DEVICE_PATH}")
message(STATUS "CMSIS Core: ${CMSIS_CORE_PATH}")

add_library(drivers STATIC ${DRIVER_SOURCES})

target_include_directories(drivers 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC ${CMSIS_CORE_PATH}
    PUBLIC ${CMSIS_DEVICE_PATH}
    PRIVATE ${DRIVER_MCU_DIR}
)

target_compile_definitions(drivers PUBLIC ${MCU_DEVICE})

target_link_libraries(drivers PUBLIC bsp)