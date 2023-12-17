#include "gd32e23x.h"
#include "gd32e230c_eval.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_usart.h"
#include <stdio.h>

uint32_t delay = 0;

void InitMySys();
void InitGPIO();
void InitGPIO_USART0();
void InitUSART0();

void DelayMs(uint32_t ms) {
	delay = ms;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(0U != delay) {}
}
void SysTick_Handler() {
	if (0U != delay) {
		delay--;
	}
}

void usart0SendChar(uint8_t c) {
	usart_data_transmit(USART0, c);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

int fputc(int c, FILE *f) {
	usart_data_transmit(USART0, (uint8_t) c);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
	return c;
}

void USART0_IRQHandler(void) {
	uint16_t re = 0;
	if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
		re = usart_data_receive(USART0);
		
		if (re == 13)
		{
			usart0SendChar('\r');
			usart0SendChar('\n');
		} else {
			usart0SendChar(re);
		}
	}
}

int main() {
	InitMySys();
	InitGPIO();
	InitUSART0();
	
	//gpio_bit_set(GPIOA, GPIO_PIN_8);
	//gpio_bit_set(GPIOB, GPIO_PIN_9);
	while(1){
		DelayMs(1000);
		gpio_bit_toggle(GPIOA, GPIO_PIN_8);
		gpio_bit_toggle(GPIOB, GPIO_PIN_9);
	}
}

void InitMySys() {
	if (SysTick_Config(SystemCoreClock / 1000U)) {
		while(1){}
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	NVIC_SetPriority(SysTick_IRQn, 0X00U);
}

void InitGPIO() {
	// GPIOA
	rcu_periph_clock_enable(RCU_GPIOA);
	
	// gpio_deinit(GPIOA);
	/* PA8 */
	gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_8);
	gpio_bit_reset(GPIOA, GPIO_PIN_8);
	
	InitGPIO_USART0();
	
	// GPIOB
	rcu_periph_clock_enable(RCU_GPIOB);
	/* PB9 */
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);
	gpio_bit_reset(GPIOB, GPIO_PIN_9);
}

void InitGPIO_USART0() {
	/* PA9 TX   PA10 RX*/
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);
}

void InitUSART0() {
	rcu_periph_clock_enable(RCU_USART0);
	usart_deinit(USART0);
	usart_baudrate_set(USART0, 115200U);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_enable(USART0);
	
	nvic_irq_enable(USART0_IRQn, 0);
	usart_interrupt_enable(USART0, USART_INT_RBNE);
}