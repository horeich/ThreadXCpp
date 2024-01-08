# (c) HOREICH - Andreas Reichle

cmake_minimum_required(VERSION 3.16)

project(
    stm32l4_drivers 
    VERSION 0.1.0 
    LANGUAGES C ASM)

    # Add sources in this folder
set(SOURCES
    pinmap.c
    peripheral_pins.c
    serial_api.c
    gpio_api.c
)

# Create a library
add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)

# Directory needed by parent app
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
# set_target_properties(${PROJECT_NAME} PROPERTIES
#   INTERFACE_INCLUDE_DIRECTORIES ../include
# )

# Link with hal and ll libraries
target_link_libraries(${PROJECT_NAME} PUBLIC stm32l4) # public: make available for high layer libs