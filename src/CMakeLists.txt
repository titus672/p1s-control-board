##cmake_minimum_required(VERSION 3.13...3.27)
#
## initialize the SDK based on PICO_SDK_PATH
## note: this must happen before project()
#
#include(/home/titus/repos/p1s-reverse-engineering/src/pico-sdk/pico_sdk_init.cmake)
#
#project(p1s_switch_panel)
#
## initialize the Raspberry Pi Pico SDK
#
## rest of your project
#
#add_executable(p1s_switch_panel
#  switch_panel.c
#)
#
#target_link_libraries(pico_stdlib)

cmake_minimum_required(VERSION 3.13)
include(/home/titus/pico/pico-sdk/external/pico_sdk_import.cmake)
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
