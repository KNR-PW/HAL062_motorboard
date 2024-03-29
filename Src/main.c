/**
 ******************************************************************************
 * @file           : main.c
 * @author         : TODO: Add credits
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stm32f4xx_hal.h>

#include "Can/can.h"
#include "leds/leds.h"

#include "motors/timers.h"
#include "motors/motor_interface.h"
#include "motors/pwm.h"

int d = 6000;

static int speed = 6000;
extern struct singleMotorParam param[3];

//extern enum motorSide side = LEFT_SIDE;

void SystemClock_Config(void);
void Error_Handler(void);

int main(void) {
	SystemClock_Config();

	HAL_Init();
	SysTick_Config(80000);

	CAN_Init();
	Leds_init();
	Leds_welcomeFLash();

	PWM_Init();
	updateSpeed(0);
	InitTimers();



	/* Loop forever */
	//find problem that motor speeds up imediatelly
//	updateSpeed(0);
//	param[0].speed = speed;
//	param[0].id = LR;
//	param[1].speed = speed;
//	param[1].id = LM;
//	param[2].speed = speed;
//	param[2].id = LF;


	while (1) {

//		updateSpeed(speed);

//		setOneSideSpeeds(param, 3);
		PWM_SetDutyCycle(CHANNEL2, d);
	}
}

TIM_HandleTypeDef htim4;

void TIM4_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htim4);
}

void SystemClock_Config(void) {
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 4;
	  RCC_OscInitStruct.PLL.PLLN = 80;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 2;
	  RCC_OscInitStruct.PLL.PLLR = 2;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	}


void Error_Handler(void) {
	while (1) {
	};
}

void WWDG_IRQHandler(){

}
