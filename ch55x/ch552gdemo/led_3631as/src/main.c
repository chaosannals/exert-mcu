#include <8052.h>
#include <ch552_gpio.h>

#define LED_D1 P1_1
#define LED_D2 P1_4
#define LED_D3 P3_2

#define LED_A P3_3

/* 这个脚没有输出 1 能力 */
/* #define LED_B P3_6 */
#define LED_B P1_7
#define LED_C P1_6
#define LED_D P3_1
#define LED_E P3_0
#define LED_F P3_4
#define LED_G P1_5
/* #define LED_DF P1_7 */

#define BUTTON P3_6

#define OFF = 0b00000000;

int digits[] = {
	/*_GFEDCBA*/
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
};

int leds[] = { 0, 0, 0 };

void set_led(int code) {
	LED_A = code & 0x1;
	LED_B = (code >> 1) & 0x1;
	LED_C = (code >> 2) & 0x1;
	LED_D = (code >> 3) & 0x1;
	LED_E = (code >> 4) & 0x1;
	LED_F = (code >> 5) & 0x1;
	LED_G = (code >> 6) & 0x1;
}

inline void delay(int t) {
	while (t--) {
		int y = 64;
		while (y--);
	}
}

void let_leds(int number) {
	for (int i = 0; i < 3; ++i) {
		leds[i] = digits[number % 10];
		number /= 10;
	}
}

void flash_leds(int t) {
	LED_D1 = 1;
	LED_D2 = 1;
	LED_D3 = 0;
	set_led(leds[0]);
	delay(t);
	LED_D1 = 1;
	LED_D2 = 0;
	LED_D3 = 1;
	set_led(leds[1]);
	delay(t);
	LED_D1 = 0;
	LED_D2 = 1;
	LED_D3 = 1;
	set_led(leds[2]);
	delay(t);
}

int main() {
	LED_D1 = 1;
	LED_D2 = 1;
	LED_D3 = 1;

	P1_MOD_OC = 0b00000000;
	P3_MOD_OC = 0b00000000;

	set_led(0);

	int i = 0;
	while (1) {
		let_leds(i++ / 100);
		flash_leds(24);
	}
}