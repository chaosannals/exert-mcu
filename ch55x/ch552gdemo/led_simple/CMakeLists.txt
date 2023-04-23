include("../cmake/CH552GProject.cmake")

AddCH552GProject(led_simple)

target_sources(
    led_simple
    PRIVATE
    "src/main.c"
)
