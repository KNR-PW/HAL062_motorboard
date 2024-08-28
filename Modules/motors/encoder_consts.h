/*
 ******************************************************************************
 * @file           : encoder_consts.h
 * @author         : D. Mucha
 * @brief          : Provides constants to encoder control
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_ENCODER_CONSTS_H
#define MODULES_MOTORS_ENCODER_CONSTS_H

#include <stm32f4xx_hal_gpio.h>

#define ENCODER1_PORT GPIOA
#define ENCODER2_A_PORT GPIOA
#define ENCODER2_B_PORT GPIOB /* only encoder output on port B */
#define ENCODER3_PORT GPIOA
#define ENCODER1_A_PIN GPIO_PIN_8
#define ENCODER1_B_PIN GPIO_PIN_9
#define ENCODER2_A_PIN GPIO_PIN_5
#define ENCODER2_B_PIN GPIO_PIN_3
#define ENCODER3_A_PIN GPIO_PIN_6
#define ENCODER3_B_PIN GPIO_PIN_7

/* contains information of max pulse count*/
#define ENC_MAX_PULSE_VALUE 20000

/* contains information of numbers of pulse per whole rotation*/
#define ENC_PULSE_PER_ROTATION 1024


#define VELOCITY_CLOCK_TIME 100 //in ms

#endif /* MODULES_MOTORS_ENCODER_CONSTS_H */
