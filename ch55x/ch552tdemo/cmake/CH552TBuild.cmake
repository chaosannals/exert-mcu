function(
	AddCH552TProject
	TARGET_NAME
)
	add_executable(${TARGET_NAME})

    set_target_properties(
        ${TARGET_NAME}
        PROPERTIES
        OUTPUT_NAME ${TARGET_NAME}
        SUFFIX ".ihx"
    )

    # 生成 ihx 和 bin 文件。
    # 详见 CMakeSettings.json 配置指定 sdcc 作为编译工具。
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMENT "output ${TARGET_NAME}.hex"
        COMMAND packihx "${TARGET_NAME}.ihx" > "${TARGET_NAME}.hex"
        COMMENT "output ${TARGET_NAME}.bin"
        COMMAND objcopy -I ihex -O binary "${TARGET_NAME}.ihx" "${TARGET_NAME}.bin"
    )

    # 使用 sdcc
    find_program(SDCC_COMPILER sdcc)

    if(SDCC_COMPILER)
        message(STATUS "sdcc found: ${SDCC_COMPILER}")
        get_filename_component(SDCC_BIN_DIR ${SDCC_COMPILER} DIRECTORY)
        get_filename_component(SDCC_DIR ${SDCC_BIN_DIR} DIRECTORY)
        message(STATUS "sdcc dir: ${SDCC_DIR} proejct dir: ${PROJECT_SOURCE_DIR}")
        target_include_directories(
            ${TARGET_NAME}
            PUBLIC
            "${SDCC_DIR}/include/mcs51"
            "${PROJECT_SOURCE_DIR}/inc"
        )
    else()
        message(STATUS "sdcc not found")
    endif()
endfunction()
