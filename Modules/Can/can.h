/**
 * @file can.h
 * @brief Provides high level can driver.
 */
#include <stm32f4xx_hal_can.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MODULES_CAN_CAN_H
#define MODULES_CAN_CAN_H

/* Includes ------------------------------------------------------------------*/
// #include <stm32f4xx_hal.h>
// #include "main.h"
// #include "COMMlib.h"
//#include "usart.h"
extern CAN_HandleTypeDef hcan1;
// extern CAN_HandleTypeDef hcan2;


//CAN_TxHeaderTypeDef CAN_TxHeader2;
//uint32_t CAN_TxMailbox2;
//uint8_t CAN_TxData[8];
//
//uint32_t txmailbox;
//CAN_TxHeaderTypeDef canmsg;


//extern void _Error_Handler(char *, int);

void MX_CAN1_Init(void);
// void MX_CAN2_Init(void);

void Can_testMessage(void);


#endif // MODULES_CAN_CAN_H
