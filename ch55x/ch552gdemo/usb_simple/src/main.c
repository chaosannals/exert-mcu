#include <8052.h>
#include <ch552.h>

void delay(short t) {
	while (t--);
}

int main() {
	while (1) {
		delay(1000000);
		P3_2 = 1;
		delay(1000000);
		P3_2 = 0;
	}
	return 0;
}