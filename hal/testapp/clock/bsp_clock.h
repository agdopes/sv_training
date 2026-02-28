#include "hal_rcc.h"


rcc_osc_config osc_config = {
	.OscillatorType = RCC_SYSCLK_HSI16,
	.HSIEnable = HSION, 
	.HSIDiv = HSI_DIV_2,
	.HSICalibrationValue = HSI_DEFAULT_TRIM 
};

rcc_clock_config clock_config = {
	.clockType = SYSCLK | HCLCK | PCLCK,
	.clockSource = RCC_SYSCLK_HSI16,
	.ahbClockDiv = AHB_DIV_1,
	.apbClockDiv = APB_DIV_1
};
