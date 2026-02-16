
cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk")
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(p1s_switch_panel
switch_panel.c
)
pico_generate_pio_header(p1s_switch_panel ${CMAKE_CURRENT_LIST_DIR}/switch_panel.pio)
pico_enable_stdio_usb(p1s_switch_panel 1)
pico_enable_stdio_uart(p1s_switch_panel 1)
pico_add_extra_outputs(p1s_switch_panel)
target_link_libraries(p1s_switch_panel
  pico_stdlib
  hardware_pio
  pico_cyw43_arch_none)
