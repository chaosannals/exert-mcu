#include "sys_tick.h"
#include "gd32e23x.h"
#include "gd32e23x_timer.h"

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
	
	//[START] TIMER2 CH3 for ADC
	timer_deinit(TIMER2);
	timer_parameter_struct tps;
	tps.prescaler = 71;
	tps.alignedmode = TIMER_COUNTER_EDGE;
	tps.counterdirection = TIMER_COUNTER_UP;
	tps.period = 999U;
	tps.clockdivision = TIMER_CKDIV_DIV1;
	tps.repetitioncounter = 0U;
	timer_init(TIMER2, &tps);
	
	timer_oc_parameter_struct tops;
	tops.ocpolarity = TIMER_OC_POLARITY_HIGH;
	tops.outputnstate = TIMER_CCX_ENABLE;
	timer_channel_output_config(TIMER2, TIMER_CH_3, &tops);
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 1U);
	timer_channel_output_mode_config(TIMER2, TIMER_CH_3, TIMER_OC_MODE_PWM1);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);
	
	timer_enable(TIMER2);
	//[END] TIMER2 CH3 for ADC
}