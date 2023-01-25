#ifndef STM32F10X_RCC_H_
#define STM32F10X_RCC_H_

#include "stm32f10x_periph.h"

const uint32_t RCC_BASE = AHB_BASE + 0x1000;
uint32_t *const RCC_APB2ENR = (uint32_t *)(RCC_BASE + 0x18);

#endif /* STM32F10X_RCC_H_ */
