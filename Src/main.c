/**
 ******************************************************************************
 * @file           : main.c
 * @author         : TODO: Add credits
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx.h>
#include <stdbool.h>

#include "can/can.h"
#include "leds/leds.h"

#include "motors/timers.h"
#include "motors/motor_interface.h"
#include "motors/pwm.h"

typedef enum {
	LEFT_SIDE, RIGHT_SIDE
} ROVER_SIDE;

ROVER_SIDE roverSide;

void SystemClock_Config(void);
void Error_Handler(void);

void SysTick_Handler(void) {
	static int work_led_cnt = 0u;
	static bool work_led_state = false;
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();

	if (work_led_state && work_led_cnt >= 100u) {
		work_led_cnt = 0u;
		work_led_state = false;
		Leds_turnOffLed(LED1);
	}
	if (!work_led_state && work_led_cnt >= 400u) {
		work_led_cnt = 0u;
		work_led_state = true;
		Leds_turnOnLed(LED1);
	}
	work_led_cnt++;
}

int main(void) {
	SystemClock_Config();
	HAL_Init();
	PWM_Init();
	InitTimers();

	MX_CAN1_Init();
	Leds_init();
	Leds_welcomeFLash();

	/* Loop forever */
	while (1) {
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

		setOneSideSpeeds(param, 3);
	}
}

TIM_HandleTypeDef htim4;

void TIM4_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htim4);
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	// Enable HSE oscillator as clock source
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 80;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

void Error_Handler(void) {
	while (1) {
	};
}
