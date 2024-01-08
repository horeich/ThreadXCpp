# Copyright (c) HOREICH

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Let cmake know where to find Ninja (use as generator)
if(WIN32)
   set(CMAKE_MAKE_PROGRAM ${CMAKE_BASE_DIR}/ninja CACHE STRING "Ninja location")
endif()

# Set compiler flags
if(NOT CMAKE_TOOLCHAIN_FILE)
   set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BASE_DIR}/arm-gcc-cortex-m4.cmake)
endif()

include(${CMAKE_BASE_DIR}/utilities.cmake)

project(
    threadXtest 
    VERSION 0.1.0 
    LANGUAGES CXX C ASM)

# Add hal and ll driver
add_subdirectory(extern/platform/stm32l4)

# Add driver abstraction
add_subdirectory(extern/stm32l4_drivers/src)

# add_subdirectory(extern/horos/src)

# Add threadx
add_subdirectory(extern/kernel)

add_subdirectory(extern/cmsis-rtos2)

add_subdirectory(extern/horos/src)

add_subdirectory(app/src)
