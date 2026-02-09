cmake_minimum_required(VERSION 3.15)
project(sv_training C ASM)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set toolchain file if provided
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

# Add subdirectories
add_subdirectory(drivers)
add_subdirectory(bsp)
add_subdirectory(app)