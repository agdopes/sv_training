/**
 * @file hal_clock.h
 * @brief Generic clock Hardware Abstraction Layer Interface
 * 
 * This file defines a platform-independent clock interface using function pointers.
 * Platform-specific implementations must provide hal_clock_get_interface() function.
 * 
 * @defgroup HAL_CLOCK CLOCK Hardware Abstraction Layer
 * @{
 */

#ifndef HAL_CLOCK_H
#define HAL_CLOCK_H

#include<stdint.h>

/*
// RCC
HSI16 RC
	HSISYS 
		SYSCLK
			AHBPRESC - HCLCK
					HCLK8 -	
					APBPRESC - PCLK
						TIMPCLK		
*/
struct rcc_osc_config {
	uint32_t OscillatorType;
	uint32_t HSIState;
	uint32_t HSIDiv;
	uint32_t HSICalibrationValue;
};

struct rcc_clock_config {
	uint32_t ClockType;
	uint32_t SYSCLKSource;
	uint32_t AHBCLKDiv;
	uint32_t APBCLKDiv;
};

struct rcc_hal_interface {

	uint32_t (*osc_init)(struct rcc_osc_config *osc_config);

	uint32_t (*clock_init)(struct rcc_clock_config *clock_config);
};

const struct rcc_hal_interface* hal_rcc_get_interface(void);

static inline uint32_t rcc_osc_init(struct rcc_osc_config *osc_config)
{
	return hal_rcc_get_interface()->osc_init(osc_config);
}

static inline uint32_t rcc_clock_init(struct rcc_clock_config *clock_config)
{
	return hal_rcc_get_interface()->clock_init(clock_config);
}
