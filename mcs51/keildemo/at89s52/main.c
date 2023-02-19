#include <reg52.h>

sbit LED = P0 ^ 3;
sbit KEY = P1 ^ 2;

sbit P00 = P0 ^ 0;
sbit P01 = P0 ^ 1;
sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;

void delay(short t) {
	while (t--);
}

void main()
{
	KEY = 0;
	P10 = 0;
	P11 = 1;
	P00 = 0;
	P01 = 0;
	while (1) {
		//LED = KEY;
		delay(40000);
		P11 = 0;
		LED = 1;
		delay(40000);
		P11 = 1;
		LED = 0;
	}
}