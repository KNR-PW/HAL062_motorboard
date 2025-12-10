/**
 ******************************************************************************
 * @file           : error_handlers.h
 * @author         : Jacek Prokopczuk, Krystian Czechowicz, Adam Rybojad
 * @brief          : Handling all errors that is detected TODO
 ******************************************************************************
 */

#ifndef ERROR_HANDLERS_ERROR_HANDLERS_H_
#define ERROR_HANDLERS_ERROR_HANDLERS_H_

#define MAINBOARD_ERROR_ID 0x69

typedef enum {
	MAINError_test,
	MAINEError_oscConfig,
	MAINEError_clkConfig,
	CANError_init,
	CANError_configFilter,
	CANError_start,
	CANError_activateNotification,

} Error_code;

typedef enum {
	MAINEErrorFunc_test = 1,
	MAINEErrorFunc_sysClkConfig,
	CANErrorFunc_init,

} Error_function;

/* Functions ----------------------------------------------------------------- */

/** 
 ****************************************************************************** 
 * Function to handle the errors that may occur during the runtime 
 * tries to restore the functional state of the program, most often by redoing 
 * some initialization steps
 *
 * The error handling logic is located in the switch-case construction, 
 * each value of Error_function enum corresponds its own case.
 *
 * USAGE:
 *    Error_Handler(Error_function, Error_code);
 *    return; 
 *
 * It is IMPORTANT to return from function after calling Error_Handler,
 * failure to do so will lead to unexpected behavior.
 *
 * @param error_func  solely responsible for the behavior of the error_handler 
 * Does Not influence the error code sent outside via coms
 *
 * @param error_code  solely responsible for the error code sent outside
 * Does Not influence the behavior of error handling  
 ****************************************************************************** 
 */
void Error_Handler(Error_function error_func, Error_code error_code);

// void can_error_to_uart(uint8_t *message, uint8_t ID);

#endif /* ERROR_HANDLERS_ERROR_HANDLERS_H_ */
