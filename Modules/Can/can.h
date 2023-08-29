
#ifndef MODULES_CAN_CAN_H
#define MODULES_CAN_CAN_H

#include <stm32f4xx_hal_can.h>

extern CAN_HandleTypeDef hcan1;

void CAN_Init(void);

void Can_testMessage(void);


#endif // MODULES_CAN_CAN_H
