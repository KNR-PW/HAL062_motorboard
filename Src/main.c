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

typedef enum {
	LEFT_SIDE, RIGHT_SIDE
} ROVER_SIDE;

ROVER_SIDE roverSide;

void SysTick_Handler(void) {
	HAL_IncTick();
}

int main(void) {
	HAL_Init();
	PWM_Init();
	InitTimers();

	roverSide = LEFT_SIDE;

	struct singleMotorParam param[3];


	if(roverSide == LEFT_SIDE){
	param[0].id = LR;
	param[0].speed = 0;

	param[1].id = LM;
	param[1].speed = 0;

	param[2].id = LF;
	param[2].speed = 0;
	}

	if(roverSide == RIGHT_SIDE){
	param[0].id = RR;
	param[0].speed = 0;

	param[1].id = RM;
	param[1].speed = 0;

	param[2].id = RF;
	param[2].speed = 0;
	}

	/* Loop forever */
	while (1) {

		setOneSideSpeeds(param, 3);
	}
}
