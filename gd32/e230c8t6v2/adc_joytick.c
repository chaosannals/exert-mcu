#include "adc_joytick.h"
#include "sys_tick.h"
#include "gd32e23x_adc.h"

uint16_t adc_value[2] = {0};

void InitADCJoytick(void) {
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
	

	// use DMA ,disable interrupt
	//nvic_irq_enable(ADC_CMP_IRQn, 0U);
	//adc_interrupt_enable(ADC_INT_EOC);
	adc_interrupt_disable(ADC_INT_EOC);
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}

//void ADC_CMP_IRQHandler(void) {
//	adc_interrupt_flag_clear(ADC_INT_EOC);
//	adc_value[0] = adc_inserted_data_read(ADC_INSERTED_CHANNEL_1);
//	adc_value[1] = adc_inserted_data_read(ADC_INSERTED_CHANNEL_2);
//}