#include "motor.h"
#include "pid_consts.h"
#include "timers/timers.h"

extern TIM_HandleTypeDef *tim_pwm;


float TP = 0.1; // 100 ms = 8 Mhz clock / (80 kHz tim7 prescaler * 10 tim7 period) -> encoders measure

float PID_K = 3.5;
float PID_TD = 0.0;
float PID_TI = 1.0;
float R0;
float R1;
float R2;

static float PIDOut = 0.0f;
static float error[3] = {0.0f};
static int16_t speed_modifier = 10; // 10 seems to give best results, TODO find out why and document

float current_speed = 0.0f;
int32_t target_speed = 0;

// min PWM - 64_000*5% = 3_200
// mid PWM - 64_000*7.5% = 4_800
// max PWM - 64_000*10% = 6_400
static void PWM_SetDutyCycle(uint16_t duty) {
	__HAL_TIM_SET_COMPARE(tim_pwm, PWM_CHANNEL, duty);
}

void updatePID(int32_t encoder_ticks) {
	if (encoder_ticks > ENC_MAX_PULSE_VALUE / 2.0)
		encoder_ticks = encoder_ticks - ENC_MAX_PULSE_VALUE;

	current_speed = (float)encoder_ticks * 1000.0f/((float)VELOCITY_CLOCK_TIME * (float)ENC_PULSE_PER_ROTATION);
	current_speed *= speed_modifier; // 100 is 1 rps

	error[0] = (float) target_speed - current_speed;
	error[2] = error[1];
	error[1] = error[0];

	// TODO find the formula for this and paste it in without all this macro math
	R0 = (PID_K * (1 + TP / (2 * PID_TI) + PID_TD / TP));
	R1 = (PID_K * (TP / (2 * PID_TI) - 2 * PID_TD / TP - 1));
	R2 = (PID_K * PID_TD / TP);

	PIDOut = R2*error[2] + R1*error[1] + R0*error[0] + PIDOut;

	if (target_speed == 0) {PIDOut = 0;}

	PWM_SetDutyCycle((uint16_t) (4800 + PIDOut));
}

// unused?
void motor_calibration(void) {
	PWM_SetDutyCycle(10000);
	HAL_Delay(5000);
	PWM_SetDutyCycle(5000);
	HAL_Delay(5000);
	PWM_SetDutyCycle(7500);
	HAL_Delay(5000);
}
