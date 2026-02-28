
#ifndef HAL_RCC_H
#define HAL_RCC_H
/* pending PLL initialization
typedef struct
{

}rcc_pll_config;
*/
#include <stdint.h>

typedef struct
{
	uint32_t OscillatorType;
	uint32_t HSIEnable;
	uint32_t HSIDiv;
	uint32_t HSICalibrationValue;
	// rcc_pll_config pll; //pending pll initialization
}rcc_osc_config;


typedef struct
{
	uint32_t clockType;
	uint32_t clockSource;
	uint32_t ahbClockDiv;
	uint32_t apbClockDiv;

}rcc_clock_config;


extern rcc_osc_config osc_config;
extern rcc_clock_config clock_config;

typedef enum
{
	RCC_SYSCLK_HSI16 = 0,
	RCC_SYSCLK_HSE,
	RCC_SYSCLK_PLL,
	RCC_SYSCLK_LSI,
	RCC_SYSCLK_LSE
}rcc_sysclock_t;

typedef enum
{
	HSIOFF = 0,
	HSION

}rcc_hsi_en_t;

typedef enum
{
	RCC_OK = 0,
	RCC_ERROR,
	RCC_CLOCK_ERROR,
	RCC_BUSY
}rcc_ret_codes_t;

typedef enum
{
	HSI_DIV_1 = 0,
	HSI_DIV_2,
	HSI_DIV_4,
	HSI_DIV_8,
	HSI_DIV_16,
	HSI_DIV_32,
	HSI_DIV_64,
	HSI_DIV_128,
}hsi_div_t;

typedef enum
{
	APB_DIV_1 = 0,
	APB_DIV_2 = 4,
	APB_DIV_4,
	APB_DIV_8,
	APB_DIV_16
}apb_div_t;

typedef enum
{
	AHB_DIV_1 = 0,
	AHB_DIV_2 = 8,
	AHB_DIV_4,
	AHB_DIV_8,
	AHB_DIV_16,
	AHB_DIV_64,
	AHB_DIV_128,
	AHB_DIV_256,
	AHB_DIV_512
}ahb_div_t;

#define SYSCLK	0x1
#define HCLCK	0x02
#define PCLCK	0x04

#define HSI_DEFAULT_TRIM 64U

struct rcc_hal_interface {

	uint32_t (*rcc_osc_init)(rcc_osc_config *oscConfig);

	uint32_t (*rcc_deinit)(rcc_osc_config *oscConfig, rcc_clock_config *clockConfig);

	uint32_t (*rcc_clock_init)(rcc_clock_config *clockConfig);

	// uint32_t (*rcc_pll_initialize)(pll_config *pllConfig); //pending
};

const struct rcc_hal_interface *hal_rcc_get_interface(void);

static inline uint32_t hal_rcc_osc_init(rcc_osc_config *oscConfig)
{
	return hal_rcc_get_interface->rcc_osc_init(oscConfig);
}

static inline uint32_t hal_rcc_deinit(rcc_osc_config *oscConfig, rcc_clock_config *clockConfig)
{
	return hal_rcc_get_interface->rcc_deinit(oscConfig, clockConfig);
}

static inline uint32_t hal_rcc_clock_init(rcc_clock_config *clockConfig)
{
	return hal_rcc_get_interface->rcc_clock_init(clockConfig);
}

#endif
