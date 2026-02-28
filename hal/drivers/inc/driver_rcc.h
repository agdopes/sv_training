#ifndef LLD_RCC_H
#define LLD_RCC_H

#include <stdint.h>

uint32_t getSysClockSource(void);

void setClockEnable(rcc_sysclock_t clocktype);

uint32_t getClockEnableState(rcc_sysclock_t clocktype);

uint32_t getClockRdyState(rcc_sysclock_t clocktype);

void setHSICalibrationTrim(uint32_t hsitrim);

void setHSIDiv(hsi_div_t hsidiv);

void setAPBPrescaler(apb_div_t apbClockDiv);

void setAHBPrescaler(ahb_div_t ahbClockDiv);


#endif
