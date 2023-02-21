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

float last_error = 0;
float derivative_error = 0;
float integrator_error = 0;


float PIDSpeedController(float referenceSpeed, float actualSpeed,
		float currentRegOut) {

	float speed_error = 0;
	float integrator_speed = 0;
	static float saturation;

	speed_error = referenceSpeed - actualSpeed;

	//regulation only with integration (no P or D)
	integrator_speed = PID_SPEED_KiTs * speed_error + saturation * PID_SPEED_Kp
			+ currentRegOut * PID_SPEED_Kk;

	float out = (float) integrator_speed;

	//PWM can be sat max as 1000 so in order to remember how much "over" max PWM integrator is, there is saturation
	if (referenceSpeed > 0) {
		if (out >= (PWM_MAX_DUTY - 750)) {
			saturation = -out + (PWM_MAX_DUTY - 750);
			out = PWM_MAX_DUTY - 750;
		} else if (out <= 0) {
			saturation = -out;
			out = 0;
		} else {
			saturation = 0;
		}
	} else if (referenceSpeed < 0) {
		if (out >= 0) {
			saturation = -out;
			out = 0;
		} else if (out <= -(PWM_MAX_DUTY - 750)) {
			saturation = -out - (PWM_MAX_DUTY - 750);
			out = -(PWM_MAX_DUTY - 750);
		} else {
			saturation = 0;
		}
	} else if (referenceSpeed == 0) {
		out = 0;
		integrator_speed = 0;
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

float getFilteredSpeed(int32_t encoder_ticks, float *prev_out) {
	static float raw_speed;
	if (encoder_ticks != 0) {
		// TODO: magic number 100000 - maybe some constant to take transmission into account
//		raw_speed = 100000/encoder_ticks;
		if (encoder_ticks > ENC_MAX_PULSE_VALUE / 2)
			encoder_ticks = encoder_ticks - ENC_MAX_PULSE_VALUE;
		raw_speed = encoder_ticks * 1000
				/ (VELOCITY_CLOCK_TIME * ENC_PULSE_PER_ROTATION);
	} else {
		raw_speed = 0;
	}
	float lpf_speed = lowPassFilter(raw_speed, prev_out);

//	retuen lpf_speed; - temporary skiping filtering speed
	return raw_speed;
}

