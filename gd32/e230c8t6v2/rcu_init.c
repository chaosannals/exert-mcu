#include "rcu_init.h"
#include "gd32e23x_rcu.h"

void InitRCU(void) {
	// GPIO
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	// ADC
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	rcu_periph_clock_enable(RCU_ADC);
	
	// USART0
	rcu_periph_clock_enable(RCU_USART0);
	
	// DMA
	//rcu_periph_clock_enable(RCU_DMA);
	
	// TIME2
	rcu_periph_clock_enable(RCU_TIMER2);
}