/*
 * @file timers.h
 * @brief Timers configuration
 */
#ifndef MOTORS_TIMERS_H_
#define MOTORS_TIMERS_H_
#include "stdint.h"

// [Timer - Encoder - Pin] mapping for our custom motor board
// TIM1_CH1 - ENK1_A - PA8
// TIM1_CH1 - ENK1_B - PA9
// TIM2_CH1 - ENK2_A - PA5
// TIM2_CH2 - ENK2_B - PB3
// TIM3_CH1 - ENK3_A - PA6
// TIM3_CH2 - ENK3_B - PA7

// [Timer - PWM - Pin] PWM generation for our custom motor board
// TIM5_CH1 - PWM1 - PA0
// TIM5_CH2 - PWM2 - PA1
// TIM5_CH3 - PWM3 - PA2

// @brief Initialize all timers
void InitTimers();

// @brief Initialize encoder1 timer
void TIM1_Init();

// @brief Initialize encoder2 timer
void TIM2_Init();

// @brief Initialize encoder3 timer
void TIM3_Init();

// @brief Initialize PWM timer
void TIM5_Init();

// @brief Read encoder1 data
void TIM1_IRQHandler(void);

// @brief Read encoder2 data
void TIM2_IRQHandler(void);

// @brief Read encoder3 data
void TIM3_IRQHandler(void);

// @brief Global variable for data from encoder1
volatile int32_t g_encoder1Tick;
// @brief Global variable for data from encoder2
volatile int32_t g_encoder2Tick;
// @brief Global variable for data from encoder3
volatile int32_t g_encoder3Tick;

#endif /* MOTORS_TIMERS_H_ */
