# (c) HOREICH - Andreas Reichle

cmake_minimum_required(VERSION 3.16)

project(
    threadx-cmsis-rtos2 
    VERSION 0.1.0 
    LANGUAGES C ASM)

# Add sources in this folder
set(SOURCES
    stm32_mw_cmsis_rtos_tx/cmsis_os2.c
)

# Create a library
add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)

# Directory needed by parent app
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ./stm32_mw_cmsis_rtos_tx
)

# Set necessary preprocessor variables

target_compile_definitions(${PROJECT_NAME} PUBLIC USE_DYNAMIC_MEMORY_ALLOCATION)

# Link with threadx lib
target_link_libraries(${PROJECT_NAME} PUBLIC 
    azrtos::threadx # threadx files
    hal::stm32l4 # CMSIS compiler
    ) 