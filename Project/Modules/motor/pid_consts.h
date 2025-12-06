/*
 ******************************************************************************
 * @file           : control_consts.h
 * @author         : D. Mucha
 * @brief          : Provides constants to general control (regulators, filters)
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_PID_CONSTS_H
#define MODULES_MOTORS_PID_CONSTS_H

#define TICKS_PER_ROTATION 4096
#define VELOCITY_CLOCK_TIME 0.02	// in s
#define WHEEL_RADIUS 15 			// in cm

// 2*pi*r / TICKS_PER_ROTATION / time
const float TICKS_TO_CM_PER_S = (2 * 3.14159 * WHEEL_RADIUS) / (VELOCITY_CLOCK_TIME * TICKS_PER_ROTATION);

float TP = 0.1;

float PID_K = 3.5;
float PID_TD = 0.0;
float PID_TI = 1.0;
float R0;
float R1;
float R2;

#endif /* MODULES_MOTORS_PID_CONSTS_H */
