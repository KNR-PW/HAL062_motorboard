/*
 ******************************************************************************
 * @file           : pwm.c
 * @author         : K. Czechowicz, A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#include <stm32f4xx_hal.h>
#include "pwm.h"
#include "timers.h"

TIM_HandleTypeDef hPwm;

HAL_StatusTypeDef PWM_Init() {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	__HAL_RCC_TIM5_CLK_ENABLE();	// 16MHz

	hPwm.Instance = TIM5;
	hPwm.Init.Prescaler = 160-1;
	hPwm.Init.CounterMode = TIM_COUNTERMODE_UP;
	hPwm.Init.Period = 9999;
	hPwm.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hPwm.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_PWM_Init(&hPwm) != HAL_OK) {
		//Error_Handler();
		return HAL_ERROR;
	}

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM5 GPIO Configuration
		 PA0-WKUP     ------> TIM5_CH1
		 PA1     ------> TIM5_CH2
		 PA2     ------> TIM5_CH3
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(&hPwm, &sMasterConfig)
			!= HAL_OK) {
		//Error_Handler();
		return HAL_ERROR;
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	if (HAL_TIM_PWM_ConfigChannel(&hPwm, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
		//Error_Handler();
		return HAL_ERROR;
	}
	if (HAL_TIM_PWM_ConfigChannel(&hPwm, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
		//Error_Handler();
		return HAL_ERROR;
	}
	if (HAL_TIM_PWM_ConfigChannel(&hPwm, &sConfigOC, TIM_CHANNEL_3) != HAL_OK) {
		//Error_Handler();
		return HAL_ERROR;
	}


	HAL_TIM_PWM_Start(&hPwm, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&hPwm, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&hPwm, TIM_CHANNEL_3);

	PWM_SetDutyCycle(TIM_CHANNEL_1, 750);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 750);
	PWM_SetDutyCycle(TIM_CHANNEL_3, 750);

	return HAL_OK;
}


HAL_StatusTypeDef PWM_SetDutyCycle(ChannelType channel, uint16_t duty) {
	__HAL_TIM_SET_COMPARE(&hPwm, channel, duty);
	return HAL_OK;
}

void motor_calibration(ChannelType channel) {
	PWM_SetDutyCycle(channel, 1000);
	HAL_Delay(5000);
	PWM_SetDutyCycle(channel, 500);
	HAL_Delay(5000);
	PWM_SetDutyCycle(channel, 750);
	HAL_Delay(5000);
}
