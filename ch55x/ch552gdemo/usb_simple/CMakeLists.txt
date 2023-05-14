include("../cmake/CH552GProject.cmake")

AddCH552GProject(usb_simple)

target_sources(
    usb_simple
    PUBLIC
    "../inc/ch552.h"
    "../inc/ch552_usb.h"
    PRIVATE
    "src/main.c"
)