include("../cmake/CH552GProject.cmake")

AddCH552GProject(pwm_simple)

target_sources(
    pwm_simple
    PRIVATE
    "src/main.c"
)