/*
 ******************************************************************************
 * @file           : motor_controller.c
 * @author         : D. Mucha
 * @brief          : Motors' driver
 ******************************************************************************
 */

#include "motor_controller.h"
#include "control_consts.h"
#include "encoder_consts.h"

static float prev_error_1 = 0;
static float prev_prev_error_1 = 0;
static float speed_error_1 = 0;
static float u_1 = 0;

static float prev_error_2 = 0;
static float prev_prev_error_2 = 0;
static float speed_error_2 = 0;
static float u_2 = 0;

static float prev_error_3 = 0;
static float prev_prev_error_3 = 0;
static float speed_error_3 = 0;
static float u_3 = 0;

float PIDSpeedController(float referenceSpeed, float actualSpeed,
		float prev_u, int i) {


	int16_t out;

	if (i == 0){
	speed_error_1 = referenceSpeed - actualSpeed;
	u_1 = r2 * prev_prev_error_1 + r1 * prev_error_1 + r0 * speed_error_1 + prev_u;

	prev_prev_error_1 = prev_error_1;
	prev_error_1 = speed_error_1;


	out = (int16_t)(u_1);
	}
	else if(i==1){
	speed_error_2 = referenceSpeed - actualSpeed;
	u_2 = r2 * prev_prev_error_2 + r1 * prev_error_2 + r0 * speed_error_2 + prev_u;

	prev_prev_error_2 = prev_error_2;
	prev_error_2 = speed_error_2;


	out = (int16_t)(u_2);

	}
	else{
	speed_error_3 = referenceSpeed - actualSpeed;
	u_3 = r2 * prev_prev_error_3 + r1 * prev_error_3 + r0 * speed_error_3 + prev_u;

	prev_prev_error_3 = prev_error_3;
	prev_error_3 = speed_error_3;


	out = (int16_t)(u_3);
	}

//	if(out > 1000) out = 1000;
//	else if(out < -1000) out = -1000;

	if(referenceSpeed == 0){
		out = 0;
	}

	return out;

}

float lowPassFilter(float curr_in, float *prev_out) {
	float out;
	if (curr_in != 0) {
		out = LPF_ALPHA * curr_in + (1 - LPF_ALPHA) * (*prev_out);
		*prev_out = out;
		return out;
	} else {
		*prev_out = 0;
		return 0;
	}
}

float getFilteredSpeed(int32_t encoder_ticks){
	static float raw_speed;
	if (encoder_ticks != 0) {
		if (encoder_ticks > ENC_MAX_PULSE_VALUE / 2.0)
			encoder_ticks = encoder_ticks - ENC_MAX_PULSE_VALUE;
		raw_speed = (float)encoder_ticks * 1000.0/((float)VELOCITY_CLOCK_TIME * (float)ENC_PULSE_PER_ROTATION);
	} else {
		raw_speed = 0.0;
	}
	raw_speed = 100.0*raw_speed*3.0; // 100 is 1 rotate per sec
//	float lpf_speed = lowPassFilter(raw_speed, prev_out);

	return raw_speed;
}

