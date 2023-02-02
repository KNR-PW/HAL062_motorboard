/*
 ******************************************************************************
 * @file           : motor_interface.c
 * @author         : D. Mucha
 * @brief          : Provides high level motors control
 ******************************************************************************
 */

#include "motor_interface.h"
#include "motor_controller.h"
#include "timers.h"
#include <stddef.h>
#include <stdint.h>

// @brief structre Map allows to map sequence numbers in loops to pointers of specific variables
struct Map {
	int key;
	void *ptr;
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

struct Map speed_map[3] = { { .key = 0, .ptr = &previousSpeedMotor1 }, { .key =
		1, .ptr = &previousSpeedMotor2 }, { .key = 2, .ptr =
		&previousSpeedMotor3 } };

struct Map PID_map[3] = { { .key = 0, .ptr = &PIDOutMotor1 }, { .key = 1, .ptr =
		&PIDOutMotor2 }, { .key = 2, .ptr = &PIDOutMotor3 } };

bool setOneSideSpeeds(struct singleMotorParam *params, int array_length) {
	// non-const map (because of extern variables) has to be created in execution time
	struct Map encoders_map[3] = { { .key = 0, .ptr = &g_encoder1Tick }, {
			.key = 1, .ptr = &g_encoder2Tick }, { .key = 2, .ptr =
			&g_encoder3Tick } };
	if (params == NULL || array_length == 0) {
		return false;
	}
	int i = 0;
	for (i = 0; i < array_length; i += 1) {
		float filtered_speed = getFilteredSpeed(*(int32_t*) encoders_map[i].ptr,
				speed_map[i].ptr);
		*(float*) PID_map[i].ptr = PIDSpeedController(params[i].speed,
				filtered_speed, *(float*) PID_map[i].ptr);
	}
	return true;
}
