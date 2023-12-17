# HAL062_motorboard
`git clone --recurse-submodules -j8 https://github.com/KNR-PW/SUB-HAL-062-motorboard.git`

##### Solved Errors:

## In main:
- lack of SysTick function
Going to Infinite Loop

- lack of HAL_Init
NVIC didn't go to Interrupt

## Interrupt
- interrupt variables need to be *volatile* type
