#include "timers.h"
#include "motor/motor.h"
#include "can/can.h"
#include "leds/leds.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;


TIM_HandleTypeDef *tim_encoder = &htim3; //encoder - TIM3
TIM_HandleTypeDef *tim_pwm = &htim2; // PWM - TIM2
TIM_HandleTypeDef *tim_speed = &htim4; // measuring speed - TIM4
TIM_HandleTypeDef *tim_comwdg = &htim1;
static int16_t g_encoderTick = 0;
static uint8_t counter = 0;

static void TIM_speedPeriodElapsedCallback(TIM_HandleTypeDef *htim);
static void TIM_comwdgCallback(TIM_HandleTypeDef *htim);

void TIM_init(void) {
	HAL_TIM_RegisterCallback(tim_speed, HAL_TIM_PERIOD_ELAPSED_CB_ID, TIM_speedPeriodElapsedCallback);
	HAL_TIM_RegisterCallback(tim_comwdg,HAL_TIM_PERIOD_ELAPSED_CB_ID,TIM_comwdgCallback);
	HAL_TIM_Base_Start_IT(tim_speed);
    HAL_TIM_PWM_Start(tim_pwm, PWM_CHANNEL);
    HAL_TIM_Encoder_Start(tim_encoder, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(tim_comwdg);
}

void TIM_speedPeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	(void) htim;
	counter++;

	g_encoderTick = (int16_t) tim_encoder->Instance->CNT;
	__HAL_TIM_SET_COUNTER(tim_encoder, 0);

	updatePID(g_encoderTick);

	if (counter > 5) {
		counter = 0;
		// testing ids: 50, 51, 52, 53
		union Message data = { .u8={0} };
		data.f32[0] = current_speed;
		data.u32[1] = target_speed;
		CAN_transmit(50, data.u8, 8);
	}
}
void TIM_comwdgCallback(TIM_HandleTypeDef* htim)
{
	target_speed = 0;
}

// TODO add error callback registration 
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim) {(void) htim;}

