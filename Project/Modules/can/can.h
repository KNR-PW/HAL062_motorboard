#ifndef PROJECT_MODULES_CAN_CAN_H
#define PROJECT_MODULES_CAN_CAN_H

#include <stm32f1xx_hal.h>

union Message {
	uint8_t u8[8];
	uint32_t u32[2];
};

void CAN_init(void);
void CAN_transmit(uint8_t id, uint8_t *data, uint8_t data_lenght);

#endif // PROJECT_MODULES_CAN_CAN_H
