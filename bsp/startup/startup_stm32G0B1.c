#include<stdint.h>

#define SRAM_START 0x20000000U	//SRAM start address
#define SRAM_SIZE (20U * 1024U) //20KB
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START		SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;


extern uint32_t _ebss;
extern uint32_t _sbss;

int main(void);

void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Tamper_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void Flash_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UCPD_USB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Ch1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Ch2_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Ch4_5_6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM16_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM17_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CEC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void AES_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));


//vector table creation
uint32_t vectors[] __attribute__((section (".isr_vector"))) = {
	STACK_START,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	0,
	(uint32_t)&SVC_Handler,
	0,
	(uint32_t)&PendSV_Handler,
	(uint32_t)&SysTick_Handler,
	(uint32_t)&WWDG_IRQHandler,
	(uint32_t)&PVD_IRQHandler,
	(uint32_t)&RTC_Tamper_IRQHandler,
	(uint32_t)&Flash_IRQHandler,
	(uint32_t)&RCC_CRS_IRQHandler,
	(uint32_t)&EXTI0_1_IRQHandler,
	(uint32_t)&EXTI2_3_IRQHandler,
	(uint32_t)&EXTI4_15_IRQHandler,
	(uint32_t)&UCPD_USB_IRQHandler,
	(uint32_t)&DMA1_Ch1_IRQHandler,
	(uint32_t)&DMA1_Ch2_3_IRQHandler,
	(uint32_t)&DMA1_Ch4_5_6_IRQHandler,
	(uint32_t)&ADC_IRQHandler,
	(uint32_t)&TIM1_BRK_IRQHandler,
	(uint32_t)&TIM1_CC_IRQHandler,
	(uint32_t)&TIM2_IRQHandler,
	(uint32_t)&TIM3_IRQHandler,
	(uint32_t)&TIM6_IRQHandler,
	(uint32_t)&TIM7_IRQHandler,
	(uint32_t)&TIM14_IRQHandler,
	(uint32_t)&TIM15_IRQHandler,
	(uint32_t)&TIM16_IRQHandler,
	(uint32_t)&TIM17_IRQHandler,
	(uint32_t)&I2C1_IRQHandler,
	(uint32_t)&I2C2_IRQHandler,
	(uint32_t)&SPI1_IRQHandler,
	(uint32_t)&SPI2_IRQHandler,
	(uint32_t)&USART1_IRQHandler,
	(uint32_t)&USART2_IRQHandler,
	(uint32_t)&USART3_IRQHandler,
	(uint32_t)&CEC_IRQHandler,
	(uint32_t)&AES_IRQHandler,
}; //store to section isr_vector

void Default_Handler(void)
{
	while(1);
}
void Reset_Handler(void)
{
	//copy .data section to SRAM
	uint32_t size = &_edata - &_sdata;
	uint8_t *pDst = (uint8_t*)&_sdata;
	uint8_t *pSrc = (uint8_t*)&_etext;

	for(uint32_t i=0; i<size;i++)
	{
		*pDst++ = *pSrc++;
	}

	//init the .bss section to zero in SRAM
	size = &_ebss - &_sbss;
	pDst = (uint8_t*)&_sbss;
	for(uint32_t i=0; i<size; i++)
	{
		*pDst++=0;
	}

	main();
}
