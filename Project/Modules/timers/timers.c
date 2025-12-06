#include "timers.h"
#include "motor/motor.h"
#include "can/can.h"
#include "leds/leds.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

TIM_HandleTypeDef *tim_encoder = &htim3; //encoder - TIM3
TIM_HandleTypeDef *tim_pwm = &htim2; // PWM - TIM2
TIM_HandleTypeDef *tim_speed = &htim4; // measuring speed - TIM4

static int16_t g_encoderTick = 0;

static void TIM_speedPeriodElapsedCallback(TIM_HandleTypeDef *htim);

void TIM_init(void) {
	HAL_TIM_RegisterCallback(tim_speed, HAL_TIM_PERIOD_ELAPSED_CB_ID, TIM_speedPeriodElapsedCallback);
	HAL_TIM_Base_Start_IT(tim_speed);
    HAL_TIM_PWM_Start(tim_pwm, PWM_CHANNEL);
    HAL_TIM_Encoder_Start(tim_encoder, TIM_CHANNEL_ALL);
}

void TIM_speedPeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	(void) htim;

	g_encoderTick = (int16_t) tim_encoder->Instance->CNT;
	__HAL_TIM_SET_COUNTER(tim_encoder, 0);

	updatePID(g_encoderTick);
}

// TODO add error callback registration 
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim) {(void) htim;}

