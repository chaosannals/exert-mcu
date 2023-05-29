#ifndef TM1650_H
#define TM1650_H

#include <8052.h>

#define TM1650_SCL P3_2
#define TM1650_SDA P3_0

//#define TM1650_SCL P1_5
//#define TM1650_SDA P1_6

/*
* 键盘扫码
*         D4         D3         D2        D1
* A/K1   0x47       0x46       0x45      0x44
* B/K2   0x4F       0x4E       0x4D      0x4C
* C/K3   0x57       0x56       0x55      0x54
* D/K4   0x5F       0x5E       0x5D      0x5C
* E/K5   0x67       0x66       0x65      0x64
* F/K6   0x6F       0x6E       0x6D      0x6C
* G/K7   0x77       0x76       0x75      0x74
*/

/*
* 显存地址
*
*	A        B        C        D        E         F        G        DP
*  B0       B1       B2       B3       B4       B5        B6       B7
*
* D1   0x68
* D2   0x6A
* D3   0x6C
* D4   0x6E
*/

//  0x48 显示模式
#define TM1650_CMD_MODE 0b01001000
//  0x49 扫码模式
#define TM1650_CMD_READ 0b01001001

// 显示模式亮度命令 位   B6 B5 B4
#define TM1650_CMD_LV8 0b00000000
#define TM1650_CMD_LV1 0b00010000
#define TM1650_CMD_LV2 0b00100000
#define TM1650_CMD_LV3 0b00110000
#define TM1650_CMD_LV4 0b01000000
#define TM1650_CMD_LV5 0b01010000
#define TM1650_CMD_LV6 0b01100000
#define TM1650_CMD_LV7 0b01110000

// 显示模式显示控制位 B3   7 / 8 显示控制位
#define TM1650_CMD_D7 0b00000000
#define TM1650_CMD_D8 0b00001000

// 显示模式显示控制位 B1   显示开/关
#define TM1650_CMD_ENABLE  0b00000000
#define TM1650_CMD_DISABLE 0b00000001

#define TM1650_ADDR_D1   0x68
#define TM1650_ADDR_D2   0x6A
#define TM1650_ADDR_D3   0x6C
#define TM1650_ADDR_D4   0x6E

inline void delay(int t) {
	while (--t) {
		for (int i = 0; i < 44; ++i);
	}
}

void tm1650_start();
void tm1650_end();
void tm1650_ack();
void tm1650_write(char data);
char tm1650_read();
void tm1650_write_to(char addr, char data);
char tm1650_read_from(char addr);

#endif
