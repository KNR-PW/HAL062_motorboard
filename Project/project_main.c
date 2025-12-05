#include "project_main.h"
#include "can/can.h"
#include "leds/leds.h"
#include "motor/motor.h"
#include "timers/timers.h"

void project_main(void)
{
	
	TIM_init();
	CAN_init();

	LED_TURN_ON(LED_ALL);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0x01u);

	HAL_Delay(1000);
	LED_TURN_OFF(LED_ALL);
	HAL_Delay(1000);

	while(1)
	{

	}
}
