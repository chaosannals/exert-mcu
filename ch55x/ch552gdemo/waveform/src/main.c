#include <8052.h>
#include <ch552_gpio.h>

inline void delay(int t) {
	while (--t) {
		for (int i = 0; i < 44; ++i);
	}
}

void main() {
	P3_MOD_OC = 0b00000000;
	P1_MOD_OC = 0b00000000;
	P1_4 = 0;
	P3_2 = 0;

	int i = 0;
	//P1_4 = 1;
	while (1) {
		if (!(i & 0b11)) {
			P3_2 = P3_2 ? 0 : 1;
		}
		if (!(i & 0b1)) {
			P1_4 = P1_4 ? 0 : 1;
		}
		delay(4);

		if (!(i & 0b1111)) {
			delay(4444);
		}
		++i;
	}
}