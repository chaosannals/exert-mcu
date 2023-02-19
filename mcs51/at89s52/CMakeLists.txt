cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(at89s52 C)

add_executable(at89s52)

find_program(SDCC_COMPILER sdcc)

if(SDCC_COMPILER)
    message(STATUS "sdcc found: ${SDCC_COMPILER}")
    get_filename_component(SDCC_BIN_DIR ${SDCC_COMPILER} DIRECTORY)
    get_filename_component(SDCC_DIR ${SDCC_BIN_DIR} DIRECTORY)
    message(STATUS "sdcc dir: ${SDCC_DIR}")
    target_include_directories(
        at89s52
        PUBLIC
        "${SDCC_DIR}/include/mcs51"
    )
else()
    message(STATUS "sdcc not found")
endif()

target_sources(
    at89s52
    PRIVATE
    "src/main.c"
)