#include "hal_rcc.h"
#include "driver_rcc.h"

static uint32_t stm32_rcc_osc_init(rcc_osc_config *oscConfig)
{
	uint32_t sysclock = getSysClockSource();
	//oscinit
	if(oscConfig.OscillatorType == RCC_SYSCLK_HSI16)
	{
		if(sysclock == RCC_SYSCLK_HSI16)
		{
			uint32_t clk_en = getClockEnableState(oscConfig.OscillatorType);
			uint32_t clk_rdy = getClockRdyState(oscConfig.OscillatorType);
			if(clk_en & clk_rdy)
			{
				setHSICalibrationTrim(oscConfig.HSICalibrationValue);
				setHSIDiv(oscConfig.HSIDiv);
			}
			else
			{
				return RCC_BUSY;
			}
		}
		else
		{
			setHSIDiv(oscConfig.HSIDiv);
			if(oscConfig.HSIEnable)
			{
				setClockEnable(oscConfig.OscillatorType);
			}
			while(getClockRdyState(oscConfig.OscillatorType)==0U)
			{
				// gettick-tickstart > hsi_timeout_val
				// {
				// // 	return RCC_TIMEOUT;
				// }

			}
			setHSICalibrationTrim(oscConfig.HSICalibrationValue);
		}

	}
	else
	{
		//other osc type not yet supported
		return RCC_CLOCK_ERROR;
	}
}

static uint32_t stm32_rcc_deinit(rcc_osc_config *oscConfig)
{
	//deinit
}

static uint32_t stm32_rcc_clock_init(rcc_clock_config *clkConfig)
{
	//clockinit
	if((clkConfig.clockType & HCLCK) == HCLCK)
	{
		setAHBPrescaler(clkConfig.ahbClockDiv);	
	}
	if((clkConfig.clockType & SYSCLK) == SYSCLK)
	{
		if(getSysClockSource() != clkConfig.clockSource)
		{
			if(getClockRdyState(clkConfig.clockSource) = 0U)
			{
				return RCC_TIMEOUT;

			}
			setSYSclckSource(clkConfig.clockSource);
			//gettick sync
		}
		while(getSysClockSource() != clkConfig.clockSource)
		{
			//set timeout
			for(uint32_t i = 0; i < 100000; i++)
			{
				//temp deay
			}
			return RCC_TIMEOUT;
		}
	}
	if((clkConfig.clockType & PCLCK) == PCLCK)
	{
		setAPBPrescaler(clkConfig.apbClockDiv);
	}
	//update systemcoreclock
	//init SYStick
}

static const struct rcc_hal_interface stm32_rcc_interface = {
	.rcc_osc_init 	= stm32_rcc_osc_init,
	.rcc_deinit 	= stm32_rcc_deinit,
	.rcc_clock_init	= stm32_rcc_clock_init
};

const struct rcc_hal_interface *hal_rcc_get_interface(void){
	return &stm32_rcc_interface;
}
