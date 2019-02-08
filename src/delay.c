
#include "delay.h"
#include "stm32f0xx_rcc.h"

uint32_t MicSecTick;

void Init_Delay()
{
	SysTick_Config(SystemCoreClock / 100000);
}

void SysTick_Handler()
{
	if (MicSecTick != 0)
	{
		MicSecTick--;
	}
}

void Delay_MicSec(uint32_t micsec)
{
	MicSecTick = micsec;
	while (MicSecTick);
}

void Delay_MilliSec(uint32_t millisec)
{
	while (millisec--)
	{
		Delay_MicSec(100);
	}
}
