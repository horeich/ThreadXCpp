cmake_minimum_required(VERSION 3.16)

# project(
#     app 
#     VERSION 0.1.0 
#     LANGUAGES CXX C ASM)

set(SOURCES 
    ../startup/tx_initialize_low_level.S
    main.cpp
    app.cpp
)

# Include startup which initializes memory and jumps to main()

set(EXECUTABLE ${PROJECT_NAME})

set(LINKER_SCRIPT ../startup/STM32L476RGTx_FLASH.ld)

# Executable of the project
add_executable(${EXECUTABLE} 
# ../startup/tx_initialize_low_level.s
# ../startup/tx_initialize_low_level.s
    ../startup/startup_stm32l476xx.s 
    ${SOURCES}
)

# add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# Include directories
target_include_directories(${EXECUTABLE} PUBLIC ../include)

# why include again here? should be open throuh interface
# target_include_directories(${EXECUTABLE} PUBLIC ../../extern/stm32l4_drivers/include)
# target_include_directories(${EXECUTABLE} PUBLIC ../../extern/horos/include)

# target_include_directories(${EXECUTABLE} PUBLIC ../../exter/kernel/threadx/utility/execution_profile_kit/smp_version)

# Libraries
target_link_libraries(${EXECUTABLE} 
    PUBLIC
    hal::stm32l4
    cpp_api

    # azrtos::threadx
    # stm32l4_drivers
    threadx-cmsis-rtos2
)

# enable C++ 20
target_compile_features(${EXECUTABLE} PRIVATE cxx_std_20)

## target_include_directories(app PUBLIC ../objects)

target_link_directories(${EXECUTABLE} 
    PUBLIC 
    ../startup
)

set_target_linker(${EXECUTABLE} ${LINKER_SCRIPT})

# Set linker script
# --no-warn-rwx-segments for GCC 12
target_link_options(${EXECUTABLE} PRIVATE -T${LINKER_SCRIPT})
target_link_options(${EXECUTABLE} PRIVATE -Wl,--no-warn-rwx-segments,-Map=${EXECUTABLE}.map)

# # target_link_options(${EXECUTABLE} PRIVATE
# #         -T${LINKER_SCRIPT}
# #         -mcpu=cortex-m4
# #         -mthumb
# #         -mfpu=fpv4-sp-d16
# #         -mfloat-abi=hard
# #         -specs=nano.specs
# #         -lc
# #         -lm
# #         -lnosys
# #         -Wl,-Map=${PROJECT_NAME}.map,--cref
# #         -Wl,--gc-sections
# #         )

# # Make sure we have the right file ending
set_target_properties(${EXECUTABLE} PROPERTIES SUFFIX ".elf")

# Create .bin and .hex files
# add_custom_target(${EXECUTABLE}.bin
#     ALL 
#     DEPENDS ${EXECUTABLE}
#     COMMAND ${CMAKE_OBJCOPY} -Obinary ${EXECUTABLE}.elf ${EXECUTABLE}.bin
#     COMMAND ${CMAKE_OBJCOPY} -Oihex ${EXECUTABLE}.elf ${EXECUTABLE}.hex)
# add_custom_command(TARGET ${EXECUTABLE}
#         POST_BUILD
#         COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
#         COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
# add_custom_command(TARGET ${PROJECT_NAME}
#     POST_BUILD
#     COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE})

# target_link_libraries(app PRIVATE libUdpCpp)
# target_link_libraries(app PRIVATE libLwM2MCpp)

post_build(${EXECUTABLE})