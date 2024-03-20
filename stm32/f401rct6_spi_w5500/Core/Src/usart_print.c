/*
 * usart-print.c
 *
 *  Created on: Mar 20, 2024
 *      Author: chens
 */

#include "main.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "usart_print.h"

extern UART_HandleTypeDef huart1;

void UART_Printf(const char* fmt, ...) {
    char buff[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_UART_Transmit(&huart1, (uint8_t*)buff, strlen(buff),
                      HAL_MAX_DELAY);
    va_end(args);
}
