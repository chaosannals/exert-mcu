set(ARMTOOL_OBJCOPY "arm-none-eabi-objcopy")
set(ARMTOOL_SIZE "arm-none-eabi-size")

function(
	STM32_AddOutHexAndBin
	TARGET_NAME
	OUT_PATH
	HEX_PATH
	BIN_PATH
)
	add_custom_command(
		TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND ${ARMTOOL_OBJCOPY} -Oihex ${OUT_PATH} ${HEX_PATH}
		COMMAND ${ARMTOOL_OBJCOPY} -Obinary ${OUT_PATH} ${BIN_PATH}
		COMMENT "Build ${HEX_PATH} And ${BIN_PATH}"

		COMMAND ${ARMTOOL_SIZE} --format=berkeley ${OUT_PATH} ${HEX_PATH} ${BIN_PATH}
		COMMENT "Print Size"
	)
endfunction()