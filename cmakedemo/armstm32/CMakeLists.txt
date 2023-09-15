cmake_minimum_required(VERSION 3.24)

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP "arm-none-eabi-objdump")
set(CMAKE_SIZE "arm-none-eabi-size")

find_program(ARM_C_COMPILER "arm-none-eabi-gcc")
find_program(ARM_CXX_COMPILER "arm-none-eabi-g++")
find_program(ARM_OBJCOPY "arm-none-eabi-objcopy")
find_program(ARM_OBJDUMP "arm-none-eabi-objdump")
find_program(ARM_SIZE "arm-none-eabi-size")

message(STATUS "ARM c compiler: ${ARM_C_COMPILER}")
message(STATUS "ARM c++ compiler: ${ARM_CXX_COMPILER}")
message(STATUS "ARM objcopy: ${ARM_OBJCOPY}")
message(STATUS "ARM objdump: ${ARM_OBJDUMP}")
message(STATUS "ARM size: ${ARM_SIZE}")



project(stm32demo)

add_subdirectory(f10x)
add_subdirectory(f40x)


