/**
 ******************************************************************************
 * @file           : error_handlers.c
 * @author         : Jacek Prokopczuk, Krystian Czechowicz, Adam Rybojad
 * @brief          : Handling all errors that is detected TODO
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------- */

#include <stm32f4xx_hal.h>
#include "error_handlers/error_handlers.h"
#include "leds/leds.h"
//#include "communication/communication.h"

//#include "timers/timers.h"
#include "Can/can.h"
//#include <stm32h7xx_hal.h>

uint8_t ERROR_COUNT = 0;
uint8_t ERROR_ACTIVE = 0;
uint8_t ERROR_CURRENT = 0;

/* Functions ------------------------------------------------------------------- */


/**
 * @see  documentation in the header file (error_handlers.h)
 */
void Error_Handler(Error_function error_func, Error_code error_code) {
	__disable_irq();

	ERROR_ACTIVE = 1;
	uint8_t BOARD_ERROR_ID = 72;
	if (ERROR_COUNT > 3) {
		while (1) {
		}
	}

	if (ERROR_CURRENT == error_func) {
		ERROR_COUNT++;
		return;
	}

	if (ERROR_CURRENT != 0) {
		// we have two different errors
		while (1) {
		}
	}

	ERROR_CURRENT = error_func;

	Can_sendMessage((uint8_t*) &error_code,(uint8_t) BOARD_ERROR_ID);



	/*
	 MAINEErrorFunc_test = 1,
	MAINEErrorFunc_sysClkConfig,
	MAINEErrorFunc_ethInit,
	MAINEErrorFunc_uart3Init,
	MAINEErrorFunc_usbInit,
	MSBErrorFunc_uartInit,
	MSBErrorFunc_pcdInit,
	 */
	switch (error_func) {
	case MAINEErrorFunc_test:
		ERROR_ACTIVE = 0;
		break;
	case MAINEErrorFunc_sysClkConfig:
		while (ERROR_ACTIVE) {
			ERROR_ACTIVE = 0;
			SystemClock_Config();
		}
		break;

	case CANErrorFunc_init:
		while (ERROR_ACTIVE) {
			ERROR_ACTIVE = 0;
			CAN_Init();
		}
		break;




	default:
		break;
	}

	if (ERROR_ACTIVE == 1) {
		while (1) {
		}
	}
	ERROR_COUNT = 0;
	ERROR_CURRENT = 0;

	__enable_irq();

	/// TODO: FInish Error handler!

//	Leds_init();
//	Leds_turnOff(LED_ALL);
//	Leds_turnOn(LED_4);
}
