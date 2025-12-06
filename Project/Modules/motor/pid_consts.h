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

#define TP 0.1
#define PID_K 3.5
#define PID_TD 0
#define PID_TI 1.0

const float R0 = (PID_K * (1 + TP / (2 * PID_TI) + PID_TD / TP));
const float R1 = (PID_K * (TP / (2 * PID_TI) - 2 * PID_TD / TP - 1));
const float R2 = (PID_K * PID_TD / TP);

#endif /* MODULES_MOTORS_PID_CONSTS_H */
