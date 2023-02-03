/*
 ******************************************************************************
 * @file           : pwm.h
 * @author         : K. Czechowicz, A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#ifndef MOTORS_PWM_H_
#define MOTORS_PWM_H_

typedef enum {
	CHANNEL1 = TIM_CHANNEL_1, // PWM1
	CHANNEL2 = TIM_CHANNEL_2, // PWM2
	CHANNEL3 = TIM_CHANNEL_3, // PWM3
} ChannelType;

HAL_StatusTypeDef PWM_Init();

// @brief required motor calibration before first usage
// @param channel enum type number of channel to precise motor
void motor_calibration(ChannelType channel);

// @brief Setting duty of motors PWM
// @param channel enum type number of channel to precise motor
// @param duty duty chosen from 500 to 1000
// @returns predefined enum status type from HAL library
HAL_StatusTypeDef PWM_SetDutyCycle(ChannelType channel, uint16_t duty);

#endif //MOTORS_PWM_H_
