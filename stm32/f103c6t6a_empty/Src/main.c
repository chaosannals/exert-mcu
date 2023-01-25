/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	*RCC_APB2ENR |= (1 << 3);
    gpio_init(GPIOB, 1, GPIO_MODE_OUT_PUSH_PULL, GPIO_SPEED_OUT_10MHZ);
    gpio_init(GPIOB, 11, GPIO_MODE_OUT_PUSH_PULL, GPIO_SPEED_OUT_50MHZ);
    gpio_pin_set(GPIOB, 1);
    gpio_pin_set(GPIOB, 11);
	for(;;) {
//		gpio_pin_set(GPIOB, 11);
//		for(uint32_t i = 0; i < 1000; ++i);
//		gpio_pin_reset(GPIOB, 11);
//		for(uint32_t i = 0; i < 1000; ++i);
	}
}
