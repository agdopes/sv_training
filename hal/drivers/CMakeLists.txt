# Drivers CMakeLists.txt

if(NOT DEFINED MCU_FAMILY)
    message(FATAL_ERROR "MCU_FAMILY must be defined")
endif()

if(NOT DEFINED MCU_SERIES)
    message(FATAL_ERROR "MCU_SERIES must be defined")
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

message(STATUS "MCU Family: ${MCU_FAMILY}")
message(STATUS "MCU Series: ${MCU_SERIES}")
message(STATUS "Using drivers from: ${DRIVER_MCU_DIR}")

add_library(drivers STATIC ${DRIVER_SOURCES})

target_include_directories(drivers 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PRIVATE ${DRIVER_MCU_DIR}
)

target_link_libraries(drivers PUBLIC bsp)
