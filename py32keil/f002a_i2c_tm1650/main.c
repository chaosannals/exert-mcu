/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define DATA_LENGTH      15                 /*数据长度*/
#define I2C_ADDRESS      0xA0               /*本机地址0xA0*/
#define I2C_SPEEDCLOCK   100000             /*通讯速度100K*/
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_16_9 /*占空比*/
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef I2cHandle;
uint8_t aTxBuffer[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t aRxBuffer[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_CheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  I2cHandle.Instance             = I2C;                                                                    /*I2C*/
  I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;                                                        /*I2C通讯速度*/
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;                                                         /*I2C占空比*/
  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;                                                           /*I2C地址*/
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;                                               /*禁止广播呼叫*/
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;                                                 /*允许时钟延长*/

  if (HAL_I2C_Init(&I2cHandle) != HAL_OK)                                                                 /*I2C初始化*/
  {
    APP_Error_Handler();
  }
  /*等待用户按键按下，主机程序开始运行*/
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }

  /*I2C主机中断方式发送*/
  while (HAL_I2C_Master_Transmit(&I2cHandle, I2C_ADDRESS, (uint8_t *)aTxBuffer, DATA_LENGTH,5000) != HAL_OK)
  {
    APP_Error_Handler();
  }
  /*判断当前I2C状态*/
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);
  /*I2C主机中断方式接收*/
  while (HAL_I2C_Master_Receive(&I2cHandle, I2C_ADDRESS, (uint8_t *)aRxBuffer, DATA_LENGTH,5000) != HAL_OK)
  {
    APP_Error_Handler();
  }
  
  /* Check the current I2C state */
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);
  
  /* Check the received data */
  APP_CheckEndOfTransfer();
  
  while (1)
  {

  }
}

/**
  * @brief  Data verification function
  * @param  None
  * @retval None
  */
static void APP_CheckEndOfTransfer(void)
{
  /* Compare the transmitted data with the received data */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, DATA_LENGTH))
  {
    /* Error handling */
    APP_LedBlinking();
  }
  else
  {
    /* If data received successfully, turn on the LED */
    BSP_LED_On(LED_GREEN);
  }
}

/**
  * @brief  Character comparison function
  * @param  pBuffer1：Pointer to the first buffer to be compared
  * @param  pBuffer2：Pointer to the second buffer to be compared
  * @param  BufferLength：Number of characters to compare
  * @retval 0: buffers are the same; 1: buffers are different
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  LED blinking function
  * @param  None
  * @retval None
  */
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);; 
    HAL_Delay(500);
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_Error_Handler(void)
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
