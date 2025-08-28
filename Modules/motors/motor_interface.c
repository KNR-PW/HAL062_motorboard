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
#include "Can/can.h"

// @brief structre Map allows to map sequence numbers in loops to pointers of specific variables
struct Map {
	int key;
	void *ptr;
};

union Speed {
	float f;
	uint32_t ui;
};

union Speed measured_speed[3] = {0};
uint8_t data_to_send[3][8];

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
//enum motorSide side = RIGHT_SIDE;
enum motorSide side = LEFT_SIDE;

struct Map speed_map[3] = { { .key = 0, .ptr = &previousSpeedMotor1 }, { .key =
		1, .ptr = &previousSpeedMotor2 }, { .key = 2, .ptr =
		&previousSpeedMotor3 } };

struct Map PID_map[3] = { { .key = 0, .ptr = &PIDOutMotor1 }, { .key = 1, .ptr =
		&PIDOutMotor2 }, { .key = 2, .ptr = &PIDOutMotor3 } };

bool setOneSideSpeeds(struct singleMotorParam *params, int array_length) {

	// taking encoders measurements
	struct Map encoders_map[3] = { { .key = 0, .ptr = &g_encoder1Tick }, {
			.key = 1, .ptr = &g_encoder2Tick }, { .key = 2, .ptr =
			&g_encoder3Tick }, };

	// checking if params are set
	if (params == NULL || array_length == 0) {
		return false;
	}

	// calculating speed and current control signal value from PID
	int i = 0;
	for (i = 0; i < array_length; i += 1) {
		union Speed filtered_speed;
		filtered_speed.f = getFilteredSpeed(*(int32_t*) encoders_map[i].ptr,
				speed_map[i].ptr);
		*(float*) PID_map[i].ptr = PIDSpeedController(params[i].speed,
				filtered_speed.f, *(float*) PID_map[i].ptr, i);

		measured_speed[i].f = filtered_speed.f;
//		uint32_t filtered_speed_coded = filtered_speed;
//		uint8_t data[8];
//		data_to_send[i][0] = (filtered_speed.ui&0xFF000000)>>24;
//		data_to_send[i][1] = (filtered_speed.ui&0x00FF0000)>>16;
//		data_to_send[i][2] = (filtered_speed.ui&0x0000FF00)>>8;
//		data_to_send[i][3] = (filtered_speed.ui&0x000000FF);
////		for(uint8_t k = 4; k<8; k++)
////			data[k] = 0;
//		if(side == RIGHT_SIDE)
//		Can_sendMessage(data_to_send[i], 23+i);
//		else
//		Can_sendMessage(data_to_send[i], 26+i);


	}

//	 setting PWM duty to concrete channel;
	for (uint8_t i = 0; i < 3; i++) {
		if (params[i].id == LR || params[i].id == RR) {
			if(params[i].speed > 0)
				PWM_SetDutyCycle(CHANNEL1, 7800 + *(float*) PID_map[i].ptr);
			else if(params[i].speed < 0)
				PWM_SetDutyCycle(CHANNEL1, 7200 + *(float*) PID_map[i].ptr);
			else if(params[i].speed == 0)
				PWM_SetDutyCycle(CHANNEL1, 7500 + *(float*) PID_map[i].ptr);

		}
		if (params[i].id == LM || params[i].id == RM) {
//			if(params[i].speed > 0)
//				PWM_SetDutyCycle(CHANNEL2, 7800 + *(float*) PID_map[i].ptr);
//			else if(params[i].speed < 0)
//				PWM_SetDutyCycle(CHANNEL2, 7200 + *(float*) PID_map[i].ptr);
//			else if(params[i].speed == 0)
//				PWM_SetDutyCycle(CHANNEL2, 7500 + *(float*) PID_map[i].ptr);
		}
		if (params[i].id == LF || params[i].id == RF) {
			if(params[i].speed > 0)
				PWM_SetDutyCycle(CHANNEL3, 7800 + *(float*) PID_map[i].ptr);
			else if(params[i].speed < 0)
				PWM_SetDutyCycle(CHANNEL3, 7200 + *(float*) PID_map[i].ptr);
			else if(params[i].speed == 0)
				PWM_SetDutyCycle(CHANNEL3, 7500 + *(float*) PID_map[i].ptr);
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

bool updateSpeedCam(uint16_t  speed) {

	static uint16_t angle = 0;
	angle = (uint16_t)(speed*50 - 2500);
	if (side == LEFT_SIDE) {

		PWM_SetDutyCycle(CHANNEL2, 7500 + angle);
	}
	if (side == RIGHT_SIDE) {
		PWM_SetDutyCycle(CHANNEL2, 7500 + angle);
	}

	return 0;
}



bool updatePID() {
	setOneSideSpeeds(param, 3);
	return 0;
}

