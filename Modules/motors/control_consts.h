/*
 ******************************************************************************
 * @file           : control_consts.h
 * @author         : D. Mucha
 * @brief          : Provides constants to general control (regulators, filters)
 ******************************************************************************
 */

#ifndef MODULES_MOTORS_CONSTS_H
#define MODULES_MOTORS_CONSTS_H

// maximal speed
const int MAX_BOARD_SPEED = 2000;
// speed ramp (higher value causes slower acceleration)
const int PID_SPEED_RAMP = 1;

// alpha parameter of LPF filter (alpha = dt / (RC + dt))
const float LPF_ALPHA = 1;

const float Tp = 0.1; // 100 ms = 8 Mhz clock / (80 kHz tim7 prescaler * 10 tim7 period) -> encoders measure

const float PID_K = 3.5;
const float PID_Td = 0.0;
const float PID_Ti = 1.0;

const float r0 = PID_K * (1 + Tp / (2*PID_Ti) + PID_Td/Tp);
const float r1 = PID_K * (Tp/(2*PID_Ti) - 2 * PID_Td / Tp - 1);
const float r2 = PID_K * PID_Td/ Tp;

#endif /* MODULES_MOTORS_CONSTS_H */
