include("../cmake/CH552GProject.cmake")

AddCH552GProject(led_3631as)

target_sources(
    led_3631as
    PRIVATE
    "src/main.c"
)