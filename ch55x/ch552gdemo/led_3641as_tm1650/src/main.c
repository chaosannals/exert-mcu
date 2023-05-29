#include <ch552_gpio.h>
#include "tm1650.h"


int main() {
	//tm1650_write_to(TM1650_CMD_MODE, TM1650_CMD_LV8 | TM1650_CMD_D8 | TM1650_CMD_DISABLE);
	//tm1650_write_to(TM1650_ADDR_D1, 0);
	//tm1650_write_to(TM1650_ADDR_D2, 0);
	//P3_MOD_OC = 0b00000000;

	//TM1650_SCL = 1;
	//TM1650_SDA = 1;
	tm1650_write_to(TM1650_CMD_MODE, TM1650_CMD_LV8 | TM1650_CMD_D8 | TM1650_CMD_ENABLE);
	tm1650_write_to(TM1650_ADDR_D1, 0b11111111);
	tm1650_write_to(TM1650_ADDR_D2, 0b11111111);
	tm1650_write_to(TM1650_ADDR_D3, 0);
	tm1650_write_to(TM1650_ADDR_D4, 0);
	while (1) {
		/*TM1650_SCL = 0;
		TM1650_SDA = 1;
		delay(4);
		TM1650_SCL = 1;
		TM1650_SDA = 0;
		delay(4);*/

		//TM1650_SCL = 1;
		//TM1650_SDA = 1;
		//delay(4);
		//TM1650_SCL = 0;
		//TM1650_SDA = 0;
		//delay(4);

		tm1650_write_to(TM1650_ADDR_D1, 0b11111111);
		tm1650_write_to(TM1650_ADDR_D2, 0b11111111);
		delay(10000);
		tm1650_write_to(TM1650_ADDR_D3, 0b11111111);
		tm1650_write_to(TM1650_ADDR_D4, 0b11111111);
		delay(10000);
		//delay(10000);
		//delay(10000);
		//delay(10000);
		//delay(10000);
		//delay(10000);
		//delay(10000);
	}
}