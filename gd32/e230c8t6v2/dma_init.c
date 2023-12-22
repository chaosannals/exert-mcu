#include "dma_init.h"
#include "gd32e23x_dma.h"

extern uint16_t adc_value[2];

void InitDMA(void) {
	dma_parameter_struct dps;
	
	// ch0  adc
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
	dma_channel_enable(DMA_CH0);
	
	
}