cmake_minimum_required(VERSION 3.18)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(main C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_DEOPTIMIZED_DEBUG 1)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME}
  src/main.c
)

set(PICO_BOARD pico_w)

pico_sdk_init()

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)

pico_add_extra_outputs(${PROJECT_NAME})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
