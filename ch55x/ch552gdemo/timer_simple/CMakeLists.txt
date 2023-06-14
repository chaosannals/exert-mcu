include("../cmake/CH552GProject.cmake")

AddCH552GProject(timer_simple)

target_sources(
    timer_simple
    PRIVATE
    "src/main.c"
)