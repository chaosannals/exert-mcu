#include <8052.h>

#define LED_D1 P1_1
#define LED_D2 P1_4
#define LED_D3 P3_2

#define LED_A P3_3

/* 这个脚没有输出 1 能力 */
#define LED_B P3_7
#define LED_C P1_6
#define LED_D P3_1
#define LED_E P3_0
#define LED_F P3_4
#define LED_G P1_5
#define LED_DF P1_7

#define BUTTON P3_6


int main() {
	LED_D1 = 0;
	LED_D2 = 0;
	LED_D3 = 0;

	LED_A = 1;
	LED_B = 1;
	LED_C = 1;
	LED_D = 1;
	LED_E = 1;
	LED_F = 1;
	LED_G = 1;
	LED_DF = 1;

	while (1) {

	}
}