/*
 * nrf24l01.h
 *
 *  Created on: May 8, 2024
 *      Author: chens
 */

#ifndef INC_NRF24L01_H_
#define INC_NRF24L01_H_

#include <stdint.h>

void NRF24L01_Init(void);
uint8_t NRF24L01_SendByte(uint8_t data);
uint8_t NRF24L01_WriteByte(uint8_t address, uint8_t data);
uint8_t NRF24L01_ReadByte(uint8_t address);
uint8_t NRF24L01_ReadBuf(uint8_t address, uint8_t *buffer, uint8_t length);
uint8_t NRF24L01_WriteBuf(uint8_t address, uint8_t *buffer, uint8_t length);
uint8_t NRF24L01_Check(void);
void NRF24L01_TxMode(uint8_t chan);
uint8_t NRF24L01_TxPacket(uint8_t *buffer, uint8_t size);
void NRF24L01_RxMode(uint8_t chan, uint8_t psize);
uint8_t NRF24L01_RxPacket(uint8_t *buffer, uint8_t size);


#endif /* INC_NRF24L01_H_ */
