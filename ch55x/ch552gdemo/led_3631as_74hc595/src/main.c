#include <8052.h>
#include <ch552_gpio.h>

// TODO

#define SH_CP P3_3
#define ST_CP P3_4
#define DS P3_0

#define LED_1_A
#define LED_1_B
#define LED_1_C
#define LED_1_D
#define LED_1_E
#define LED_1_F
#define LED_1_G
#define LED_1_DF
#define LED_1_D1
#define LED_1_D2
#define LED_1_D3
#define LED_2_A
#define LED_2_B
#define LED_2_C
#define LED_2_D
#define LED_2_E
#define LED_2_F
#define LED_2_G
#define LED_2_DF
#define LED_2_D1
#define LED_2_D2
#define LED_2_D3

int led_digits[24] = { 1 };

inline void delay(int t) {
	while (t--) {
		int y = 64;
		while (y--);
	}
}

int main() {
	DS = 1;

	while (1) {
		SH_CP = 1;
		ST_CP = 1;
		delay(100);
		SH_CP = 0;
		ST_CP = 0;
		delay(100);
	}
}