/*
 * w5500.h
 *
 *  Created on: Mar 20, 2024
 *      Author: chens
 */

#ifndef W5500_H_
#define W5500_H_

void W5500_Select(void);
void W5500_Unselect(void);

void W5500_ReadBuff(uint8_t* buff, uint16_t len);
void W5500_WriteBuff(uint8_t* buff, uint16_t len);

uint8_t W5500_ReadByte(void);
void W5500_WriteByte(uint8_t byte);

void W5500_Init(void);

#endif /* W5500_H_ */

