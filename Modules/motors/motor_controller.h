/*
 ******************************************************************************
 * @file           : motor_controller.h
 * @author         : D. Mucha
 * @brief          : Provides high level motors control
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_MOTOR_CONTROLLER_H
#define MODULES_MOTORS_MOTOR_CONTROLLER_H

#include <stdint.h>

// TODO: no idea why this is 1000
#define PWM_MAX_DUTY 1000
#define PWM_MIN_DUTY 500

// @brief PID controller algorithm
// @param referenceSpeed reference speed to be reached
// @param actualSpeed true speed at moment of calling the function
// @returns duty of PWM for engine to reach set speed
float PIDSpeedController(float referenceSpeed, float actualSpeed,
		float currentRegOut, int i);

// @brief Low pass filter (LPF) implemented according to wikipedia
// @param curr_in current input
// @param prev_out pointer to output of filter from previous step
// @returns output in current step
float lowPassFilter(float curr_in, float *prev_out);

// @brief Transformation raw encoder data to filtered speed
// @param encoder_ticks raw encoder tick data
// @param prev_out pointer to output of filter from previous step
// @returns output in current step
float getFilteredSpeed(int32_t encoder_ticks);

#endif /* MODULES_MOTORS_MOTOR_CONTROLLER_H */
