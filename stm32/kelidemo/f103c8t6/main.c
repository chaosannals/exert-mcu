#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stdbool.h>

void Delay(uint32_t n);
void InitGPIO(void);

int main (void) {
	InitGPIO();
	
	while(true) {
		Delay(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		Delay(100);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	}
}

void Delay(uint32_t n) {
	while (n > 0) --n;
}

void InitGPIO(void) {
	GPIO_InitTypeDef gpioDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpioDef.GPIO_Pin = GPIO_Pin_0;
	gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioDef);
}
