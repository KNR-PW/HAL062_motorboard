/**
 ******************************************************************************
 * @file           : main.c
 * @author         : K. Czechowicz, A. Rybojad, J. Prokopczuk, D. Mucha
 * @brief          : Main program body
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------- */

#include <stm32f4xx_hal.h>
#include "Can/can.h"
#include "leds/leds.h"
#include "motors/timers.h"
#include "motors/motor_interface.h"
#include "motors/pwm.h"


/* Global variables ----------------------------------------------------------- */

//static int speed = 0;
extern struct singleMotorParam param[3];

/* Functions declaration ------------------------------------------------------ */

void SystemClock_Config(void);
void Error_Handler(void);


/* Functions ------------------------------------------------------------------ */


/**
 ******************************************************************************
 * @brief          :	Main function initialize all required components
 ******************************************************************************
 */
int main(void) {

	SystemClock_Config(); 	//<Configuration of system clock
	HAL_Init(); 			//< Initialization of HAL Library
	SysTick_Config(80000); 	//<Setting SysTick Time

	CAN_Init(); 			//< CAN initialization

	Leds_init(); 			//< LEDs Initialization
	Leds_welcomeFLash(); 	//< Blinking all LED to inform of Program beginning

	PWM_Init(); 			//< PWM initialization to steering motors
	updateSpeed(0);			//< Setting Speed to 0, to be sure

	InitTimers();			//< Initialization of timers of encoders


	// Infinity loop
	while (1){
	}
}



/**
 ******************************************************************************
 * @brief          :	Function to configure system clock
 ******************************************************************************
 */
void SystemClock_Config(void) {
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  // Configure the main internal regulator output voltage
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	  //Initializes the RCC Oscillators according to the specified parameters
	  //in the RCC_OscInitTypeDef structure.
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

	  // Initializes the CPU, AHB and APB buses clocks
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

/**
 ******************************************************************************
 * @brief          :	Function to handle all detected errors.
 * 						TODO separate files.
 ******************************************************************************
 */
void Error_Handler(void) {
	while (1) {
	};
}
