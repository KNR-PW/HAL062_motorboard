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
	InitTimers();

	struct singleMotorParam param[1];

	param[0].id = LM;
	param[0].speed = 0;

	motor_calibration(CHANNEL2);
	/* Loop forever */
	while (1) {
		if (setOneSideSpeeds(param, 1))
			param[0].speed
//			PWM_SetDutyCycle(CHANNEL2, param[0].speed);
//		PWM_SetDutyCycle(CHANNEL2, 1500);

	}
}
