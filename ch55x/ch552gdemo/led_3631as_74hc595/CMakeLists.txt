include("../cmake/CH552GProject.cmake")

AddCH552GProject(led_3631as_74hc595)

target_sources(
    led_3631as_74hc595
    PRIVATE
    "src/main.c"
)