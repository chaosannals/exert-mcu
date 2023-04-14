include("../cmake/STM32Build.cmake")

add_executable(f10xdemo)

set_target_properties(
	f10xdemo
	PROPERTIES
	#C_FLAGS "-mcpu=cortex-m3 -w -Wno-unknown-pragmas"
	C_FLAGS "-mcpu=cortex-m3 -Wall -Wno-unknown-pragmas"
	C_FLAGS_DEBUG "-O0 -g2 -ggdb"
	C_FLAGS_RELEASE "-O3"
	OUTPUT_NAME "f10xdemo"
	SUFFIX ".out"
)

STM32_AddOutHexAndBin(
	f10xdemo
	"$<TARGET_FILE_DIR:f10xdemo>/f10xdemo.out"
	"$<TARGET_FILE_DIR:f10xdemo>/f10xdemo.hex"
	"$<TARGET_FILE_DIR:f10xdemo>/f10xdemo.bin"
)

target_sources(
	f10xdemo
	PRIVATE
	"src/main.c"
)