/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef UartHandle;
static uint8_t aTxBuffer[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static uint8_t aRxBuffer[12] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
void APP_LED_Init(void);
void APP_USARTConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  APP_LED_Init();
  APP_USARTConfig(); 

  /*通过中断方式接收数据*/
  if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t *)aTxBuffer, 12) != HAL_OK)
  {
    Error_Handler();
  }
  while (1)
  {
			HAL_Delay(40);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  }
}

void APP_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();                        

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief  USART配置函数
  * @param  无
  * @retval 无
  */
void APP_USARTConfig(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
	
  /* USART1初始化 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	
	/* GPIO初始化
    PA7 TX,PB2 RX
  */
	GPIO_InitStruct.Pin       = GPIO_PIN_7;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	/*USART1中断使能*/
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	
  UartHandle.Instance          = USART1;
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  
  if (HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  USART错误回调执行函数，输出错误代码
  * @param  无
  * @retval 无
  */
 void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  printf("Uart Error, ErrorCode = %d\r\n", huart->ErrorCode);
}
/**
  * @brief  USART发送回调执行函数
  * @param  无
  * @retval 无
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *uartHandle)
{
  /*通过中断方式接收数据*/
  if (HAL_UART_Receive_IT(uartHandle, (uint8_t *)aRxBuffer, 12) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  USART接收回调执行函数
  * @param  无
  * @retval 无
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uartHandle)
{
  /*通过中断方式接收数据*/
  if (HAL_UART_Transmit_IT(uartHandle, (uint8_t *)aRxBuffer, 12) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
