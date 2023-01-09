/*
 ******************************************************************************
 * @file           : timers.c
 * @author         : D. Mucha
 * @brief          : Timers configuration
 ******************************************************************************
 */

void InitTimers() {
	TIM1_Init();
	TIM2_Init();
	TIM3_Init();
	TIM5_Init();
}

void TIM1_Init() {
}

void TIM2_Init() {
}

void TIM3_Init() {
}

void TIM5_Init() {
}

void TIM1_IRQHandler(void) {
	// g_encoder1Tick = read_encoder_data JACEK HELP!!!
}

void TIM2_IRQHandler(void) {
	//g_encoder2Tick=
}

void TIM3_IRQHandler(void) {
	//g_encoder3Tick=
}
