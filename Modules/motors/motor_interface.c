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
#include "pwm.h"
//#include <stddef.h>
//#include <stdint.h>

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

struct singleMotorParam param[3];
enum motorSide side = RIGHT_SIDE;

struct Map speed_map[3] = { { .key = 0, .ptr = &previousSpeedMotor1 }, { .key =
		1, .ptr = &previousSpeedMotor2 }, { .key = 2, .ptr =
		&previousSpeedMotor3 } };

struct Map PID_map[3] = { { .key = 0, .ptr = &PIDOutMotor1 }, { .key = 1, .ptr =
		&PIDOutMotor2 }, { .key = 2, .ptr = &PIDOutMotor3 } };

bool setOneSideSpeeds(struct singleMotorParam *params, int array_length) {
	// non-const map (because of extern variables) has to be created in execution time
	struct Map encoders_map[3] = { { .key = 0, .ptr = &g_encoder1Tick }, {
			.key = 1, .ptr = &g_encoder2Tick }, { .key = 2, .ptr =
			&g_encoder3Tick }, };
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

//	 setting PWM duty to concrete channel;
	for (uint8_t i = 0; i < 3; i++) {
		if (params[i].id == LR || params[i].id == RR) {
//	            old_duty = hPwm.Instance->CCR1;
//			if (750 + *(float*) PID_map[i].ptr > PWM_MAX_DUTY)
//				PWM_SetDutyCycle(CHANNEL1, PWM_MAX_DUTY);
//			else if (750 + *(float*) PID_map[i].ptr < PWM_MIN_DUTY)
//				PWM_SetDutyCycle(CHANNEL1, PWM_MIN_DUTY);
//			else
				PWM_SetDutyCycle(CHANNEL1, 750 + *(float*) PID_map[i].ptr);
		}
		if (params[i].id == LM || params[i].id == RM) {
//	            old_duty = hPwm.Instance->CCR2;
//			if (750 + *(float*) PID_map[i].ptr > PWM_MAX_DUTY)
//				PWM_SetDutyCycle(CHANNEL2, PWM_MAX_DUTY);
//			else if (750 + *(float*) PID_map[i].ptr < PWM_MIN_DUTY)
//				PWM_SetDutyCycle(CHANNEL2, PWM_MIN_DUTY);
//			else
				PWM_SetDutyCycle(CHANNEL2, 750 + *(float*) PID_map[i].ptr);
		}
		if (params[i].id == LF || params[i].id == RF) {
//	            old_duty = hPwm.Instance->CCR3;
//			if (750 + *(float*) PID_map[i].ptr > PWM_MAX_DUTY)
//				PWM_SetDutyCycle(CHANNEL3, PWM_MAX_DUTY);
//			else if (750 + *(float*) PID_map[i].ptr < PWM_MIN_DUTY)
//				PWM_SetDutyCycle(CHANNEL3, PWM_MIN_DUTY);
//			else
				PWM_SetDutyCycle(CHANNEL3, 750 + *(float*) PID_map[i].ptr);
		}
	}

	return true;
}

bool updateSpeed(int speed) {

	if (side == LEFT_SIDE) {
		param[0].speed = speed;
		param[0].id = LR;
		param[1].speed = speed;
		param[1].id = LM;
		param[2].speed = speed;
		param[2].id = LF;
	}
	if (side == RIGHT_SIDE) {
		param[0].speed = speed;
		param[0].id = RR;
		param[1].speed = speed;
		param[1].id = RM;
		param[2].speed = speed;
		param[2].id = RF;
	}

	return 0;
}

bool updatePID() {
	setOneSideSpeeds(param, 3);
	return 0;
}

