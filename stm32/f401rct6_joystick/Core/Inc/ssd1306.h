#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include <stdint.h>

#define SSD1306_BLACK 0x00
#define SSD1306_WHITE 0xFF

void SSD1306_Init(void);
void SSD1306_Fill(uint8_t color);
void SSD1306_Flush(void);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color);

#endif /* INC_SSD1306_H_ */
