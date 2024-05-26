#include "main.h"

UART_HandleTypeDef UartHandle;
static uint8_t aTxBuffer[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static uint8_t aRxBuffer[12] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
// static __IO ITStatus UartReady = RESET;


void Error_Handler(void);
void APP_LED_Init(void);
void APP_USARTConfig(void);

int main(void)
{
	HAL_StatusTypeDef status;
	
  HAL_Init();
  APP_LED_Init();
  APP_USARTConfig(); 

  while (1)
  {
		// 都不满 12 byte 会超时。这个比中断差就差在数据要是固定长度。
		status = HAL_UART_Receive(&UartHandle, (uint8_t *)aRxBuffer, 12, 400);
    if (status == HAL_OK)
    {
			HAL_Delay(40);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

			// echo 回去
			status = HAL_UART_Transmit(&UartHandle, (uint8_t *)aRxBuffer, 12, 4000);
			if (status != HAL_OK)
			{
				Error_Handler();
			}
		}
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
    GPIO_InitStruct.Pin       = GPIO_PIN_2;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin	 			= GPIO_PIN_7;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
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


void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}
