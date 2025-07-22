/*
 ******************************************************************************
 * @file           : pwm.h
 * @author         : K. Czechowicz, A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#ifndef MOTORS_PWM_H_
#define MOTORS_PWM_H_

extern TIM_HandleTypeDef hPwm;

typedef enum {
	CHANNEL1 = TIM_CHANNEL_1, // PWM1
	CHANNEL2 = TIM_CHANNEL_2, // PWM2
	CHANNEL3 = TIM_CHANNEL_3, // PWM3
} ChannelType;

HAL_StatusTypeDef PWM_Init();
void PWM_SetDutyCycle(uint16_t duty);

#endif //MOTORS_PWM_H_
