#include "sys_tick.h"
#include "rcu_init.h"
#include "gpio_init.h"
#include "dma_init.h"
#include "usart_print.h"
#include "adc_joytick.h"
#include "gd32e23x_gpio.h"
#include <stdio.h>

extern uint16_t adc_value[2];

int main(void) {
	InitSysTick();
	InitRCU();
	InitGPIO();
	InitDMA();
	InitUSART0();
	InitADCJoytick();
	
	while(1){
		gpio_bit_toggle(GPIOA, GPIO_PIN_8);
		gpio_bit_toggle(GPIOB, GPIO_PIN_9);
		//SendUSART0(adc_value[0]);
		//SendUSART0(adc_value[0] >> 8);
		//SendUSART0(adc_value[1]);
		//SendUSART0(adc_value[1] >> 8);
		printf("x: %d y:%d", adc_value[0], adc_value[1]);
		DelayMs(1000);
	}
}
