#include <8052.h>
#include <ch552_timer.h>
#include <ch552_uart.h>

inline void delay(int t) {
	while (--t) {
		for (int i = 0; i < 44; ++i);
	}
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
void get_i0() __interrupt(0) {
	if ((UART_SCON & 0b01) > 0) {
		buf_i0 = UART_SBUF;
		UART_SCON &= 0b11111110;
	}
}

void main() {
	// B7 SM0 8bit
	// B6 SM1 Fsys/12
	// B4 REN ‘ –ÌΩ” ’
	UART_SCON = 0b00010000;

	while (1) {
		put_0('a');
		delay(10000);
		//P3_2 = 1;
		put_0('b');
		delay(10000);
		put_0('c');
		delay(10000);
		//P3_2 = 0;
	}
}
