#include "tm1650.h"

void tm1650_start() {
	TM1650_SCL = 1;
	TM1650_SDA = 1;
	delay(4);
	TM1650_SDA = 0;
	delay(4);
	TM1650_SCL = 0;
	delay(4);
}

void tm1650_end() {
	TM1650_SCL = 1;
	TM1650_SDA = 0;
	delay(4);
	TM1650_SDA = 1;
	delay(4);
}

char tm1650_ack() {
	int i = 44;
	while (TM1650_SDA && --i) {
		delay(4);
	}
	TM1650_SCL = 1;
	delay(4);
	TM1650_SCL = 0;
	delay(4);
	return i;
}

void tm1650_write(char data) {
	for (int i = 7; i >= 0; i--) {
		TM1650_SDA = (data >> i) & 1;
		delay(4);
		TM1650_SCL = 1;
		delay(4);
		TM1650_SCL = 0;
		delay(4);
	}
}

char tm1650_read() {
	char result = 0;
	for (int i = 7; i >= 0; i--) {
		TM1650_SCL = 0;
		delay(4);
		result <<= 1;
		result |= (TM1650_SDA & 1);
		delay(4);
		TM1650_SCL = 1;
		delay(4);
	}
	return result;
}

void tm1650_write_to(char addr, char data) {
	tm1650_start();
	tm1650_write(addr);
	tm1650_ack();
	tm1650_write(data);
	tm1650_ack();
	tm1650_end();
}

char tm1650_read_from(char addr) {
	tm1650_start();
	tm1650_write(addr);
	tm1650_ack();
	char result = tm1650_read();
	tm1650_ack();
	tm1650_end();
	return result;
}