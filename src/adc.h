#ifndef ADC_H_
#define ADC_H_

#include "stm32f0xx_adc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

void Init_Adc(void);
void Read_AdcResult(uint16_t *result);


#endif
