# (c) HOREICH - Andreas Reichle

cmake_minimum_required(VERSION 3.16)

project(
    cpp_api 
    VERSION 0.1.0 
    LANGUAGES CXX C ASM)

    # Add sources in this folder
set(SOURCES
    digitalInOut.cpp
    digitalOut.cpp
    retarget.cpp
    kernel.cpp
    thread.cpp
)

# Create a library
add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)

# Directory needed by parent app
target_include_directories(${PROJECT_NAME} PUBLIC ../include)

# target_include_directories(${PROJECT_NAME} PUBLIC ../../extern/kernel/threadx/common_smp/inc)
# set_target_properties(${PROJECT_NAME} PROPERTIES
#   INTERFACE_INCLUDE_DIRECTORIES ../include
# )

# Link with hal and ll libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
    stm32l4_drivers     
    azrtos::threadx 
)
