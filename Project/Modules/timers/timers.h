/*
 ******************************************************************************
 * @file           : timers.h
 * @author         : D. Mucha
 * @brief          : Timers configuration
 ******************************************************************************
 */

#ifndef MOTORS_TIMERS_H_
#define MOTORS_TIMERS_H_

#include <stm32f1xx_hal.h>

extern TIM_HandleTypeDef *tim_encoder; //encoder - TIM3
extern TIM_HandleTypeDef *tim_pwm; // PWM - TIM2
extern TIM_HandleTypeDef *tim_speed; // measuring speed - TIM4
extern TIM_HandleTypeDef *tim_comwdg;

void TIM_init(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* MOTORS_TIMERS_H_ */
