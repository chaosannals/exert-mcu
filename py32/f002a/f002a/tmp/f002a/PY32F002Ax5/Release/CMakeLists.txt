# CMSIS Build CMakeLists generated on 2024-05-17T02:37:58

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET f002a)
set(CPU Cortex-M0+)
set(PRJ_DIR "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a")
set(OUT_DIR "G:/chaosannals/exert-mcu/py32/f002a/f002a/out/f002a/PY32F002Ax5/Release")
set(INT_DIR "G:/chaosannals/exert-mcu/py32/f002a/f002a/tmp/f002a/PY32F002Ax5/Release")
set(FPU NO_FPU)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE balanced)
set(DEBUG off)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=gnu11 -Wno-macro-redefined -Wno-pragma-pack -Wno-parentheses-equality -Wno-license-management")
set(CXX_FLAGS_GLOBAL "-Wno-macro-redefined -Wno-pragma-pack -Wno-parentheses-equality -Wno-license-management")
set(LD_FLAGS_GLOBAL "--entry=Reset_Handler --map --info summarysizes --summary_stderr --diag_suppress=L6314W")
set(LD_SCRIPT "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/RTE/Device/PY32F002Ax5/ac6_linker_script.sct.src")
set(LD_REGIONS "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/RTE/Device/PY32F002Ax5/regions_PY32F002Ax5.h")
set(LD_SCRIPT_PP "G:/chaosannals/exert-mcu/py32/f002a/f002a/tmp/f002a/PY32F002Ax5/Release/ac6_linker_script.sct")

set(DEFINES
  _RTE_
)

set(INC_PATHS
  "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/RTE/_Release_PY32F002Ax5"
  "C:/Users/chens/AppData/Local/arm/packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/chens/AppData/Local/arm/packs/ARM/CMSIS/5.9.0/CMSIS/Driver/Include"
  "C:/Users/chens/AppData/Local/arm/packs/Puya/PY32F0xx_DFP/1.2.1/Drivers/CMSIS/Device/PY32F0xx/Include"
)

set(AS_ARM_SRC_FILES
  "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/RTE/Device/PY32F002Ax5/startup_py32f002ax5.s"
)

set(CC_SRC_FILES
  "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/RTE/Device/PY32F002Ax5/system_py32f0xx.c"
  "g:/chaosannals/exert-mcu/py32/f002a/f002a/f002a/main.c"
)

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/chens/.vcpkg/artifacts/2139c4c6/compilers.arm.armclang/6.22.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.22.0")
set(TOOLCHAIN_VERSION_MIN "6.22.0")
include ("C:/Users/chens/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/AC6.6.16.2.cmake")
include ("C:/Users/chens/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS} ${AS_FLAGS_GLOBAL}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT_PP}\" ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "f002a")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})

# Linker script pre-processing

add_custom_command(TARGET ${TARGET} PRE_LINK COMMAND ${CPP} ARGS ${CPP_ARGS_LD_SCRIPT} BYPRODUCTS ${LD_SCRIPT_PP})
