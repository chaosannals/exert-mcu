#include "stm32f4xx_hal.h"

#include "nrf24l01.h"

// 地址
#define REG_CONFIG			0x00
#define REG_EN_AA			0x01
#define REG_EN_RXADDR		0x02
#define REG_SETUP_RETR		0x04
#define REG_RF_CH			0x05
#define REG_RF_SETUP		0x06
#define REG_STATUS			0x07
#define REG_RX_ADDR_P0  	0x0A
#define REG_RX_ADDR_P1  	0x0B
#define REG_TX_ADDR 		0x10
#define REG_RX_PW_P0		0x11

// 命令组合宏
#define CMD_W_REG   	0b00100000 //0b001xxxxx
#define CMD_R_RX_PLOAD	0b01100001
#define CMD_W_TX_PLOAD	0b10100000
#define CMD_FLUSH_TX    0b11100001
#define CMD_FLUSH_RX	0b11100010


// REG_STATUS 地址状态掩码
#define MAX_RT			0b00010000 // 4 tx fifo max number
#define TX_DS			0b00100000 // 5 tx fifo data send.
#define RX_DR			0b01000000 // 6 data arrives rx fifo

extern SPI_HandleTypeDef hspi1;

uint8_t pipe0[5] = {0xE1,0xF0,0xF0,0xF0,0xF0};
uint8_t pipe1[5] = {0xD2,0xF0,0xF0,0xF0,0xF0};

void NRF24L01_Init(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // CSN 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // CE 0
	HAL_Delay(1);
}

uint8_t NRF24L01_SendByte(uint8_t data) {
	uint8_t buffer;
	HAL_SPI_TransmitReceive(&hspi1, &data, &buffer, 1, 0x10);
	return buffer;
}

uint8_t NRF24L01_WriteByte(uint8_t address, uint8_t data) {
	uint8_t status;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); //CSN 0
	status = NRF24L01_SendByte(address);
	NRF24L01_SendByte(data);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); //CSN 1
	return status;
}

uint8_t NRF24L01_ReadByte(uint8_t address) {
	uint8_t data;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); //CSN 0
	NRF24L01_SendByte(address);
	data = NRF24L01_SendByte(0xFF);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); //CSN 1
	return data;
}

uint8_t NRF24L01_ReadBuf(uint8_t address, uint8_t *buffer, uint8_t length) {
	uint8_t status;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); //CSN 0
	status = NRF24L01_SendByte(address);
	HAL_SPI_Receive(&hspi1, buffer, length, 0x10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); //CSN 1
	return status;
}

uint8_t NRF24L01_WriteBuf(uint8_t address, uint8_t *buffer, uint8_t length) {
	uint8_t status;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); //CSN 0
	status = NRF24L01_SendByte(address);
	HAL_SPI_Transmit(&hspi1, buffer, length, 0x10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); //CSN 1
	return status;
}

uint8_t NRF24L01_Check(void) {
	int r = 1;
	uint8_t origin[5] = { 0xA5,0xA5,0xA5,0xA5,0xA5 };
	uint8_t result[5] = { 0x00,0x00,0x00,0x00,0x00 };
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // CE 0
	NRF24L01_WriteBuf(CMD_W_REG | REG_TX_ADDR, origin, 5);
	NRF24L01_ReadBuf(REG_TX_ADDR, result, 5);
	for (int i = 0; i < 5; ++i) {
		if (origin[i] != result[i]) {
			r = 0;
			break;
		}
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // CE 1
	return r;
}

void NRF24L01_TxMode(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // CE 0
	NRF24L01_WriteBuf(CMD_W_REG | REG_TX_ADDR, pipe0, 5);
	NRF24L01_WriteBuf(CMD_W_REG | REG_RX_ADDR_P0, pipe0, 5);

	NRF24L01_WriteByte(CMD_W_REG | REG_EN_AA, 0x01); // enable pipe0
	NRF24L01_WriteByte(CMD_W_REG | REG_EN_RXADDR, 0x01); // enable pipe0 rx address
	NRF24L01_WriteByte(CMD_W_REG | REG_SETUP_RETR, 0x1A); // set retry times
	NRF24L01_WriteByte(CMD_W_REG | REG_RF_CH, 0x02); // set rf channel
	NRF24L01_WriteByte(CMD_W_REG | REG_RF_SETUP, 0x0F); // cont_wave
	NRF24L01_WriteByte(CMD_W_REG | REG_CONFIG, 0x0E); // PWR_UP CRCO EN_CRC
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // CE 1
}

uint8_t NRF24L01_TxPacket(uint8_t *buffer, uint8_t size) {
	uint8_t state;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // CE 0
	NRF24L01_WriteBuf(CMD_W_TX_PLOAD, buffer, size);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // CE 1
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) != 0);

	state=NRF24L01_ReadByte(REG_STATUS); // read status
	NRF24L01_WriteByte(CMD_W_REG | REG_STATUS, state); // clear rx_ds / max_rt
	if (state & MAX_RT) {
		NRF24L01_WriteByte(CMD_FLUSH_TX, 0xFF); // clear tx fifo
		return MAX_RT;
	}
	if (state & TX_DS) {
		return TX_DS;
	}
	return 0xFF;
}

void NRF24L01_RxMode(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // CE 0

	NRF24L01_WriteBuf(CMD_W_REG | REG_RX_ADDR_P0, pipe0, 5);
	NRF24L01_WriteByte(CMD_W_REG | REG_EN_AA, 0x01); // enable pipe0
	NRF24L01_WriteByte(CMD_W_REG | REG_EN_RXADDR, 0x01); // enable pipe0 rx address
	NRF24L01_WriteByte(CMD_W_REG | REG_RF_CH, 0x02); // set rf channel
	NRF24L01_WriteByte(CMD_W_REG | REG_RX_PW_P0, 32); // set rf payload width 32bit
	NRF24L01_WriteByte(CMD_W_REG | REG_RF_SETUP, 0x0F); // const_wave
	NRF24L01_WriteByte(CMD_W_REG | REG_CONFIG, 0x0F); // PWR_UP CRCO EN_CRC PRIM_RX

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // CE 1
}


uint8_t NRF24L01_RxPacket(uint8_t *buffer) {
	uint8_t state;
	state = NRF24L01_ReadByte(REG_STATUS);
	NRF24L01_WriteByte(CMD_W_REG | REG_STATUS, state); // clear tx_ds max_rt
	if (state & RX_DR) {
		NRF24L01_ReadBuf(REG_RX_PW_P0, buffer, 5);
		NRF24L01_WriteByte(CMD_FLUSH_RX, 0xFF); // clear rx fifo
		return 1;
	}
	return 0;
}
