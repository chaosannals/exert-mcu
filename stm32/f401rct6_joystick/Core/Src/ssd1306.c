#include "ssd1306.h"
#include <string.h>
#include "stm32f4xx_hal.h"

#define SSD1306_IIC_ADDR0 0x3C << 1
#define SSD1306_IIC_ADDR1 0x3D << 1

#define CMD_SET_CONTRAST 			0x81
#define CMD_SET_VCOMH_DESELECT 		0xDB
#define CMD_SET_DISPLAY_NORMAL 		0xA6
#define CMD_SET_DISPLAY_INVERSE 	0xA7
#define CMD_SET_ON 					0xAF
#define CMD_SET_OFF   				0xAE
#define CMD_SET_REMAP0				0xA0
#define CMD_SET_REMAP127			0xA1
#define CMD_SCAN_0TON				0xC0
#define CMD_SCAN_NTO0				0xC8

#define SSD1306_HEIGHT          64
#define SSD1306_WIDTH           128
#define SSD1306_BUFFER_SIZE   	SSD1306_WIDTH * SSD1306_HEIGHT / 8

extern I2C_HandleTypeDef hi2c1;

void SSD1306_WriteCommand(uint8_t cmd) {
	HAL_I2C_Mem_Write(&hi2c1, SSD1306_IIC_ADDR0, 0x00, 1, &cmd, 1, HAL_MAX_DELAY);
}

void SSD1306_WriteBuf(uint8_t *buffer, size_t size) {
	HAL_I2C_Mem_Write(&hi2c1, SSD1306_IIC_ADDR0, 0x40, 1, buffer, size, HAL_MAX_DELAY);
}

uint8_t screen_buffer[SSD1306_BUFFER_SIZE];


void SSD1306_Init(void) {
	HAL_Delay(100);

	SSD1306_WriteCommand(CMD_SET_OFF); // set off

	SSD1306_WriteCommand(0x20); //Set Memory Addressing Mode
	SSD1306_WriteCommand(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
	                                // 10b,Page Addressing Mode (RESET); 11b,Invalid

	SSD1306_WriteCommand(0xB0); // set page address

	SSD1306_WriteCommand(CMD_SCAN_0TON); // 垂直正向
//	SSD1306_WriteCommand(CMD_SCAN_NTO0); // 垂直反向

	SSD1306_WriteCommand(0x00); // set lower column address
	SSD1306_WriteCommand(0x10); // set higher column address

	SSD1306_WriteCommand(0x40); // set display start line

	SSD1306_WriteCommand(CMD_SET_CONTRAST); //
//	SSD1306_WriteCommand(0xCF); // 128
	SSD1306_WriteCommand(0xFF); //

//	SSD1306_WriteCommand(CMD_SET_REMAP0); // 左右调转
	SSD1306_WriteCommand(CMD_SET_REMAP127); // 横向正向

	SSD1306_WriteCommand(CMD_SET_DISPLAY_NORMAL); // 正常颜色
//	SSD1306_WriteCommand(CMD_SET_DISPLAY_INVERSE); // 反色

	SSD1306_WriteCommand(0xFF); // multiplex ratio
//	SSD1306_WriteCommand(0xA8); // multiplex ratio

//	SSD1306_WriteCommand(0x3F); // duty = 1/64;   height 32
	SSD1306_WriteCommand(0x3F); // duty = 1/64;   height 128 or 64

	SSD1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

	SSD1306_WriteCommand(0xD3); // set display offset
	SSD1306_WriteCommand(0x00); // offset 0

	SSD1306_WriteCommand(0xD5); // set display clock divide ratio/oscillator frequency
//	SSD1306_WriteCommand(0x80); // set divide ratio
	SSD1306_WriteCommand(0xF0); // set divide ratio

	SSD1306_WriteCommand(0xD9); // set pre-charge period
	SSD1306_WriteCommand(0x22); //
//	SSD1306_WriteCommand(0xF1); //

	SSD1306_WriteCommand(0xDA); // set COM pins
//	SSD1306_WriteCommand(0x02); // height: 32
	SSD1306_WriteCommand(0x12); // height: 128 or 64

	SSD1306_WriteCommand(CMD_SET_VCOMH_DESELECT);
//	SSD1306_WriteCommand(0x30); //
	SSD1306_WriteCommand(0x20); //0x20,0.77xVcc

	SSD1306_WriteCommand(0x8D); // set charge pump
//	SSD1306_WriteCommand(0x10); // disable
	SSD1306_WriteCommand(0x14); // enable

	SSD1306_WriteCommand(CMD_SET_ON); // set on

	SSD1306_Fill(SSD1306_WHITE); //

	SSD1306_Flush();
}

void SSD1306_Fill(uint8_t color) {
	memset(screen_buffer, color, sizeof(screen_buffer));
}

void SSD1306_Flush(void) {
	for (uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {
		SSD1306_WriteCommand(0xB0 + i); // set RAM page address
		SSD1306_WriteCommand(0x00 + 0);
		SSD1306_WriteCommand(0x10 + 0);
		SSD1306_WriteBuf(&screen_buffer[SSD1306_WIDTH*i], SSD1306_WIDTH);
	}
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
	if (x >= SSD1306_HEIGHT || y >= SSD1306_HEIGHT) {
		return;
	}

	if (color == SSD1306_WHITE) {
		screen_buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		screen_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}
