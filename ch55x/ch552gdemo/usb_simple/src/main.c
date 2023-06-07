#include <8052.h>
#include <ch552_timer.h>
#include <ch552_uart.h>

void delay(short t) {
	while (t--);
}

void put_0(char c) {
	UART_SBUF = c;
	while ((UART_SCON & 0b10) == 0);
	UART_SCON &= 0b11111101;
}
char get_0() {
	char r;
	while ((UART_SCON & 0b01) == 0);
	r = UART_SBUF;
	UART_SCON &= 0b11111110;
	return r;
}

char buf_i0;
void get_i0() interrupt 0 {
	if ((UART_SCON & 0b01) > 0) {
		buf_i0 = UART_SBUF;
		UART_SCON &= 0b11111110;
	}
}

int main() {
	// B7 8bit
	UART_SCON = 0b00010000;

	while (1) {
		put_0('a');
		delay(100);
		P3_2 = 1;
		put_0('a');
		delay(100);
		P3_2 = 0;
	}
	return 0;
}