/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "nrf24l01.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOC
#define KEY_L_Pin GPIO_PIN_2
#define KEY_L_GPIO_Port GPIOC
#define KEY_H_Pin GPIO_PIN_3
#define KEY_H_GPIO_Port GPIOC
#define NRF24L01_IRQ_Pin GPIO_PIN_0
#define NRF24L01_IRQ_GPIO_Port GPIOB
#define NRF24L01_CSN_Pin GPIO_PIN_1
#define NRF24L01_CSN_GPIO_Port GPIOB
#define NRF24L01_CE_Pin GPIO_PIN_2
#define NRF24L01_CE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
