include("../cmake/CH552GProject.cmake")

AddCH552GProject(usb_simple)

target_sources(
    usb_simple
    PUBLIC
    "src/ch552.h"
    "src/ch552_usb.h"
    PRIVATE
    "src/main.c"
)