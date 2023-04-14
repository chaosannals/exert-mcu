cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")

project(stm32demo)

add_subdirectory(f10x)
add_subdirectory(f40x)


