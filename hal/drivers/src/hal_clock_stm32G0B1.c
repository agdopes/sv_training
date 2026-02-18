#ifdef HAL_RCC_BACKEND_STM32G0B1


//RCC Registers
#define RCC_CR	//base clock address here
#define RCC_ICSCR		0x04 //clock trimming and calibration
#define RCC_CFGR 		0x08 //
#define RCC_PLLCFGR		0x0C
#define RCC_CRRCR		0x14
#define RCC_CIER 		0x18
#define RCC_CIFR		0x1C
#define RCC_CICR		0x20
#define RCC_IOPRSTR		0x24
#define RCC_AHBRSTR		0x28
#define RCC_APBRSTR1 	0x2C
#define RCC_APBRSTR2	0x30
#define RCC_IOPENR		0x34
#define RCC_AHBENR		0x38
#define RCC_APBENR1		0x3C
#define RCC_APBENR2		0x40
#define RCC_IOPSMENR	0x44
#define RCC_AHBSMENR	0x48
#define RCC_APBSMENR1	0x4C
#define RCC_APBSMENR2	0x50
#define RCC_CCIPR		0x54
#define RCC_CCIPR2		0x58
#define RCC_BDCR		0x5C
#define RCC_CSR			0x60

/*

static uint32_t set_clock_control()
{
	set pin 8 rcc_cr to 1
	set 11-13 001 = 2 for 8MHz
}

set_hsi_calibration
{
		RCC_ICSCR HSITRIM
		default of 64 / set pin 14
}

setclockconfiguration
{
	RCC_CFGR
	
	set APB prescaler 14:12 PPRE
	set AHB prescaler 11:8 HPRE
	000  1
	100	 2
	101  4
	110  8
	111  16

	set SW 0:2
	000 HSISYS
	001 HSE 
	001 PLLRCLK 
}

setPLLconfig
{
	PLLREN:28->0 disable pll
}
*/
static uint32_t stm32_osc_init(struct rcc_osc_config *osc_config)
{
	if(osc_config == NULL)
	{
		return RCC_ERROR;
	}
}

static const struct rcc_hal_interface stm32_rcc_interface = {
	.osc_init 	=	stm32_osc_init,
	.clock_init =	stm32_clock_init
};

const struct rcc_hal_interface*	hal_rcc_get_interface(void)
{
	return &stm32_rcc_interface;
}

#endif 


