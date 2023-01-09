/*
 ******************************************************************************
 * @file           : motor_controller.c
 * @author         : D. Mucha
 * @brief          : Motors' driver
 ******************************************************************************
 */
#include "motor_controller.h"
#include "consts.h"

int16_t PIDSpeedController(float referenceSpeed, float actualSpeed,
		float currentRegOut) {
	float integrator_speed = 0;
	float speed_error = 0;
	static int16_t saturation;
	speed_error = referenceSpeed - actualSpeed;
	// TODO: no idea how this regulator is actually working:
	// PID_SPEED_KiTs * speed_error - probably proportional term
	// the rest is unclear to me
	integrator_speed += (PID_SPEED_KiTs * speed_error
			+ (saturation * PID_SPEED_Kk) + (currentRegOut * PID_SPEED_Kk));
	int16_t out = (int16_t) (PID_SPEED_Kp * speed_error + integrator_speed);

	// TODO: I'm not sure what these ifs do exactly
	if (referenceSpeed > 0) {
		if (out >= (PWM_MAX_DUTY - 50)) {
			saturation = -out + (PWM_MAX_DUTY - 50);
			out = PWM_MAX_DUTY - 50;
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
		} else if (out <= -(PWM_MAX_DUTY - 50)) {
			saturation = -out - (PWM_MAX_DUTY - 50);
			out = -(PWM_MAX_DUTY - 50);
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
		raw_speed = 100000 / encoder_ticks;
	} else {
		raw_speed = 0;
	}
	float lpf_speed = lowPassFilter(raw_speed, prev_out);
	return lpf_speed;
}

