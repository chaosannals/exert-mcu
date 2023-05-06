include("../cmake/CH552GProject.cmake")

AddCH552GProject(xl2400)

target_sources(
    xl2400
    PRIVATE
    "src/main.c"
)