include("../cmake/CH552GProject.cmake")

AddCH552GProject(usb_simple)

target_sources(
    usb_simple
    PRIVATE
    "src/main.c"
)