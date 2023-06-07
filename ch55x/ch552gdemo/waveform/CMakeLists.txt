include("../cmake/CH552GProject.cmake")

AddCH552GProject(waveform)

target_sources(
    waveform
    PRIVATE
    "src/main.c"
)