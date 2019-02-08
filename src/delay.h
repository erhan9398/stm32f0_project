#ifndef __DELAY_H
#define __DELAY_H


#include "stm32f0xx.h"
void Init_Delay();
void Delay_MicSec(uint32_t micsec);
void Delay_MilliSec(uint32_t millisec);

#endif
