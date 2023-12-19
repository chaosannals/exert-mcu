#include "gd32e23x.h"
#include "gd32e230c_eval.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_usart.h"
#include "gd32e23x_dma.h"
#include <stdio.h>

uint32_t delay = 0;
__IO uint16_t adc_value;

void InitMySys();
void InitGPIO();
void InitGPIO_USART0();
void InitGPIO_ADC();
void InitUSART0();
void InitADC();

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

// USART0
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

// ADC
void ADC_CMP_IRQHandler(void) {
	adc_interrupt_flag_clear(ADC_INT_EOC);
	//adc_value = adc_inserted_data_read(ADC_INSERTED_CHANNEL_1);
}

int main() {
	InitMySys();
	InitGPIO();
	InitUSART0();
	InitADC();
	
	//gpio_bit_set(GPIOA, GPIO_PIN_8);
	//gpio_bit_set(GPIOB, GPIO_PIN_9);
	while(1){
		DelayMs(1000);
		
		//adc_value = adc_inserted_data_read(ADC_INSERTED_CHANNEL_1);
		usart0SendChar(adc_value);
		usart0SendChar(adc_value >> 8);
		usart0SendChar('\n');
		
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
	InitGPIO_ADC();
	
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

void InitGPIO_ADC() {
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_1);
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_2);
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

void InitADC() {
	// DMA
	rcu_periph_clock_enable(RCU_DMA);
	
	dma_parameter_struct dps;
	dma_deinit(DMA_CH0);
	dps.periph_addr = (uint32_t)(&ADC_RDATA);
	dps.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dps.memory_addr = (uint32_t)(&adc_value);
	dps.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dps.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
	dps.memory_width = DMA_MEMORY_WIDTH_16BIT;
	dps.direction = DMA_PERIPHERAL_TO_MEMORY;
	dps.number = 2U;
	dps.priority = DMA_PRIORITY_HIGH;
	dma_init(DMA_CH0, &dps);
	
	dma_circulation_enable(DMA_CH0);
	//dma_memory_to_memory_disable(DMA_CH0);
	dma_channel_enable(DMA_CH0);
	
	// ADC
	
	rcu_periph_clock_enable(RCU_ADC);
	
	adc_special_function_config(ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 2U);
	
	adc_inserted_channel_config(0U, ADC_CHANNEL_1, ADC_SAMPLETIME_55POINT5);
	adc_inserted_channel_config(1U, ADC_CHANNEL_2, ADC_SAMPLETIME_55POINT5);
	
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	adc_enable();
	DelayMs(1);
	adc_calibration_enable();
	adc_dma_mode_enable();
	

	nvic_irq_enable(ADC_CMP_IRQn, 0U);
	adc_interrupt_enable(ADC_INT_EOC);
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}