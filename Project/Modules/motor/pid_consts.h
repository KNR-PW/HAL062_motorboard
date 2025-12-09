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

extern float TP;
extern float PID_K;
extern float PID_TD;
extern float PID_TI;

#endif /* MODULES_MOTORS_PID_CONSTS_H */
