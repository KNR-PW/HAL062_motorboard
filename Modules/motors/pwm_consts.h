/*
 ******************************************************************************
 * @file           : pwm_consts.h
 * @author         : D. Mucha
 * @brief          : Provides constants to pwm control
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_PWM_CONSTS_H
#define MODULES_MOTORS_PWM_CONSTS_H

#include <stm32f4xx_hal_gpio.h>

#define PWM_PORT GPIOA
#define PWM1_PIN GPIO_PIN_0
#define PWM2_PIN GPIO_PIN_1
#define PWM3_PIN GPIO_PIN_2

/* PWM constants for 16MHz clock */
const uint32_t PWM_PRESCALER = 32-1;
const uint32_t PWM_PERIOD = 10000-1;
const uint32_t PWM_REPETITION_COUNTER = 1;

#endif /* MODULES_MOTORS_PWM_CONSTS_H */
