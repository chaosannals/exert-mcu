#ifndef STM32F10X_RCC_H_
#define STM32F10X_RCC_H_

#include "stm32f10x_periph.h"

const uint32_t RCC_BASE = AHB_BASE + 0x1000;
uint32_t *const RCC_APB2ENR = (uint32_t *)(RCC_BASE + 0x18);

typedef enum {
	RCC_APB2_ENABLE_AFIO = 0,

	RCC_APB2_ENABLE_IOPA = 2,
	RCC_APB2_ENABLE_IOPB = 3,
	RCC_APB2_ENABLE_IOPc = 4,

	RCC_APB2_ENABLE_ADC1 = 9,
	RCC_APB2_ENABLE_ADC2 = 10,
	RCC_APB2_ENABLE_TIM1 = 11,
	RCC_APB2_ENABLE_SPI1 = 12,
	RCC_APB2_ENABLE_TIM8 = 13,
	RCC_APB2_ENABLE_USART1 = 14,
	RCC_APB2_ENABLE_ADC3 = 15,
} rcc_apb2_periph_enable_e;

void rcc_apb2_enable(rcc_apb2_periph_enable_e target) {
	*RCC_APB2ENR |= (1 << target);
}

#endif /* STM32F10X_RCC_H_ */
