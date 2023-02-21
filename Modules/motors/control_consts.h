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

// TODO: no idea how to name this pid constant setting
const float PID_SPEED_Kp = 0;
// TODO: no idea how to name this pid constant setting
const int PID_SPEED_Kk = 1;
// TODO: no idea how to name this pid constant setting
const float PID_SPEED_KiTs = 0.05;

// alpha parameter of LPF filter (alpha = dt / (RC + dt))
const float LPF_ALPHA = 1;

const float PID_K = 0;
const float PID_Td = 0;
const float PID_Ti = 0.00007;

#endif /* MODULES_MOTORS_CONSTS_H */
