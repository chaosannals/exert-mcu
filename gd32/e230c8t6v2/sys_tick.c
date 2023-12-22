#include "sys_tick.h"
#include "gd32e23x.h"

uint32_t ticker = 0;

void DelayMs(uint32_t ms) {
	uint32_t end = ticker + ms;
	//SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(end > ticker) {}
}

void SysTick_Handler() {
	++ticker;
}

void InitSysTick() {
	if (SysTick_Config(SystemCoreClock / 1000U)) {
		while(1){}
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	NVIC_SetPriority(SysTick_IRQn, 0x00U);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}