include("../cmake/CH552GProject.cmake")

AddCH552GProject(led_rx)

target_sources(
    led_rx
    PRIVATE
    "src/main.c"
)