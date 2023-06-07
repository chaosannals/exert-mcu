#include <ch552_gpio.h>
#include "tm1650.h"

int digits[] = {
	/*.GFEDCBA*/
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

int leds[] = { 0, 0, 0, 0 };

void let_leds(int number) {
	for (int i = 0; i < 4; ++i) {
		leds[i] = digits[number % 10];
		number /= 10;
	}
}

void flash_leds() {
	tm1650_write_to(TM1650_ADDR_D1, leds[3]);
	tm1650_write_to(TM1650_ADDR_D2, leds[2]);
	tm1650_write_to(TM1650_ADDR_D3, leds[1]);
	tm1650_write_to(TM1650_ADDR_D4, leds[0]);
}

void main() {
	// 开漏输出，类似 I2C 协议，不过默认就是开漏所以不用设置。
	//P3_MOD_OC = 0b00000101;

	// 需要延迟 60ms 让 TM1650 开机。
	delay(10000);

	//
	tm1650_write_to(TM1650_CMD_MODE, TM1650_CMD_LV8 | TM1650_CMD_D8 | TM1650_CMD_ENABLE);
	int i = 0;
	while (1) {
		let_leds(++i);
		flash_leds();
		delay(10000);
	}
}