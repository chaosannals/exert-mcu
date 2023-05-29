include("../cmake/CH552GProject.cmake")

AddCH552GProject(led_3641as_tm1650)

target_sources(
    led_3641as_tm1650
    PRIVATE
    "src/tm1650.h"
    "src/main.c"
 "src/tm1650.c")