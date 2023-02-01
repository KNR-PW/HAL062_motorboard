/*
 ******************************************************************************
 * @file           : timers.c
 * @author         : D. Mucha, K. Czechowicz, A. Rybojad
 * @brief          : Timers configuration
 ******************************************************************************
 */

#include <stm32f4xx_hal.h> // this include replaces including <stm32f4xx_hal_tim.h>,
// including only <stm32f4xx_hal_tim.h> causes compilation errors
#include "timers.h"
#include "pwm_consts.h"
#include "encoder_consts.h"
#include "tim_handlers.h"

TIM_HandleTypeDef htim1; //encoder 1 - TIM1
TIM_HandleTypeDef htim2; // encoder 2 - TIM2
TIM_HandleTypeDef htim3; // encoder 3 - TIM3
TIM_HandleTypeDef htim5; // PWM 1,2,3 - TIM5
TIM_HandleTypeDef htim7; // measuring speed - TIM14

/* number of pulse that encoder count */
volatile uint16_t enc1PulseNumber;
volatile uint16_t enc2PulseNumber;
volatile uint16_t enc3PulseNumber;

/* number of pulse that encoder generates per second */
volatile int16_t enc1PulsePerSec;
volatile int16_t enc2PulsePerSec;
volatile int16_t enc3PulsePerSec;

/* angular value of motors */
volatile int16_t motor1Velocity;
volatile int16_t motor2Velocity;
volatile int16_t motor3Velocity;

void InitTimers() {
	TIM1_Init();
	TIM2_Init();
	TIM3_Init();
	TIM5_Init();
	TIM7_Init();
}

void TIM1_Init() {

	TIM_Encoder_InitTypeDef sConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = ENC3_MAX_PULSE_VALUE;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK) {
		//TODO: error handling needed
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		//TODO: error handling needed
	}
	if (HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL) != HAL_OK) {
		// TODO: error handling needed
	}

}

void TIM2_Init() {
	TIM_Encoder_InitTypeDef sConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = ENC2_MAX_PULSE_VALUE;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK) {
		//TODO: error handling needed
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		//TODO: error handling needed
	}
	if (HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL) != HAL_OK) {
		// TODO: error handling needed
	}
}

void TIM3_Init() {
	TIM_Encoder_InitTypeDef sConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = ENC3_MAX_PULSE_VALUE;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK) {
		//TODO: error handling needed
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		//TODO: error handling needed
	}
	if (HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL) != HAL_OK) {
		// TODO: error handling needed
	}
}

void TIM5_Init() {
	htim5.Instance = TIM5;
	htim5.Init.Prescaler = PWM_PRESCALER;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = PWM_MAX_DUTY;
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim5.Init.RepetitionCounter = PWM_REPETITION_COUNTER;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_PWM_Init(&htim5) != HAL_OK) {
		// TODO: error handling needed
	}
	if (HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2 | TIM_CHANNEL_3)
			!= HAL_OK) {
		// TODO: error handling needed
	}
}

void TIM7_Init(void) {
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 15999;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Period = VELOCITY_CLOCK_TIME - 1;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim7) != HAL_OK) {
		// TODO: error handling needed
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig)
			!= HAL_OK) {
		// TODO: error handling needed
	}
	HAL_TIM_Base_Start_IT(&htim7);
}

void TIM7_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htim7);

}

/* overwritten weak msp functions (gpio and clock config)*/

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim_encoder) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	if (htim_encoder->Instance == TIM1) {
		/* Peripheral clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/**TIM1 GPIO Configuration
		 PA8     ------> TIM1_CH1
		 PA9     ------> TIM1_CH2
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	} else if (htim_encoder->Instance == TIM2) {
		/* Peripheral clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/**TIM2 GPIO Configuration
		 PA5     ------> TIM2_CH1
		 PB3     ------> TIM2_CH2
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	else if (htim_encoder->Instance == TIM3) {
		/* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/**TIM3 GPIO Configuration
		 PA6     ------> TIM3_CH1
		 PA7     ------> TIM3_CH2
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim_pwm) {
	if (htim_pwm->Instance == TIM5) {
		/* Peripheral clock enable */
		__HAL_RCC_TIM5_CLK_ENABLE();
	}
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (htim->Instance == TIM5) {
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
	}
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim_base) {
	if (htim_base->Instance == TIM7) {
		/* Peripheral clock enable */
		__HAL_RCC_TIM7_CLK_ENABLE();
		/* TIM7 interrupt Init */
		HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
	}

}

// @brief interrupt for angular speed calculation
// @param htim handler for TIM7 interrupt clock
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM7) {

		// getting actual position of encoder
		enc1PulseNumber = __HAL_TIM_GET_COUNTER(&htim1);
		enc2PulseNumber = __HAL_TIM_GET_COUNTER(&htim2);
		enc3PulseNumber = __HAL_TIM_GET_COUNTER(&htim3);

		// checking if direction is negative
		// if position decreases from high value then direction is negative
		// uint16_t converted to int16_t and set as negative value
		if (enc1PulseNumber > ENC1_MAX_PULSE_VALUE / 2) {
			enc1PulseNumber = ENC1_MAX_PULSE_VALUE - enc1PulseNumber;
			enc1PulseNumber = (int16_t) enc1PulseNumber;
			enc1PulseNumber = -1 * enc1PulseNumber;
		} else
			(int16_t) enc1PulseNumber;

		if (enc2PulseNumber > ENC2_MAX_PULSE_VALUE / 2) {
			enc2PulseNumber = ENC2_MAX_PULSE_VALUE - enc2PulseNumber;
			enc2PulseNumber = (int16_t) enc2PulseNumber;
			enc2PulseNumber = -1 * enc2PulseNumber;
		} else
			(int16_t) enc2PulseNumber;

		if (enc3PulseNumber > ENC3_MAX_PULSE_VALUE / 2) {
			enc3PulseNumber = ENC3_MAX_PULSE_VALUE - enc3PulseNumber;
			enc3PulseNumber = (int16_t) enc3PulseNumber;
			enc3PulseNumber = -1 * enc3PulseNumber;
		} else
			(int16_t) enc3PulseNumber;

		// evaluating number of pulses occured in one sec
		enc1PulsePerSec = enc1PulseNumber * 1000 / VELOCITY_CLOCK_TIME;
		enc2PulsePerSec = enc2PulseNumber * 1000 / VELOCITY_CLOCK_TIME;
		enc3PulsePerSec = enc3PulseNumber * 1000 / VELOCITY_CLOCK_TIME;

		// evaluating angular speed basing on encoder resolution
		motor1Velocity = enc1PulsePerSec / ENC1_PULSE_PER_ROTATION;
		motor2Velocity = enc2PulsePerSec / ENC2_PULSE_PER_ROTATION;
		motor3Velocity = enc3PulsePerSec / ENC3_PULSE_PER_ROTATION;

		// resetting counter for next interrupt
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
	}
}

HAL_StatusTypeDef PWM_SetDutyCycle(ChannelType channel, uint16_t duty) {
	__HAL_TIM_SET_COMPARE(&htim5, channel, duty);
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
