#include "driver_rcc.h"
#include "hal_rcc.h"
#include "stm32g0xx.h"

uint32_t getSysClockSource(void)
{
	return (RCC->CFGR & RCC_CFGR_SWS); 
}

void setClockEnable(rcc_sysclock_t clocktype)
{
	switch(clocktype)
	{
	case RCC_SYSCLK_HSI16:
		RCC->CR &= ~(RCC_CR_HSION);
		RCC->CR |= RCC_CR_HSION;
		break;
	case RCC_SYSCLK_HSE:
		RCC->CR &= ~(RCC_CR_HSEON);
		RCC->CR |= RCC_CR_HSEON;
		break;
	case RCC_SYSCLK_PLL:
		RCC->CR &= ~(RCC_CR_PLLON);
		RCC->CR |= RCC_CR_PLLON;
		break;
	case RCC_SYSCLK_LSI:
		RCC->CSR &= ~(RCC_CSR_LSION);
		RCC->CSR |= RCC_CSR_LSION;
		break;
	case RCC_SYSCLK_LSE:
		RCC->BDCR &= ~(RCC_BDCR_LSEON);
		RCC->BDCR |= RCC_BDCR_LSEON;
		break;
	default:
		tmp = RCC_CLOCK_ERROR;
		break;
	}
		
	return tmp;  
}

void setSYSclckSource(rcc_sysclock_t clocktype)
{
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= (clocktype << RCC_CFGR_SW_Pos);
}

uint32_t getClockEnableState(rcc_sysclock_t clocktype)
{
	uint32_t tmp;

	switch(clocktype)
	{
	case RCC_SYSCLK_HSI16:
		tmp = (RCC->CR & RCC_CR_HSION);
		break;
	case RCC_SYSCLK_HSE:
		tmp = (RCC->CR & RCC_CR_HSEON);
		break;
	case RCC_SYSCLK_PLL:
		tmp = (RCC->CR & RCC_CR_PLLON);
		break;
	case RCC_SYSCLK_LSI:
		tmp = (RCC->CSR & RCC_CSR_LSION);
		break;
	case RCC_SYSCLK_LSE:
		tmp = (RCC->BDCR & RCC_BDCR_LSEON);
		break;
	default:
		tmp = RCC_CLOCK_ERROR;
		break;
	}
		
	return tmp;  
}

uint32_t getClockRdyState(rcc_sysclock_t clocktype)
{
	uint32_t tmp;

	switch(clocktype)
	{
	case RCC_SYSCLK_HSI16:
		tmp = (RCC->CR & RCC_CR_HSIRDY);
		break;
	case RCC_SYSCLK_HSE:
		tmp = (RCC->CR & RCC_CR_HSERDY);
		break;
	case RCC_SYSCLK_PLL:
		tmp = (RCC->CR & RCC_CR_PLLRDY);
		break;
	case RCC_SYSCLK_LSI:
		tmp = (RCC->CSR & RCC_CSR_LSIRDY);
		break;
	case RCC_SYSCLK_LSE:
		tmp = (RCC->BDCR & RCC_BDCR_LSERDY);
		break;
	default:
		tmp = RCC_CLOCK_ERROR;
		break;
	}
		
	return tmp;  
}

void setHSICalibrationTrim(uint32_t hsitrim)
{
	RCC->ICSCR &= ~(RCC_ICSCR_HSITRIM);
	RCC->ICSCR |= (hsitrim << RCC_ICSCR_HSITRIM_Pos);
}

void setHSIDiv(hsi_div_t hsidiv)
{
	RCC->CR &= ~(RCC_CR_HSIDIV);	
	RCC->CR |=	(hsidiv << RCC_CR_HSIDIV_Pos);
}

void setAPBPrescaler(uint32_t apbClockDiv)
{
	RCC->CFGR &= ~(RCC_CFGR_PPRE);
	RCC->CFGR |= (apbClockDiv << RCC_CFGR_PPRE_Pos);
}

void setAHBPrescaler(uint32_t ahbClockDiv)
{
	RCC->CFGR &= ~(RCC_CFGR_HPRE);
	RCC->CFGR |= (ahbClockDiv << RCC_CFGR_HPRE_Pos);
}

