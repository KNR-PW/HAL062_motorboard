/*
 * @file motor_interface.h
 * @brief Provides high level motors control
 */

#ifndef MODULES_MOTORS_MOTOR_INTERFACE_H
#define MODULES_MOTORS_MOTOR_INTERFACE_H

#include "stdbool.h"

// @brief LEDs ID structure
// names corresponds to following designations of rover's wheels:
// LF - left front
// LM - left middle
// LR - left rear
// RF - right front
// RM - right middle
// RR - right rear
typedef enum {
	LF, LM, LR, RF, RM, RR
} MOTOR_ID;

// @brief Command of speed to be set to single motor
struct singleMotorParam {
	// id of motor (defined by MOTOR_ID structure)
	MOTOR_ID id;
	// speed of motor (value from -100 to 100)
	int speed;
};

// variable stores speed of motor1 form previous step
float previousSpeedMotor1 = 0;
// variable stores speed of motor2 form previous step
float previousSpeedMotor2 = 0;
// variable stores speed of motor3 form previous step
float previousSpeedMotor3 = 0;

// variable stores output of PID controller for motor1
float PIDOutMotor1 = 0;
// variable stores output of PID controller for motor2
float PIDOutMotor2 = 0;
// variable stores output of PID controller for motor3
float PIDOutMotor3 = 0;

// @brief High-level function that should be placed in a continuous loop to control the speed of motors
// @param params array of singleMotorParam structures for 3 motors from one side of the rover
// @param array_length length of params array (is anticipated to be always 3 - 3 motors connected to one board)
// @returns true if iteration succeeded, false otherwise
bool setOneSideSpeeds(struct singleMotorParam *params, int array_length);

#endif /* MODULES_MOTORS_MOTOR_INTERFACE_H */
