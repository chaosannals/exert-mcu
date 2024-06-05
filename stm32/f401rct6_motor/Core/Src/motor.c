#include "stm32f4xx_hal.h"
#include "motor.h"

void PWM_SetPulse(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t value);
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

void Motor_SetX(int16_t v) {
	if (v == 0) {
		HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);
	} else if(v > 0) {
		HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
		PWM_SetPulse(&htim10, TIM_CHANNEL_1, 2000 - v);
	} else {
		HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);
		PWM_SetPulse(&htim11, TIM_CHANNEL_1, 2000 + v);
	}
}

void Motor_SetY(int16_t v) {
	if (v == 0) {
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	} else if (v > 0) {
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		PWM_SetPulse(&htim4, TIM_CHANNEL_2, 2000 - v);
	} else {
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
		PWM_SetPulse(&htim4, TIM_CHANNEL_1, 2000 + v);
	}
}
