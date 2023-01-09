/*
 * @file consts.h
 * @brief Provides constants to motors control
 */

#ifndef MODULES_MOTORS_CONSTS_H
#define MODULES_MOTORS_CONSTS_H

#include "stm32f4xx_hal_gpio.h"

#define PWM_PORT GPIOA
#define PWM1_PIN GPIO_PIN_0
#define PWM2_PIN GPIO_PIN_0
#define PWM3_PIN GPIO_PIN_0

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

// maximal speed
const int MAX_BOARD_SPEED = 2000;
// speed ramp (higher value causes slower acceleration)
const int PID_SPEED_RAMP = 1;

// TODO: no idea how to name this pid constant setting
const float PID_SPEED_Kp = 0.01;
// TODO: no idea how to name this pid constant setting
const int PID_SPEED_Kk = 1;
// TODO: no idea how to name this pid constant setting
const float PID_SPEED_KiTs = 0.0003;

// alpha parameter of LPF filter (alpha = dt / (RC + dt))
const float LPF_ALPHA = 1;

#endif /* MODULES_MOTORS_CONSTS_H */
