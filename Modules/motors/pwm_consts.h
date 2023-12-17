/*
 ******************************************************************************
 * @file           : pwm_consts.h
 * @author         : A.Rybojad
 * @brief          : Provides constants to PWM control
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_PWM_CONSTS_H
#define MODULES_MOTORS_PWM_CONSTS_H

#include <stm32f4xx_hal_gpio.h>

#define PWM_PORT GPIOA
#define PWM1_PIN GPIO_PIN_0
#define PWM2_PIN GPIO_PIN_1
#define PWM3_PIN GPIO_PIN_2

/* PWM constants for MAX motor drivers
 * Resolution is adjusted such as 7500 is the middle */

#define MAX_MOTOR_DURATION 0.002 /*!< Maximum duty cycle for maxon is 2ms signal !>*/

#define MAX_MOTOR_DUTY 10000 /*!< Maximum duty cycle for maxon is 2ms signal !>*/
#define MID_MOTOR_DUTY 7500 /*!< Middle duty cycle for maxon is 1.5ms signal !>*/
#define MIN_MOTOR_DUTY 5000 /*!< Minimum duty cycle for maxon is 1ms signal !>*/

/* PWM_PERIOD_DURATION must be equal to MAX_MOTOR_DUTY * MAX_MOTOR_DURATION */
const uint32_t PWM_PERIOD_DURATION = MAX_MOTOR_DUTY * MAX_MOTOR_DURATION; /*!< Whole period must be 20ms for maxon !>*/

const uint32_t TIM_CLK_FRQ = 80000000; /*!< Frequency of APB1 timers !>*/
const uint32_t PWM_PRESCALER = 16-1;
const uint32_t TIM_TICK_FRQ = TIM_CLK_FRQ / (PWM_PRESCALER+1); /*!< Frequency of tick in PWM timer !>*/


/* PWM constants for 80/40MHz clock */
//const uint32_t PWM_PERIOD = 100000-1;
const uint32_t PWM_PERIOD = (TIM_TICK_FRQ/PWM_PERIOD_DURATION) -1;
const uint32_t PWM_REPETITION_COUNTER = 1;

#endif /* MODULES_MOTORS_PWM_CONSTS_H */
