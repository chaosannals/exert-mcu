#include <8052.h>

void delay(short t) {
	while (t--);
}

int main() {
	while (1) {
		delay(10000);
		P0_0 = 1;
		delay(10000);
		P0_0 = 0;
	}
	return 0;
}