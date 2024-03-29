#include "usart_print.h"
#include "gd32e23x_usart.h"
#include "stdio.h"

void InitUSART0(void) {
	usart_deinit(USART0);
	usart_baudrate_set(USART0, 115200U);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_enable(USART0);
	
	nvic_irq_enable(USART0_IRQn, 0);
	usart_interrupt_enable(USART0, USART_INT_RBNE);
}

void SendUSART0(char c) {
	usart_data_transmit(USART0, c);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

char int_chars[8];
void SendUSART0Ui16(uint16_t i16) {
	int start = 0;
	do {
		int_chars[start++] = (i16 % 10) + 0x30;
		i16 /= 10;
	} while(i16 != 0);
	for (int index = start - 1; index >= 0; --index) {
		SendUSART0(int_chars[index]);
	}
}

void PrintUSART0(char *t) {
	while (*t != '\0') {
		SendUSART0(*t);
		++t;
	}
}

/*
// cover stdio fputc
int fputc(int ch, FILE *f) {
	uint16_t count = 0;
	while(usart_flag_get(USART0, USART_FLAG_TBE) == RESET) {
		if (count ++ >= 60000) {
			return ch;
		}
	}
	usart_data_transmit(USART0, (uint8_t)ch);
	return ch;
}
*/

// USART0
void USART0_IRQHandler(void) {
	uint16_t re = 0;
	if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
		re = usart_data_receive(USART0);
		
		if (re == 13)
		{
			SendUSART0('\r');
			SendUSART0('\n');
		} else {
			SendUSART0(re);
		}
	}
}