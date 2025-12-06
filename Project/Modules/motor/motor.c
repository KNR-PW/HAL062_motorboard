#include "motor.h"
#include "pid_consts.h"
#include "timers/timers.h"

extern TIM_HandleTypeDef *tim_pwm;

static float PIDOut = 0.0f;
static float error[3] = {0.0f};

float current_speed = 0.0f;
int32_t target_speed = 0;

// min PWM - 64_000*5% = 3_200
// mid PWM - 64_000*7.5% = 4_800
// max PWM - 64_000*10% = 6_400
static void PWM_SetDutyCycle(uint16_t duty) {
	__HAL_TIM_SET_COMPARE(tim_pwm, PWM_CHANNEL, duty);
}

void updatePID(int16_t encoder_ticks) {
	current_speed = encoder_ticks*TICKS_TO_CM_PER_S;

	error[2] = error[1];
	error[1] = error[0];
	error[0] = (float) target_speed - current_speed;

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
