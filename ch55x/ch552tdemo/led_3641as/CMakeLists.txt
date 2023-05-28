include("../cmake/CH552TBuild.cmake")

AddCH552TProject(led_3641as)

target_sources(
    led_3641as
    PRIVATE
    "src/main.c"
)