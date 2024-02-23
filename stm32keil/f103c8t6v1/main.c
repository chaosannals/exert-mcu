#include "stm32f10x.h"
#include <stdint.h>

static uint32_t delay = 0;

static void DelayMs(uint32_t ms) {
	delay = ms;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(0U != delay) {}
}


int main(void) {
	while(1){
		DelayMs(1000);
	}
}
