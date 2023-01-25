#ifndef STM32F10X_PERIPH_H_
#define STM32F10X_PERIPH_H_

#include<stdint.h>

const uint32_t PERIPH_BASE = 0x40000000;
const uint32_t APB1_BASE = PERIPH_BASE;
const uint32_t APB2_BASE = PERIPH_BASE + 0x00010000;
const uint32_t AHB_BASE = PERIPH_BASE + 0x00020000;

#endif /* STM32F10X_PERIPH_H_ */
