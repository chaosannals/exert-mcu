cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(ch552gdemo)

add_subdirectory(led_3631as)
add_subdirectory(led_3641as_tm1650)
add_subdirectory(led_simple)
add_subdirectory(led_rx)
add_subdirectory(usb_simple)
add_subdirectory(xl2400)