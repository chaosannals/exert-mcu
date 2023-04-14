add_executable(f40xdemo)

set_target_properties(
	f40xdemo
	PROPERTIES
	# C_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hare -mfpu=fpv4-sp-d16 -w -Wno-unknown-pragmas"
	C_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hare -mfpu=fpv4-sp-d16 -Wall -Wno-unknown-pragmas"
	C_FLAGS_DEBUG "-O0 -g2 -ggdb"
	C_FLAGS_RELEASE "-O3"
)


target_sources(
	f40xdemo
	PRIVATE
	"src/main.c"
)