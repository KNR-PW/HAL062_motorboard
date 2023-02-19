/*
 ******************************************************************************
 * @file           : timers.h
 * @author         : D. Mucha
 * @brief          : Timers configuration
 ******************************************************************************
 */

#ifndef MOTORS_TIMERS_H_
#define MOTORS_TIMERS_H_

#include <stm32f4xx_hal.h>

// [Timer - Encoder - Pin] mapping for our custom motor board
// TIM1_CH1 - ENK1_A - PA8
// TIM1_CH2 - ENK1_B - PA9
// TIM2_CH1 - ENK2_A - PA5
// TIM2_CH2 - ENK2_B - PB3
// TIM3_CH1 - ENK3_A - PA6
// TIM3_CH2 - ENK3_B - PA7

// [Timer - PWM - Pin] PWM generation for our custom motor board
// TIM5_CH1 - PWM1 - PA0
// TIM5_CH2 - PWM2 - PA1
// TIM5_CH3 - PWM3 - PA2

extern int32_t g_encoder1Tick;
extern int32_t g_encoder2Tick;
extern int32_t g_encoder3Tick;


extern TIM_HandleTypeDef htim1; //encoder 1 - TIM1
extern TIM_HandleTypeDef htim2; // encoder 2 - TIM2
extern TIM_HandleTypeDef htim3; // encoder 3 - TIM3
extern TIM_HandleTypeDef htim5; // PWM 1,2,3 - TIM5
extern TIM_HandleTypeDef htim7; // measuring speed - TIM14

// @brief Initialize all timers
void InitTimers();

// @brief Initialize encoder1 timer
void TIM1_Init();

// @brief Initialize encoder2 timer
void TIM2_Init();

// @brief Initialize encoder3 timer
void TIM3_Init();

// @brief Initialize PWM timer
void TIM5_Init();

// @brief Initialize timer for measuring speed
void TIM7_Init(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* MOTORS_TIMERS_H_ */
