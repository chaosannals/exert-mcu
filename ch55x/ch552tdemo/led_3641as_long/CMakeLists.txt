include("../cmake/CH552TBuild.cmake")

AddCH552TProject(led_3641as_long)

target_sources(
    led_3641as_long
    PRIVATE
    "src/main.c"
)