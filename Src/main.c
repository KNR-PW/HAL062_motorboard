/**
 ******************************************************************************
 * @file           : main.c
 * @author         : TODO: Add credits
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stm32f4xx_hal.h>
#include "motors/timers.h"
#include "motors/motor_interface.h"
#include "motors/pwm.h"

void SysTick_Handler(void) {
	HAL_IncTick();
}

int main(void) {
	HAL_Init();
	PWM_Init();
	PWM_SetDutyCycle(CHANNEL3, 750);
	InitTimers();
//	PWM_SetDutyCycle(CHANNEL1, 750);

	struct singleMotorParam param[3];

	param[0].id = LR;
	param[0].speed = 30;

	param[1].id = LM;
	param[1].speed = 0;

	param[2].id = LF;
	param[2].speed = 0;

//	motor_calibration(CHANNEL1);
	/* Loop forever */
	while (1) {
		setOneSideSpeeds(param, 3);
	}
}
