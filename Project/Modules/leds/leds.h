#ifndef PROJECT_MODULES_LEDS_LEDS_H
#define PROJECT_MODULES_LEDS_LEDS_H

#include <stm32f1xx_hal.h>

#define LED_ERROR	GPIO_PIN_9
#define LED_STATUS	GPIO_PIN_8
#define LED_ALL		LED_ERROR | LED_STATUS
#define LED_PORT 	GPIOC

#define LED_TURN_ON(led)	HAL_GPIO_WritePin(LED_PORT, led, 0x01u) 
#define LED_TURN_OFF(led)	HAL_GPIO_WritePin(LED_PORT, led, 0x00u)
#define LED_TOGGLE(led)		HAL_GPIO_TogglePin(LED_PORT, led) 

#endif // PROJECT_MODULES_LEDS_LEDS_H
